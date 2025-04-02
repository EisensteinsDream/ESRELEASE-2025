#include "utility/timer.h"

// NOTE: global function descriptions in header.

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

// specialized functions ----------------------------------------------------------------------------------------------------

PLEX_TIMER PLEX_createTimer()
{
	PLEX_TIMER ret;

	memset(&ret, 0, sizeof(ret));

	ret.unpaused = true;

	return ret;
}

void PLEX_pauseInt(PLEX_TIMER* timer, const size_t errorline, const char* const errorfile)
{
	if(timer == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_TIMING, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_TIME_ONRPAUSE, PLEX_ERRORMESS_TIME_TIMER, errorline, errorfile);
		return;
	}

	timer->paused = true;
}

void PLEX_unpauseInt(PLEX_TIMER* timer, const size_t errorline, const char* const errorfile)
{
	if(timer == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_TIMING, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_TIME_ONRUNPAUSE, PLEX_ERRORMESS_TIME_TIMER, errorline, errorfile);
		return;
	}

	timer->unpaused = true;
}

void PLEX_fastForwardInt(PLEX_TIMER* timer, const uint64_t by, const size_t errorline, const char* const errorfile)
{
	if(timer == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_TIMING, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_TIME_ONRFASTFORWARD, PLEX_ERRORMESS_TIME_TIMER, errorline, errorfile);
		return;
	}

	timer->time += by;
}

void PLEX_rewindInt(PLEX_TIMER* timer, const uint64_t by, const size_t errorline, const char* const errorfile)
{
	if(timer == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_TIMING, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_TIME_ONREWIND, PLEX_ERRORMESS_TIME_TIMER, errorline, errorfile);
		return;
	}

	if(by < timer->time) timer->time -= by;
	else timer->time = 0;
}

void PLEX_resetTimerInt(PLEX_TIMER* timer, const size_t errorline, const char* const errorfile)
{
	if(timer == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_TIMING, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_TIME_ONRESET, PLEX_ERRORMESS_TIME_TIMER, errorline, errorfile);
		return;
	}

	timer->time = 0;
}

// start, update, end functions ---------------------------------------------------------------------------------------------

void PLEX_startTimerInt(PLEX_TIMER* timer, const uint64_t baseTime, const size_t errorline, const char* const errorfile)
{
	if(timer == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_TIMING, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_TIME_ONRSTART, PLEX_ERRORMESS_TIME_TIMER, errorline, errorfile);
		return;
	}

	timer->time = 0;
	timer->lastTime = 0;
	timer->secondsPass = 0;
	timer->marker = baseTime;
	timer->paused = false;
	timer->unpaused = true;
	timer->multiplier = 1;
	timer->started = true;
}

void PLEX_updateTimerInt(PLEX_TIMER* timer, const uint64_t time, const size_t errorline, const char* const errorfile)
{
	uint64_t newTime = 0;

	if(timer == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_TIMING, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_TIME_ONUPDATING, PLEX_ERRORMESS_TIME_TIMER, errorline, errorfile);
		return;
	}

	if(timer->paused)
	{
		timer->marker = time;

		if(timer->unpaused) // < this is here to ensure that the marker is set to time when unpaused
		{
			timer->paused = false;
			timer->unpaused = false;
		}

		timer->secondsPass = 0;

		return;
	}

	if(time < timer->marker) timer->marker = time;

	newTime = (time - timer->marker) * timer->multiplier;

	timer->lastTime = timer->time;
	timer->time += newTime;
	timer->secondsPass = newTime/1000.0;
	timer->marker = time;
	timer->unpaused = false;
}

// setters ------------------------------------------------------------------------------------------------------------------

void PLEX_setMultiplierTimerInt(PLEX_TIMER* timer, const double multiplier, const size_t errorline, const char* const errorfile)
{
	if(timer == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_TIMING, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_TIME_ONMULTIPLIER, PLEX_ERRORMESS_TIME_TIMER, errorline, errorfile);
		return;
	}

	if(multiplier > 0) timer->multiplier = multiplier;
	else
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_TIMING, PLEX_ERROR_ZEROVALUE, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_TIME_ONMULTIPLIER, PLEX_ERRORMESS_TIME_MULTIPLIER, errorline, errorfile);
	}
}

// getters ------------------------------------------------------------------------------------------------------------------

bool PLEX_getPausedInt(PLEX_TIMER* timer, const size_t errorline, const char* const errorfile)
{
	if(timer == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_TIMING, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_TIME_ONPAUSING, PLEX_ERRORMESS_TIME_TIMER, errorline, errorfile);
		return false;
	}

	return timer->paused;
}

uint64_t PLEX_getTimeInt(PLEX_TIMER* timer, const size_t errorline, const char* const errorfile)
{
	if(timer == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_TIMING, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_TIME_TIME, PLEX_ERRORMESS_TIME_TIMER, errorline, errorfile);
		return 0;
	}

	return timer->time;
}

double PLEX_getSecondsPassedInt(PLEX_TIMER* timer, const size_t errorline, const char* const errorfile)
{
	if(timer == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_TIMING, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_TIME_ONGETSECONDS, PLEX_ERRORMESS_TIME_TIMER, errorline, errorfile);
		return false;
	}

	return timer->secondsPass;
}

uint64_t PLEX_countdownTimeInt(PLEX_TIMER* timer, const uint64_t from, const size_t errorline, const char* const errorfile)
{
	if(timer == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_TIMING, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_TIME_COUNTDOWN, PLEX_ERRORMESS_TIME_TIMER, errorline, errorfile);
		return 0;
	}

	if(from < timer->time) return 0; // < no error

	return from - timer->time;
}

bool PLEX_timerStarted(const PLEX_TIMER timer){ return timer.started; }

PLEX_FAKESTRING_10 PLEX_formatStringTime(const uint64_t time)
{
	const uint64_t rawSeconds = time/1000;

	const uint8_t seconds = rawSeconds % 60;
	const uint8_t minutes = rawSeconds/60 % 60;
	const uint8_t hours = rawSeconds/3600 % 99;

	const uint8_t sdigit1 = seconds/10;
	const uint8_t sdigit2 = seconds % 10;

	const uint8_t mdigit1 = minutes/10;
	const uint8_t mdigit2 = minutes % 10;

	const uint8_t hdigit1 = hours/10;
	const uint8_t hdigit2 = hours % 10;

	PLEX_FAKESTRING_10 ret;

	size_t it = 0;

	uint8_t* edit = (uint8_t*)&ret;

	if(rawSeconds >= 3600)
	{
		edit[it] = '0' + hdigit1;
		it++;
		edit[it] = '0' + hdigit2;
		it++;
		edit[it] = ':';
		it++;
	}

	if(rawSeconds >= 60)
	{
		edit[it] = '0' + mdigit1;
		it++;
		edit[it] = '0' + mdigit2;
		it++;
		edit[it] = ':';
		it++;
	}

	edit[it] = '0' + sdigit1;
	it++;
	edit[it] = '0' + sdigit2;
	it++;
	edit[it] = '\0';

	return ret;
}

PLEX_FAKESTRING_10 PLEX_timeStringInt(PLEX_TIMER* timer, const size_t errorline, const char* const errorfile)
{
	if(timer == NULL)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_TIMING, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_TIME_STRING, errorline, errorfile);
		return PLEX_blankString10();
	}

	return PLEX_formatStringTime(timer->time);
}

PLEX_FAKESTRING_10 PLEX_timeCountdownStringInt(PLEX_TIMER* timer, const uint64_t from, const size_t errorline, const char* const errorfile)
{
	if(timer == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_TIMING, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_TIME_COUNTDOWNSTRING, PLEX_ERRORMESS_TIME_TIMER, errorline, errorfile);
		return PLEX_blankString10();
	}

	return PLEX_formatStringTime(PLEX_countdownTime(timer, from));
}
