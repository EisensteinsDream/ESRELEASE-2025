#include "minigame/minigame2/minigame2.h"

static bool p_running = false;

// initializes the game - starts anything in all of the subsystems that won't be reset when the game is reset

static void p_initGame(const size_t chapter2SpriteTex, const size_t chapter2SpriteTex2, const size_t chapter2SpriteTex3, const size_t chapter2SpriteTex4, const uint64_t time)
{
	MMS2_initSystemTutorial();
	MMS2_initSystemGameoverSnapshot();
	MMS2_initSystemPlayer();
	MMS2_initSystemEnemy(chapter2SpriteTex, chapter2SpriteTex3, chapter2SpriteTex4, time);
	MMS2_initSystemCover(chapter2SpriteTex, chapter2SpriteTex2, chapter2SpriteTex3, time);
	MMS2_initSystemTreasure();
	MMS2_initSystemCalmArea();
	MMS2_initSystemRoom();
	MMS2_initSystemFinalBoss();
	MMS2_initSystemPenultimateCutscene();
	MMS2_initSystemGUI();

	MMS_MMS2MarkMinigame();
}

// sets the game - starts anything in all of the subsystems that will be reset when the game is reset. return value of true - continues iterations, return value of false - signals to end game.

static bool p_runGame(const size_t pamaleanaSpriteTex, const size_t cubicleBackdrop, const size_t venariusSpriteTex, const size_t extraplocanSpriteTex, const size_t label, const size_t bubble, const size_t arrow, const size_t chapter2SpriteTex, const size_t chapter2SpriteTex2, const size_t chapter2SpriteTex3, const size_t chapter2SpriteTex4, const size_t fontPlate, const uint64_t time, bool* success)
{
	bool coverHit = false;

	PLEX_RECT coverRect;

	double coverLayer = 0, coverAbsorb = 1;

	if(!MMS2_checkRunSystemGameoverSnapshot(chapter2SpriteTex, chapter2SpriteTex2, fontPlate, time)) return !MMS2_terminateConfirm();

	if(!MMS2_checkRunSystemGUIA(fontPlate, success, time)) return false;

	if(MMS2_checkRunSystemTutorial(chapter2SpriteTex, chapter2SpriteTex2, fontPlate, time)) return true;

	if(MMS2_checkRunSystemPenultimateCutscene(fontPlate, label, bubble, arrow)) return true;

	if(MMS2_checkRunSystemFinalBoss(success, time) && *success) return false;

	if(!MMS2_checkRunSystemPlayer(chapter2SpriteTex, chapter2SpriteTex2, pamaleanaSpriteTex, cubicleBackdrop, venariusSpriteTex, extraplocanSpriteTex, label, bubble, arrow, fontPlate, success, time)) return false; // < keep run player before run cover

	MMS2_checkRunSystemCover(&coverHit, &coverRect, &coverLayer, &coverAbsorb, time); // < run cover before enemies
	MMS2_checkRunSystemEnemy(coverHit, coverRect, coverLayer, coverAbsorb, time);
	MMS2_checkRunSystemTreasure(time);

	MMS2_checkRunSystemRoom(chapter2SpriteTex, chapter2SpriteTex2, chapter2SpriteTex3, chapter2SpriteTex4, fontPlate, time);

	MMS2_checkRunSystemCalmArea(chapter2SpriteTex, chapter2SpriteTex2, fontPlate, time);

	MMS2_checkRunSystemGUIB(chapter2SpriteTex, chapter2SpriteTex2, fontPlate, time);

	return true;
}

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

bool MMS2_setGame(const size_t chapter2SpriteTex, const size_t chapter2SpriteTex2, const uint64_t time)
{
	// do not check p_running here

	MMS2_setSystemTutorial();
	if(!MMS2_setSystemGameoverSnapshot(chapter2SpriteTex, chapter2SpriteTex2, time)) return false;
	MMS2_setSystemPlayer(time);
	MMS2_setSystemEnemy();
	MMS2_setSystemCover();
	MMS2_setSystemTreasure();
	MMS2_setSystemCalmArea();
	MMS2_setSystemRoom();
	MMS2_setSystemFinalBoss();
	MMS2_setSystemPenultimateCutscene();
	MMS2_setSystemGUI();

	return true;
}

bool MMS_beginMinigame2(const size_t chapter2SpriteTex, const size_t chapter2SpriteTex2, const size_t chapter2SpriteTex3, const size_t chapter2SpriteTex4, const uint64_t time)
{
	if(p_running)
	{
		PLEX_errorNoDesc(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_DOUBLESTART, PLEX_ERROR_SEVERITY_BADSTYLE);
		return true;
	}

	p_initGame(chapter2SpriteTex, chapter2SpriteTex2, chapter2SpriteTex3, chapter2SpriteTex4, time);

	p_running = true;

	return true;
}

bool MMS_updateMinigame2(const size_t pamaleanaSpriteTex, const size_t cubicleBackdrop, const size_t venariusSpriteTex, const size_t extraplocanSpriteTex, const size_t label, const size_t bubble, const size_t arrow, const size_t chapter2SpriteTex, const size_t chapter2SpriteTex2, const size_t chapter2SpriteTex3, const size_t chapter2SpriteTex4, const size_t fontPlate, const uint64_t time, bool* success)
{
	if(!p_running)
	{
		PLEX_errorNoDesc(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_UPDATEBEFORESTART, PLEX_ERROR_SEVERITY_BADSTYLE);
		return false;
	}

	if(!p_runGame(pamaleanaSpriteTex, cubicleBackdrop, venariusSpriteTex, extraplocanSpriteTex, label, bubble, arrow, chapter2SpriteTex, chapter2SpriteTex2, chapter2SpriteTex3, chapter2SpriteTex4, fontPlate, time, success)) return false;

	MM_COMMON_update();

	return !MMS2_terminateConfirm();
}

void MMS_endMinigame2()
{
	if(!p_running)
	{
		PLEX_errorNoDesc(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_ENDBEFORESTART, PLEX_ERROR_SEVERITY_BADSTYLE);
		return;
	}

	MMS2_endSystemGUI();
	MMS2_endSystemPenultimateCutscene();
	MMS2_endSystemFinalBoss();
	MMS2_endSystemRoom();
	MMS2_endSystemCalmArea();
	MMS2_endSystemTreasure();
	MMS2_endSystemCover();
	MMS2_endSystemEnemy();
	MMS2_endSystemPlayer();
	MMS2_endSystemGameoverSnapshot();
	MMS2_endSystemTutorial();

	p_running = false;
}

void MMS_runMinigame2(const size_t pamaleanaSpriteTex, const size_t cubicleBackdrop, const size_t venariusSpriteTex, const size_t extraplocanSpriteTex, const size_t label, const size_t bubble, const size_t arrow, const size_t chapter2SpriteTex, const size_t chapter2SpriteTex2, const size_t chapter2SpriteTex3, const size_t chapter2SpriteTex4, const size_t fontPlate)
{
	uint64_t time = PLEX_getGameTime();

	bool success = false;

	MMS_beginMinigame2(chapter2SpriteTex, chapter2SpriteTex2, chapter2SpriteTex3, chapter2SpriteTex4, time);

	while(!success && !MMS2_terminateConfirm())
	{
		if(!MMS2_setGame(chapter2SpriteTex, chapter2SpriteTex2, time))
		{
			PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_BADOPERATION, PLEX_ERROR_SEVERITY_FATAL, MMS2_ERRORMESS_ONRUNGAME, MMS2_ERRORMESS_OP_SETGAME);
			return;
		}

		while(MMS_updateMinigame2(pamaleanaSpriteTex, cubicleBackdrop, venariusSpriteTex, extraplocanSpriteTex, label, bubble, arrow, chapter2SpriteTex, chapter2SpriteTex2, chapter2SpriteTex3, chapter2SpriteTex4, fontPlate, time, &success) && !MMS2_terminateConfirm())
		{
			PLEX_updatePlex();
			if(PLEX_askingToQuit()) PLEX_terminate();
			time = PLEX_getGameTime();
		}
	}

	MMS_endMinigame2();
}

void MMS2_freeMinigameSprites()
{
	MMS2_clearPenultimateCutsceneSprites();
	MMS2_clearPlayerSprites();
	MMS2_clearCalmAreaSprites();
	MMS2_clearFinalBossSprites();
	MMS2_clearEnemySprites();
	MMS2_clearCoverSprites();
	MMS2_clearRoomSprites();
}

bool MMS_isMinigame2Running(){ return p_running; }
