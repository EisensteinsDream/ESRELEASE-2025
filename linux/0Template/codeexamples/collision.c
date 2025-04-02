#include "collision/collision.h"

// NOTE: global function descriptions in header.

// structs, unions, enums ---------------------------------------------------------------------------------------------------

typedef struct
{
	size_t index;
	PLEX_POINT distance;
} P_MOVECOLLISION;

// static values ------------------------------------------------------------------------------------------------------------

static PLEX_EXPANDARRAY* p_cBoxes = NULL;
static PLEX_EXPANDARRAY* p_moves = NULL;

static bool p_collisionInit = false;

static int64_t p_playerColIndex = -1;
static int64_t p_obstColIndex = -1;

static bool p_active = false;
static bool p_running = false;

// static functions ---------------------------------------------------------------------------------------------------------

static int64_t p_checkCollision(const int64_t ignore, const (PROJ)_COLLISIONBOX with)
{
	size_t count = 0;

	if(with.activated) return -1;

	count = PLEX_expandArrayCount(p_cBoxes);

	for(size_t l = 0; l < count; ++l)
	{
		(PROJ)_COLLISIONBOX* box = NULL;

		if(l == ignore) continue; // < skips the index intended to be ignored

		box = PLEX_getExpandArrayEntry(l, p_cBoxes);

		if(box == NULL)
		{
			PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_IMPOSSIBLE, "Collision System", "Collision Boxes");
			return -1;
		}

		if(!box->activated) continue;

		if(PLEX_rectCollisionNoMove(box->area, with.area)) return l;
	}

	return -1;
}

static void p_startPlayer()
{
	const PLEX_DIMENS playerDimens = PLEX_convDimens(1.5, 1.5);

	p_playerColIndex = (PROJ)_addCollisionBox(false, PLEX_WIDTHUNITMAX(false)/2.0 - playerDimens.w/2.0, PLEX_HEIGHTUNITMAX()/2.0 - playerDimens.h/2.0, playerDimens.w, playerDimens.h);

	if(p_playerColIndex == -1)
	{
		PLEX_error(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_BADOPERATION, PLEX_ERROR_SEVERITY_MINOR, "Failed to create player collision block");
		return; // < redundant but put in case you put anything after this for any reason.
	}
}

static void p_startObstruction()
{
	const PLEX_DIMENS obstDimens = PLEX_convDimens(4, 4);

	p_obstColIndex = (PROJ)_addCollisionBox(false, PLEX_WIDTHUNITMAX()/4.0 - obstDimens.w/2.0, PLEX_HEIGHTUNITMAX()/4.0 - obstDimens.h/2.0, obstDimens.w, obstDimens.h);

	if(p_obstColIndex == -1)
	{
		PLEX_error(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_BADOPERATION, PLEX_ERROR_SEVERITY_MINOR, "Failed to create obstruction collision block");
		return; // < redundant but put in case you put anything after this for any reason.
	}
}

static void p_drawPlayer()
{
	const (PROJ)_COLLISIONBOX playerBox = (PROJ)_getCollisionBox(p_playerColIndex);

	PLEX_fillRect(0, PLEX_UNIT(playerBox.area.origin.x), PLEX_UNIT(playerBox.area.origin.y), PLEX_UNIT(playerBox.area.dimens.w), PLEX_UNIT(playerBox.area.dimens.h), 255, 0, 0, 255, true);
}

static void p_drawObstruction()
{
	const (PROJ)_COLLISIONBOX obstBox = (PROJ)_getCollisionBox(p_obstColIndex);

	PLEX_fillRect(0, PLEX_UNIT(obstBox.area.origin.x), PLEX_UNIT(obstBox.area.origin.y), PLEX_UNIT(obstBox.area.dimens.w), PLEX_UNIT(obstBox.area.dimens.h), 0, 0, 255, 255, true);
}

static void p_movePlayer()
{
	const double speed = 3;
	const double velocity = PLEX_getGameSecondsPassed() * speed;

	PLEX_POINT distance = PLEX_convPoint(0, 0);

	if(PLEX_KEY_down('w')) distance.y -= velocity;
	else if(PLEX_KEY_down('d')) distance.x += velocity;
	else if(PLEX_KEY_down('s')) distance.y += velocity;
	else if(PLEX_KEY_down('a')) distance.x -= velocity;

	if(PLEX_KEY_down('\n'))
	{
		if((PROJ)_collisionBoxDeactivated(p_obstColIndex)) (PROJ)_activateCollisionBox(p_obstColIndex);
		else (PROJ)_deactivateCollisionBox(p_obstColIndex);
	}

	if(distance.x || distance.y) (PROJ)_addMove(p_playerColIndex, distance.x, distance.y);
}

static void p_collisionTest()
{
	if(!p_collisionInit)
	{
		p_startPlayer();
		p_startObstruction();

		p_collisionInit = true;
	}

	if(!(PROJ)_collisionBoxDeactivated(p_playerColIndex))
	{
		p_movePlayer();
		p_drawPlayer();
	}

	if(!(PROJ)_collisionBoxDeactivated(p_obstColIndex)) p_drawObstruction();
}

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

// specialized functions ----------------------------------------------------------------------------------------------------

int64_t (PROJ)_addCollisionBox(const bool ignoreCollision, const double x, const double y, const double w, const double h)
{
	(PROJ)_COLLISIONBOX* newBox = NULL;

	(PROJ)_COLLISIONBOX copyBox;

	if(!p_running)
	{
		PLEX_error(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, "Add Collision Box");
		return -1;
	}

	copyBox.area.origin = PLEX_convPoint(x, y);
	copyBox.area.dimens = PLEX_convDimens(w, h);

	if(!ignoreCollision && p_checkCollision(-1, copyBox) != -1) // -1 means no collision
	{
		PLEX_error(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_BADOPERATION, PLEX_ERROR_SEVERITY_MINOR, "Attempted to add a collision block where it's already colliding");
		return -1;
	}

	if(!PLEX_incrementExpandArray(p_cBoxes))
	{
		PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_INCREMENT, PLEX_ERROR_SEVERITY_FATAL, "Collision System", "Collision Boxes");
		return -1;
	}

	newBox = PLEX_getExpandArrayLast(p_cBoxes);

	if(newBox == NULL)
	{
		PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_ACQUIRELAST, PLEX_ERROR_SEVERITY_FATAL, "Collision System", "Collision Boxes");
		return -1;
	}

	newBox->area.origin = PLEX_convPoint(x, y);
	newBox->area.dimens = PLEX_convDimens(w, h);
	newBox->activated = true;

	return PLEX_expandArrayCount(p_cBoxes) - 1;
}

void (PROJ)_addMove(const size_t index, const double x, const double y)
{
	P_MOVECOLLISION* move = NULL;

	size_t boxCount = 0;

	if(!p_running)
	{
		PLEX_error(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, "While adding moves");
		return;
	}

	if(!p_active)
	{
		PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_BADOPERATION, PLEX_ERROR_SEVERITY_MINOR, "While adding moves", "Collision System is inactive");
		return;
	}

	boxCount = PLEX_expandArrayCount(p_cBoxes);

	if(index >= boxCount)
	{
		PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, "While adding moves", "Moves");
		return;
	}

	if(!PLEX_incrementExpandArray(p_moves))
	{
		PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_INCREMENT, PLEX_ERROR_SEVERITY_FATAL, "Collision System", "Moves");
		return;
	}

	move = PLEX_getExpandArrayLast(p_moves);

	if(move == NULL)
	{
		PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_ACQUIRELAST, PLEX_ERROR_SEVERITY_FATAL, "Collision System", "Moves");
		return;
	}

	move->index = index;
	move->distance = PLEX_convPoint(x, y);
}

void (PROJ)_clearCollisionBoxes()
{
	if(!p_running)
	{
		PLEX_error(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, "While clear boxes");
		return;
	}

	if(!p_active)
	{
		PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_BADOPERATION, PLEX_ERROR_SEVERITY_MINOR, "While clear boxes", "Collision System is inactive");
		return;
	}

	PLEX_clearExpandArray(p_cBoxes);
}

void (PROJ)_activateCollision()
{
	if(!p_running)
	{
		PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_BADOPERATION, PLEX_ERROR_SEVERITY_MINOR, PLEX_LANGUAGE_OPDEACTIVE_ACTIVATE, PLEX_LANGUAGE_SYSTEMERROR0 "Collision" PLEX_LANGUAGE_SYSTEMERROR1);
		return;
	}

	p_active = true;
}

void (PROJ)_deactivateCollision()
{
	if(!p_running)
	{
		PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_BADOPERATION, PLEX_ERROR_SEVERITY_MINOR, PLEX_LANGUAGE_OPDEACTIVE_DEACTIVATE, PLEX_LANGUAGE_SYSTEMERROR0 "Collision" PLEX_LANGUAGE_SYSTEMERROR1);
		return;
	}

	p_active = false;
}

// start, update, end functions ---------------------------------------------------------------------------------------------

bool (PROJ)_startCollision()
{
	if(p_running)
	{
		PLEX_error(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_DOUBLESTART, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_LANGUAGE_SYSTEMERROR0 "Collision" PLEX_LANGUAGE_SYSTEMERROR1);
		return true;
	}

	p_cBoxes = PLEX_genExpandArray(10, sizeof((PROJ)_COLLISIONBOX));

	if(p_cBoxes == NULL)
	{
		PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_ALLOCFAIL, PLEX_ERROR_SEVERITY_FATAL, "Collision System", "Collision Boxes");
		return false;
	}

	p_moves = PLEX_genExpandArray(10, sizeof(P_MOVECOLLISION));

	if(p_moves == NULL)
	{
		PLEX_destroyExpandArray(&p_cBoxes);
		PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_ALLOCFAIL, PLEX_ERROR_SEVERITY_FATAL, "Collision System", "Moves");
		return false;
	}

	p_collisionInit = false;

	p_active = false;
	p_running = true;

	return true;
}

bool (PROJ)_updateCollision(const uint64_t time)
{
	size_t count = 0;

	if(!p_running)
	{
		PLEX_error(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_LANGUAGE_SYSTEMERROR0 "Collision" PLEX_LANGUAGE_SYSTEMERROR1);
		return false;
	}

	if(!p_active)
	{
		PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_BADOPERATION, PLEX_ERROR_SEVERITY_MINOR, PLEX_LANGUAGE_OPDEACTIVE_UPDATE, PLEX_LANGUAGE_SYSTEMERROR0 "Collision" PLEX_LANGUAGE_SYSTEMERROR1);
		return false;
	}

	count = PLEX_expandArrayCount(p_moves);

	for(size_t l = 0; l < count; ++l)
	{
		(PROJ)_COLLISIONBOX newBox;

		(PROJ)_COLLISIONBOX* box = NULL;

		P_MOVECOLLISION* move = PLEX_getExpandArrayEntry(l, p_moves);

		if(move == NULL)
		{
			PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_IMPOSSIBLE, "During move check", "Moves");
			return false;
		}

		box = PLEX_getExpandArrayEntry(move->index, p_cBoxes);

		if(box == NULL)
		{
			PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_IMPOSSIBLE, "During move check", "Collision Boxes");
			return false;
		}

		newBox.area.origin.x = box->area.origin.x + move->distance.x;
		newBox.area.origin.y = box->area.origin.y + move->distance.y;

		newBox.area.dimens = box->area.dimens;

		if(p_checkCollision(move->index, newBox) == -1) box->area.origin = newBox.area.origin;
	}

	PLEX_clearExpandArray(p_moves);

	p_collisionTest();

	return true;
}

void (PROJ)_endCollision()
{
	if(!p_running)
	{
		PLEX_error(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_ENDBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_LANGUAGE_SYSTEMERROR0 "Collision" PLEX_LANGUAGE_SYSTEMERROR1);
		return;
	}

	PLEX_destroyExpandArray(&p_moves);
	PLEX_destroyExpandArray(&p_cBoxes);

	p_running = false;
}

// setters ------------------------------------------------------------------------------------------------------------------

void (PROJ)_activateCollisionBox(const size_t index)
{
	(PROJ)_COLLISIONBOX* box = NULL;

	if(!p_running)
	{
		PLEX_error(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, "While activating collision");
		return;
	}

	if(index >= PLEX_expandArrayCount(p_cBoxes))
	{
		PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, "While activating collision", PLEX_ERRORMESS_GENERIC_INDEX);
		return;
	}

	box = PLEX_getExpandArrayEntry(index, p_cBoxes);

	if(box == NULL)
	{
		PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_FATAL, "While activating collision", "Collision Box");
		return;
	}

	box->activated = true;
}

void (PROJ)_deactivateCollisionBox(const size_t index)
{
	(PROJ)_COLLISIONBOX* box = NULL;

	if(!p_running)
	{
		PLEX_error(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, "While deactivating collision");
		return;
	}

	if(index >= PLEX_expandArrayCount(p_cBoxes))
	{
		PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, "While deactivating collision", PLEX_ERRORMESS_GENERIC_INDEX);
		return;
	}

	box = PLEX_getExpandArrayEntry(index, p_cBoxes);

	if(box == NULL)
	{
		PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_FATAL, "While activating decollision", "Collision Box");
		return;
	}

	box->activated = false;
}

// getters ------------------------------------------------------------------------------------------------------------------

bool (PROJ)_isCollisionRunning(){ return p_running; }
bool (PROJ)_isCollisionActive(){ return p_active; }

(PROJ)_COLLISIONBOX (PROJ)_getCollisionBox(const int64_t index)
{
	(PROJ)_COLLISIONBOX blankBox;

	(PROJ)_COLLISIONBOX* box = NULL;

	size_t count = 0;

	blankBox.area = PLEX_convRect(PLEX_convPoint(0, 0), PLEX_convDimens(0, 0));
	blankBox.activated = false;

	if(index < 0)
	{
		PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_UNDERLIMIT, PLEX_ERROR_SEVERITY_MINOR, "While getting collision rectangle", "Collision Index");
		return blankBox;
	}

	count = PLEX_expandArrayCount(p_cBoxes);

	if(index >= count)
	{
		PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, "While getting collision rectangle", "Collision Index");
		return blankBox;
	}

	box = PLEX_getExpandArrayEntry(index, p_cBoxes);

	if(box == NULL)
	{
		PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_FATAL, "While getting collision rectangle", "Collision Box");
		return blankBox;
	}

	return *box;
}

bool (PROJ)_collisionBoxDeactivated(const size_t index)
{
	(PROJ)_COLLISIONBOX* box = NULL;

	if(!p_running)
	{
		PLEX_error(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, "Check if collision is active.");
		return false;
	}

	if(index >= PLEX_expandArrayCount(p_cBoxes))
	{
		PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, "Check if collision is active.", PLEX_ERRORMESS_GENERIC_INDEX);
		return false;
	}

	box = PLEX_getExpandArrayEntry(index, p_cBoxes);

	if(box == NULL)
	{
		PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_FATAL, "Check if collision is active.", "Collision Box");
		return false;
	}

	return !box->activated;
}
