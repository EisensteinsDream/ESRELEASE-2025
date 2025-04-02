#ifndef PLEX_TERMINATE_H
#define PLEX_TERMINATE_H

// This unit contains the terminate signals for PLEX. If a program using PLEX is set up properly than these functions can set it to terminate at any point. Also, in termination, all of the proper 'end' functions are executed. This is much recommended to use with plex rather than something like 'exit' or std::exit since it's build into PLEX. Of course, these functions are not in the standard library level and will not escape from loops unless prompted within the loop.

#include "meta/cinclude.h"

// public functions ---------------------------------------------------------------------------------------------------------

#ifdef __cplusplus
extern"C"
{
#endif
// specialized functions ----------------------------------------------------------------------------------------------------

	// functions that 'ask' to quit. Essentially these will not terminate the program but put a signal up that, if intercepted, a custom quit screen can execute from within the program. (I.E. an exit screen.) However, in absence of a formal 'exit' screen these will simply terminate. They are executed when a user hits the close button or escape button and those means of exiting are enabled in config.  Clicking the close button or pressing esc or whatever does this rather than terminating.

	extern void PLEX_askQuit();

	// cancels a request to quit.

	extern void PLEX_unaskQuit();

	// signal to terminate the program without asking.

	extern void PLEX_terminate();

	// cancels a signal to terminate the program.

	extern void PLEX_unterminate();

// getters ------------------------------------------------------------------------------------------------------------------

	// returns true if the program is asking to quit

	extern bool PLEX_askingToQuit();

	// returns true if the program is terminating.

	extern bool PLEX_isTerminated();
#ifdef __cplusplus
}
#endif

#endif
