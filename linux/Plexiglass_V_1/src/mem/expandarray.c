#include "mem/expandarray.h"

// NOTE: global function descriptions in header.

// NOTE: you can note all of these functions simply call an equivalent protoExpandArray function. The reason for this is that the alloc and dealloc hooks are passed in on generation. This is mostly done just to prevent syntactical confusion. On all updates and modifications these should remain synchronized. Most of the important information about how expand arrays work is in protoexpandarray not expandarray.

// static functions ---------------------------------------------------------------------------------------------------------

// the hook for expand array allocation

static void* p_expandArrayAlloc(size_t size, const size_t errorline, const char* const errorfile)
{
	return PLEX_allocInt(size, errorline, errorfile);
}

// the hook for expand array deallocation

static void p_expandArrayDealloc(void** toFree, const size_t errorline, const char* const errorfile)
{
	PLEX_deallocInt(toFree, errorline, errorfile);
}

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

// specialized functions ----------------------------------------------------------------------------------------------------

PLEX_EXPANDARRAY* PLEX_genExpandArrayInt(const size_t growthUnit, const size_t unitSize, const size_t errorline, const char* const errorfile)
{
	return PLEX_genProtoExpandArrayInt(growthUnit, unitSize, p_expandArrayAlloc, p_expandArrayDealloc, errorline, errorfile);
}

void PLEX_destroyExpandArrayInt(PLEX_EXPANDARRAY** expandArray, const size_t errorline, const char* const errorfile)
{
	PLEX_destroyProtoExpandArrayInt(expandArray, errorline, errorfile);
}

bool PLEX_expandExpandArrayInt(const size_t capacity, PLEX_EXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile)
{
	return PLEX_expandProtoExpandArrayInt(capacity, expandArray, errorline, errorfile);
}

bool PLEX_incrementExpandArrayInt(PLEX_EXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile)
{
	return PLEX_incrementProtoExpandArrayInt(expandArray, errorline, errorfile);
}

bool PLEX_multiIncrementExpandArrayInt(const size_t by, PLEX_EXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile)
{
	return PLEX_multiIncrementProtoExpandArrayInt(by, expandArray, errorline, errorfile);
}

bool PLEX_decrementExpandArrayInt(PLEX_EXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile)
{
	 return PLEX_decrementProtoExpandArrayInt(expandArray, errorline, errorfile);
}

bool PLEX_removeExpandArrayInt(const size_t index, PLEX_EXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile)
{
	return PLEX_removeProtoExpandArrayInt(index, expandArray, errorline, errorfile);
}

void PLEX_clearExpandArrayInt(PLEX_EXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile)
{
	PLEX_clearCountProtoExpandArrayInt(expandArray, errorline, errorfile);
}

bool PLEX_rearrangeExpandArrayInt(const size_t beg, const size_t beg2, const size_t len, PLEX_EXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile)
{
	return PLEX_rearrangeProtoExpandArrayInt(beg, beg2, len, expandArray, errorline, errorfile);
}

bool PLEX_swapExpandArrayInt(const size_t beg, const size_t beg2, const size_t len, PLEX_EXPANDARRAY* expandArray, PLEX_EXPANDARRAY* expandArray2, const size_t errorline, const char* const errorfile)
{
	return PLEX_swapProtoExpandArrayInt(beg, beg2, len, expandArray, expandArray2, errorline, errorfile);
}

bool PLEX_cutExpandArrayInt(const size_t beg, const size_t len, PLEX_EXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile)
{
	return PLEX_cutProtoExpandArrayInt(beg, len, expandArray, errorline, errorfile);
}

bool PLEX_reverseExpandArrayInt(const size_t beg, const size_t len, PLEX_EXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile)
{
	return PLEX_reverseProtoExpandArrayInt(beg, len, expandArray, errorline, errorfile);
}

bool PLEX_rearrangeExpandArrayPercInt(const double begPerc, const double begPerc2, const double lenPerc, PLEX_EXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile)
{
	return PLEX_rearrangeProtoExpandArrayPercInt(begPerc, begPerc2, lenPerc, expandArray, errorline, errorfile);
}

bool PLEX_swapExpandArrayPercInt(const double begPerc, const double begPerc2, const double lenPerc, PLEX_EXPANDARRAY* expandArray, PLEX_EXPANDARRAY* expandArray2, const size_t errorline, const char* const errorfile)
{
	return PLEX_swapProtoExpandArrayPercInt(begPerc, begPerc2, lenPerc, expandArray, expandArray2, errorline, errorfile);
}

bool PLEX_cutExpandArrayPercInt(const double begPerc, const double lenPerc, PLEX_PROTOEXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile)
{
	return PLEX_cutProtoExpandArrayPercInt(begPerc, lenPerc, expandArray, errorline, errorfile);
}

bool PLEX_reverseExpandArrayPercInt(const double begPerc, const double lenPerc, PLEX_PROTOEXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile)
{
	return PLEX_reverseProtoExpandArrayPercInt(begPerc, lenPerc, expandArray, errorline, errorfile);
}

// setters ------------------------------------------------------------------------------------------------------------------

void PLEX_setGrowthUnitExpandArrayInt(const size_t growthUnit, PLEX_EXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile)
{
	PLEX_setGrowthUnitProtoExpandArrayInt(growthUnit, expandArray, errorline, errorfile);
}

// getters ------------------------------------------------------------------------------------------------------------------

void* PLEX_getExpandArrayEntryInt(const size_t index, PLEX_EXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile)
{
	return PLEX_getProtoExpandArrayEntryInt(index, expandArray, errorline, errorfile);
}

void* PLEX_getExpandArrayLastInt(PLEX_EXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile)
{
	return PLEX_getProtoExpandArrayLastInt(expandArray, errorline, errorfile);
}

size_t PLEX_expandArrayCountInt(const PLEX_EXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile)
{
	return PLEX_protoExpandArrayCountInt(expandArray, errorline, errorfile);
}

size_t PLEX_expandArrayCapacityInt(const PLEX_EXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile)
{
	return PLEX_protoExpandArrayCapacityInt(expandArray, errorline, errorfile);
}

size_t PLEX_expandArrayUnitSizeInt(const PLEX_EXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile)
{
	return PLEX_protoExpandArrayUnitSizeInt(expandArray, errorline, errorfile);
}

size_t PLEX_expandArrayGrowthUnitInt(const PLEX_EXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile)
{
	return PLEX_protoExpandArrayGrowthUnitInt(expandArray, errorline, errorfile);
}

size_t PLEX_expandArraySizeInt(const PLEX_EXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile)
{
	return PLEX_protoExpandArraySizeInt(expandArray, errorline, errorfile);
}

size_t PLEX_expandArrayCapacitySizeInt(const PLEX_EXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile)
{
	return PLEX_protoExpandArrayCapacitySizeInt(expandArray, errorline, errorfile);
}

void* PLEX_expandArrayContentsInt(const PLEX_EXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile)
{
	return PLEX_protoExpandArrayContentsInt(expandArray, errorline, errorfile);
}
