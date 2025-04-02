#include "mem/mem.h"

// NOTE: global function descriptions in header.

// structs ------------------------------------------------------------------------------------------------------------------

typedef struct
{
	void* contents;
} P_MEMENTRY;

typedef struct
{
	bool used;
	size_t line, size;
	char filename[PLEX_LIMIT_MEMREPORTFILENAME];
} P_MEMREPORTLINE;

// static values ------------------------------------------------------------------------------------------------------------

static PLEX_PROTOEXPANDARRAY* p_contents = NULL;
static PLEX_PROTOEXPANDARRAY* p_reuse = NULL;
static PLEX_PROTOEXPANDARRAY* p_memReportLines = NULL;

static bool p_running = false;

static uint64_t p_totalAlloc = 0;
static uint64_t p_totalDealloc = 0;

static uint64_t p_currentAlloc = 0;
static uint64_t p_peakAlloc = 0;

static bool p_memReport = true; // < defaults to true
static FILE* p_memReportFile = NULL;
static char* p_memReportFileLoc = NULL;

// static functions ---------------------------------------------------------------------------------------------------------

// the internal allocation function

void* p_suballoc(const size_t size, const size_t errorline, const char* const errorfile)
{
	void* const ret = malloc(size);

	if(ret == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_MEM, PLEX_ERROR_ALLOCFAIL, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_MEM_ONSUBALLOC, PLEX_ERRORMESS_MEM_ALLOCED, errorline, errorfile);
		return NULL;
	}

	memset(ret, 0, size);

	return ret;
}

// the internal deallocation function. Even though this is a static function it still does null checks.

void p_subdealloc(void** target, const size_t errorline, const char* const errorfile)
{
	void* targetPtr = NULL;

	if(target == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_MEM, PLEX_ERROR_FREENULLPTR, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_MEM_ONSUBDEALLOC, PLEX_ERRORMESS_MEM_ALLOCEDPOINTER, errorline, errorfile);
		return;
	}

	targetPtr = *target;

	if(targetPtr == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_MEM, PLEX_ERROR_FREENULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_MEM_ONSUBDEALLOC, PLEX_ERRORMESS_MEM_ALLOCED, errorline, errorfile);
		return;
	}

	free(targetPtr);

	*target = NULL;
}

// prints a string to the mem report file

static void p_printMemReportString(const char* const toPrint, const size_t errorline, const char* const errorfile)
{
	printf("%s", toPrint);

	if(p_memReportFile != NULL)
	{
		int32_t check = fprintf(p_memReportFile, "%s", toPrint);

		if(check < 0)
		{
			PLEX_errorInt(PLEX_ERROR_CATEGORY_MEM, PLEX_ERROR_FILESAVE, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_MEM_ONPRINTREPORTSTRING, PLEX_ERRORMESS_GENERIC_LINE, errorline, errorfile);
		}
	}
}

// prints a size_t to the memory report file

static void p_printMemReportSizeT(const size_t toPrint, const size_t errorline, const char* const errorfile)
{
	printf("%zu", toPrint);

	if(p_memReportFile != NULL)
	{
		int32_t check = fprintf(p_memReportFile, "%zu", toPrint);

		if(check < 0)
		{
			PLEX_errorInt(PLEX_ERROR_CATEGORY_MEM, PLEX_ERROR_FILESAVE, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_MEM_ONPRINTREPORTNUMSTRING, PLEX_ERRORMESS_GENERIC_NUMBER, errorline, errorfile);
		}
	}
}

// prints the memory report (happens if enabled in defaults)

static void p_printPlexMemReport(const size_t errorline, const char* const errorfile)
{
	p_printMemReportString(PLEX_NL, errorline, errorfile);
	p_printMemReportString(PLEX_NL, errorline, errorfile);
	p_printMemReportString(PLEX_MEMREPORT_HEADING, errorline, errorfile);
	p_printMemReportString(PLEX_NL, errorline, errorfile);
	p_printMemReportString(PLEX_NL, errorline, errorfile);
	p_printMemReportString("\t", errorline, errorfile);
	p_printMemReportString(PLEX_MEMREPORT_PEAKMEMORY, errorline, errorfile);
	p_printMemReportString(": ", errorline, errorfile);
	p_printMemReportSizeT(p_peakAlloc, errorline, errorfile);
	p_printMemReportString(PLEX_NL, errorline, errorfile);
	p_printMemReportString(PLEX_NL, errorline, errorfile);
	p_printMemReportString("\t", errorline, errorfile);
	p_printMemReportString(PLEX_MEMREPORT_MEMALLOCTOTAL, errorline, errorfile);
	p_printMemReportString(" | ", errorline, errorfile);
	p_printMemReportSizeT(p_totalAlloc, errorline, errorfile);
	p_printMemReportString(" |", errorline, errorfile);

	p_printMemReportString(PLEX_NL, errorline, errorfile);
	p_printMemReportString("\t", errorline, errorfile);
	p_printMemReportString(PLEX_MEMREPORT_MEMDEALLOCTOTAL, errorline, errorfile);
	p_printMemReportString(" | ", errorline, errorfile);
	p_printMemReportSizeT(p_totalDealloc, errorline, errorfile);
	p_printMemReportString(" |", errorline, errorfile);

	if(p_totalAlloc != p_totalDealloc)
	{
		const size_t difference = p_totalAlloc - p_totalDealloc;

		p_printMemReportString(PLEX_NL, errorline, errorfile);
		p_printMemReportString(PLEX_NL, errorline, errorfile);
		p_printMemReportString(PLEX_MEMREPORT_ALLOCDIFF, errorline, errorfile);
		p_printMemReportString(" | ", errorline, errorfile);
		p_printMemReportSizeT(difference, errorline, errorfile);
		p_printMemReportString(" | ", errorline, errorfile);
		p_printMemReportString(PLEX_MEMREPORT_ALLOCDIFF2, errorline, errorfile);
	}else{
		p_printMemReportString(PLEX_NL, errorline, errorfile);
		p_printMemReportString(PLEX_NL, errorline, errorfile);
		p_printMemReportString(PLEX_MEMREPORT_ALLOCSAME, errorline, errorfile);
	}

	p_printMemReportString(PLEX_NL, errorline, errorfile);
	p_printMemReportString(PLEX_NL, errorline, errorfile);
	p_printMemReportString(PLEX_MEMREPORT_FOOTER, errorline, errorfile);
	p_printMemReportString(PLEX_NL, errorline, errorfile);
}

static void p_flagMemReportToFile(const size_t errorline, const char* const errorfile)
{
	uint16_t year = 0;
	uint8_t month = 0;
	uint8_t day = 0;
	uint8_t hour = 0;
	uint8_t minute = 0;
	uint8_t second = 0;

	PLEX_getErrorLogDateInt(&year, &month, &day, &hour, &minute, &second);

	p_memReportFileLoc = malloc(PATH_MAX);

	if(p_memReportFileLoc == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_MEM, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_MEM_ONINITREPORTFILE, PLEX_ERRORMESS_MEM_REPORTFILENAME, errorline, errorfile);
		return;
	}

	snprintf(p_memReportFileLoc, PLEX_LIMIT_MEMREPORTFILENAME, PLEX_ERRORCHECKDIRECTORY "memreport_%04u_%02u_%02u_%02u_%02u_%02u.txt", year, month, day, hour, minute, second);

	p_memReportFile = fopen(p_memReportFileLoc, "w+");
}

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

// specialized functions ----------------------------------------------------------------------------------------------------

void* PLEX_allocInt(const size_t size, const size_t errorline, const char* const errorfile)
{
	const size_t fullsize = size + sizeof(size_t) * 2;

	P_MEMENTRY* target = NULL;

	void* ret = NULL;

	size_t index = 0;

	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_MEM, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_MEM_ONALLOC, errorline, errorfile);
		return NULL;
	}

	if(!size)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_MEM, PLEX_ERROR_UNDERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_MEM_ONALLOC, PLEX_ERRORMESS_GENERIC_LENGTH, errorline, errorfile);
		return NULL;
	}

	if(p_contents == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_MEM, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_IMPOSSIBLE, PLEX_ERRORMESS_MEM_ONALLOC, PLEX_ERRORMESS_MEM_PREALLOCSSTACKCONTENTS, errorline, errorfile);
		return NULL;
	}

	if(p_reuse == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_MEM, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_IMPOSSIBLE, PLEX_ERRORMESS_MEM_ONALLOC, PLEX_ERRORMESS_MEM_REUSESTACK, errorline, errorfile);
		return NULL;
	}

	if(PLEX_protoExpandArrayCountInt(p_reuse, errorline, errorfile))
	{
		size_t reuseIndex = 0;

		size_t* reuseIndexPtr = PLEX_getProtoExpandArrayLastInt(p_reuse, errorline, errorfile);

		if(reuseIndexPtr == NULL)
		{
			PLEX_errorInt(PLEX_ERROR_CATEGORY_MEM, PLEX_ERROR_ACQUIRELAST, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_MEM_ONALLOC, PLEX_ERRORMESS_MEM_REUSESTACK, errorline, errorfile);
			return NULL;
		}

		reuseIndex = *reuseIndexPtr;

		target = (P_MEMENTRY*)PLEX_getProtoExpandArrayEntryInt(reuseIndex, p_contents, errorline, errorfile);

		if(target == NULL)
		{
			PLEX_errorInt(PLEX_ERROR_CATEGORY_MEM, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_MEM_ONALLOC, PLEX_ERRORMESS_MEM_REUSESTACK, errorline, errorfile);
			return NULL;
		}

		if(target->contents != NULL)
		{
			const size_t size2 = ((size_t*)target->contents)[1];

			if(size > size2 || size2 >= PLEX_getMemProfileMemReuse())
			{
				p_subdealloc((void**)&target->contents, errorline, errorfile);
				target->contents = p_suballoc(fullsize + 1, errorline, errorfile);
			}
		}else target->contents = p_suballoc(fullsize + 1, errorline, errorfile);

		((size_t*)target->contents)[0] = reuseIndex;

		PLEX_decrementProtoExpandArrayInt(p_reuse, errorline, errorfile);

		index = reuseIndex;
	}else{
		if(!PLEX_incrementProtoExpandArrayInt(p_contents, errorline, errorfile))
		{
			PLEX_errorInt(PLEX_ERROR_CATEGORY_MEM, PLEX_ERROR_INCREMENT, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_MEM_ONALLOC, PLEX_ERRORMESS_MEM_PREALLOCSSTACK, errorline, errorfile);
			return false;
		}

		target = (P_MEMENTRY*)PLEX_getProtoExpandArrayLastInt(p_contents, errorline, errorfile);

		if(target == NULL)
		{
			PLEX_errorInt(PLEX_ERROR_CATEGORY_MEM, PLEX_ERROR_ACQUIRELAST, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_MEM_ONALLOC, PLEX_ERRORMESS_MEM_PREALLOCSSTACK, errorline, errorfile);
			return NULL;
		}

		target->contents = p_suballoc(fullsize + 1, errorline, errorfile);

		index = PLEX_protoExpandArrayCountInt(p_contents, errorline, errorfile) - 1;

		((size_t*)target->contents)[0] = index;
	}

	((size_t*)target->contents)[1] = size;

	ret = (void*)((size_t*)target->contents + 2);

	memset(ret, 0, size);

	if(p_memReport)
	{
		const size_t originalCount = PLEX_protoExpandArrayCountInt(p_memReportLines, errorline, errorfile);

		P_MEMREPORTLINE* newLine = NULL;

		size_t copySize = 0;

		bool overSize = false;

		if(index >= originalCount)
		{
			if(!PLEX_multiIncrementProtoExpandArrayInt(index - originalCount + 1, p_memReportLines, errorline, errorfile))
			{
				PLEX_errorInt(PLEX_ERROR_CATEGORY_MEM, PLEX_ERROR_INCREMENT, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_MEM_ONALLOC, PLEX_ERRORMESS_MEM_REPORTSTACK, errorline, errorfile);
				return ret;
			}
		}

		newLine = PLEX_getProtoExpandArrayEntryInt(index, p_memReportLines, errorline, errorfile);

		copySize = strlen(errorfile) + 1;

		if(copySize >= PLEX_LIMIT_MEMREPORTFILENAME)
		{
			copySize = PLEX_LIMIT_MEMREPORTFILENAME - 5;
			overSize = true;

			PLEX_errorInt(PLEX_ERROR_CATEGORY_MEM, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_MEM_ONALLOC, PLEX_ERRORMESS_MEM_REPORTFILENAME, errorline, errorfile);
		}

		memcpy(newLine->filename, errorfile, copySize);

		if(overSize)
		{
			newLine->filename[PLEX_LIMIT_MEMREPORTFILENAME - 4] = '.';
			newLine->filename[PLEX_LIMIT_MEMREPORTFILENAME - 3] = '.';
			newLine->filename[PLEX_LIMIT_MEMREPORTFILENAME - 2] = '.';
			newLine->filename[PLEX_LIMIT_MEMREPORTFILENAME - 1] = '\0';
		}

		newLine->line = errorline;
		newLine->size = size;
		newLine->used = true;
	}

	p_totalAlloc += size;
	p_currentAlloc += size;

	return ret;
}

void PLEX_deallocInt(void** toFree, const size_t errorline, const char* const errorfile)
{
	size_t* reuseEntry = NULL;
	size_t reuseIndex = 0;

	size_t* sizePtr = NULL;
	size_t size = 0;

	size_t* indexPtr = NULL;
	size_t index = 0;

	void* toFreePtr = NULL;

	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_MEM, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_MEM_ONDEALLOC, errorline, errorfile);
		return;
	}

	if(toFree == NULL)
	{
		PLEX_errorInt0A(PLEX_ERROR_CATEGORY_MEM, PLEX_ERROR_FREENULLPTR, PLEX_ERROR_SEVERITY_BADSTYLE, errorline, errorfile);
		return;
	}

	toFreePtr = *toFree;
	*toFree = NULL;

	if(toFreePtr == NULL)
	{
		PLEX_errorInt0A(PLEX_ERROR_CATEGORY_MEM, PLEX_ERROR_FREENULL, PLEX_ERROR_SEVERITY_BADSTYLE, errorline, errorfile);
		return;
	}

	sizePtr = ((size_t*)toFreePtr - 1);
	size = *sizePtr;

	indexPtr = ((size_t*)toFreePtr - 2);
	index = *indexPtr;

	if(index == SIZE_MAX) // < index number is set to SIZE_MAX when deallocated
	{
		PLEX_errorInt0A(PLEX_ERROR_CATEGORY_MEM, PLEX_ERROR_DOUBLEDEALLOC, PLEX_ERROR_SEVERITY_BADSTYLE, errorline, errorfile);
		return;
	}

	reuseIndex = index;

	if(!PLEX_incrementProtoExpandArrayInt(p_reuse, errorline, errorfile))
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_MEM, PLEX_ERROR_INCREMENT, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_MEM_ONDEALLOC, PLEX_ERRORMESS_MEM_REUSESTACK, errorline, errorfile);
		return;
	}

	reuseEntry = (size_t*)PLEX_getProtoExpandArrayLastInt(p_reuse, errorline, errorfile);

	if(reuseEntry == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_MEM, PLEX_ERROR_ACQUIRELAST, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_MEM_ONDEALLOC, PLEX_ERRORMESS_MEM_REUSESTACK, errorline, errorfile);
		return;
	}

	*reuseEntry = reuseIndex;
	*indexPtr = SIZE_MAX;

	p_totalDealloc += size;
	p_currentAlloc -= size;
}

// start, update, end functions ---------------------------------------------------------------------------------------------

void PLEX_updateMemProfileInt(const size_t errorline, const char* const errorfile)
{
	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_MEM, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_MEM_ONUPDATEPROFILE, errorline, errorfile);
		return;
	}

	if(p_contents == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_MEM, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_IMPOSSIBLE, PLEX_ERRORMESS_MEM_ONUPDATEPROFILE, PLEX_ERRORMESS_MEM_PREALLOCSSTACKCONTENTS, errorline, errorfile);
		return;
	}

	if(p_reuse == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_MEM, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_IMPOSSIBLE, PLEX_ERRORMESS_MEM_ONUPDATEPROFILE, PLEX_ERRORMESS_MEM_REUSESTACK, errorline, errorfile);
	}

	PLEX_setGrowthUnitProtoExpandArrayInt(PLEX_getMemProfilePreload(), p_contents, errorline, errorfile);
	PLEX_setGrowthUnitProtoExpandArrayInt(PLEX_getMemProfilePreload(), p_reuse, errorline, errorfile);

	if(p_memReportLines != NULL) PLEX_setGrowthUnitProtoExpandArrayInt(PLEX_getMemProfilePreload(), p_memReportLines, errorline, errorfile); // NO ERROR
}

bool PLEX_startMemInt(const size_t errorline, const char* const errorfile)
{
	if(p_running)
	{
		PLEX_errorInt0A(PLEX_ERROR_CATEGORY_MEM, PLEX_ERROR_DOUBLESTART, PLEX_ERROR_SEVERITY_BADSTYLE, errorline, errorfile);
		return true;
	}

	p_contents = PLEX_genProtoExpandArrayInt(PLEX_getMemProfilePreload(), sizeof(P_MEMENTRY), p_suballoc, p_subdealloc, errorline, errorfile);

	if(p_contents == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_MEM, PLEX_ERROR_CREATE, PLEX_ERROR_SEVERITY_IMPOSSIBLE, PLEX_ERRORMESS_MEM_ONSTART, PLEX_ERRORMESS_MEM_PREALLOCSSTACK, errorline, errorfile);
		return false;
	}

	p_reuse = PLEX_genProtoExpandArrayInt(PLEX_getMemProfilePreload(), sizeof(size_t), p_suballoc, p_subdealloc, errorline, errorfile);

	if(p_reuse == NULL)
	{
		PLEX_destroyProtoExpandArrayInt(&p_contents, errorline, errorfile);

		PLEX_errorInt(PLEX_ERROR_CATEGORY_MEM, PLEX_ERROR_CREATE, PLEX_ERROR_SEVERITY_IMPOSSIBLE, PLEX_ERRORMESS_MEM_ONSTART, PLEX_ERRORMESS_MEM_REUSESTACK, errorline, errorfile);
		return false;
	}

	p_memReportLines = PLEX_genProtoExpandArrayInt(PLEX_getMemProfilePreload(), sizeof(P_MEMREPORTLINE), p_suballoc, p_subdealloc, errorline, errorfile);

	if(p_memReportLines == NULL)
	{
		// error
		return false;
	}

	p_totalAlloc = 0;
	p_totalDealloc = 0;
	p_currentAlloc = 0;
	p_peakAlloc = 0;

	p_flagMemReportToFile(errorline, errorfile);

	p_memReport = true; // < defaults to true
	p_running = true;

	return true;
}

bool PLEX_updateMemInt(const size_t errorline, const char* const errorfile)
{
	if(!p_running)
	{
		PLEX_errorInt0A(PLEX_ERROR_CATEGORY_MEM, PLEX_ERROR_UPDATEBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, errorline, errorfile);
		return false;
	}

	if(p_currentAlloc > p_peakAlloc) p_peakAlloc = p_currentAlloc;

	return true;
}

void PLEX_endMemInt(const size_t errorline, const char* const errorfile)
{
	char errPrintBuffer[PLEX_STANDNUM_MEMERRORPRINTBUFFLEN];

	if(!p_running)
	{
		PLEX_errorInt0A(PLEX_ERROR_CATEGORY_MEM, PLEX_ERROR_ENDBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, errorline, errorfile);
		return;
	}

	if(p_contents == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_MEM, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_MEM_ONEND, PLEX_ERRORMESS_MEM_PREALLOCSSTACK, errorline, errorfile);

		if(p_memReportLines != NULL) PLEX_destroyProtoExpandArrayInt(&p_memReportLines, errorline, errorfile);

		PLEX_clearProtoExpandInternalMemInt(p_memReport, p_memReportFile, errorline, errorfile); // keep second to last thing in this bracket

		if(p_memReportFile != NULL) // keep last thing in this bracket
		{
			fclose(p_memReportFile);
			p_memReportFile = NULL;
		}

		return; // < one of the rare cases an 'end' function should return
	}

	if(p_memReport)
	{
		const size_t memReportLineCount = PLEX_protoExpandArrayCountInt(p_memReportLines, errorline, errorfile);

		if(memReportLineCount)
		{
			p_printMemReportString(PLEX_NL, errorline, errorfile);
			p_printMemReportString(PLEX_NL, errorline, errorfile);
			p_printMemReportString(PLEX_MEMREPORT_HEADING_TOP, errorline, errorfile);
			p_printMemReportString(PLEX_NL, errorline, errorfile);
			p_printMemReportString(PLEX_NL, errorline, errorfile);

			size_t index = 0;

			for(size_t ze = 0; ze < memReportLineCount; ++ze)
			{
				const P_MEMREPORTLINE* const line = PLEX_getProtoExpandArrayEntryInt(ze, p_memReportLines, errorline, errorfile);

				P_MEMENTRY* target = NULL;

				if(line->used)
				{
					target = (P_MEMENTRY*)PLEX_getProtoExpandArrayEntryInt(ze, p_contents, errorline, errorfile);

					if(target == NULL)
					{
						snprintf((char*)errPrintBuffer, PLEX_STANDNUM_MEMERRORPRINTBUFFLEN, "%s %zu", PLEX_ERRORMESS_MEM_PREALLOCSSTACKENTRY, ze);

						PLEX_errorInt(PLEX_ERROR_CATEGORY_MEM, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_MEM_ONEND, (char*)errPrintBuffer, errorline, errorfile);

						continue;
					}

					index = *(size_t*)target->contents;

					if(index != SIZE_MAX)
					{
						p_printMemReportString(PLEX_NL, errorline, errorfile);
						p_printMemReportString("\t", errorline, errorfile);
						p_printMemReportString(PLEX_MEMREPORT_UNFREE1, errorline, errorfile);
						p_printMemReportSizeT(ze, errorline, errorfile);
						p_printMemReportString(PLEX_MEMREPORT_UNFREE2, errorline, errorfile);
						p_printMemReportSizeT(line->line, errorline, errorfile);
						p_printMemReportString(PLEX_MEMREPORT_UNFREE3, errorline, errorfile);
						p_printMemReportString(line->filename, errorline, errorfile);
						p_printMemReportString(PLEX_MEMREPORT_UNFREE4, errorline, errorfile);
						p_printMemReportSizeT(line->size, errorline, errorfile);
					}
				}
			}
		}
	}

	for(size_t ze = 0; ze < PLEX_protoExpandArrayCountInt(p_contents, errorline, errorfile); ++ze)
	{
		P_MEMENTRY* target = (P_MEMENTRY*)PLEX_getProtoExpandArrayEntryInt(ze, p_contents, errorline, errorfile);

		if(target == NULL)
		{
			snprintf((char*)errPrintBuffer, PLEX_STANDNUM_MEMERRORPRINTBUFFLEN, "%s %zu", PLEX_ERRORMESS_MEM_PREALLOCSSTACKENTRY, ze);

			PLEX_errorInt(PLEX_ERROR_CATEGORY_MEM, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_MEM_ONEND, (char*)errPrintBuffer, errorline, errorfile);

			continue;
		}

		if(target->contents == NULL)
		{
			snprintf((char*)errPrintBuffer, PLEX_STANDNUM_MEMERRORPRINTBUFFLEN, "%s %zu", PLEX_ERRORMESS_MEM_PREALLOCSSTACKENTRYCONTENTS, ze);

			PLEX_errorInt(PLEX_ERROR_CATEGORY_MEM, PLEX_ERROR_CONTENTCORRUPTION, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_MEM_ONEND, (char*)errPrintBuffer, errorline, errorfile);

			continue;
		}

		p_subdealloc((void**)&target->contents, errorline, errorfile);
	}

	if(p_memReport) p_printPlexMemReport(errorline, errorfile);

	PLEX_destroyProtoExpandArrayInt(&p_contents, errorline, errorfile);
	PLEX_destroyProtoExpandArrayInt(&p_reuse, errorline, errorfile);
	if(p_memReportLines != NULL) PLEX_destroyProtoExpandArrayInt(&p_memReportLines, errorline, errorfile);

	PLEX_clearProtoExpandInternalMemInt(p_memReport, p_memReportFile, errorline, errorfile); // < PUT NOTHING BUT THE CLOSING OF THE MEM REPORT FILE AFTER THIS!

	if(p_memReportFile != NULL)
	{
		fclose(p_memReportFile);
		p_memReportFile = NULL;
	}

	if(p_memReportFileLoc != NULL) free(p_memReportFileLoc);

	p_memReportFileLoc = 0;
}

// setters ------------------------------------------------------------------------------------------------------------------

void PLEX_unflagMemReportToFileInt(const size_t errorline, const char* const errorfile)
{
	if(p_memReportFile == NULL) return;

	fclose(p_memReportFile);

	remove(p_memReportFileLoc);

	free(p_memReportFileLoc);

	p_memReportFile = NULL;
	p_memReportFileLoc = NULL;
}

void PLEX_unflagMemReportInt(const size_t errorline, const char* const errorfile)
{
	if(!p_memReport) return;

	PLEX_destroyProtoExpandArrayInt(&p_memReportLines, errorline, errorfile);

	p_memReport = false;
}
