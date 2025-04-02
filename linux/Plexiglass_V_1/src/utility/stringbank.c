#include "utility/stringbank.h"

PLEX_STRINGBANK* PLEX_genStringBankInt(const size_t errorline, const char* const errorfile)
{
	PLEX_STRINGBANK* ret = PLEX_allocInt(sizeof(PLEX_STRINGBANK), errorline, errorfile);

	if(ret == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_STRINGBANK, PLEX_ERROR_ALLOCFAIL, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_STRINGBANK_ONGENERATE, PLEX_ERRORMESS_STRINGBANK_STRINGBANK, errorline, errorfile);
		return NULL;
	}

	ret->contents = PLEX_genExpandArrayInt(10, sizeof(PLEX_FAKESTRING_500), errorline, errorfile);

	if(ret->contents == NULL)
	{
		PLEX_deallocInt((void**)ret, errorline, errorfile);

		PLEX_errorInt(PLEX_ERROR_CATEGORY_STRINGBANK, PLEX_ERROR_ALLOCFAIL, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_STRINGBANK_ONGENERATE, PLEX_ERRORMESS_STRINGBANK_STRINGBANKCONTENTS, errorline, errorfile);
		return NULL;
	}

	return ret;
}

void PLEX_destroyStringBankInt(PLEX_STRINGBANK** toDestroy, const size_t errorline, const char* const errorfile)
{
	PLEX_STRINGBANK* toDestroyPtr = NULL;

	if(toDestroy == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_STRINGBANK, PLEX_ERROR_FREENULLPTR, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_STRINGBANK_ONDESTROY, PLEX_ERRORMESS_STRINGBANK_STRINGBANK, errorline, errorfile);
		return;
	}

	toDestroyPtr = *toDestroy;

	if(toDestroyPtr == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_STRINGBANK, PLEX_ERROR_FREENULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_STRINGBANK_ONDESTROY, PLEX_ERRORMESS_STRINGBANK_STRINGBANK, errorline, errorfile);
		return;
	}

	PLEX_destroyExpandArrayInt(&toDestroyPtr->contents, errorline, errorfile);

	PLEX_deallocInt((void**)toDestroy, errorline, errorfile);
}

int64_t PLEX_addStringToBankInt(const char* const string, PLEX_STRINGBANK* bank, const size_t errorline, const char* const errorfile)
{
	PLEX_FAKESTRING_500* entry = NULL;

	if(string == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_STRINGBANK, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_STRINGBANK_ONADD, PLEX_ERRORMESS_GENERIC_STRING, errorline, errorfile);
		return -1;
	}

	if(string[0] == '\0')
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_STRINGBANK, PLEX_ERROR_NOSTRINGLEN, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_STRINGBANK_ONADD, PLEX_ERRORMESS_GENERIC_STRING, errorline, errorfile);
		return -1;
	}

	if(bank == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_STRINGBANK, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_STRINGBANK_ONADD, PLEX_ERRORMESS_STRINGBANK_STRINGBANK, errorline, errorfile);
		return -1;
	}

	if(!PLEX_incrementExpandArrayInt(bank->contents, errorline, errorfile))
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_STRINGBANK, PLEX_ERROR_INCREMENT, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_STRINGBANK_ONADD, PLEX_ERRORMESS_STRINGBANK_STRINGBANKCONTENTS, errorline, errorfile);
		return -1;
	}

	entry = PLEX_getExpandArrayLastInt(bank->contents, errorline, errorfile);

	if(entry == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_STRINGBANK, PLEX_ERROR_ACQUIRELAST, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_STRINGBANK_ONADD, PLEX_ERRORMESS_STRINGBANK_STRINGBANKCONTENTS, errorline, errorfile);
		return -1;
	}

	*entry = PLEX_createString500Int(string, errorline, errorfile);

	return PLEX_expandArrayCountInt(bank->contents, errorline, errorfile) - 1;
}

void PLEX_removeStringFromBankInt(const size_t index, PLEX_STRINGBANK* bank, const size_t errorline, const char* const errorfile)
{
	if(bank == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_STRINGBANK, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_STRINGBANK_ONREMOVE, PLEX_ERRORMESS_STRINGBANK_STRINGBANK, errorline, errorfile);
		return;
	}

	PLEX_removeExpandArrayInt(index, bank->contents, errorline, errorfile);
}

PLEX_STRINGBANK* PLEX_loadStringBankInt(const char* const fileloc, const size_t errorline, const char* const errorfile)
{
	PLEX_PARSEDFILE* parseFile = NULL;

	PLEX_STRINGBANK* ret = NULL;

	size_t count = 0;

	PLEX_FAKESTRING_500 newLine = PLEX_blankString500();
	bool onNewLine = true;

	if(fileloc == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_STRINGBANK, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_STRINGBANK_ONLOAD, PLEX_ERRORMESS_GENERIC_FILEPATH, errorline, errorfile);
		return NULL;
	}

	ret = PLEX_genStringBankInt(errorline, errorfile);

	if(ret == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_STRINGBANK, PLEX_ERROR_ALLOCFAIL, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_STRINGBANK_ONLOAD, PLEX_ERRORMESS_STRINGBANK_STRINGBANK, errorline, errorfile);
		return NULL;
	}

	parseFile = PLEX_parseFileInt(0, ' ', 0, '\\', 0, 0, "", fileloc, errorline, errorfile);

	if(parseFile == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_STRINGBANK, PLEX_ERROR_CREATE, PLEX_ERROR_SEVERITY_MAJOR, PLEX_ERRORMESS_STRINGBANK_ONLOAD, PLEX_ERRORMESS_FILEPARSE_FILEPARSER, errorline, errorfile);

		return NULL;
	}

	count = PLEX_parseLineCountInt(parseFile, errorline, errorfile);

	for(size_t ze = 0; ze < count; ++ze)
	{
		size_t count2 = 0;

		PLEX_PARSELINE* line = PLEX_getParselineInt(ze, parseFile, errorline, errorfile);

		if(!line->line.len) continue;

		count2 = PLEX_parseTokenCountInt(ze, parseFile, errorline, errorfile);

		for(size_t uh = 0; uh < count2; ++uh)
		{
			PLEX_FAKESTRING_50 token;

			if(PLEX_getTokenInt(ze, uh, &token, parseFile, errorline, errorfile))
			{
				PLEX_FAKESTRING_50 token2 = PLEX_trimmedString50(token, " \r\n\t");

				if(!token2.len) continue;

				if(token2.len == 1 && token2.s0 == '~')
				{
					PLEX_addStringToBankInt(PLEX_fts(newLine), ret, errorline, errorfile);
					newLine = PLEX_blankString500();
					onNewLine = true;
				}else{
					PLEX_FAKESTRING_500 bigToken = PLEX_createString500Int(PLEX_fts(token), errorline, errorfile);

					if(!onNewLine) newLine = PLEX_concatString500(newLine, ' ', 1);
					newLine = PLEX_mergeString500(newLine, bigToken);
					newLine = PLEX_trimmedString500(newLine, " \r\n\t");
					onNewLine = false;
				}
			}else{
				PLEX_errorInt(PLEX_ERROR_CATEGORY_STRINGBANK, PLEX_ERROR_CREATE, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_STRINGBANK_ONLOAD, PLEX_ERRORMESS_GENERIC_TOKEN, errorline, errorfile);
				break;
			}
		}
	}

	if(newLine.len)
	{
		newLine = PLEX_trimmedString500(newLine, " \r\n\t");
		PLEX_addStringToBankInt(PLEX_fts(newLine), ret, errorline, errorfile);
	}

	return ret;
}

PLEX_FAKESTRING_500 PLEX_getStringBankEntryInt(const size_t index, PLEX_STRINGBANK* bank, const size_t errorline, const char* const errorfile)
{
	PLEX_FAKESTRING_500* entry = NULL;

	if(bank == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_STRINGBANK, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_STRINGBANK_ONGETENTRY, PLEX_ERRORMESS_STRINGBANK_STRINGBANK, errorline, errorfile);
		return PLEX_blankString500();
	}

	if(index >= PLEX_expandArrayCountInt(bank->contents, errorline, errorfile))
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_STRINGBANK, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_STRINGBANK_ONGETENTRY, PLEX_ERRORMESS_STRINGBANK_STRINGBANKCONTENTS, errorline, errorfile);
		return PLEX_blankString500();
	}

	entry = PLEX_getExpandArrayEntryInt(index, bank->contents, errorline, errorfile);

	if(entry == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_STRINGBANK, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_STRINGBANK_ONGETENTRY, PLEX_ERRORMESS_STRINGBANK_STRINGBANKCONTENTS, errorline, errorfile);
		return PLEX_blankString500();
	}

	return *entry;
}

size_t PLEX_stringBankCountInt(PLEX_STRINGBANK* bank, const size_t errorline, const char* const errorfile)
{
	if(bank == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_STRINGBANK, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_STRINGBANK_ONCOUNT, PLEX_ERRORMESS_STRINGBANK_STRINGBANK, errorline, errorfile);
		return 0;
	}

	return PLEX_expandArrayCountInt(bank->contents, errorline, errorfile);
}
