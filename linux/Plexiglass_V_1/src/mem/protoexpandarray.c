#include "mem/protoexpandarray.h"

// NOTE: global function descriptions in header.

static void** p_expandArrayMem = NULL;
static size_t p_expandMemCount = 0;
static size_t p_expandMemCapacity = 0;

static void p_freeExpandMemPtr(void* ptr, const bool report, FILE* const reportFile)
{
	char* cptr = NULL;

	if(ptr == NULL) return;

	cptr = (char*)ptr;

	if(report)
	{
		const size_t amount = *((size_t*)cptr - 1);

		size_t errorline = 0;
		const char* errorfile = NULL;

		char* cptr2 = cptr + amount;

		char errPrintBuffer[PLEX_STANDNUM_MEMERRORPRINTBUFFLEN];

		errorline = *((size_t*)cptr2);
		errorfile = (const char*)(cptr2 + sizeof(size_t) * 2);

		snprintf((char*)errPrintBuffer, PLEX_STANDNUM_MEMERRORPRINTBUFFLEN, "%s %zu %s \"%s\" %s" PLEX_NL, PLEX_MEMREPORT_EXPANDARRAY, errorline, PLEX_MEMREPORT_EXPANDARRAY2, errorfile, PLEX_MEMREPORT_EXPANDARRAY3);

		printf("%s", (char*)errPrintBuffer);

		if(reportFile != NULL) fprintf(reportFile, "%s", (char*)errPrintBuffer);
	}

	cptr -= sizeof(size_t);

	free(cptr);
}

static void p_clearExpandArrayMem(const bool report, FILE* const reportFile, const size_t errorline, const char* const errorfile)
{
	if(p_expandArrayMem == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_BADOPERATION, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_ARRAY_ONMEMCLEARING, PLEX_ERRORMESS_OP_CLEARCLEAREDPROTOTOEXPANDMEM, errorline, errorfile);
		return;
	}

	for(size_t ze = 0; ze < p_expandMemCount; ++ze)
	{
		p_freeExpandMemPtr(p_expandArrayMem[ze], report, reportFile);
		p_expandArrayMem[ze] = NULL;
	}

	free(p_expandArrayMem);

	p_expandArrayMem = NULL;
}

static void* p_expandArrayMalloc(const size_t amount, size_t* index, const size_t errorline, const char* const errorfile)
{
	const size_t errorflen = strlen(errorfile);
	const size_t adjust = sizeof(size_t) * 3 + errorflen;
	const size_t totalAmount = amount + adjust + 1; // the +1 is for the null terminator of the error file string

	size_t lindex = 0;

	char* ret = NULL; // < returns as void but must remain char*

	if(p_expandArrayMem == NULL)
	{
		p_expandArrayMem = (void**)malloc(sizeof(void*) * PLEX_getMemProfileExpandArrayCap());

		if(p_expandArrayMem == NULL)
		{
			PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_ALLOCFAIL, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_ARRAY_ONMEMEXPANSION, PLEX_ERRORMESS_ARRAY_INTERNALMEMARRAY, errorline, errorfile);
			return NULL;
		}

		p_expandMemCount = 0;
		p_expandMemCapacity = PLEX_getMemProfileExpandArrayCap();
	}

	if(p_expandMemCount >= p_expandMemCapacity)
	{
		const size_t expand = p_expandMemCount + PLEX_getMemProfileExpandArrayCap();

		const size_t totalSize = sizeof(void*) * expand;

		void** newMem = (void**)malloc(totalSize);

		if(newMem == NULL)
		{
			p_clearExpandArrayMem(false, NULL, errorline, errorfile);
			PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_ALLOCFAIL, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_ARRAY_ONMEMEXPANSION, PLEX_ERRORMESS_ARRAY_INTERNALMEMEXPANDPOINTER, errorline, errorfile);
			return NULL;
		}

		memset(newMem, 0, totalSize);

		for(size_t ze = 0; ze < p_expandMemCount; ++ze)
		{
			newMem[ze] = p_expandArrayMem[ze];
			p_expandArrayMem[ze] = NULL;
		}

		free(p_expandArrayMem);

		p_expandArrayMem = newMem;

		p_expandMemCapacity = expand;
	}

	ret = malloc(totalAmount);

	if(ret == NULL)
	{
		p_clearExpandArrayMem(false, NULL, errorline, errorfile);
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_ALLOCFAIL, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_ARRAY_ONMEMEXPANSION, PLEX_ERRORMESS_ARRAY_INTERNALMEMPOINTER, errorline, errorfile);
		return NULL;
	}

	memset(ret, 0, totalAmount);

	// puts the amount as a size_t before the return data

	memcpy(ret, (const void*)&amount, sizeof(size_t));

	// puts the error line, error file len, and error file string after the data

	memcpy(ret + amount + sizeof(size_t), (const void*)&errorline, sizeof(size_t));
	memcpy(ret + amount + sizeof(size_t) * 2, (const void*)&errorflen, sizeof(size_t));
	memcpy(ret + amount + sizeof(size_t) * 3, (const void*)errorfile, errorflen);

	lindex = p_expandMemCount;

	for(size_t ze = 0; ze < p_expandMemCount; ++ze)
	{
		if(p_expandArrayMem[ze] == NULL)
		{
			lindex = ze;
			break;
		}
	}

	p_expandArrayMem[lindex] = (void*)(ret + sizeof(size_t));

	*index = lindex;

	if(lindex == p_expandMemCount) ++p_expandMemCount;

	return p_expandArrayMem[lindex];
}

static void p_expandArrayFree(const size_t memTicket, const size_t errorline, const char* const errorfile)
{
	if(p_expandArrayMem == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_FREENULL, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_ARRAY_ONMEMFREE, PLEX_ERRORMESS_ARRAY_INTERNALMEMARRAY, errorline, errorfile);
		return;
	}

	p_freeExpandMemPtr(p_expandArrayMem[memTicket], false, NULL);
	p_expandArrayMem[memTicket] = NULL;
}

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

// specialized functions ----------------------------------------------------------------------------------------------------

PLEX_PROTOEXPANDARRAY* PLEX_genProtoExpandArrayInt(const size_t growthUnit, const size_t unitSize, PLEX_F_MEMHOOK memHook, PLEX_F_FREEHOOK freeHook, const size_t errorline, const char* const errorfile)
{
	const size_t size = growthUnit * unitSize;

	PLEX_PROTOEXPANDARRAY* ret = NULL;

	size_t memTicket = 0;

	if(memHook == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MAJOR, PLEX_ERRORMESS_ARRAY_ONCREATE, PLEX_ERRORMESS_ARRAY_MEMHOOK, errorline, errorfile);
		return NULL;
	}

	if(freeHook == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MAJOR, PLEX_ERRORMESS_ARRAY_ONCREATE, PLEX_ERRORMESS_ARRAY_FREEHOOK, errorline, errorfile);
		return NULL;
	}

	if(!growthUnit)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_ZEROVALUE, PLEX_ERROR_SEVERITY_MAJOR, PLEX_ERRORMESS_ARRAY_ONCREATE, PLEX_ERRORMESS_ARRAY_ARRAYGROWTHUNIT, errorline, errorfile);
		return NULL;
	}

	if(!unitSize)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_ZEROVALUE, PLEX_ERROR_SEVERITY_MAJOR, PLEX_ERRORMESS_ARRAY_ONCREATE, PLEX_ERRORMESS_ARRAY_ARRAYUNITSIZE, errorline, errorfile);
		return NULL;
	}

	ret = p_expandArrayMalloc(sizeof(PLEX_PROTOEXPANDARRAY), &memTicket, errorline, errorfile);

	if(ret == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_ALLOCFAIL, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_ARRAY_ONCREATE, PLEX_ERRORMESS_ARRAY_ARRAY, errorline, errorfile);
		return NULL;
	}

	ret->count = 0;
	ret->capacity = growthUnit;
	ret->growthUnit = growthUnit;
	ret->unitSize = unitSize;
	ret->memTicket = memTicket;

	ret->contents = (char*)memHook(size, errorline, errorfile);
	ret->memHook = memHook;
	ret->freeHook = freeHook;

	if(ret->contents == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_ALLOCFAIL, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_ARRAY_ONCREATE, PLEX_ERRORMESS_ARRAY_ARRAYCONTENTS, errorline, errorfile);
		p_expandArrayFree(ret->memTicket, errorline, errorfile);

		return NULL;
	}

	return ret;
}

void PLEX_destroyProtoExpandArrayInt(PLEX_PROTOEXPANDARRAY** expandArray, const size_t errorline, const char* const errorfile)
{
	PLEX_PROTOEXPANDARRAY* ptr = NULL;

	if(expandArray == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_FREENULLPTR, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_ARRAY_ONDESTROY, PLEX_ERRORMESS_ARRAY_ARRAY, errorline, errorfile);
		return;
	}

	ptr = *expandArray;

	if(ptr == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_FREENULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_ARRAY_ONDESTROY, PLEX_ERRORMESS_ARRAY_ARRAYPTR, errorline, errorfile);
		return;
	}

	if(ptr->contents == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_CONTENTCORRUPTION, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_ARRAY_ONDESTROY, PLEX_ERRORMESS_ARRAY_ONDESTROY, errorline, errorfile);
		return;
	}

	if(ptr->freeHook == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_HOOKCORRUPTION, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_ARRAY_ONDESTROY, PLEX_ERRORMESS_ARRAY_ARRAYFREEHOOK, errorline, errorfile);
		return;
	}

	ptr->freeHook((void**)&ptr->contents, errorline, errorfile);

	p_expandArrayFree(ptr->memTicket, errorline, errorfile);

	*expandArray = NULL;
}

bool PLEX_expandProtoExpandArrayInt(const size_t capacity, PLEX_PROTOEXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile)
{
	size_t newCapacity = 0;
	size_t oldCapacity = 0;

	size_t oldSize = 0;
	size_t newSize = 0;

	void* oldContents = NULL;

	if(expandArray == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_EXPANDNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_ARRAY_ONDESTROY, PLEX_ERRORMESS_ARRAY_ONEXPANSION, errorline, errorfile);
		return false;
	}

	if(expandArray->contents == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_CONTENTCORRUPTION, PLEX_ERROR_SEVERITY_IMPOSSIBLE, PLEX_ERRORMESS_ARRAY_ONEXPANSION, PLEX_ERRORMESS_ARRAY_ONEXPANSION, errorline, errorfile);
		return false;
	}

	if(expandArray->memHook == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_HOOKCORRUPTION, PLEX_ERROR_SEVERITY_IMPOSSIBLE, PLEX_ERRORMESS_ARRAY_ONEXPANSION, PLEX_ERRORMESS_ARRAY_MEMHOOK, errorline, errorfile);
		return false;
	}

	if(expandArray->freeHook == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_HOOKCORRUPTION, PLEX_ERROR_SEVERITY_IMPOSSIBLE, PLEX_ERRORMESS_ARRAY_ONEXPANSION, PLEX_ERRORMESS_ARRAY_FREEHOOK, errorline, errorfile);
		return false;
	}

	if(capacity >= expandArray->capacity)
	{
		oldCapacity = expandArray->capacity;
		newCapacity = capacity + expandArray->growthUnit;

		oldSize = oldCapacity * expandArray->unitSize;
		newSize = newCapacity * expandArray->unitSize;

		oldContents = expandArray->contents;

		expandArray->contents = expandArray->memHook(newSize, errorline, errorfile);

		if(expandArray->contents == NULL)
		{
			PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_ALLOCFAIL, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_ARRAY_ONEXPANSION, PLEX_ERRORMESS_ARRAY_NEWARRAYCONTENTS, errorline, errorfile);

			expandArray->contents = oldContents;
			return false;
		}

		memcpy(expandArray->contents, oldContents, oldSize);

		expandArray->freeHook((void**)&oldContents, errorline, errorfile);

		expandArray->capacity = newCapacity;
	}

	return true;
}

bool PLEX_incrementProtoExpandArrayInt(PLEX_PROTOEXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile)
{
	if(expandArray == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_ARRAY_ONINCREMENTATION, PLEX_ERRORMESS_ARRAY_ARRAY, errorline, errorfile);
		return false;
	}

	if(expandArray->contents == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_CONTENTCORRUPTION, PLEX_ERROR_SEVERITY_IMPOSSIBLE, PLEX_ERRORMESS_ARRAY_ONINCREMENTATION, PLEX_ERRORMESS_ARRAY_ARRAYCONTENTS, errorline, errorfile);
		return false;
	}

	return PLEX_multiIncrementProtoExpandArrayInt(1, expandArray, errorline, errorfile);
}

bool PLEX_multiIncrementProtoExpandArrayInt(const size_t by, PLEX_PROTOEXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile)
{
	if(expandArray == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_EXPANDNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_ARRAY_ONMULTIINCREMENTATION, PLEX_ERRORMESS_ARRAY_ARRAY, errorline, errorfile);
		return false;
	}

	if(expandArray->contents == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_CONTENTCORRUPTION, PLEX_ERROR_SEVERITY_IMPOSSIBLE, PLEX_ERRORMESS_ARRAY_ONMULTIINCREMENTATION, PLEX_ERRORMESS_ARRAY_ARRAYCONTENTS, errorline, errorfile);
		return false;
	}

	if(!PLEX_expandProtoExpandArrayInt(expandArray->count + by, expandArray, errorline, errorfile))
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_EXPAND, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_ARRAY_ONMULTIINCREMENTATION, PLEX_ERRORMESS_ARRAY_ARRAYCONTENTS, errorline, errorfile);
		return false;
	}

	expandArray->count += by;

	return true;
}

bool PLEX_decrementProtoExpandArrayInt(PLEX_PROTOEXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile)
{
	if(expandArray == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_ARRAY_ONDECREMENTATION, PLEX_ERRORMESS_ARRAY_ARRAY, errorline, errorfile);
		return false;
	}

	if(expandArray->contents == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_CONTENTCORRUPTION, PLEX_ERROR_SEVERITY_IMPOSSIBLE, PLEX_ERRORMESS_ARRAY_ONDECREMENTATION, PLEX_ERRORMESS_ARRAY_ARRAYCONTENTS, errorline, errorfile);
		return false;
	}

	if(!expandArray->count)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_ZEROVALUE, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_ARRAY_ONDECREMENTATION, PLEX_ERRORMESS_ARRAY_ARRAYCOUNT, errorline, errorfile);
		return false;
	}

	--expandArray->count;
	return true;
}

bool PLEX_removeProtoExpandArrayInt(const size_t index, PLEX_PROTOEXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile)
{
	if(expandArray == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_ARRAY_ONREMOVAL, PLEX_ERRORMESS_ARRAY_ARRAY, errorline, errorfile);
		return false;
	}

	if(expandArray->contents == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_CONTENTCORRUPTION, PLEX_ERROR_SEVERITY_IMPOSSIBLE, PLEX_ERRORMESS_ARRAY_ONREMOVAL, PLEX_ERRORMESS_ARRAY_ARRAYCONTENTS, errorline, errorfile);
		return false;
	}

	if(index >= expandArray->count)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_ARRAY_ONREMOVAL, PLEX_ERRORMESS_ARRAY_ARRAYCOUNT, errorline, errorfile);
		return false;
	}

	if(index == expandArray->count - 1) return PLEX_decrementProtoExpandArrayInt(expandArray, errorline, errorfile);

	memmove(expandArray->contents + (index * expandArray->unitSize), expandArray->contents + ((index + 1) * expandArray->unitSize), expandArray->unitSize * (expandArray->count - index - 1));

	--expandArray->count;

	return true;
}

void PLEX_clearCountProtoExpandArrayInt(PLEX_PROTOEXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile)
{
	size_t size = 0;

	if(expandArray == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_ARRAY_ONCLEARING, PLEX_ERRORMESS_ARRAY_ARRAY, errorline, errorfile);
		return;
	}

	if(expandArray->contents == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_CONTENTCORRUPTION, PLEX_ERROR_SEVERITY_IMPOSSIBLE, PLEX_ERRORMESS_ARRAY_ONCLEARING, PLEX_ERRORMESS_ARRAY_ARRAYCONTENTS, errorline, errorfile);
		return;
	}

	if(!expandArray->count) return; // < no need for an error here

	size = expandArray->capacity * expandArray->unitSize;

	memset(expandArray->contents, 0, size);

	expandArray->count = 0;
}

bool PLEX_rearrangeProtoExpandArrayInt(const size_t beg, const size_t beg2, const size_t len, PLEX_PROTOEXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile)
{
	size_t alen = len;

	size_t fbeg = 0;
	size_t fbeg2 = 0;
	size_t flen = 0;

	void* buffer = NULL;

	if(expandArray == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_ARRAY_ONREARRANGING, PLEX_ERRORMESS_ARRAY_ARRAY, errorline, errorfile);
		return false;
	}

	if(expandArray->contents == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_CONTENTCORRUPTION, PLEX_ERROR_SEVERITY_IMPOSSIBLE, PLEX_ERRORMESS_ARRAY_ONREARRANGING, PLEX_ERRORMESS_ARRAY_ARRAYCONTENTS, errorline, errorfile);
		return false;
	}

	if(beg >= expandArray->count - 1)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_ARRAY_ONREARRANGING, PLEX_ERRORMESS_ARRAY_ARRAYBEG1, errorline, errorfile);
		return false;
	}

	if(beg2 >= expandArray->count - 1)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_ARRAY_ONREARRANGING, PLEX_ERRORMESS_ARRAY_ARRAYBEG2, errorline, errorfile);
		return false;
	}

	if(!len)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_ZEROVALUE, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_ARRAY_ONREARRANGING, PLEX_ERRORMESS_GENERIC_LENGTH, errorline, errorfile);
		return false;
	}

	if(expandArray->memHook == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_HOOKCORRUPTION, PLEX_ERROR_SEVERITY_IMPOSSIBLE, PLEX_ERRORMESS_ARRAY_ONREARRANGING, PLEX_ERRORMESS_ARRAY_ARRAYMEMHOOK, errorline, errorfile);
		return false;
	}

	if(expandArray->freeHook == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_HOOKCORRUPTION, PLEX_ERROR_SEVERITY_IMPOSSIBLE, PLEX_ERRORMESS_ARRAY_ONREARRANGING, PLEX_ERRORMESS_ARRAY_ARRAYFREEHOOK, errorline, errorfile);
		return false;
	}

	if(beg > beg2)
	{
		if(beg + alen > expandArray->count - 1) alen = expandArray->count - beg - 1;
	}else{
		if(beg2 + alen > expandArray->count - 1) alen = expandArray->count - beg2 - 1;
	}

	fbeg = beg * expandArray->unitSize;
	fbeg2 = beg2 * expandArray->unitSize;
	flen = alen * expandArray->unitSize;

	buffer = expandArray->memHook(flen, errorline, errorfile);

	if(buffer == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_ALLOCFAIL, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_ARRAY_ONREARRANGING, PLEX_ERRORMESS_ARRAY_NEWBUFFER, errorline, errorfile);
		return false;
	}

	memcpy(buffer, expandArray->contents + fbeg, flen);
	memmove(expandArray->contents + fbeg, expandArray->contents + fbeg2, flen);
	memcpy(expandArray->contents + fbeg2, buffer, flen);

	expandArray->freeHook((void**)&buffer, errorline, errorfile);

	return true;
}

bool PLEX_swapProtoExpandArrayInt(const size_t beg, const size_t beg2, const size_t len, PLEX_PROTOEXPANDARRAY* expandArray, PLEX_PROTOEXPANDARRAY* expandArray2, const size_t errorline, const char* const errorfile)
{
	size_t alen = len;

	size_t flen = 0;
	size_t flen2 = 0;

	size_t fbeg = 0;
	size_t fbeg2 = 0;

	void* buffer = NULL;
	void* buffer2 = NULL;

	if(expandArray == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_ARRAY_ONSWAPPING, PLEX_ERRORMESS_ARRAY_ARRAY, errorline, errorfile);
		return false;
	}

	if(expandArray2 == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_ARRAY_ONSWAPPING, PLEX_ERRORMESS_ARRAY_ARRAY2, errorline, errorfile);
		return false;
	}

	if(expandArray->contents == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_CONTENTCORRUPTION, PLEX_ERROR_SEVERITY_IMPOSSIBLE, PLEX_ERRORMESS_ARRAY_ONSWAPPING, PLEX_ERRORMESS_ARRAY_ARRAYCONTENTS, errorline, errorfile);
		return false;
	}

	if(expandArray2->contents == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_CONTENTCORRUPTION, PLEX_ERROR_SEVERITY_IMPOSSIBLE, PLEX_ERRORMESS_ARRAY_ONSWAPPING, PLEX_ERRORMESS_ARRAY_ARRAYCONTENTS2, errorline, errorfile);
		return false;
	}

	if(!len)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_ZEROVALUE, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_ARRAY_ONSWAPPING, PLEX_ERRORMESS_GENERIC_LENGTH, errorline, errorfile);
		return false;
	}

	if(beg >= expandArray->count - 1)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_ARRAY_ONSWAPPING, PLEX_ERRORMESS_ARRAY_ARRAYBEG1, errorline, errorfile);
		return false;
	}

	if(beg >= expandArray2->count - 1)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_ARRAY_ONSWAPPING2, PLEX_ERRORMESS_ARRAY_ARRAYBEG1, errorline, errorfile);
		return false;
	}

	if(beg2 >= expandArray->count - 1)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_ARRAY_ONSWAPPING, PLEX_ERRORMESS_ARRAY_ARRAYBEG2, errorline, errorfile);
		return false;
	}

	if(beg2 >= expandArray2->count - 1)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_ARRAY_ONSWAPPING2, PLEX_ERRORMESS_ARRAY_ARRAYBEG2, errorline, errorfile);
		return false;
	}

	if(expandArray->memHook == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_HOOKCORRUPTION, PLEX_ERROR_SEVERITY_IMPOSSIBLE, PLEX_ERRORMESS_ARRAY_ONSWAPPING, PLEX_ERRORMESS_ARRAY_ARRAYMEMHOOK, errorline, errorfile);
		return false;
	}

	if(expandArray->freeHook == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_HOOKCORRUPTION, PLEX_ERROR_SEVERITY_IMPOSSIBLE, PLEX_ERRORMESS_ARRAY_ONSWAPPING, PLEX_ERRORMESS_ARRAY_ARRAYFREEHOOK, errorline, errorfile);
		return false;
	}

	if(expandArray->contents == expandArray2->contents) // < not an error
	{
		PLEX_rearrangeProtoExpandArrayInt(beg, beg2, len, expandArray, errorline, errorfile);
		return false;
	}

	if(beg + alen > expandArray->count - 1) alen = expandArray->count - beg - 1;
	if(beg2 + alen > expandArray->count - 1) alen = expandArray->count - beg2 - 1;
	if(beg + alen > expandArray2->count - 1) alen = expandArray2->count - beg - 1;
	if(beg2 + alen > expandArray2->count - 1) alen = expandArray2->count - beg2 - 1;

	flen = alen * expandArray->unitSize;
	flen2 = alen * expandArray2->unitSize;

	fbeg = beg * expandArray->unitSize;
	fbeg2 = beg2 * expandArray2->unitSize;

	buffer = expandArray->memHook(flen, errorline, errorfile);

	if(buffer == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_ALLOCFAIL, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_ARRAY_ONSWAPPING, PLEX_ERRORMESS_ARRAY_ARRAYBUFFER, errorline, errorfile);
		return false;
	}

	buffer2 = expandArray2->memHook(flen2, errorline, errorfile);

	if(buffer2 == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_ALLOCFAIL, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_ARRAY_ONSWAPPING, PLEX_ERRORMESS_ARRAY_ARRAYBUFFER2, errorline, errorfile);
		expandArray->freeHook((void**)&buffer, errorline, errorfile);
		return false;
	}

	memcpy(buffer, expandArray->contents + fbeg, flen);
	memcpy(buffer2, expandArray2->contents + fbeg2, flen2);

	if(flen2 > flen)
	{
		memcpy(expandArray->contents + fbeg, buffer2, flen);
		memcpy(expandArray2->contents + fbeg2, buffer, flen);
	}else{
		memcpy(expandArray->contents + fbeg, buffer2, flen2);
		memcpy(expandArray2->contents + fbeg2, buffer, flen2);
	}

	expandArray->freeHook((void**)&buffer, errorline, errorfile);
	expandArray->freeHook((void**)&buffer2, errorline, errorfile);

	return true;
}

bool PLEX_cutProtoExpandArrayInt(const size_t beg, const size_t len, PLEX_PROTOEXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile)
{
	size_t alen = len;

	size_t fbeg = 0;
	size_t flen = 0;
	size_t flen2 = 0;

	if(expandArray == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_ARRAY_ONCUTTING, PLEX_ERRORMESS_ARRAY_ARRAY, errorline, errorfile);
		return false;
	}

	if(expandArray->contents == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_CONTENTCORRUPTION, PLEX_ERROR_SEVERITY_IMPOSSIBLE, PLEX_ERRORMESS_ARRAY_ONCUTTING, PLEX_ERRORMESS_ARRAY_ARRAYCONTENTS, errorline, errorfile);
		return false;
	}

	if(!alen)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_ZEROVALUE, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_ARRAY_ONCUTTING, PLEX_ERRORMESS_GENERIC_LENGTH, errorline, errorfile);
		return false;
	}

	if(beg >= expandArray->count - 1)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_ARRAY_ONCUTTING, PLEX_ERRORMESS_ARRAY_ARRAYBEG1, errorline, errorfile);
		return false;
	}

	if(beg + alen >= expandArray->count) alen = expandArray->count - beg - 1;

	fbeg = beg * expandArray->unitSize;
	flen = alen * expandArray->unitSize;
	flen2 = (expandArray->count - (beg + alen)) * expandArray->unitSize;

	memmove(expandArray->contents + fbeg, expandArray->contents + fbeg + flen, flen2);

	if(alen + 1 < expandArray->count) expandArray->count -= alen + 1;
	else expandArray->count = 0;

	return true;
}

bool PLEX_reverseProtoExpandArrayInt(const size_t beg, const size_t len, PLEX_PROTOEXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile)
{
	size_t alen = 0;
	size_t count = 0;

	size_t fbeg = 0;
	size_t flen = 0;

	char* buffer = NULL;

	if(expandArray == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_ARRAY_ONREVERSING, PLEX_ERRORMESS_ARRAY_ARRAY, errorline, errorfile);
		return false;
	}

	if(expandArray->contents == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_CONTENTCORRUPTION, PLEX_ERROR_SEVERITY_IMPOSSIBLE, PLEX_ERRORMESS_ARRAY_ONREVERSING, PLEX_ERRORMESS_ARRAY_ARRAYCONTENTS, errorline, errorfile);
		return false;
	}

	if(beg >= expandArray->count - 1)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_ARRAY_ONREVERSING, PLEX_ERRORMESS_ARRAY_ARRAYBEG1, errorline, errorfile);
		return false;
	}

	if(!len)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_ZEROVALUE, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_ARRAY_ONREVERSING, PLEX_ERRORMESS_GENERIC_LENGTH, errorline, errorfile);
		return false;
	}

	if(expandArray->memHook == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_HOOKCORRUPTION, PLEX_ERROR_SEVERITY_IMPOSSIBLE, PLEX_ERRORMESS_ARRAY_ONREVERSING, PLEX_ERRORMESS_ARRAY_ARRAYMEMHOOK, errorline, errorfile);
		return false;
	}

	if(expandArray->freeHook == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_HOOKCORRUPTION, PLEX_ERROR_SEVERITY_IMPOSSIBLE, PLEX_ERRORMESS_ARRAY_ONREVERSING, PLEX_ERRORMESS_ARRAY_ARRAYFREEHOOK, errorline, errorfile);
		return false;
	}

	if(beg + alen > expandArray->count - 1) alen = expandArray->count - beg - 1;

	fbeg = beg * expandArray->unitSize;
	flen = alen * expandArray->unitSize;

	buffer = expandArray->memHook(flen, errorline, errorfile);

	if(buffer == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_ALLOCFAIL, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_ARRAY_ONREVERSING, PLEX_ERRORMESS_ARRAY_ARRAYBUFFER, errorline, errorfile);
		return false;
	}

	memcpy(buffer, expandArray->contents + fbeg, flen);

	count = beg + alen;

	for(size_t ze = beg; ze < count; ++ze)
	{
		const size_t it = ze - beg;
		const size_t last = count - ze;

		const size_t fit = it * expandArray->unitSize;
		const size_t flast = last * expandArray->unitSize;

		memcpy((char*)expandArray->contents + flast, buffer + fit, expandArray->unitSize);
	}

	expandArray->freeHook((void**)&buffer, errorline, errorfile);

	return true;
}

bool PLEX_rearrangeProtoExpandArrayPercInt(const double begPerc, const double begPerc2, const double lenPerc, PLEX_PROTOEXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile)
{
	size_t count = 0;

	double aBegPerc = begPerc;
	double aBegPerc2 = begPerc2;

	double aLenPerc = lenPerc;

	if(expandArray == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_ARRAY_ONREARRANGINGPERC, PLEX_ERRORMESS_ARRAY_ARRAY, errorline, errorfile);
		return false;
	}

	if(expandArray->contents == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_CONTENTCORRUPTION, PLEX_ERROR_SEVERITY_IMPOSSIBLE, PLEX_ERRORMESS_ARRAY_ONREARRANGINGPERC, PLEX_ERRORMESS_ARRAY_ARRAYCONTENTS, errorline, errorfile);
		return false;
	}

	if(begPerc >= 1.0)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_ARRAY_ONREARRANGINGPERC, PLEX_ERRORMESS_ARRAY_ARRAYBEG1, errorline, errorfile);
		return false;
	}

	if(begPerc2 >= 1.0)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_ARRAY_ONREARRANGINGPERC, PLEX_ERRORMESS_ARRAY_ARRAYBEG2, errorline, errorfile);
		return false;
	}

	if(begPerc <= 0)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_UNDERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_ARRAY_ONREARRANGINGPERC, PLEX_ERRORMESS_ARRAY_ARRAYBEG1, errorline, errorfile);
		aBegPerc = 0;
	}

	if(begPerc2 <= 0)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_UNDERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_ARRAY_ONREARRANGINGPERC, PLEX_ERRORMESS_ARRAY_ARRAYBEG2, errorline, errorfile);
		aBegPerc2 = 0;
	}

	if(lenPerc <= 0)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_UNDERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_ARRAY_ONREARRANGINGPERC, PLEX_ERRORMESS_GENERIC_LENGTH, errorline, errorfile);
		return false;
	}

	if(lenPerc >= 1.0)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_ARRAY_ONREARRANGINGPERC, PLEX_ERRORMESS_GENERIC_LENGTH, errorline, errorfile);
		aLenPerc = 1;
	}

	count = expandArray->count;

	PLEX_rearrangeProtoExpandArrayInt(aBegPerc * count, aBegPerc2 * count, aLenPerc * count, expandArray, errorline, errorfile);

	return true;
}

bool PLEX_swapProtoExpandArrayPercInt(const double begPerc, const double begPerc2, const double lenPerc, PLEX_PROTOEXPANDARRAY* expandArray, PLEX_PROTOEXPANDARRAY* expandArray2, const size_t errorline, const char* const errorfile)
{
	size_t count = 0;

	double aBegPerc = begPerc;
	double aBegPerc2 = begPerc2;

	double aLenPerc = lenPerc;

	if(expandArray == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_ARRAY_ONSWAPPINGPERC, PLEX_ERRORMESS_ARRAY_ARRAY, errorline, errorfile);
		return false;
	}

	if(expandArray->contents == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_CONTENTCORRUPTION, PLEX_ERROR_SEVERITY_IMPOSSIBLE, PLEX_ERRORMESS_ARRAY_ONSWAPPINGPERC, PLEX_ERRORMESS_ARRAY_ARRAYCONTENTS, errorline, errorfile);
		return false;
	}

	if(expandArray2 == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_ARRAY_ONSWAPPINGPERC, PLEX_ERRORMESS_ARRAY_ARRAY2, errorline, errorfile);
		return false;
	}

	if(expandArray2->contents == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_CONTENTCORRUPTION, PLEX_ERROR_SEVERITY_IMPOSSIBLE, PLEX_ERRORMESS_ARRAY_ONSWAPPINGPERC, PLEX_ERRORMESS_ARRAY_ARRAYCONTENTS2, errorline, errorfile);
		return false;
	}

	if(begPerc >= 1.0)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_ARRAY_ONSWAPPINGPERC, PLEX_ERRORMESS_ARRAY_ARRAYBEG1, errorline, errorfile);
		return false;
	}

	if(begPerc2 >= 1.0)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_ARRAY_ONSWAPPINGPERC, PLEX_ERRORMESS_ARRAY_ARRAYBEG2, errorline, errorfile);
		return false;
	}

	if(lenPerc <= 0)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_UNDERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_ARRAY_ONSWAPPINGPERC, PLEX_ERRORMESS_GENERIC_LENGTH, errorline, errorfile);
		return false;
	}

	if(begPerc <= 0)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_UNDERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_ARRAY_ONSWAPPINGPERC, PLEX_ERRORMESS_ARRAY_ARRAYBEG1, errorline, errorfile);
		aBegPerc = 0;
	}

	if(begPerc2 <= 0)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_UNDERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_ARRAY_ONSWAPPINGPERC, PLEX_ERRORMESS_ARRAY_ARRAYBEG2, errorline, errorfile);
		aBegPerc2 = 0;
	}

	if(lenPerc >= 1.0)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_ARRAY_ONSWAPPINGPERC, PLEX_ERRORMESS_GENERIC_LENGTH, errorline, errorfile);
		aLenPerc = 1;
	}

	count = expandArray->count;

	PLEX_swapProtoExpandArrayInt(aBegPerc * count, aBegPerc2 * count, aLenPerc * count, expandArray, expandArray2, errorline, errorfile);

	return true;
}

bool PLEX_cutProtoExpandArrayPercInt(const double begPerc, const double lenPerc, PLEX_PROTOEXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile)
{
	size_t count = 0;

	double aBegPerc = begPerc;

	double aLenPerc = lenPerc;

	if(expandArray == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_ARRAY_ONCUTTINGPERC, PLEX_ERRORMESS_ARRAY_ARRAY, errorline, errorfile);
		return false;
	}

	if(expandArray->contents == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_CONTENTCORRUPTION, PLEX_ERROR_SEVERITY_IMPOSSIBLE, PLEX_ERRORMESS_ARRAY_ONCUTTINGPERC, PLEX_ERRORMESS_ARRAY_ARRAYCONTENTS, errorline, errorfile);
		return false;
	}

	if(begPerc <= 0)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_UNDERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_ARRAY_ONCUTTINGPERC, PLEX_ERRORMESS_ARRAY_ARRAYBEG1, errorline, errorfile);
		aBegPerc = 0;
	}

	if(begPerc >= 1.0)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_ARRAY_ONCUTTINGPERC, PLEX_ERRORMESS_ARRAY_ARRAYBEG1, errorline, errorfile);
		return false;
	}

	if(lenPerc <= 0)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_UNDERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_ARRAY_ONCUTTINGPERC, PLEX_ERRORMESS_GENERIC_LENGTH, errorline, errorfile);
		return false;
	}

	if(lenPerc >= 1.0)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_ARRAY_ONCUTTINGPERC, PLEX_ERRORMESS_GENERIC_LENGTH, errorline, errorfile);
		aLenPerc = 1;
	}

	count = expandArray->count;

	PLEX_cutProtoExpandArrayInt(aBegPerc * count, aLenPerc * count, expandArray, errorline, errorfile);

	return true;
}

bool PLEX_reverseProtoExpandArrayPercInt(const double begPerc, const double lenPerc, PLEX_PROTOEXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile)
{
	size_t count = 0;

	double aBegPerc = begPerc;
	double aLenPerc = lenPerc;

	if(expandArray == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_ARRAY_ONREVERSINGPERC, PLEX_ERRORMESS_ARRAY_ARRAY, errorline, errorfile);
		return false;
	}

	if(expandArray->contents == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_CONTENTCORRUPTION, PLEX_ERROR_SEVERITY_IMPOSSIBLE, PLEX_ERRORMESS_ARRAY_ONREVERSINGPERC, PLEX_ERRORMESS_ARRAY_ARRAYCONTENTS, errorline, errorfile);
		return false;
	}

	if(begPerc <= 0)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_UNDERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_ARRAY_ONREVERSINGPERC, PLEX_ERRORMESS_ARRAY_ARRAYBEG1, errorline, errorfile);
		aBegPerc = 0;
	}

	if(begPerc >= 1.0)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_ARRAY_ONREVERSINGPERC, PLEX_ERRORMESS_ARRAY_ARRAYBEG1, errorline, errorfile);
		return false;
	}

	if(lenPerc <= 0)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_UNDERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_ARRAY_ONREVERSINGPERC, PLEX_ERRORMESS_GENERIC_LENGTH, errorline, errorfile);
		return false;
	}

	if(lenPerc >= 1.0)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_ARRAY_ONREVERSINGPERC, PLEX_ERRORMESS_GENERIC_LENGTH, errorline, errorfile);
		aLenPerc = 1;
	}

	count = expandArray->count;

	PLEX_reverseProtoExpandArrayInt(aBegPerc * count, aLenPerc * count, expandArray, errorline, errorfile);

	return true;
}

// setters ------------------------------------------------------------------------------------------------------------------

void PLEX_setGrowthUnitProtoExpandArrayInt(const size_t growthUnit, PLEX_PROTOEXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile)
{
	if(expandArray == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_ARRAY_ONGROWTHUNITSET, PLEX_ERRORMESS_ARRAY_ARRAY, errorline, errorfile);
		return;
	}

	if(!growthUnit)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_ZEROVALUE, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_ARRAY_ONGROWTHUNITSET, PLEX_ERRORMESS_ARRAY_ARRAYGROWTHUNIT, errorline, errorfile);
		return;
	}

	expandArray->growthUnit = growthUnit;
}

// getters ------------------------------------------------------------------------------------------------------------------

void* PLEX_getProtoExpandArrayEntryInt(const size_t index, PLEX_PROTOEXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile)
{
	if(expandArray == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_ARRAY_ONGETENTRY, PLEX_ERRORMESS_ARRAY_ARRAY, errorline, errorfile);
		return NULL;
	}

	if(expandArray->contents == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_CONTENTCORRUPTION, PLEX_ERROR_SEVERITY_IMPOSSIBLE, PLEX_ERRORMESS_ARRAY_ONGETENTRY, PLEX_ERRORMESS_ARRAY_ARRAYCONTENTS, errorline, errorfile);
		return NULL;
	}

	if(index >= expandArray->count)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_ARRAY_ONGETENTRY, PLEX_ERRORMESS_ARRAY_ARRAYCOUNT, errorline, errorfile);
		return NULL;
	}

	return expandArray->contents + (index * expandArray->unitSize);
}

void* PLEX_getProtoExpandArrayLastInt(PLEX_PROTOEXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile)
{
	if(expandArray == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_ARRAY_ONGETENTRYLAST, PLEX_ERRORMESS_ARRAY_ARRAY, errorline, errorfile);
		return NULL;
	}

	if(expandArray->contents == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_CONTENTCORRUPTION, PLEX_ERROR_SEVERITY_IMPOSSIBLE, PLEX_ERRORMESS_ARRAY_ONGETENTRYLAST, PLEX_ERRORMESS_ARRAY_ARRAYCONTENTS, errorline, errorfile);
		return NULL;
	}

	return PLEX_getProtoExpandArrayEntryInt(expandArray->count - 1, expandArray, errorline, errorfile);
}

size_t PLEX_protoExpandArrayCountInt(const PLEX_PROTOEXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile)
{
	if(expandArray == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_ARRAY_ONGETCOUNT, PLEX_ERRORMESS_ARRAY_ARRAY, errorline, errorfile);
		return 0;
	}

	if(expandArray->contents == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_CONTENTCORRUPTION, PLEX_ERROR_SEVERITY_IMPOSSIBLE, PLEX_ERRORMESS_ARRAY_ONGETCOUNT, PLEX_ERRORMESS_ARRAY_ARRAYCONTENTS, errorline, errorfile);
		return 0;
	}

	return expandArray->count;
}

size_t PLEX_protoExpandArrayCapacityInt(const PLEX_PROTOEXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile)
{
	if(expandArray == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_ARRAY_ONGETCAPACITY, PLEX_ERRORMESS_ARRAY_ARRAY, errorline, errorfile);
		return 0;
	}

	if(expandArray->contents == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_CONTENTCORRUPTION, PLEX_ERROR_SEVERITY_IMPOSSIBLE, PLEX_ERRORMESS_ARRAY_ONGETCAPACITY, PLEX_ERRORMESS_ARRAY_ARRAYCONTENTS, errorline, errorfile);
		return 0;
	}

	return expandArray->capacity;
}

size_t PLEX_protoExpandArrayUnitSizeInt(const PLEX_PROTOEXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile)
{
	if(expandArray == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_ARRAY_ONGETUNITSIZE, PLEX_ERRORMESS_ARRAY_ARRAY, errorline, errorfile);
		return 0;
	}

	if(expandArray->contents == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_CONTENTCORRUPTION, PLEX_ERROR_SEVERITY_IMPOSSIBLE, PLEX_ERRORMESS_ARRAY_ONGETUNITSIZE, PLEX_ERRORMESS_ARRAY_ARRAYCONTENTS, errorline, errorfile);
		return 0;
	}

	return expandArray->unitSize;
}

size_t PLEX_protoExpandArrayGrowthUnitInt(const PLEX_PROTOEXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile)
{
	if(expandArray == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_ARRAY_ONGETGROWTHUNIT, PLEX_ERRORMESS_ARRAY_ARRAY, errorline, errorfile);
		return 0;
	}

	if(expandArray->contents == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_CONTENTCORRUPTION, PLEX_ERROR_SEVERITY_IMPOSSIBLE, PLEX_ERRORMESS_ARRAY_ONGETGROWTHUNIT, PLEX_ERRORMESS_ARRAY_ARRAYCONTENTS, errorline, errorfile);
		return 0;
	}

	return expandArray->growthUnit;
}

size_t PLEX_protoExpandArraySizeInt(const PLEX_PROTOEXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile)
{
	if(expandArray == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_ARRAY_ONGETSIZE, PLEX_ERRORMESS_ARRAY_ARRAY, errorline, errorfile);
		return 0;
	}

	if(expandArray->contents == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_CONTENTCORRUPTION, PLEX_ERROR_SEVERITY_IMPOSSIBLE, PLEX_ERRORMESS_ARRAY_ONGETSIZE, PLEX_ERRORMESS_ARRAY_ARRAYCONTENTS, errorline, errorfile);
		return 0;
	}

	return expandArray->count * expandArray->unitSize;
}

size_t PLEX_protoExpandArrayCapacitySizeInt(const PLEX_PROTOEXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile)
{
	if(expandArray == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_ARRAY_ONGETCAPACITYSIZE, PLEX_ERRORMESS_ARRAY_ARRAYCONTENTS, errorline, errorfile);
		return 0;
	}

	if(expandArray->contents == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_CONTENTCORRUPTION, PLEX_ERROR_SEVERITY_IMPOSSIBLE, PLEX_ERRORMESS_ARRAY_ONGETCAPACITYSIZE, PLEX_ERRORMESS_ARRAY_ARRAYCONTENTS, errorline, errorfile);
		return 0;
	}

	return expandArray->capacity * expandArray->unitSize;
}

void* PLEX_protoExpandArrayContentsInt(const PLEX_PROTOEXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile)
{
	if(expandArray == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_ARRAY_ONGECONTENT, PLEX_ERRORMESS_ARRAY_ARRAY, errorline, errorfile);
		return NULL;
	}

	if(expandArray->contents == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ARRAY, PLEX_ERROR_CONTENTCORRUPTION, PLEX_ERROR_SEVERITY_IMPOSSIBLE, PLEX_ERRORMESS_ARRAY_ONGECONTENT, PLEX_ERRORMESS_ARRAY_ARRAYCONTENTS, errorline, errorfile);
		return NULL;
	}

	return expandArray->contents;
}

void PLEX_clearProtoExpandInternalMemInt(const bool report, FILE* const reportFile, const size_t errorline, const char* const errorfile)
{
	p_clearExpandArrayMem(report, reportFile, errorline, errorfile);
}
