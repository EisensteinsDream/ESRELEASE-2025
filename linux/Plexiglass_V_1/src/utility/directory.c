#include "utility/directory.h"

// NOTE: global function descriptions in header.

#if PLEX_CORE_IS_UNIX
	#include "directory_unix.c.h"
#endif

#if PLEX_CORE_OS == PLEX_CORE_WINDOWS
	#include "directory_windows.c.h"
#endif

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

// specialized functions ----------------------------------------------------------------------------------------------------

PLEX_DIRECTORYCRAWL_DATA PLEX_blankDirectoryCrawlerData()
{
	PLEX_DIRECTORYCRAWL_DATA ret;

	memset(&ret, 0, sizeof(ret));

	return ret;
}

bool PLEX_compDirectoriesInt(const PLEX_DIRECTORY a, const PLEX_DIRECTORY b, const size_t errorline, const char* const errorfile)
{
	return PLEX_compStrings100Int(a.fullPath, b.fullPath, false, errorline, errorfile);
}

// getters ------------------------------------------------------------------------------------------------------------------

bool PLEX_getDirectoryFromCrawlerDataInt(PLEX_DIRECTORYCRAWL_DATA* output, PLEX_DIRECTORY* directory, const size_t errorline, const char* const errorfile)
{
	if(output == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DIRECTORY, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DIRECTORY_ONGETCRAWLER, PLEX_ERRORMESS_DIRECTORY_CRAWLER, errorline, errorfile);
		return false;
	}

	if(directory == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DIRECTORY, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DIRECTORY_ONGETCRAWLER, PLEX_ERRORMESS_DIRECTORY_DIRECTORY, errorline, errorfile);
		return false;
	}

	if(output->directory == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DIRECTORY, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DIRECTORY_ONGETCRAWLER, PLEX_ERRORMESS_DIRECTORY_CRAWLERSDIRECTORY, errorline, errorfile);
		return false;
	}

	if(!output->isDirectory)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DIRECTORY, PLEX_ERROR_FILETYPE, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_DIRECTORY_ONGETCRAWLER, PLEX_ERRORMESS_DIRECTORY_CRAWLERSDIRECTORY, errorline, errorfile);
		return false;
	}

	return PLEX_getDirectoryInt(PLEX_fts(output->path), directory, errorline, errorfile);
}

bool PLEX_isCrawlerDataDirectory(const PLEX_DIRECTORYCRAWL_DATA output)
{
	return output.isDirectory;
}

bool PLEX_isRedirecDirectory(const PLEX_DIRECTORY directory)
{
	const char* const path = PLEX_fts(directory.path);
	const size_t plen = directory.path.len;

	char symbol = 0;

	if(!plen) return false;
	if(plen == 1) return path[0] == '.';
	if(plen == 2) return path[0] == '.' && path[1] == '.';

	symbol = path[plen - 1];

	if(symbol != '.') return false;

	symbol = path[plen - 2];

	if(symbol == '/' || symbol == '\\') return true;

	if(symbol != '.') return false;

	symbol = path[plen - 3];

	if(symbol != '/' && symbol != '\\') return false;

	return true;
}

PLEX_FAKESTRING_100 PLEX_getDirectoryPathInt(const PLEX_DIRECTORY* const directory, const size_t errorline, const char* const errorfile)
{
	if(directory == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DIRECTORY, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DIRECTORY_ONGETPATH, PLEX_ERRORMESS_DIRECTORY_DIRECTORY, errorline, errorfile);
		return PLEX_blankString100Int(errorline, errorfile);
	}

	return directory->path;
}

PLEX_FAKESTRING_100 PLEX_getDirectoryFullPathInt(const PLEX_DIRECTORY* const directory, const size_t errorline, const char* const errorfile)
{
	if(directory == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DIRECTORY, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DIRECTORY_ONGETFULLPATH, PLEX_ERRORMESS_DIRECTORY_DIRECTORY, errorline, errorfile);
		return PLEX_blankString100Int(errorline, errorfile);
	}

	return directory->fullPath;
}

PLEX_FAKESTRING_100 PLEX_getDirectoryCrawlerPathInt(const PLEX_DIRECTORYCRAWL_DATA* const crawler, const size_t errorline, const char* const errorfile)
{
	if(crawler == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DIRECTORY, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DIRECTORY_ONGETCRAWLERPATH, PLEX_ERRORMESS_DIRECTORY_CRAWLER, errorline, errorfile);
		return PLEX_blankString100Int(errorline, errorfile);
	}

	return crawler->path;
}

PLEX_FAKESTRING_100 PLEX_getDirectoryCrawlerFullPathInt(const PLEX_DIRECTORYCRAWL_DATA* const crawler, const size_t errorline, const char* const errorfile)
{
	if(crawler == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DIRECTORY, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DIRECTORY_ONGETFULLCRAWLERPATH, PLEX_ERRORMESS_DIRECTORY_CRAWLER, errorline, errorfile);
		return PLEX_blankString100Int(errorline, errorfile);
	}

	return crawler->fullPath;
}

FILE* PLEX_getDirectoryCrawlerFileInt(const PLEX_DIRECTORYCRAWL_DATA* const crawler, const size_t errorline, const char* const errorfile)
{
	if(crawler == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DIRECTORY, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DIRECTORY_ONGETCRAWLERFILE, PLEX_ERRORMESS_DIRECTORY_CRAWLER, errorline, errorfile);
		return NULL;
	}

	return crawler->file;
}

bool PLEX_getDirectoryCrawlerIsDirectoryInt(const PLEX_DIRECTORYCRAWL_DATA* const crawler, const size_t errorline, const char* const errorfile)
{
	if(crawler == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DIRECTORY, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DIRECTORY_ONCHECKINGCRAWLERISDIRECTORY, PLEX_ERRORMESS_DIRECTORY_CRAWLER, errorline, errorfile);
		return NULL;
	}

	return crawler->isDirectory;
}
