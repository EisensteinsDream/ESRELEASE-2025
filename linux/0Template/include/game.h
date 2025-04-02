#ifndef (PROJ)_GAME_H
#define (PROJ)_GAME_H

#include "plex.h"

#include "meta/proj_language.h"

// NOTE: this unit is designed basically as your entry point. You can interchangeably put stuff in main.c or in game.c. I catch myself doing that. It is recommended, however, for organizational sake to simply let main.c run the start, update, and end functions of game.c. Then to put all the start, update, and end functions of all subsystems inside of game's start, update, and end functions. A copy of a template basicsystem header and source is in the 'codeexamples' directory. Not strictly required to make a PLEX based project but highly recommended you do things that way.

// macro functions and macros -----------------------------------------------------------------------------------------------

// macro functions and macros go here, if they are needed.

// structs, unions, enums ---------------------------------------------------------------------------------------------------

// structs, unions, and enums go here if they are needed.

// public functions ---------------------------------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C"
{
#endif
// specialized functions ----------------------------------------------------------------------------------------------------

	// Here is where you put functions that are specific to this unit.

// start, update, end functions ---------------------------------------------------------------------------------------------

	// starts game - should start all neccessary subsystems inc. PLEX

	extern bool (PROJ)_startGame();

	// updates game - should update all neccessary subsystems inc. PLEX

	extern bool (PROJ)_updateGame();

	// ends game - should end all neccessary subsystems inc. PLEX

	extern void (PROJ)_endGame();

// setters ------------------------------------------------------------------------------------------------------------------

	// any functions that set internal values go here.

// getters ------------------------------------------------------------------------------------------------------------------

	// any functions that get internal values go here.

#ifdef __cplusplus
}
#endif

#endif
