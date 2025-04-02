#ifndef PLEX_DATETIME_H
#define PLEX_DATETIME_H

#include "utility/defaults.h"

// This unit stores realworld datetime information which can be created manually or taken from the system directly (ie. acquire the current date and time). It can also work with custom created and generated dates and time if you wish to use those for any reason. It does plenty of math, too, to determine the amount of years, months, days, seconds, minutes, etc. between dates. It can do both 24 and 12 hour time. If the default for 24 hour time is true it assumes all non-specific time functions are 24, and 12 likewise.

// NOTE: This is an independent unit. Not a unit with an accompanying state machine. It has no 'start, update, or end' functions that need to be called to operate.

// macro functions and macros -----------------------------------------------------------------------------------------------

// ARGUMENTS: (const uint16_t year, const uint8_t month, const uint8_t day, const uint8_t hour, const uint8_t second, const uint8_t minute, const bool pm, PLEX_DATETIME* toSet)- returns bool

#define PLEX_setDateTime(year, month, day, hour, second, minute, pm, toSet) PLEX_setDateTimeInt(year, month, day, hour, second, minute, pm, toSet, __LINE__, __FILE__)

// ARGUMENTS: (const uint16_t year, const uint8_t month, const uint8_t day, const uint8_t hour, const uint8_t second, const uint8_t minute, const bool pm, PLEX_DATETIME* toSet)- returns bool

#define PLEX_setDateTime12(year, month, day, hour, second, minute, pm, toSet) PLEX_setDateTime12Int(year, month, day, hour, second, minute, pm, toSet, __LINE__, __FILE__)

// ARGUMENTS: (const uint16_t year, const uint8_t month, const uint8_t day, const uint8_t hour, const uint8_t second, const uint8_t minute, const bool pm, PLEX_DATETIME* toSet)- returns bool

#define PLEX_setDateTime24(year, month, day, hour, second, minute, pm, toSet) PLEX_setDateTime24Int(year, month, day, hour, second, minute, pm, toSet, __LINE__, __FILE__)

// ARGUMENTS: (PLEX_DATETIME* toSet)- returns bool

#define PLEX_setCurrentDateTime(toSet) PLEX_setCurrentDateTimeInt(toSet, __LINE__, __FILE__)

// ARGUMENTS: (PLEX_DATETIME* toSet)- returns bool

#define PLEX_setCurrentDateTime12(toSet) PLEX_setCurrentDateTime12Int(toSet, __LINE__, __FILE__)

// ARGUMENTS: (PLEX_DATETIME* toSet)- returns bool

#define PLEX_setCurrentDateTime24(toSet) PLEX_setCurrentDateTime24Int(toSet, __LINE__, __FILE__)

// ARGUMENTS: (uint8_t* day, uint8_t* month, uint16_t* year, const PLEX_DATETIME* from)- returns bool

#define PLEX_getDateTime(day, month, year, from) PLEX_getDateTimeInt(day, month, year, from, __LINE__, __FILE__)

// ARGUMENTS: (uint8_t* minute, uint8_t* second, uint8_t* hour, bool* pm, const PLEX_DATETIME* from)- returns bool

#define PLEX_getTimeDateTime(minute, second, hour, pm, from) PLEX_getTimeDateTimeInt(minute, second, hour, pm, from, __LINE__, __FILE__)

// ARGUMENTS: (const PLEX_DATETIME* from)- returns uint8_t

#define PLEX_getDayDateTime(from) PLEX_getDayDateTimeInt(from, __LINE__, __FILE__)

// ARGUMENTS: (const PLEX_DATETIME* from)- returns uint8_t

#define PLEX_getMonthDateTime(from) PLEX_getMonthDateTimeInt(from, __LINE__, __FILE__)

// ARGUMENTS: (const PLEX_DATETIME* from)- returns uint16_t

#define PLEX_getYearDateTime(from) PLEX_getYearDateTimeInt(from, __LINE__, __FILE__)

// ARGUMENTS: (const PLEX_DATETIME* from)- returns uint8_t

#define PLEX_getMinuteDateTime(from) PLEX_getMinuteDateTimeInt(from, __LINE__, __FILE__)

// ARGUMENTS: (const PLEX_DATETIME* from)- returns uint8_t

#define PLEX_getSecondDateTime(from) PLEX_getSecondDateTimeInt(from, __LINE__, __FILE__)

// ARGUMENTS: (const PLEX_DATETIME* from)- returns uint8_t

#define PLEX_getHourDateTime(from) PLEX_getHourDateTimeInt(from, __LINE__, __FILE__)

// ARGUMENTS: (const PLEX_DATETIME* from)- returns uint8_t

#define PLEX_getPMDateTime(from) PLEX_getPMDateTimeInt(from, __LINE__, __FILE__)

// ARGUMENTS: (const PLEX_DATETIME* from, const PLEX_DATETIME* from2)- returns PLEX_DATETIME

#define PLEX_getDifferenceDateTime(from, from2) PLEX_getDifferenceDateTimeInt(from, from2, __LINE__, __FILE__)

// ARGUMENTS: (const PLEX_DATETIME* from, const PLEX_DATETIME* from2)- returns PLEX_DATETIME

#define PLEX_getDifferenceDateTime12(from, from2) PLEX_getDifferenceDateTime12Int(from, from2, __LINE__, __FILE__)

// ARGUMENTS: (const PLEX_DATETIME* from, const PLEX_DATETIME* from2)- returns PLEX_DATETIME

#define PLEX_getDifferenceDateTime24(from, from2) PLEX_getDifferenceDateTime24Int(from, from2, __LINE__, __FILE__)

// ARGUMENTS: (const PLEX_DATETIME* from)- returns uint64_t

#define PLEX_getTotalDaysDateTime(from) PLEX_getTotalDaysDateTimeInt(from, __LINE__, __FILE__)

// ARGUMENTS: (const PLEX_DATETIME* from)- returns uint64_t

#define PLEX_getTotalMonthsDateTime(from) PLEX_getTotalMonthsDateTimeInt(from, __LINE__, __FILE__)

// ARGUMENTS: (const PLEX_DATETIME* from)- returns uint64_t

#define PLEX_getTotalYearsDateTime(from) PLEX_getTotalYearsDateTimeInt(from, __LINE__, __FILE__)

// ARGUMENTS: (const PLEX_DATETIME* from)- returns uint64_t

#define PLEX_getTotalHoursDateTime(from) PLEX_getTotalHoursDateTimeInt(from, __LINE__, __FILE__)

// ARGUMENTS: (const PLEX_DATETIME* from)- returns uint64_t

#define PLEX_getTotalMinutesDateTime(from) PLEX_getTotalMinutesDateTimeInt(from, __LINE__, __FILE__)

// ARGUMENTS: (const PLEX_DATETIME* from)- returns uint64_t

#define PLEX_getTotalSecondsDateTime(from) PLEX_getTotalSecondsDateTimeInt(from, __LINE__, __FILE__)

// structs, unions, enums, function prototypes ------------------------------------------------------------------------------

// the struct which contains the date time info

typedef struct
{
	uint16_t year;
	uint8_t month, day, hour, second, minute;
	bool pm;
} PLEX_DATETIME;

// public functions ---------------------------------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C"
{
#endif
// specialized functions ----------------------------------------------------------------------------------------------------

	extern PLEX_DATETIME PLEX_blankDateTime();

// setters ------------------------------------------------------------------------------------------------------------------

	// sets a datetime by year, month, day, hour and second. Utilizes 12/24 hour time dependent on the 24-hour default set.

	extern bool PLEX_setDateTimeInt(const uint16_t year, const uint8_t month, const uint8_t day, const uint8_t hour, const uint8_t second, const uint8_t minute, const bool pm, PLEX_DATETIME* toSet, const size_t errorline, const char* const errorfile);


	// sets a datetime by year, month, day, hour, and second in 12 hour time.

	extern bool PLEX_setDateTime12Int(const uint16_t year, const uint8_t month, const uint8_t day, const uint8_t hour, const uint8_t second, const uint8_t minute, const bool pm, PLEX_DATETIME* toSet, const size_t errorline, const char* const errorfile);

	// sets a datetime by year, month, day, hour, and second in 24 hour time.

	extern bool PLEX_setDateTime24Int(const uint16_t year, const uint8_t month, const uint8_t day, const uint8_t hour, const uint8_t second, const uint8_t minute, const bool pm, PLEX_DATETIME* toSet, const size_t errorline, const char* const errorfile);

	// sets a datetime to the current date and time based. Utilizes 12/24 hour time dependent on the 24-hour default set.

	extern bool PLEX_setCurrentDateTimeInt(PLEX_DATETIME* toSet, const size_t errorline, const char* const errorfile);

	// sets a datetime to the current date and time based in 12 hour time.

	extern bool PLEX_setCurrentDateTime12Int(PLEX_DATETIME* toSet, const size_t errorline, const char* const errorfile);

	// sets a datetime to the current date and time based in 24 hour time.

	extern bool PLEX_setCurrentDateTime24Int(PLEX_DATETIME* toSet, const size_t errorline, const char* const errorfile);

// getters ------------------------------------------------------------------------------------------------------------------

	// gets the day, month, and year of of a datetime

	extern bool PLEX_getDateTimeInt(uint8_t* day, uint8_t* month, uint16_t* year, const PLEX_DATETIME* from, const size_t errorline, const char* const errorfile);

	// gets the minute, second, hour, and pm of a datetime

	extern bool PLEX_getTimeDateTimeInt(uint8_t* minute, uint8_t* second, uint8_t* hour, bool* pm, const PLEX_DATETIME* from, const size_t errorline, const char* const errorfile);

	// gets the day of a datetime

	extern uint8_t PLEX_getDayDateTimeInt(const PLEX_DATETIME* from, const size_t errorline, const char* const errorfile);

	// gets the month of a datetime

	extern uint8_t PLEX_getMonthDateTimeInt(const PLEX_DATETIME* from, const size_t errorline, const char* const errorfile);

	// gets the year of a datetime

	extern uint16_t PLEX_getYearDateTimeInt(const PLEX_DATETIME* from, const size_t errorline, const char* const errorfile);

	// gets the minute of a datetime

	extern uint8_t PLEX_getMinuteDateTimeInt(const PLEX_DATETIME* from, const size_t errorline, const char* const errorfile);

	// gets the second of a datetime

	extern uint8_t PLEX_getSecondDateTimeInt(const PLEX_DATETIME* from, const size_t errorline, const char* const errorfile);

	// gets the hour of a datetime

	extern uint8_t PLEX_getHourDateTimeInt(const PLEX_DATETIME* from, const size_t errorline, const char* const errorfile);

	// gets the PM of a datetime

	extern bool PLEX_getPMDateTimeInt(const PLEX_DATETIME* from, const size_t errorline, const char* const errorfile);

	// returns a datetime that's the difference between two dates. Utilizes 12/24 hour time dependent on the 24-hour default set.

	extern PLEX_DATETIME PLEX_getDifferenceDateTimeInt(const PLEX_DATETIME* from, const PLEX_DATETIME* from2, const size_t errorline, const char* const errorfile);

	// returns a datetime that's the difference between two dates based in 12 hour time

	extern PLEX_DATETIME PLEX_getDifferenceDateTime12Int(const PLEX_DATETIME* from, const PLEX_DATETIME* from2, const size_t errorline, const char* const errorfile);

	// returns a datetime that's the difference between two dates based in 24 hour time

	extern PLEX_DATETIME PLEX_getDifferenceDateTime24Int(const PLEX_DATETIME* from, const PLEX_DATETIME* from2, const size_t errorline, const char* const errorfile);


	// returns the grand total of days calculating the number of days all values equate to (for example adding 365 days for every year and however many days per month for the month it's on)

	extern uint64_t PLEX_getTotalDaysDateTimeInt(const PLEX_DATETIME* from, const size_t errorline, const char* const errorfile);

	// returns the grand total of days calculating the number of days all values equate to (for example adding 12 months for every year)

	extern uint64_t PLEX_getTotalMonthsDateTimeInt(const PLEX_DATETIME* from, const size_t errorline, const char* const errorfile);

	// returns the grand total of days calculating the number of days all values equate to (for example if the months are over 12 it adds a year for every one)

	extern uint64_t PLEX_getTotalYearsDateTimeInt(const PLEX_DATETIME* from, const size_t errorline, const char* const errorfile);

	// returns the grand total of days calculating the number of days all values equate to (for example it adds 24 hours for every day calculated from the grand total of days)

	extern uint64_t PLEX_getTotalHoursDateTimeInt(const PLEX_DATETIME* from, const size_t errorline, const char* const errorfile);

	// returns the grand total of days calculating the number of days all values equate to (for example it adds 1440 minutes for every day calculated from the grand total of days)

	extern uint64_t PLEX_getTotalMinutesDateTimeInt(const PLEX_DATETIME* from, const size_t errorline, const char* const errorfile);

	// returns the grand total of days calculating the number of days all values equate to (for example it adds 86400 seconds for every day calculated from the grand total of days)

	extern uint64_t PLEX_getTotalSecondsDateTimeInt(const PLEX_DATETIME* from, const size_t errorline, const char* const errorfile);
#ifdef __cplusplus
}
#endif

#endif
