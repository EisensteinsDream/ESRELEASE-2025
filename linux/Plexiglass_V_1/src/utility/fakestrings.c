#include "utility/fakestrings.h"

// NOTE: function descriptions can be found in header

// static functions ---------------------------------------------------------------------------------------------------------

// copies the from to the to with a character limit no longer than limit

static size_t p_setString(const char* const from, uint8_t* to, const size_t limit)
{
	size_t next = from[0];
	size_t index = 0;

	while(next != '\0')
	{
		if(index >= limit) break;
		to[index] = next;
		++index;
		next = from[index];
	}

	to[index] = '\0';

	return index;
}

// converts a number into a string no longer than limit with a decimal no longer than the metavalue of PLEX_STANDNUM_NUMCONVPREC to the power of 10

static size_t p_setStringFromNumber(const double from, uint8_t* to, const size_t limit, const size_t prec)
{
	double adapt = from;
	size_t index = 0;
	size_t digitCount = 1;

	uint64_t digitBase = 9;
	uint64_t digitMask = 0;
	uint64_t digitExcess = 0;

	bool nonZeroDigit = false;

	if(!from)
	{
		to[0] = '0';
		to[1] = '\0';

		return 1;
	}

	memset(to, '\0', limit + 1); // limit + 1 is the 'nt' variable in fakestrings.

	if(from < 0) // adds the '-' for negative numbers, taking up a space
	{
		to[index] = '-';
		index++;
		adapt *= -1;
	}

	while(adapt > digitBase) // counts the number of digits above 0
	{
		++digitCount;
		digitMask = digitBase + 1;
		digitBase = (digitBase * 10) + 9; // ensures the sequence 9, 99, 999, 9999, etc. for this number.
	}

	// prints each digit from left to right. If hitting less than 3 characters beyond the limit it ends in a '...' like if you had a PLEX_FAKESTRING_10 and you had a number like 123456789012 the string would be something like "1234567..."
	for(size_t ze = 0; ze < digitCount; ++ze)
	{
		const uint32_t divider = digitMask ? adapt/digitMask : 0;

		uint8_t digit = '0' + divider;

		adapt -= divider * digitMask; // < do not use digit here

		if(index >= limit)
		{
			to[index - 3] = '.';
			to[index - 2] = '.';
			to[index - 1] = '.';
			to[index] = '\0';
			adapt = 0;
			break;
		}

		if(nonZeroDigit || digit != '0')
		{
			to[index] = digit;
			++index;
		}

		if(digit != '0') nonZeroDigit = true;

		digitMask /= 10;
	}

	if(adapt >= 1)
	{
		const uint8_t adaptExcess = adapt;

		to[index] = '0' + adaptExcess;
		++index;

		adapt -= adaptExcess;
	}

	if(!prec) return index;

	// the +1 preserves leading 0's past the decimal
	if(adapt > 0)
	{
		for(size_t ze = 0; ze < prec; ++ze)
		{
			digitExcess *= 10;
			adapt *= 10;

			if(adapt > 8 && adapt < 10) digitExcess += 9; // < urgh.... cheap workaround for float math.
			else digitExcess += adapt;

			adapt -= trunc(adapt);
		}
	}

	digitBase = 9;

	if(digitExcess) // all of this is ignored if the digitExcess is 0, which means no decimal value.
	{
		size_t lastNonZero = 0;

		to[index] = '.'; // the '.' symbol is added at the beginning of string of decimal values
		++index;

		while(digitExcess > digitBase) // counts the number of digits above 0
		{
			digitMask = digitBase + 1;
			digitBase = (digitBase * 10) + 9; // ensures the sequence 9, 99, 999, 9999, etc. for this number.
		}

		while(digitExcess) // reads and adds digits one by one by multiplying the number by a related amount. ie. if you have 0.33 it would determine the digit by multiplying that by 10 and making it 3.3 then converting it to an integer making it 3. Then for the next digit it would multiply by 100 to make it 33 and so on. It's an odd process but it works.
		{
			const uint32_t divider = digitMask ? digitExcess/digitMask : 0;

			uint8_t digit = '0' + divider;

			if(digit != '0') lastNonZero = index;

			digitExcess -= divider * digitMask; // < do not use digit here

			if(index >= limit) break;

			to[index] = digit;
			++index;

			digitMask /= 10;
		}

		if(lastNonZero) memset(to + lastNonZero + 1, '\0', limit - lastNonZero + 1);
	}

	return index;
}

// adds character of length clen (for uint8_t values) to the end of string to no longer than the length of limit and returning the stringlen of len

static void p_concatString(uint8_t* to, const size_t limit, size_t* len, const uint64_t character, const size_t clen)
{
	size_t llen = *len;

	if(llen + clen >= limit) return;

	memcpy(to + llen, &character, clen);

	to[llen + clen] = '\0';

	*len = llen + clen;
}

// adds the entirety of from to to with length of tlen + flen with the length of no longer than max

static size_t p_mergeString(uint8_t* to, const uint8_t* from, const size_t tlen, const size_t flen, const size_t max)
{
	size_t totalLen = 0;

	size_t copyLen = flen;

	if(tlen >= max || !copyLen) return tlen;

	if(tlen + copyLen > max) copyLen = max - tlen;

	if(!copyLen) return tlen;

	memcpy(to + tlen, from, copyLen);

	totalLen = tlen + copyLen;

	to[totalLen] = '\0';

	return totalLen;
}

// sets every single upper case character in the string to a lower case. Assuming the lowercase letter starts at lowerStart and the upper at upperStart. Using the checkLen for the length of letters plus lower and upper starts (which need to be the same length). For the English alphabet this is 'a', 'A', and 26. This is kept generic so that unicode can be added in the future.

static void p_setLower(uint8_t* to, const size_t len, const size_t lowerStart, const size_t upperStart, const size_t checkLen)
{
	if(!len) return;

	for(size_t ze = 0; ze < len; ++ze)
	{
		uint8_t* next = to + ze;

		uint8_t lNext = *next;

		if(lNext >= upperStart && lNext < upperStart + checkLen) *next = lowerStart + (lNext - upperStart);
	}
}

// compares the strings a and b, comparing the length first, and optionally ignoring the case

static bool p_compare(const uint8_t* a, const uint8_t* b, const size_t aLen, const size_t bLen, const bool ignoreCase, const size_t errorline, const char* errorfile)
{
	bool ret = false;

	uint8_t* ac = NULL;
	uint8_t* bc = NULL;

	if(aLen != bLen) return false;

	ac = PLEX_allocInt(aLen + 1, errorline, errorfile);
	bc = PLEX_allocInt(bLen + 1, errorline, errorfile);

	memcpy(ac, a, aLen);
	memcpy(bc, b, bLen);

	if(ignoreCase)
	{
	#if (PLEX_LANGUAGE == PLEX_LANGUAGE_ENGLISH)
		p_setLower(ac, aLen, 'a', 'A', 26);
		p_setLower(bc, bLen, 'a', 'A', 26);
	#endif
	}

	ret = !memcmp(ac, bc, aLen); // remember 0 == success in memcmp

	PLEX_dealloc(&ac);
	PLEX_dealloc(&bc);

	return ret;
}

// checks if the beginning of strings a and b are the same to the length of bLen

static bool p_startsWith(uint8_t* a, uint8_t* b, const size_t aLen, const size_t bLen, const bool ignoreCase, const size_t errorline, const char* errorfile)
{
	uint8_t* ac = NULL;
	uint8_t* bc = NULL;

	if(bLen > aLen) return false;

	ac = PLEX_allocInt(aLen + 1, errorline, errorfile);
	bc = PLEX_allocInt(bLen + 1, errorline, errorfile);

	memcpy(ac, a, aLen);
	memcpy(bc, b, bLen);

	if(ignoreCase)
	{
	#if (PLEX_LANGUAGE == PLEX_LANGUAGE_ENGLISH)
		p_setLower(ac, aLen, 'a', 'A', 26);
		p_setLower(bc, bLen, 'a', 'A', 26);
	#endif
	}

	for(size_t ze = 0; ze < bLen; ++ze)
	{
		const uint8_t aChar = ac[ze];
		const uint8_t bChar = bc[ze];

		if(aChar != bChar)
		{
			PLEX_dealloc(&ac);
			PLEX_dealloc(&bc);
			return false;
		}
	}

	PLEX_dealloc(&ac);
	PLEX_dealloc(&bc);

	return true;
}

// checks if b is inside a

static bool p_insideOf(uint8_t* a, uint8_t* b, const size_t aLen, const size_t bLen, const bool ignoreCase, const size_t errorline, const char* errorfile)
{
	uint8_t* ac = NULL;
	uint8_t* bc = NULL;

	if(bLen > aLen) return false;

	ac = PLEX_allocInt(aLen + 1, errorline, errorfile);
	bc = PLEX_allocInt(bLen + 1, errorline, errorfile);

	memcpy(ac, a, aLen);
	memcpy(bc, b, bLen);

	if(ignoreCase)
	{
		#if (PLEX_LANGUAGE == PLEX_LANGUAGE_ENGLISH)
			p_setLower(ac, aLen, 'a', 'A', 26);
			p_setLower(bc, bLen, 'a', 'A', 26);
		#endif
	}

	for(size_t ze = 0; ze < aLen; ++ze)
	{
		const uint8_t aChar = ac[ze];

		if(aChar == bc[0])
		{
			bool equal = true;

			for(size_t uh = 0; uh < bLen; ++uh)
			{
				uint8_t bChar = 0;
				uint8_t aChar2 = 0;

				if(uh + ze >= aLen || uh >= bLen)
				{
					PLEX_dealloc(&ac);
					PLEX_dealloc(&bc);
					return false;
				}

				bChar = bc[uh];
				aChar2 = ac[uh + ze];

				if(aChar2 != bChar)
				{
					equal = false;
					break;
				}
			}

			if(equal)
			{
				PLEX_dealloc(&ac);
				PLEX_dealloc(&bc);
				return true;
			}
		}
	}

	PLEX_dealloc(&ac);
	PLEX_dealloc(&bc);
	return false;
}

// the basic operation to check if a string is a valid number

static bool p_numerical(const uint8_t* string, const size_t len)
{
	size_t it = 0;

	uint8_t next = string[it];
	uint8_t last = 0;

	bool hasDecimal = false;

	while(next != '\0' && it < len)
	{
		if(!(next >= '0' && next <= '9') && !(next == '-' && it) && !(last != '-' && next == ' ') && !(!hasDecimal && next == '.'))
		{
			return false;
		}

		if(next == '.') hasDecimal = true;

		++it;
		if(it < len)
		{
			last = next;
			next = string[it];
		}
	}

	return true;
}

// an operation to see if a string is a valid number and also there is no decimal

static bool p_integer(const uint8_t* string, const size_t len)
{
	size_t it = 0;

	uint8_t next = string[it];
	uint8_t last = 0;

	while(next != '\0' && it < len)
	{
		if(!(next >= '0' && next <= '9') && !(next == '-' && it) && !(last != '-' && next == ' '))
		{
			return false;
		}

		++it;

		if(it < len)
		{
			last = next;
			next = string[it];
		}
	}

	return true;
}

// a function that trims the beginning and end of a string if it starts or ends with the passed string

static void p_trim(uint8_t* string, const char* const trimString, size_t* slen)
{
	const size_t len = strlen((char*)string);
	const size_t trimLen = strlen(trimString);

	size_t startTrim = 0;
	size_t endTrim = len;

	bool noStart = true;

	for(size_t ze = 0; ze < len; ++ze)
	{
		const uint8_t symbol = string[ze];

		bool trimmed = false;

		for(size_t uh = 0; uh < trimLen; ++uh)
		{
			const uint8_t trimSymbol = trimString[uh];

			if(symbol == trimSymbol)
			{
				trimmed = true;
				if(noStart) startTrim = ze + 1;
				break;
			}
		}

		if(!trimmed)
		{
			endTrim = ze + 1;
			noStart = false;
		}
	}

	if(startTrim >= endTrim)
	{
		memset(string, '\0', len);
		*slen = 0;
		return;
	}

	memmove(string, string + startTrim, endTrim - startTrim);

	endTrim -= startTrim;
	memset(string + endTrim, '\0', len - endTrim);

	*slen = strlen((char*)string);
}

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

// NOTE: these are very reliant on static functions. It's probably more useful to look at the static functions they reference rather than what they contain.

// specialized functions ----------------------------------------------------------------------------------------------------

PLEX_FAKESTRING_10 PLEX_blankString10Int(const size_t errorline, const char* const errorfile){ return PLEX_createString10Int("", errorline, errorfile); }
PLEX_FAKESTRING_25 PLEX_blankString25Int(const size_t errorline, const char* const errorfile){ return PLEX_createString25Int("", errorline, errorfile); }
PLEX_FAKESTRING_50 PLEX_blankString50Int(const size_t errorline, const char* const errorfile){ return PLEX_createString50Int("", errorline, errorfile); }
PLEX_FAKESTRING_100 PLEX_blankString100Int(const size_t errorline, const char* const errorfile){ return PLEX_createString100Int("", errorline, errorfile); }
PLEX_FAKESTRING_500 PLEX_blankString500Int(const size_t errorline, const char* const errorfile){ return PLEX_createString500Int("", errorline, errorfile); }

PLEX_FAKESTRING_10 PLEX_createString10Int(const char* const from, const size_t errorline, const char* const errorfile)
{
	PLEX_FAKESTRING_10 ret;

	memset(&ret, 0, sizeof(ret));

	if(from == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_FAKESTRING, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_FAKESTRINGS_ONCREATE, PLEX_ERRORMESS_FAKESTRINGS_FAKESTRING10, errorline, errorfile);
		return ret;
	}

	ret.len = p_setString(from, (uint8_t*)&ret, 10);

	return ret;
}

PLEX_FAKESTRING_25 PLEX_createString25Int(const char* const from, const size_t errorline, const char* const errorfile)
{
	PLEX_FAKESTRING_25 ret;

	memset(&ret, 0, sizeof(ret));

	if(from == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_FAKESTRING, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_FAKESTRINGS_ONCREATE, PLEX_ERRORMESS_FAKESTRINGS_FAKESTRING25, errorline, errorfile);
		return ret;
	}

	ret.len = p_setString(from, (uint8_t*)&ret, 25);

	return ret;
}

PLEX_FAKESTRING_50 PLEX_createString50Int(const char* const from, const size_t errorline, const char* const errorfile)
{
	PLEX_FAKESTRING_50 ret;

	memset(&ret, 0, sizeof(ret));

	if(from == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_FAKESTRING, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_FAKESTRINGS_ONCREATE, PLEX_ERRORMESS_FAKESTRINGS_FAKESTRING50, errorline, errorfile);
		return ret;
	}

	ret.len = p_setString(from, (uint8_t*)&ret, 50);

	return ret;
}

PLEX_FAKESTRING_100 PLEX_createString100Int(const char* const from, const size_t errorline, const char* const errorfile)
{
	PLEX_FAKESTRING_100 ret;

	memset(&ret, 0, sizeof(ret));

	if(from == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_FAKESTRING, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_FAKESTRINGS_ONCREATE, PLEX_ERRORMESS_FAKESTRINGS_FAKESTRING100, errorline, errorfile);
		return ret;
	}

	ret.len = p_setString(from, (uint8_t*)&ret, 100);

	return ret;
}

PLEX_FAKESTRING_500 PLEX_createString500Int(const char* const from, const size_t errorline, const char* const errorfile)
{
	PLEX_FAKESTRING_500 ret;

	memset(&ret, 0, sizeof(ret));

	if(from == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_FAKESTRING, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_FAKESTRINGS_ONCREATE, PLEX_ERRORMESS_FAKESTRINGS_FAKESTRING500, errorline, errorfile);
		return ret;
	}

	ret.len = p_setString(from, (uint8_t*)&ret, 500);

	return ret;
}

PLEX_FAKESTRING_10 PLEX_createStringFromNumber10(const double number){ PLEX_FAKESTRING_10 ret; ret.len = p_setStringFromNumber(number, (uint8_t*)&ret, 10, PLEX_STANDNUM_NUMCONVPREC); return ret; }
PLEX_FAKESTRING_25 PLEX_createStringFromNumber25(const double number){ PLEX_FAKESTRING_25 ret; ret.len = p_setStringFromNumber(number, (uint8_t*)&ret, 25, PLEX_STANDNUM_NUMCONVPREC); return ret; }
PLEX_FAKESTRING_50 PLEX_createStringFromNumber50(const double number){ PLEX_FAKESTRING_50 ret; ret.len = p_setStringFromNumber(number, (uint8_t*)&ret, 50, PLEX_STANDNUM_NUMCONVPREC); return ret; }
PLEX_FAKESTRING_100 PLEX_createStringFromNumber100(const double number){ PLEX_FAKESTRING_100 ret; ret.len = p_setStringFromNumber(number, (uint8_t*)&ret, 100, PLEX_STANDNUM_NUMCONVPREC); return ret; }
PLEX_FAKESTRING_500 PLEX_createStringFromNumber500(const double number){ PLEX_FAKESTRING_500 ret; ret.len = p_setStringFromNumber(number, (uint8_t*)&ret, 500, PLEX_STANDNUM_NUMCONVPREC); return ret; }

PLEX_FAKESTRING_10 PLEX_createStringFromNumberPrec10(const double number, const size_t prec){ PLEX_FAKESTRING_10 ret; ret.len = p_setStringFromNumber(number, (uint8_t*)&ret, 10, prec); return ret; }
PLEX_FAKESTRING_25 PLEX_createStringFromNumberPrec25(const double number, const size_t prec){ PLEX_FAKESTRING_25 ret; ret.len = p_setStringFromNumber(number, (uint8_t*)&ret, 25, prec); return ret; }
PLEX_FAKESTRING_50 PLEX_createStringFromNumberPrec50(const double number, const size_t prec){ PLEX_FAKESTRING_50 ret; ret.len = p_setStringFromNumber(number, (uint8_t*)&ret, 50, prec); return ret; }
PLEX_FAKESTRING_100 PLEX_createStringFromNumberPrec100(const double number, const size_t prec){ PLEX_FAKESTRING_100 ret; ret.len = p_setStringFromNumber(number, (uint8_t*)&ret, 100, prec); return ret; }
PLEX_FAKESTRING_500 PLEX_createStringFromNumberPrec500(const double number, const size_t prec){ PLEX_FAKESTRING_500 ret; ret.len = p_setStringFromNumber(number, (uint8_t*)&ret, 500, prec); return ret; }

PLEX_FAKESTRING_10 PLEX_concatString10(const PLEX_FAKESTRING_10 string, const uint64_t character, const size_t clen)
{
	PLEX_FAKESTRING_10 ret = string;

	p_concatString((uint8_t*)&ret, 10, &ret.len, character, clen);

	return ret;
}

PLEX_FAKESTRING_25 PLEX_concatString25(const PLEX_FAKESTRING_25 string, const uint64_t character, const size_t clen)
{
	PLEX_FAKESTRING_25 ret = string;

	p_concatString((uint8_t*)&ret, 25, &ret.len, character, clen);

	return ret;
}

PLEX_FAKESTRING_50 PLEX_concatString50(const PLEX_FAKESTRING_50 string, const uint64_t character, const size_t clen)
{
	PLEX_FAKESTRING_50 ret = string;

	p_concatString((uint8_t*)&ret, 50, &ret.len, character, clen);

	return ret;
}

PLEX_FAKESTRING_100 PLEX_concatString100(const PLEX_FAKESTRING_100 string, const uint64_t character, const size_t clen)
{
	PLEX_FAKESTRING_100 ret = string;

	p_concatString((uint8_t*)&ret, 100, &ret.len, character, clen);

	return ret;
}

PLEX_FAKESTRING_500 PLEX_concatString500(const PLEX_FAKESTRING_500 string, const uint64_t character, const size_t clen)
{
	PLEX_FAKESTRING_500 ret = string;

	p_concatString((uint8_t*)&ret, 500, &ret.len, character, clen);

	return ret;
}

PLEX_FAKESTRING_10 PLEX_mergeString10(const PLEX_FAKESTRING_10 string, const PLEX_FAKESTRING_10 string2)
{
	PLEX_FAKESTRING_10 ret = string;

	ret.len = p_mergeString((uint8_t*)&ret, (const uint8_t*)&string2, ret.len, string2.len, 10);

	return ret;
}

PLEX_FAKESTRING_25 PLEX_mergeString25(const PLEX_FAKESTRING_25 string, const PLEX_FAKESTRING_25 string2)
{
	PLEX_FAKESTRING_25 ret = string;

	ret.len = p_mergeString((uint8_t*)&ret, (const uint8_t*)&string2, ret.len, string2.len, 25);

	return ret;
}

PLEX_FAKESTRING_50 PLEX_mergeString50(const PLEX_FAKESTRING_50 string, const PLEX_FAKESTRING_50 string2)
{
	PLEX_FAKESTRING_50 ret = string;

	ret.len = p_mergeString((uint8_t*)&ret, (const uint8_t*)&string2, ret.len, string2.len, 50);

	return ret;
}

PLEX_FAKESTRING_100 PLEX_mergeString100(const PLEX_FAKESTRING_100 string, const PLEX_FAKESTRING_100 string2)
{
	PLEX_FAKESTRING_100 ret = string;

	ret.len = p_mergeString((uint8_t*)&ret, (const uint8_t*)&string2, ret.len, string2.len, 100);

	return ret;
}

PLEX_FAKESTRING_500 PLEX_mergeString500(const PLEX_FAKESTRING_500 string, const PLEX_FAKESTRING_500 string2)
{
	PLEX_FAKESTRING_500 ret = string;

	ret.len = p_mergeString((uint8_t*)&ret, (const uint8_t*)&string2, ret.len, string2.len, 500);

	return ret;
}

PLEX_FAKESTRING_10 PLEX_toLowerString10(const PLEX_FAKESTRING_10 string)
{
	PLEX_FAKESTRING_10 ret = string;

	#if (PLEX_LANGUAGE == PLEX_LANGUAGE_ENGLISH)
		p_setLower((uint8_t*)&ret, ret.len, 'a', 'A', 26);
	#endif

	return ret;
}

PLEX_FAKESTRING_25 PLEX_toLowerString25(const PLEX_FAKESTRING_25 string)
{
	PLEX_FAKESTRING_25 ret = string;

	#if (PLEX_LANGUAGE == PLEX_LANGUAGE_ENGLISH)
		p_setLower((uint8_t*)&ret, ret.len, 'a', 'A', 26);
	#endif

	return ret;
}

PLEX_FAKESTRING_50 PLEX_toLowerString50(const PLEX_FAKESTRING_50 string)
{
	PLEX_FAKESTRING_50 ret = string;

	#if (PLEX_LANGUAGE == PLEX_LANGUAGE_ENGLISH)
		p_setLower((uint8_t*)&ret, ret.len, 'a', 'A', 26);
	#endif

	return ret;
}

PLEX_FAKESTRING_100 PLEX_toLowerString100(const PLEX_FAKESTRING_100 string)
{
	PLEX_FAKESTRING_100 ret = string;

	#if (PLEX_LANGUAGE == PLEX_LANGUAGE_ENGLISH)
		p_setLower((uint8_t*)&ret, ret.len, 'a', 'A', 26);
	#endif

	return ret;
}

PLEX_FAKESTRING_500 PLEX_toLowerString500(const PLEX_FAKESTRING_500 string)
{
	PLEX_FAKESTRING_500 ret = string;

	#if (PLEX_LANGUAGE == PLEX_LANGUAGE_ENGLISH)
		p_setLower((uint8_t*)&ret, ret.len, 'a', 'A', 26);
	#endif

	return ret;
}

PLEX_FAKESTRING_10 PLEX_trimmedString10Int(const PLEX_FAKESTRING_10 string, const char* const toTrim, const size_t errorline, const char* errorfile)
{
	PLEX_FAKESTRING_10 ret = string;

	p_trim((uint8_t*)&ret, toTrim, &ret.len);

	return ret;
}

PLEX_FAKESTRING_25 PLEX_trimmedString25Int(const PLEX_FAKESTRING_25 string, const char* const toTrim, const size_t errorline, const char* errorfile)
{
	PLEX_FAKESTRING_25 ret = string;

	p_trim((uint8_t*)&ret, toTrim, &ret.len);

	return ret;
}

PLEX_FAKESTRING_50 PLEX_trimmedString50Int(const PLEX_FAKESTRING_50 string, const char* const toTrim, const size_t errorline, const char* errorfile)
{
	PLEX_FAKESTRING_50 ret = string;

	p_trim((uint8_t*)&ret, toTrim, &ret.len);

	return ret;
}

PLEX_FAKESTRING_100 PLEX_trimmedString100Int(const PLEX_FAKESTRING_100 string, const char* const toTrim, const size_t errorline, const char* errorfile)
{
	PLEX_FAKESTRING_100 ret = string;

	p_trim((uint8_t*)&ret, toTrim, &ret.len);

	return ret;
}

PLEX_FAKESTRING_500 PLEX_trimmedString500Int(const PLEX_FAKESTRING_500 string, const char* const toTrim, const size_t errorline, const char* errorfile)
{
	PLEX_FAKESTRING_500 ret = string;

	p_trim((uint8_t*)&ret, toTrim, &ret.len);

	return ret;
}

bool PLEX_compStrings10Int(const PLEX_FAKESTRING_10 a, const PLEX_FAKESTRING_10 b, const bool ignoreCase, const size_t errorline, const char* errorfile)
{
	return p_compare((uint8_t*)&a, (uint8_t*)&b, a.len, b.len, ignoreCase, errorline, errorfile);
}

bool PLEX_compStrings25Int(const PLEX_FAKESTRING_25 a, const PLEX_FAKESTRING_25 b, const bool ignoreCase, const size_t errorline, const char* errorfile)
{
	return p_compare((uint8_t*)&a, (uint8_t*)&b, a.len, b.len, ignoreCase, errorline, errorfile);
}

bool PLEX_compStrings50Int(const PLEX_FAKESTRING_50 a, const PLEX_FAKESTRING_50 b, const bool ignoreCase, const size_t errorline, const char* errorfile)
{
	return p_compare((uint8_t*)&a, (uint8_t*)&b, a.len, b.len, ignoreCase, errorline, errorfile);
}

bool PLEX_compStrings100Int(const PLEX_FAKESTRING_100 a, const PLEX_FAKESTRING_100 b, const bool ignoreCase, const size_t errorline, const char* errorfile)
{
	return p_compare((uint8_t*)&a, (uint8_t*)&b, a.len, b.len, ignoreCase, errorline, errorfile);
}

bool PLEX_compStrings500Int(const PLEX_FAKESTRING_500 a, const PLEX_FAKESTRING_500 b, const bool ignoreCase, const size_t errorline, const char* errorfile)
{
	return p_compare((uint8_t*)&a, (uint8_t*)&b, a.len, b.len, ignoreCase, errorline, errorfile);
}

bool PLEX_insideString10Int(const PLEX_FAKESTRING_10 a, const PLEX_FAKESTRING_10 b, const bool ignoreCase, const size_t errorline, const char* errorfile)
{
	return p_insideOf((uint8_t*)&a, (uint8_t*)&b, a.len, b.len, ignoreCase, errorline, errorfile);
}

bool PLEX_insideString25Int(const PLEX_FAKESTRING_25 a, const PLEX_FAKESTRING_25 b, const bool ignoreCase, const size_t errorline, const char* errorfile)
{
	return p_insideOf((uint8_t*)&a, (uint8_t*)&b, a.len, b.len, ignoreCase, errorline, errorfile);
}

bool PLEX_insideString50Int(const PLEX_FAKESTRING_50 a, const PLEX_FAKESTRING_50 b, const bool ignoreCase, const size_t errorline, const char* errorfile)
{
	return p_insideOf((uint8_t*)&a, (uint8_t*)&b, a.len, b.len, ignoreCase, errorline, errorfile);
}

extern bool PLEX_insideString100Int(const PLEX_FAKESTRING_100 a, const PLEX_FAKESTRING_100 b, const bool ignoreCase, const size_t errorline, const char* errorfile)
{
	return p_insideOf((uint8_t*)&a, (uint8_t*)&b, a.len, b.len, ignoreCase, errorline, errorfile);
}

extern bool PLEX_insideString500Int(const PLEX_FAKESTRING_500 a, const PLEX_FAKESTRING_500 b, const bool ignoreCase, const size_t errorline, const char* errorfile)
{
	return p_insideOf((uint8_t*)&a, (uint8_t*)&b, a.len, b.len, ignoreCase, errorline, errorfile);
}

bool PLEX_startsWithString10Int(const PLEX_FAKESTRING_10 a, const PLEX_FAKESTRING_10 b, const bool ignoreCase, const size_t errorline, const char* errorfile)
{
	return p_startsWith((uint8_t*)&a, (uint8_t*)&b, a.len, b.len, ignoreCase, errorline, errorfile);
}

bool PLEX_startsWithString25Int(const PLEX_FAKESTRING_25 a, const PLEX_FAKESTRING_25 b, const bool ignoreCase, const size_t errorline, const char* errorfile)
{
	return p_startsWith((uint8_t*)&a, (uint8_t*)&b, a.len, b.len, ignoreCase, errorline, errorfile);
}

bool PLEX_startsWithString50Int(const PLEX_FAKESTRING_50 a, const PLEX_FAKESTRING_50 b, const bool ignoreCase, const size_t errorline, const char* errorfile)
{
	return p_startsWith((uint8_t*)&a, (uint8_t*)&b, a.len, b.len, ignoreCase, errorline, errorfile);
}

bool PLEX_startsWithString100Int(const PLEX_FAKESTRING_100 a, const PLEX_FAKESTRING_100 b, const bool ignoreCase, const size_t errorline, const char* errorfile)
{
	return p_startsWith((uint8_t*)&a, (uint8_t*)&b, a.len, b.len, ignoreCase, errorline, errorfile);
}

bool PLEX_startsWithString500Int(const PLEX_FAKESTRING_500 a, const PLEX_FAKESTRING_500 b, const bool ignoreCase, const size_t errorline, const char* errorfile)
{
	return p_startsWith((uint8_t*)&a, (uint8_t*)&b, a.len, b.len, ignoreCase, errorline, errorfile);
}

PLEX_FAKESTRING_100 PLEX_fileLoadErrorPath(const char* const fileloc, const char* const errorTarget)
{
	PLEX_FAKESTRING_100 ret = PLEX_blankString100();
	PLEX_FAKESTRING_100 lFilename = PLEX_blankString100();
	PLEX_FAKESTRING_100 lErrorTarget = PLEX_blankString100();
	PLEX_FAKESTRING_100 mid = PLEX_blankString100();

	if(fileloc == NULL || errorTarget == NULL) return ret;

	lFilename = PLEX_createString100(fileloc);
	lErrorTarget = PLEX_createString100(errorTarget);
	mid = PLEX_createString100(PLEX_ERRORMESS_ERROR_FILENAMEMID);

	ret = PLEX_mergeString100(ret, lErrorTarget);
	ret = PLEX_mergeString100(ret, mid);
	ret = PLEX_concatString100(ret, '\"', 1);
	ret = PLEX_mergeString100(ret, lFilename);
	ret = PLEX_concatString100(ret, '\"', 1);

	return ret;
}

// getters ------------------------------------------------------------------------------------------------------------------

size_t PLEX_strLen10(const PLEX_FAKESTRING_10 string){ return string.len; }
size_t PLEX_strLen25(const PLEX_FAKESTRING_25 string){ return string.len; }
size_t PLEX_strLen50(const PLEX_FAKESTRING_50 string){ return string.len; }
size_t PLEX_strLen100(const PLEX_FAKESTRING_100 string){ return string.len; }
size_t PLEX_strLen500(const PLEX_FAKESTRING_500 string){ return string.len; }

bool PLEX_isStringNumber10(const PLEX_FAKESTRING_10 string)
{
	return p_numerical((uint8_t*)&string, string.len);
}

bool PLEX_isStringNumber25(const PLEX_FAKESTRING_25 string)
{
	return p_numerical((uint8_t*)&string, string.len);
}

bool PLEX_isStringNumber50(const PLEX_FAKESTRING_50 string)
{
	return p_numerical((uint8_t*)&string, string.len);
}

bool PLEX_isStringNumber100(const PLEX_FAKESTRING_100 string)
{
	return p_numerical((uint8_t*)&string, string.len);
}

bool PLEX_isStringNumber500(const PLEX_FAKESTRING_500 string)
{
	return p_numerical((uint8_t*)&string, string.len);
}

bool PLEX_isStringInteger10(const PLEX_FAKESTRING_10 string)
{
	return p_integer((uint8_t*)&string, string.len);
}

bool PLEX_isStringInteger25(const PLEX_FAKESTRING_25 string)
{
	return p_integer((uint8_t*)&string, string.len);
}

bool PLEX_isStringInteger50(const PLEX_FAKESTRING_50 string)
{
	return p_integer((uint8_t*)&string, string.len);
}

bool PLEX_isStringInteger100(const PLEX_FAKESTRING_100 string)
{
	return p_integer((uint8_t*)&string, string.len);
}

bool PLEX_isStringInteger500(const PLEX_FAKESTRING_500 string)
{
	return p_integer((uint8_t*)&string, string.len);
}
