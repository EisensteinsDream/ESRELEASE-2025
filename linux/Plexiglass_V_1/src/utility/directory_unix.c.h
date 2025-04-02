#ifndef PLEX_DIRECTORY_UNIX_C_H
#define PLEX_DIRECTORY_UNIX_C_H

// NOTE: global function descriptions in header.

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

// specialized functions ----------------------------------------------------------------------------------------------------

bool PLEX_startDirectoryCrawlerInt(PLEX_DIRECTORY* directory, const size_t errorline, const char* const errorfile)
{
	if(directory == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DIRECTORY, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DIRECTORY_ONSTARTCRAWLER, PLEX_ERRORMESS_DIRECTORY_DIRECTORY, errorline, errorfile);
		return false;
	}

	if(!directory->open)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DIRECTORY, PLEX_ERROR_DIRECTORYOPENSTATE, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DIRECTORY_ONSTARTCRAWLER, PLEX_ERRORMESS_GENERIC_CLOSED, errorline, errorfile);
		return false;
	}

	if(directory->contents == NULL) // < should be checked after checking "if closed" always
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DIRECTORY, PLEX_ERROR_CONTENTCORRUPTION, PLEX_ERROR_SEVERITY_IMPOSSIBLE, PLEX_ERRORMESS_DIRECTORY_ONSTARTCRAWLER, PLEX_ERRORMESS_DIRECTORY_DIRECTORYCONTENTS, errorline, errorfile);
		return false;
	}

	rewinddir(directory->contents);

	return true;
}

bool PLEX_crawlDirectoryInt(const bool readOnly, PLEX_DIRECTORY* directory, PLEX_DIRECTORYCRAWL_DATA* output, const size_t errorline, const char* const errorfile)
{
	struct dirent* crawler = NULL;

	DIR* testDir = NULL;

	char* path = NULL;
	char* fullpath = NULL;

	size_t namelen = 0;
	size_t direclen = 0;

	if(directory == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DIRECTORY, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DIRECTORY_ONCRAWL, PLEX_ERRORMESS_DIRECTORY_DIRECTORY, errorline, errorfile);
		return false;
	}

	if(output == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DIRECTORY, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DIRECTORY_ONCRAWL, PLEX_ERRORMESS_DIRECTORY_CRAWLER, errorline, errorfile);
		return false;
	}

	if(!directory->open)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DIRECTORY, PLEX_ERROR_DIRECTORYOPENSTATE, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DIRECTORY_ONCRAWL, PLEX_ERRORMESS_GENERIC_CLOSED, errorline, errorfile);
		return false;
	}

	if(directory->contents == NULL) // < should be checked after checking "if closed" always
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DIRECTORY, PLEX_ERROR_CONTENTCORRUPTION, PLEX_ERROR_SEVERITY_IMPOSSIBLE, PLEX_ERRORMESS_DIRECTORY_ONCRAWL, PLEX_ERRORMESS_DIRECTORY_DIRECTORYCONTENTS, errorline, errorfile);
		return false;
	}

	output->path = PLEX_blankString100Int(errorline, errorfile);
	output->file = NULL;
	output->directory = NULL;
	output->isDirectory = false;

	crawler = readdir(directory->contents);

	if(crawler == NULL)
	{
		rewinddir(directory->contents);
		return false;
	}

	namelen = strlen(crawler->d_name);
	direclen = directory->path.len;

	path = PLEX_allocInt(PATH_MAX, errorline, errorfile);
	fullpath = PLEX_allocInt(PATH_MAX, errorline, errorfile);

	memcpy(path, PLEX_fts(directory->path), direclen);
	path[direclen] = '/';
	memcpy(path + direclen + 1, crawler->d_name, namelen);

	realpath(path, fullpath);

	output->path = PLEX_createString100Int(path, errorline, errorfile);
	output->fullPath = PLEX_createString100Int(fullpath, errorline, errorfile);

	testDir = opendir(fullpath);

	if(testDir == NULL)
	{
		const char* const fArgs = readOnly ? "rb" : "rab+";

		output->file = fopen(fullpath, fArgs);

		if(output->file == NULL)
		{
			PLEX_FAKESTRING_100 targMessage;

			PLEX_FAKESTRING_100 createMessage = PLEX_createString100Int(PLEX_ERRORMESS_DIRECTORY_DIRECTORYCONTENTS, errorline, errorfile);
			PLEX_FAKESTRING_100 pathMessage = PLEX_createString100Int(fullpath, errorline, errorfile);

			createMessage = PLEX_concatString100(createMessage, '(', 1);
			createMessage = PLEX_mergeString100(createMessage, pathMessage);
			createMessage = PLEX_concatString100(createMessage, ')', 1);

			PLEX_deallocInt((void**)&path, errorline, errorfile);
			PLEX_deallocInt((void**)&fullpath, errorline, errorfile);

			targMessage = PLEX_fileLoadErrorPath(PLEX_fts(createMessage), PLEX_ERRORMESS_DIRECTORY_DIRECTORY);

			PLEX_errorInt(PLEX_ERROR_CATEGORY_DIRECTORY, PLEX_ERROR_FILELOAD, PLEX_ERROR_SEVERITY_MAJOR, PLEX_ERRORMESS_DIRECTORY_ONCRAWL, PLEX_fts(targMessage), errorline, errorfile);

			return false;
		}
	}else{
		output->directory = testDir;
		output->isDirectory = true;
	}

	PLEX_deallocInt((void**)&path, errorline, errorfile);
	PLEX_deallocInt((void**)&fullpath, errorline, errorfile);

	return true;
}

bool PLEX_reopenDirectoryInt(PLEX_DIRECTORY* directory, const size_t errorline, const char* const errorfile)
{
	if(directory == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DIRECTORY, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DIRECTORY_ONREOPEN, PLEX_ERRORMESS_DIRECTORY_DIRECTORY, errorline, errorfile);
		return false;
	}

	if(directory->open)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DIRECTORY, PLEX_ERROR_DIRECTORYOPENSTATE, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DIRECTORY_ONREOPEN, PLEX_ERRORMESS_GENERIC_OPENED, errorline, errorfile);
		return false;
	}

	if(directory->contents == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DIRECTORY, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_DIRECTORY_ONREOPEN, PLEX_ERRORMESS_DIRECTORY_DIRECTORYCONTENTS, errorline, errorfile); // < this should not be a content corruption error
		return false;
	}

	directory->contents = opendir(PLEX_fts(directory->path));

	if(directory->contents == NULL)
	{
		PLEX_FAKESTRING_100 targMessage;

		PLEX_FAKESTRING_100 createMessage = PLEX_createString100Int(PLEX_ERRORMESS_DIRECTORY_DIRECTORYCONTENTS, errorline, errorfile);

		createMessage = PLEX_concatString100(createMessage, '(', 1);
		createMessage = PLEX_mergeString100(createMessage, directory->path);
		createMessage = PLEX_concatString100(createMessage, ')', 1);

		targMessage = PLEX_fileLoadErrorPath(PLEX_fts(createMessage), PLEX_ERRORMESS_DIRECTORY_DIRECTORY);

		PLEX_errorInt(PLEX_ERROR_CATEGORY_DIRECTORY, PLEX_ERROR_FILELOAD, PLEX_ERROR_SEVERITY_MAJOR, PLEX_ERRORMESS_DIRECTORY_ONREOPEN, PLEX_fts(targMessage), errorline, errorfile);
		return false;
	}

	directory->open = true;

	PLEX_startDirectoryCrawlerInt(directory, errorline, errorfile);

	return true;
}

bool PLEX_closeDirectoryInt(PLEX_DIRECTORY* directory, const size_t errorline, const char* const errorfile)
{
	if(directory == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DIRECTORY, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DIRECTORY_ONCLOSE, PLEX_ERRORMESS_DIRECTORY_DIRECTORY, errorline, errorfile);
		return false;
	}

	if(!directory->open)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DIRECTORY, PLEX_ERROR_DIRECTORYOPENSTATE, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DIRECTORY_ONCLOSE, PLEX_ERRORMESS_GENERIC_CLOSED, errorline, errorfile);
		return false;
	}

	if(directory->contents == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DIRECTORY, PLEX_ERROR_CONTENTCORRUPTION, PLEX_ERROR_SEVERITY_IMPOSSIBLE, PLEX_ERRORMESS_DIRECTORY_ONCLOSE, PLEX_ERRORMESS_DIRECTORY_DIRECTORYCONTENTS, errorline, errorfile);
		return false;
	}

	if(closedir(directory->contents) < 0)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DIRECTORY, PLEX_ERROR_BADOPERATION, PLEX_ERROR_SEVERITY_MAJOR, PLEX_ERRORMESS_DIRECTORY_ONCLOSE, PLEX_ERRORMESS_OP_CLOSEDIRECTORY, errorline, errorfile);
		return false;
	}

	directory->contents = NULL;
	directory->open = false;

	return true;
}

void PLEX_freeDirectoryCrawlerDataInt(PLEX_DIRECTORYCRAWL_DATA* output, const size_t errorline, const char* const errorfile)
{
	if(output == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DIRECTORY, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DIRECTORY_ONFREECRAWLER, PLEX_ERRORMESS_DIRECTORY_CRAWLER, errorline, errorfile);
		return;
	}

	if(output->file != NULL) fclose(output->file);
	if(output->directory != NULL) closedir(output->directory);

	output->file = NULL;
	output->directory = NULL;
}

// getters ------------------------------------------------------------------------------------------------------------------

bool PLEX_getDirectoryInt(const char* const path, PLEX_DIRECTORY* directory, const size_t errorline, const char* const errorfile)
{
	char* fullpath = NULL;

	if(path == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DIRECTORY, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DIRECTORY_ONGET, PLEX_ERRORMESS_GENERIC_FILEPATH, errorline, errorfile);
		return false;
	}

	if(path[0] == '\0')
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DIRECTORY, PLEX_ERROR_NOSTRINGLEN, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DIRECTORY_ONGET, PLEX_ERRORMESS_GENERIC_FILEPATH, errorline, errorfile);
		return false;
	}

	if(directory == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DIRECTORY, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DIRECTORY_ONGET, PLEX_ERRORMESS_DIRECTORY_DIRECTORY, errorline, errorfile);
		return false;
	}

	directory->open = false;
	directory->path = PLEX_blankString100Int(errorline, errorfile);
	directory->fullPath = PLEX_blankString100Int(errorline, errorfile);

	directory->contents = opendir(path);

	if(directory->contents == NULL)
	{
		PLEX_FAKESTRING_100 targMessage;

		PLEX_FAKESTRING_100 createMessage = PLEX_createString100Int(PLEX_ERRORMESS_DIRECTORY_DIRECTORYCONTENTS, errorline, errorfile);

		PLEX_FAKESTRING_100 pathStr = PLEX_createString100Int(path, errorline, errorfile);

		createMessage = PLEX_concatString100(createMessage, '(', 1);
		createMessage = PLEX_mergeString100(createMessage, pathStr);
		createMessage = PLEX_concatString100(createMessage, ')', 1);

		targMessage = PLEX_fileLoadErrorPath(PLEX_fts(createMessage), PLEX_ERRORMESS_DIRECTORY_DIRECTORY);

		PLEX_errorInt(PLEX_ERROR_CATEGORY_DIRECTORY, PLEX_ERROR_FILELOAD, PLEX_ERROR_SEVERITY_MAJOR, PLEX_ERRORMESS_DIRECTORY_ONGET, PLEX_fts(targMessage), errorline, errorfile);
		return false;
	}

	fullpath = PLEX_allocInt(PATH_MAX, errorline, errorfile);

	realpath(path, fullpath);

	directory->fullPath = PLEX_createString100Int(fullpath, errorline, errorfile);

	PLEX_deallocInt((void**)&fullpath, errorline, errorfile);

	PLEX_startDirectoryCrawlerInt(directory, errorline, errorfile);

	directory->path = PLEX_createString100Int(path, errorline, errorfile);
	directory->open = true;

	return true;
}

bool PLEX_compPathsInt(const char* const a, const char* const b, const size_t errorline, const char* const errorfile)
{
	bool ret = false;

	char* fullpathA = NULL;
	char* fullpathB = NULL;

	PLEX_FAKESTRING_100 pathStrA;
	PLEX_FAKESTRING_100 pathStrB;

	if(a == NULL && b == NULL) return true;
	if(a == NULL || b == NULL) return false;

	fullpathA = PLEX_allocInt(PATH_MAX, errorline, errorfile);

	if(fullpathA == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DIRECTORY, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DIRECTORY_ONCOMPPATHS, PLEX_ERRORMESS_GENERIC_FILEPATH, errorline, errorfile);
		return false;
	}

	fullpathB = PLEX_allocInt(PATH_MAX, errorline, errorfile);

	if(fullpathB == NULL)
	{
		PLEX_deallocInt((void**)&fullpathA, errorline, errorfile);
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DIRECTORY, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DIRECTORY_ONCOMPPATHS, PLEX_ERRORMESS_GENERIC_FILEPATH2, errorline, errorfile);
		return false;
	}

	realpath(a, fullpathA);
	realpath(b, fullpathB);

	pathStrA = PLEX_createString100Int(fullpathA, errorline, errorfile);
	pathStrB = PLEX_createString100Int(fullpathB, errorline, errorfile);

	ret = PLEX_compStrings100Int(pathStrA, pathStrB, false, errorline, errorfile);

	PLEX_deallocInt((void**)&fullpathA, errorline, errorfile);
	PLEX_deallocInt((void**)&fullpathB, errorline, errorfile);

	return ret;
}

#endif
