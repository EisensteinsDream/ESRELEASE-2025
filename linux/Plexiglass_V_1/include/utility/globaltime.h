#ifndef PLEX_GLOBALTIME_H
#define PLEX_GLOBALTIME_H

#include "utility/timer.h"

// This unit keeps track of the total time the program is running or 'gametime'. It also allows you to access 'gametime' in a way which ignores all of the times game time is paused if you need that, too.

// NOTE: This is a unit with a state machine affiliated therefore has a start, update, and end function. Some functions will not work if the 'start' function is not called successfully. PLEX_start, PLEX_update, and PLEX_end should call the start, update, and end functions of the state machine so they don't need to be called manually.

// macro functions and macros -----------------------------------------------------------------------------------------------

// NO ARGUMENTS

#define PLEX_pauseGameTime() PLEX_pauseGameTimeInt(__LINE__, __FILE__)

// NO ARGUMENTS

#define PLEX_unpauseGameTime() PLEX_unpauseGameTimeInt(__LINE__, __FILE__)

// NO ARGUMENTS - returns bool

#define PLEX_startGlobalTime() PLEX_startGlobalTimeInt(__LINE__, __FILE__)

// NO ARGUMENTS - returns bool

#define PLEX_updateGlobalTime() PLEX_updateGlobalTimeInt(__LINE__, __FILE__)

// NO ARGUMENTS

#define PLEX_endGlobalTime() PLEX_endGlobalTimeInt(__LINE__, __FILE__)

// NO ARGUMENTS - returns uint64_t

#define PLEX_getGameTime() PLEX_getGameTimeInt(__LINE__, __FILE__)

// NO ARGUMENTS - returns double

#define PLEX_getGameSecondsPassed() PLEX_getGameSecondsPassedInt(__LINE__, __FILE__)

// NO ARGUMENTS - returns bool

#define PLEX_getGameTimePaused() PLEX_getGameTimePausedInt(__LINE__, __FILE__)

// NO ARGUMENTS - const char*

#define PLEX_getGameTimeString() PLEX_getGameTimeStringInt(__LINE__, __FILE__)

// NO ARGUMENTS - returns uint64_t

#define PLEX_getNoPauseTime() PLEX_getNoPauseTimeInt(__LINE__, __FILE__)

// NO ARGUMENTS - returns double

#define PLEX_getNoPauseGameSecondsPassed() PLEX_getNoPauseGameSecondsPassedInt(__LINE__, __FILE__)

// NO ARGUMENTS - const char*

#define PLEX_getNoPauseGameTimeString() PLEX_getNoPauseGameTimeStringInt(__LINE__, __FILE__)

// public functions ---------------------------------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C"
{
#endif
// specialized functions ----------------------------------------------------------------------------------------------------

	// pauses the main game time (does this automatically if the space key is pressed and is not paused; the space key for un/pause can be disabled)

	extern void PLEX_pauseGameTimeInt(const size_t errorline, const char* const errorfile);

	// unpauses the main game time (also does this automatically if the space key is pressed and is paused; the space key for un/pause can be disabled)

	extern void PLEX_unpauseGameTimeInt(const size_t errorline, const char* const errorfile);

// start, update, end functions ---------------------------------------------------------------------------------------------

	// starts the global time state machine. Returns false on failure. Is called in PLEX_start and does not need to be manually called. Terminates the program if it fails in PLEX_start.

	extern bool PLEX_startGlobalTimeInt(const size_t errorline, const char* const errorfile);

	// updates the global time state machine. Returns false on failure. Is called in PLEX_update and does not need to be manually called. Terminates the program if it fails in PLEX_update.

	extern bool PLEX_updateGlobalTimeInt(const size_t errorline, const char* const errorfile);

	// ends the global time state machine. Is called in PLEX_end and does not need to be manually called.

	extern void PLEX_endGlobalTimeInt(const size_t errorline, const char* const errorfile);

// getters ------------------------------------------------------------------------------------------------------------------

	// returns the total game time as microseconds

	extern uint64_t PLEX_getGameTimeInt(const size_t errorline, const char* const errorfile);

	// returns the seconds passed since the game time was last updated in decimal form

	extern double PLEX_getGameSecondsPassedInt(const size_t errorline, const char* const errorfile);

	// returns true if the game time is paused

	extern bool PLEX_getGameTimePausedInt(const size_t errorline, const char* const errorfile);

	// returns a string in the 00:00 format for the gametime

	extern const char* PLEX_getGameTimeStringInt(const size_t errorline, const char* const errorfile);

	// returns the game time in total but ignores the times in which the game is paused

	extern uint64_t PLEX_getNoPauseTimeInt(const size_t errorline, const char* const errorfile);

	// returns the number of seconds since last time the game time was updated but ignores the times which the game is paused

	extern double PLEX_getNoPauseGameSecondsPassedInt(const size_t errorline, const char* const errorfile);

	// returns a string in the 00:00 format for the gametime but ignoring when the game time is paused

	extern const char* PLEX_getNoPauseGameTimeStringInt(const size_t errorline, const char* const errorfile);
#ifdef __cplusplus
}
#endif

#endif
