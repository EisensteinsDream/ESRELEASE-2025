#ifndef PLEX_MEM_H
#define PLEX_MEM_H

#include "mem/memprofile.h"

#include "mem/protoexpandarray.h"

#include "meta/hardlimits.h"

#include "utility/error.h"

// this unit contains the plex allocation system. The difference between PLEX's allocation and the typical 'malloc' and 'free' is that PLEX's memory allocation system preallocates and reuses allocated memory. This is NOT a garbage collector. It does not create memory leaks because it frees all memory at termination of program. However, it can create memory hangs if allocated pointers are not deallcated as none of the memory is automatically managed. Essentially, it's your typical c-style allocation but with some light safety and efficiency improvements. It also contains a system you can turn on through the config that gives a detailed memory report of all allocated not not deallocated memory with source file name and line.

// NOTE: This is a unit with a state machine affiliated therefore has a start, update, and end function. Some functions will not work if the 'start' function is not called successfully. PLEX_start, PLEX_update, and PLEX_end should call the start, update, and end functions of the state machine so they don't need to be called manually.

// macro functions and macros -----------------------------------------------------------------------------------------------

// ARGUMENTS: (const size_t size) - returns void*

#define PLEX_alloc(size) PLEX_allocInt(size, __LINE__, __FILE__)

// ARGUMENTS: (void** toFree)

#define PLEX_dealloc(toFree) PLEX_deallocInt((void**)toFree, __LINE__, __FILE__)

// NO ARGUMENTS

#define PLEX_updateMemProfile() PLEX_updateMemProfileInt(__LINE__, __FILE__)

// NO ARGUMENTS

#define PLEX_startMem() PLEX_startMemInt(__LINE__, __FILE__)

// NO ARGUMENTS

#define PLEX_updateMem() PLEX_updateMemInt(__LINE__, __FILE__)

// NO ARGUMENTS

#define PLEX_endMem() PLEX_endMemInt(__LINE__, __FILE__)

// NO ARGUMENTS

#define PLEX_unflagMemReportToFile() PLEX_unflagMemReportToFileInt(__LINE__, __FILE__)

// NO ARGUMENT

#define PLEX_unflagMemReport() PLEX_unflagMemReportInt(__LINE__, __FILE__)

// public functions ---------------------------------------------------------------------------------------------------------

#ifdef __cplusplus
extern"C"
{
#endif

// specialized functions ----------------------------------------------------------------------------------------------------

	// allocates a piece of managed memory

	extern void* PLEX_allocInt(const size_t count, const size_t errorline, const char* const errorfile);

	// deallocates a pointer to a piece of managed memory and sets it to NULL. This can handle both NULL pointers and pointers to a NULL, but if you pass anything in here that was not allocated with PLEX_alloc you might be in trouble.

	extern void PLEX_deallocInt(void** toFree, const size_t errorline, const char* const errorfile);

// start, update, end functions ---------------------------------------------------------------------------------------------

	// updates the memory profile. This is done automatically when you turn on the default so no real need to call it manually.

	extern void PLEX_updateMemProfileInt(const size_t errorline, const char* const errorfile);

	// this starts the memory state machine. If it returns false the entirety of PLEX terminates. You don't need to manually call this as it's called in PLEX_start.

	extern bool PLEX_startMemInt(const size_t errorline, const char* const errorfile);

	// this updates the memory state machine. If it returns false the entirety of PLEX terminates. You don't need to manually call this as it's called in PLEX_update.

	extern bool PLEX_updateMemInt(const size_t errorline, const char* const errorfile);

	// this end the memory state machine. You don't need to manually call this as it's called in PLEX_end.

	extern void PLEX_endMemInt(const size_t errorline, const char* const errorfile);

// setters ------------------------------------------------------------------------------------------------------------------

	// this flags to run the memory report. This is done through defaults and doesn't need to be manually called.

	extern void PLEX_unflagMemReportInt(const size_t errorline, const char* const errorfile);

	// this flags to print the memory report to a file. This is done through defaults and doesn't need to be manually called.

	extern void PLEX_unflagMemReportToFileInt(const size_t errorline, const char* const errorfile);

#ifdef __cplusplus
}
#endif

#endif
