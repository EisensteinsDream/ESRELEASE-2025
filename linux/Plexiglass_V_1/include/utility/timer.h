#ifndef PLEX_TIMER_H
#define PLEX_TIMER_H

#include "utility/fakestrings.h"

// this unit stores realtime timer information. Based on SDL_Ticks() so it has microsecond precision. Individual timers can be paused, speed up, slowed down, used in a countdown, and wound back.

// NOTE: This is an independent unit. Not a unit with an accompanying state machine. It has no 'start, update, or end' functions that need to be called to operate.

// macro functions and macros -----------------------------------------------------------------------------------------------

// ARGUMENTS: (PLEX_TIMER* timer)

#define PLEX_pause(timer) PLEX_pauseInt(timer, __LINE__, __FILE__)

// ARGUMENTS: (PLEX_TIMER* timer)

#define PLEX_unpause(timer) PLEX_unpauseInt(timer, __LINE__, __FILE__)

// ARGUMENTS: (PLEX_TIMER* timer, const uint64_t by)

#define PLEX_fastForward(timer, by) PLEX_fastForwardInt(timer, by, __LINE__, __FILE__)

// ARGUMENTS: (PLEX_TIMER* timer, const uint64_t by)

#define PLEX_rewind(timer, by) PLEX_rewindInt(timer, by, __LINE__, __FILE__)

// ARGUMENTS: (PLEX_TIMER* timer)

#define PLEX_resetTimer(timer) PLEX_resetTimerInt(timer, __LINE__, __FILE__)

// ARGUMENTS: (PLEX_TIMER* timer, const uint64_t baseTime)

#define PLEX_startTimer(timer, baseTime) PLEX_startTimerInt(timer, baseTime, __LINE__, __FILE__)

// ARGUMENTS: (PLEX_TIMER* timer, const uint64_t time)

#define PLEX_updateTimer(timer, time) PLEX_updateTimerInt(timer, time, __LINE__, __FILE__)

// ARGUMENTS: (PLEX_TIMER* timer, const double multiplier)

#define PLEX_setMultiplierTimer(timer, multiplier) PLEX_setMultiplierTimerInt(timer, multiplier, __LINE__, __FILE__)

// ARGUMENTS: (PLEX_TIMER* timer) - returns bool

#define PLEX_getPaused(timer) PLEX_getPausedInt(timer, __LINE__, __FILE__)

// ARGUMENTS: (PLEX_TIMER* timer) - returns uint64_t

#define PLEX_getTime(timer) PLEX_getTimeInt(timer, __LINE__, __FILE__)

// ARGUMENTS: (PLEX_TIMER* timer) - returns double

#define PLEX_getSecondsPassed(timer) PLEX_getSecondsPassedInt(timer, __LINE__, __FILE__)

// ARGUMENTS: (PLEX_TIMER* timer, const uint64_t from) - returns uint64_t

#define PLEX_countdownTime(timer, from) PLEX_countdownTimeInt(timer, from, __LINE__, __FILE__)

// ARGUMENTS: (PLEX_TIMER* timer) - returns PLEX_FAKESTRING_10

#define PLEX_timeString(timer) PLEX_timeStringInt(timer, __LINE__, __FILE__)

// ARGUMENTS: (PLEX_TIMER* timer, const uint64_t from) - returns PLEX_FAKESTRING_10

#define PLEX_timeCountdownString(timer, from) PLEX_timeCountdownStringInt(timer, from, __LINE__, __FILE__)

// structs, unions, enums ---------------------------------------------------------------------------------------------------

typedef struct
{
	uint64_t time, lastTime, marker;
	bool paused, unpaused, started;
	double multiplier, secondsPass;
} PLEX_TIMER;

// public functions ---------------------------------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C"
{
#endif
// specialized functions ----------------------------------------------------------------------------------------------------

	// generates a new timer, unset.

	extern PLEX_TIMER PLEX_createTimer();

	// pauses a timer

	extern void PLEX_pauseInt(PLEX_TIMER* timer, const size_t errorline, const char* const errorfile);

	// unpauses a timer

	extern void PLEX_unpauseInt(PLEX_TIMER* timer, const size_t errorline, const char* const errorfile);

	// fast forward the timer 'by' microseconds

	extern void PLEX_fastForwardInt(PLEX_TIMER* timer, const uint64_t by, const size_t errorline, const char* const errorfile);

	// rewind a timer 'by' microseconds. Stops when hits 0.

	extern void PLEX_rewindInt(PLEX_TIMER* timer, const uint64_t by, const size_t errorline, const char* const errorfile);

	// resets the timer back to 0 microseconds

	extern void PLEX_resetTimerInt(PLEX_TIMER* timer, const size_t errorline, const char* const errorfile);

// start, update, end functions ---------------------------------------------------------------------------------------------

	// starts the timer based off of 'baseTime' in microseconds. Not part of a state machine.

	extern void PLEX_startTimerInt(PLEX_TIMER* timer, const uint64_t baseTime, const size_t errorline, const char* const errorfile);

	// synchronizes the timer to a 'time' in microseconds. Not part of a state machine.

	extern void PLEX_updateTimerInt(PLEX_TIMER* timer, const uint64_t time, const size_t errorline, const char* const errorfile);

// setters ------------------------------------------------------------------------------------------------------------------

	// sets a multiplier to the timer. Typically, it is 1 or 100%. If at 3 time begins to calculate 3 times faster (or 300%). If 0.5 the time begins to calculate at half the speed.

	extern void PLEX_setMultiplierTimerInt(PLEX_TIMER* timer, const double multiplier, const size_t errorline, const char* const errorfile);

// getters ------------------------------------------------------------------------------------------------------------------

	// returns whether or not the timer is paused

	extern bool PLEX_getPausedInt(PLEX_TIMER* timer, const size_t errorline, const char* const errorfile);

	// returns the time of the timer

	extern uint64_t PLEX_getTimeInt(PLEX_TIMER* timer, const size_t errorline, const char* const errorfile);

	// get the number of seconds passed since last update of the timer

	extern double PLEX_getSecondsPassedInt(PLEX_TIMER* timer, const size_t errorline, const char* const errorfile);

	// returns the time of the timer counted down from 'from' and stops at 0

	extern uint64_t PLEX_countdownTimeInt(PLEX_TIMER* timer, const uint64_t from, const size_t errorline, const char* const errorfile);

	// returns whether or not a timer has been started

	extern bool PLEX_timerStarted(const PLEX_TIMER timer);

	// returns a string of the formatted time. Something like '382' seconds coming off as '6:22'

	extern PLEX_FAKESTRING_10 PLEX_formatStringTime(const uint64_t time);

	// returns a time string formatted from a timer

	extern PLEX_FAKESTRING_10 PLEX_timeStringInt(PLEX_TIMER* timer, const size_t errorline, const char* const errorfile);

	// returns a time string formatted from a timer counting down from 'from'

	extern PLEX_FAKESTRING_10 PLEX_timeCountdownStringInt(PLEX_TIMER* timer, const uint64_t from, const size_t errorline, const char* const errorfile);
#ifdef __cplusplus
}
#endif

#endif
