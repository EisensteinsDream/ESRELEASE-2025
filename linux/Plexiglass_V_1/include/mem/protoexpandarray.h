#ifndef PLEX_PROTOEXPANDARRAY_H
#define PLEX_PROTOEXPANDARRAY_H

#include "mem/memprofile.h"

#include "utility/error.h"

// This unit handles customizable dynamic low level arrays. Useful mostly as a base for more specific dynamic arrays as it utilizes custom allocation and deallocation methods. In most cases you won't be using this unit but using expandarray.h/c instead.

// NOTE: This is an independent unit. Not a unit with an accompanying state machine. It has no 'start, update, or end' functions that need to be called to operate.

// macro functions and macros -----------------------------------------------------------------------------------------------

// ARGUMENTS: (const size_t growthUnit, const size_t unitSize, PLEX_F_MEMHOOK memHook, PLEX_F_FREEHOOK freeHook) - returns PLEX_PROTOEXPANDARRAY*

#define PLEX_genProtoExpandArray(growthUnit, unitSize, memHook, freeHook) PLEX_genProtoExpandArrayInt(growthUnit, unitSize, memHook, freeHook, __LINE__, __FILE__)

// ARGUMENTS: (PLEX_PROTOEXPANDARRAY** expandArray)

#define PLEX_destroyProtoExpandArray(expandArray) PLEX_destroyProtoExpandArrayInt(expandArray, __LINE__, __FILE__)

// ARGUMENTS: (const size_t capacity, PLEX_PROTOEXPANDARRAY* expandArray) - returns bool

#define PLEX_expandProtoExpandArray(capacity, expandArray) PLEX_expandProtoExpandArrayInt(capacity, expandArray, __LINE__, __FILE__)

// ARGUMENTS: (const size_t capacity, PLEX_PROTOEXPANDARRAY* expandArray) - returns bool

#define PLEX_incrementProtoExpandArray(expandArray) PLEX_incrementProtoExpandArrayInt(expandArray, __LINE__, __FILE__)

// ARGUMENTS: (const size_t by, PLEX_PROTOEXPANDARRAY* expandArray) - returns bool

#define PLEX_multiIncrementProtoExpandArray(by, expandArray) PLEX_multiIncrementProtoExpandArrayInt(by, expandArray, __LINE__, __FILE__)

// ARGUMENTS: (PLEX_PROTOEXPANDARRAY* expandArray) - returns bool

#define PLEX_decrementProtoExpandArray(expandArray) PLEX_decrementProtoExpandArrayInt(expandArray, __LINE__, __FILE__)

// ARGUMENTS: (const size_t index, PLEX_PROTOEXPANDARRAY* expandArray) - returns bool

#define PLEX_removeProtoExpandArray(index, expandArray) PLEX_removeProtoExpandArrayInt(index, expandArray, __LINE__, __FILE__)

// ARGUMENTS: (PLEX_PROTOEXPANDARRAY* expandArray)

#define PLEX_clearCountProtoExpandArray(expandArray) PLEX_clearCountProtoExpandArrayInt(expandArray, __LINE__, __FILE__)

// ARGUMENTS: (const bool report, FILE* const reportFile)

#define PLEX_clearProtoExpandInternalMem(report, reportFile) PLEX_clearProtoExpandInternalMemInt(report, reportFile,  __LINE__, __FILE__)

// ARGUMENTS: (const size_t beg, const size_t beg2, const size_t len, PLEX_PROTOEXPANDARRAY* expandArray) - returns bool

#define PLEX_rearrangeProtoExpandArray(beg, beg2, len, expandArray) PLEX_rearrangeProtoExpandArrayInt(beg, beg2, len, expandArray, __LINE__, __FILE__)

// ARGUMENTS: (const size_t beg, const size_t beg2, const size_t len, PLEX_PROTOEXPANDARRAY* expandArray, PLEX_PROTOEXPANDARRAY* expandArray2) - returns bool

#define PLEX_swapProtoExpandArray(beg, beg2, len, expandArray, expandArray2) PLEX_swapProtoExpandArrayInt(beg, beg2, len, expandArray, expandArray2, __LINE__, __FILE__)

// ARGUMENTS: (const size_t beg, const size_t len, PLEX_PROTOEXPANDARRAY* expandArray) - returns bool

#define PLEX_cutProtoExpandArray(beg, len, expandArray) PLEX_cutProtoExpandArrayInt(beg, len, expandArray, __LINE__, __FILE__)

// ARGUMENTS: (const size_t beg, const size_t len, PLEX_PROTOEXPANDARRAY* expandArray) - returns bool

#define PLEX_reverseProtoExpandArray(beg, len, expandArray) PLEX_reverseProtoExpandArrayInt(beg, len, expandArray, __LINE__, __FILE__)

// ARGUMENTS: (const double begPerc, const double begPerc2, const double lenPerc, PLEX_PROTOEXPANDARRAY* expandArray) - returns bool

#define PLEX_rearrangeProtoExpandArrayPerc(begPerc, begPerc2, lenPerc, expandArray) PLEX_rearrangeProtoExpandArrayPercInt(begPerc, begPerc2, lenPerc, expandArray, __LINE__, __FILE__)

// ARGUMENTS: (const double begPerc, const double begPerc2, const double lenPerc, PLEX_PROTOEXPANDARRAY* expandArray, PLEX_PROTOEXPANDARRAY* expandArray2) - returns bool

#define PLEX_swapProtoExpandArrayPerc(begPerc, begPerc2, lenPerc, expandArray, expandArray2) PLEX_swapProtoExpandArrayPercInt(begPerc, begPerc2, lenPerc, expandArray, expandArray2, __LINE__, __FILE__)

// ARGUMENTS: (const double begPerc, const double lenPerc, PLEX_PROTOEXPANDARRAY* expandArray) - returns bool

#define PLEX_cutProtoExpandArrayPerc(begPerc, lenPerc, expandArray) PLEX_cutProtoExpandArrayPercInt(begPerc, lenPerc, expandArray, __LINE__, __FILE__)

// ARGUMENTS: (const double begPerc, const double lenPerc, PLEX_PROTOEXPANDARRAY* expandArray) - returns bool

#define PLEX_reverseProtoExpandArrayPerc(begPerc, lenPerc, expandArray) PLEX_reverseProtoExpandArrayPercInt(begPerc, lenPerc, expandArray, __LINE__, __FILE__)

// ARGUMENTS: (const size_t growthUnit, PLEX_PROTOEXPANDARRAY* expandArray)

#define PLEX_setGrowthUnitProtoExpandArray(growthUnit, expandArray) PLEX_setGrowthUnitProtoExpandArrayInt(growthUnit, expandArray, __LINE__, __FILE__)

// ARGUMENTS: (const size_t index, PLEX_PROTOEXPANDARRAY* expandArray) - returns void*

#define PLEX_getProtoExpandArrayEntry(index, expandArray) PLEX_getProtoExpandArrayEntryInt(index, expandArray, __LINE__, __FILE__)

// ARGUMENTS: (PLEX_PROTOEXPANDARRAY* expandArray) - returns void*

#define PLEX_getProtoExpandArrayLast(expandArray) PLEX_getProtoExpandArrayLastInt(expandArray, __LINE__, __FILE__)

// ARGUMENTS: (PLEX_PROTOEXPANDARRAY* expandArray) - returns size_t

#define PLEX_protoExpandArrayCount(expandArray) PLEX_protoExpandArrayCountInt(expandArray, __LINE__, __FILE__)

// ARGUMENTS: (PLEX_PROTOEXPANDARRAY* expandArray) - returns size_t

#define PLEX_protoExpandArrayCapacity(expandArray) PLEX_protoExpandArrayCapacityInt(expandArray, __LINE__, __FILE__)

// ARGUMENTS: (PLEX_PROTOEXPANDARRAY* expandArray) - returns size_t

#define PLEX_protoExpandArrayUnitSize(expandArray) PLEX_protoExpandArrayUnitSizeInt(expandArray, __LINE__, __FILE__)

// ARGUMENTS: (PLEX_PROTOEXPANDARRAY* expandArray) - returns size_t

#define PLEX_protoExpandArrayGrowthUnit(expandArray) PLEX_protoExpandArrayGrowthUnitInt(expandArray, __LINE__, __FILE__)

// ARGUMENTS: (PLEX_PROTOEXPANDARRAY* expandArray) - returns size_t

#define PLEX_protoExpandArraySize(expandArray) PLEX_protoExpandArraySizeInt(expandArray, __LINE__, __FILE__)

// ARGUMENTS: (PLEX_PROTOEXPANDARRAY* expandArray) - returns size_t

#define PLEX_protoExpandArrayCapacitySize(expandArray) PLEX_protoExpandArrayCapacitySizeInt(expandArray, __LINE__, __FILE__)

// ARGUMENTS: (PLEX_PROTOEXPANDARRAY* expandArray) - returns void*

#define PLEX_protoExpandArrayContents(expandArray) PLEX_protoExpandArrayContentsInt(expandArray, __LINE__, __FILE__)

// structs, unions, enums, function prototypes ------------------------------------------------------------------------------

// the basic custom allocation and deallocation function types to be passed into expand arrays
typedef void* (PLEX_F_MEMHOOK)(const size_t, size_t, const char* const);
typedef void (PLEX_F_FREEHOOK)(void**, size_t, const char* const);

// the structs that contain protoexpandarray information
typedef struct
{
	char* contents;
	size_t count, capacity, growthUnit, unitSize, memTicket;
	PLEX_F_MEMHOOK* memHook;
	PLEX_F_FREEHOOK* freeHook;
} PLEX_PROTOEXPANDARRAY;

// public functions ---------------------------------------------------------------------------------------------------------

#ifdef __cplusplus
extern"C"
{
#endif
// specialized functions ----------------------------------------------------------------------------------------------------

	// allocates a new protoexpandarray. Growth Unit indicates how many entries are allocated at beginning and how many will be allocated as the array expands. The unitSize would be the size of the individual unit in bytes contained within. memHook is the memory allocation unit for hooks, freeHook is the memory unit deallocation for hooks. Hook function types are described above.

	extern PLEX_PROTOEXPANDARRAY* PLEX_genProtoExpandArrayInt(const size_t growthUnit, const size_t unitSize, PLEX_F_MEMHOOK memHook, PLEX_F_FREEHOOK freeHook, const size_t errorline, const char* const errorfile);

	// destroys the protoExpandArray by a pointer to an allocated pointer. Frees all content (by the freeHook), frees the protoExpandArray allocation, and sets it to NULL.

	extern void PLEX_destroyProtoExpandArrayInt(PLEX_PROTOEXPANDARRAY** expandArray, const size_t errorline, const char* const errorfile);

	// expands a protoExpandArray up to capacity (number of bytes = capacity * unitSize). If the capacity is more than the current capacity, then it expands. If it is not, it doesn't bother expanding. Returns true whether it expands or not, but returns false if anything goes wrong.

	extern bool PLEX_expandProtoExpandArrayInt(const size_t capacity, PLEX_PROTOEXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile);

	// increments the protoExpandArray by one unit, expanding it internally if needed. Returns false if anything goes wrong.

	extern bool PLEX_incrementProtoExpandArrayInt(PLEX_PROTOEXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile);

	// increments the protoExpandArray by 'by' number of units, expanding internally if needed. Returns false if anything goes wrong.

	extern bool PLEX_multiIncrementProtoExpandArrayInt(const size_t by, PLEX_PROTOEXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile);

	// decrements the protoExpandArray by one unit.

	extern bool PLEX_decrementProtoExpandArrayInt(PLEX_PROTOEXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile);

	// removes an entry from the protoExpandArray

	extern bool PLEX_removeProtoExpandArrayInt(const size_t index, PLEX_PROTOEXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile);

	// clears the protoExpandArray of all values

	extern void PLEX_clearCountProtoExpandArrayInt(PLEX_PROTOEXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile);

	// takes one piece of protoExpandArray to another. From beg to beg2 with a chunk as big as 'len'. len may be shrunk for safety reasons. Returns false if anything goes wrong.

	extern bool PLEX_rearrangeProtoExpandArrayInt(const size_t beg, const size_t beg2, const size_t len, PLEX_PROTOEXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile);

	// moves a piece of a piece of one protoExpandArray to another protoExpandArray from beg to beg2. The size is up to len but will be shrunk by the size of either protoExpandArray's contents for safety. Returns false if anything goes wrong.

	extern bool PLEX_swapProtoExpandArrayInt(const size_t beg, const size_t beg2, const size_t len, PLEX_PROTOEXPANDARRAY* expandArray, PLEX_PROTOEXPANDARRAY* expandArray2, const size_t errorline, const char* const errorfile);

	// cuts out a piece of protoExpandArray at beg size of length, decreasing the size of protoExpandArray. Also, reducing len if needed for safety reasons. Returns false if anything goes wrong.

	extern bool PLEX_cutProtoExpandArrayInt(const size_t beg, const size_t len, PLEX_PROTOEXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile);

	// reverses the order of a section of the protoExpandArray

	extern bool PLEX_reverseProtoExpandArrayInt(const size_t beg, const size_t len, PLEX_PROTOEXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile);

	// same as rearrange except by percentages rather than determined lengths. Of course, the percentages are related to the length of the protoExpandArray. Returns false if anything goes wrong.

	extern bool PLEX_rearrangeProtoExpandArrayPercInt(const double begPerc, const double begPerc2, const double lenPerc, PLEX_PROTOEXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile);

	// same as swap except by percentages rather than determined lengths. Of course, the percentages are related to the length of the protoExpandArray. Returns false if anything goes wrong.

	extern bool PLEX_swapProtoExpandArrayPercInt(const double begPerc, const double begPerc2, const double lenPerc, PLEX_PROTOEXPANDARRAY* expandArray, PLEX_PROTOEXPANDARRAY* expandArray2, const size_t errorline, const char* const errorfile);

	// same as cut except by percentages rather than determined lengths. Of course, the percentages are related to the length of the protoExpandArray. Returns false if anything goes wrong.

	extern bool PLEX_cutProtoExpandArrayPercInt(const double begPerc, const double lenPerc, PLEX_PROTOEXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile);

	// same as rearrange except by percentages rather than determined lengths. Of course, the percentages are related to the length of the protoExpandArray. Returns false if anything goes wrong.

	extern bool PLEX_reverseProtoExpandArrayPercInt(const double begPerc, const double lenPerc, PLEX_PROTOEXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile);

	// clears the internal memory needed to allocate protoexpandarrays. PLEX_endMem() should handle this. You never need to call it manually.

	extern void PLEX_clearProtoExpandInternalMemInt(const bool report, FILE* const reportFile, const size_t errorline, const char* const errorfile);

// setters ------------------------------------------------------------------------------------------------------------------

	// sets the growth unit to something else

	extern void PLEX_setGrowthUnitProtoExpandArrayInt(const size_t growthUnit, PLEX_PROTOEXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile);

// getters ------------------------------------------------------------------------------------------------------------------

	// returns a pointer to an entry to the protoExpandArray by index. Returns NULL if anything goes wrong.

	extern void* PLEX_getProtoExpandArrayEntryInt(const size_t index, PLEX_PROTOEXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile);

	// returns the last pointer to an entry to the protoExpandArray. Returns NULL if anything goes wrong.

	extern void* PLEX_getProtoExpandArrayLastInt(PLEX_PROTOEXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile);

	// returns the number of entries (each size of 'unit size') contained in the protoExpandArray.

	extern size_t PLEX_protoExpandArrayCountInt(const PLEX_PROTOEXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile);

	// returns the 'capacity' contained in the protoExpandArray. (ie. the potential number of units needed before expanding)

	extern size_t PLEX_protoExpandArrayCapacityInt(const PLEX_PROTOEXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile);

	// returns the 'unit size' of a protoExpandArray.

	extern size_t PLEX_protoExpandArrayUnitSizeInt(const PLEX_PROTOEXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile);

	// returns the 'growth unit' of a protoExpandArray.

	extern size_t PLEX_protoExpandArrayGrowthUnitInt(const PLEX_PROTOEXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile);

	// returns the 'size' of a protoExpandArray which means the byte size of the count. Where as 'count' is the number of units.

	extern size_t PLEX_protoExpandArraySizeInt(const PLEX_PROTOEXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile);

	// returns the 'capacity size' of a protoExpandArray which means the byte size of the capacity. Where as 'capacity' is the number of units capacity.

	extern size_t PLEX_protoExpandArrayCapacitySizeInt(const PLEX_PROTOEXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile);

	// returns the pointer to the contents of a protoExpandArray, use sparingly.

	extern void* PLEX_protoExpandArrayContentsInt(const PLEX_PROTOEXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile);
#ifdef __cplusplus
}
#endif

#endif
