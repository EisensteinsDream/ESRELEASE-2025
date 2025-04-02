#ifndef PLEX_DIRECTORY_H
#define PLEX_DIRECTORY_H

#include "utility/fakestrings.h"

// NOTE: this is the directory unit. As described, it manages directories. Since directories are OS-specific this abstracts them. Even if there's one header there are multiple source units compiled in relation to this header. First is 'directory.c' which contains anything that is not platform specific. After that it's branched to different directory files that do OS-specific stuff like 'directory_unix.c.h' and 'directory_windows.c.h.'. I don't imagine PLEX ever being ported to anything that isn't unix or windows based (honestly, I can't think of a single modern OS that isn't windows or unix based), but if it is new source files will be created.

// NOTE: This is an independent unit. Not a unit with an accompanying state machine. It has no 'start, update, or end' functions that need to be called to operate.

// macro functions and macros -----------------------------------------------------------------------------------------------

// INSIDE 'directory.c' -----------------------------------------------------------------------------------------------------

// ARGUMENTS: (const PLEX_DIRECTORY a, const PLEX_DIRECTORY b) - returns bool

#define PLEX_compDirectories(a, b) PLEX_compDirectoriesInt(a, b, __LINE__, __FILE__)

// ARGUMENTS: (PLEX_DIRECTORY* directory) - returns bool

#define PLEX_startDirectoryCrawler(directory) PLEX_startDirectoryCrawlerInt(directory, __LINE__, __FILE__)

// ARGUMENTS: (const bool readOnly, PLEX_DIRECTORY* directory, PLEX_DIRECTORYCRAWL_DATA* output) - returns bool

#define PLEX_crawlDirectory(readOnly, directory, output) PLEX_crawlDirectoryInt(readOnly, directory, output, __LINE__, __FILE__)

// ARGUMENTS: (PLEX_DIRECTORYCRAWL_DATA* output)

#define PLEX_freeDirectoryCrawlerData(output) PLEX_freeDirectoryCrawlerDataInt(output, __LINE__, __FILE__)

// ARGUMENTS: (PLEX_DIRECTORY* directory) - returns bool

#define PLEX_reopenDirectory(directory) PLEX_reopenDirectoryInt(directory, __LINE__, __FILE__)

// ARGUMENTS: (PLEX_DIRECTORY* directory) - returns bool

#define PLEX_closeDirectory(directory) PLEX_closeDirectoryInt(directory, __LINE__, __FILE__)

// ARGUMENTS: (PLEX_DIRECTORYCRAWL_DATA* output, PLEX_DIRECTORY* directory) - returns bool

#define PLEX_getDirectoryFromCrawlerData(output, directory) PLEX_getDirectoryFromCrawlerDataInt(output, directory, __LINE__, __FILE__)

// ARGUMENTS: (const PLEX_DIRECTORY* const directory) - returns bool

#define PLEX_getDirectoryPath(directory) PLEX_getDirectoryPathInt(directory, __LINE__, __FILE__)

// ARGUMENTS: (const PLEX_DIRECTORY* const directory) - returns PLEX_FAKESTRING_100

#define PLEX_getDirectoryFullPath(directory) PLEX_getDirectoryFullPathInt(directory, __LINE__, __FILE__)

// ARGUMENTS: (const PLEX_DIRECTORYCRAWL_DATA* const crawler) - returns PLEX_FAKESTRING_100

#define PLEX_getDirectoryCrawlerPath(crawler) PLEX_getDirectoryCrawlerPathInt(crawler, __LINE__, __FILE__)

// ARGUMENTS: (const PLEX_DIRECTORYCRAWL_DATA* const crawler) - returns PLEX_FAKESTRING_100

#define PLEX_getDirectoryCrawlerFullPath(crawler) PLEX_getDirectoryCrawlerFullPathInt(crawler, __LINE__, __FILE__)

// ARGUMENTS: (const PLEX_DIRECTORYCRAWL_DATA* const crawler) - returns FILE*

#define PLEX_getDirectoryCrawlerFile(crawler) PLEX_getDirectoryCrawlerFileInt(crawler, __LINE__, __FILE__)

// ARGUMENTS: (const PLEX_DIRECTORYCRAWL_DATA* const crawler) - returns bool

#define PLEX_getDirectoryCrawlerIsDirectory(crawler) PLEX_getDirectoryCrawlerIsDirectoryInt(crawler, __LINE__, __FILE__)

// ARGUMENTS: (PLEX_DIRECTORYCRAWL_DATA* output, PLEX_DIRECTORY* directory) - returns bool

#define PLEX_getDirectory(path, directory) PLEX_getDirectoryInt(path, directory, __LINE__, __FILE__)

// ARGUMENTS: (const char* const a, const char* const b) - returns bool

#define PLEX_compPaths(a, b) PLEX_compPathsInt(a, b, __LINE__, __FILE__)

// structs, unions, enums, function prototypes ------------------------------------------------------------------------------

typedef struct
{
	PLEX_FAKESTRING_100 path, fullPath;
	bool open;

	#if PLEX_CORE_IS_UNIX
		DIR* contents;
	#endif

	#if PLEX_CORE_OS == PLEX_CORE_WINDOWS
		HANDLE contents;
		WIN32_FIND_DATA fdata;
	#endif

} PLEX_DIRECTORY;

typedef struct
{
	PLEX_FAKESTRING_100 path, fullPath;
	FILE* file;

	#if PLEX_CORE_IS_UNIX
		DIR* directory;
	#endif

	#if PLEX_CORE_OS == PLEX_CORE_WINDOWS
		HANDLE directory;
		WIN32_FIND_DATA fdata;
		bool done;
	#endif

	bool isDirectory;
} PLEX_DIRECTORYCRAWL_DATA;

// public functions --------------------------------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C"
{
#endif

// specialized functions ----------------------------------------------------------------------------------------------------

// INSIDE 'directory.c' -----------------------------------------------------------------------------------------------------

	// returns blank crawler data struct

	extern PLEX_DIRECTORYCRAWL_DATA PLEX_blankDirectoryCrawlerData();

	// compares directories to see if they're the same

	extern bool PLEX_compDirectoriesInt(const PLEX_DIRECTORY a, const PLEX_DIRECTORY b, const size_t errorline, const char* const errorfile);

// INSIDE EITHER 'directory_unix.c.h' or 'directory_windows.c.h' ------------------------------------------------------------

	// initializes a directory crawler inside of a directory. returns false on failure.

	extern bool PLEX_startDirectoryCrawlerInt(PLEX_DIRECTORY* directory, const size_t errorline, const char* const errorfile);

	// continues to crawl through a directory's crawler. returns false on end of crawl.

	extern bool PLEX_crawlDirectoryInt(const bool readOnly, PLEX_DIRECTORY* directory, PLEX_DIRECTORYCRAWL_DATA* output, const size_t errorline, const char* const errorfile);

	// frees the directory crawler. Should be done every time one is created.

	extern void PLEX_freeDirectoryCrawlerDataInt(PLEX_DIRECTORYCRAWL_DATA* output, const size_t errorline, const char* const errorfile);

	// reopens a closed directory

	extern bool PLEX_reopenDirectoryInt(PLEX_DIRECTORY* directory, const size_t errorline, const char* const errorfile);

	// closes a directory

	extern bool PLEX_closeDirectoryInt(PLEX_DIRECTORY* directory, const size_t errorline, const char* const errorfile);

// getters ------------------------------------------------------------------------------------------------------------------

// INSIDE 'directory.c' -----------------------------------------------------------------------------------------------------

	// gets the directory from directory into output struct pointer returns false on failure.

	extern bool PLEX_getDirectoryFromCrawlerDataInt(PLEX_DIRECTORYCRAWL_DATA* output, PLEX_DIRECTORY* directory, const size_t errorline, const char* const errorfile);

	// returns true if the crawler data references a directory

	extern bool PLEX_isCrawlerDataDirectory(const PLEX_DIRECTORYCRAWL_DATA output);

	// checks whether the directory is the '.' or '..' directories. It's available in windows, but only really relevant to unix based systems.

	extern bool PLEX_isRedirecDirectory(const PLEX_DIRECTORY directory);

	// return the directory's path (relative)

	extern PLEX_FAKESTRING_100 PLEX_getDirectoryPathInt(const PLEX_DIRECTORY* const directory, const size_t errorline, const char* const errorfile);

	// return the directory's path (absolute)

	extern PLEX_FAKESTRING_100 PLEX_getDirectoryFullPathInt(const PLEX_DIRECTORY* const directory, const size_t errorline, const char* const errorfile);

	// return the directory crawler's path (relative)

	extern PLEX_FAKESTRING_100 PLEX_getDirectoryCrawlerPathInt(const PLEX_DIRECTORYCRAWL_DATA* const crawler, const size_t errorline, const char* const errorfile);

	// return the directory crawlers path (absolute)

	extern PLEX_FAKESTRING_100 PLEX_getDirectoryCrawlerFullPathInt(const PLEX_DIRECTORYCRAWL_DATA* const crawler, const size_t errorline, const char* const errorfile);

	// returns a file from the directory crawler (NULL if there is no file)

	extern FILE* PLEX_getDirectoryCrawlerFileInt(const PLEX_DIRECTORYCRAWL_DATA* const crawler, const size_t errorline, const char* const errorfile);

	// returns true if the directory crawler is a directory

	extern bool PLEX_getDirectoryCrawlerIsDirectoryInt(const PLEX_DIRECTORYCRAWL_DATA* const crawler, const size_t errorline, const char* const errorfile);

// INSIDE EITHER 'directory_unix.c.h' or 'directory_windows.c.h' ------------------------------------------------------------

	// puts a directory from 'path' into the directory stuct pointer. returns false on failure.

	extern bool PLEX_getDirectoryInt(const char* const path, PLEX_DIRECTORY* directory, const size_t errorline, const char* const errorfile);

	// compares two string paths to see if they're the same filepath

	extern bool PLEX_compPathsInt(const char* const a, const char* const b, const size_t errorline, const char* const errorfile);
#ifdef __cplusplus
}
#endif


#endif
