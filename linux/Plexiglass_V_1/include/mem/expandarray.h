#ifndef PLEX_EXPANDARRAY_H
#define PLEX_EXPANDARRAY_H

#include "mem.h"

// A simple low-level dynamic storage unit. Utilizes the PLEX_alloc and PLEX_dealloc for it's memory management.

// NOTE: This is an independent unit. Not a unit with an accompanying state machine. It has no 'start, update, or end' functions that need to be called to operate.

// macro functions and macros -----------------------------------------------------------------------------------------------

// ARGUMENTS: (const size_t growthUnit, const size_t unitSize) - returns PLEX_EXPANDARRAY*

#define PLEX_genExpandArray(growthUnit, unitSize) PLEX_genExpandArrayInt(growthUnit, unitSize, __LINE__, __FILE__)

// ARGUMENTS: (PLEX_EXPANDARRAY* expandArray)

#define PLEX_destroyExpandArray(expandArray) PLEX_destroyExpandArrayInt(expandArray, __LINE__, __FILE__)

// ARGUMENTS: (const size_t capacity, PLEX_EXPANDARRAY* expandArray)- returns bool

#define PLEX_expandExpandArray(capacity, expandArray) PLEX_expandExpandArrayInt(capacity, expandArray, __LINE__, __FILE__)

// ARGUMENTS: (PLEX_EXPANDARRAY* expandArray)- returns bool

#define PLEX_incrementExpandArray(expandArray) PLEX_incrementExpandArrayInt(expandArray, __LINE__, __FILE__)

// ARGUMENTS: (const size_t by, PLEX_EXPANDARRAY* expandArray) - returns bool

#define PLEX_multiIncrementExpandArray(by, expandArray) PLEX_multiIncrementExpandArrayInt(by, expandArray, __LINE__, __FILE__)

// ARGUMENTS: (PLEX_EXPANDARRAY* expandArray) - returns bool

#define PLEX_decrementExpandArray(expandArray) PLEX_decrementExpandArrayInt(expandArray, __LINE__, __FILE__)

// ARGUMENTS: (const size_t index, PLEX_EXPANDARRAY* expandArray) - returns bool

#define PLEX_removeExpandArray(index, expandArray) PLEX_removeExpandArrayInt(index, expandArray, __LINE__, __FILE__)

// ARGUMENTS: (PLEX_EXPANDARRAY* expandArray)

#define PLEX_clearExpandArray(expandArray) PLEX_clearExpandArrayInt(expandArray, __LINE__, __FILE__)

// ARGUMENTS: (const size_t beg, const size_t beg2, const size_t len, PLEX_EXPANDARRAY* expandArray)- returns bool

#define PLEX_rearrangeExpandArray(beg, beg2, len, expandArray) PLEX_rearrangeExpandArrayInt(beg, beg2, len, expandArray, __LINE__, __FILE__)

// ARGUMENTS: (const size_t beg, const size_t beg2, const size_t len, PLEX_EXPANDARRAY* expandArray, PLEX_EXPANDARRAY* expandArray2)- returns bool

#define PLEX_swapExpandArray(beg, beg2, len, expandArray, expandArray2) PLEX_swapExpandArrayInt(beg, beg2, len, expandArray, expandArray2, __LINE__, __FILE__)

// ARGUMENTS: (const size_t beg, const size_t len, PLEX_EXPANDARRAY* expandArray) - returns bool

#define PLEX_cutExpandArray(beg, len, expandArray) PLEX_cutExpandArrayInt(beg, len, expandArray, __LINE__, __FILE__)

// ARGUMENTS: (const size_t beg, const size_t len, PLEX_EXPANDARRAY* expandArray) - returns bool

#define PLEX_reverseExpandArray(beg, len, expandArray) PLEX_reverseExpandArrayInt(beg, len, expandArray, __LINE__, __FILE__)

// ARGUMENTS: (const double begPerc, const double begPerc2, const double lenPerc, PLEX_EXPANDARRAY* expandArray) - returns bool

#define PLEX_rearrangeExpandArrayPerc(begPerc, begPerc2, lenPerc, expandArray) PLEX_rearrangeExpandArrayPercInt(begPerc, begPerc2, lenPerc, expandArray, __LINE__, __FILE__)

// ARGUMENTS: (const double begPerc, const double begPerc2, const double lenPerc, PLEX_EXPANDARRAY* expandArray, PLEX_EXPANDARRAY* expandArray2) - returns bool

#define PLEX_swapExpandArrayPerc(begPerc, begPerc2, lenPerc, expandArray, expandArray2) PLEX_swapExpandArrayPercInt(begPerc, begPerc2, lenPerc, expandArray, expandArray2, __LINE__, __FILE__)

// ARGUMENTS: (const double begPerc, const double lenPerc, PLEX_PROTOEXPANDARRAY* expandArray) - returns bool

#define PLEX_cutExpandArrayPerc(begPerc, lenPerc, expandArray) PLEX_cutExpandArrayPercInt(begPerc, lenPerc, expandArray, __LINE__, __FILE__)

// ARGUMENTS: (const double begPerc, const double lenPerc, PLEX_PROTOEXPANDARRAY* expandArray) - returns bool

#define PLEX_reverseExpandArrayPerc(begPerc, lenPerc, expandArray) PLEX_reverseExpandArrayPercInt(begPerc, lenPerc, expandArray, __LINE__, __FILE__)

// ARGUMENTS: (const size_t growthUnit, PLEX_EXPANDARRAY* expandArray)

#define PLEX_setGrowthUnitExpandArray(growthUnit, expandArray) PLEX_setGrowthUnitExpandArrayInt(growthUnit, expandArray, __LINE__, __FILE__)

// ARGUMENTS: (const size_t index, PLEX_EXPANDARRAY* expandArray) - returns void*

#define PLEX_getExpandArrayEntry(index, expandArray) PLEX_getExpandArrayEntryInt(index, expandArray, __LINE__, __FILE__)

// ARGUMENTS: (PLEX_EXPANDARRAY* expandArray) - returns void*

#define PLEX_getExpandArrayLast(expandArray) PLEX_getExpandArrayLastInt(expandArray, __LINE__, __FILE__)

// ARGUMENTS: (PLEX_EXPANDARRAY* expandArray) - returns size_t

#define PLEX_expandArrayCount(expandArray) PLEX_expandArrayCountInt(expandArray, __LINE__, __FILE__)

// ARGUMENTS: (const PLEX_EXPANDARRAY* expandArray) - returns size_t

#define PLEX_expandArrayCapacity(expandArray) PLEX_expandArrayCapacityInt(expandArray, __LINE__, __FILE__)

// ARGUMENTS: (const PLEX_EXPANDARRAY* expandArray) - returns size_t

#define PLEX_expandArrayUnitSize(expandArray) PLEX_expandArrayUnitSizeInt(expandArray, __LINE__, __FILE__)

// ARGUMENTS: (const PLEX_EXPANDARRAY* expandArray) - returns size_t

#define PLEX_expandArrayGrowthUnit(expandArray) PLEX_expandArrayGrowthUnitInt(expandArray, __LINE__, __FILE__)

// ARGUMENTS: (const PLEX_EXPANDARRAY* expandArray) - returns size_t

#define PLEX_expandArraySize(expandArray) PLEX_expandArraySizeInt(expandArray, __LINE__, __FILE__)

// ARGUMENTS: (const PLEX_EXPANDARRAY* expandArray) - returns size_t

#define PLEX_expandArrayCapacitySize(expandArray) PLEX_expandArrayCapacitySizeInt(expandArray, __LINE__, __FILE__)

// ARGUMENTS: (const PLEX_EXPANDARRAY* expandArray) - returns void*

#define PLEX_expandArrayContents(expandArray) PLEX_expandArrayContentsInt(expandArray, __LINE__, __FILE__)

// structs, unions, enums, function prototypes ------------------------------------------------------------------------------

// expandarray is essentially a typedef'd protoexpandarray. Still, it's not good practice to interchange them.

typedef PLEX_PROTOEXPANDARRAY PLEX_EXPANDARRAY;

// public functions ---------------------------------------------------------------------------------------------------------

#ifdef __cplusplus
extern"C"
{
#endif
// specialized functions ----------------------------------------------------------------------------------------------------

	// generates the expand array. 'growthUnit' is the amount of units needed to be added before expanding an expandArray internally. 'unit size' being the byte size of an individual contained unit.

	extern PLEX_EXPANDARRAY* PLEX_genExpandArrayInt(const size_t growthUnit, const size_t unitSize, const size_t errorline, const char* const errorfile);

	// destroys the expandArray by a pointer to an allocated pointer. Frees all content, frees the expandArray allocation, and sets it to NULL.

	extern void PLEX_destroyExpandArrayInt(PLEX_EXPANDARRAY** expandArray, const size_t errorline, const char* const errorfile);

	// expands a expandArray up to capacity (number of bytes = capacity * unitSize). If the capacity is more than the current capacity, then it expands. If it is not, it doesn't bother expanding. Returns true whether it expands or not, but returns false if anything goes wrong.

	extern bool PLEX_expandExpandArrayInt(const size_t capacity, PLEX_EXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile);

	// increments the expandArray by one unit, expanding internal capacity if needed. Returns false if anything goes wrong.

	extern bool PLEX_incrementExpandArrayInt(PLEX_EXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile);

	// increments the expandArray by 'by' number of units, expanding internal capacity if needed. Returns false if anything goes wrong.

	extern bool PLEX_multiIncrementExpandArrayInt(const size_t by, PLEX_EXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile);

	// decrements the expandArray by one unit.

	extern bool PLEX_decrementExpandArrayInt(PLEX_EXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile);

	// removes an entry from the protoExpandArray

	extern bool PLEX_removeExpandArrayInt(const size_t index, PLEX_EXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile);

	// clears the expandArray of all values

	extern void PLEX_clearExpandArrayInt(PLEX_EXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile);

	// takes one piece of expandArray to another. From beg to beg2 with a chunk as big as 'len'. len may be shrunk for safety reasons. Returns false if anything goes wrong. (in units)

	extern bool PLEX_rearrangeExpandArrayInt(const size_t beg, const size_t beg2, const size_t len, PLEX_EXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile);

	// moves a piece of a piece of one expandArray to another expandArray from beg to beg2. The size is up to len but will be shrunk by the size of either expandArray's contents for safety. Returns false if anything goes wrong. (in units)

	extern bool PLEX_swapExpandArrayInt(const size_t beg, const size_t beg2, const size_t len, PLEX_EXPANDARRAY* expandArray, PLEX_EXPANDARRAY* expandArray2, const size_t errorline, const char* const errorfile);

	// cuts out a piece of expandArray at beg size of length, decreasing the size of protoExpandArray. Also, reducing len if needed for safety reasons. Returns false if anything goes wrong. (in units)

	extern bool PLEX_cutExpandArrayInt(const size_t beg, const size_t len, PLEX_EXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile);

	// reverses the order of a section of the expandArray (in units)

	extern bool PLEX_reverseExpandArrayInt(const size_t beg, const size_t len, PLEX_EXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile);

	// same as rearrange except by percentages rather than determined lengths. Of course, the percentages are related to the length of the expandArray. Returns false if anything goes wrong.

	extern bool PLEX_rearrangeExpandArrayPercInt(const double begPerc, const double begPerc2, const double lenPerc, PLEX_EXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile);

	// same as swap except by percentages rather than determined lengths. Of course, the percentages are related to the length of the expandArray. Returns false if anything goes wrong.

	extern bool PLEX_swapExpandArrayPercInt(const double begPerc, const double begPerc2, const double lenPerc, PLEX_EXPANDARRAY* expandArray, PLEX_EXPANDARRAY* expandArray2, const size_t errorline, const char* const errorfile);

	// same as cut except by percentages rather than determined lengths. Of course, the percentages are related to the length of the expandArray. Returns false if anything goes wrong.

	extern bool PLEX_cutExpandArrayPercInt(const double begPerc, const double lenPerc, PLEX_PROTOEXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile);

	// same as rearrange except by percentages rather than determined lengths. Of course, the percentages are related to the length of the protoExpandArray. Returns false if anything goes wrong.

	extern bool PLEX_reverseExpandArrayPercInt(const double begPerc, const double lenPerc, PLEX_EXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile);

// setters ------------------------------------------------------------------------------------------------------------------

	// sets the growth unit to something else. Use with extreme care.

	extern void PLEX_setGrowthUnitExpandArrayInt(const size_t growthUnit, PLEX_EXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile);

// getters ------------------------------------------------------------------------------------------------------------------

	// returns a pointer to an entry to the expandArray by index. Returns NULL if anything goes wrong.

	extern void* PLEX_getExpandArrayEntryInt(const size_t index, PLEX_EXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile);

	// returns the last pointer to an entry to the expandArray. Returns NULL if anything goes wrong.

	extern void* PLEX_getExpandArrayLastInt(PLEX_EXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile);

	// returns the number of entries (each size of 'unit size') contained in the expandArray.

	extern size_t PLEX_expandArrayCountInt(const PLEX_EXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile);

	// returns the 'capacity' contained in the expandArray in. (ie. the potential number of units needed before expanding)

	extern size_t PLEX_expandArrayCapacityInt(const PLEX_EXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile);

	// returns the 'unit size' of a expandArray.

	extern size_t PLEX_expandArrayUnitSizeInt(const PLEX_EXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile);

	// returns the 'growth unit' of a expandArray.

	extern size_t PLEX_expandArrayGrowthUnitInt(const PLEX_EXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile);

	// returns the 'size' of a expandArray which means the byte size of the count. Whereas the 'count' is the number of units.

	extern size_t PLEX_expandArraySizeInt(const PLEX_EXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile);

	// returns the 'capacity size' of an expandarray which is the byte size of the capacity. Whereas the 'capacity' is the number of units.

	extern size_t PLEX_expandArrayCapacitySizeInt(const PLEX_EXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile);

	// returns the pointer to the contents of a expandArray, use sparingly.

	extern void* PLEX_expandArrayContentsInt(const PLEX_EXPANDARRAY* expandArray, const size_t errorline, const char* const errorfile);
#ifdef __cplusplus
}
#endif


#endif
