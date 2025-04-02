#include "minigame/minigame1/function.h"

static size_t p_domeParallaxTex = 0;
static size_t p_domeParallaxTex2 = 0;
static size_t p_skyline = 0;

static size_t p_backdrop0 = 0;
static size_t p_backdrop1 = 0;
static size_t p_backdrop2 = 0;
static size_t p_backdrop3 = 0;
static size_t p_backdrop4 = 0;

static size_t p_road0Tex = 0;
static size_t p_road1Tex = 0;
static size_t p_road2Tex = 0;
static size_t p_road3Tex = 0;
static size_t p_road4Tex = 0;

static size_t p_wall3Tex = 0;
static size_t p_wall4Tex = 0;

static size_t p_windshieldBreak = 0;

static size_t p_glassShatterLevel = 0;

static PLEX_SPRITE* p_road0 = NULL;
static PLEX_SPRITE* p_road1 = NULL;
static PLEX_SPRITE* p_road2 = NULL;
static PLEX_SPRITE* p_road3 = NULL;
static PLEX_SPRITE* p_road4 = NULL;

static PLEX_SPRITE* p_wall4 = NULL;
static PLEX_SPRITE* p_wall3 = NULL;

static PLEX_SPRITE* p_domeParallax = NULL;
static PLEX_SPRITE* p_domeParallax2 = NULL;

static void p_texLoadWindshieldEffect()
{
	if(!p_windshieldBreak) p_windshieldBreak = PLEX_loadTextureFromFileOrHeaderless(1920, 3240, 255, 255, 255, 255, 0, MMS1_FILEPATH_TEX_WINDSHIELD, MMS1_FILEPATH_HEADERLESS_WINDSHIELD);
}

static void p_loadSkybackdrops()
{
	if(!p_skyline) p_skyline = PLEX_loadTextureFromFileOrHeaderless(800, 500, 255, 255, 255, 255, 0, MMS1_FILEPATH_TEX_SKYLINE, MMS1_FILEPATH_HEADERLESS_SKYLINE);

	if(!p_backdrop0) p_backdrop0 = PLEX_loadTextureFromFileOrHeaderless(3840, 1644, 255, 255, 255, 255, 0, MMS1_FILEPATH_TEX_PHASE0, MMS1_FILEPATH_HEADERLESS_PHASE0);
	if(!p_backdrop1) p_backdrop1 = PLEX_loadTextureFromFileOrHeaderless(3840, 1644, 255, 255, 255, 255, 0, MMS1_FILEPATH_TEX_PHASE1, MMS1_FILEPATH_HEADERLESS_PHASE1);
	if(!p_backdrop2) p_backdrop2 = PLEX_loadTextureFromFileOrHeaderless(3840, 1644, 255, 255, 255, 255, 0, MMS1_FILEPATH_TEX_PHASE2, MMS1_FILEPATH_HEADERLESS_PHASE2);
	if(!p_backdrop3) p_backdrop3 = PLEX_loadTextureFromFileOrHeaderless(3840, 1644, 255, 255, 255, 255, 0, MMS1_FILEPATH_TEX_PHASE3, MMS1_FILEPATH_HEADERLESS_PHASE3);
	if(!p_backdrop4) p_backdrop4 = PLEX_loadTextureFromFileOrHeaderless(3840, 1644, 255, 255, 255, 255, 0, MMS1_FILEPATH_TEX_PHASE4, MMS1_FILEPATH_HEADERLESS_PHASE4);
}

static void p_createDomeSprite(const uint64_t time)
{
	PLEX_ANIMATION_PLATE domeParallaxPlate;
	PLEX_ANIMATION_PLATE domeParallaxPlate2;

	PLEX_ANIMATION* domeParallaxAnimation = NULL;
	PLEX_ANIMATION* domeParallaxAnimation2 = NULL;

	if(!p_domeParallaxTex) p_domeParallaxTex = PLEX_loadTextureFromFileOrHeaderless(1560, 200, 255, 255, 255, 255, 0, MMS1_FILEPATH_TEX_PARALLAXDOME, MMS1_FILEPATH_HEADERLESS_PARALLAXDOME);
	if(!p_domeParallaxTex2) p_domeParallaxTex2 = PLEX_loadTextureFromFileOrHeaderless(1560, 200, 255, 255, 255, 255, 0, MMS1_FILEPATH_TEX_PARALLAXDOME2, MMS1_FILEPATH_HEADERLESS_PARALLAXDOME2);

	domeParallaxPlate = PLEX_createAnimationPlate(0.5, 1, p_domeParallaxTex);
	domeParallaxPlate2 = PLEX_createAnimationPlate(0.5, 1, p_domeParallaxTex2);

	p_domeParallax = PLEX_genSprite(&domeParallaxPlate);
	p_domeParallax2 = PLEX_genSprite(&domeParallaxPlate2);

	PLEX_addAnimation(p_domeParallax, 400, time);

	domeParallaxAnimation = PLEX_getAnimation(0, p_domeParallax);

	PLEX_addAnimationFrame(0, domeParallaxAnimation);
	PLEX_addAnimationFrame(1, domeParallaxAnimation);

	PLEX_startSprite(time, p_domeParallax);

	PLEX_addAnimation(p_domeParallax2, 400, time);

	domeParallaxAnimation2 = PLEX_getAnimation(0, p_domeParallax2);

	PLEX_addAnimationFrame(0, domeParallaxAnimation2);
	PLEX_addAnimationFrame(1, domeParallaxAnimation2);

	PLEX_startSprite(time, p_domeParallax2);
}

static void p_loadRoadSprites(const uint64_t time)
{
	PLEX_ANIMATION_PLATE road0Plate;
	PLEX_ANIMATION_PLATE road1Plate;
	PLEX_ANIMATION_PLATE road2Plate;
	PLEX_ANIMATION_PLATE road3Plate;
	PLEX_ANIMATION_PLATE road4Plate;

	PLEX_ANIMATION* road0Animation = NULL;
	PLEX_ANIMATION* road1Animation = NULL;
	PLEX_ANIMATION* road2Animation = NULL;
	PLEX_ANIMATION* road3Animation = NULL;
	PLEX_ANIMATION* road4Animation = NULL;

	if(!p_road0Tex) p_road0Tex = PLEX_loadTextureFromFileOrHeaderless(3840, 2466, 255, 255, 255, 255, 0, MMS1_FILEPATH_TEX_ROAD0, MMS1_FILEPATH_HEADERLESS_ROAD0);
	if(!p_road1Tex) p_road1Tex = PLEX_loadTextureFromFileOrHeaderless(3840, 2466, 255, 255, 255, 255, 0, MMS1_FILEPATH_TEX_ROAD1, MMS1_FILEPATH_HEADERLESS_ROAD1);
	if(!p_road2Tex) p_road2Tex = PLEX_loadTextureFromFileOrHeaderless(3840, 2466, 255, 255, 255, 255, 0, MMS1_FILEPATH_TEX_ROAD2, MMS1_FILEPATH_HEADERLESS_ROAD2);
	if(!p_road3Tex) p_road3Tex = PLEX_loadTextureFromFileOrHeaderless(3840, 2466, 255, 255, 255, 255, 0, MMS1_FILEPATH_TEX_ROAD3, MMS1_FILEPATH_HEADERLESS_ROAD3);
	if(!p_road4Tex) p_road4Tex = PLEX_loadTextureFromFileOrHeaderless(3840, 2466, 255, 255, 255, 255, 0, MMS1_FILEPATH_TEX_ROAD4, MMS1_FILEPATH_HEADERLESS_ROAD4);

	road0Plate = PLEX_createAnimationPlate(1, 0.5, p_road0Tex);
	road1Plate = PLEX_createAnimationPlate(1, 0.5, p_road1Tex);
	road2Plate = PLEX_createAnimationPlate(1, 0.5, p_road2Tex);
	road3Plate = PLEX_createAnimationPlate(1, 0.5, p_road3Tex);
	road4Plate = PLEX_createAnimationPlate(1, 0.5, p_road4Tex);

	p_road0 = PLEX_genSprite(&road0Plate);
	p_road1 = PLEX_genSprite(&road1Plate);
	p_road2 = PLEX_genSprite(&road2Plate);
	p_road3 = PLEX_genSprite(&road3Plate);
	p_road4 = PLEX_genSprite(&road4Plate);

	// Road 0 Animation

	PLEX_addAnimation(p_road0, 400, time);

	road0Animation = PLEX_getAnimation(0, p_road0);

	PLEX_addAnimationFrame(0, road0Animation);
	PLEX_addAnimationFrame(1, road0Animation);

	PLEX_startSprite(time, p_road0);

	// Road 1 Animation

	PLEX_addAnimation(p_road1, 400, time);

	road1Animation = PLEX_getAnimation(0, p_road1);

	PLEX_addAnimationFrame(0, road1Animation);
	PLEX_addAnimationFrame(1, road1Animation);

	PLEX_startSprite(time, p_road1);

	// Road 2 Animation

	PLEX_addAnimation(p_road2, 400, time);

	road2Animation = PLEX_getAnimation(0, p_road2);

	PLEX_addAnimationFrame(0, road2Animation);
	PLEX_addAnimationFrame(1, road2Animation);

	PLEX_startSprite(time, p_road2);

	// Road 3 Animation

	PLEX_addAnimation(p_road3, 400, time);

	road3Animation = PLEX_getAnimation(0, p_road3);

	PLEX_addAnimationFrame(0, road3Animation);
	PLEX_addAnimationFrame(1, road3Animation);

	PLEX_startSprite(time, p_road3);

	// Road 4 Animation

	PLEX_addAnimation(p_road4, 400, time);

	road4Animation = PLEX_getAnimation(0, p_road4);

	PLEX_addAnimationFrame(0, road4Animation);
	PLEX_addAnimationFrame(1, road4Animation);

	PLEX_startSprite(time, p_road4);
}

static void p_loadWallSprites(const uint64_t time)
{
	PLEX_ANIMATION_PLATE wall3Plate;
	PLEX_ANIMATION_PLATE wall4Plate;

	PLEX_ANIMATION* wall3Animation = NULL;
	PLEX_ANIMATION* wall4Animation = NULL;

	if(!p_wall3Tex) p_wall3Tex = PLEX_loadTextureFromFileOrHeaderless(3840, 2466, 255, 255, 255, 255, 0, MMS1_FILEPATH_TEX_WALL3, MMS1_FILEPATH_HEADERLESS_WALL3);
	if(!p_wall4Tex) p_wall4Tex = PLEX_loadTextureFromFileOrHeaderless(3840, 2466, 255, 255, 255, 255, 0, MMS1_FILEPATH_TEX_WALL4, MMS1_FILEPATH_HEADERLESS_WALL4);

	// Wall 3

	wall3Plate = PLEX_createAnimationPlate(1, 0.5, p_wall3Tex);

	p_wall3 = PLEX_genSprite(&wall3Plate);

	PLEX_addAnimation(p_wall3, 400, time);

	wall3Animation = PLEX_getAnimation(0, p_wall3);

	PLEX_addAnimationFrame(0, wall3Animation);
	PLEX_addAnimationFrame(1, wall3Animation);

	PLEX_startSprite(time, p_wall3);

	// Wall 4

	wall4Plate = PLEX_createAnimationPlate(1, 0.5, p_wall4Tex);

	p_wall4 = PLEX_genSprite(&wall4Plate);

	PLEX_addAnimation(p_wall4, 400, time);

	wall4Animation = PLEX_getAnimation(0, p_wall4);

	PLEX_addAnimationFrame(0, wall4Animation);
	PLEX_addAnimationFrame(1, wall4Animation);

	PLEX_startSprite(time, p_wall4);
}

static void p_loadEnvironmentGraphics(const uint64_t time)
{
	p_texLoadWindshieldEffect();

	p_loadSkybackdrops();

	p_createDomeSprite(time);
	p_loadRoadSprites(time);
	p_loadWallSprites(time);
}

static void p_destroyEnvironmentGraphics()
{
	if(p_road0 != NULL) PLEX_destroySprite(&p_road0);
	if(p_road1 != NULL) PLEX_destroySprite(&p_road1);
	if(p_road2 != NULL) PLEX_destroySprite(&p_road2);
	if(p_road3 != NULL) PLEX_destroySprite(&p_road3);
	if(p_road4 != NULL) PLEX_destroySprite(&p_road4);

	if(p_wall3 != NULL) PLEX_destroySprite(&p_wall3);
	if(p_wall4 != NULL) PLEX_destroySprite(&p_wall4);

	if(p_domeParallax != NULL) PLEX_destroySprite(&p_domeParallax);
	if(p_domeParallax2 != NULL) PLEX_destroySprite(&p_domeParallax2);

	if(p_road0Tex) PLEX_destroyTexture(p_road0Tex);
	if(p_road1Tex) PLEX_destroyTexture(p_road1Tex);
	if(p_road2Tex) PLEX_destroyTexture(p_road2Tex);
	if(p_road3Tex) PLEX_destroyTexture(p_road3Tex);
	if(p_road4Tex) PLEX_destroyTexture(p_road4Tex);

	if(p_wall3Tex) PLEX_destroyTexture(p_wall3Tex);
	if(p_wall4Tex) PLEX_destroyTexture(p_wall4Tex);

	if(p_domeParallaxTex) PLEX_destroyTexture(p_domeParallaxTex);
	if(p_domeParallaxTex2) PLEX_destroyTexture(p_domeParallaxTex2);

	if(p_skyline) PLEX_destroyTexture(p_skyline);

	if(p_windshieldBreak) PLEX_destroyTexture(p_windshieldBreak);

	if(p_backdrop0) PLEX_destroyTexture(p_backdrop0);
	if(p_backdrop1) PLEX_destroyTexture(p_backdrop1);
	if(p_backdrop2) PLEX_destroyTexture(p_backdrop2);
	if(p_backdrop3) PLEX_destroyTexture(p_backdrop3);
	if(p_backdrop4) PLEX_destroyTexture(p_backdrop4);

	p_road0Tex = 0;
	p_road1Tex = 0;
	p_road2Tex = 0;
	p_road3Tex = 0;
	p_road4Tex = 0;

	p_wall3Tex = 0;
	p_wall4Tex = 0;

	p_domeParallaxTex = 0;
	p_domeParallaxTex2 = 0;

	p_skyline = 0;

	p_windshieldBreak = 0;

	p_backdrop0 = 0;
	p_backdrop1 = 0;
	p_backdrop2 = 0;
	p_backdrop3 = 0;
	p_backdrop4 = 0;
}

static void p_updateWall(const size_t phase, const double phasePerc, PLEX_SPRITE* road, PLEX_SPRITE* nextRoad, const uint64_t time)
{
	const uint32_t roadCycleSpeed = MMS1_calcAnimationCycle(MMS1_FASTESTCYCLE_ROADANIMATION, MMS1_SLOWESTCYCLE_ROADANIMATION);
	const uint32_t road4CycleSpeed = MMS1_calcAnimationCycle(MMS1_FASTESTCYCLE_ROAD4ANIMATION, MMS1_SLOWESTCYCLE_ROAD4ANIMATION);

	if(phase != 4) PLEX_changeSpriteCycleSpeed(0, roadCycleSpeed, road, time);
	else PLEX_changeSpriteCycleSpeed(0, road4CycleSpeed, road, time);

	if(nextRoad != NULL)
	{
		if(phase != 3) PLEX_changeSpriteCycleSpeed(0, roadCycleSpeed, nextRoad, time);
		else PLEX_changeSpriteCycleSpeed(0, road4CycleSpeed, nextRoad, time);
	}

	PLEX_syncSprites(0, p_road3, p_wall3);
	PLEX_syncSprites(0, p_road4, p_wall4);
}

static void p_updateRoad(const size_t phase, PLEX_SPRITE** road, PLEX_SPRITE** nextRoad)
{
	switch(phase)
	{
		case 0: *road = p_road0; *nextRoad = p_road1; break;
		case 1: *road = p_road1; *nextRoad = p_road2; break;
		case 2: *road = p_road2; *nextRoad = p_road3; break;
		case 3: *road = p_road3; *nextRoad = p_road4; break;
		default: *road = p_road4; *nextRoad = NULL; break;
	};
}

static void p_updateDomeSprites(const uint64_t time)
{
	PLEX_changeSpriteCycleSpeed(0, MMS1_calcAnimationCycle(MMS1_FASTESTCYCLE_DOMEANIMATION, MMS1_SLOWESTCYCLE_DOMEANIMATION), p_domeParallax, time);
	PLEX_changeSpriteCycleSpeed(0, MMS1_calcAnimationCycle(MMS1_FASTESTCYCLE_DOMEANIMATION, MMS1_SLOWESTCYCLE_DOMEANIMATION), p_domeParallax2, time);

	PLEX_drawSprite(MMS1_ENDLAYER - 2, 0, 0, 0, PLEX_WW(true), PLEX_WH(true)/4.5, p_domeParallax, true, time);
	PLEX_drawSprite(MMS1_ENDLAYER - 2, 0, 0, PLEX_WH(true)/4.5, PLEX_WW(true), PLEX_WH(true) * 0.75 - PLEX_WH(true)/4.5, p_domeParallax2, true, time);
}

static void p_updateBackdrop(const size_t phase, size_t* phaseBack, size_t* nextPhaseBack)
{
	switch(phase)
	{
		case 0: *phaseBack = p_backdrop0; *nextPhaseBack = p_backdrop1; break;
		case 1: *phaseBack = p_backdrop1; *nextPhaseBack = p_backdrop2; break;
		case 2: *phaseBack = p_backdrop2; *nextPhaseBack = p_backdrop3; break;
		case 3: *phaseBack = p_backdrop3; *nextPhaseBack = p_backdrop4; break;
		case 4: *phaseBack = p_backdrop4; break;
	}
}

static void p_drawPhaseBack(const size_t phase, const double phasePerc, const size_t phaseBack, const size_t nextPhaseBack)
{
	PLEX_setTextureAlpha(phaseBack, 255);
	PLEX_printTexture(MMS1_ENDLAYER, phaseBack, 0, 0, 3840, 2466, 0, 0, PLEX_WW(true), PLEX_WH(true) * 0.75, true);

	if(phase != 4)
	{
		PLEX_setTextureAlpha(nextPhaseBack, 255 * phasePerc);
		PLEX_printTexture(MMS1_ENDLAYER, nextPhaseBack, 0, 0, 3840, 2466, 0, 0, PLEX_WW(true), PLEX_WH(true) * 0.75, true);
	}
}

static void p_drawRoad(const size_t phase, const double phasePerc, const PLEX_SPRITE* road, const PLEX_SPRITE* nextRoad, const uint64_t time)
{
	if(nextRoad != NULL && phasePerc > 0.8 && phase != 4)
	{
		const double overlapPerc = (phasePerc - 0.8)/0.2;

		PLEX_drawSprite(MMS1_ENDLAYER - 5, 0, 0, PLEX_WH(true) * 0.75, PLEX_WW(true), PLEX_WH(true)/4 * overlapPerc, nextRoad, true, time);
	}

	PLEX_drawSprite(MMS1_ENDLAYER - 4, 0, 0, PLEX_WH(true) * 0.75, PLEX_WW(true), PLEX_WH(true)/4, road, true, time);
}

static void p_drawWall(const size_t phase, const double phasePerc, const uint64_t time)
{
	if(phase == 3 || (phase == 2 && phasePerc > 0.8))
	{
		PLEX_drawSprite(MMS1_ENDLAYER - 5, 0, 0, PLEX_WH(true)/2, PLEX_WW(true), PLEX_WH(true)/4, p_wall3, true, time);
	}

	if(phase == 4 || (phase == 3 && phasePerc > 0.8))
	{
		const double hperc = phase == 3 ? (phasePerc - 0.8)/0.2 : 1;

		const uint32_t wallheight = hperc * PLEX_WH(true);

		PLEX_drawSprite(MMS1_ENDLAYER - 6, 0, 0, PLEX_WH(true) * 0.75 - wallheight, PLEX_WW(true), wallheight, p_wall4, true, time);
	}
}

static void p_drawSkyline(const double completePerc)
{
	const double skylineY = PLEX_WH(true) * 0.75 - PLEX_WH(true) * 0.75 * completePerc;
	const uint8_t skylineTint = 255 * completePerc;

	PLEX_printTextureTinted(MMS1_ENDLAYER - 3, p_skyline, 0, 0, 800, 500, 0, skylineY, PLEX_WW(true), PLEX_WH(true) * 0.75, skylineTint, skylineTint, skylineTint, true);
}

static void p_updateStopGraphics(const uint64_t time)
{
	if(MMS1_accel())
	{
		if(PLEX_isSpriteStopped(p_road0)) PLEX_startSprite(time, p_road0);
		if(PLEX_isSpriteStopped(p_road1)) PLEX_startSprite(time, p_road1);
		if(PLEX_isSpriteStopped(p_road2)) PLEX_startSprite(time, p_road2);
		if(PLEX_isSpriteStopped(p_road3)) PLEX_startSprite(time, p_road3);
		if(PLEX_isSpriteStopped(p_road4)) PLEX_startSprite(time, p_road4);
		if(PLEX_isSpriteStopped(p_domeParallax)) PLEX_startSprite(time, p_domeParallax);
		if(PLEX_isSpriteStopped(p_domeParallax2)) PLEX_startSprite(time, p_domeParallax2);
		if(PLEX_isSpriteStopped(p_wall3)) PLEX_startSprite(time, p_wall3);
		if(PLEX_isSpriteStopped(p_wall4)) PLEX_startSprite(time, p_wall4);
	}else{
		PLEX_stopSprite(p_road0);
		PLEX_stopSprite(p_road1);
		PLEX_stopSprite(p_road2);
		PLEX_stopSprite(p_road3);
		PLEX_stopSprite(p_road4);
		PLEX_stopSprite(p_domeParallax);
		PLEX_stopSprite(p_domeParallax2);
		PLEX_stopSprite(p_wall3);
		PLEX_stopSprite(p_wall4);
	}
}

static void p_windshieldEffect()
{
	size_t windshieldAniIndex = MMS1_windshieldAniIndex();

	if(windshieldAniIndex > 0)
	{
		const size_t index = windshieldAniIndex - 1;

		uint32_t w = 0;
		uint32_t h = 0;

		uint32_t ah  = 0;

		PLEX_textureWH(p_windshieldBreak, &w, &h);

		ah = h/3.0;

		PLEX_printTexture(MMS1_MENULAYER + 1, p_windshieldBreak, 0, ah * index, w, ah, 0, 0, PLEX_WW(true), PLEX_WH(true), true);

		if(windshieldAniIndex > p_glassShatterLevel)
		{
			MM_COMMON_playSoundEffect(MM_COMMON_SOUNDEFFECT_SURREALGLASSCRACK);
			p_glassShatterLevel = windshieldAniIndex;
		}
	}
}

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

bool MMS1_beginEnvironment(const uint64_t time)
{
	p_loadEnvironmentGraphics(time);

	p_glassShatterLevel = 0;

	return true;
}

bool MMS1_updateEnvironment(const size_t phase, const double phasePerc, const double completePerc, const uint64_t time)
{
	PLEX_SPRITE* road = NULL;
	PLEX_SPRITE* nextRoad = NULL;

	size_t phaseBack = 0;
	size_t nextPhaseBack = 0;

	p_updateStopGraphics(time);

	p_updateDomeSprites(time);

	p_updateRoad(phase, &road, &nextRoad);

	p_updateWall(phase, phasePerc, road, nextRoad, time); // < keep after updateRaod

	p_updateBackdrop(phase, &phaseBack, &nextPhaseBack);

	p_windshieldEffect();

	p_drawSkyline(completePerc);

	p_drawRoad(phase, phasePerc, road, nextRoad, time);

	p_drawWall(phase, phasePerc, time);

	p_drawPhaseBack(phase, phasePerc, phaseBack, nextPhaseBack);

	return true;
}

void MMS1_endEnvironment()
{
	p_destroyEnvironmentGraphics();
}
