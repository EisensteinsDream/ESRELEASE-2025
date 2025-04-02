#ifndef PLEX_DIRECTORY_WINDOWS_C_H
#define PLEX_DIRECTORY_WINDOWS_C_H

// NOTE: global function descriptions in header.

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

// specialized functions ----------------------------------------------------------------------------------------------------

bool PLEX_startDirectoryCrawlerInt(PLEX_DIRECTORY* directory, const size_t errorline, const char* const errorfile)
{
	PLEX_FAKESTRING_100 dirPath;

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

	if(directory->contents == INVALID_HANDLE_VALUE)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DIRECTORY, PLEX_ERROR_CONTENTCORRUPTION, PLEX_ERROR_SEVERITY_IMPOSSIBLE, PLEX_ERRORMESS_DIRECTORY_ONSTARTCRAWLER, PLEX_ERRORMESS_DIRECTORY_DIRECTORYCONTENTS, errorline, errorfile);
		return false;
	}

	dirPath = PLEX_concatString100(directory->path, '\\', 1);
	dirPath = PLEX_concatString100(dirPath, '*', 1);

	directory->contents = FindFirstFile(PLEX_fts(dirPath), &directory->fdata);

	return true;
}

bool PLEX_crawlDirectoryInt(const bool readOnly, PLEX_DIRECTORY* directory, PLEX_DIRECTORYCRAWL_DATA* output, const size_t errorline, const char* const errorfile)
{
	PLEX_FAKESTRING_100 path;

	char fullPath[101]; // < 101 because it's stored in a 100 sized fake string with a null terminator

	if(output == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DIRECTORY, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DIRECTORY_ONCRAWL, PLEX_ERRORMESS_DIRECTORY_CRAWLER, errorline, errorfile);
		return false;
	}

	if(directory == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DIRECTORY, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DIRECTORY_ONCRAWL, PLEX_ERRORMESS_DIRECTORY_DIRECTORY, errorline, errorfile);
		return false;
	}

	if(!directory->open)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DIRECTORY, PLEX_ERROR_DIRECTORYOPENSTATE, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DIRECTORY_ONCRAWL, PLEX_ERRORMESS_GENERIC_CLOSED, errorline, errorfile);
		return false;
	}

	if(directory->contents == INVALID_HANDLE_VALUE)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DIRECTORY, PLEX_ERROR_CONTENTCORRUPTION, PLEX_ERROR_SEVERITY_IMPOSSIBLE, PLEX_ERRORMESS_DIRECTORY_ONCRAWL, PLEX_ERRORMESS_DIRECTORY_DIRECTORYCONTENTS, errorline, errorfile);
		return false;
	}

	if(output->done) return false;

	if(output->directory == INVALID_HANDLE_VALUE || output->directory == NULL)
	{
		output->fdata = directory->fdata;
		output->directory = directory->contents;
	}

	if(output->file != NULL) fclose(output->file);
	output->file = NULL;

	output->path = PLEX_createString100Int(output->fdata.cFileName, errorline, errorfile);

	path = directory->path;
	path = PLEX_concatString100(path, '/', 1);

	GetFullPathNameA(PLEX_fts(path), 100, fullPath, NULL);

	output->fullPath = PLEX_createString100Int(fullPath, errorline, errorfile);
	output->fullPath = PLEX_mergeString100Int(output->fullPath, output->path, errorline, errorfile);

	output->isDirectory = output->fdata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY;

	if(!output->isDirectory)
	{
		const char* const fstr = readOnly ? "rb" : "ab+";

		output->file = fopen(output->fdata.cFileName, fstr);

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
	}

	if(!FindNextFile(output->directory, &output->fdata)) output->done = true;

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

	directory->contents = FindFirstFile(PLEX_fts(directory->fullPath), &directory->fdata);

	if(directory->contents == INVALID_HANDLE_VALUE)
	{
		PLEX_FAKESTRING_100 targMessage;

		PLEX_FAKESTRING_100 createMessage = PLEX_createString100Int(PLEX_ERRORMESS_DIRECTORY_DIRECTORYCONTENTS, errorline, errorfile);

		createMessage = PLEX_concatString100(createMessage, '(', 1);
		createMessage = PLEX_mergeString100Int(createMessage, directory->path, errorline, errorfile);
		createMessage = PLEX_concatString100(createMessage, ')', 1);

		targMessage = PLEX_fileLoadErrorPath(PLEX_fts(createMessage), PLEX_ERRORMESS_DIRECTORY_DIRECTORY);

		directory->path = PLEX_blankString100(errorline, errorfile);
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DIRECTORY, PLEX_ERROR_FILELOAD, PLEX_ERROR_SEVERITY_MAJOR, PLEX_ERRORMESS_DIRECTORY_ONREOPEN, PLEX_fts(targMessage), errorline, errorfile);
		return false;
	}

	directory->open = true;

	return false;
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

	if(directory->contents == INVALID_HANDLE_VALUE)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DIRECTORY, PLEX_ERROR_CONTENTCORRUPTION, PLEX_ERROR_SEVERITY_IMPOSSIBLE, PLEX_ERRORMESS_DIRECTORY_ONCLOSE, PLEX_ERRORMESS_DIRECTORY_DIRECTORYCONTENTS, errorline, errorfile);
		return false;
	}

	FindClose(directory->contents);

	directory->contents = INVALID_HANDLE_VALUE;
	directory->open = false;

	return false;
}

void PLEX_freeDirectoryCrawlerDataInt(PLEX_DIRECTORYCRAWL_DATA* output, const size_t errorline, const char* const errorfile)
{
	if(output == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_DIRECTORY, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_DIRECTORY_ONFREECRAWLER, PLEX_ERRORMESS_DIRECTORY_CRAWLER, errorline, errorfile);
		return;
	}

	if(output->file != NULL) fclose(output->file);

	// windows API specifies the directory from FindNextFile does not need to be closed

	output->file = NULL;
	output->done = false;

	output->directory = INVALID_HANDLE_VALUE;
}

// getters ------------------------------------------------------------------------------------------------------------------

bool PLEX_getDirectoryInt(const char* const path, PLEX_DIRECTORY* directory, const size_t errorline, const char* const errorfile)
{
	PLEX_FAKESTRING_100 dirPath;

	char fullPath[101]; // < 101 because it's stored in a 100 sized fake string with a null terminator

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
	directory->path = PLEX_createString100Int(path, errorline, errorfile);
	directory->fullPath = PLEX_blankString100(errorline, errorfile);

	dirPath = PLEX_concatString100(directory->path, '\\', 1);
	dirPath = PLEX_concatString100(dirPath, '*', 1);

	directory->contents = FindFirstFile(PLEX_fts(dirPath), &directory->fdata);

	if(directory->contents == INVALID_HANDLE_VALUE)
	{
		PLEX_FAKESTRING_100 targMessage;

		PLEX_FAKESTRING_100 createMessage = PLEX_createString100Int(PLEX_ERRORMESS_DIRECTORY_DIRECTORYCONTENTS, errorline, errorfile);

		createMessage = PLEX_concatString100(createMessage, '(', 1);
		createMessage = PLEX_mergeString100Int(createMessage, directory->path, errorline, errorfile);
		createMessage = PLEX_concatString100(createMessage, ')', 1;

		directory->path = PLEX_blankString100(errorline, errorfile);

		targMessage = PLEX_fileLoadErrorPath(PLEX_fts(createMessage), PLEX_ERRORMESS_DIRECTORY_DIRECTORY);

		PLEX_errorInt(PLEX_ERROR_CATEGORY_DIRECTORY, PLEX_ERROR_FILELOAD, PLEX_ERROR_SEVERITY_MAJOR, PLEX_ERRORMESS_DIRECTORY_ONGET, PLEX_fts(targMessage), errorline, errorfile);
		return false;
	}

	GetFullPathNameA(path, 100, fullPath, NULL);

	directory->fullPath = PLEX_createString100Int(fullPath, errorline, errorfile);
	directory->open = true;

	return true;
}

bool PLEX_compPathsInt(const char* const a, const char* const b, const size_t errorline, const char* const errorfile)
{
	bool ret = false;

	char fullpathA[100];
	char fullpathB[100];

	PLEX_FAKESTRING_100 pathStrA;
	PLEX_FAKESTRING_100 pathStrB;

	if(a == NULL && b == NULL) return true;
	if(a == NULL || b == NULL) return false;

	GetFullPathNameA(a, 100, fullpathA, NULL);
	GetFullPathNameA(b, 100, fullpathB, NULL);

	pathStrA = PLEX_createString100Int(fullpathA, errorline, errorfile);
	pathStrB = PLEX_createString100Int(fullpathB, errorline, errorfile);

	ret = PLEX_compStrings100Int(pathStrA, pathStrB, false, errorline, errorfile);

	return true;
}

#endif
