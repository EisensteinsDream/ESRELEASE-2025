#include "chapters/mms3.h"

static size_t p_deeblockOutsideBack = 0;
static size_t p_deeblockOfficeBack = 0;
static size_t p_deeblockOfficeBackInvert = 0;

static size_t p_deeblockCafeteriaBack = 0;
static size_t p_deeblockArenaBack = 0;
static size_t p_deeblockQuartersBack = 0;
static size_t p_deeblockAngstBack = 0;

static size_t p_drDeeblock = 0;
static size_t p_deeblockChair1 = 0;
static size_t p_deeblockChair2 = 0;

static size_t p_cafeteriaDenizens[11];
static size_t p_cafeteriaGuards[8];

static size_t p_fightingKid1;
static size_t p_fightingKid2;

static size_t p_facelessCrowd[13];

static size_t p_tvShows[4];

static size_t p_lightCone = 0;

static size_t p_deeblockPamaleana = 0;

static size_t p_hellDemonBeatDown = 0;
static size_t p_hellDemon666 = 0;

PLEX_SPRITE* p_drDeeblockSprite = NULL;
PLEX_SPRITE* p_deeblockChairSprite = NULL;

PLEX_SPRITE* p_cafeteriaDenizenSprite = NULL;
PLEX_SPRITE* p_cafeteriaGuardSprite = NULL;

PLEX_SPRITE* p_fightingKidSprite = NULL;

PLEX_SPRITE* p_facelessCrowdSprite = NULL;

PLEX_SPRITE* p_tvShowSprite = NULL;

PLEX_SPRITE* p_lightConeSprite = NULL;

PLEX_SPRITE* p_deeblockPamSprite = NULL;

PLEX_SPRITE* p_hellDemonBeatDownSprite = NULL;
PLEX_SPRITE* p_hellDemon666Sprite = NULL;

static void p_tvShowTalk(const char* const message)
{
	PLEX_addSpriteTheaterSlide(191, 175, 15, message, p_tvShows[1], 0, true);
}

static void p_facelessPersonTalk(const char* const message)
{
	PLEX_addSpriteTheaterSlide(200, 200, 200, message, p_cafeteriaDenizens[3], 0, false);
}

static void p_workerATalk(const char* const message)
{
	PLEX_addSpriteTheaterSlide(50, 200, 200, message, p_cafeteriaGuards[0], 0, false);
}

static void p_workerBTalk(const char* const message)
{
	PLEX_addSpriteTheaterSlide(50, 200, 50, message, p_cafeteriaGuards[4], 0, false);
}

static void p_createDrDeeblock(const size_t chapter3SpriteTex)
{
	PLEX_ANIMATION* deeblockStanding = NULL;
	PLEX_ANIMATION* deeblockStorytelling = NULL;
	PLEX_ANIMATION* deeblockAirStabbing = NULL;
	PLEX_ANIMATION* deeblockContract = NULL;
	PLEX_ANIMATION* deeblockTurnRight = NULL;
	PLEX_ANIMATION* deeblockTurnLeft = NULL;

	PLEX_ANIMATION* deeblockGameshowHost = NULL;
	PLEX_ANIMATION* deeblockGameshowHostSnicker = NULL;
	PLEX_ANIMATION* deeblockGameshowHostLaugh = NULL;
	PLEX_ANIMATION* deeblockGameshowHostStorytelling = NULL;
	PLEX_ANIMATION* deeblockGameshowHostSmoking = NULL;
	PLEX_ANIMATION* deeblockGameshowHostSmokingSide = NULL;

	PLEX_ANIMATION_PLATE deeblockPlate = PLEX_createAnimationPlate(0.0625, 0.03125, chapter3SpriteTex);

	p_drDeeblockSprite = PLEX_genSprite(&deeblockPlate);

	PLEX_addAnimation(p_drDeeblockSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_drDeeblockSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_drDeeblockSprite, 100, PLEX_getGameTime());
	PLEX_addAnimation(p_drDeeblockSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_drDeeblockSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_drDeeblockSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_drDeeblockSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_drDeeblockSprite, 250, PLEX_getGameTime());
	PLEX_addAnimation(p_drDeeblockSprite, 500, PLEX_getGameTime());
	PLEX_addAnimation(p_drDeeblockSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_drDeeblockSprite, 1000, PLEX_getGameTime());
	PLEX_addAnimation(p_drDeeblockSprite, 500, PLEX_getGameTime());

	deeblockStanding = PLEX_getAnimation(0, p_drDeeblockSprite);

	PLEX_addAnimationFrame(178, deeblockStanding);

	deeblockStorytelling = PLEX_getAnimation(1, p_drDeeblockSprite);

	PLEX_addAnimationFrame(179, deeblockStorytelling);

	deeblockAirStabbing = PLEX_getAnimation(2, p_drDeeblockSprite);

	PLEX_addAnimationFrame(179, deeblockAirStabbing);
	PLEX_addAnimationFrame(180, deeblockAirStabbing);

	deeblockContract = PLEX_getAnimation(3, p_drDeeblockSprite);

	PLEX_addAnimationFrame(181, deeblockContract);

	deeblockTurnRight = PLEX_getAnimation(4, p_drDeeblockSprite);

	PLEX_addAnimationFrame(182, deeblockTurnRight);

	deeblockTurnLeft = PLEX_getAnimation(5, p_drDeeblockSprite);

	PLEX_addAnimationFrame(208, deeblockTurnLeft);

	deeblockGameshowHost = PLEX_getAnimation(6, p_drDeeblockSprite);

	PLEX_addAnimationFrame(222, deeblockGameshowHost);

	deeblockGameshowHostSnicker = PLEX_getAnimation(7, p_drDeeblockSprite);

	PLEX_addAnimationFrame(223, deeblockGameshowHostSnicker);
	PLEX_addAnimationFrame(224, deeblockGameshowHostSnicker);

	deeblockGameshowHostLaugh = PLEX_getAnimation(8, p_drDeeblockSprite);

	PLEX_addAnimationFrame(225, deeblockGameshowHostLaugh);
	PLEX_addAnimationFrame(226, deeblockGameshowHostLaugh);
	PLEX_addAnimationFrame(227, deeblockGameshowHostLaugh);
	PLEX_addAnimationFrame(226, deeblockGameshowHostLaugh);
	PLEX_addAnimationFrame(227, deeblockGameshowHostLaugh);
	PLEX_addAnimationFrame(226, deeblockGameshowHostLaugh);
	PLEX_addAnimationFrame(227, deeblockGameshowHostLaugh);

	deeblockGameshowHostStorytelling = PLEX_getAnimation(9, p_drDeeblockSprite);

	PLEX_addAnimationFrame(228, deeblockGameshowHostStorytelling);

	deeblockGameshowHostSmoking = PLEX_getAnimation(10, p_drDeeblockSprite);

	PLEX_addAnimationFrame(229, deeblockGameshowHostSmoking);
	PLEX_addAnimationFrame(230, deeblockGameshowHostSmoking);
	PLEX_addAnimationFrame(231, deeblockGameshowHostSmoking);
	PLEX_addAnimationFrame(232, deeblockGameshowHostSmoking);

	deeblockGameshowHostSmokingSide = PLEX_getAnimation(11, p_drDeeblockSprite);

	PLEX_addAnimationFrame(233, deeblockGameshowHostSmokingSide);
	PLEX_addAnimationFrame(234, deeblockGameshowHostSmokingSide);

	PLEX_startSprite(PLEX_getGameTime(), p_drDeeblockSprite);
}

static void p_createDeeblockChairs(const size_t chapter3SpriteTex)
{
	PLEX_ANIMATION* deeblockChair = NULL;

	PLEX_ANIMATION_PLATE chairPlate = PLEX_createAnimationPlate(0.0625, 0.03125, chapter3SpriteTex);

	p_deeblockChairSprite = PLEX_genSprite(&chairPlate);

	PLEX_addAnimation(p_deeblockChairSprite, 1, PLEX_getGameTime());

	deeblockChair = PLEX_getAnimation(0, p_deeblockChairSprite);

	PLEX_addAnimationFrame(27, deeblockChair);
}

static void p_createCafeteriaDenizens(const size_t chapter3SpriteTex)
{
	PLEX_ANIMATION* denizen00 = 0;
	PLEX_ANIMATION* denizen01 = 0;
	PLEX_ANIMATION* denizen02 = 0;
	PLEX_ANIMATION* denizen03 = 0;
	PLEX_ANIMATION* denizen04 = 0;
	PLEX_ANIMATION* denizen05 = 0;
	PLEX_ANIMATION* denizen06 = 0;
	PLEX_ANIMATION* denizen07 = 0;
	PLEX_ANIMATION* denizen08 = 0;
	PLEX_ANIMATION* denizen09 = 0;
	PLEX_ANIMATION* denizen10 = 0;

	PLEX_ANIMATION* denizenFaceless = 0;

	PLEX_ANIMATION_PLATE denizenPlate = PLEX_createAnimationPlate(0.0625, 0.03125, chapter3SpriteTex);

	p_cafeteriaDenizenSprite = PLEX_genSprite(&denizenPlate);

	PLEX_addAnimation(p_cafeteriaDenizenSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_cafeteriaDenizenSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_cafeteriaDenizenSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_cafeteriaDenizenSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_cafeteriaDenizenSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_cafeteriaDenizenSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_cafeteriaDenizenSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_cafeteriaDenizenSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_cafeteriaDenizenSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_cafeteriaDenizenSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_cafeteriaDenizenSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_cafeteriaDenizenSprite, 1, PLEX_getGameTime());

	denizen00 = PLEX_getAnimation(0, p_cafeteriaDenizenSprite);

	PLEX_addAnimationFrame(183, denizen00);

	denizen01 = PLEX_getAnimation(1, p_cafeteriaDenizenSprite);

	PLEX_addAnimationFrame(184, denizen01);

	denizen02 = PLEX_getAnimation(2, p_cafeteriaDenizenSprite);

	PLEX_addAnimationFrame(185, denizen02);

	denizen03 = PLEX_getAnimation(3, p_cafeteriaDenizenSprite);

	PLEX_addAnimationFrame(186, denizen03);

	denizen04 = PLEX_getAnimation(4, p_cafeteriaDenizenSprite);

	PLEX_addAnimationFrame(187, denizen04);

	denizen05 = PLEX_getAnimation(5, p_cafeteriaDenizenSprite);

	PLEX_addAnimationFrame(188, denizen05);

	denizen06 = PLEX_getAnimation(6, p_cafeteriaDenizenSprite);

	PLEX_addAnimationFrame(189, denizen06);

	denizen07 = PLEX_getAnimation(7, p_cafeteriaDenizenSprite);

	PLEX_addAnimationFrame(190, denizen07);

	denizen08 = PLEX_getAnimation(8, p_cafeteriaDenizenSprite);

	PLEX_addAnimationFrame(191, denizen08);

	denizen09 = PLEX_getAnimation(9, p_cafeteriaDenizenSprite);

	PLEX_addAnimationFrame(192, denizen09);

	denizen10 = PLEX_getAnimation(10, p_cafeteriaDenizenSprite);

	PLEX_addAnimationFrame(193, denizen10);

	denizenFaceless = PLEX_getAnimation(11, p_cafeteriaDenizenSprite);

	PLEX_addAnimationFrame(210, denizenFaceless);
}

static void p_createCafeteriaGuards(const size_t chapter3SpriteTex)
{
	PLEX_ANIMATION* guardLeft = 0;
	PLEX_ANIMATION* guardRight = 0;
	PLEX_ANIMATION* guardLeftUp = 0;
	PLEX_ANIMATION* guardRightUp = 0;

	PLEX_ANIMATION_PLATE guardPlate = PLEX_createAnimationPlate(0.0625, 0.03125, chapter3SpriteTex);

	p_cafeteriaGuardSprite = PLEX_genSprite(&guardPlate);

	PLEX_addAnimation(p_cafeteriaGuardSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_cafeteriaGuardSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_cafeteriaGuardSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_cafeteriaGuardSprite, 1, PLEX_getGameTime());

	guardLeft = PLEX_getAnimation(0, p_cafeteriaGuardSprite);

	PLEX_addAnimationFrame(194, guardLeft);

	guardRight = PLEX_getAnimation(1, p_cafeteriaGuardSprite);

	PLEX_addAnimationFrame(195, guardRight);

	guardLeftUp = PLEX_getAnimation(2, p_cafeteriaGuardSprite);

	PLEX_addAnimationFrame(205, guardLeftUp);

	guardRightUp = PLEX_getAnimation(3, p_cafeteriaGuardSprite);

	PLEX_addAnimationFrame(206, guardRightUp);
}

void p_createFightingKids(const size_t chapter3SpriteTex)
{
	PLEX_ANIMATION* fightingKidLeft = 0;
	PLEX_ANIMATION* fightingKidRight = 0;

	PLEX_ANIMATION_PLATE fightingKidPlate = PLEX_createAnimationPlate(0.0625, 0.03125, chapter3SpriteTex);

	p_fightingKidSprite = PLEX_genSprite(&fightingKidPlate);

	PLEX_addAnimation(p_fightingKidSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_fightingKidSprite, 1, PLEX_getGameTime());

	fightingKidLeft = PLEX_getAnimation(0, p_fightingKidSprite);

	PLEX_addAnimationFrame(196, fightingKidLeft);

	fightingKidRight = PLEX_getAnimation(1, p_fightingKidSprite);

	PLEX_addAnimationFrame(197, fightingKidRight);
}

static void p_createFacelessCrowd(const size_t chapter3SpriteTex)
{
	PLEX_ANIMATION* facelessCrowdLeft = 0;
	PLEX_ANIMATION* facelessCrowdRight = 0;

	PLEX_ANIMATION_PLATE facelessCrowdPlate = PLEX_createAnimationPlate(0.125, 0.03125, chapter3SpriteTex);

	p_facelessCrowdSprite = PLEX_genSprite(&facelessCrowdPlate);

	PLEX_addAnimation(p_facelessCrowdSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_facelessCrowdSprite, 1, PLEX_getGameTime());

	facelessCrowdLeft = PLEX_getAnimation(0, p_facelessCrowdSprite);

	PLEX_addAnimationFrame(99, facelessCrowdLeft);

	facelessCrowdRight = PLEX_getAnimation(1, p_facelessCrowdSprite);

	PLEX_addAnimationFrame(100, facelessCrowdRight);
}

static void p_createTVShow(const size_t tvShowTex)
{
	PLEX_ANIMATION* tvShowAnim = 0;

	PLEX_ANIMATION_PLATE tvShowPlate = PLEX_createAnimationPlate(0.05, 1, tvShowTex);

	p_tvShowSprite = PLEX_genSprite(&tvShowPlate);

	PLEX_addAnimation(p_tvShowSprite, 30000, PLEX_getGameTime());

	tvShowAnim = PLEX_getAnimation(0, p_tvShowSprite);

	PLEX_addAnimationFrame(0, tvShowAnim);
	PLEX_addAnimationFrame(1, tvShowAnim);
	PLEX_addAnimationFrame(2, tvShowAnim);
	PLEX_addAnimationFrame(3, tvShowAnim);
	PLEX_addAnimationFrame(4, tvShowAnim);
	PLEX_addAnimationFrame(5, tvShowAnim);
	PLEX_addAnimationFrame(6, tvShowAnim);
	PLEX_addAnimationFrame(7, tvShowAnim);
	PLEX_addAnimationFrame(8, tvShowAnim);
	PLEX_addAnimationFrame(4, tvShowAnim);
	PLEX_addAnimationFrame(7, tvShowAnim);
	PLEX_addAnimationFrame(9, tvShowAnim);
	PLEX_addAnimationFrame(10, tvShowAnim);
	PLEX_addAnimationFrame(11, tvShowAnim);
	PLEX_addAnimationFrame(7, tvShowAnim);
	PLEX_addAnimationFrame(12, tvShowAnim);
	PLEX_addAnimationFrame(3, tvShowAnim);
	PLEX_addAnimationFrame(4, tvShowAnim);
	PLEX_addAnimationFrame(6, tvShowAnim);
	PLEX_addAnimationFrame(7, tvShowAnim);
	PLEX_addAnimationFrame(13, tvShowAnim);
	PLEX_addAnimationFrame(7, tvShowAnim);
	PLEX_addAnimationFrame(13, tvShowAnim);
	PLEX_addAnimationFrame(7, tvShowAnim);
	PLEX_addAnimationFrame(14, tvShowAnim);
	PLEX_addAnimationFrame(6, tvShowAnim);
	PLEX_addAnimationFrame(4, tvShowAnim);
	PLEX_addAnimationFrame(13, tvShowAnim);
	PLEX_addAnimationFrame(7, tvShowAnim);
	PLEX_addAnimationFrame(13, tvShowAnim);
	PLEX_addAnimationFrame(7, tvShowAnim);
	PLEX_addAnimationFrame(13, tvShowAnim);
	PLEX_addAnimationFrame(7, tvShowAnim);

	PLEX_startSprite(PLEX_getGameTime(), p_tvShowSprite);
}

static void p_createLightCone(const size_t chapter3SpriteTex)
{
	PLEX_ANIMATION* lightCone = 0;

	PLEX_ANIMATION_PLATE lightConePlate = PLEX_createAnimationPlate(0.125, 0.03125, chapter3SpriteTex);

	p_lightConeSprite = PLEX_genSprite(&lightConePlate);

	PLEX_addAnimation(p_lightConeSprite, 1, PLEX_getGameTime());

	lightCone = PLEX_getAnimation(0, p_lightConeSprite);

	PLEX_addAnimationFrame(101, lightCone);
}

static void p_createDeeblockPamaleana(const size_t chapter3SpriteTex)
{
	PLEX_ANIMATION* pamStandAnim = 0;
	PLEX_ANIMATION* pamStandDownAnim = 0;
	PLEX_ANIMATION* pamEating = 0;
	PLEX_ANIMATION* pamShockChair = 0;
	PLEX_ANIMATION* pamShockChairStill = 0;
	PLEX_ANIMATION* pamShockChairShocked = 0;
	PLEX_ANIMATION* pamContract = 0;

	PLEX_ANIMATION_PLATE pamPlate = PLEX_createAnimationPlate(0.0625, 0.03125, chapter3SpriteTex);

	p_deeblockPamSprite = PLEX_genSprite(&pamPlate);

	PLEX_addAnimation(p_deeblockPamSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_deeblockPamSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_deeblockPamSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_deeblockPamSprite, 1000, PLEX_getGameTime());
	PLEX_addAnimation(p_deeblockPamSprite, 1000, PLEX_getGameTime());
	PLEX_addAnimation(p_deeblockPamSprite, 50, PLEX_getGameTime());
	PLEX_addAnimation(p_deeblockPamSprite, 1, PLEX_getGameTime());

	pamStandAnim = PLEX_getAnimation(0, p_deeblockPamSprite);

	PLEX_addAnimationFrame(204, pamStandAnim);

	pamStandDownAnim = PLEX_getAnimation(1, p_deeblockPamSprite);

	PLEX_addAnimationFrame(207, pamStandDownAnim);

	pamEating = PLEX_getAnimation(2, p_deeblockPamSprite);

	PLEX_addAnimationFrame(209, pamEating);

	pamShockChair = PLEX_getAnimation(3, p_deeblockPamSprite);

	PLEX_addAnimationFrame(245, pamShockChair);
	PLEX_addAnimationFrame(246, pamShockChair);
	PLEX_addAnimationFrame(247, pamShockChair);
	PLEX_addAnimationFrame(248, pamShockChair);
	PLEX_addAnimationFrame(249, pamShockChair);
	PLEX_addAnimationFrame(248, pamShockChair);

	pamShockChairStill = PLEX_getAnimation(4, p_deeblockPamSprite);

	PLEX_addAnimationFrame(245, pamShockChairStill);
	PLEX_addAnimationFrame(252, pamShockChairStill);
	PLEX_addAnimationFrame(247, pamShockChairStill);
	PLEX_addAnimationFrame(253, pamShockChairStill);
	PLEX_addAnimationFrame(249, pamShockChairStill);
	PLEX_addAnimationFrame(253, pamShockChairStill);

	pamShockChairShocked = PLEX_getAnimation(5, p_deeblockPamSprite);

	PLEX_addAnimationFrame(256, pamShockChairShocked);
	PLEX_addAnimationFrame(257, pamShockChairShocked);

	pamContract = PLEX_getAnimation(6, p_deeblockPamSprite);

	PLEX_addAnimationFrame(30, pamContract);

	PLEX_startSprite(PLEX_getGameTime(), p_deeblockPamSprite);
}

static void p_createHellDemonBeatdown(const size_t chapter3SpriteTex)
{
	PLEX_ANIMATION* anim = 0;

	PLEX_ANIMATION_PLATE hellPlate = PLEX_createAnimationPlate(0.125, 0.03125, chapter3SpriteTex);

	p_hellDemonBeatDownSprite = PLEX_genSprite(&hellPlate);

	PLEX_addAnimation(p_hellDemonBeatDownSprite, 1000, PLEX_getGameTime());

	anim = PLEX_getAnimation(0, p_hellDemonBeatDownSprite);

	PLEX_addAnimationFrame(107, anim);
	PLEX_addAnimationFrame(107, anim);
	PLEX_addAnimationFrame(108, anim);
	PLEX_addAnimationFrame(109, anim);
	PLEX_addAnimationFrame(109, anim);
	PLEX_addAnimationFrame(109, anim);
	PLEX_addAnimationFrame(109, anim);
	PLEX_addAnimationFrame(109, anim);

	PLEX_addAnimationFrame(110, anim);
	PLEX_addAnimationFrame(110, anim);
	PLEX_addAnimationFrame(110, anim);
	PLEX_addAnimationFrame(110, anim);
	PLEX_addAnimationFrame(110, anim);
	PLEX_addAnimationFrame(110, anim);
	PLEX_addAnimationFrame(110, anim);

	PLEX_startSprite(PLEX_getGameTime(), p_hellDemonBeatDownSprite);
}

static void p_createHellDemon666(const size_t chapter3SpriteTex)
{
	PLEX_ANIMATION* hellDemonStandAnim = 0;
	PLEX_ANIMATION* hellDemonEating = 0;
	PLEX_ANIMATION* hellDemonShockChair = 0;
	PLEX_ANIMATION* hellDemonShockChairStill = 0;
	PLEX_ANIMATION* hellDemonShockChairShocked = 0;
	PLEX_ANIMATION* hellDemonShockChairButton = 0;

	PLEX_ANIMATION_PLATE hellDemonPlate = PLEX_createAnimationPlate(0.0625, 0.03125, chapter3SpriteTex);

	p_hellDemon666Sprite = PLEX_genSprite(&hellDemonPlate);

	PLEX_addAnimation(p_hellDemon666Sprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_hellDemon666Sprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_hellDemon666Sprite, 1000, PLEX_getGameTime());
	PLEX_addAnimation(p_hellDemon666Sprite, 1000, PLEX_getGameTime());
	PLEX_addAnimation(p_hellDemon666Sprite, 50, PLEX_getGameTime());
	PLEX_addAnimation(p_hellDemon666Sprite, 1, PLEX_getGameTime());

	hellDemonStandAnim = PLEX_getAnimation(0, p_hellDemon666Sprite);

	PLEX_addAnimationFrame(211, hellDemonStandAnim);

	hellDemonEating = PLEX_getAnimation(1, p_hellDemon666Sprite);

	PLEX_addAnimationFrame(212, hellDemonEating);

	hellDemonShockChair = PLEX_getAnimation(2, p_hellDemon666Sprite);

	PLEX_addAnimationFrame(240, hellDemonShockChair);
	PLEX_addAnimationFrame(241, hellDemonShockChair);
	PLEX_addAnimationFrame(242, hellDemonShockChair);
	PLEX_addAnimationFrame(243, hellDemonShockChair);
	PLEX_addAnimationFrame(244, hellDemonShockChair);
	PLEX_addAnimationFrame(243, hellDemonShockChair);

	hellDemonShockChairStill = PLEX_getAnimation(3, p_hellDemon666Sprite);

	PLEX_addAnimationFrame(240, hellDemonShockChairStill);
	PLEX_addAnimationFrame(250, hellDemonShockChairStill);
	PLEX_addAnimationFrame(242, hellDemonShockChairStill);
	PLEX_addAnimationFrame(251, hellDemonShockChairStill);
	PLEX_addAnimationFrame(244, hellDemonShockChairStill);
	PLEX_addAnimationFrame(251, hellDemonShockChairStill);

	hellDemonShockChairShocked = PLEX_getAnimation(4, p_hellDemon666Sprite);

	PLEX_addAnimationFrame(254, hellDemonShockChairShocked);
	PLEX_addAnimationFrame(255, hellDemonShockChairShocked);

	hellDemonShockChairButton = PLEX_getAnimation(5, p_hellDemon666Sprite);

	PLEX_addAnimationFrame(258, hellDemonShockChairButton);

	PLEX_startSprite(PLEX_getGameTime(), p_hellDemon666Sprite);
}

static void p_addCafeteriaDenizen(const size_t index)
{
	const double x = PLEX_WIDTHUNITMAX()/2 - 11.5 + (index * 2) + (index/3 * 0.75) + ((index >= 5) * 2.5) - ((index > 5) * 0.75) + ((index >= 8) * 1.5) - ((index > 8) * 1);
	const double y = PLEX_HEIGHTUNITMAX()/2 + 1.45;

	p_cafeteriaDenizens[index] = PLEX_createActor(p_cafeteriaDenizenSprite, 0, PLEX_convRect(PLEX_convPoint(x, y), PLEX_convDimens(2, 4)), true);

	PLEX_changeActor(p_cafeteriaDenizens[index], index);
}

static void p_addCafeteriaGaurd(const size_t index)
{
	const double x = PLEX_WIDTHUNITMAX()/2 - 11.5 + (3.4 * index);
	const double y = PLEX_HEIGHTUNITMAX()/2 - 2;

	p_cafeteriaGuards[index] = PLEX_createActor(p_cafeteriaGuardSprite, 0, PLEX_convRect(PLEX_convPoint(x, y), PLEX_convDimens(2, 4)), true);

	if(index >= 4) PLEX_changeActor(p_cafeteriaGuards[index], 1);
}

static void p_addFightingKids()
{
	p_fightingKid1 = PLEX_createActor(p_fightingKidSprite, 0, PLEX_convRect(PLEX_convPoint(PLEX_WIDTHUNITMAX()/2 - 3, PLEX_HEIGHTUNITMAX() * 0.75 - 2), PLEX_convDimens(2, 4)), true);
	p_fightingKid2 = PLEX_createActor(p_fightingKidSprite, 0, PLEX_convRect(PLEX_convPoint(PLEX_WIDTHUNITMAX()/2 + 3, PLEX_HEIGHTUNITMAX() * 0.75 - 2), PLEX_convDimens(2, 4)), true);

	PLEX_changeActor(p_fightingKid2, 1);
}

static void p_addFacelessCrowd()
{
	// row 1

	p_facelessCrowd[0] = PLEX_createActor(p_facelessCrowdSprite, 0, PLEX_convRect(PLEX_convPoint(PLEX_WIDTHUNITMAX()/2 - 13, PLEX_HEIGHTUNITMAX() * 0.75 - 4), PLEX_convDimens(2, 2)), true);

	p_facelessCrowd[1] = PLEX_createActor(p_facelessCrowdSprite, 0, PLEX_convRect(PLEX_convPoint(PLEX_WIDTHUNITMAX()/2 - 13, PLEX_HEIGHTUNITMAX() * 0.75 + 1), PLEX_convDimens(2, 2)), true);

	// row 2

	p_facelessCrowd[2] = PLEX_createActor(p_facelessCrowdSprite, 0, PLEX_convRect(PLEX_convPoint(PLEX_WIDTHUNITMAX()/2 - 8, PLEX_HEIGHTUNITMAX() * 0.75 - 4), PLEX_convDimens(2, 2)), true);

	p_facelessCrowd[3] = PLEX_createActor(p_facelessCrowdSprite, 0, PLEX_convRect(PLEX_convPoint(PLEX_WIDTHUNITMAX()/2 - 8, PLEX_HEIGHTUNITMAX() * 0.75 + 1), PLEX_convDimens(2, 2)), true);

	// row 3

	p_facelessCrowd[4] = PLEX_createActor(p_facelessCrowdSprite, 0, PLEX_convRect(PLEX_convPoint(PLEX_WIDTHUNITMAX()/2 - 4, PLEX_HEIGHTUNITMAX() * 0.75 - 4), PLEX_convDimens(2, 2)), true);

	p_facelessCrowd[5] = PLEX_createActor(p_facelessCrowdSprite, 0, PLEX_convRect(PLEX_convPoint(PLEX_WIDTHUNITMAX()/2 - 4, PLEX_HEIGHTUNITMAX() * 0.75 + 1), PLEX_convDimens(2, 2)), true);

	// row 4

	p_facelessCrowd[6] = PLEX_createActor(p_facelessCrowdSprite, 0, PLEX_convRect(PLEX_convPoint(PLEX_WIDTHUNITMAX()/2 - 0.8, PLEX_HEIGHTUNITMAX() * 0.75 + 1), PLEX_convDimens(2, 2)), true);

	// row 5

	p_facelessCrowd[7] = PLEX_createActor(p_facelessCrowdSprite, 0, PLEX_convRect(PLEX_convPoint(PLEX_WIDTHUNITMAX()/2 + 2, PLEX_HEIGHTUNITMAX() * 0.75), PLEX_convDimens(2, 2)), true);

	// row 6

	p_facelessCrowd[8] = PLEX_createActor(p_facelessCrowdSprite, 0, PLEX_convRect(PLEX_convPoint(PLEX_WIDTHUNITMAX()/2 + 5, PLEX_HEIGHTUNITMAX() * 0.75 + 1), PLEX_convDimens(2, 2)), true);

	// row 7

	p_facelessCrowd[9] = PLEX_createActor(p_facelessCrowdSprite, 0, PLEX_convRect(PLEX_convPoint(PLEX_WIDTHUNITMAX()/2 + 8.5, PLEX_HEIGHTUNITMAX() * 0.75 - 4), PLEX_convDimens(2, 2)), true);

	p_facelessCrowd[10] = PLEX_createActor(p_facelessCrowdSprite, 0, PLEX_convRect(PLEX_convPoint(PLEX_WIDTHUNITMAX()/2 + 8.5, PLEX_HEIGHTUNITMAX() * 0.75 + 1), PLEX_convDimens(2, 2)), true);

	// row 8

	p_facelessCrowd[11] = PLEX_createActor(p_facelessCrowdSprite, 0, PLEX_convRect(PLEX_convPoint(PLEX_WIDTHUNITMAX()/2 + 12, PLEX_HEIGHTUNITMAX() * 0.75 - 4), PLEX_convDimens(2, 2)), true);

	p_facelessCrowd[12] = PLEX_createActor(p_facelessCrowdSprite, 0, PLEX_convRect(PLEX_convPoint(PLEX_WIDTHUNITMAX()/2 + 12, PLEX_HEIGHTUNITMAX() * 0.75 + 1), PLEX_convDimens(2, 2)), true);

	for(size_t ze = 7; ze < 13; ++ze) PLEX_changeActor(p_facelessCrowd[ze], 1);
}

static void p_addTVShows()
{
	for(size_t ze = 0; ze < 4; ++ze) p_tvShows[ze] = PLEX_createActor(p_tvShowSprite, 0, PLEX_convRect(PLEX_convPoint(2 + (ze * 7.25), PLEX_HEIGHTUNITMAX()/2 - 5), PLEX_convDimens(6, 4)), true);
}

static void p_addHelldemonBeatdown()
{
	p_hellDemonBeatDown = PLEX_createActor(p_hellDemonBeatDownSprite, 0, PLEX_convRect(PLEX_convPoint(PLEX_WIDTHUNITMAX()/2 - 1, PLEX_HEIGHTUNITMAX() - 4.5), PLEX_convDimens(4, 4)), true);
}

static void p_loadDeeblockOfficeOutsideBack()
{
	if(!p_deeblockOutsideBack) p_deeblockOutsideBack = PLEX_loadTextureFromFileOrHeaderless(3840, 1640, 255, 255, 255, 255, 0, MMS3_FILEPATH_TEX_DEEBLOCKOUTSIDE, MMS3_FILEPATH_HEADERLESS_DEEBLOCKOUTSIDE);
}

static void p_loadDeeblockOfficeInvertBack()
{
	if(!p_deeblockOfficeBackInvert) p_deeblockOfficeBackInvert = PLEX_loadTextureFromFileOrHeaderless(3840, 1640, 255, 255, 255, 255, 0, MMS3_FILEPATH_TEX_DEEBLOCKOFFICEINVERT, MMS3_FILEPATH_HEADERLESS_DEEBLOCKOFFICEINVERT);
}

static void p_loadDeeblockCafeteriaBack()
{
	if(!p_deeblockCafeteriaBack) p_deeblockCafeteriaBack = PLEX_loadTextureFromFileOrHeaderless(3840, 1640, 255, 255, 255, 255, 0, MMS3_FILEPATH_TEX_DEEBLOCKCAFETERIA, MMS3_FILEPATH_HEADERLESS_DEEBLOCKCAFETERIA);
}


static void p_loadDeeblockArenaBack()
{
	if(!p_deeblockArenaBack) p_deeblockArenaBack = PLEX_loadTextureFromFileOrHeaderless(3840, 1640, 255, 255, 255, 255, 0, MMS3_FILEPATH_TEX_DEEBLOCKARENA, MMS3_FILEPATH_HEADERLESS_DEEBLOCKARENA);
}


static void p_loadDeeblockQuartersBack()
{
	if(!p_deeblockQuartersBack) p_deeblockQuartersBack = PLEX_loadTextureFromFileOrHeaderless(3840, 1640, 255, 255, 255, 255, 0, MMS3_FILEPATH_TEX_DEEBLOCKQUARTERS, MMS3_FILEPATH_HEADERLESS_DEEBLOCKQUARTERS);
}


static void p_loadDeeblockAngstBack(){ if(!p_deeblockAngstBack) p_deeblockAngstBack = PLEX_loadTextureFromFileOrHeaderless(3840, 1640, 255, 255, 255, 255, 0, MMS3_FILEPATH_TEX_DEEBLOCKANGST, MMS3_FILEPATH_HEADERLESS_DEEBLOCKANGST); }

static void p_clearDeeblockScene()
{
	for(size_t ze = 0; ze < 8; ++ze) PLEX_hideActor(p_cafeteriaGuards[ze]);
	for(size_t ze = 0; ze < 11; ++ze) PLEX_hideActor(p_cafeteriaDenizens[ze]);

	for(size_t ze = 0; ze < 13; ++ze) PLEX_hideActor(p_facelessCrowd[ze]);

	for(size_t ze = 0; ze < 4; ++ze) PLEX_hideActor(p_tvShows[ze]);

	PLEX_hideActor(p_fightingKid1);
	PLEX_hideActor(p_fightingKid2);

	MMS3_hideTeenPamPam();

	PLEX_hideActor(p_lightCone);

	MMS3_hideDeeblockPamaleana();
	PLEX_hideActor(p_drDeeblock);

	MMS3_resizeTeenPamPam(2, 4);

	PLEX_actorResizeActionChange(p_deeblockPamaleana, 2, 4);
	PLEX_actorResizeActionChange(p_cafeteriaGuards[0], 2, 4);
	PLEX_actorResizeActionChange(p_cafeteriaGuards[1], 2, 4);

	PLEX_hideActor(p_hellDemonBeatDown);
}

static void p_setDeeblockArea(const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow)
{
	PLEX_startSpriteTheater(MMS_LANGUAGE_SETTING_DRDEEBLOCKSOUTSIDE, 0, 0, 0, 400, 100, 255, 255, 255, fontPlate, label, bubble, arrow, PLEX_getGameTime());

	MMS3_addTeenPamaleana(0, 0, true);

	for(size_t ze = 0; ze < 8; ++ze) p_addCafeteriaGaurd(ze);
	for(size_t ze = 0; ze < 11; ++ze) p_addCafeteriaDenizen(ze);

	p_addFightingKids();
	p_addFacelessCrowd();
	MMS3_addDeeblockPamaleana();

	MMS3_addDrDeeblock(PLEX_WIDTHUNITMAX()/2 - 1, PLEX_HEIGHTUNITMAX() * 0.75 - 6);

	p_addTVShows();

	MMS3_addLightCone(PLEX_WIDTHUNITMAX()/2 - 2.5, PLEX_HEIGHTUNITMAX()/2);

	p_addHelldemonBeatdown();
	MMS3_addHelldemon666();

	MMS3_clearBackTextures();
	MMS3_loadDeeblockOfficeBack();
	p_loadDeeblockCafeteriaBack();
	p_loadDeeblockArenaBack();
	p_loadDeeblockQuartersBack();
	p_loadDeeblockAngstBack();

	p_clearDeeblockScene();
}

static void p_setAsDeeblockKitchen(const bool pamaleanaIsAdult, const bool sitWithHellDemon)
{
	p_clearDeeblockScene();

	PLEX_changeSpriteTheaterBackground(p_deeblockCafeteriaBack, MMS_LANGUAGE_SETTING_DEEBLOCKCAFETERIA);

	for(size_t ze = 0; ze < 11; ++ze) PLEX_unhideActor(p_cafeteriaDenizens[ze]);
	for(size_t ze = 0; ze < 8; ++ze) PLEX_unhideActor(p_cafeteriaGuards[ze]);

	if(pamaleanaIsAdult)
	{
		if(!sitWithHellDemon)
		{
			PLEX_hideActor(p_cafeteriaDenizens[2]);
		}else{
			PLEX_unhideActor(p_hellDemon666);
			PLEX_changeActor(p_hellDemon666, 1);

			PLEX_moveActor(p_hellDemon666, PLEX_WIDTHUNITMAX()/2 - 2.5, PLEX_HEIGHTUNITMAX()/2  + 1.45);
		}

		PLEX_hideActor(p_cafeteriaDenizens[4]);

		PLEX_unhideActor(p_deeblockPamaleana);
		PLEX_changeActor(p_deeblockPamaleana, 2);
		PLEX_moveActor(p_deeblockPamaleana, PLEX_WIDTHUNITMAX()/2 - 1, PLEX_HEIGHTUNITMAX()/2 + 1.45);

		for(size_t ze = 0; ze < 11; ++ze) PLEX_changeActor(p_cafeteriaDenizens[ze], 11);
	}else{
		MMS3_unhideTeenPamPam();
		MMS3_teenPamPamActorAnimationActionChange(12);
		MMS3_moveTeenPamPam(PLEX_WIDTHUNITMAX()/2 - 1, PLEX_HEIGHTUNITMAX()/2 + 1.45);
	}
}

static void p_setAsDeeblockArena()
{
	p_clearDeeblockScene();

	PLEX_changeSpriteTheaterBackground(p_deeblockArenaBack, MMS_LANGUAGE_SETTING_DEEBLOCKARENA);

	for(size_t ze = 0; ze < 8; ++ze) PLEX_unhideActor(p_cafeteriaGuards[ze]);

	PLEX_unhideActor(p_fightingKid1);
	PLEX_unhideActor(p_fightingKid2);

	PLEX_moveActor(p_cafeteriaGuards[0], PLEX_WIDTHUNITMAX()/2 - 11.5, PLEX_HEIGHTUNITMAX() * 0.75);
	PLEX_moveActor(p_cafeteriaGuards[1], PLEX_WIDTHUNITMAX()/2 - 11.5, PLEX_HEIGHTUNITMAX() * 0.75 - 6);
	PLEX_moveActor(p_cafeteriaGuards[2], PLEX_WIDTHUNITMAX()/2 - 10.5, PLEX_HEIGHTUNITMAX() * 0.75 - 9);
	PLEX_moveActor(p_cafeteriaGuards[3], PLEX_WIDTHUNITMAX()/2 - 6.5, PLEX_HEIGHTUNITMAX() * 0.75 - 10);

	PLEX_moveActor(p_cafeteriaGuards[4], PLEX_WIDTHUNITMAX()/2 + 4.5, PLEX_HEIGHTUNITMAX() * 0.75 - 10);
	PLEX_moveActor(p_cafeteriaGuards[5], PLEX_WIDTHUNITMAX()/2 + 8.5, PLEX_HEIGHTUNITMAX() * 0.75 - 9);
	PLEX_moveActor(p_cafeteriaGuards[6], PLEX_WIDTHUNITMAX()/2 + 9.5, PLEX_HEIGHTUNITMAX() * 0.75 - 6);
	PLEX_moveActor(p_cafeteriaGuards[7], PLEX_WIDTHUNITMAX()/2 + 9.5, PLEX_HEIGHTUNITMAX() * 0.75);
}

static void p_setAsDeeblockQuarters(const bool emptyCell)
{
	p_clearDeeblockScene();

	PLEX_changeSpriteTheaterBackground(p_deeblockQuartersBack, MMS_LANGUAGE_SETTING_DEEBLOCKQUARTERS);

	for(size_t ze = 0; ze < 13; ++ze)
	{
		if(ze == 7 && emptyCell) continue;

		PLEX_unhideActor(p_facelessCrowd[ze]);
	}

	for(size_t ze = 0; ze < 4; ++ze) PLEX_unhideActor(p_tvShows[ze]);

	if(emptyCell)
	{
		PLEX_unhideActor(p_deeblockPamaleana);
		PLEX_changeActor(p_deeblockPamaleana, 0);
		PLEX_moveActor(p_deeblockPamaleana, PLEX_WIDTHUNITMAX()/2 + 2, PLEX_HEIGHTUNITMAX() * 0.75);

		PLEX_unhideActor(p_cafeteriaGuards[0]);
		PLEX_unhideActor(p_cafeteriaGuards[4]);

		PLEX_moveActor(p_cafeteriaGuards[0], PLEX_WIDTHUNITMAX()/2 + 2, 13);
		PLEX_moveActor(p_cafeteriaGuards[4], PLEX_WIDTHUNITMAX()/2 + 4, 13);

		PLEX_actorResizeActionChange(p_deeblockPamaleana, 1, 2);
		PLEX_actorResizeActionChange(p_cafeteriaGuards[0], 1, 2);
		PLEX_actorResizeActionChange(p_cafeteriaGuards[4], 1, 2);
	}else{
		MMS3_unhideTeenPamPam();
		MMS3_teenPamPamActorAnimationActionChange(13);
		MMS3_moveTeenPamPam(PLEX_WIDTHUNITMAX()/2 + 2, PLEX_HEIGHTUNITMAX() * 0.75 + 1);
	}

	MMS3_resizeTeenPamPam(1, 2);
}

static void p_setAsDeeblockAngst()
{
	p_clearDeeblockScene();

	PLEX_changeSpriteTheaterBackground(p_deeblockAngstBack, MMS_LANGUAGE_SETTING_DEEBLOCKQUARTERS);

	PLEX_unhideActor(p_lightCone);
	MMS3_unhideTeenPamPam();

	MMS3_moveTeenPamPam(PLEX_WIDTHUNITMAX()/2 - 1, PLEX_HEIGHTUNITMAX() * 0.75 - 2);
}

void p_setAsDeeblockDrOffice(const bool finalMeeting)
{
	p_clearDeeblockScene();

	PLEX_changeSpriteTheaterBackground(p_deeblockOfficeBack, MMS_LANGUAGE_SETTING_DRDEEBLOCKSOFFICE);

	PLEX_unhideActor(p_deeblockPamaleana);
	PLEX_unhideActor(p_drDeeblock);

	PLEX_moveActor(p_drDeeblock, PLEX_WIDTHUNITMAX()/2 - 1, PLEX_HEIGHTUNITMAX() * 0.75 - 6);

	if(!finalMeeting)
	{
		PLEX_moveActor(p_deeblockPamaleana, PLEX_WIDTHUNITMAX()/2 - 1, PLEX_HEIGHTUNITMAX() * 0.75 + 1);

		PLEX_unhideActor(p_cafeteriaGuards[0]);
		PLEX_unhideActor(p_cafeteriaGuards[4]);

		PLEX_changeActor(p_cafeteriaGuards[0], 2);
		PLEX_changeActor(p_cafeteriaGuards[4], 3);

		PLEX_moveActor(p_cafeteriaGuards[0], PLEX_WIDTHUNITMAX()/2 - 3, PLEX_HEIGHTUNITMAX() * 0.75 + 1);
		PLEX_moveActor(p_cafeteriaGuards[4], PLEX_WIDTHUNITMAX()/2 + 2, PLEX_HEIGHTUNITMAX() * 0.75 + 1);
	}
}

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

void MMS3_startSceneL(const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow)
{
	MMS3_clearBackTextures();
	p_loadDeeblockOfficeOutsideBack();

	PLEX_startSpriteTheater(MMS_LANGUAGE_SETTING_DRDEEBLOCKSOUTSIDE, p_deeblockOutsideBack, 0, 0, 400, 100, 255, 255, 255, fontPlate, label, bubble, arrow, PLEX_getGameTime());

	MMS_pamNarration(MMS3_LANGUAGE_SCENEL00);
}

void MMS3_startSceneM(const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow)
{
	MMS3_clearBackTextures();
	MMS3_loadDeeblockOfficeBack();
	p_loadDeeblockOfficeInvertBack();

	PLEX_startSpriteTheater(MMS_LANGUAGE_SETTING_DRDEEBLOCKSOFFICE, p_deeblockOfficeBack, 0, 0, 400, 100, 255, 255, 255, fontPlate, label, bubble, arrow, PLEX_getGameTime());

	PLEX_changeSpriteTheaterMusic(MM_COMMON_THEMEID_DAYTODAY);

	MMS3_addDrDeeblock(PLEX_WIDTHUNITMAX()/2 - 1, PLEX_HEIGHTUNITMAX() * 0.75 - 6);

	MMS3_addTeenPamaleana(PLEX_WIDTHUNITMAX()/2 + 5, PLEX_HEIGHTUNITMAX() * 0.75 - 6, false);

	MMS3_addPollockCodelli(PLEX_WIDTHUNITMAX()/2 - 3, PLEX_HEIGHTUNITMAX() * 0.75 + 1, false, false);
	MMS3_addStephinaCodelli(PLEX_WIDTHUNITMAX()/2 + 2, PLEX_HEIGHTUNITMAX() * 0.75 + 1, false);

	MMS3_addDeeblockChairs();

	MMS3_pollockCodelliActorAnimationActionChange(5);
	MMS3_stephinaCodelliActorAnimationActionChange(5);
	MMS3_teenPamPamActorAnimationActionChange(11);

	MMS3_drDeeblockTalk(MMS3_LANGUAGE_SCENEM00);

	PLEX_changeActor(p_drDeeblock, 1);

	MMS3_drDeeblockTalk(MMS3_LANGUAGE_SCENEM01);

	PLEX_changeActor(p_drDeeblock, 2);

	PLEX_changeSpriteTheaterMusic(MM_COMMON_THEMEID_AGGRESSION);

	PLEX_changeSpriteTheaterBackground(p_deeblockOfficeBackInvert, MMS_LANGUAGE_SETTING_DRDEEBLOCKSOFFICE);

	MMS3_pollockCodelliActorAnimationActionChange(12);
	MMS3_stephinaCodelliActorAnimationActionChange(14);

	MMS3_drDeeblockTalk(MMS3_LANGUAGE_SCENEM02);

	PLEX_changeSpriteTheaterMusic(MM_COMMON_THEMEID_DAYTODAY);

	PLEX_changeSpriteTheaterBackground(p_deeblockOfficeBack, MMS_LANGUAGE_SETTING_DRDEEBLOCKSOFFICE);

	PLEX_changeActor(p_drDeeblock, 1);
	MMS3_pollockCodelliActorAnimationActionChange(5);
	MMS3_stephinaCodelliActorAnimationActionChange(5);

	MMS3_drDeeblockTalk(MMS3_LANGUAGE_SCENEM03);

	PLEX_changeActor(p_drDeeblock, 0);

	MMS3_drDeeblockTalkWait(MMS3_LANGUAGE_SCENEM04, 3000);

	MMS3_stephinaCodelliTalk(MMS3_LANGUAGE_SCENEM05);

	MMS3_pollockTalk(MMS3_LANGUAGE_SCENEM06);

	PLEX_changeActor(p_drDeeblock, 3);

	MMS3_drDeeblockTalk(MMS3_LANGUAGE_SCENEM07);

	PLEX_changeActor(p_drDeeblock, 4);

	MMS3_drDeeblockTalk(MMS3_LANGUAGE_SCENEM08);
}

void MMS3_startSceneN(const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow)
{
	p_setDeeblockArea(fontPlate, label, bubble, arrow);

	PLEX_changeSpriteTheaterMusic(MM_COMMON_THEMEID_FEAR);

	MMS_pamNarration(MMS3_LANGUAGE_SCENEN00);

	p_setAsDeeblockKitchen(false, false);

	MMS_pamNarration(MMS3_LANGUAGE_SCENEN01);

	MMS_pamNarration(MMS3_LANGUAGE_SCENEN02);

	p_setAsDeeblockArena();

	MMS_pamNarration(MMS3_LANGUAGE_SCENEN03);

	p_setAsDeeblockQuarters(false);

	MMS_pamNarration(MMS3_LANGUAGE_SCENEN04);

	p_tvShowTalk(MMS3_LANGUAGE_SCENEN05);

	p_setAsDeeblockAngst();

	MMS_pamNarration(MMS3_LANGUAGE_SCENEN06);
}

void MMS3_startSceneO(const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow)
{
	p_setDeeblockArea(fontPlate, label, bubble, arrow);

	p_setAsDeeblockDrOffice(false);

	PLEX_changeSpriteTheaterMusic(MM_COMMON_THEMEID_STRIFE);

	MMS3_drDeeblockTalk(MMS3_LANGUAGE_SCENEO00);

	MMS3_deeblockPamPamTalk(MMS3_LANGUAGE_SCENEO01);

	PLEX_changeActor(p_drDeeblock, 3);

	MMS3_drDeeblockTalk(MMS3_LANGUAGE_SCENEO02);

	PLEX_changeActor(p_drDeeblock, 1);

	MMS3_drDeeblockTalk(MMS3_LANGUAGE_SCENEO03);

	PLEX_changeActor(p_drDeeblock, 5);

	MMS3_drDeeblockTalk(MMS3_LANGUAGE_SCENEO04);

	PLEX_changeActor(p_drDeeblock, 4);

	MMS3_drDeeblockTalk(MMS3_LANGUAGE_SCENEO05);

	PLEX_changeActor(p_drDeeblock, 1);

	MMS3_drDeeblockTalk(MMS3_LANGUAGE_SCENEO06);

	PLEX_changeActor(p_drDeeblock, 0);

	MMS3_deeblockPamPamTalk(MMS3_LANGUAGE_SCENEO07);

	MMS3_drDeeblockTalk(MMS3_LANGUAGE_SCENEO08);

	PLEX_changeActor(p_deeblockPamaleana, 1);
	PLEX_changeActor(p_cafeteriaGuards[0], 0);
	PLEX_changeActor(p_cafeteriaGuards[4], 1);

	MMS3_deeblockPamPamTalk(MMS3_LANGUAGE_SCENEO09);

	PLEX_hideActor(p_deeblockPamaleana);
	PLEX_hideActor(p_cafeteriaGuards[0]);
	PLEX_hideActor(p_cafeteriaGuards[4]);

	PLEX_changeActor(p_drDeeblock, 1);

	MMS3_drDeeblockTalk(MMS3_LANGUAGE_SCENEO10);
}

void MMS3_startSceneP(const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow)
{
	p_setDeeblockArea(fontPlate, label, bubble, arrow);

	PLEX_changeSpriteTheaterMusic(MM_COMMON_THEMEID_DREAM);

	MMS_pamNarration(MMS3_LANGUAGE_SCENEP00);

	p_setAsDeeblockKitchen(true, false);

	MMS_pamNarration(MMS3_LANGUAGE_SCENEP01);

	MMS_pamNarration(MMS3_LANGUAGE_SCENEP02);

	PLEX_changeSpriteTheaterMusic(MM_COMMON_THEMEID_METAL);

	PLEX_unhideActor(p_hellDemonBeatDown);

	MMS_pamNarration(MMS3_LANGUAGE_SCENEP03);

	MMS3_deeblockPamPamTalk(MMS3_LANGUAGE_SCENEP04);

	p_facelessPersonTalk(MMS3_LANGUAGE_SCENEP05);

	MMS3_deeblockPamPamTalk(MMS3_LANGUAGE_SCENEP06);

	p_facelessPersonTalk(MMS3_LANGUAGE_SCENEP07);

	MMS3_deeblockPamPamTalk(MMS3_LANGUAGE_SCENEP08);
}

void MMS3_startSceneQ(const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow)
{
	p_setDeeblockArea(fontPlate, label, bubble, arrow);

	PLEX_changeSpriteTheaterMusic(MM_COMMON_THEMEID_DAYTODAY);

	MMS_pamNarration(MMS3_LANGUAGE_SCENEQ00);

	p_setAsDeeblockKitchen(true, true);

	MMS3_deeblockPamPamTalk(MMS3_LANGUAGE_SCENEQ01);

	MMS3_hellDemon666Talk(MMS3_LANGUAGE_SCENEQ02);

	MMS3_deeblockPamPamTalk(MMS3_LANGUAGE_SCENEQ03);

	MMS3_hellDemon666Talk(MMS3_LANGUAGE_SCENEQ04);

	MMS3_deeblockPamPamTalk(MMS3_LANGUAGE_SCENEQ05);

	MMS3_hellDemon666Talk(MMS3_LANGUAGE_SCENEQ06);

	MMS3_deeblockPamPamTalk(MMS3_LANGUAGE_SCENEQ07);

	MMS3_hellDemon666Talk(MMS3_LANGUAGE_SCENEQ08);

	MMS3_deeblockPamPamTalk(MMS3_LANGUAGE_SCENEQ09);

	MMS3_hellDemon666Talk(MMS3_LANGUAGE_SCENEQ10);

	MMS3_deeblockPamPamTalk(MMS3_LANGUAGE_SCENEQ11);

	MMS3_hellDemon666Talk(MMS3_LANGUAGE_SCENEQ12);

	MMS3_deeblockPamPamTalk(MMS3_LANGUAGE_SCENEQ13);

	MMS3_hellDemon666Talk(MMS3_LANGUAGE_SCENEQ14);

	MMS3_deeblockPamPamTalk(MMS3_LANGUAGE_SCENEQ15);

	MMS3_hellDemon666Talk(MMS3_LANGUAGE_SCENEQ16);

	MMS3_deeblockPamPamTalk(MMS3_LANGUAGE_SCENEQ17);
}

void MMS3_startSceneR(const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow)
{
	p_setDeeblockArea(fontPlate, label, bubble, arrow);

	PLEX_changeSpriteTheaterMusic(MM_COMMON_THEMEID_SUSPENSE);

	MMS_pamNarration(MMS3_LANGUAGE_SCENER00);

	p_setAsDeeblockQuarters(true);

	p_workerATalk(MMS3_LANGUAGE_SCENER01);

	MMS3_deeblockPamPamTalk(MMS3_LANGUAGE_SCENER02);

	p_workerBTalk(MMS3_LANGUAGE_SCENER03);

	p_workerBTalk(MMS3_LANGUAGE_SCENER04);

	MMS3_deeblockPamPamTalk(MMS3_LANGUAGE_SCENER05);

	p_workerBTalk(MMS3_LANGUAGE_SCENER06);
}

void MMS3_drDeeblockTalkWait(const char* const message, const uint64_t wait)
{
	PLEX_addSpriteTheaterSlide(235, 25, 55, message, p_drDeeblock, wait, true);
}

void MMS3_drDeeblockTalk(const char* const message)
{
	MMS3_drDeeblockTalkWait(message, 0);
}

void MMS3_addDrDeeblock(const double x, const double y)
{
	p_drDeeblock = PLEX_createActor(p_drDeeblockSprite, 0, PLEX_convRect(PLEX_convPoint(x, y), PLEX_convDimens(2, 4)), false);
}

void MMS3_changeDeeblockAnimation(const size_t index)
{
	PLEX_changeActor(p_drDeeblock, index);
}

void MMS3_hideDeeblock()
{
	PLEX_hideActor(p_drDeeblock);
}

void MMS3_unhideDeeblock()
{
	PLEX_unhideActor(p_drDeeblock);
}

void MMS3_moveDeeblock(const double x, const double y)
{
	PLEX_moveActor(p_drDeeblock, x, y);
}

void MMS3_addDeeblockPamaleana()
{
	p_deeblockPamaleana = PLEX_createActor(p_deeblockPamSprite, 0, PLEX_convRect(PLEX_convPoint(0, 0), PLEX_convDimens(2, 4)), true);
}

void MMS3_hideDeeblockPamaleana()
{
	PLEX_hideActor(p_deeblockPamaleana);
}

void MMS3_unhideDeeblockPamaleana()
{
	PLEX_unhideActor(p_deeblockPamaleana);
}

void MMS3_changeDeeblockPamaleana(const size_t index)
{
	PLEX_changeActor(p_deeblockPamaleana, index);
}

void MMS3_moveDeeblockPamaleana(const double x, const double y)
{
	PLEX_moveActor(p_deeblockPamaleana, x, y);
}

void MMS3_deeblockPamPamTalk(const char* const message)
{
	PLEX_addSpriteTheaterSlide(29, 180, 255, message, p_deeblockPamaleana, 0, false);
}

void MMS3_hideHellDemon666()
{
	PLEX_hideActor(p_hellDemon666);
}

void MMS3_unhideHellDemon666()
{
	PLEX_unhideActor(p_hellDemon666);
}

void MMS3_moveHellDemon666(const double x, const double y)
{
	PLEX_moveActor(p_hellDemon666, x, y);
}

void MMS3_hellDemon666Talk(const char* const message)
{
	PLEX_addSpriteTheaterSlide(200, 100, 100, message, p_hellDemon666, 0, false);
}

size_t MMS3_createLightCone(const double x, const double y)
{
	return PLEX_createActor(p_lightConeSprite, 0, PLEX_convRect(PLEX_convPoint(x, y), PLEX_convDimens(5, 10)), false);
}

void MMS3_addLightCone(const double x, const double y)
{
	p_lightCone = MMS3_createLightCone(x, y);
}

void MMS3_hideLightCone()
{
	PLEX_hideActor(p_lightCone);
}

void MMS3_unhideLightCone()
{
	PLEX_unhideActor(p_lightCone);
}

void MMS3_addHelldemon666()
{
	p_hellDemon666 = PLEX_createActor(p_hellDemon666Sprite, 0, PLEX_convRect(PLEX_convPoint(0, 0), PLEX_convDimens(2, 4)), true);
}

void MMS3_changeActorHellDemon666(const size_t index)
{
	PLEX_changeActor(p_hellDemon666, index);
}

void MMS3_addDeeblockChairs()
{
	p_deeblockChair1 = PLEX_createActor(p_deeblockChairSprite, 0, PLEX_convRect(PLEX_convPoint(PLEX_WIDTHUNITMAX()/2 - 3, PLEX_HEIGHTUNITMAX() * 0.75 + 2), PLEX_convDimens(2, 4)), false);

	p_deeblockChair2 = PLEX_createActor(p_deeblockChairSprite, 0, PLEX_convRect(PLEX_convPoint(PLEX_WIDTHUNITMAX()/2 + 2, PLEX_HEIGHTUNITMAX() * 0.75 + 2), PLEX_convDimens(2, 4)), false);
}

void MMS3_loadDeeblockOfficeBack()
{
	if(!p_deeblockOfficeBack) p_deeblockOfficeBack = PLEX_loadTextureFromFile(3840, 1640, 255, 255, 255, 255, 0, MMS3_FILEPATH_TEX_DEEBLOCKOFFICE);
}

void MMS3_setSceneDeeblockOffice(const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow)
{
	PLEX_startSpriteTheater(MMS_LANGUAGE_SETTING_DRDEEBLOCKSOFFICE, p_deeblockOfficeBack, 0, 0, 400, 100, 255, 255, 255, fontPlate, label, bubble, arrow, PLEX_getGameTime());
}

void MMS3_createSection4(const size_t chapter3SpriteTex, const size_t tvShowTex)
{
	p_createDrDeeblock(chapter3SpriteTex);
	p_createDeeblockChairs(chapter3SpriteTex);
	p_createCafeteriaDenizens(chapter3SpriteTex);
	p_createCafeteriaGuards(chapter3SpriteTex);
	p_createFightingKids(chapter3SpriteTex);
	p_createFacelessCrowd(chapter3SpriteTex);
	p_createTVShow(tvShowTex);
	p_createLightCone(chapter3SpriteTex);
	p_createDeeblockPamaleana(chapter3SpriteTex);
	p_createHellDemonBeatdown(chapter3SpriteTex);
	p_createHellDemon666(chapter3SpriteTex);
}

void MMS3_freeSection4()
{
	if(p_deeblockOutsideBack) PLEX_destroyTexture(p_deeblockOutsideBack);
	if(p_deeblockOfficeBack) PLEX_destroyTexture(p_deeblockOfficeBack);
	if(p_deeblockOfficeBackInvert) PLEX_destroyTexture(p_deeblockOfficeBackInvert);
	if(p_deeblockCafeteriaBack) PLEX_destroyTexture(p_deeblockCafeteriaBack);
	if(p_deeblockArenaBack) PLEX_destroyTexture(p_deeblockArenaBack);
	if(p_deeblockQuartersBack) PLEX_destroyTexture(p_deeblockQuartersBack);
	if(p_deeblockAngstBack) PLEX_destroyTexture(p_deeblockAngstBack);

	p_deeblockOutsideBack = 0;
	p_deeblockOfficeBack = 0;
	p_deeblockOfficeBackInvert = 0;
	p_deeblockCafeteriaBack = 0;
	p_deeblockArenaBack = 0;
	p_deeblockQuartersBack = 0;
	p_deeblockAngstBack = 0;
}

void MMS3_finalFreeSection4()
{
	PLEX_destroySprite(&p_drDeeblockSprite);
	PLEX_destroySprite(&p_deeblockChairSprite);

	PLEX_destroySprite(&p_cafeteriaDenizenSprite);
	PLEX_destroySprite(&p_cafeteriaGuardSprite);

	PLEX_destroySprite(&p_fightingKidSprite);

	PLEX_destroySprite(&p_facelessCrowdSprite);

	PLEX_destroySprite(&p_tvShowSprite);

	PLEX_destroySprite(&p_lightConeSprite);

	PLEX_destroySprite(&p_deeblockPamSprite);

	PLEX_destroySprite(&p_hellDemonBeatDownSprite);
	PLEX_destroySprite(&p_hellDemon666Sprite);
}
