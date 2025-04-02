#ifndef MMS2_FUNCTION_H
#define MMS2_FUNCTION_H

#include "minigame/minigame2/struct.h"

// FUNCTION HOOKS

typedef void (*MMS_F_AIPATTERN)(const size_t index, const uint64_t time);

// FUNCTIONS THEMSELVES

#ifdef __cplusplus
extern "C"
{
#endif

// GAME OVER AND SNAPSHOT

	extern bool MMS2_setSystemGameoverSnapshot(const size_t chapter2SpriteTex, const size_t chapter2SpriteTex2, const uint64_t time);  // < initializes gameover and snapshot system to a state that resets when the game is reset
	extern void MMS2_initSystemGameoverSnapshot(); // < initializes gameover and snapshot system to a state that doesn't reset when the game is reset
	extern bool MMS2_checkRunSystemGameoverSnapshot(const size_t chapter2SpriteTex, const size_t chapter2SpriteTex2, const size_t fontPlate, const uint64_t time); // < checks if the gameover and snapshot system should be running, and runs it if it should
	extern void MMS2_endSystemGameoverSnapshot(); // < ends the gameover and snapshot system freeing all allocated data along the way

	extern void MMS2_snapshotTown(); // < snapshots data of the last town to be restored

	extern void MMS2_restoreTown(); // < returns to the last town stored in the snapshot data

	extern void MMS2_dumpSnapshot(); // < dumps the snapshot of the town to be reloaded on later date

	extern void MMS2_gameOverScene(const size_t pamaleanaSpriteTex, const size_t cubicleBackdrop, const size_t venariusSpriteTex, const size_t extraplocanSpriteTex, const size_t label, const size_t bubble, const size_t arrow, const size_t fontPlate, const uint64_t time); // < starts the gameover sprite theater scene

	extern bool MMS2_runGameoverMode(const size_t chapter2SpriteTex, const size_t chapter2SpriteTex2, const uint64_t time); // < continues to run the gameover sprite theater mode if it's running

	extern void MMS2_checkHasSnapshotFile(); // < marks whether or not there's a snapshot file to be loaded from

	extern void MMS2_checkRestoreTown(const size_t chapter2SpriteTex, const size_t chapter2SpriteTex2, const uint64_t time); // < restores town from snapshot file if 'MMS2_checkHasSnapshotFile' function marks it as existing

	extern bool MMS2_checkTerminated(const size_t fontPlate); // < catches whether or not the program has been terminated in order to prompt the player to possibly save snapshot

	extern bool MMS2_lastTownGotBoss(); // < returns whether or not the snapshot file marked the boss being reached

	extern bool MMS2_terminateConfirm(); // < returns whether or not the termination screen has been exited

	extern bool MMS2_canRestoreTown(); // < returns whether or not a town snapshot can be returned from file (for the 'restore save' button)

// TUTORIAL

	extern void MMS2_setSystemTutorial(); // < initializes tutorial system to a state that resets when the game is reset
	extern void MMS2_initSystemTutorial(); // < initializes tutorial system to a state that doesn't reset when the game is reset
	extern bool MMS2_checkRunSystemTutorial(const size_t chapter2SpriteTex, const size_t chapter2SpriteTex2, const size_t fontPlate, const uint64_t time); // < checks if the tutorial system should be running, and runs it if it should
	extern void MMS2_endSystemTutorial(); // < ends the tutorial system freeing all allocated data along the way

	extern void MMS2_endTutorial(); // < ends the tutorial if it's running

// GUI

	extern void MMS2_setSystemGUI(); // < initializes GUI system to a state that resets when the game is reset
	extern void MMS2_initSystemGUI(); // < initializes GUI system to a state that doesn't reset when the game is reset
	extern bool MMS2_checkRunSystemGUIA(const size_t fontPlate, bool* success, const uint64_t time); // < checks if the GUI system should be running, and runs it if it should (before all the other systems - can end the game by returning false)
	extern void MMS2_checkRunSystemGUIB(const size_t chapter2SpriteTex, const size_t chapter2SpriteTex2, const size_t fontPlate, const uint64_t time); // < checks if the GUI system should be running, and runs it if it should (after all the other systems - can't end the game by returning false)
	extern void MMS2_endSystemGUI(); // < ends the GUI system freeing all allocated data along the way

	extern uint32_t MMS2_menuIx(const uint32_t id, const uint32_t ix, const size_t it); // < returns the X of a clickable menu item

	extern void MMS2_startMenu(uint32_t* id, uint32_t* ix, uint32_t* iy, uint32_t* lh); // < starts a menu returning relevant dimensions

	extern bool MMS2_drawArrow(const uint32_t fx, const uint32_t fy, const uint32_t fw, const uint32_t fh, const uint32_t x, const uint32_t y, const uint8_t direc, const uint64_t time); // < draws an arrow on the screen, returns true when clicked.

	extern void MMS2_bloodSplatter(const uint64_t time);

	extern bool MMS2_factorMenuItem(const uint32_t ix2, const uint32_t iy, const uint32_t id, const uint32_t lh, const char* const label, const size_t fontPlate); // < updates a menu item and returns whether or not it's selected

	extern void MMS2_printMenuItem(const uint32_t ix2, const uint32_t iy, const uint32_t id, const size_t tex); // < prints a menu item

	extern void MMS2_runCalmMenu(const size_t fontPlate, const uint64_t time);  // < run the calm menu
	extern void MMS2_runUncalmMenu(const size_t fontPlate, const uint64_t time);  // < run the uncalm menu

	extern void MMS2_drawEnemyOffscreenArrow(const bool left); // < draws an arrow to indicate an enemy is shooting the player in the margins

	extern void MMS2_drawRestoreTownButton(const size_t chapter2SpriteTex, const size_t chapter2SpriteTex2, const size_t fontPlate, const uint64_t time); // < draws the button that, when pressed, restores the town to the snapshot in mg2town

	extern void MMS2_setCustomCursorSelect(); // < sets the cursor to the custom cursor
	extern void MMS2_unsetCustomCursor(); // < unsets the cursor to custom cursor

	extern void MMS2_gunMenuBack(); // sets the gun menu forward
	extern void MMS2_gunMenuForward(); // sets the gun menu backwards

	extern void MMS2_selectLastGun(const uint64_t time); // selects the gun before the currently selected wrapping to the last gun
	extern void MMS2_selectNextGun(const uint64_t time); // selects the next gun after the currently selected wrapping to the first gun
	extern void MMS2_selectGunSlotAt(const size_t at, const uint64_t time); // selects and starts a gun at the slot (not index) of 'at'

	extern void MMS2_updateSelectGun(const uint64_t time); // updates the gun select values

	extern size_t MMS2_gunScroll(); // returns where the gun is scrolled

	extern PLEX_RECT MMS2_getPamaleanaIconSpace(); // return the space the pamaleana icon occupies

	extern size_t MMS2_selectedGunIndex(); // returns the index of the selected gun
	extern size_t MMS2_selectedGunSlot(); // returns the slot of the selected gun
	extern size_t MMS2_selectedGunSlotIndex(); // returns the index of the gun in the selected slot
	extern size_t MMS2_showGunCount(); // shows the number of guns in the menu
	extern size_t MMS2_gunSlotIndex(const size_t slot); // returns the index of the gun in the slot

	extern void MMS2_setPamalenaIconSpace(const PLEX_RECT pamIconSpace); // sets the icon space

	extern PLEX_RECT MMS2_shotArea(); // returns the shot area
	extern PLEX_RECT MMS2_innerShotArea(); // return the inner shot area

// CALM AREA

	extern void MMS2_setSystemCalmArea(); // < initializes calm area (town) system to a state that resets when the game is reset
	extern void MMS2_initSystemCalmArea(); // < initializes calm area (town) system to a state that doesn't reset when the game is reset
	extern void MMS2_checkRunSystemCalmArea(const size_t chapter2SpriteTex, const size_t chapter2SpriteTex2, const size_t fontPlate, const uint64_t time); // < checks if the calm area (town) system should be running, and runs it if it should
	extern void MMS2_endSystemCalmArea(); // < ends the calm area (town) system freeing all allocated data along the way

	extern void MMS2_clearCalmAreaSprites(); // < clear calm area related sprites

	extern void MMS2_clearNPC(struct MMS_MINIGAME2NPC* npc); // < destroys an NPC clearing all allocated data

	extern void MMS2_setAsTown0(const size_t chapter2SpriteTex, struct MMS_MINIGAME2ROOM* room, const uint64_t time); // < sets the room as the first town
	extern void MMS2_setAsTown1(const size_t chapter2SpriteTex, const size_t chapter2SpriteTex2, struct MMS_MINIGAME2ROOM* room, const uint64_t time); // < sets the room as the second town
	extern void MMS2_setAsTown2(const size_t chapter2SpriteTex, const size_t chapter2SpriteTex2, struct MMS_MINIGAME2ROOM* room, const uint64_t time); // < sets the room as the third town
	extern void MMS2_setAsTown3(const size_t chapter2SpriteTex, const size_t chapter2SpriteTex2, struct MMS_MINIGAME2ROOM* room, const uint64_t time); // < sets the room a the fourth town
	extern void MMS2_setAsTown4(const size_t chapter2SpriteTex, const size_t chapter2SpriteTex2, struct MMS_MINIGAME2ROOM* room, const uint64_t time); // < sets the room as the fifth town

	extern void MMS2_runCalmNoMayorCutaway(const size_t fontPlate, const uint64_t time); // < run the parts of the calm area that show when it isn't showing a mayor's message

	extern bool MMS2_checkMayorMessage(const size_t fontPlate); // < checks to see whether or not to show the mayor message on the screen

	extern void MMS2_goNextTownArea(); // < go to the next town area
	extern void MMS2_goLastTownArea(); // < go to the last town area

	extern void MMS2_setTownArea(const size_t index); // < sets the current town area to index

	extern bool MMS2_mayorCutaway(); // returns whether or not the cutaway for the message from the mayor is active

	extern size_t MMS2_townArea(); // returns the number for which area in a town the player is in

// PLAYER

	extern void MMS2_setSystemPlayer(const uint64_t time); // < initializes player system to a state that resets when the game is reset
	extern void MMS2_initSystemPlayer(); // < initializes player system to a state that doesn't reset when the game is reset
	extern bool MMS2_checkRunSystemPlayer(const size_t chapter2SpriteTex, const size_t chapter2SpriteTex2, const size_t pamaleanaSpriteTex, const size_t cubicleBackdrop, const size_t venariusSpriteTex, const size_t extraplocanSpriteTex, const size_t label, const size_t bubble, const size_t arrow, const size_t fontPlate, bool* success, const uint64_t time); // < checks if the player system should be running, and runs it if it should
	extern void MMS2_endSystemPlayer(); // < ends the player system freeing all allocated data along the way

	extern void MMS2_clearPlayerSprites(); // < clears away all the sprites made for the player

	extern void MMS2_initPointsCashHealth(); // < sets the points, cash, and health to it's initial values

	extern void MMS2_cure(const double amount); // cures the player by 'amount' of HP (percentage 0-1)
	extern void MMS2_fillHealth(); // fills the player to full health ie. 1 == 100%

	extern void MMS2_setHealth(const double health); // sets the player health to a value
	extern void MMS2_decrementHealth(const double health); // decrements health

	extern void MMS2_setPoints(const uint32_t points); // sets the current points to points
	extern void MMS2_incrementPoints(const uint32_t points); // increments current points by points
	extern void MMS2_decrementPoints(const uint32_t points); // decrements current points by points
	extern void MMS2_clearPoints(); // clears points

	extern bool MMS2_costCash(const double cost); // decrements cash amount by cost, returning false if the cost is too much
	extern void MMS2_emptyCash(); // sets cash to 0

	extern void MMS2_setCash(const double cash); // sets cash to cash
	extern void MMS2_incrementCash(const double cash); // increments cash by cash
	extern void MMS2_clearCash(); // clears cash

	extern void MMS2_createGuns(const uint64_t time); // initializes guns

	extern bool MMS2_hasGun(const size_t index); // returns true of the player has gun at index
	extern void MMS2_purchaseGun(const size_t index); // purchases a gun at 'index' if possible
	extern void MMS2_refillGun(const size_t index); // sets gun at 'index' to full ammo and full clip

	extern void MMS2_addGun(const size_t index); // adds gun at index
	extern void MMS2_takeGun(const size_t index); // takes away gun at index

	extern void MMS2_setShotTime(const int64_t time); // sets the time in which the a player gunshot starts
	extern void MMS2_setShotDuration(const uint64_t duration); // sets how long a player gunshot will last

	extern void MMS2_setShotArea(const PLEX_RECT shotArea); // sets the area of shot collision
	extern void MMS2_setInnerShotArea(const PLEX_RECT innerShotArea); // sets the inner area of shot collision (higher damage)
	extern void MMS2_setShotIcon(const size_t icon); // sets the cursor as icon

	extern void MMS2_setPlayerShotTime(const uint64_t time); // sets the beginning of the enemy shooting the player

	extern void MMS2_setEmptyChamberSE(const int64_t emptyChamberSE); // sets the empty chamber SE to be played, cannot override if there's one already playing

	extern void MMS2_setDodgePhase(const MMS_MINIGAME2DODGEPHASE phase); // sets the player dodge phase

	extern void MMS2_setLeanX(const double leanX); // sets the lean X
	extern void MMS2_setLeanY(const double leanY); // sets the lean Y

	extern double MMS2_health(); // returns the health
	extern uint32_t MMS2_points(); // returns the points
	extern double MMS2_cash(); // returns the cash

	extern int64_t MMS2_shotTime(); // returns the shot time
	extern uint64_t MMS2_shotDuration(); // returns the shot duration
	extern size_t MMS2_shotIcon(); // returns the shot icon

	extern uint64_t MMS2_getPlayerShotTime(); // returns the time when the enemy shot the player

	extern bool MMS2_playerIsShooting(const uint64_t time); // returns true if the player is shooting
	extern bool MMS2_playerIsNotShooting(const uint64_t time); // returns true if the player is not shooting

	extern bool MMS2_isReloading(const uint64_t time); // returns whether or not the player is reloading

	extern bool MMS2_isDodgePhase(const MMS_MINIGAME2DODGEPHASE phase); // returns true if the dodge phase passed is the same as the current

	extern double MMS2_dodgePhaseAsNumber(); // returns the dodge phase but as a number rather than an enum

	extern double MMS2_leanX(); // return the lean x amount
	extern double MMS2_leanY(); // return the lean y amount

	extern struct MMS_MINIGAME2GUN* MMS2_gun(const size_t index); // returns the gun at index
	extern struct MMS_MINIGAME2GUN* MMS2_selectedGun(); // returns the selected gun

// ENEMY

	extern void MMS2_setSystemEnemy(); // < initializes enemy system to a state that resets when the game is reset
	extern void MMS2_initSystemEnemy(const size_t chapter2SpriteTex, const size_t chapter2SpriteTex3, const size_t chapter2SpriteTex4, const uint64_t time); // < initializes enemy system to a state that doesn't reset when the game is reset
	extern void MMS2_checkRunSystemEnemy(const bool coverHit, const PLEX_RECT coverRect, const double coverLayer, const double coverAbsorb, const uint64_t time); // < checks if the enemy system should be running, and runs it if it should
	extern void MMS2_endSystemEnemy(); // < ends the enemy system freeing all allocated data along the way

	extern void MMS2_clearEnemySprites(); // < clears out all the sprite data used by enemies

	extern void MMS2_setEnemySprite(const size_t startImage, struct MMS_MINIGAME2ENEMY* enemy, const uint64_t time); // sets the enemy sprite starting at image 'startImage'

	extern void MMS2_setEnemyGenerator(const double minDuration, const double maxDuration, const size_t enemyCount, MMS_F_AIPATTERN aiPattern0, const size_t typeIndex0, struct MMS_MINIGAME2ROOM* room, const uint64_t time); // < initializes the enemy generator

	extern void MMS2_placeEnemyGen(const size_t index, const char* const name, const double health, const PLEX_RECT space, const double minMoveSpeed, const double maxMoveSpeed, const uint64_t thoughtDelay, const uint64_t shotDuration, const uint64_t shotMax, const uint64_t reloadDuration, const double damagePotential, const double accuracyPotential, const size_t pointGain, const double treasureChance, const double likelyCashTreasure, const double likelyHealthTreasure, const double cashTreasureAmount, const size_t startImage, PLEX_ANIMATION_PLATE animPlate, const uint64_t time); // places enemy generation data at 'index'

	extern void MMS2_addGeneratorAIPattern(struct MMS_MINIGAME2ROOM* room, MMS_F_AIPATTERN aiPattern); // < adds a AI pattern to the enemy generator

	extern void MMS2_addEnemyGeneratorTypeIndex(struct MMS_MINIGAME2ROOM* room, const size_t index); // < adds the index of a new generator type

	extern void MMS2_startEnemyGenerator(struct MMS_MINIGAME2ROOM* room, const uint64_t time); // < starts running the enemy generator

	extern void MMS2_resetEnemyGenerator(struct MMS_MINIGAME2ROOM* room, const uint64_t time); // < resets the enemy generator

	extern void MMS2_incrementEnemyCount(); // increments the enemy count
	extern void MMS2_incrementTotalEnemyCount(); // increments the total enemy count
	extern void MMS2_clearEnemyCount(); // sets enemy count to 0, clearing enemies from field

	extern uint32_t MMS2_getEnemyLayer(const PLEX_RECT rect); // < gets the enemy draw layer for an enemy occupying space 'rect'

	extern size_t MMS2_enemyCount(); // returns the number of enemies on field
	extern size_t MMS2_defeatedEnemyCount(); // returns the number of defeated enemies

	extern struct MMS_MINIGAME2ENEMY* MMS2_enemyGen(const size_t index); // returns a pointer to an enemy generation value at index
	extern struct MMS_MINIGAME2ENEMY* MMS2_enemy(const size_t index); // returns a pointer to enemy at index

	// enemy AI hooks:

	extern void MMS2_ai_dodger(const size_t index, const uint64_t time); // enemy tries to run away from the cursor
	extern void MMS2_ai_coward(const size_t index, const uint64_t time); // enemy tries to run outside of view or hide in margins
	extern void MMS2_ai_runner(const size_t index, const uint64_t time); // enemy tries to constantly run
	extern void MMS2_ai_sneak(const size_t index, const uint64_t time); // enemy specifically runs into the margins
	extern void MMS2_ai_diver(const size_t index, const uint64_t time); // enemy tries to dive and roll away from the cursor
	extern void MMS2_ai_sharpshooter(const size_t index, const uint64_t time); // enemy aggressively shoots attempting to get the most damage
	extern void MMS2_ai_maniac(const size_t index, const uint64_t time); // enemy is a wildcard and erratically flips through strategies

// COVER

	extern void MMS2_setSystemCover(); // < initializes cover system to a state that resets when the game is reset
	extern void MMS2_initSystemCover(const size_t chapter2SpriteTex, const size_t chapter2SpriteTex2, const size_t chapter2SpriteTex3, const uint64_t time); // < initializes cover system to a state that doesn't reset when the game is reset
	extern void MMS2_checkRunSystemCover(bool* coverHit, PLEX_RECT* coverRect, double* coverLayer, double* coverAbsorb, const uint64_t time); // < checks if the cover system should be running, and runs it if it should
	extern void MMS2_endSystemCover(); // < ends the cover system freeing all allocated data along the way

	extern void MMS2_clearCoverSprites(); // < clears all cover sprites

	extern void MMS2_setCoverGenerator(const double minCount, const double maxCount, const size_t initialCover, struct MMS_MINIGAME2ROOM* room, const uint64_t time); // < sets the cover generator in room's paramaters

	extern void MMS2_addCoverTypeIndex(struct MMS_MINIGAME2ROOM* room, const size_t index); // < adds a type of cover to the cover generator in room

	extern void MMS2_useCoverGenerator(struct MMS_MINIGAME2ROOM* room, const uint64_t time); // use the cover generator to generate cover

	extern void MMS2_placeCoverGen(const size_t index, const bool bleeds, const size_t killPenalty, const bool moving, const MMS_MINIGAME2MOVEPATTERN movePattern, const double moveSpeed, const uint64_t moveAnimSpeed, const size_t tex, const size_t texStart, const double wperc, const double hperc, const PLEX_DIMENS dimens, const uint64_t time); // place a new cover type into the generator

	extern void MMS2_placeCoverGenNoMove(const size_t index, const bool bleeds, const size_t killPenalty, const size_t tex, const size_t texStart, const double wperc, const double hperc, const PLEX_DIMENS dimens, const uint64_t time); // place a non-moving cover type into the generator

	extern void MMS2_addGravesite(const size_t tex, const size_t texStart, const PLEX_RECT space, const double wperc, const double hperc, const uint64_t time); // adds a gravesite where an enemy dies (which is a kind of cover)

	extern void MMS2_incrementCoverCount(); // increment the cover count (used by final boss)

	extern void MMS2_clearCoverCount(); // clears the cover count

	extern size_t MMS2_coverCount(); // returns the cover count

	extern struct MMS_MINIGAME2COVER* MMS2_cover(const size_t index); // returns cover at index
	extern struct MMS_MINIGAME2COVER* MMS2_coverGen(const size_t index); // returns cover to be copied from the generator at index

// TREASURE

	extern void MMS2_setSystemTreasure(); // < initializes treasure system to a state that resets when the game is reset
	extern void MMS2_initSystemTreasure(); // < initializes treasure system to a state that doesn't reset when the game is reset
	extern void MMS2_checkRunSystemTreasure(const uint64_t time); // < checks if the treasure system should be running, and runs it if it should
	extern void MMS2_endSystemTreasure(); // < ends the treasure system freeing all allocated data along the way

	extern void MMS2_addTreasureBoxCash(const double x, const double y, const double cash); // < add a cash filled treasure box onto the field

	extern void MMS2_addTreasureBoxHealth(const double x, const double y); // < add a health restore treasure box onto the field

	extern void MMS2_addTreasureBoxAmmo(const double x, const double y); // < add an ammo refill treasure box on the field

	extern void MMS2_clearTreasureCount(); // < clears the treasure boxes from the field

// ROOM

	extern void MMS2_setSystemRoom(); // < initializes room system to a state that resets when the game is reset
	extern void MMS2_initSystemRoom(); // < initializes room system to a state that doesn't reset when the game is reset
	extern bool MMS2_checkRunSystemRoom(const size_t chapter2SpriteTex, const size_t chapter2SpriteTex2, const size_t chapter2SpriteTex3, const size_t chapter2SpriteTex4, const size_t fontPlate, const uint64_t time); // < checks if the room system should be running, and runs it if it should
	extern void MMS2_endSystemRoom(); // < ends the room system freeing all allocated data along the way

	extern void MMS2_clearRoomSprites(); // < clears all sprites related to rooms

	extern void MMS2_setCurrentRoom(const char* const title, const size_t background, const size_t skytex, const bool calm); // < sets the current room as a new room with passed values

	extern void MMS2_copyRoomNPCs(struct MMS_MINIGAME2ROOMCONTENTS* a, const struct MMS_MINIGAME2ROOMCONTENTS* const b); // < copies all NPCs from room B to room A

	extern void MMS2_genNextPath(const size_t chapter2SpriteTex, const size_t chapter2SpriteTex2, const size_t chapter2SpriteTex3, const size_t chapter2SpriteTex4, const uint64_t time); // < generates the next path to be moved to

	extern void MMS2_startMoving(const size_t direc, const uint64_t time); // < initiates the player to move to a new room

	extern void MMS2_checkMove(const uint64_t time); // < checks whether or not the player is moving to a new room and acts accordingly

	extern bool MMS2_pointCheckTown(const size_t chapter2SpriteTex, const size_t chapter2SpriteTex2, const uint64_t time); // < sets the current town by the points currently had

	extern void MMS2_markFlagGen(); // < marks the room generator flag as true

	extern size_t MMS2_backgroundGraphic(const size_t index); // < returns the background graphic at index
	extern size_t MMS2_skyGraphic(const size_t index); // < returns the sky graphic at index

	extern bool MMS2_pathOpen(const size_t direc); // < returns whether a path in a direction is open
	extern bool MMS2_pathCalm(const size_t direc); // < returns whether a path in a direction is calm or not

	extern bool MMS2_isNotMoving(); // < returns if the player is not moving
	extern bool MMS2_isMoving(); // < returns if the player is moving
	extern size_t MMS2_moveDirec(); // < returns the movement direction

	extern PLEX_FAKESTRING_25 MMS2_currentRoomName(); // < returns the current room's name
	extern bool MMS2_currentRoomCalm(); // < returns whether or not the current room is calm
	extern size_t MMS2_currentRoomFloor(); // < returns the current room's floor
	extern size_t MMS2_currentRoomSky(); // < return the current room's sky

	extern PLEX_FAKESTRING_500 MMS2_currentMayorMessage(); // < get the current mayor message

	extern struct MMS_MINIGAME2ROOM* MMS2_currentRoom(); // < returns a pointer to the current room
	extern struct MMS_MINIGAME2ENEMYGENERATOR* MMS2_currentEnemyGenerator(); // < returns a pointer to the current room's enemy generator

	extern bool MMS2_flagGen(); // < returns whether or not the generators are flagged

// PENULTIMATE CUSTCENE

	extern void MMS2_setSystemPenultimateCutscene(); // < initializes penultimate cutscene system to a state that resets when the game is reset
	extern void MMS2_initSystemPenultimateCutscene(); // < initializes penultimate cutscene system to a state that doesn't reset when the game is reset
	extern bool MMS2_checkRunSystemPenultimateCutscene(const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow); // < checks if the penultimate cutscene system should be running, and runs it if it should
	extern void MMS2_endSystemPenultimateCutscene(); // < ends the penultimate cutscene system freeing all allocated data along the way

	extern void MMS2_clearPenultimateCutsceneSprites(); // < clears all the sprites allocated for the penultimate cutscene

	extern void MMS2_penultimateCutscene(const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow); // run the penultimat cutscene

	extern void MMS2_clearPenultimateCutscene(); // clears all the values of the penultimate cutscene

	extern void MMS2_markPenultimateCutscene(); // mark penultimate cutscene to be played
	extern void MMS2_markPenultimateCustcenePlaying(); // mark that the penultimate cutscene is playing

	extern bool MMS2_penultimateCutPlay(); // return the penultimate cutscene is marked to be played
	extern bool MMS2_penultimateCutIsPlaying(); // return that the penultimate cutscene is playing

// FINAL BOSS

	extern void MMS2_setSystemFinalBoss(); // < initializes final boss system to a state that resets when the game is reset
	extern void MMS2_initSystemFinalBoss(); // < initializes final boss system to a state that doesn't reset when the game is reset
	extern bool MMS2_checkRunSystemFinalBoss(bool* success, const uint64_t time); // < checks if the final boss system should be running, and runs it if it should
	extern void MMS2_endSystemFinalBoss(); // < ends the final boss system freeing all allocated data along the way

	extern void MMS2_clearFinalBossSprites(); // < clears the sprites allocated for the final boss

	extern void MMS2_clearFinalBoss(); // < clears all the values for final boss

	extern void MMS2_readyLevineFight(); // < marks the levine (ie. final boss) as ready
	extern void MMS2_unmarkLevineFight(); // < unmarks levine boss as ready in order to mark the start of the final boss intro

	extern void MMS2_markFinalBossIntroCut();  // < marks the start of the final boss intro cutscene
	extern void MMS2_unmarkFinalBossIntroCut(); // < unmarks the final boss cutscene end in order to mark the start of the final boss fight
	extern void MMS2_finalBossIntroCut(const uint64_t time); // < updates the final boss intro cut

	extern void MMS2_startFinalBoss(const uint64_t time); // < initializes the final boss
	extern bool MMS2_updateFinalBoss(const uint64_t time); // < updates the final boss

	extern void MMS2_markFinalBossActive(); // < marks the final boss as active
	extern void MMS2_markFinalBossDead(); // < marks the final boss as dead

	extern void MMS2_markFinalBossOutroCut(); // < marks the beginning of the final boss outro after his defeat
	extern void MMS2_unmarkFinalBossOutroCut(); // < marks the end of the final boss outro as to end the minigame
	extern void MMS2_playFinalBossOutroTheme(); // < starts the theme for the final boss outro cutscene
	extern void MMS2_stopFinalBossOutroTheme(); // < stops the theme for the final boss outro cutscene
	extern bool MMS2_finalBossOutroCut(const uint64_t time); // < updates the final boss outro cut

	extern bool MMS2_levineFight(); // returns whether or not the levine final boss fight is starting (intro starts next)
	extern bool MMS2_beginFinalBossIntro(); // returns whether or not the final boss intro should be started (activation starts next)
	extern bool MMS2_activateFinalBoss(); // returns whether or not the final boss should be activated (outro starts next)
	extern bool MMS2_beginFinalBossOutro(); // returns whether or not the final boss outro should be started

// MINIGAME 2

	extern bool MMS2_setGame(const size_t chapter2SpriteTex, const size_t chapter2SpriteTex2, const uint64_t time); // < sets the initial values of the game that are cleared when the game is reset

	extern void MMS2_freeMinigameSprites(); // frees all sprites in the minigame

#ifdef __cplusplus
}
#endif


#endif
