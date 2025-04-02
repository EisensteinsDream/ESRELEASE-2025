#ifndef MM_COMMON_H
#define MM_COMMON_H

#include "plex.h"

#include "meta/mmcommon_language.h"
#include "meta/mmcommon_filepaths.h"

#include "mmthemes.h"

// This is the main header for MM Common. Basically contains odds-and-ends that are useful for any of the MM based projects.

// NOTE: This is a unit with a state machine affiliated therefore has a start, update, and end function. Some functions will not work if the 'start' function is not called successfully.

// public functions ---------------------------------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C"
{
#endif

// specialized functions ----------------------------------------------------------------------------------------------------

	// loads the custom cursor intended for MM base projects. (free'd in the MM_COMMON_end() function)

	extern void MM_COMMON_loadMMCursor();

	// draws a 'skip' button in the upper right corner of the screen. Returns 'true' when button clicked.

	extern bool MM_COMMON_skipButton(const size_t font);

// start, update, end functions ---------------------------------------------------------------------------------------------

	// start, update, end for MM Common operations. Also executes the start, update, end functions of all subsystems.

	extern bool MM_COMMON_start();
	extern bool MM_COMMON_update();
	extern void MM_COMMON_end();
#ifdef __cplusplus
}
#endif

#endif
