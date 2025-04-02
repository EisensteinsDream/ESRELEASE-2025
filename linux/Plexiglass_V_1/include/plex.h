#ifndef PLEX_H
#define PLEX_H

// This is the main PLEX header. It should include all headers necessary for all portions of PLEX and should be the only thing you need to include in any project. The way that PLEX operates is that it's a series of subsystems that have a 'start' an 'update' and an 'end'. If a 'start' or 'update' function of any of the subsystems fail then the program terminates with a fatal error. It is important to understand that PLEX is written in C and not C++.

// For this reason, PLEX is not object oriented at all (and lacks some nice things like namespaces, references, templates, etc. If you are used to C++ and wonder why I'm missing something that seems obvious in the code, that's likely why). So, the function is king, and none of the subsystems update functions will work unless in between the 'start' and 'end' calls of that particular subsystem.

// NOTE: PLEX_startPlex starts all subsystems, PLEX_updatePlex updates all subsystems, and PLEX_endPlex ends all subsystems. If PLEX_updatePlex throws a 'false' then a properly written PLEX based program ends. This is repeated below in the function notes. Individual start, update, and stop methods of subsystems never need to be called. This is important to understanding the structure of PLEX.

#include "utility/error.h"

#include "mem/memprofile.h"

#include "mem/mem.h"

#include "sound/sound.h"

#include "windowing/sprite.h"
#include "windowing/screeneffects.h"

#include "utility/fileparse.h"
#include "utility/spritetheater.h"
#include "utility/directory.h"

#include "utility/generator.h"
#include "utility/prominencemachine.h"
#include "utility/scroller.h"

// macro functions and macros -----------------------------------------------------------------------------------------------

// NO ARGUMENTS - returns bool

#define PLEX_startPlex() PLEX_startPlexInt(PLEX_LANGUAGE_TITLE, __LINE__, __FILE__) // < this allows the window title to be undefined and redefined in source that uses PLEX as a dependency.

// NO ARGUMENTS - returns bool

#define PLEX_updatePlex() PLEX_updatePlexInt(__LINE__, __FILE__)

// NO ARGUMENTS

#define PLEX_endPlex() PLEX_endPlexInt(__LINE__, __FILE__)

#ifdef __cplusplus
extern "C"
{
#endif
// start, update, end functions ---------------------------------------------------------------------------------------------

	// functions that start, update, and end the PLEX system, and all of it's subsystems. If set up properly, the start and update functions will kill the program if they return false.

	extern bool PLEX_startPlexInt(const char* const title, const size_t errorline, const char* const errorfile);
	extern bool PLEX_updatePlexInt(const size_t errorline, const char* const errorfile);
	extern void PLEX_endPlexInt(const size_t errorline, const char* const errorfile);
#ifdef __cplusplus
}
#endif

#endif
