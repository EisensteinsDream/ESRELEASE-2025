#include "terminate.h"

// NOTE: global function descriptions in header.

// static variables

static bool p_terminated = false;
static bool p_askQuit = false;

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

void PLEX_askQuit(){ p_askQuit = true; }
void PLEX_unaskQuit(){ p_askQuit = false; }
bool PLEX_askingToQuit(){ return p_askQuit; }

void PLEX_terminate(){ p_terminated = true; }
void PLEX_unterminate(){ p_terminated = false; }
bool PLEX_isTerminated(){ return p_terminated; }
