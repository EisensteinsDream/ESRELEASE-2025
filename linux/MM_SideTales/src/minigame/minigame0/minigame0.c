#include "minigame/minigame0/minigame0.h"

static bool p_running = false;

static PLEX_SPRITE* p_coffeeIcon = NULL;

static uint64_t p_lastTime = 0;
static uint64_t p_startTime = 0;

static size_t p_tutorial = 0;
static size_t p_pause = 0;

static bool p_tutorialOn = true;

static bool p_end = false;
static int64_t p_fade = -1;

static uint32_t p_floorTileW = 0;
static uint32_t p_floorTileH = 0;

static size_t p_floorTiles = 0;

static size_t p_leftBorder = 0;
static size_t p_rightBorder = 0;

// static functions

// BEGIN FUNCTIONS

static void p_drawFloor(const double perc)
{
	const uint32_t w = PLEX_WW(true);
	const uint32_t h = PLEX_WH(true);

	const double revPerc = 1 - perc;

	const uint8_t fr = 60 * perc;
	const uint8_t fg = 30 * revPerc;
	const uint8_t fb = 60 * revPerc;

	const uint8_t br = fr;
	const uint8_t bg = 60 * revPerc;
	const uint8_t bb = 30 * revPerc;

	const uint32_t tileD = PLEX_UNIT(1.5);

	if(!p_floorTiles)
	{
		p_floorTiles = PLEX_createGeneratedTexture(w, h, 0, 0, 0, 0);

		PLEX_setTextureTarget(p_floorTiles);

		for(uint32_t x = 0; x < w; x += tileD)
		{
			const bool nudge = x/tileD % 2 == 1;

			for(int64_t y = 0; y < h; y += tileD)
			{
				const bool nudge2 = y/tileD % 2 == 1;

				const bool nudgeOp = (nudge && nudge2) || (!nudge && !nudge2);

				if(nudgeOp) continue; // < this keeps the nudged tiles transparent. Imagine as the black tiles on a chess board

				// the texture is white tiles that are tinted on draw

				PLEX_fillRect(0, x, y, tileD, tileD, 255, 255, 255, 255, false);
				PLEX_drawRect(0, x, y, tileD, tileD, 0, 0, 0, 255, PLEX_UNIT(0.05), false);
			}
		}

		PLEX_unsetTextureTarget();

		p_floorTileW = w;
		p_floorTileH = h;
	}

	PLEX_fillRect(MMS0_DRAWLAYER_FLOORBACK, 0, 0, w, h, br, bg, bb, 255, true);
	PLEX_printTextureTinted(MMS0_DRAWLAYER_FLOORFRONT, p_floorTiles, 0, 0, p_floorTileW, p_floorTileH, 0, 0, w, h, fr, fg, fb, true);
}

static void p_createCoffeeSprite(const size_t chapter0spriteTex, const uint64_t time)
{
	PLEX_ANIMATION_PLATE coffee = PLEX_createAnimationPlate(0.125, 0.125, chapter0spriteTex);

	PLEX_ANIMATION* coffeeAnim = NULL;

	if(p_coffeeIcon != NULL) return;

	p_coffeeIcon = PLEX_genSprite(&coffee);

	PLEX_addAnimation(p_coffeeIcon, 1, PLEX_getGameTime());

	coffeeAnim = PLEX_getAnimation(0, p_coffeeIcon);

	PLEX_addAnimationFrame(33, coffeeAnim);
}

static void p_generateTutorialBack()
{
	p_tutorial = PLEX_loadTextureFromFileOrHeaderless(1827, 1370, 255, 255, 255, 255, 0, MMS0_FILEPATH_TUTORIAL, MMS0_FILEPATH_HEADERLESS_CHAPTER0TUTORIAL);
}

static void p_generatePauseBack()
{
	p_pause = PLEX_loadTextureFromFileOrHeaderless(1827, 1370, 255, 255, 255, 255, 0, MMS0_FILEPATH_PAUSE, MMS0_FILEPATH_HEADERLESS_PAUSE);
}

static void p_generateBorder()
{
	p_leftBorder = PLEX_loadTextureFromFileOrHeaderless(800, 1644, 255, 255, 255, 255, 0, MMS0_FILEPATH_LEFTBORDER, MMS0_FILEPATH_HEADERLESS_LEFTBORDER);

	p_rightBorder = PLEX_loadTextureFromFileOrHeaderless(800, 1644, 255, 255, 255, 255, 0, MMS0_FILEPATH_RIGHTBORDER, MMS0_FILEPATH_HEADERLESS_RIGHTBORDER);
}

static void p_generateGraphics(const size_t chapter0spriteTex, const size_t pamaleanaSpriteTex, const uint64_t time)
{
	p_generateTutorialBack();
	p_generatePauseBack();

	p_generateBorder();

	p_createCoffeeSprite(chapter0spriteTex, time);

	MMS0_createEnemySprite(chapter0spriteTex, time);
	MMS0_createTableSprite(chapter0spriteTex, time);
	MMS0_createThePrizeSprite(chapter0spriteTex, time);

	MMS0_createPamaleanaSprite(pamaleanaSpriteTex, time);

	p_fade = -1;
}

static void p_startPositions()
{
	MMS0_startThePrizePositions(); // < keep before start crash positions
	MMS0_startPlayerPosition(); // < keep before start crash positions

	MMS0_startCrashPositions();

	MMS0_startTablePositions(); // < keep after start crash positions
}

static void p_setStartingConditions(const uint64_t time)
{
	MMS0_startEnemyValues();
	MMS0_startCoffee();

	p_startPositions();

	p_lastTime = time;
	p_startTime = time;

	p_end = false;

	p_tutorialOn = true;
}

static void p_drawBorder()
{
	if(PLEX_WOFFSET())
	{
		PLEX_printTexture(0, p_leftBorder, 0, 0, 800, 1644, 0, 0, PLEX_WOFFSET(), PLEX_WH(false), false);
		PLEX_printTexture(0, p_rightBorder, 0, 0, 800, 1644, PLEX_WW(false) -  PLEX_WOFFSET(), 0, PLEX_WOFFSET(), PLEX_WH(false), false);
	}
}

// UPDATE FUNCTIONS

static bool p_checkFade(bool* victory, const uint64_t time)
{
	if(p_fade != -1 && PLEX_screenEffectOver(p_fade, time))
	{
		*victory = true;
		p_fade = -1;
		return true;
	}

	return false;
}

static bool p_checkTutorial(const double perc, const uint64_t time)
{
	if(p_tutorialOn)
	{
		uint32_t fw = 0, fh = 0;

		PLEX_textureWH(p_tutorial, &fw, &fh);

		p_drawFloor(perc);

		PLEX_printTexture(0, p_tutorial, 0, 0, fw, fh, 0, 0, PLEX_WW(true), PLEX_WH(true), true);

		if(PLEX_leftClick() || PLEX_KEY_press('\n') || PLEX_CONTROLLER_down(0, SDL_CONTROLLER_BUTTON_A)) p_tutorialOn = false;

		PLEX_getUniversalThemeStopSignal();

		p_startTime = time;
		p_lastTime = time;

		return true;
	}

	return false;
}

static bool p_checkSkip(bool* victory, const size_t fontPlate)
{
	if(MMS_MMS1Unlocked() && MM_COMMON_skipButton(fontPlate))
	{
		*victory = true;
		return true;
	}

	return false;
}

static void p_checkEnd(double* perc, const uint64_t time)
{
	if(*perc >= 1)
	{
		*perc = 1;

		if(!p_end)
		{
			for(size_t ze = 0; ze < MMS0_enemyCapacity(); ++ze)
			{
				if(!MMS0_enemyDead(ze)) break;
			}

			p_fade = PLEX_doScreenEffect(PLEX_SCREENEFFECT_TINTFADE, 0, 0, 0, 255, false, false, 3000, 0, time);

			p_end = true;
		}
	}
}

static void p_reset(bool* victory)
{
	MM_COMMON_playTheme(MM_COMMON_THEMEID_NONE);
	MMS0_stopGulpEffect();
	*victory = false;
}

static bool p_checkDeath(bool* victory)
{
	if(MMS0_coffeePerc() <= 0)
	{
		p_reset(victory);
		return true;
	}

	return false;
}

static bool p_checkReset(bool* victory)
{
	if(PLEX_KEY_fdown(1))
	{
		p_reset(victory);
		return true;
	}

	return false;
}

static void p_checkMusic()
{
	if(MM_COMMON_getTheme() == MM_COMMON_THEMEID_NONE) MM_COMMON_playTheme((size_t)MM_COMMON_THEMEID_PANIC);
}

static void p_drawCoffeeBar(const uint64_t time)
{
	PLEX_drawSprite(0, 0, PLEX_UNIT(1), PLEX_UNIT(1), PLEX_UNIT(2), PLEX_UNIT(2), p_coffeeIcon, true, time);

	PLEX_drawChargeBar(0, MMS0_coffeePerc(), PLEX_UNIT(1), PLEX_UNIT(4), PLEX_UNIT(2), PLEX_WH(true) - PLEX_UNIT(6), 255, 255, 255, 200, 60, 50, 30, 200, PLEX_UNIT(0.05), true, true);
}

// this function checks for the possibility of movement but does not check if movement is happening. If there is a collision between the rectangle at 'index' and any other rectangle 'target' will be it's index. Otherwise it'll be -1.

static bool p_checkMovement(const double momX, const double momY, const size_t index, const size_t count, int64_t* target, PLEX_RECT* rects)
{
	PLEX_RECT rect = rects[index];

	*target = -1;

	rect.origin.x += momX;
	rect.origin.y += momY;

	// movement is cancelled if out of range

	if(rect.origin.x < 0) return false;
	if(rect.origin.y < 0) return false;
	if(rect.origin.x + rect.dimens.w > PLEX_WIDTHUNITMAX()) return false;
	if(rect.origin.y + rect.dimens.h > PLEX_HEIGHTUNITMAX()) return false;

	// movement is cancelled if the perspective rectangle collides with any other rectangle on the field. A target index number the colliding rectangle is returned

	for(size_t ze = 0; ze < count; ++ze)
	{
		PLEX_RECT rect2;

		if(ze == index) continue;

		rect2 = rects[ze];

		if(PLEX_rectCollisionNoMove(rect, rect2))
		{
			*target = ze;
			return false;
		}
	}

	return true; // < no collision
}

// updates potential movement of all objects
static void p_updateMovement(PLEX_MPREC* tmomXs, PLEX_MPREC* tmomYs, PLEX_MPREC* emomXs, PLEX_MPREC* emomYs, const PLEX_MPREC momX, const PLEX_MPREC momY)
{
	PLEX_RECT playerSpace = MMS0_getPlayerSpace();

	PLEX_RECT moveRects[16]; // the prize, 1 player, 4 tables, up to 10 enemies

	size_t moveRectCount = 6; // the prize, 1 player, 4 tables

	int64_t target = -1;

	// all 'move rectangles' are loaded into an array

	moveRects[0] = MMS0_prizeRect();

	moveRects[1] = playerSpace;

	moveRects[2] = MMS0_getTableSpace(0);
	moveRects[3] = MMS0_getTableSpace(1);
	moveRects[4] = MMS0_getTableSpace(2);
	moveRects[5] = MMS0_getTableSpace(3);

	for(size_t ze = 0; ze < MMS0_enemyCapacity(); ++ze)
	{
		// ensures dead enemies don't invisibly block the player
		if(MMS0_enemyDead(ze))
		{
			moveRects[6 + ze].origin.x = -100;
			moveRects[6 + ze].origin.y = -100;
		}else{
			moveRects[6 + ze] = MMS0_getEnemyRect(ze);
		}

		++moveRectCount;
	}

	// table movement - keep before player and enemy movement

	for(size_t ze = 0; ze < 4; ++ze)
	{
		if(p_checkMovement(tmomXs[ze], tmomYs[ze], ze + 2, moveRectCount, &target, moveRects))
		{
			MMS0_moveTable(ze);
		}else{
			// target < 6 means anything that's not an enemy. Tables do not stop at enemy but instead kill enemy on collision if moving.

			if(target < 6) MMS0_setTableDirection(MMS0_DIRECTION_NONE, ze);
			else
			{
				if(MMS0_getTableDirec(ze) != MMS0_DIRECTION_NONE) MMS0_killEnemy(target - 6, ze);

				MMS0_moveTable(ze);
			}
		}
	}

	// player movement

	// target > 5 means the player and all tables. To prevent the player from continually getting stuck or enemies getting stuck in the player, enemy/player collision is ignored.

	if(p_checkMovement(momX, momY, 1, moveRectCount, &target, moveRects) || target > 5)
	{
		playerSpace.origin.x += momX;
		playerSpace.origin.y += momY;

		MMS0_setPlayerSpace(playerSpace);
	}

	// enemy collision is checked. Of course, dead enemies are ignored (enemies can be killed between checking for rectangles and table collision).

	for(size_t ze = 0; ze < MMS0_enemyCapacity(); ++ze)
	{
		PLEX_RECT moveRect;

		if(MMS0_enemyDead(ze)) continue;

		moveRect = MMS0_getEnemyRect(ze);

		// first checks if enemy is colliding with player or other enemy
		if(p_checkMovement(emomXs[ze], emomYs[ze], ze + 6, moveRectCount, &target, moveRects) || target > 5 || target == 1)
		{
			MMS0_moveEnemy(ze, emomXs[ze], emomYs[ze]);

			// 0 == the prize, this way enemies switch to vertical movement if they think the can get to the prize
			if(!MMS0_enemyVert(ze) && moveRect.origin.x + moveRect.dimens.w > moveRects[0].origin.x && moveRect.origin.x < moveRects[0].origin.x + moveRects[0].dimens.w) MMS0_setVert(ze);
		}else{
			// sets the enemy to drinking mode if they collide with the prize and the prize is not moving
			if(!target && MMS0_prizeDirection() == MMS0_DIRECTION_NONE) MMS0_setDrinking(ze);

			// factors the enemy colliding with the table. If the table is moving this also kills the enemy. It checks this a second time because the table may move between checking the first time and this time. Otherwise, the enemy flips to horizontal movement.
			if(target >= 2 && target <= 5)
			{
				const size_t tableIndex = target - 2;

				if(MMS0_getTableDirec(tableIndex) != MMS0_DIRECTION_NONE || MMS0_getTableReset(tableIndex)) MMS0_killEnemy(ze, tableIndex);
				else MMS0_setHorz(ze);

				// factors the enemy being pushed by the player
				if(MMS0_isPlayerPushing()) MMS0_moveEnemy(ze, emomXs[ze], emomYs[ze]);
			}
		}
	}
}

static void p_checkPause()
{
	if(PLEX_getGameTimePaused())
	{
		uint32_t fw = 0, fh = 0;

		PLEX_textureWH(p_pause, &fw, &fh);

		PLEX_printTexture(0, p_pause, 0, 0, fw, fh, 0, 0, PLEX_WW(true), PLEX_WH(true), true);
	}
}

static void p_updateObjects(const double perc, const double tableMomentum, const double enemyMomentum, const double momentum, const uint64_t time)
{
	// momentum = per second movement

	// table momentums

	PLEX_MPREC tmomXs[MMS0_TABLE_MAX];
	PLEX_MPREC tmomYs[MMS0_TABLE_MAX];

	// player momentums

	PLEX_MPREC momX = 0;
	PLEX_MPREC momY = 0;

	// enemy momentums

	PLEX_MPREC emomXs[MMS0_ENEMY_MAX];
	PLEX_MPREC emomYs[MMS0_ENEMY_MAX];

	if(PLEX_getGameTimePaused()) return;

	MMS0_updatePlayer(&momX, &momY, momentum, time);

	// the prize does not need to return a momentum because it stops for nothing, therefore does not need to check collision for move

	MMS0_updateThePrize(momentum, tableMomentum, time);

	for(size_t ze = 0; ze < MMS0_TABLE_MAX; ++ze) MMS0_updateTable(tableMomentum, tmomXs, tmomYs, ze,  time);

	for(size_t ze = 0; ze < MMS0_enemyCapacity(); ++ze) MMS0_updateEnemy(enemyMomentum, emomXs, emomYs, ze, time - p_lastTime, time);

	p_updateMovement(tmomXs, tmomYs, emomXs, emomYs, momX, momY);
}

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

bool MMS_beginMinigame0(const size_t chapter0spriteTex, const size_t pamaleanaSpriteTex, const uint64_t time)
{
	if(p_running) return true;

	p_generateGraphics(chapter0spriteTex, pamaleanaSpriteTex, time);

	p_setStartingConditions(time);

	MMS_MMS0MarkMinigame();

	p_running = true;

	return true;
}

bool MMS_updateMinigame0(bool* victory, const size_t fontPlate, const uint64_t time)
{
	const uint64_t turnTime = time - p_lastTime;

	double perc = MMS0_enemiesKilled()/(double)MMS0_ENEMY_STOPGEN;

	const double enemySpeed = MMSO_ENEMY_MINWALKSPEED + ((MMSO_ENEMY_MAXWALKSPEED - MMSO_ENEMY_MINWALKSPEED) * perc);

	const double momentum = turnTime * MMS0_MOMENTUM_PLAYER;
	const double enemyMomentum = turnTime * enemySpeed;
	const double tableMomentum = turnTime * MMS0_MOMENTUM_TABLE;

	if(!p_running) return false;

	p_drawBorder();

	if(p_checkFade(victory, time)) return false;

	if(p_checkTutorial(perc, time)) return true;

	if(p_checkSkip(victory, fontPlate)) return false;

	p_checkEnd(&perc, time);

	if(p_checkDeath(victory)) return false;
	if(p_checkReset(victory)) return false;

	p_checkMusic();

	p_drawCoffeeBar(time);

	p_updateObjects(perc, tableMomentum, enemyMomentum, momentum, time);

	MMS0_updateAllEnemies(perc);

	p_checkPause();

	p_drawFloor(perc);

	p_lastTime = time;

	MM_COMMON_update();

	return true;
}

void MMS_endMinigame0()
{
	if(!p_running) return;

	PLEX_destroyTexture(p_tutorial);
	PLEX_destroyTexture(p_pause);

	PLEX_destroyTexture(p_floorTiles);

	PLEX_destroyTexture(p_leftBorder);
	PLEX_destroyTexture(p_rightBorder);

	p_tutorial = 0;
	p_pause = 0;

	p_floorTiles = 0;

	p_leftBorder = 0;
	p_rightBorder = 0;

	p_running = false;
}

void MMS_runMinigame0(const size_t chapter0spriteTex, const size_t pamaleanaSpriteTex, const size_t fontPlate)
{
	uint64_t time = PLEX_getGameTime();

	bool victory = false;

	p_running = false;

	while(!victory && !PLEX_isTerminated())
	{
		MMS_beginMinigame0(chapter0spriteTex, pamaleanaSpriteTex, time);

		while(MMS_updateMinigame0(&victory, fontPlate, time) && !PLEX_isTerminated())
		{
			PLEX_updatePlex();
			if(PLEX_askingToQuit()) PLEX_terminate();
			time = PLEX_getGameTime();
		}

		if(victory) MMS_MMS0MarkEnd();

		MMS_endMinigame0();
	}
}
uint32_t MMS0_drawLayer(const PLEX_RECT area)
{
	return 1 + PLEX_HEIGHTUNITMAX() - (area.origin.y + area.dimens.h);
}

void MMS0_freeMinigameSprites()
{
	MMS0_freeEnemySprite();
	MMS0_freeTableSprite();
	MMS0_freePrizeSprite();
	MMS0_freePlayerSprite();

	PLEX_destroySprite(&p_coffeeIcon);
}

bool MMS_isMinigame0Running(){ return p_running; }
