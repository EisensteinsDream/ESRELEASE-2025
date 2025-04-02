#include "utility/globaltime.h"

// NOTE: global function descriptions in header.

// static values ------------------------------------------------------------------------------------------------------------

static bool p_running = false;

static PLEX_TIMER p_gameTime, p_noPauseTime;

static PLEX_FAKESTRING_10 p_gameTimeString, p_gameNoPauseTimeString;

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

// specialized functions ----------------------------------------------------------------------------------------------------

void PLEX_pauseGameTimeInt(const size_t errorline, const char* const errorfile)
{
	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_GLOBALTIME, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_GLOBALTIME_ONPAUSE, errorline, errorfile);
		return;
	}

	PLEX_pause(&p_gameTime);
}

void PLEX_unpauseGameTimeInt(const size_t errorline, const char* const errorfile)
{
	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_GLOBALTIME, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_GLOBALTIME_ONUNPAUSE, errorline, errorfile);
		return;
	}

	PLEX_unpause(&p_gameTime);
}

// start, update, end functions ---------------------------------------------------------------------------------------------

bool PLEX_startGlobalTimeInt(const size_t errorline, const char* const errorfile)
{
	uint64_t ticks = 0;

	if(p_running)
	{
		PLEX_errorInt0A(PLEX_ERROR_CATEGORY_GLOBALTIME, PLEX_ERROR_DOUBLESTART, PLEX_ERROR_SEVERITY_BADSTYLE, errorline, errorfile);
		return true;
	}

	if(SDL_InitSubSystem(SDL_INIT_TIMER))
	{
		PLEX_errorSDLInt(PLEX_ERROR_SEVERITY_FATAL, errorline, errorfile);
		return false; // remember 0 == success with this method
	}

	ticks = SDL_GetTicks();

	p_gameTime = PLEX_createTimer();
	p_noPauseTime = PLEX_createTimer();

	PLEX_startTimerInt(&p_gameTime, ticks, errorline, errorfile);
	PLEX_startTimerInt(&p_noPauseTime, ticks, errorline, errorfile);

	p_running = true;

	return true;
}

bool PLEX_updateGlobalTimeInt(const size_t errorline, const char* const errorfile)
{
	uint64_t ticks = 0;

	if(!p_running)
	{
		PLEX_errorInt0A(PLEX_ERROR_CATEGORY_GLOBALTIME, PLEX_ERROR_UPDATEBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, errorline, errorfile);
		return false;
	}

	ticks = SDL_GetTicks();

	PLEX_updateTimerInt(&p_gameTime, ticks, errorline, errorfile);
	PLEX_updateTimerInt(&p_noPauseTime, ticks, errorline, errorfile);

	return true;
}

void PLEX_endGlobalTimeInt(const size_t errorline, const char* const errorfile)
{
	if(!p_running)
	{
		PLEX_errorInt0A(PLEX_ERROR_CATEGORY_GLOBALTIME, PLEX_ERROR_ENDBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, errorline, errorfile);
		return;
	}

	SDL_QuitSubSystem(SDL_INIT_TIMER);

	p_running = false;
}

// getters ------------------------------------------------------------------------------------------------------------------

uint64_t PLEX_getGameTimeInt(const size_t errorline, const char* const errorfile)
{
	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_GLOBALTIME, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_GLOBALTIME_ONGET, errorline, errorfile);
		return 0;
	}

	return PLEX_getTimeInt(&p_gameTime, errorline, errorfile);
}

double PLEX_getGameSecondsPassedInt(const size_t errorline, const char* const errorfile)
{
	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_GLOBALTIME, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_GLOBALTIME_ONGETSECONDS, errorline, errorfile);
		return 0;
	}

	return PLEX_getSecondsPassedInt(&p_gameTime, errorline, errorfile);
}

bool PLEX_getGameTimePausedInt(const size_t errorline, const char* const errorfile)
{
	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_GLOBALTIME, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_GLOBALTIME_ONGETUNPAUSE, errorline, errorfile);
		return 0;
	}

	return PLEX_getPausedInt(&p_gameTime, errorline, errorfile);
}

const char* PLEX_getGameTimeStringInt(const size_t errorline, const char* const errorfile)
{
	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_GLOBALTIME, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_GLOBALTIME_ONGETSTRING, errorline, errorfile);
		return "";
	}

	p_gameTimeString = PLEX_timeStringInt(&p_gameTime, errorline, errorfile);

	return PLEX_fts(p_gameTimeString);
}

uint64_t PLEX_getNoPauseTimeInt(const size_t errorline, const char* const errorfile)
{
	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_GLOBALTIME, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_GLOBALTIME_ONGETNOPAUSE, errorline, errorfile);
		return 0;
	}

	return PLEX_getTimeInt(&p_noPauseTime, errorline, errorfile);
}

double PLEX_getNoPauseGameSecondsPassedInt(const size_t errorline, const char* const errorfile)
{
	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_GLOBALTIME, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_GLOBALTIME_ONGETSECONDSNOPAUSE, errorline, errorfile);
		return 0;
	}

	return PLEX_getSecondsPassedInt(&p_noPauseTime, errorline, errorfile);
}

const char* PLEX_getNoPauseGameTimeStringInt(const size_t errorline, const char* const errorfile)
{
	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_GLOBALTIME, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_GLOBALTIME_ONGETNOPAUSESTRING, errorline, errorfile);
		return "";
	}

	p_gameNoPauseTimeString = PLEX_timeStringInt(&p_noPauseTime, errorline, errorfile);

	return PLEX_fts(p_gameNoPauseTimeString);
}
