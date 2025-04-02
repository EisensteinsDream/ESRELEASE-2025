#ifndef MMS_MINIGAME0_FUNCTION_H
#define MMS_MINIGAME0_FUNCTION_H

#include "minigame/minigame0/struct.h"

#ifdef __cplusplus
extern "C"
{
#endif

	// the prize functions, ie. the table with coffee (theprize.c)

	extern void MMS0_startCoffee(); // fills the coffee

	extern void MMS0_createThePrizeSprite(const size_t chapter0spriteTex, const uint64_t time); // creates the sprite for the prize

	extern void MMS0_startThePrizePositions(); // starts the prize position

	extern void MMS0_startCrashPositions(); // starts the crash lines for tables

	extern void MMS0_updateThePrize(const double momentum, const double tableMomentum, const uint64_t time); // updates the prize, does not need to return momentum

	extern void MMS0_factorCoffeeDrink(); // factors an enemy drinking coffee

	extern void MMS0_freePrizeSprite(); // frees the prize's sprite

	extern double MMS0_theLine(); // returns collision line at top (a line the tables cannot stay past when pushed)

	extern double MMS0_theLine2(); // returns the collision line at bottom

	extern PLEX_RECT MMS0_prizeRect(); // returns the prize's physical space
	extern uint8_t MMS0_prizeDirection(); // returns the direction of the prize

	extern double MMS0_coffeePerc(); // returns the percentage of coffee drunk, at 0 the player loses

	// table functions (table.c)

	extern void MMS0_createTableSprite(const size_t chapter0spriteTex, const uint64_t time); // creates the table sprite

	extern void MMS0_startTablePositions(); // sets the starting table positions

	extern void MMS0_updateTable(const double tableMomentum, PLEX_MPREC* tmomXs, PLEX_MPREC* tmomYs, const size_t index, const uint64_t time); // updates the table and returns table movement momentums

	extern void MMS0_freeTableSprite(); // frees the table sprite

	extern void MMS0_moveTable(const size_t index); // moves the table at index

	extern void MMS0_setTableDirection(const size_t direction, const size_t index); // sets the table at index to a new direction

	extern PLEX_RECT MMS0_getTableSpace(const size_t index); // returns the table at the index's physical space
	extern size_t MMS0_getTableDirec(const size_t index); // returns the table at index's direction
	extern bool MMS0_getTableReset(const size_t index); // checks whether table at index is resetting

	// player functions (player.c)

	extern void MMS0_createPamaleanaSprite(const size_t pamaleanaSpriteTex, const uint64_t time); // < creates the pamaleana sprite for the minigame

	extern void MMS0_startPlayerPosition(); // puts the player at the beginning point

	extern void MMS0_updatePlayer(PLEX_MPREC* momX, PLEX_MPREC* momY, const double momentum, const uint64_t time); // updates the player determining the momentum x and momentum y for movement. input is contained in this function

	extern void MMS0_setPlayerSpace(const PLEX_RECT playerSpace); // puts the player directly in a spot

	extern void MMS0_freePlayerSprite(); // free's the sprite the player is using

	extern size_t MMS0_getPlayerDirection(); // returns the player's direction
	extern PLEX_RECT MMS0_getPlayerSpace(); // returns the physical space the player occupies

	extern bool MMS0_isPlayerPushing(); // returns whether or not the player is pushing
	extern PLEX_RECT MMS0_getPlayerPushRect(); // returns the collision box for the player's pushing

	// enemy functions (enemy.c)

	extern void MMS0_startEnemyValues(); // < the start of all enemy related variables

	extern void MMS0_createEnemySprite(const size_t chapter0spriteTex, const uint64_t time); // < creates the sprite the enemies use

	extern void MMS0_killEnemy(const size_t index, const size_t tableIndex); // < kills an enemy at index with the table at tableIndex

	extern void MMS0_updateEnemy(const double enemyMomentum, PLEX_MPREC* emomXs, PLEX_MPREC* emomYs, const size_t index, const uint64_t timePass, const uint64_t time); // < updates a singular enemy and returns a series of momentums needed to check for enemy movement

	extern void MMS0_updateAllEnemies(const double perc); // < updates all enemies

	extern void MMS0_moveEnemy(const size_t index, const PLEX_MPREC moveX, const PLEX_MPREC moveY); // moves an enemy by moveX and moveY (ignoring collision)

	extern void MMS0_stopGulpEffect(); // < stops the gulp coffee drinking sound effect from looping

	extern void MMS0_setVert(const size_t index); // sets enemy at index as vertical movement

	extern void MMS0_setHorz(const size_t index); // sets enemy at index as horizontal movement

	extern void MMS0_setDrinking(const size_t index); // sets enemy at index to be drinking

	extern void MMS0_freeEnemySprite(); // frees the sprite the enemy uses

	extern bool MMS0_enemyDead(const size_t index); // return whether or not an enemy at index is dead

	extern size_t MMS0_enemyCapacity(); // returns the capacity of the enemies (ie. how many spots in the array that they are using)

	extern size_t MMS0_enemiesKilled(); // returns the amount of enemies killed

	extern PLEX_RECT MMS0_getEnemyRect(const size_t index); // gets an enemy at 'index'

	extern bool MMS0_enemyVert(const size_t index); // returns whether the enemy is moving vertical or not

	// main functions (minigame1.c)

	extern uint32_t MMS0_drawLayer(const PLEX_RECT area); // acquires the draw layer for any object in physical space

	extern void MMS0_freeMinigameSprites(); // frees all sprites used by minigame 0, setting them to NULL
#ifdef __cplusplus
}
#endif


#endif
