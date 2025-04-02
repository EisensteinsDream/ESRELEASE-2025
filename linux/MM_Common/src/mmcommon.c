#include "mmcommon.h"

// NOTE: global function descriptions in header.

static size_t p_cursorTex = 0;
static size_t p_cursorClickTex = 0;
static size_t p_cursorDownTex = 0;

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

// specialized functions ----------------------------------------------------------------------------------------------------

void MM_COMMON_loadMMCursor()
{
	if(!p_cursorTex) p_cursorTex = PLEX_loadTextureFromFile(64, 64, 255, 255, 255, 255, 0, MM_FILEPATH_TEX_CURSOR);
	if(!p_cursorClickTex) p_cursorClickTex = PLEX_loadTextureFromFile(64, 64, 255, 255, 255, 255, 0, MM_FILEPATH_TEX_CURSORCLICK);
	if(!p_cursorDownTex) p_cursorDownTex = PLEX_loadTextureFromFile(64, 64, 255, 255, 255, 255, 0, MM_FILEPATH_TEX_CURSORDOWN);

	if(p_cursorTex) PLEX_setCustomCursorTinted(p_cursorTex, PLEX_UNIT(1.5), PLEX_UNIT(1.5), 0, 0, 64, 64, 0, 0, 64, 64, 0, 0, 64, 64, PLEX_DEF_cursorR(), PLEX_DEF_cursorG(), PLEX_DEF_cursorB());
	if(p_cursorClickTex) PLEX_setCustomCursorClick(p_cursorClickTex, 0, 0, 64, 64);
	if(p_cursorDownTex) PLEX_setCustomCursorDown(p_cursorDownTex, 0, 0, 64, 64);
}

bool MM_COMMON_skipButton(const size_t font)
{
	return PLEX_drawButton(0, MM_LANGUAGE_SKIPSCENE, PLEX_STANDNUM_FW, PLEX_STANDNUM_FH, PLEX_WW(false) - PLEX_UNIT(5), 0, PLEX_UNIT(5), PLEX_UNIT(1.25), 255, 255, 255, 255, 0, 0, 0, 255, PLEX_UNIT(0.05), PLEX_LANGUAGE_ALPHASTRING, font, 0, 0, 0, 0, 0, false);
}

// start, update, end functions ---------------------------------------------------------------------------------------------

bool MM_COMMON_start()
{
	MM_COMMON_loadMMCursor();

	MM_COMMON_startTheme();

	return true;
}

bool MM_COMMON_update()
{
	MM_COMMON_updateTheme();

	return true;
}

void MM_COMMON_end()
{
	if(p_cursorTex) PLEX_destroyTexture(p_cursorTex);
	if(p_cursorClickTex) PLEX_destroyTexture(p_cursorClickTex);
	if(p_cursorDownTex) PLEX_destroyTexture(p_cursorDownTex);

	p_cursorTex = 0;
	p_cursorClickTex = 0;
	p_cursorDownTex = 0;

	MM_COMMON_endTheme();
}
