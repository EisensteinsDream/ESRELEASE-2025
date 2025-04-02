#include "utility/fileparse.h"

// NOTE: global function descriptions in header.

// static functions ---------------------------------------------------------------------------------------------------------

// adds a new line to the parsefile

static bool p_addLine(PLEX_PARSEDFILE* pfile, const size_t errorline, const char* const errorfile)
{
	PLEX_PARSELINE* next = NULL;

	if(!PLEX_incrementExpandArrayInt(pfile->lines, errorline, errorfile))
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_FILEPARSE, PLEX_ERROR_INCREMENT, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_FILEPARSE_ONADDLINE, PLEX_ERRORMESS_GENERIC_LINES, errorline, errorfile);
		return false;
	}

	next = PLEX_getExpandArrayLastInt(pfile->lines, errorline, errorfile);

	if(next == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_FILEPARSE, PLEX_ERROR_ACQUIRELAST, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_FILEPARSE_ONADDLINE, PLEX_ERRORMESS_GENERIC_LINES, errorline, errorfile);
		return false;
	}

	next->tokens = PLEX_genExpandArrayInt(PLEX_getMemProfileTokenPreload(), sizeof(PLEX_FAKESTRING_50), errorline, errorfile);

	if(next->tokens == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_FILEPARSE, PLEX_ERROR_ALLOCFAIL, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_FILEPARSE_ONADDLINE, PLEX_ERRORMESS_FILEPARSE_NEXTLINESTOKEN, errorline, errorfile);
		return false;
	}

	next->commentString = PLEX_blankString500Int(errorline, errorfile);

	return true;
}

// adds a new token to the parseline

static bool p_addToken(PLEX_PARSELINE* line, const PLEX_FAKESTRING_50 token, const size_t errorline, const char* const errorfile)
{
	PLEX_FAKESTRING_50* nextToken = NULL;

	if(!PLEX_incrementExpandArrayInt(line->tokens, errorline, errorfile))
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_FILEPARSE, PLEX_ERROR_INCREMENT, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_FILEPARSE_ONADDTOKEN, PLEX_ERRORMESS_GENERIC_TOKENS, errorline, errorfile);
		return false;
	}

	nextToken = PLEX_getExpandArrayLastInt(line->tokens, errorline, errorfile);

	if(nextToken == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_FILEPARSE, PLEX_ERROR_ACQUIRELAST, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_FILEPARSE_ONADDTOKEN, PLEX_ERRORMESS_GENERIC_TOKENS, errorline, errorfile);
		return false;
	}

	*nextToken = token;

	return true;
}

// checks for the next character from a file or a buffer. if the file is not null the buffer is ignored. If the file is null, the value is pulled straight from the buffer.

static uint64_t p_nextChar(FILE* file, const char* const buffer, const size_t iterator)
{
	if(file != NULL) return fgetc(file);

	return buffer[iterator];
}

// reads a unicode value from either a file or a buffer. If the file is not null the buffer is ignored. If the file is null, the value is pulled from the buffer. Can be passed a starting iterator (which optionally can be null), and is passed a pointer to a size_t to return the length of the read utf-8 character.

static uint64_t p_readUnicodeBase(size_t* symbolLen, size_t* iterator, const char* const buffer, FILE* file)
{
	const size_t literator = iterator == NULL ? 0 : *iterator;

	const int32_t first = file == NULL ? buffer[literator] : fgetc(file);

	uint64_t ret = 0;

	char cbuff[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

	size_t citerator = 0;

	if(first == EOF) return EOF;

	if(first < 0x80)
	{
		ret = first;
		*symbolLen = 1;
		citerator = 1;
	}else{
		cbuff[citerator] = p_nextChar(file, buffer, literator + citerator);
		++citerator;

		if(first < 0xE0)
		{
			memcpy(&ret, cbuff, 2);
			*symbolLen = 2;
		}else{
			cbuff[citerator] = p_nextChar(file, buffer, literator + citerator);
			++citerator;

			if(first < 0xF0)
			{
				memcpy(&ret, cbuff, 3);
				*symbolLen = 3;
			}else{
				cbuff[citerator] = p_nextChar(file, buffer, literator + citerator);
				++citerator;

				if(first < 0xF8)
				{
					memcpy(&ret, cbuff, 4);
					*symbolLen = 4;
				}else{
					cbuff[citerator] = p_nextChar(file, buffer, literator + citerator);
					++citerator;

					if(first < 0xFC)
					{
						memcpy(&ret, cbuff, 5);
						*symbolLen = 5;
					}else{
						cbuff[citerator] = p_nextChar(file, buffer, literator + citerator);
						++citerator;

						if(first < 0xFE)
						{
							memcpy(&ret, cbuff, 6);
							*symbolLen = 6;
						}else{
							cbuff[citerator] = p_nextChar(file, buffer, literator + citerator);

							memcpy(&ret, cbuff, 7);
							*symbolLen = 7;
						}
					}
				}
			}
		}
	}

	if(iterator != NULL) *iterator += citerator;

	return ret;
}

// loads next from a file or buffer. If file is not null, the buffer is ignored. If the file is null, the value is pulled straight from the buffer.

static uint64_t p_loadNext(FILE* file, const char* const buffer, size_t* symbolLen, size_t* iterator)
{
	return p_readUnicodeBase(symbolLen, iterator, buffer, file);
}

// reads and returns the unicode of a singular numerical symbol 'from'. Also, acquires the symbolLen of said utf-8 symbol.

static uint64_t p_readUnicode(size_t* symbolLen, uint64_t from)
{
	return p_readUnicodeBase(symbolLen, NULL, (const char*)&from, NULL);
}

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

// specialized functions ----------------------------------------------------------------------------------------------------

PLEX_PARSEDFILE* PLEX_parseFileInt(const uint64_t linebreak, const uint64_t tokenbreak, const uint64_t comment, const uint64_t escape, const uint64_t ignoreBreak, const uint64_t multiline, const char* const ignore, const char* const fileloc, const size_t errorline, const char* const errorfile)
{
	uint64_t next = 0;
	uint64_t last = 0;

	size_t symbolLen = 0;
	size_t iterator = 0;
	size_t lineCount = 0;

	bool commented = false;
	bool ignoreTokenBreak = false;
	bool isMultiline = false;

	FILE* file = NULL;

	PLEX_EXPANDARRAY* line = NULL;

	PLEX_FAKESTRING_50 token = PLEX_blankString50Int(errorline, errorfile);

	PLEX_PARSEDFILE* ret = NULL;

	if(fileloc == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_FILEPARSE, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_FILEPARSE_ONPARSEFILE, PLEX_ERRORMESS_GENERIC_FILEPATH, errorline, errorfile);
		return NULL;
	}

	file = fopen(fileloc, "rb+");

	if(file == NULL)
	{
		const PLEX_FAKESTRING_100 targMessage = PLEX_fileLoadErrorPath(fileloc, PLEX_ERRORMESS_GENERIC_FILE);

		PLEX_errorInt(PLEX_ERROR_CATEGORY_FILEPARSE, PLEX_ERROR_FILELOAD, PLEX_ERROR_SEVERITY_MAJOR, PLEX_ERRORMESS_FILEPARSE_ONPARSEFILE, PLEX_fts(targMessage), errorline, errorfile);
		return NULL;
	}

	ret = PLEX_allocInt(sizeof(PLEX_PARSEDFILE), errorline, errorfile);

	if(ret == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_FILEPARSE, PLEX_ERROR_ALLOCFAIL, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_FILEPARSE_ONPARSEFILE, PLEX_ERRORMESS_FILEPARSE_PARSEFILE, errorline, errorfile);
		fclose(file);
		return NULL;
	}

	ret->lines = PLEX_genExpandArrayInt(PLEX_getMemProfileLineParsePreload(), sizeof(PLEX_PARSELINE), errorline, errorfile);

	if(ret->lines == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_FILEPARSE, PLEX_ERROR_ALLOCFAIL, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_FILEPARSE_ONPARSEFILE, PLEX_ERRORMESS_GENERIC_LINES, errorline, errorfile);
		fclose(file);
		PLEX_deallocInt((void**)&ret, errorline, errorfile);
		return NULL;
	}

	if(!p_addLine(ret, errorline, errorfile))
	{
		fclose(file);
		PLEX_destroyExpandArrayInt(&ret->lines, errorline, errorfile);
		PLEX_deallocInt((void**)&ret, errorline, errorfile);

		PLEX_errorInt(PLEX_ERROR_CATEGORY_FILEPARSE, PLEX_ERROR_CREATE, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_FILEPARSE_ONPARSEFILE, PLEX_ERRORMESS_GENERIC_LINES, errorline, errorfile);
		return NULL;
	}

	lineCount = PLEX_expandArrayCountInt(ret->lines, errorline, errorfile);

	if(!lineCount)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_FILEPARSE, PLEX_ERROR_ZEROVALUE, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_FILEPARSE_ONPARSEFILE, PLEX_ERRORMESS_GENERIC_LINECOUNT, errorline, errorfile);
		return NULL;
	}

	line = PLEX_getExpandArrayEntryInt(0, ret->lines, errorline, errorfile);

	if(line == NULL)
	{
		fclose(file);
		PLEX_destroyExpandArrayInt(&ret->lines, errorline, errorfile);
		PLEX_deallocInt((void**)&ret, errorline, errorfile);

		PLEX_errorInt(PLEX_ERROR_CATEGORY_FILEPARSE, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_FILEPARSE_ONPARSEFILE, PLEX_ERRORMESS_GENERIC_LINE, errorline, errorfile);
		return NULL;
	}

	ret->linebreak = linebreak;
	ret->tokenbreak = tokenbreak;
	ret->comment = comment;
	ret->ignoreBreak = ignoreBreak;

	next = p_loadNext(file, NULL, &symbolLen, &iterator);

	while(next != EOF)
	{
		const bool addToken = next == tokenbreak;

		const bool addLine = next == linebreak || next == '\r' || next == '\n';

		const bool escaped = last == escape && next != escape;

		bool addNext = true;

		if(!escaped && !commented && addToken)
		{
			if(!ignoreTokenBreak) addNext = false;
		}

		if(!escaped && !commented && next == multiline)
		{
			isMultiline = true;
			addNext = false;
		}

		if(!escaped && !commented && next == escape) addNext = false;

		if(!escaped && !commented && next == ignoreBreak)
		{
			ignoreTokenBreak = !ignoreTokenBreak;
			addNext = false;
		}

		if(!escaped && !commented && next == comment)
		{
			commented = true;
			addNext = false;
		}

		if(!escaped && next == linebreak)
		{
			addNext = false;
		}

		if(addNext)
		{
			size_t ignoreLen = strlen(ignore);

			size_t ignoreIt = 0;

			uint64_t ignoreNext = ignore[ignoreIt];

			size_t symbolLen = 0;

			while(ignoreIt < ignoreLen)
			{
				ignoreNext = p_loadNext(NULL, ignore, &symbolLen, &ignoreIt);

				if(next == ignoreNext)
				{
					addNext = false;
					break;
				}
			}
		}

		if(addNext) token = PLEX_concatString50(token, next, symbolLen);

		if((!ignoreTokenBreak && addToken) || (addLine && token.len))
		{
			if(token.len)
			{
				PLEX_PARSELINE* nextLine = PLEX_getExpandArrayLastInt(ret->lines, errorline, errorfile);

				PLEX_FAKESTRING_500 bigToken = PLEX_createString500Int(PLEX_fts(token), errorline, errorfile);

				if(!addLine && !commented) bigToken = PLEX_concatString500(bigToken, ' ', 1);

				if(commented)
				{
					nextLine->commentString = PLEX_mergeString500(nextLine->commentString, bigToken);
				}else{
					nextLine->line = PLEX_mergeString500(nextLine->line, bigToken);

					if(!p_addToken(nextLine, token, errorline, errorfile))
					{
						PLEX_errorInt(PLEX_ERROR_CATEGORY_FILEPARSE, PLEX_ERROR_CREATE, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_FILEPARSE_ONPARSEFILE, PLEX_ERRORMESS_GENERIC_TOKEN, errorline, errorfile);
						return false;
					}
				}
			}

			token = PLEX_blankString50Int(errorline, errorfile);
		}

		if(addLine)
		{
			if(!isMultiline)
			{
				const size_t lineCount = PLEX_expandArrayCountInt(ret->lines, errorline, errorfile);

				if(lineCount)
				{
					if(!p_addLine(ret, errorline, errorfile))
					{
						PLEX_errorInt(PLEX_ERROR_CATEGORY_FILEPARSE, PLEX_ERROR_CREATE, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_FILEPARSE_ONPARSEFILE, PLEX_ERRORMESS_GENERIC_LINE, errorline, errorfile);
						return false;
					}
				}

				commented = false;
				ignoreTokenBreak = false;
			}

			isMultiline = false;
		}

		last = next;
		next = p_loadNext(file, NULL, &symbolLen, &iterator);
	}

	if(token.len)
	{
		PLEX_FAKESTRING_500 bigToken;

		PLEX_PARSELINE* nextLine = PLEX_getExpandArrayLastInt(ret->lines, errorline, errorfile);

		if(nextLine == NULL)
		{
			PLEX_errorInt(PLEX_ERROR_CATEGORY_FILEPARSE, PLEX_ERROR_ACQUIRELAST, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_FILEPARSE_ONPARSEFILE, PLEX_ERRORMESS_GENERIC_NEXTLINE, errorline, errorfile);
			return false;
		}

		bigToken = PLEX_createString500Int(PLEX_fts(token), errorline, errorfile);

		bigToken = PLEX_concatString500(bigToken, ' ', 1);

		if(commented) nextLine->commentString = PLEX_mergeString500(nextLine->commentString, bigToken);
		else{
			nextLine->line = PLEX_mergeString500(nextLine->line, bigToken);

			if(!p_addToken(nextLine, token, errorline, errorfile))
			{
				PLEX_errorInt(PLEX_ERROR_CATEGORY_FILEPARSE, PLEX_ERROR_CREATE, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_FILEPARSE_ONPARSEFILE, PLEX_ERRORMESS_GENERIC_TOKEN, errorline, errorfile);
				return false;
			}
		}
	}

	fclose(file);

	return ret;
}

void PLEX_destroyParseFileInt(PLEX_PARSEDFILE** pFile, const size_t errorline, const char* const errorfile)
{
	PLEX_PARSEDFILE* pFilePtr = NULL;

	size_t lineCount = 0;

	if(pFile == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_FILEPARSE, PLEX_ERROR_FREENULLPTR, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_FILEPARSE_ONPARSEFILEDESTROY, PLEX_ERRORMESS_GENERIC_FILEPTR, errorline, errorfile);
		return;
	}

	pFilePtr = *pFile;

	if(pFilePtr == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_FILEPARSE, PLEX_ERROR_FREENULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_FILEPARSE_ONPARSEFILEDESTROY, PLEX_ERRORMESS_GENERIC_FILE, errorline, errorfile);
		return;
	}

	lineCount = PLEX_expandArrayCountInt(pFilePtr->lines, errorline, errorfile);

	for(size_t ze = 0; ze < lineCount; ++ze)
	{
		PLEX_PARSELINE* line = PLEX_getExpandArrayEntryInt(ze, pFilePtr->lines, errorline, errorfile);

		if(line == NULL)
		{
			PLEX_errorInt(PLEX_ERROR_CATEGORY_FILEPARSE, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_FILEPARSE_ONPARSEFILEDESTROY, PLEX_ERRORMESS_GENERIC_LINE, errorline, errorfile);
			continue;
		}

		PLEX_destroyExpandArrayInt(&line->tokens, errorline, errorfile);
	}

	PLEX_destroyExpandArrayInt(&pFilePtr->lines, errorline, errorfile);

	PLEX_deallocInt((void**)&pFilePtr, errorline, errorfile);

	*pFile = NULL;
}

void PLEX_exportParsefileInt(const PLEX_PARSEDFILE parsefile, const char* const fileloc, const bool append, const size_t errorline, const char* const errorfile)
{
	size_t count = 0;

	FILE* file = NULL;

	if(parsefile.lines == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_FILEPARSE, PLEX_ERROR_CONTENTCORRUPTION, PLEX_ERROR_SEVERITY_IMPOSSIBLE, PLEX_ERRORMESS_FILEPARSE_ONEXPORTPARSEFILE, PLEX_ERRORMESS_GENERIC_LINES, errorline, errorfile);
		return;
	}

	file = fopen(fileloc, append ? "a+" : "w+");

	if(file == NULL)
	{
		const PLEX_FAKESTRING_100 targMessage = PLEX_fileLoadErrorPath(fileloc, PLEX_ERRORMESS_GENERIC_FILE);

		PLEX_errorInt(PLEX_ERROR_CATEGORY_FILEPARSE, PLEX_ERROR_FILELOAD, PLEX_ERROR_SEVERITY_MAJOR, PLEX_ERRORMESS_FILEPARSE_ONEXPORTPARSEFILE, PLEX_fts(targMessage), errorline, errorfile);

		return;
	}

	count = PLEX_expandArrayCountInt(parsefile.lines, errorline, errorfile);

	for(size_t ze = 0; ze < count; ++ze)
	{
		size_t linebreakSymbolLen = 0;

		char* lbuffer = (char*)&parsefile.linebreak;

		PLEX_PARSELINE* line = PLEX_getExpandArrayEntryInt(ze, parsefile.lines, errorline, errorfile);

		if(line == NULL)
		{
			PLEX_errorInt(PLEX_ERROR_CATEGORY_FILEPARSE, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_FILEPARSE_ONEXPORTPARSEFILE, PLEX_ERRORMESS_GENERIC_LINE, errorline, errorfile);
			return;
		}

		fwrite((char*)&line->line, line->line.len, 1, file);

		if(line->commentString.len)
		{
			size_t commentSymbolLen = 0;

			char* cbuffer = (char*)&parsefile.comment;

			p_readUnicode(&commentSymbolLen, parsefile.comment);

			fwrite(cbuffer, commentSymbolLen, 1, file);

			fwrite((char*)&line->commentString, line->commentString.len, 1, file);
		}

		p_readUnicode(&linebreakSymbolLen, parsefile.linebreak);

		fwrite(lbuffer, linebreakSymbolLen, 1, file);
	}

	fclose(file);
}

// getters ------------------------------------------------------------------------------------------------------------------

PLEX_PARSELINE* PLEX_getParselineInt(const size_t index, PLEX_PARSEDFILE* parseFile, const size_t errorline, const char* const errorfile)
{
	size_t lineCount = 0;

	PLEX_PARSELINE* ret = 0;

	if(parseFile == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_FILEPARSE, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_FILEPARSE_ONGETPARSELINE, PLEX_ERRORMESS_FILEPARSE_PARSEFILE, errorline, errorfile);
		return NULL;
	}

	lineCount = PLEX_expandArrayCountInt(parseFile->lines, errorline, errorfile);

	if(index >= lineCount)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_FILEPARSE, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_FILEPARSE_ONGETPARSELINE, PLEX_ERRORMESS_GENERIC_LINES, errorline, errorfile);
		return NULL;
	}

	ret = PLEX_getExpandArrayEntryInt(index, parseFile->lines, errorline, errorfile);

	if(ret == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_FILEPARSE, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_FILEPARSE_ONGETPARSELINE, PLEX_ERRORMESS_FILEPARSE_PARSEFILE, errorline, errorfile);
		return NULL;
	}

	return ret;
}

bool PLEX_getTokenInt(const size_t lineIndex, const size_t tokenIndex, PLEX_FAKESTRING_50* token, PLEX_PARSEDFILE* parseFile, const size_t errorline, const char* const errorfile)
{
	PLEX_PARSELINE* parseLine = NULL;

	size_t tokenCount = 0;

	PLEX_FAKESTRING_50* token2 = NULL;

	if(parseFile == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_FILEPARSE, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_FILEPARSE_ONGETTOKEN, PLEX_ERRORMESS_FILEPARSE_PARSEFILE, errorline, errorfile);
		return false;
	}

	parseLine = PLEX_getParselineInt(lineIndex, parseFile, errorline, errorfile);

	if(parseLine == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_FILEPARSE, PLEX_ERROR_CREATE, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_FILEPARSE_ONGETTOKEN, PLEX_ERRORMESS_GENERIC_LINE, errorline, errorfile);
		return false;
	}

	tokenCount = PLEX_expandArrayCountInt(parseLine->tokens, errorline, errorfile);

	if(tokenIndex >= tokenCount)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_FILEPARSE, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_FILEPARSE_ONGETTOKEN, PLEX_ERRORMESS_GENERIC_TOKENS, errorline, errorfile);
		return false;
	}

	token2 = PLEX_getExpandArrayEntryInt(tokenIndex, parseLine->tokens, errorline, errorfile);

	if(token2 == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_FILEPARSE, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_FILEPARSE_ONGETTOKEN, PLEX_ERRORMESS_GENERIC_TOKEN2, errorline, errorfile);
		return false;
	}

	*token = *token2;

	return true;
}

size_t PLEX_parseLineCountInt(const PLEX_PARSEDFILE* parseFile, const size_t errorline, const char* const errorfile)
{
	if(parseFile == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_FILEPARSE, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_FILEPARSE_ONGETPARSELINECOUNT, PLEX_ERRORMESS_FILEPARSE_PARSEFILE, errorline, errorfile);
		return 0;
	}

	if(parseFile->lines == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_FILEPARSE, PLEX_ERROR_CONTENTCORRUPTION, PLEX_ERROR_SEVERITY_IMPOSSIBLE, PLEX_ERRORMESS_FILEPARSE_ONGETPARSELINECOUNT, PLEX_ERRORMESS_GENERIC_LINES, errorline, errorfile);
		return 0;
	}

	return PLEX_expandArrayCountInt(parseFile->lines, errorline, errorfile);
}

size_t PLEX_parseTokenCountInt(const size_t index, PLEX_PARSEDFILE* parseFile, const size_t errorline, const char* const errorfile)
{
	PLEX_PARSELINE* line = NULL;

	size_t lineCount = 0;

	if(parseFile == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_FILEPARSE, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_FILEPARSE_ONGETTOKENCOUNT, PLEX_ERRORMESS_GENERIC_FILE, errorline, errorfile);
		return 0;
	}

	if(parseFile->lines == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_FILEPARSE, PLEX_ERROR_CONTENTCORRUPTION, PLEX_ERROR_SEVERITY_IMPOSSIBLE, PLEX_ERRORMESS_FILEPARSE_ONGETTOKENCOUNT, PLEX_ERRORMESS_GENERIC_LINES, errorline, errorfile);
		return 0;
	}

	lineCount = PLEX_expandArrayCountInt(parseFile->lines, errorline, errorfile);

	if(index >= lineCount)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_FILEPARSE, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_FILEPARSE_ONGETTOKENCOUNT, PLEX_ERRORMESS_GENERIC_LINES, errorline, errorfile);
		return 0;
	}

	line = PLEX_getParselineInt(index, parseFile, errorline, errorfile);

	return PLEX_expandArrayCountInt(line->tokens, errorline, errorfile);
}
