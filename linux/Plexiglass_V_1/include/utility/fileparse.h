#ifndef PLEX_FILEPARSE_H
#define PLEX_FILEPARSE_H

#include "utility/fakestrings.h"

#include "mem/expandarray.h"

// this unit is for parsing files into parsefiles and tokens. It's very very flexible. Far more flexible than the strtok function. You can decide your own line breaks, token breaks, comments, escape characters, etc. Also it's easy to allocate and deallocate parsed files which are allocated in PLEX's controlled memory.

// NOTE: This is an independent unit. Not a unit with an accompanying state machine. It has no 'start, update, or end' functions that need to be called to operate.

// macro functions and macros -----------------------------------------------------------------------------------------------

// ARGUMENTS: (const uint64_t linebreak, const uint64_t tokenbreak, const uint64_t comment, const uint64_t escape, const uint64_t ignoreBreak, const uint64_t multiline, const char* const ignore, const char* const fileloc) - returns PLEX_PARSEDFILE*

#define PLEX_parseFile(linebreak, tokenbreak, comment, escape, ignoreBreak, multiline, ignore, fileloc) PLEX_parseFileInt(linebreak, tokenbreak, comment, escape, ignoreBreak, multiline, ignore, fileloc, __LINE__, __FILE__)

// ARGUMENTS: (PLEX_PARSEDFILE** pFile)

#define PLEX_destroyParseFile(pFile) PLEX_destroyParseFileInt(pFile, __LINE__, __FILE__)

// ARGUMENTS: (const PLEX_PARSEDFILE parsefile, const char* const fileloc, const bool append)

#define PLEX_exportParsefile(parsefile, fileloc, append) PLEX_exportParsefileInt(parsefile, fileloc, append, __LINE__, __FILE__)

// ARGUMENTS: (const size_t index, PLEX_PARSEDFILE* parseFile) - returns PLEX_PARSEDFILE*

#define PLEX_getParseline(index, parseFile) PLEX_getParselineInt(index, parseFile, __LINE__, __FILE__)

// ARGUMENTS: (const size_t lineIndex, const size_t tokenIndex, PLEX_FAKESTRING_50* token, PLEX_PARSEDFILE* parseFile) - returns bool

#define PLEX_getToken(lineIndex, tokenIndex, token, parseFile) PLEX_getTokenInt(lineIndex, tokenIndex, token, parseFile, __LINE__, __FILE__)

// ARGUMENTS: (const PLEX_PARSEDFILE* parseFile) - returns size_t

#define PLEX_parseLineCount(parseFile) PLEX_parseLineCountInt(parseFile, __LINE__, __FILE__)

// ARGUMENTS: (const size_t index, PLEX_PARSEDFILE* parseFile) - returns size_t

#define PLEX_parseTokenCount(index, parseFile) PLEX_parseTokenCountInt(index, parseFile, __LINE__, __FILE__)

// structs, unions, enums, function prototypes ------------------------------------------------------------------------------

typedef struct
{
	PLEX_FAKESTRING_500 line, commentString;
	PLEX_EXPANDARRAY* tokens;
} PLEX_PARSELINE;

typedef struct
{
	PLEX_EXPANDARRAY* lines;
	uint64_t linebreak, tokenbreak, comment, ignoreBreak;
} PLEX_PARSEDFILE;

// public functions ---------------------------------------------------------------------------------------------------------

#ifdef __cplusplus
extern"C"
{
#endif
// specialized functions ----------------------------------------------------------------------------------------------------

	// allocates a parse file from 'fileloc'. bringing in the optional characters: linebreak, tokenbreak, ignoreBreak (Breaks out of ignore), multiline (breaks out of line parsing). Also allows a string of characters passed to 'ignore' that are all skipped over.

	extern PLEX_PARSEDFILE* PLEX_parseFileInt(const uint64_t linebreak, const uint64_t tokenbreak, const uint64_t comment, const uint64_t escape, const uint64_t ignoreBreak, const uint64_t multiline, const char* const ignore, const char* const fileloc, const size_t errorline, const char* const errorfile);

	// deallocates a parsefile

	extern void PLEX_destroyParseFileInt(PLEX_PARSEDFILE** pFile, const size_t errorline, const char* const errorfile);

	// exports a parsefile to a text file

	extern void PLEX_exportParsefileInt(const PLEX_PARSEDFILE parsefile, const char* const fileloc, const bool append, const size_t errorline, const char* const errorfile);

// getters ------------------------------------------------------------------------------------------------------------------

	// returns line at 'index' inside parse file. Returns NULL if it cannot.

	extern PLEX_PARSELINE* PLEX_getParselineInt(const size_t index, PLEX_PARSEDFILE* parseFile, const size_t errorline, const char* const errorfile);

	// passes the token at lineIndex and tokenIndex into the token fakestring.

	extern bool PLEX_getTokenInt(const size_t lineIndex, const size_t tokenIndex, PLEX_FAKESTRING_50* token, PLEX_PARSEDFILE* parseFile, const size_t errorline, const char* const errorfile);

	// returns the amount of lines in a parsefile

	extern size_t PLEX_parseLineCountInt(const PLEX_PARSEDFILE* parseFile, const size_t errorline, const char* const errorfile);

	// returns the amount of tokens in a parsefile

	extern size_t PLEX_parseTokenCountInt(const size_t index, PLEX_PARSEDFILE* parseFile, const size_t errorline, const char* const errorfile);
#ifdef __cplusplus
}
#endif

#endif
