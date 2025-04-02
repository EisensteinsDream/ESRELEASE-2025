#ifndef (PROJ)_COLLISION_H
#define (PROJ)_COLLISION_H

#include "plex.h"

#include "meta/proj_language.h"

// macro functions and macros -----------------------------------------------------------------------------------------------

// macro functions and macros go here, if they are needed.

// structs, unions, enums ---------------------------------------------------------------------------------------------------

typedef struct
{
	PLEX_RECT area;
	bool activated;
} (PROJ)_COLLISIONBOX;

// public functions ---------------------------------------------------------------------------------------------------------

#include "plex.h"
#ifdef __cplusplus
extern "C"
{
#endif
	// specialized functions ----------------------------------------------------------------------------------------------------

	extern int64_t (PROJ)_addCollisionBox(const bool ignoreCollision, const double x, const double y, const double w, const double h);

	extern void (PROJ)_addMove(const size_t index, const double x, const double y);

	extern void (PROJ)_clearCollisionBoxes();

	// activates the "Collision" system

	extern void (PROJ)_activateCollision();

	// deactivates the "Collision" system

	extern void (PROJ)_deactivateCollision();

	// start, update, end functions ---------------------------------------------------------------------------------------------

	// starts the "Collision" system (only needs to be done once). Allocating resources needed for it to run.

	extern bool (PROJ)_startCollision();

	// updates the "Collision" system, passing the time. This should only be done if active.

	extern bool (PROJ)_updateCollision(const uint64_t time);

	// ends the "Collision" system. Freeing resources.

	extern void (PROJ)_endCollision();

	// setters ------------------------------------------------------------------------------------------------------------------

	extern void (PROJ)_activateCollisionBox(const size_t index);

	extern void (PROJ)_deactivateCollisionBox(const size_t index);

	// getters ------------------------------------------------------------------------------------------------------------------

	// returns true if the "Collision" system is running

	extern bool (PROJ)_isCollisionRunning();

	// returns true if the "Collision" system is active.

	extern bool (PROJ)_isCollisionActive();

	extern (PROJ)_COLLISIONBOX (PROJ)_getCollisionBox(const int64_t index);

	extern bool (PROJ)_collisionBoxDeactivated(const size_t index);
#ifdef __cplusplus
}
#endif

#endif
