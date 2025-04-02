#include "game.h"

// NOTE: global function descriptions in header.

// structs, unions, enums ---------------------------------------------------------------------------------------------------

// structs, unions, and enums go here if they are needed.

// static values ------------------------------------------------------------------------------------------------------------

// a boolean that decides whether or not the quit screen should be shown

static bool p_quitPrompt = false;

// textures are represented as index numbers that are typically stored in size_t variables. Later versions may have a unique type for this.

static size_t p_font = 0;

// static functions ---------------------------------------------------------------------------------------------------------

static bool p_quitScreen()
{
	if(!p_quitPrompt)
	{
		PLEX_unaskQuit();
		p_quitPrompt = true;
	}else{
		// attempting to exit the program a second time is considered 'yes' on the quit screen

		if(PLEX_askingToQuit()) return true;
	}

	PLEX_drawRect(0, 0, 0, PLEX_WW(true), PLEX_WH(true), 255, 255, 255, 255, PLEX_UNIT(0.1), true);

	PLEX_drawTextBoxTinted(1, "Do you wish to quit the game?", PLEX_STANDNUM_FW, PLEX_STANDNUM_FH, 255, 255, 255, 255, 0, 0, 0, 255, PLEX_UNIT(1), PLEX_UNIT(2), PLEX_WW(true) - PLEX_UNIT(2), PLEX_WH(true), PLEX_UNIT(2), PLEX_UNIT(3), 0.1, 0.1, 0.9, 0.8, 0, PLEX_LANGUAGE_ALPHASTRING, p_font, 0, 0, 0, 0, 0, 0.1, true);

	if(PLEX_drawButton(1, "Return", PLEX_STANDNUM_FW, PLEX_STANDNUM_FH, PLEX_UNIT(2), PLEX_WH(true) - PLEX_UNIT(3), PLEX_WW(true)/2 - PLEX_UNIT(2), PLEX_UNIT(2), 255, 255, 255, 255, 0, 0, 0, 255, PLEX_UNIT(0.1), PLEX_LANGUAGE_ALPHASTRING, p_font, 0, 0, 0, 0, 0, true)) p_quitPrompt = false;

	if(PLEX_drawButton(1, "End Game", PLEX_STANDNUM_FW, PLEX_STANDNUM_FH, PLEX_WW(true)/2 + PLEX_UNIT(1), PLEX_WH(true) - PLEX_UNIT(3), PLEX_WW(true)/2 - PLEX_UNIT(2), PLEX_UNIT(2), 255, 255, 255, 255, 0, 0, 0, 255, PLEX_UNIT(0.1), PLEX_LANGUAGE_ALPHASTRING, p_font, 0, 0, 0, 0, 0, true)) return true;

	return false;
}

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

// specialized functions ----------------------------------------------------------------------------------------------------

// Here is where you put functions that are specific to this unit.

// start, update, end functions ---------------------------------------------------------------------------------------------

bool (PROJ)_startGame()
{
	if(!PLEX_startPlex())
	{
		PLEX_error(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_START, PLEX_ERROR_SEVERITY_FATAL, PLEX_LANGUAGE_GAME);
		return false;
	}

	// loads the generic font either from the 'resources/font.png' or a headerless texture 'headerlesstex/font' which is generated on first load if all goes well.

	p_font = PLEX_loadTextureFromFileOrHeaderless(128, 128, 255, 255, 255, 255, 0, PLEX_RECDIRECTORY "font.png", PLEX_HEADERLESSDIRECTORY "font");

	// 0 is the index for a 'NULL texture'. So if the previous line fails to load the font it returns a 0. This catches that error.

	if(!p_font)
	{
		PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_BADOPERATION, PLEX_ERROR_SEVERITY_MINOR, PLEX_LANGUAGE_OPGAMESTART, PLEX_LANGUAGE_FONTERROR);
		return false;
	}

	p_quitPrompt = false;

	return true;
}

bool (PROJ)_updateGame()
{
	// const uint64_t time = PLEX_getGameTime(); // < uncomment when needed

	if(!PLEX_updatePlex())
	{
		PLEX_error(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_UPDATE, PLEX_ERROR_SEVERITY_FATAL, PLEX_LANGUAGE_GAME);
		return false;
	}

	if(PLEX_askingToQuit() || p_quitPrompt)
	{
		if(p_quitScreen()) PLEX_terminate();
	}else{
		// update everything here //
	}

	return !PLEX_isTerminated();
}

void (PROJ)_endGame()
{
	PLEX_destroyTexture(p_font);

	PLEX_endPlex();

	p_font = 0;
}

// setters ------------------------------------------------------------------------------------------------------------------

// any functions that set internal values go here.

// getters ------------------------------------------------------------------------------------------------------------------

// any functions that get internal values go here.
