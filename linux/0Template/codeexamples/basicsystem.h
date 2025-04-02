#ifndef (PROJ)_BASICSYSTEM_H
#define (PROJ)_BASICSYSTEM_H

#include "plex.h"

#include "meta/proj_language.h"

// NOTE: This is designed to be copy/pasted to create 'systems'. PLEX and all projects I build off of PLEX run in this way. There is no requirement that projects built off PLEX operate in this way, BUT it's much easier and more conducive. A system basically has two states: running and not running. Also: active and not active. Resources are expected to be allocated in the start phase and deallocated in the end phase. The update phase should only run if the system is active. Copy this and just replace (System Name) with whatever system you want. It should be cased like this: for graphics make 'begin(System Name)' 'beginGraphics'. Also replacing (PROJ) with a project namespace. This is not set up for C++ namespaces so the name of the function will do. There is also a correlating basicsystem.c in this directory where the same operation can be applied.

// macro functions and macros -----------------------------------------------------------------------------------------------

// macro functions and macros go here, if they are needed.

// structs, unions, enums ---------------------------------------------------------------------------------------------------

// structs, unions, and enums go here if they are needed.

// public functions ---------------------------------------------------------------------------------------------------------

#include "plex.h"
#ifdef __cplusplus
extern "C"
{
#endif
// specialized functions ----------------------------------------------------------------------------------------------------

	// activates the "(System Name)" system

	extern void (PROJ)_activate(System Name)();

	// deactivates the "(System Name)" system

	extern void (PROJ)_deactivate(System Name)();

// start, update, end functions ---------------------------------------------------------------------------------------------

	// starts the "(System Name)" system (only needs to be done once). Allocating resources needed for it to run.

	extern bool (PROJ)_start(System Name)();

	// updates the "(System Name)" system, passing the time. This should only be done if active.

	extern bool (PROJ)_update(System Name)(const uint64_t time);

	// ends the "(System Name)" system. Freeing resources.

	extern void (PROJ)_end(System Name)();

// setters ------------------------------------------------------------------------------------------------------------------

// any functions that set internal values go here.

// getters ------------------------------------------------------------------------------------------------------------------

	// returns true if the "(System Name)" system is running

	extern bool (PROJ)_is(System Name)Running();

	// returns true if the "(System Name)" system is active.

	extern bool (PROJ)_is(System Name)Active();
#ifdef __cplusplus
}
#endif

#endif
