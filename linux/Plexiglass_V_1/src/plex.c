#include "plex.h"

// NOTE: global function descriptions in header.

static bool p_running = false;

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

// start, update, end functions ---------------------------------------------------------------------------------------------

bool PLEX_startPlexInt(const char* const title, const size_t errorline, const char* const errorfile)
{
	if(p_running) return true;

	if(PLEX_CORE_OS == PLEX_CORE_NOOS) // must be first
	{
		printf("%s" PLEX_NL, PLEX_ERRORMESS_ERROR_SYSTEMFAIL_NOOS);
		return false;
	}

	if(!PLEX_startErrorSystem()) // must be second
	{
		printf("%s" PLEX_NL, PLEX_ERRORMESS_ERROR_SYSTEMFAIL_INIT);
		return false;
	}

	if(!PLEX_startMem()) // must be third
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_START, PLEX_ERROR_START, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SUBSYSTEM_MEMORY, errorline, errorfile);
		return false;
	}

	PLEX_startMath(); // < cannot possibly fail

	if(!PLEX_startDefaultsInt(errorline, errorfile))
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_START, PLEX_ERROR_START, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SUBSYSTEM_DEFAULT, errorline, errorfile);
		return false;
	}

	if(!PLEX_startGlobalTimeInt(errorline, errorfile))
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_START, PLEX_ERROR_START, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SUBSYSTEM_TIME, errorline, errorfile);
		PLEX_errorSDLInt(PLEX_ERROR_SEVERITY_FATAL, errorline, errorfile);
		return false;
	}

	if(!PLEX_startWindowInt(title, PLEX_DEF_width(), PLEX_DEF_height(), PLEX_STARTING_ASPECTRATIO, errorline, errorfile))
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_START, PLEX_ERROR_START, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SUBSYSTEM_WINDOW, errorline, errorfile);
		PLEX_errorSDLInt(PLEX_ERROR_SEVERITY_FATAL, errorline, errorfile);
		return false;
	}

	if(!PLEX_startTexturesInt(errorline, errorfile))
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_START, PLEX_ERROR_START, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SUBSYSTEM_TEXTURE, errorline, errorfile);
		PLEX_errorSDLInt(PLEX_ERROR_SEVERITY_FATAL, errorline, errorfile);
		return false;
	}

	if(!PLEX_startGraphicsInt(errorline, errorfile))
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_START, PLEX_ERROR_START, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SUBSYSTEM_GRAPHICS, errorline, errorfile);
		PLEX_errorSDLInt(PLEX_ERROR_SEVERITY_FATAL, errorline, errorfile);
		return false;
	}

	if(!PLEX_startInputInt(errorline, errorfile))
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_START, PLEX_ERROR_START, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SUBSYSTEM_INPUT, errorline, errorfile);
		PLEX_errorSDLInt(PLEX_ERROR_SEVERITY_FATAL, errorline, errorfile);
		return false;
	}

	if(!PLEX_startSoundInt(errorline, errorfile))
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_START, PLEX_ERROR_START, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SUBSYSTEM_SOUND, errorline, errorfile);
		return false;
	}

	if(!PLEX_startScreenEffectsInt(PLEX_getGameTimeInt(errorline, errorfile), errorline, errorfile))
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_START, PLEX_ERROR_START, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SUBSYSTEM_SCREENEFFECTS, errorline, errorfile);
		return false;
	}

	p_running = true;

	return true;
}

bool PLEX_updatePlexInt(const size_t errorline, const char* const errorfile)
{
	if(!PLEX_updateErrorSystem())
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_UPDATE, PLEX_ERROR_UPDATE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SUBSYSTEM_ERROR, errorline, errorfile);
		return false;
	}

	if(!PLEX_updateMem())
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_UPDATE, PLEX_ERROR_UPDATE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SUBSYSTEM_MEMORY, errorline, errorfile);
		return false;
	}

	if(!PLEX_updateGlobalTime())
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_UPDATE, PLEX_ERROR_UPDATE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SUBSYSTEM_TIME, errorline, errorfile);
		return false;
	}

	if(!PLEX_updateWindow())
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_UPDATE, PLEX_ERROR_UPDATE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SUBSYSTEM_WINDOW, errorline, errorfile);
		return false;
	}

	if(!PLEX_updateInput())
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_UPDATE, PLEX_ERROR_UPDATE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SUBSYSTEM_INPUT, errorline, errorfile);
		return false;
	}

	// KEEP BEFORE GRAPHICS UPDATE //
	if(!PLEX_updateScreenEffects(PLEX_getGameTimeInt(errorline, errorfile)))
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_UPDATE, PLEX_ERROR_UPDATE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SUBSYSTEM_SCREENEFFECTS, errorline, errorfile);
		return false;
	}

	if(!PLEX_updateTexturesInt(errorline, errorfile))
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_UPDATE, PLEX_ERROR_UPDATE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SUBSYSTEM_TEXTURE, errorline, errorfile);
		return false;
	}

	if(!PLEX_updateGraphics(PLEX_getWindowContents(), PLEX_WW(false), PLEX_WH(false)))
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_UPDATE, PLEX_ERROR_UPDATE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SUBSYSTEM_GRAPHICS, errorline, errorfile);
		return false;
	}

	if(!PLEX_updateSound())
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_UPDATE, PLEX_ERROR_UPDATE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SUBSYSTEM_SOUND, errorline, errorfile);
		return false;
	}

	return true;
}

void PLEX_endPlexInt(const size_t errorline, const char* const errorfile)
{
	if(!PLEX_isSpriteTheaterOver()) PLEX_endSpriteTheaterInt(errorline, errorfile);

	PLEX_endScreenEffectsInt(errorline, errorfile);
	PLEX_endSoundInt(errorline, errorfile);
	PLEX_endGraphicsInt(errorline, errorfile);
	PLEX_endInputInt(errorline, errorfile);
	PLEX_endTexturesInt(errorline, errorfile);
	PLEX_endWindowInt(errorline, errorfile);
	PLEX_endGlobalTimeInt(errorline, errorfile);
	PLEX_endDefaultsInt(errorline, errorfile);
	PLEX_endMemInt(errorline, errorfile); // must be second to last
	PLEX_endErrorSystem();

	SDL_Quit();
}
