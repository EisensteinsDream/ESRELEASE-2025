#include "utility/datetime.h"

// NOTE: global function descriptions in header.

// static functions ---------------------------------------------------------------------------------------------------------

// the base function to set all values of the time. Has an is24 boolean to adjust to either 12 or 24 hour time.

static bool p_setDateTimeBase(const uint16_t year, const uint8_t month, const uint8_t day, const uint8_t hour, const uint8_t second, const uint8_t minute, const bool pm, PLEX_DATETIME* toSet, const bool is24)
{
	toSet->second = second;
	toSet->minute = minute;
	toSet->hour = hour;
	toSet->day = day;
	toSet->month = month;
	toSet->year = year;
	toSet->pm = pm;

	if(!is24)
	{
		toSet->hour %= 12;
		if(!hour) toSet->hour = 12;
	}

	return true;
}

// sets a datetime to the current real world time. Has an is24 boolean to adjust to either 12 or 24 hour time.

static bool p_setCurrentDateTime(PLEX_DATETIME* toSet, const bool is24, const size_t errorline, const char* const errorfile)
{
	time_t source;
	struct tm* values;

	#if (PLEX_CORE_IS_UNIX)
		struct tm buff;
	#endif

	uint16_t year = 0;
	uint8_t month = 0;
	uint8_t day = 0;
	uint8_t hour = 0;
	uint8_t second = 0;
	uint8_t minute = 0;
	bool pm = false;

	if(time(&source) == -1)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DATETIME, PLEX_ERROR_BADOPERATION, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_DATETIME_ONGETCURRENTLOW, PLEX_ERRORMESS_OP_CTIME, errorline, errorfile);
		return false;
	}

	#if (PLEX_CORE_IS_UNIX)
		values = localtime_r(&source, &buff);
	#elif
		values = localtime(&source);
	#endif

	if(values == NULL)
	{
		PLEX_FAKESTRING_100 errMess = PLEX_createString100(PLEX_ERRORMESS_OP_CLOCALTIME);
		PLEX_FAKESTRING_100 errMess2 = PLEX_createString100(PLEX_ERRORMESS_DATETIME_ERRNO);
		PLEX_FAKESTRING_100 errMess3 = PLEX_createStringFromNumber100(errno);
		PLEX_FAKESTRING_100 errMess4 = PLEX_createString100(PLEX_ERRORMESS_DATETIME_ERRNO2);

		errMess = PLEX_mergeString100(errMess, errMess2);
		errMess = PLEX_mergeString100(errMess, errMess3);
		errMess = PLEX_mergeString100(errMess, errMess4);

		PLEX_errorInt(PLEX_ERROR_CATEGORY_DATETIME, PLEX_ERROR_BADOPERATION, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_DATETIME_ONGETCURRENTLOW, PLEX_fts(errMess), errorline, errorfile);
		return false;
	}

	second = values->tm_sec;
	minute = values->tm_min;
	hour = values->tm_hour;
	day = values->tm_mday;
	month = values->tm_mon + 1;
	year = values->tm_year + 1900;
	pm = values->tm_hour >= 12;

	return p_setDateTimeBase(year, month, day, hour, second, minute, pm, toSet, is24);
}

// returns whether or not a year is a leap year from the year number

static bool p_isLeapYearBase(const uint32_t year)
{
	return year % 4 && (!(year % 100) || year % 400);
}

// returns whether or not a year is a leapyear from the datetime

static bool p_isLeapYear(const PLEX_DATETIME* from)
{
	return p_isLeapYearBase(from->year);
}

// returns the length of the month. With January being month 0 and December being month 11

static uint64_t p_monthLen(const bool isLeapYear, const uint64_t month)
{
	const size_t aMonth = month % 12;

	switch(aMonth)
	{
		case 3:
		case 5:
		case 8:
		case 10:
			return 30;
		case 1:
			return 28 + isLeapYear;
		break;
	};


	return 31;
}

// returns the length of a year in days taking account for the leap year from year date

static uint64_t p_yearDaysBase(const uint32_t onYear)
{
	return 365 + p_isLeapYearBase(onYear);
}

// returns the length of a year in days taking account for the leap year

static uint64_t p_yearDays(const PLEX_DATETIME* from)
{
	return p_yearDaysBase(from->year);
}

// returns the length of a month in days taking account for the leap year

static uint64_t p_monthDays(const bool isLeapYear, const PLEX_DATETIME* from)
{
	uint64_t monthDays = 0;

	// month 0 is January and month 11 is December
	if(from->month > 0) monthDays += 31;
	if(from->month > 1) monthDays += 28 + isLeapYear;
	if(from->month > 2) monthDays += 31;
	if(from->month > 3) monthDays += 30;
	if(from->month > 4) monthDays += 31;
	if(from->month > 5) monthDays += 30;
	if(from->month > 6) monthDays += 31;
	if(from->month > 7) monthDays += 31;
	if(from->month > 8) monthDays += 30;
	if(from->month > 9) monthDays += 31;
	if(from->month > 10) monthDays += 30;

	return monthDays;
}

// converts the number of days to years leaving the remainder as the days value

static uint64_t p_dayYears(const PLEX_DATETIME* from)
{
	uint64_t dayCount = from->day;
	uint64_t dayYears = 0;
	uint64_t onYear = from->year;
	uint64_t yearLen = p_yearDays(from);

	while(dayCount > yearLen)
	{
		dayCount -= yearLen;

		++dayYears;
		onYear = from->year + dayYears;

		yearLen = p_yearDaysBase(onYear); // keep after incrementing dayYears
	}

	return dayYears;
}

// converts the number of days to months leaving the remainder as the days value

static uint64_t p_dayMonths(bool isLeapYear, const PLEX_DATETIME* from)
{
	uint64_t monthCount = 0;
	uint64_t monthDays = from->day;
	uint64_t yearOn = from->year;

	uint64_t onMonth = from->month;
	uint64_t aMonth = onMonth % 12;
	uint64_t monthLen = p_monthLen(isLeapYear, aMonth);

	while(monthDays > monthLen || onMonth > 12)
	{
		monthDays -= monthLen;
		++monthCount;

		if(aMonth) --onMonth;
		else
		{
			onMonth = 11;
			--yearOn;

			isLeapYear = p_isLeapYearBase(yearOn);
		}

		aMonth = onMonth % 12;

		monthLen = p_monthLen(isLeapYear, aMonth);
	}

	return monthCount;
}

// returns a new datetime with the values equaling the difference between two dates

static PLEX_DATETIME p_getDifferenceDateTimeBase(const PLEX_DATETIME* from, const PLEX_DATETIME* from2, const bool is24, const size_t errorline, const char* const errorfile)
{
	PLEX_DATETIME lFrom, lFrom2;

	PLEX_DATETIME ret;

	uint8_t hour = 0;
	uint8_t hour2 = 0;

	bool swap = false;

	memset(&ret, 0, sizeof(ret));

	if(from2->year < from->year)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DATETIME, PLEX_ERROR_MINMAXREVERSE, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DATETIME_ONGETDIFFERENCELOW, PLEX_ERRORMESS_DATETIME_TIMEYEAR, errorline, errorfile);
		swap = true;
	}else{
		if(from2->year == from->year && from2->month < from->month)
		{
			PLEX_errorInt(PLEX_ERROR_CATEGORY_DATETIME, PLEX_ERROR_MINMAXREVERSE, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DATETIME_ONGETDIFFERENCELOW, PLEX_ERRORMESS_DATETIME_TIMEMONTH, errorline, errorfile);
			swap = true;
		}else{
			if(from2->month == from->month && from2->day < from->day)
			{
				PLEX_errorInt(PLEX_ERROR_CATEGORY_DATETIME, PLEX_ERROR_MINMAXREVERSE, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DATETIME_ONGETDIFFERENCELOW, PLEX_ERRORMESS_DATETIME_TIMEDAY, errorline, errorfile);
				swap = true;
			}else{
				if(from2->day == from->day && from2->hour < from->hour)
				{
					PLEX_errorInt(PLEX_ERROR_CATEGORY_DATETIME, PLEX_ERROR_MINMAXREVERSE, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DATETIME_ONGETDIFFERENCELOW, PLEX_ERRORMESS_DATETIME_TIMEHOUR, errorline, errorfile);
					swap = true;
				}else{
					if(from2->hour == from->hour && from2->minute < from->minute)
					{
						PLEX_errorInt(PLEX_ERROR_CATEGORY_DATETIME, PLEX_ERROR_MINMAXREVERSE, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DATETIME_ONGETDIFFERENCELOW, PLEX_ERRORMESS_DATETIME_TIMEMINUTE, errorline, errorfile);
						swap = true;
					}else{
						if(from2->minute == from->minute && from2->second < from->second)
						{
							PLEX_errorInt(PLEX_ERROR_CATEGORY_DATETIME, PLEX_ERROR_MINMAXREVERSE, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DATETIME_ONGETDIFFERENCELOW, PLEX_ERRORMESS_DATETIME_TIMESECOND, errorline, errorfile);
							swap = true;
						}
					}
				}
			}
		}
	}

	if(swap)
	{
		lFrom = *from2;
		lFrom2 = *from;
	}else{
		lFrom = *from;
		lFrom2 = *from2;
	}

	hour = lFrom.hour;
	hour2 = lFrom2.hour;

	if(!is24)
	{
		if(hour == 12 && lFrom.pm) hour += 12;
		if(hour2 == 12 && lFrom2.pm) hour2 += 12;
	}

	ret.year = lFrom2.year - lFrom.year;
	ret.month = lFrom2.month - lFrom.month;
	ret.day = lFrom2.day - lFrom.day;
	ret.hour = lFrom2.hour - lFrom.hour;
	ret.minute = lFrom2.minute - lFrom.minute;
	ret.second = lFrom2.second - lFrom.second;
	ret.pm = false;

	if(!is24)
	{
		if(ret.hour > 12)
		{
			ret.hour = ret.hour % 12;
			ret.pm = true;
		}

		if(hour == 0) ret.hour = 12;
	}

	return ret;
}

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

// specialized functions ----------------------------------------------------------------------------------------------------

PLEX_DATETIME PLEX_blankDateTime()
{
	PLEX_DATETIME ret;

	memset(&ret, 0, sizeof(ret));

	return ret;
}

// setters ------------------------------------------------------------------------------------------------------------------

bool PLEX_setDateTimeInt(const uint16_t year, const uint8_t month, const uint8_t day, const uint8_t hour, const uint8_t second, const uint8_t minute, const bool pm, PLEX_DATETIME* toSet, const size_t errorline, const char* const errorfile)
{
	if(toSet == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DATETIME, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DATETIME_ONSETTIMEDATE, PLEX_ERRORMESS_DATETIME_DATETIME, errorline, errorfile);
		return false;
	}

	return p_setDateTimeBase(year, month, day, hour, second, minute, pm, toSet, PLEX_DEF_24HourTime());
}

bool PLEX_setDateTime12Int(const uint16_t year, const uint8_t month, const uint8_t day, const uint8_t hour, const uint8_t second, const uint8_t minute, const bool pm, PLEX_DATETIME* toSet, const size_t errorline, const char* const errorfile)
{
	if(toSet == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DATETIME, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DATETIME_ONSETTIMEDATE12, PLEX_ERRORMESS_DATETIME_DATETIME, errorline, errorfile);
		return false;
	}

	return p_setDateTimeBase(year, month, day, hour, second, minute, pm, toSet, false);
}

bool PLEX_setDateTime24Int(const uint16_t year, const uint8_t month, const uint8_t day, const uint8_t hour, const uint8_t second, const uint8_t minute, const bool pm, PLEX_DATETIME* toSet, const size_t errorline, const char* const errorfile)
{
	if(toSet == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DATETIME, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DATETIME_ONSETTIMEDATE24, PLEX_ERRORMESS_DATETIME_DATETIME, errorline, errorfile);
		return false;
	}

	return p_setDateTimeBase(year, month, day, hour, second, minute, pm, toSet, true);
}

bool PLEX_setCurrentDateTimeInt(PLEX_DATETIME* toSet, const size_t errorline, const char* const errorfile)
{
	if(toSet == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DATETIME, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DATETIME_ONSETCURRENT, PLEX_ERRORMESS_DATETIME_ONSETCURRENT, errorline, errorfile);
		return false;
	}

	return p_setCurrentDateTime(toSet, PLEX_DEF_24HourTime(), errorline, errorfile);
}

bool PLEX_setCurrentDateTime12Int(PLEX_DATETIME* toSet, const size_t errorline, const char* const errorfile)
{
	if(toSet == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DATETIME, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DATETIME_ONSETCURRENT12, PLEX_ERRORMESS_DATETIME_DATETIME, errorline, errorfile);
		return false;
	}

	return p_setCurrentDateTime(toSet, false, errorline, errorfile);
}

bool PLEX_setCurrentDateTime24Int(PLEX_DATETIME* toSet, const size_t errorline, const char* const errorfile)
{
	if(toSet == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DATETIME, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DATETIME_ONSETCURRENT24, PLEX_ERRORMESS_DATETIME_DATETIME, errorline, errorfile);
		return false;
	}

	return p_setCurrentDateTime(toSet, true, errorline, errorfile);
}


// forward declared in error.h. You never need to call this manually.

void PLEX_setErrorLogDate()
{
	PLEX_DATETIME current;

	uint16_t year = 0;
	uint8_t month = 0, day = 0, hour = 0, minute = 0, second = 0;

	PLEX_setCurrentDateTime24(&current);

	year = PLEX_getYearDateTime(&current);
	month = PLEX_getMonthDateTime(&current);
	day = PLEX_getDayDateTime(&current);
	hour = PLEX_getHourDateTime(&current);
	minute = PLEX_getMinuteDateTime(&current);
	second = PLEX_getSecondDateTime(&current);

	PLEX_setErrorLogDateInt(year, month, day, hour % 24, minute, second); // < defined in error.c. You never need to manually call this.
}

// getters ------------------------------------------------------------------------------------------------------------------

bool PLEX_getDateTimeInt(uint8_t* day, uint8_t* month, uint16_t* year, const PLEX_DATETIME* from, const size_t errorline, const char* const errorfile)
{
	if(day == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DATETIME, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DATETIME_ONGETMYD, PLEX_ERRORMESS_DATETIME_TIMEDAY, errorline, errorfile);
		return false;
	}

	*day = 0;

	if(month == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DATETIME, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DATETIME_ONGETMYD, PLEX_ERRORMESS_DATETIME_TIMEMONTH, errorline, errorfile);
		return false;
	}

	*month = 0;

	if(year == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DATETIME, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DATETIME_ONGETMYD, PLEX_ERRORMESS_DATETIME_TIMEYEAR, errorline, errorfile);
		return false;
	}

	*year = 0;

	if(from == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DATETIME, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DATETIME_ONGETMYD, PLEX_ERRORMESS_DATETIME_DATETIME, errorline, errorfile);
		return false;
	}

	*day = from->day;
	*month = from->month;
	*year = from->year;

	return true;
}

bool PLEX_getTimeDateTimeInt(uint8_t* minute, uint8_t* second, uint8_t* hour, bool* pm, const PLEX_DATETIME* from, const size_t errorline, const char* const errorfile)
{
	if(minute == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DATETIME, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DATETIME_ONGETMSH, PLEX_ERRORMESS_DATETIME_TIMEMINUTE, errorline, errorfile);
		return false;
	}

	*minute = 0;

	if(second == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DATETIME, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DATETIME_ONGETMSH, PLEX_ERRORMESS_DATETIME_TIMESECOND, errorline, errorfile);
		return false;
	}

	*second = 0;

	if(hour == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DATETIME, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DATETIME_ONGETMSH, PLEX_ERRORMESS_DATETIME_TIMEHOUR, errorline, errorfile);
		return false;
	}

	*hour = 0;

	if(pm == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DATETIME, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DATETIME_ONGETMSH, PLEX_ERRORMESS_DATETIME_AMPM, errorline, errorfile);
		return false;
	}

	*pm = false;

	if(from == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DATETIME, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DATETIME_ONGETMSH, PLEX_ERRORMESS_DATETIME_DATETIMESMALL, errorline, errorfile);
		return false;
	}

	*hour = from->hour;
	*minute = from->minute;
	*second = from->second;
	*pm = from->pm;

	return true;
}

uint8_t PLEX_getDayDateTimeInt(const PLEX_DATETIME* from, const size_t errorline, const char* const errorfile)
{ 
	if(from == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DATETIME, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DATETIME_ONGETDAY, PLEX_ERRORMESS_DATETIME_TIMEDAY, errorline, errorfile);
		return 0;
	}

	return from->day;
}

uint8_t PLEX_getMonthDateTimeInt(const PLEX_DATETIME* from, const size_t errorline, const char* const errorfile)
{
	if(from == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DATETIME, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DATETIME_ONGETMONTH, PLEX_ERRORMESS_DATETIME_TIMEMONTH, errorline, errorfile);
		return 0;
	}

	return from->month;
}

uint16_t PLEX_getYearDateTimeInt(const PLEX_DATETIME* from, const size_t errorline, const char* const errorfile)
{
	if(from == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DATETIME, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DATETIME_ONGETYEAR, PLEX_ERRORMESS_DATETIME_TIMEYEAR, errorline, errorfile);
		return 0;
	}

	return from->year;
}

uint8_t PLEX_getMinuteDateTimeInt(const PLEX_DATETIME* from, const size_t errorline, const char* const errorfile)
{
	if(from == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DATETIME, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DATETIME_ONGETMINUTE, PLEX_ERRORMESS_DATETIME_TIMEMINUTE, errorline, errorfile);
		return 0;
	}

	return from->minute;
}

uint8_t PLEX_getSecondDateTimeInt(const PLEX_DATETIME* from, const size_t errorline, const char* const errorfile)
{
	if(from == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DATETIME, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DATETIME_ONGETSECOND, PLEX_ERRORMESS_DATETIME_TIMESECOND, errorline, errorfile);
		return 0;
	}

	return from->second;
}

uint8_t PLEX_getHourDateTimeInt(const PLEX_DATETIME* from, const size_t errorline, const char* const errorfile)
{
	if(from == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DATETIME, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DATETIME_ONGETHOUR, PLEX_ERRORMESS_DATETIME_TIMEHOUR, errorline, errorfile);
		return 0;
	}

	return from->hour;
}

bool PLEX_getPMDateTimeInt(const PLEX_DATETIME* from, const size_t errorline, const char* const errorfile)
{
	if(from == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DATETIME, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DATETIME_ONGETPM, PLEX_ERRORMESS_DATETIME_AMPM, errorline, errorfile);
		return false;
	}

	return from->pm;
}

PLEX_DATETIME PLEX_getDifferenceDateTimeInt(const PLEX_DATETIME* from, const PLEX_DATETIME* from2, const size_t errorline, const char* const errorfile)
{
	if(from == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DATETIME, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DATETIME_ONGETDIFFERENCE, PLEX_ERRORMESS_DATETIME_DATETIME, errorline, errorfile);
		return PLEX_blankDateTime();
	}

	if(from2 == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DATETIME, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DATETIME_ONGETDIFFERENCE, PLEX_ERRORMESS_DATETIME_DATETIME2, errorline, errorfile);
		return PLEX_blankDateTime();
	}

	return p_getDifferenceDateTimeBase(from, from2, PLEX_DEF_24HourTime(), errorline, errorfile);
}

PLEX_DATETIME PLEX_getDifferenceDateTime12Int(const PLEX_DATETIME* from, const PLEX_DATETIME* from2, const size_t errorline, const char* const errorfile)
{
	if(from == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DATETIME, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DATETIME_ONGETDIFFERENCE12, PLEX_ERRORMESS_DATETIME_DATETIME, errorline, errorfile);
		return PLEX_blankDateTime();
	}

	if(from2 == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DATETIME, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DATETIME_ONGETDIFFERENCE12, PLEX_ERRORMESS_DATETIME_DATETIME2, errorline, errorfile);
		return PLEX_blankDateTime();
	}

	return p_getDifferenceDateTimeBase(from, from2, false, errorline, errorfile);
}

PLEX_DATETIME PLEX_getDifferenceDateTime24Int(const PLEX_DATETIME* from, const PLEX_DATETIME* from2, const size_t errorline, const char* const errorfile)
{
	if(from == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DATETIME, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DATETIME_ONGETDIFFERENCE24, PLEX_ERRORMESS_DATETIME_DATETIME, errorline, errorfile);
		return PLEX_blankDateTime();
	}

	if(from2 == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DATETIME, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DATETIME_ONGETDIFFERENCE24, PLEX_ERRORMESS_DATETIME_DATETIME2, errorline, errorfile);
		return PLEX_blankDateTime();
	}

	return p_getDifferenceDateTimeBase(from, from2, true, errorline, errorfile);
}

uint64_t PLEX_getTotalDaysDateTimeInt(const PLEX_DATETIME* from, const size_t errorline, const char* const errorfile)
{
	bool isLeapYear = false;

	uint64_t yearDays = 0;
	uint64_t monthDays = 0;

	if(from == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DATETIME, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DATETIME_ONGETTOTALDAY, PLEX_ERRORMESS_DATETIME_TIMETOTALDAYS, errorline, errorfile);
		return 0;
	}

	isLeapYear = p_isLeapYear(from);
	yearDays = p_yearDays(from);
	monthDays = p_monthDays(isLeapYear, from);

	return yearDays + monthDays + from->day;
}

uint64_t PLEX_getTotalMonthsDateTimeInt(const PLEX_DATETIME* from, const size_t errorline, const char* const errorfile)
{
	uint64_t ret = 0;

	bool isLeapYear = false;

	if(from == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DATETIME, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DATETIME_ONGETTOTALMONTH, PLEX_ERRORMESS_DATETIME_DATETIME, errorline, errorfile);
		return 0;
	}

	isLeapYear = p_isLeapYear(from);

	ret += from->year * 12;
	ret += from->month;
	ret += p_dayMonths(isLeapYear, from);

	return ret;
}

uint64_t PLEX_getTotalYearsDateTimeInt(const PLEX_DATETIME* from, const size_t errorline, const char* const errorfile)
{
	uint64_t ret = 0;

	if(from == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DATETIME, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DATETIME_ONGETTOTALYEAR, PLEX_ERRORMESS_DATETIME_DATETIME, errorline, errorfile);
		return 0;
	}

	ret += from->year;
	ret += from->month/12;
	ret += p_dayYears(from);

	return ret;
}

uint64_t PLEX_getTotalHoursDateTimeInt(const PLEX_DATETIME* from, const size_t errorline, const char* const errorfile)
{
	uint64_t ret = 0;

	if(from == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DATETIME, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DATETIME_ONGETTOTALHOUR, PLEX_ERRORMESS_DATETIME_DATETIME, errorline, errorfile);
		return 0;
	}

	ret = PLEX_getTotalSecondsDateTime(from)/360;

	return ret;
}

uint64_t PLEX_getTotalMinutesDateTimeInt(const PLEX_DATETIME* from, const size_t errorline, const char* const errorfile)
{
	uint64_t ret = 0;

	if(from == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DATETIME, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DATETIME_ONGETTOTALMINUTE, PLEX_ERRORMESS_DATETIME_DATETIME, errorline, errorfile);
		return 0;
	}

	ret = PLEX_getTotalSecondsDateTime(from)/60;

	return ret;
}

uint64_t PLEX_getTotalSecondsDateTimeInt(const PLEX_DATETIME* from, const size_t errorline, const char* const errorfile)
{
	uint64_t totalDateTime = 0;
	uint64_t ret = 0;

	if(from == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DATETIME, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DATETIME_ONGETTOTALSECOND, PLEX_ERRORMESS_DATETIME_DATETIME, errorline, errorfile);
		return 0;
	}

	totalDateTime = PLEX_getTotalDaysDateTimeInt(from, errorline, errorfile);

	ret += from->second;
	ret += from->minute * 60;
	ret += from->hour * 360;
	ret = totalDateTime * 86400;

	return ret;
}
