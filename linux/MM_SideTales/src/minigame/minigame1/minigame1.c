#include "minigame/minigame1/function.h"

typedef enum
{
	MMS1_OUTCOME_TOOEARLY = 0,
	MMS1_OUTCOME_RIGHTTIME = 1,
	MMS1_OUTCOME_TOOLATE = 2,
	MMS1_OUTCOME_RESET = 3
} MMS1_OUTCOME;

static bool p_running = false;

static size_t p_loadingTex = 0;

static size_t p_tutorial = 0;
static size_t p_pauseTex = 0;

static PLEX_SPRITE* p_pauseAnim = NULL;

static MMS1_OUTCOME p_outcome = MMS1_OUTCOME_RIGHTTIME;

static bool p_honkHonk = false;
static bool p_engineStruggle = false;

static uint64_t p_lastTime = 0;
static double p_accumSeconds = 0;

static bool p_enablePause = false;

static int64_t p_pamEngineRevSE = -1;
static int64_t p_pamEngineRunSE = -1;
static int64_t p_pamEngineStruggleSE = -1;

static size_t p_leftBorder = 0;
static size_t p_rightBorder = 0;

// STATIC FUNCTIONS

static void p_drawBorders()
{
	if(!p_leftBorder) p_leftBorder = PLEX_loadTextureFromFileOrHeaderless(800, 1644, 255, 255, 255, 255, 0, MMS1_FILEPATH_TEX_LEFTBORDER, MMS1_FILEPATH_HEADERLESS_LEFTBORDER);
	if(!p_rightBorder) p_rightBorder = PLEX_loadTextureFromFileOrHeaderless(800, 1644, 255, 255, 255, 255, 0, MMS1_FILEPATH_TEX_RIGHTBORDER, MMS1_FILEPATH_HEADERLESS_RIGHTBORDER);

	if(PLEX_WOFFSET() || PLEX_HOFFSET())
	{
		PLEX_printTexture(0, p_leftBorder, 0, 0, 800, 1644, 0, 0, PLEX_WOFFSET(), PLEX_WH(false), false);
		PLEX_printTexture(0, p_rightBorder, 0, 0, 800, 1644, PLEX_WW(false) - PLEX_WOFFSET(), 0, PLEX_WOFFSET(), PLEX_WH(false), false);
	}else{
		if(p_leftBorder) PLEX_destroyTexture(p_leftBorder);
		if(p_rightBorder) PLEX_destroyTexture(p_rightBorder);

		p_leftBorder = 0;
		p_rightBorder = 0;
	}
}

// draws speed bar which is NOT a speedometer

static int8_t p_drawSpeedBar(const double secondsToDest, const double ETA, const double minETA, const double maxETA)
{
	const double x = PLEX_UNIT(0.5);
	const double y = PLEX_UNIT(0.5);
	const double w = PLEX_WW(true) - PLEX_UNIT(1);
	const double h = PLEX_UNIT(2);

	const double cw = PLEX_UNIT(0.2);

	double ETAperc = ETA ? 1 - (ETA - minETA)/(maxETA - minETA) : 0;
	double lateETAPerc = 1 - (MMS1_UNREALISTICALLYLATE - minETA)/(maxETA - minETA);
	double earlyETAPerc = 1 - (MMS1_UNREALISTICALLYEARLY - minETA)/(maxETA - minETA);

	double cx = 0;

	double lw = 0;

	double ea = 0;
	double ex = 0;
	double ew = 0;

	if(ETAperc < 0) ETAperc = 0;
	if(lateETAPerc < 0) lateETAPerc = 0;
	if(earlyETAPerc < 0) earlyETAPerc = 0;

	if(ETAperc > 1) ETAperc = 1;
	if(lateETAPerc > 1) lateETAPerc = 1;
	if(earlyETAPerc > 1) earlyETAPerc = 1;

	cx = x + (w * ETAperc) - cw/2.0;

	lw = w * lateETAPerc;

	ea = w * earlyETAPerc;
	ex = x + ea;
	ew = w - ea;

	// white zone

	PLEX_fillRect(MMS1_MENULAYER, x, y, w, h, 255, 255, 255, 255, true);

	// red zones

	PLEX_fillRect(MMS1_MENULAYER, x, y, lw, h, 255, 0, 0, 255, true);
	PLEX_fillRect(MMS1_MENULAYER, ex, y, ew, h, 255, 0, 0, 255, true);

	// outline and cursor

	PLEX_fillRect(MMS1_MENULAYER, cx, y, cw, h, 0, 0, 0, 255, true);
	PLEX_drawRect(MMS1_MENULAYER, x, y, w, h, 0, 0, 0, 255, PLEX_UNIT(0.1), true);

	if(cx < lw) return -1;
	if(cx > ex) return 1;

	return 0;
}

static void p_failCut(const char* const extrapMessage, const size_t pamaleanaSpriteTex, const size_t cubicleBackdrop, const size_t venariusSpriteTex, const size_t extraplocanSpriteTex, const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow)
{
	MMS_startPamaleanasCubicle(pamaleanaSpriteTex, cubicleBackdrop, venariusSpriteTex, extraplocanSpriteTex, fontPlate, label, bubble, arrow);

	MMS_extrapTalk(extrapMessage);

	MMS_pamTalk(MMS1_LANGUAGE_MINIGAME_PAMFAILEXCUSE);

	while(!PLEX_isSpriteTheaterOver())
	{
		PLEX_updateSpriteTheater(PLEX_getGameTime());
		PLEX_updatePlex();
	}

	PLEX_endSpriteTheater();
}

static void p_tooFastCut(const size_t pamaleanaSpriteTex, const size_t cubicleBackdrop, const size_t venariusSpriteTex, const size_t extraplocanSpriteTex, const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow)
{
	p_failCut(MMS1_LANGUAGE_MINIGAME_FAILFAST, pamaleanaSpriteTex, cubicleBackdrop, venariusSpriteTex, extraplocanSpriteTex, fontPlate, label, bubble, arrow);
}

static void p_tooSlowCut(const size_t pamaleanaSpriteTex, const size_t cubicleBackdrop, const size_t venariusSpriteTex, const size_t extraplocanSpriteTex, const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow)
{
	p_failCut(MMS1_LANGUAGE_MINIGAME_FAILSLOW, pamaleanaSpriteTex, cubicleBackdrop, venariusSpriteTex, extraplocanSpriteTex, fontPlate, label, bubble, arrow);
}

static void p_loadingScreen()
{
	if(!p_loadingTex) p_loadingTex = PLEX_loadTextureFromFileOrHeaderless(800, 600, 255, 255, 255, 255, 0, MMS1_FILEPATH_TEX_LOADING, MMS1_FILEPATH_HEADERLESS_LOADING);

	PLEX_printTexture(0, p_loadingTex, 0, 0, 800, 600, 0, 0, PLEX_WW(false), PLEX_WH(false), false);

	PLEX_clearMouseClicks();
	PLEX_updatePlex();
}

static void p_createPauseSprite(const uint64_t time)
{
	PLEX_ANIMATION_PLATE pausePlate;

	PLEX_ANIMATION* pauseAnim = NULL;

	p_pauseTex = PLEX_loadTextureFromFileOrHeaderless(1000, 2000, 255, 255, 255, 255, 0, MMS1_FILEPATH_TEX_PAUSED, MMS1_FILEPATH_HEADERLESS_PAUSED);

	pausePlate = PLEX_createAnimationPlate(1, 0.25, p_pauseTex);

	p_pauseAnim = PLEX_genSprite(&pausePlate);

	PLEX_addAnimation(p_pauseAnim, 1000, time);

	pauseAnim = PLEX_getAnimation(0, p_pauseAnim);

	PLEX_addAnimationFrame(0, pauseAnim);
	PLEX_addAnimationFrame(1, pauseAnim);
	PLEX_addAnimationFrame(2, pauseAnim);
	PLEX_addAnimationFrame(3, pauseAnim);
	PLEX_addAnimationFrame(2, pauseAnim);
	PLEX_addAnimationFrame(1, pauseAnim);

	PLEX_startSprite(PLEX_getNoPauseTime(), p_pauseAnim);
}

static void p_runTutorial()
{
	p_tutorial = PLEX_loadTextureFromFileOrHeaderless(1827, 1370, 255, 255, 255, 255, 0, MMS1_FILEPATH_TEX_TUTORIAL, MMS1_FILEPATH_HEADERLESS_TUTORIAL);

	while(!PLEX_leftClick() && !PLEX_KEY_press('\n') && !PLEX_CONTROLLER_down(0, SDL_CONTROLLER_BUTTON_A) && !PLEX_isTerminated())
	{
		PLEX_printTexture(MMS1_MENULAYER, p_tutorial, 0, 0, 1827, 1370, 0, 0, PLEX_WW(true), PLEX_WH(true), true);

		PLEX_updatePlex();

		if(PLEX_askingToQuit()) PLEX_terminate();
	}

	PLEX_updatePlex(); // < ensures you can't accidentally hit 'skip scene' button when skipping tutorial

	PLEX_destroyTexture(p_tutorial);
	p_tutorial = 0;
}

static bool p_checkReset()
{
	const bool pressReset = !PLEX_KEY_ctrl() && PLEX_KEY_fdown(1);

	if(pressReset)
	{
		p_outcome = MMS1_OUTCOME_RESET;
		return true;
	}

	return false;
}

static uint64_t p_updateMinigame1Time(double* secondsPass, const uint64_t time)
{
	uint64_t realTime = 0;

	MMS1_checkMarkObstructionStart(time);

	realTime = time - MMS1_obstructionStart();

	if(!p_lastTime) p_lastTime = realTime;

	*secondsPass = (realTime - p_lastTime)/1000.0;

	return realTime;
}

static uint8_t p_updateLane(const double lanePerc)
{
	if(lanePerc < 0.2) return 0;
	else if(lanePerc < 0.5) return 1;
	else if(lanePerc < 0.8) return 2;

	return 3;
}

static size_t p_updateMinigameInput(bool* accelerate, size_t* backing, const uint64_t crashCycle, const uint64_t realTime)
{
	const bool controllerRight = PLEX_CONTROLLER_count() && (PLEX_CONTROLLER_axisRight(0) || PLEX_CONTROLLER_down(0, SDL_CONTROLLER_BUTTON_DPAD_RIGHT));
	const bool controllerLeft = PLEX_CONTROLLER_count() && (PLEX_CONTROLLER_axisLeft(0) || PLEX_CONTROLLER_down(0, SDL_CONTROLLER_BUTTON_DPAD_LEFT));

	const bool pressAccel = PLEX_KEY_down('w') || PLEX_CONTROLLER_down(0, SDL_CONTROLLER_BUTTON_A);
	const bool pressBrake = PLEX_KEY_down('s') || PLEX_CONTROLLER_down(0, SDL_CONTROLLER_BUTTON_B);

	const bool pressDriftLeft = !pressBrake && (PLEX_KEY_down('a') || controllerLeft);
	const bool pressDriftRight = !pressBrake && (PLEX_KEY_down('d') || controllerRight);

	if(!PLEX_getGameTimePaused())
	{
		if(!MMS1_crashDuration())
		{
			MMS1_updatePamaleanaCycleSpeed(realTime);

			MMS1_startCarSprites(realTime);

			if(MMS1_accel() <= 10) MMS1_setPamAniIndex(0);
			else
			{
				if(MMS1_accel() <= 70) MMS1_setPamAniIndex(3);
				else MMS1_setPamAniIndex(5);
			}

			if(pressAccel)
			{
				MMS1_accelCar();

				p_engineStruggle = false;

				if(MMS1_accel() < 20)
				{
					p_engineStruggle = true;

					if(p_pamEngineRevSE == -1) MM_COMMON_stopSoundEffect(p_pamEngineRevSE);
				}else{
					if(p_pamEngineRevSE == -1) p_pamEngineRevSE = MM_COMMON_loopSoundEffect(MM_COMMON_SOUNDEFFECT_PAMENGINEREV);
				}

				*accelerate = true;
			}else{
				if(pressBrake)
				{
					*backing = 4;
					MMS1_setPamAniIndex(4);

					MMS1_deaccelCar();
				}else MMS1_accumAccel();
			}

			if(pressDriftLeft)
			{
				MMS1_driftLeft();

				MMS1_setPamAniIndex(1);
			}else{
				if(pressDriftRight)
				{
					MMS1_driftRight();

					MMS1_setPamAniIndex(2);
				}
			}

			MMS1_factorDamageDrift(MMS1_carSeatHealth());
		}else{
			p_engineStruggle = pressAccel || pressDriftLeft || pressDriftRight;

			MMS1_updatePamaleanaCrashCycle(crashCycle);

			MMS1_stopCarSprites();
		}
	}else{
		PLEX_drawSprite(0, 0, PLEX_UNIT(2), PLEX_WH(true)/2 - PLEX_WH(true)/8, PLEX_WW(true) - PLEX_UNIT(4), PLEX_WH(true)/4, p_pauseAnim, true, PLEX_getNoPauseTime());
	}

	return MMS1_pamAniIndex();
}

static void p_updateEngineSE(const bool accelerate)
{
	if(!accelerate && p_pamEngineRevSE != -1)
	{
		MM_COMMON_stopSoundEffect(p_pamEngineRevSE);
		p_pamEngineRevSE = -1;
	}

	if(MMS1_accel())
	{
		if(p_pamEngineRunSE == -1) p_pamEngineRunSE = MM_COMMON_loopSoundEffect(MM_COMMON_SOUNDEFFECT_PAMENGINERUN);
	}else{
		if(p_pamEngineRunSE != -1)
		{
			MM_COMMON_stopSoundEffect(p_pamEngineRunSE);
			p_pamEngineRunSE = -1;
		}
	}

	MM_COMMON_setSoundEffectVolume(MMS1_accel()/MMS1_ACCEL_MAX, p_pamEngineRunSE);
}

static void p_updateWarnings(const int8_t speedRank, const size_t lane, const size_t fontPlate, const uint64_t realTime)
{
	if(realTime % MMS1_REALTIME_SEED < MMS1_REALTIME_SEED/2)
	{
		if(lane < 2)
		{
			PLEX_drawTextBoxTinted(MMS1_MENULAYER, MMS1_LANGUAGE_MINIGAME_WRONGLANEWARNING, PLEX_STANDNUM_FW, PLEX_STANDNUM_FH, 255, 255, 50, 255, 0, 0, 0, 255, PLEX_UNIT(1), PLEX_UNIT(3), PLEX_UNIT(7), PLEX_UNIT(1), PLEX_UNIT(0.5), PLEX_UNIT(1), 0.125, 0.125, 1, 1, PLEX_UNIT(0.05), PLEX_LANGUAGE_ALPHASTRING, fontPlate, 0, 0, 0, 0, 0, 0, true);
		}

		if(speedRank == -1)
		{
			PLEX_drawTextBoxTinted(MMS1_MENULAYER, MMS1_LANGUAGE_MINIGAME_TOOSLOWWARNING, PLEX_STANDNUM_FW, PLEX_STANDNUM_FH, 200, 50, 50, 255, 0, 0, 0, 255, PLEX_WW(true) - PLEX_UNIT(8), PLEX_UNIT(3), PLEX_UNIT(7), PLEX_UNIT(1), PLEX_UNIT(0.5), PLEX_UNIT(1), 0.125, 0.125, 1, 1, PLEX_UNIT(0.05), PLEX_LANGUAGE_ALPHASTRING, fontPlate, 0, 0, 0, 0, 0, 0, true);
		}

		if(speedRank == 1)
		{
			PLEX_drawTextBoxTinted(MMS1_MENULAYER, MMS1_LANGUAGE_MINIGAME_TOOFASTWARNING, PLEX_STANDNUM_FW, PLEX_STANDNUM_FH, 200, 50, 50, 255, 0, 0, 0, 255, PLEX_WW(true) - PLEX_UNIT(8), PLEX_UNIT(3), PLEX_UNIT(7), PLEX_UNIT(1), PLEX_UNIT(0.5), PLEX_UNIT(1), 0.125, 0.125, 1, 1, PLEX_UNIT(0.05), PLEX_LANGUAGE_ALPHASTRING, fontPlate, 0, 0, 0, 0, 0, 0, true);
		}

		if(p_engineStruggle)
		{
			PLEX_drawTextBoxTinted(MMS1_MENULAYER, MMS1_LANGUAGE_MINIGAME_ENGINEREV, PLEX_STANDNUM_FW, PLEX_STANDNUM_FH, 0, 0, 0, 100, 100, 100, 100, 100, PLEX_UNIT(1), PLEX_UNIT(5), PLEX_WW(true) - PLEX_UNIT(1), PLEX_UNIT(1), PLEX_UNIT(0.5), PLEX_UNIT(1), 0.125, 0.125, 1, 1, PLEX_UNIT(0.05), PLEX_LANGUAGE_ALPHASTRING, fontPlate, 0, 0, 0, 0, 0, 0, true);

			if(p_pamEngineStruggleSE == -1) p_pamEngineStruggleSE = MM_COMMON_loopSoundEffect(MM_COMMON_SOUNDEFFECT_PAMENGINESTRUGGLE);
		}

		if(MMS1_warnPlayer())
		{
			PLEX_drawTextBoxTinted(MMS1_MENULAYER, MMS1_LANGUAGE_MINIGAME_ONCOMINGTRAFFIC, PLEX_STANDNUM_FW, PLEX_STANDNUM_FH, 200, 50, 50, 255, 0, 0, 0, 255, PLEX_WW(true)/2 - PLEX_UNIT(4), PLEX_UNIT(3), PLEX_UNIT(7), PLEX_UNIT(1), PLEX_UNIT(0.5), PLEX_UNIT(1), 0.125, 0.125, 1, 1, PLEX_UNIT(0.05), PLEX_LANGUAGE_ALPHASTRING, fontPlate, 0, 0, 0, 0, 0, 0, true);

			if(!p_honkHonk)
			{
				MM_COMMON_playSoundEffect(MM_COMMON_SOUNDEFFECT_SURREALHONKHONK);
				p_honkHonk = true;
			}
		}
	}else p_honkHonk = false;

	if(!p_engineStruggle && p_pamEngineStruggleSE)
	{
		MM_COMMON_stopSoundEffect(p_pamEngineStruggleSE);
		p_pamEngineStruggleSE = -1;
	}
}

static bool p_updateOutcome(const PLEX_MPREC dist, const PLEX_MPREC ETA, const PLEX_MPREC minETA, const PLEX_MPREC maxETA)
{
	p_outcome = MMS1_OUTCOME_RIGHTTIME;

	if(ETA > MMS1_UNREALISTICALLYLATE) p_outcome = MMS1_OUTCOME_TOOEARLY;
	if(ETA < MMS1_UNREALISTICALLYEARLY) p_outcome = MMS1_OUTCOME_TOOLATE;

	if(dist >= MMS1_FULLDIST || minETA > MMS1_UNREALISTICALLYLATE)
	{
		if(p_outcome == MMS1_OUTCOME_RIGHTTIME) MMS_MMS1MarkEnd();
		return false;
	}

	return true;
}

static void p_updateDraw(const double secondsPass, const size_t lane, const PLEX_MPREC ETA, const PLEX_MPREC minETA, const PLEX_MPREC maxETA, const size_t fontPlate, const uint64_t realTime)
{
	int8_t speedRank = 0;

	p_drawBorders();

	speedRank = p_drawSpeedBar(secondsPass, ETA, minETA, maxETA);

	p_updateWarnings(speedRank, lane, fontPlate, realTime);
}

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

uint64_t MMS1_calcAnimationCycle(const uint64_t min, const uint64_t max)
{
	const double perc = (MMS1_ACCEL_MAX - MMS1_accel())/MMS1_ACCEL_MAX;

	return min + (max - min) * perc;
}

size_t MMS1_calcOverroadLayer(const double y, const double h, const size_t baselayer)
{
	const double bottom = y + h;

	return PLEX_WH(true) - bottom + MMS1_MENULAYER + baselayer;
}

bool MMS_beginMinigame1(const size_t chapter1SpriteTex, const size_t pamaleanaSpriteTex, const size_t venariusSpriteTex, const size_t extraplocanSpriteTex, const uint64_t time)
{
	p_loadingScreen();

	MMS1_beginCollision(time);
	MMS1_beginPamAndCar(chapter1SpriteTex, pamaleanaSpriteTex, time);
	MMS1_beginObstructionManager(chapter1SpriteTex, time);
	MMS1_beginEnvironment(time);

	p_createPauseSprite(time);

	p_runTutorial();

	MMS1_resetCarDamage();

	MM_COMMON_playTheme((size_t)MM_COMMON_THEMEID_PANIC);

	if(PLEX_pauseDisabled())
	{
		PLEX_enablePause();
		p_enablePause = true;
	}

	p_outcome = MMS1_OUTCOME_RIGHTTIME;

	p_lastTime = 0;
	p_accumSeconds = 0;

	p_pamEngineRevSE = -1;
	p_pamEngineRunSE = -1;
	p_pamEngineStruggleSE = -1;

	MMS_MMS1MarkMinigame();

	return true;
}

bool MMS_updateMinigame1(const size_t fontPlate, const uint64_t time)
{
	const PLEX_RECT playerRegion = MMS1_playerRegion();

	const double accel = MMS1_accel();
	const double accelMod = MMS1_accelMod();
	const double dist = MMS1_dist();

	const double distLeft = MMS1_FULLDIST - dist;
	const double secondsToDest = accel && accelMod ? distLeft/(accel * accelMod) : distLeft;
	const double ETA = p_accumSeconds + secondsToDest;

	const double distLeftPerc = distLeft/MMS1_FULLDIST;
	const double completePerc = 1 - distLeftPerc;

	const double minETA = p_accumSeconds + distLeft/MMS1_MINETADIV;
	const double maxETA = p_accumSeconds + distLeft/MMS1_MAXETADIV;

	const size_t phase = completePerc/0.2;
	const double phasePerc = (completePerc - (phase * 0.2))/0.2;

	uint64_t crashCycle = 0;

	double lanePerc = (playerRegion.origin.x + playerRegion.dimens.w/2)/(double)PLEX_WIDTHUNITMAX();
	size_t lane = 0;

	double secondsPass = 0;

	size_t backing = 0;

	bool accelerate = false;

	uint64_t realTime = 0;

	if(p_checkReset()) return false;

	realTime = p_updateMinigame1Time(&secondsPass, time);

	crashCycle = MMS1_checkUpdateCrash(realTime);

	lane = p_updateLane(lanePerc);

	p_updateMinigameInput(&accelerate, &backing, crashCycle, realTime);

	p_updateEngineSE(accelerate);

	MMS1_updateCollision(backing, time);

	MMS1_updatePamAndCar(backing, realTime);

	MMS1_updateEnvironment(phase, phasePerc, completePerc, realTime);

	MMS1_updateObstructionManager(phase, lane, realTime);

	p_updateDraw(secondsPass, lane, ETA, minETA, maxETA, fontPlate, realTime);

	if(!p_updateOutcome(dist, ETA, minETA, maxETA)) return false;

	p_lastTime = realTime;

	p_accumSeconds += secondsPass;

	MM_COMMON_update();

	if(MMS_MMS2Unlocked() && MM_COMMON_skipButton(fontPlate))
	{
		p_outcome = MMS1_OUTCOME_RIGHTTIME;
		return false;
	}

	return true;
}

void MMS_endMinigame1()
{
	if(p_enablePause)
	{
		PLEX_disablePause();
		p_enablePause = false;
	}

	MM_COMMON_playTheme(MM_COMMON_THEMEID_NONE);

	MM_COMMON_stopSoundEffect(p_pamEngineRevSE);
	MM_COMMON_stopSoundEffect(p_pamEngineRunSE);
	MM_COMMON_stopSoundEffect(p_pamEngineStruggleSE);

	MMS1_endPamAndCar();
	MMS1_endEnvironment();
	MMS1_endCollision();
	MMS1_endObstructionManager();

	if(p_pauseAnim != NULL) PLEX_destroySprite(&p_pauseAnim);

	if(p_leftBorder) PLEX_destroyTexture(p_leftBorder);
	if(p_rightBorder) PLEX_destroyTexture(p_rightBorder);

	if(p_loadingTex) PLEX_destroyTexture(p_loadingTex);

	if(p_pauseTex) PLEX_destroyTexture(p_pauseTex);

	p_loadingTex = 0;

	p_pauseTex = 0;

	p_leftBorder = 0;
	p_rightBorder = 0;

	p_pamEngineRevSE = -1;
	p_pamEngineRunSE = -1;
	p_pamEngineStruggleSE = -1;
}

void MMS_runMinigame1(const size_t chapter1SpriteTex, const size_t pamaleanaSpriteTex, const size_t cubicleBackdrop, const size_t venariusSpriteTex, const size_t extraplocanSpriteTex, const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow)
{
	uint64_t time = PLEX_getGameTime();

	p_running = false;

	while(!PLEX_isTerminated())
	{
		MMS_beginMinigame1(chapter1SpriteTex, pamaleanaSpriteTex, venariusSpriteTex, extraplocanSpriteTex, time);

		while(MMS_updateMinigame1(fontPlate, time) && !PLEX_isTerminated())
		{
			PLEX_updatePlex();
			if(PLEX_askingToQuit()) PLEX_terminate();
			time = PLEX_getGameTime();
		}

		MMS_endMinigame1();

		if(PLEX_isTerminated()) return;

		if(p_outcome != MMS1_OUTCOME_RIGHTTIME)
		{
			MMS1_resetObstructionStart();
			p_lastTime = 0;
		}

		switch(p_outcome)
		{
			case MMS1_OUTCOME_TOOEARLY: p_tooSlowCut(pamaleanaSpriteTex, cubicleBackdrop, venariusSpriteTex, extraplocanSpriteTex, fontPlate, label, bubble, arrow); break;
			case MMS1_OUTCOME_RIGHTTIME: return; // < this breaks the 'while' as well, do not make 'break'. Do not get rid of this
			case MMS1_OUTCOME_TOOLATE: p_tooFastCut(pamaleanaSpriteTex, cubicleBackdrop, venariusSpriteTex, extraplocanSpriteTex, fontPlate, label, bubble, arrow); break;
			default: break;
		}
	}
}

bool MMS_isMinigame1Running(){ return p_running; }
