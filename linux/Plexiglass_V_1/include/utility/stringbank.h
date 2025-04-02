#ifndef PLEX_STRINGBANK_H
#define PLEX_STRINGBANK_H

#include "utility/fileparse.h"

// NO ARGUMENTS - PLEX_STRINGBANK*

#define PLEX_genStringBank() PLEX_genStringBankInt(__LINE__, __FILE__)

// ARGUMENTS: (PLEX_STRINGBANK** toDestroy)

#define PLEX_destroyStringBank(toDestroy) PLEX_destroyStringBankInt(toDestroy, __LINE__, __FILE__)

// ARGUMENTS: (const char* const string, PLEX_STRINGBANK* bank) - int64_t

#define PLEX_addStringToBank(string, bank) PLEX_addStringToBankInt(string, bank, __LINE__, __FILE__)

// ARGUMENTS: (const size_t index, PLEX_STRINGBANK* bank)

#define PLEX_removeStringFromBank(index, bank) PLEX_removeStringFromBankInt(index, bank, __LINE__, __FILE__)

// ARGUMENTS: (const size_t index, PLEX_STRINGBANK* bank) - returns PLEX_STRINGBANK*

#define PLEX_loadStringBank(fileloc) PLEX_loadStringBankInt(fileloc, __LINE__, __FILE__)

// ARGUMENTS: (const size_t index, PLEX_STRINGBANK* bank) - PLEX_FAKESTRING_500

#define PLEX_getStringBankEntry(index, bank) PLEX_getStringBankEntryInt(index, bank, __LINE__, __FILE__)

// ARGUMENTS: (PLEX_STRINGBANK* bank) - size_t

#define PLEX_stringBankCount(bank) PLEX_stringBankCountInt(bank, __LINE__, __FILE__)

typedef struct
{
	PLEX_EXPANDARRAY* contents;
} PLEX_STRINGBANK;

#ifdef __cplusplus
extern "C"
{
#endif
	extern PLEX_STRINGBANK* PLEX_genStringBankInt(const size_t errorline, const char* const errorfile);

	extern void PLEX_destroyStringBankInt(PLEX_STRINGBANK** toDestroy, const size_t errorline, const char* const errorfile);

	extern int64_t PLEX_addStringToBankInt(const char* const string, PLEX_STRINGBANK* bank, const size_t errorline, const char* const errorfile);

	extern void PLEX_removeStringFromBankInt(const size_t index, PLEX_STRINGBANK* bank, const size_t errorline, const char* const errorfile);

	extern PLEX_STRINGBANK* PLEX_loadStringBankInt(const char* const fileloc, const size_t errorline, const char* const errorfile);

	extern PLEX_FAKESTRING_500 PLEX_getStringBankEntryInt(const size_t index, PLEX_STRINGBANK* bank, const size_t errorline, const char* const errorfile);

	extern size_t PLEX_stringBankCountInt(PLEX_STRINGBANK* bank, const size_t errorline, const char* const errorfile);
#ifdef __cplusplus
}
#endif


#endif
