#include "chapters/mms3.h"

static size_t p_highschoolBack = 0;
static size_t p_highwayBack = 0;
static size_t p_megadomeGarageBack = 0;

static size_t p_teenPamaleana = 0;
static size_t p_spikeFuck = 0;
static size_t p_stephinaCarBack = 0;
static size_t p_stephinaCarFront = 0;
static size_t p_biker = 0;
static size_t p_traffic[6];

static size_t p_blackVan = 0;
static size_t p_thug1 = 0;
static size_t p_thug2 = 0;

PLEX_SPRITE* p_teenPamaleanaSprite = NULL;
PLEX_SPRITE* p_spikeFuckSprite = NULL;
PLEX_SPRITE* p_stephinaCarBackSprite = NULL;
PLEX_SPRITE* p_stephinaCarFrontSprite = NULL;
PLEX_SPRITE* p_bikerSprite = NULL;

PLEX_SPRITE* p_trafficSprite[4] = { NULL, NULL, NULL, NULL };

PLEX_SPRITE* p_blackVanSprite = NULL;
PLEX_SPRITE* p_thug1Sprite = NULL;
PLEX_SPRITE* p_thug2Sprite = NULL;

static void p_spikeFuckTalk(const char* const message)
{
	PLEX_addSpriteTheaterSlide(180, 0, 0, message, p_spikeFuck, 0, true);
}

static void p_carFrontTalk(const char* const message)
{
	PLEX_addSpriteTheaterSlide(60, 200, 50, message, p_stephinaCarFront, 0, true);
}

static void p_thugTalk(const char* const message)
{
	PLEX_addSpriteTheaterSlide(255, 100, 0, message, p_thug2, 0, true);
}

static void p_createTeenPamaleana(const size_t chapter3SpriteTex)
{
	PLEX_ANIMATION* teenPamUp = NULL;
	PLEX_ANIMATION* teenPamNormal = NULL;
	PLEX_ANIMATION* teenPamShrugs = NULL;
	PLEX_ANIMATION* teenPamThoughtPose = NULL;
	PLEX_ANIMATION* teenPamShocked = NULL;
	PLEX_ANIMATION* teenPamShakeHead = NULL;
	PLEX_ANIMATION* teenPamAngry = NULL;
	PLEX_ANIMATION* teenPamAnimated = NULL;
	PLEX_ANIMATION* teenPamReallyAngry = NULL;
	PLEX_ANIMATION* teenPamConcertCelebrate = NULL;
	PLEX_ANIMATION* teenPamKnockedOut = NULL;
	PLEX_ANIMATION* teenPamMuzzled = NULL;
	PLEX_ANIMATION* teenPamCafeteria = NULL;
	PLEX_ANIMATION* teenPamEscape = NULL;

	PLEX_ANIMATION_PLATE teenPamPlate = PLEX_createAnimationPlate(0.0625, 0.03125, chapter3SpriteTex);

	p_teenPamaleanaSprite = PLEX_genSprite(&teenPamPlate);

	PLEX_addAnimation(p_teenPamaleanaSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_teenPamaleanaSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_teenPamaleanaSprite, 500, PLEX_getGameTime());
	PLEX_addAnimation(p_teenPamaleanaSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_teenPamaleanaSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_teenPamaleanaSprite, 500, PLEX_getGameTime());
	PLEX_addAnimation(p_teenPamaleanaSprite, 500, PLEX_getGameTime());
	PLEX_addAnimation(p_teenPamaleanaSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_teenPamaleanaSprite, 500, PLEX_getGameTime());
	PLEX_addAnimation(p_teenPamaleanaSprite, 500, PLEX_getGameTime());
	PLEX_addAnimation(p_teenPamaleanaSprite, 4000, PLEX_getGameTime());
	PLEX_addAnimation(p_teenPamaleanaSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_teenPamaleanaSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_teenPamaleanaSprite, 1, PLEX_getGameTime());

	teenPamUp = PLEX_getAnimation(0, p_teenPamaleanaSprite);

	PLEX_addAnimationFrame(75, teenPamUp);

	teenPamNormal = PLEX_getAnimation(1, p_teenPamaleanaSprite);

	PLEX_addAnimationFrame(76, teenPamNormal);

	teenPamShrugs = PLEX_getAnimation(2, p_teenPamaleanaSprite);

	PLEX_addAnimationFrame(76, teenPamShrugs);
	PLEX_addAnimationFrame(77, teenPamShrugs);

	teenPamThoughtPose = PLEX_getAnimation(3, p_teenPamaleanaSprite);

	PLEX_addAnimationFrame(78, teenPamThoughtPose);

	teenPamShocked = PLEX_getAnimation(4, p_teenPamaleanaSprite);

	PLEX_addAnimationFrame(79, teenPamShocked);

	teenPamShakeHead = PLEX_getAnimation(5, p_teenPamaleanaSprite);

	PLEX_addAnimationFrame(76, teenPamShakeHead);
	PLEX_addAnimationFrame(80, teenPamShakeHead);
	PLEX_addAnimationFrame(81, teenPamShakeHead);

	teenPamAnimated = PLEX_getAnimation(6, p_teenPamaleanaSprite);

	PLEX_addAnimationFrame(76, teenPamAnimated);
	PLEX_addAnimationFrame(82, teenPamAnimated);

	teenPamAngry = PLEX_getAnimation(7, p_teenPamaleanaSprite);

	PLEX_addAnimationFrame(83, teenPamAngry);

	teenPamReallyAngry = PLEX_getAnimation(8, p_teenPamaleanaSprite);

	PLEX_addAnimationFrame(83, teenPamReallyAngry);
	PLEX_addAnimationFrame(84, teenPamReallyAngry);

	teenPamConcertCelebrate = PLEX_getAnimation(9, p_teenPamaleanaSprite);

	PLEX_addAnimationFrame(85, teenPamConcertCelebrate);
	PLEX_addAnimationFrame(86, teenPamConcertCelebrate);
	PLEX_addAnimationFrame(85, teenPamConcertCelebrate);
	PLEX_addAnimationFrame(87, teenPamConcertCelebrate);

	teenPamKnockedOut = PLEX_getAnimation(10, p_teenPamaleanaSprite);

	PLEX_addAnimationFrame(85, teenPamKnockedOut);
	PLEX_addAnimationFrame(88, teenPamKnockedOut);
	PLEX_addAnimationFrame(88, teenPamKnockedOut);
	PLEX_addAnimationFrame(88, teenPamKnockedOut);
	PLEX_addAnimationFrame(88, teenPamKnockedOut);
	PLEX_addAnimationFrame(88, teenPamKnockedOut);

	teenPamMuzzled = PLEX_getAnimation(11, p_teenPamaleanaSprite);

	PLEX_addAnimationFrame(90, teenPamMuzzled);

	teenPamCafeteria = PLEX_getAnimation(12, p_teenPamaleanaSprite);

	PLEX_addAnimationFrame(92, teenPamCafeteria);

	teenPamEscape = PLEX_getAnimation(13, p_teenPamaleanaSprite);

	PLEX_addAnimationFrame(93, teenPamEscape);

	PLEX_startSprite(PLEX_getGameTime(), p_teenPamaleanaSprite);
}

static void p_createSpikeFuck(const size_t chapter3SpriteTex)
{
	PLEX_ANIMATION* spikeFuckNormal = NULL;
	PLEX_ANIMATION* spikeFuckLaugh = NULL;
	PLEX_ANIMATION* spikeFuckPoint = NULL;
	PLEX_ANIMATION* spikeFuckShakesHead = NULL;
	PLEX_ANIMATION* spikeFuckShrugs = NULL;
	PLEX_ANIMATION* spikeFuckTurnAway = NULL;
	PLEX_ANIMATION* spikeFuckThoughtPose = NULL;
	PLEX_ANIMATION* spikeFuckConcertCelebrate = NULL;
	PLEX_ANIMATION* spikeFuckConcertDespair = NULL;
	PLEX_ANIMATION* spikeFuckConcertHeldUp = NULL;
	PLEX_ANIMATION* spikeFuckConcertShakingFist = NULL;
	PLEX_ANIMATION* spikeFuckConcertBend = NULL;
	PLEX_ANIMATION* spikeFuckConcertPhone = NULL;

	PLEX_ANIMATION_PLATE spikeFuckPlate = PLEX_createAnimationPlate(0.0625, 0.03125, chapter3SpriteTex);

	p_spikeFuckSprite = PLEX_genSprite(&spikeFuckPlate);

	PLEX_addAnimation(p_spikeFuckSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_spikeFuckSprite, 200, PLEX_getGameTime());
	PLEX_addAnimation(p_spikeFuckSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_spikeFuckSprite, 500, PLEX_getGameTime());
	PLEX_addAnimation(p_spikeFuckSprite, 500, PLEX_getGameTime());
	PLEX_addAnimation(p_spikeFuckSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_spikeFuckSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_spikeFuckSprite, 500, PLEX_getGameTime());
	PLEX_addAnimation(p_spikeFuckSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_spikeFuckSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_spikeFuckSprite, 500, PLEX_getGameTime());
	PLEX_addAnimation(p_spikeFuckSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_spikeFuckSprite, 1, PLEX_getGameTime());

	spikeFuckNormal = PLEX_getAnimation(0, p_spikeFuckSprite);

	PLEX_addAnimationFrame(96, spikeFuckNormal);

	spikeFuckLaugh = PLEX_getAnimation(1, p_spikeFuckSprite);

	PLEX_addAnimationFrame(96, spikeFuckLaugh);
	PLEX_addAnimationFrame(97, spikeFuckLaugh);

	spikeFuckPoint = PLEX_getAnimation(2, p_spikeFuckSprite);

	PLEX_addAnimationFrame(98, spikeFuckPoint);

	spikeFuckShakesHead = PLEX_getAnimation(3, p_spikeFuckSprite);

	PLEX_addAnimationFrame(96, spikeFuckShakesHead);
	PLEX_addAnimationFrame(99, spikeFuckShakesHead);
	PLEX_addAnimationFrame(96, spikeFuckShakesHead);
	PLEX_addAnimationFrame(100, spikeFuckShakesHead);

	spikeFuckShrugs = PLEX_getAnimation(4, p_spikeFuckSprite);

	PLEX_addAnimationFrame(96, spikeFuckShrugs);
	PLEX_addAnimationFrame(101, spikeFuckShrugs);

	spikeFuckTurnAway = PLEX_getAnimation(5, p_spikeFuckSprite);

	PLEX_addAnimationFrame(102, spikeFuckTurnAway);

	spikeFuckThoughtPose = PLEX_getAnimation(6, p_spikeFuckSprite);

	PLEX_addAnimationFrame(103, spikeFuckThoughtPose);

	spikeFuckConcertCelebrate = PLEX_getAnimation(7, p_spikeFuckSprite);

	PLEX_addAnimationFrame(105, spikeFuckConcertCelebrate);
	PLEX_addAnimationFrame(104, spikeFuckConcertCelebrate);
	PLEX_addAnimationFrame(106, spikeFuckConcertCelebrate);
	PLEX_addAnimationFrame(104, spikeFuckConcertCelebrate);

	spikeFuckConcertDespair = PLEX_getAnimation(8, p_spikeFuckSprite);

	PLEX_addAnimationFrame(107, spikeFuckConcertDespair);

	spikeFuckConcertHeldUp = PLEX_getAnimation(9, p_spikeFuckSprite);

	PLEX_addAnimationFrame(108, spikeFuckConcertHeldUp);

	spikeFuckConcertShakingFist = PLEX_getAnimation(10, p_spikeFuckSprite);

	PLEX_addAnimationFrame(109, spikeFuckConcertShakingFist);
	PLEX_addAnimationFrame(110, spikeFuckConcertShakingFist);

	spikeFuckConcertBend = PLEX_getAnimation(11, p_spikeFuckSprite);

	PLEX_addAnimationFrame(111, spikeFuckConcertBend);

	spikeFuckConcertPhone = PLEX_getAnimation(12, p_spikeFuckSprite);

	PLEX_addAnimationFrame(89, spikeFuckConcertPhone);

	PLEX_startSprite(PLEX_getGameTime(), p_spikeFuckSprite);
}

static void p_createCarBack(const size_t chapter3SpriteTex)
{
	PLEX_ANIMATION* carBackNormal = NULL;

	PLEX_ANIMATION_PLATE carBackPlate = PLEX_createAnimationPlate(0.125, 0.03125, chapter3SpriteTex);

	p_stephinaCarBackSprite = PLEX_genSprite(&carBackPlate);

	PLEX_addAnimation(p_stephinaCarBackSprite, 1, PLEX_getGameTime());

	carBackNormal = PLEX_getAnimation(0, p_stephinaCarBackSprite);

	PLEX_addAnimationFrame(64, carBackNormal);
}

static void p_createCarFront(const size_t chapter3SpriteTex)
{
	PLEX_ANIMATION* carFrontNormal = NULL;
	PLEX_ANIMATION* carFrontBrake = NULL;
	PLEX_ANIMATION* carFrontStopped = NULL;

	PLEX_ANIMATION_PLATE carFrontPlate = PLEX_createAnimationPlate(0.125, 0.03125, chapter3SpriteTex);

	p_stephinaCarFrontSprite = PLEX_genSprite(&carFrontPlate);

	PLEX_addAnimation(p_stephinaCarFrontSprite, 500, PLEX_getGameTime());
	PLEX_addAnimation(p_stephinaCarFrontSprite, 500, PLEX_getGameTime());
	PLEX_addAnimation(p_stephinaCarFrontSprite, 1, PLEX_getGameTime());

	carFrontNormal = PLEX_getAnimation(0, p_stephinaCarFrontSprite);

	PLEX_addAnimationFrame(56, carFrontNormal);
	PLEX_addAnimationFrame(57, carFrontNormal);
	PLEX_addAnimationFrame(58, carFrontNormal);

	carFrontBrake = PLEX_getAnimation(1, p_stephinaCarFrontSprite);

	PLEX_addAnimationFrame(59, carFrontBrake);
	PLEX_addAnimationFrame(60, carFrontBrake);
	PLEX_addAnimationFrame(61, carFrontBrake);

	carFrontStopped = PLEX_getAnimation(2, p_stephinaCarFrontSprite);

	PLEX_addAnimationFrame(56, carFrontStopped);

	PLEX_startSprite(PLEX_getGameTime(), p_stephinaCarFrontSprite);
}

static void p_createTraffic(const size_t chapter3SpriteTex)
{
	// BIKER

	PLEX_ANIMATION* bikerNormal = NULL;
	PLEX_ANIMATION* bikerCrash = NULL;
	PLEX_ANIMATION* bikerInferno = NULL;

	// TRAFFIC 0

	PLEX_ANIMATION* traffic0Normal = NULL;
	PLEX_ANIMATION* traffic0Swap = NULL;

	// TRAFFIC 1

	PLEX_ANIMATION* traffic1Normal = NULL;
	PLEX_ANIMATION* traffic1Swap = NULL;

	// TRAFFIC 2

	PLEX_ANIMATION* traffic2Normal = NULL;
	PLEX_ANIMATION* traffic2Swap = NULL;

	// TRAFFIC 3

	PLEX_ANIMATION* traffic3Normal = NULL;
	PLEX_ANIMATION* traffic3Swap = NULL;

	// PLATES

	PLEX_ANIMATION_PLATE bikerPlate = PLEX_createAnimationPlate(0.125, 0.03125, chapter3SpriteTex);
	PLEX_ANIMATION_PLATE trafficPlate = PLEX_createAnimationPlate(0.125, 0.03125, chapter3SpriteTex);

	// BIKER

	p_bikerSprite = PLEX_genSprite(&bikerPlate);

	PLEX_addAnimation(p_bikerSprite, 500, PLEX_getGameTime());
	PLEX_addAnimation(p_bikerSprite, 500, PLEX_getGameTime());
	PLEX_addAnimation(p_bikerSprite, 500, PLEX_getGameTime());

	bikerNormal = PLEX_getAnimation(0, p_bikerSprite);

	PLEX_addAnimationFrame(65, bikerNormal);
	PLEX_addAnimationFrame(66, bikerNormal);
	PLEX_addAnimationFrame(67, bikerNormal);

	bikerCrash = PLEX_getAnimation(1, p_bikerSprite);

	PLEX_addAnimationFrame(68, bikerCrash);
	PLEX_addAnimationFrame(69, bikerCrash);
	PLEX_addAnimationFrame(70, bikerCrash);

	bikerInferno = PLEX_getAnimation(2, p_bikerSprite);

	PLEX_addAnimationFrame(71, bikerInferno);
	PLEX_addAnimationFrame(72, bikerInferno);

	PLEX_startSprite(PLEX_getGameTime(), p_bikerSprite);

	// TRAFFIC 0

	p_trafficSprite[0] = PLEX_genSprite(&trafficPlate);

	PLEX_addAnimation(p_trafficSprite[0], 500, PLEX_getGameTime());
	PLEX_addAnimation(p_trafficSprite[0], 1000, PLEX_getGameTime());

	traffic0Normal = PLEX_getAnimation(0, p_trafficSprite[0]);

	PLEX_addAnimationFrame(73, traffic0Normal);
	PLEX_addAnimationFrame(74, traffic0Normal);
	PLEX_addAnimationFrame(75, traffic0Normal);
	PLEX_addAnimationFrame(76, traffic0Normal);

	traffic0Swap = PLEX_getAnimation(1, p_trafficSprite[0]);

	PLEX_addAnimationFrame(73, traffic0Swap);
	PLEX_addAnimationFrame(77, traffic0Swap);
	PLEX_addAnimationFrame(74, traffic0Swap);
	PLEX_addAnimationFrame(78, traffic0Swap);
	PLEX_addAnimationFrame(75, traffic0Swap);
	PLEX_addAnimationFrame(79, traffic0Swap);

	PLEX_startSprite(PLEX_getGameTime(), p_trafficSprite[0]);

	// TRAFFIC 1

	p_trafficSprite[1] = PLEX_genSprite(&trafficPlate);

	PLEX_addAnimation(p_trafficSprite[1], 500, PLEX_getGameTime());
	PLEX_addAnimation(p_trafficSprite[1], 1000, PLEX_getGameTime());

	traffic1Normal = PLEX_getAnimation(0, p_trafficSprite[1]);

	PLEX_addAnimationFrame(77, traffic1Normal);
	PLEX_addAnimationFrame(78, traffic1Normal);
	PLEX_addAnimationFrame(79, traffic1Normal);

	traffic1Swap = PLEX_getAnimation(1, p_trafficSprite[1]);

	PLEX_addAnimationFrame(77, traffic1Swap);
	PLEX_addAnimationFrame(74, traffic1Swap);
	PLEX_addAnimationFrame(78, traffic1Swap);
	PLEX_addAnimationFrame(75, traffic1Swap);
	PLEX_addAnimationFrame(79, traffic1Swap);
	PLEX_addAnimationFrame(73, traffic1Swap);

	PLEX_startSprite(PLEX_getGameTime(), p_trafficSprite[1]);

	// TRAFFIC 2

	p_trafficSprite[2] = PLEX_genSprite(&trafficPlate);

	PLEX_addAnimation(p_trafficSprite[2], 500, PLEX_getGameTime());
	PLEX_addAnimation(p_trafficSprite[2], 1000, PLEX_getGameTime());

	traffic2Normal = PLEX_getAnimation(0, p_trafficSprite[2]);

	PLEX_addAnimationFrame(80, traffic2Normal);
	PLEX_addAnimationFrame(81, traffic2Normal);
	PLEX_addAnimationFrame(82, traffic2Normal);

	traffic2Swap = PLEX_getAnimation(1, p_trafficSprite[2]);

	PLEX_addAnimationFrame(80, traffic2Swap);
	PLEX_addAnimationFrame(83, traffic2Swap);
	PLEX_addAnimationFrame(81, traffic2Swap);
	PLEX_addAnimationFrame(84, traffic2Swap);
	PLEX_addAnimationFrame(82, traffic2Swap);
	PLEX_addAnimationFrame(85, traffic2Swap);

	PLEX_startSprite(PLEX_getGameTime(), p_trafficSprite[2]);

	// TRAFFIC 3

	p_trafficSprite[3] = PLEX_genSprite(&trafficPlate);

	PLEX_addAnimation(p_trafficSprite[3], 500, PLEX_getGameTime());
	PLEX_addAnimation(p_trafficSprite[3], 1000, PLEX_getGameTime());

	traffic3Normal = PLEX_getAnimation(0, p_trafficSprite[3]);

	PLEX_addAnimationFrame(83, traffic3Normal);
	PLEX_addAnimationFrame(84, traffic3Normal);
	PLEX_addAnimationFrame(85, traffic3Normal);

	traffic3Swap = PLEX_getAnimation(1, p_trafficSprite[3]);

	PLEX_addAnimationFrame(83, traffic3Swap);
	PLEX_addAnimationFrame(81, traffic3Swap);
	PLEX_addAnimationFrame(84, traffic3Swap);
	PLEX_addAnimationFrame(82, traffic3Swap);
	PLEX_addAnimationFrame(85, traffic3Swap);
	PLEX_addAnimationFrame(80, traffic3Swap);

	PLEX_startSprite(PLEX_getGameTime(), p_trafficSprite[3]);
}

static void p_createBlackVan(const size_t chapter3SpriteTex)
{
	PLEX_ANIMATION* blackVanClosed = NULL;
	PLEX_ANIMATION* blackVanOpen = NULL;
	PLEX_ANIMATION* blackVanOpenPam = NULL;

	PLEX_ANIMATION_PLATE blackVanPlate = PLEX_createAnimationPlate(0.125, 0.03125, chapter3SpriteTex);

	p_blackVanSprite = PLEX_genSprite(&blackVanPlate);

	PLEX_addAnimation(p_blackVanSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_blackVanSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_blackVanSprite, 1, PLEX_getGameTime());

	blackVanClosed = PLEX_getAnimation(0, p_blackVanSprite);

	PLEX_addAnimationFrame(86, blackVanClosed);

	blackVanOpen = PLEX_getAnimation(1, p_blackVanSprite);

	PLEX_addAnimationFrame(87, blackVanOpen);

	blackVanOpenPam = PLEX_getAnimation(2, p_blackVanSprite);

	PLEX_addAnimationFrame(88, blackVanOpenPam);
}

static void p_createThugOne(const size_t chapter3SpriteTex)
{
	PLEX_ANIMATION* thugOneSmack = NULL;

	PLEX_ANIMATION_PLATE thugOnePlate = PLEX_createAnimationPlate(0.0625, 0.03125, chapter3SpriteTex);

	p_thug1Sprite = PLEX_genSprite(&thugOnePlate);

	PLEX_addAnimation(p_thug1Sprite, 4000, PLEX_getGameTime());

	thugOneSmack = PLEX_getAnimation(0, p_thug1Sprite);

	PLEX_addAnimationFrame(124, thugOneSmack);
	PLEX_addAnimationFrame(125, thugOneSmack);
	PLEX_addAnimationFrame(126, thugOneSmack);
	PLEX_addAnimationFrame(126, thugOneSmack);
	PLEX_addAnimationFrame(126, thugOneSmack);
	PLEX_addAnimationFrame(126, thugOneSmack);
	PLEX_addAnimationFrame(126, thugOneSmack);
	PLEX_addAnimationFrame(126, thugOneSmack);
	PLEX_addAnimationFrame(126, thugOneSmack);
	PLEX_addAnimationFrame(126, thugOneSmack);

	PLEX_startSprite(PLEX_getGameTime(), p_thug1Sprite);
}

static void p_createThugTwo(const size_t chapter3SpriteTex)
{
	PLEX_ANIMATION* thugTwoHoldUp = NULL;

	PLEX_ANIMATION_PLATE thugTwoPlate = PLEX_createAnimationPlate(0.0625, 0.03125, chapter3SpriteTex);

	p_thug2Sprite = PLEX_genSprite(&thugTwoPlate);

	PLEX_addAnimation(p_thug2Sprite, 1, PLEX_getGameTime());

	thugTwoHoldUp = PLEX_getAnimation(0, p_thug2Sprite);

	PLEX_addAnimationFrame(127, thugTwoHoldUp);
}

static void p_addSpikeFuck(const double x, const double y)
{
	p_spikeFuck = PLEX_createActor(p_spikeFuckSprite, 0, PLEX_convRect(PLEX_convPoint(x, y), PLEX_convDimens(2, 4)), false);
}

static void p_addCarBack(const double x, const double y)
{
	p_stephinaCarBack = PLEX_createActor(p_stephinaCarBackSprite, 0, PLEX_convRect(PLEX_convPoint(x, y), PLEX_convDimens(4, 4)), false);
}

static void p_addCarFrontAndTraffic(const double x, const double y)
{
	p_biker = PLEX_createActor(p_bikerSprite, 0, PLEX_convRect(PLEX_convPoint(x + 2, y - 2.5), PLEX_convDimens(2, 2)), false);

	p_traffic[0] = PLEX_createActor(p_trafficSprite[0], 0, PLEX_convRect(PLEX_convPoint(x - 6, y + 1), PLEX_convDimens(4, 4)), false);

	p_traffic[1] = PLEX_createActor(p_trafficSprite[1], 0, PLEX_convRect(PLEX_convPoint(x - 1.25, y - 1), PLEX_convDimens(2, 2)), false);

	p_traffic[2] = PLEX_createActor(p_trafficSprite[2], 0, PLEX_convRect(PLEX_convPoint(x + 5, y + 1), PLEX_convDimens(4, 4)), false);

	p_traffic[3] = PLEX_createActor(p_trafficSprite[3], 0, PLEX_convRect(PLEX_convPoint(x + 4.25, y - 1), PLEX_convDimens(2, 2)), false);

	p_traffic[4] = PLEX_createActor(p_trafficSprite[3], 0, PLEX_convRect(PLEX_convPoint(x + 10, y), PLEX_convDimens(4, 4)), false);

	p_traffic[5] = PLEX_createActor(p_trafficSprite[2], 0, PLEX_convRect(PLEX_convPoint(x + 7.25, y - 1), PLEX_convDimens(2, 2)), false);

	p_stephinaCarFront = PLEX_createActor(p_stephinaCarFrontSprite, 0, PLEX_convRect(PLEX_convPoint(x, y), PLEX_convDimens(4, 4)), false);
}

static void p_addBlackVan(const double x, const double y)
{
	p_blackVan = PLEX_createActor(p_blackVanSprite, 0, PLEX_convRect(PLEX_convPoint(x, y), PLEX_convDimens(4, 4)), true);
}

static void p_addThugOne(const double x, const double y)
{
	p_thug1 = PLEX_createActor(p_thug1Sprite, 0, PLEX_convRect(PLEX_convPoint(x, y), PLEX_convDimens(2, 4)), true);
}

static void p_addThugTwo(const double x, const double y)
{
	p_thug2 = PLEX_createActor(p_thug2Sprite, 0, PLEX_convRect(PLEX_convPoint(x, y), PLEX_convDimens(2, 4)), true);
}

static void p_loadHighSchoolBack()
{
	if(!p_highschoolBack) p_highschoolBack = PLEX_loadTextureFromFileOrHeaderless(3840, 1640, 255, 255, 255, 255, 0, MMS3_FILEPATH_TEX_HIGHSCHOOL, MMS3_FILEPATH_HEADERLESS_HIGHSCHOOL);
}

static void p_loadHighwayBack()
{
	if(!p_highwayBack) p_highwayBack = PLEX_loadTextureFromFileOrHeaderless(3840, 1640, 255, 255, 255, 255, 0, MMS3_FILEPATH_TEX_HIGHWAY, MMS3_FILEPATH_HEADERLESS_HIGHWAY);
}

static void p_loadMegadomeGarageBack()
{
	if(!p_megadomeGarageBack) p_megadomeGarageBack = PLEX_loadTextureFromFileOrHeaderless(3840, 1640, 255, 255, 255, 255, 0, MMS3_FILEPATH_TEX_MEGADOMEPARKING, MMS3_FILEPATH_HEADERLESS_MEGADOMEPARKING);
}

void MMS3_startSceneI(const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow)
{
	MMS3_clearBackTextures();
	p_loadHighSchoolBack();

	PLEX_startSpriteTheater(MMS_LANGUAGE_SETTING_HIGHSCHOOL, p_highschoolBack, 0, 0, 400, 100, 255, 255, 255, fontPlate, label, bubble, arrow, PLEX_getGameTime());

	PLEX_changeSpriteTheaterMusic(MM_COMMON_THEMEID_PAMALEANA);

	MMS3_addTeenPamaleana(PLEX_WIDTHUNITMAX()/2, PLEX_HEIGHTUNITMAX()/2 + 2, false);

	p_addSpikeFuck(PLEX_WIDTHUNITMAX()/2 + 1.25, PLEX_HEIGHTUNITMAX()/2 + 2);

	MMS_narration(MMS3_LANGUAGE_SCENEI00);

	p_spikeFuckTalk(MMS3_LANGUAGE_SCENEI01);

	PLEX_changeActor(p_teenPamaleana, 1);

	MMS3_teenPamPamTalk(MMS3_LANGUAGE_SCENEI02);

	p_spikeFuckTalk(MMS3_LANGUAGE_SCENEI03);

	MMS3_teenPamPamTalkWait(MMS3_LANGUAGE_SCENEI04, 3000);

	p_spikeFuckTalk(MMS3_LANGUAGE_SCENEI05);

	MMS3_teenPamPamTalk(MMS3_LANGUAGE_SCENEI06);

	PLEX_changeActor(p_spikeFuck, 1);

	p_spikeFuckTalk(MMS3_LANGUAGE_SCENEI07);

	MMS3_teenPamPamTalk(MMS3_LANGUAGE_SCENEI08);

	PLEX_changeActor(p_spikeFuck, 2);

	p_spikeFuckTalk(MMS3_LANGUAGE_SCENEI09);

	PLEX_changeActor(p_teenPamaleana, 2);

	MMS3_teenPamPamTalk(MMS3_LANGUAGE_SCENEI10);

	PLEX_changeActor(p_teenPamaleana, 1);
	PLEX_changeActor(p_spikeFuck, 4);

	p_spikeFuckTalk(MMS3_LANGUAGE_SCENEI11);

	PLEX_changeActor(p_teenPamaleana, 3);
	PLEX_changeActor(p_spikeFuck, 0);

	MMS3_teenPamPamTalk(MMS3_LANGUAGE_SCENEI12);

	PLEX_changeActor(p_spikeFuck, 3);

	p_spikeFuckTalk(MMS3_LANGUAGE_SCENEI13);

	PLEX_changeActor(p_teenPamaleana, 4);
	PLEX_changeActor(p_spikeFuck, 0);

	MMS3_teenPamPamTalk(MMS3_LANGUAGE_SCENEI14);

	PLEX_changeActor(p_teenPamaleana, 1);

	p_spikeFuckTalk(MMS3_LANGUAGE_SCENEI15);

	MMS_pamNarration(MMS3_LANGUAGE_SCENEI16);

	PLEX_changeActor(p_teenPamaleana, 3);

	MMS3_teenPamPamTalk(MMS3_LANGUAGE_SCENEI17);

	PLEX_changeActor(p_spikeFuck, 4);

	p_spikeFuckTalk(MMS3_LANGUAGE_SCENEI18);

	PLEX_changeActor(p_teenPamaleana, 5);
	PLEX_changeActor(p_spikeFuck, 0);

	MMS3_teenPamPamTalk(MMS3_LANGUAGE_SCENEI19);

	PLEX_changeActor(p_teenPamaleana, 1);

	p_spikeFuckTalk(MMS3_LANGUAGE_SCENEI20);

	PLEX_changeActor(p_teenPamaleana, 3);

	MMS3_teenPamPamTalk(MMS3_LANGUAGE_SCENEI21);

	PLEX_changeActor(p_teenPamaleana, 1);
	PLEX_changeActor(p_spikeFuck, 0);

	p_spikeFuckTalk(MMS3_LANGUAGE_SCENEI22);

	PLEX_changeActor(p_teenPamaleana, 3);

	MMS3_teenPamPamTalk(MMS3_LANGUAGE_SCENEI23);

	PLEX_changeActor(p_teenPamaleana, 4);
	PLEX_changeActor(p_spikeFuck, 5);

	p_spikeFuckTalk(MMS3_LANGUAGE_SCENEI24);

	PLEX_changeActor(p_teenPamaleana, 6);
	PLEX_changeActor(p_spikeFuck, 0);

	MMS3_teenPamPamTalk(MMS3_LANGUAGE_SCENEI25);

	PLEX_changeActor(p_teenPamaleana, 1);
	PLEX_changeActor(p_spikeFuck, 6);

	p_spikeFuckTalk(MMS3_LANGUAGE_SCENEI26);

	PLEX_changeActor(p_teenPamaleana, 7);

	MMS3_teenPamPamTalk(MMS3_LANGUAGE_SCENEI27);

	PLEX_changeActor(p_teenPamaleana, 1);

	p_spikeFuckTalk(MMS3_LANGUAGE_SCENEI28);

	PLEX_changeActor(p_teenPamaleana, 7);

	MMS3_teenPamPamTalk(MMS3_LANGUAGE_SCENEI29);

	PLEX_changeActor(p_teenPamaleana, 1);

	p_spikeFuckTalk(MMS3_LANGUAGE_SCENEI30);

	PLEX_changeActor(p_teenPamaleana, 8);

	MMS3_teenPamPamTalk(MMS3_LANGUAGE_SCENEI31);

	PLEX_changeActor(p_spikeFuck, 1);

	p_spikeFuckTalk(MMS3_LANGUAGE_SCENEI32);
}

void MMS3_startSceneJ(const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow)
{
	MMS3_clearBackTextures();
	p_loadHighwayBack();

	PLEX_startSpriteTheater(MMS_LANGUAGE_SETTING_HIGHHWAY, p_highwayBack, 0, 0, 400, 100, 255, 255, 255, fontPlate, label, bubble, arrow, PLEX_getGameTime());

	PLEX_changeSpriteTheaterMusic(MM_COMMON_THEMEID_DAYTODAY);

	// these must stay in order
	p_addCarBack(PLEX_WIDTHUNITMAX()/2 - 4, PLEX_HEIGHTUNITMAX() * 0.75 + 1);
	MMS3_addStephinaCodelli(PLEX_WIDTHUNITMAX()/2 - 2.75, PLEX_HEIGHTUNITMAX() * 0.75 + 1, false);
	p_addCarFrontAndTraffic(PLEX_WIDTHUNITMAX()/2 - 4, PLEX_HEIGHTUNITMAX() * 0.75 + 1);
	//

	MMS3_stephinaCodelliActorAnimationActionChange(12);

	MMS3_stephinaCodelliTalk(MMS3_LANGUAGE_SCENEJ00);

	MMS3_stephinaCodelliTalk(MMS3_LANGUAGE_SCENEJ01);

	PLEX_changeSpriteTheaterMusic(MM_COMMON_THEMEID_NEWSROOM);

	p_carFrontTalk(MMS3_LANGUAGE_SCENEJ02);

	MMS3_stephinaCodelliTalk(MMS3_LANGUAGE_SCENEJ03);

	p_carFrontTalk(MMS3_LANGUAGE_SCENEJ04);

	MMS3_stephinaCodelliTalk( MMS3_LANGUAGE_SCENEJ05);

	PLEX_changeSpriteTheaterMusic(MM_COMMON_THEMEID_COMEDY);

	p_carFrontTalk(MMS3_LANGUAGE_SCENEJ06);

	p_carFrontTalk(MMS3_LANGUAGE_SCENEJ07);

	p_carFrontTalk(MMS3_LANGUAGE_SCENEJ08);

	MMS3_stephinaCodelliTalk(MMS3_LANGUAGE_SCENEJ09);

	p_carFrontTalk(MMS3_LANGUAGE_SCENEJ10);

	p_carFrontTalk(MMS3_LANGUAGE_SCENEJ11);

	p_carFrontTalk(MMS3_LANGUAGE_SCENEJ12);

	p_carFrontTalk(MMS3_LANGUAGE_SCENEJ13);

	p_carFrontTalk(MMS3_LANGUAGE_SCENEJ14);

	p_carFrontTalk(MMS3_LANGUAGE_SCENEJ15);

	p_carFrontTalk(MMS3_LANGUAGE_SCENEJ16);

	p_carFrontTalk(MMS3_LANGUAGE_SCENEJ17);

	p_carFrontTalk(MMS3_LANGUAGE_SCENEJ18);

	p_carFrontTalk(MMS3_LANGUAGE_SCENEJ19);

	p_carFrontTalk(MMS3_LANGUAGE_SCENEJ20);

	p_carFrontTalk(MMS3_LANGUAGE_SCENEJ21);

	p_carFrontTalk(MMS3_LANGUAGE_SCENEJ22);

	p_carFrontTalk(MMS3_LANGUAGE_SCENEJ23);

	p_carFrontTalk(MMS3_LANGUAGE_SCENEJ24);

	p_carFrontTalk(MMS3_LANGUAGE_SCENEJ25);

	p_carFrontTalk(MMS3_LANGUAGE_SCENEJ26);

	p_carFrontTalk(MMS3_LANGUAGE_SCENEJ27);

	PLEX_changeActor(p_stephinaCarFront, 1);
	MMS3_stephinaCodelliActorAnimationActionChange(13);
	PLEX_changeActor(p_biker, 1);

	for(size_t ze = 0; ze < 6; ++ze) PLEX_changeActor(p_traffic[ze], 1);

	PLEX_playSpriteTheaterSoundEffect((size_t)MM_COMMON_SOUNDEFFECT_SHOCK);
	PLEX_stopSpriteTheaterMusic();

	p_carFrontTalk(MMS3_LANGUAGE_SCENEJ28);

	PLEX_changeActor(p_stephinaCarFront, 2);
	PLEX_changeActor(p_biker, 2);

	MMS3_stephinaCodelliTalk(MMS3_LANGUAGE_SCENEJ29);
}

void MMS3_startSceneK(const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow)
{
	MMS3_clearBackTextures();
	p_loadMegadomeGarageBack();
	MMS3_loadCodellisLivingRoomBack();

	PLEX_startSpriteTheater(MMS_LANGUAGE_SETTING_MEGADOMEPARKINGGARAGE, p_megadomeGarageBack, 0, 0, 400, 100, 255, 255, 255, fontPlate, label, bubble, arrow, PLEX_getGameTime());

	MM_COMMON_punkThemeVolume(0.5);

	PLEX_changeSpriteTheaterMusic(MM_COMMON_THEMEID_PUNK);

	p_addSpikeFuck(PLEX_WIDTHUNITMAX()/2 - 2.625, PLEX_HEIGHTUNITMAX()/2 + 2);

	p_addThugOne(PLEX_WIDTHUNITMAX()/2 + 0.625, PLEX_HEIGHTUNITMAX()/2 - 1);
	p_addThugTwo(PLEX_WIDTHUNITMAX()/2 - 0.625, PLEX_HEIGHTUNITMAX()/2 + 2);

	MMS3_addTeenPamaleana(PLEX_WIDTHUNITMAX()/2 + 0.625, PLEX_HEIGHTUNITMAX()/2 + 2, false);

	p_addBlackVan(PLEX_WIDTHUNITMAX()/2 + 4, PLEX_HEIGHTUNITMAX()/2 - 2);

	MMS3_addPollockCodelli(PLEX_WIDTHUNITMAX()/2 - 2.625, PLEX_HEIGHTUNITMAX()/2 + 4, false, true);

	PLEX_changeActor(p_teenPamaleana, 9);
	PLEX_changeActor(p_spikeFuck, 7);

	MMS3_teenPamPamTalk(MMS3_LANGUAGE_SCENEK00);

	PLEX_unhideActor(p_blackVan);

	p_spikeFuckTalk(MMS3_LANGUAGE_SCENEK01);

	PLEX_changeActor(p_blackVan, 1);
	PLEX_changeActor(p_teenPamaleana, 10);
	PLEX_changeActor(p_spikeFuck, 8);
	PLEX_unhideActor(p_thug1);
	PLEX_unhideActor(p_thug2);

	PLEX_changeSpriteTheaterMusic(MM_COMMON_THEMEID_PANIC);

	PLEX_playSpriteTheaterSoundEffect(MM_COMMON_SOUNDEFFECT_CRUELTWIST);

	p_spikeFuckTalk(MMS3_LANGUAGE_SCENEK02);

	MMS3_hideTeenPamPam();
	PLEX_hideActor(p_thug1);

	PLEX_changeActor(p_blackVan, 2);
	PLEX_changeActor(p_spikeFuck, 9);

	p_spikeFuckTalk(MMS3_LANGUAGE_SCENEK03);

	p_thugTalk(MMS3_LANGUAGE_SCENEK04);

	PLEX_hideActor(p_blackVan);
	PLEX_hideActor(p_thug2);

	PLEX_changeActor(p_spikeFuck, 10);

	p_spikeFuckTalk(MMS3_LANGUAGE_SCENEK05);

	PLEX_changeActor(p_spikeFuck, 11);

	PLEX_changeSpriteTheaterMusic(MM_COMMON_THEMEID_SUSPENSE);

	p_spikeFuckTalk(MMS3_LANGUAGE_SCENEK06);

	PLEX_changeActor(p_spikeFuck, 12);
	MMS3_pollockCodelliActorAnimationActionChange(8);

	p_spikeFuckTalk(MMS3_LANGUAGE_SCENEK07);

	PLEX_hideActor(p_spikeFuck);
	MMS3_pollockUnhideActor();
	MMS3_setBackgroundCodellisLivingRoom();

	MMS3_pollockTalk(MMS3_LANGUAGE_SCENEK08);

	PLEX_unhideActor(p_spikeFuck);
	MMS3_pollockHideActor();
	PLEX_changeSpriteTheaterBackground(p_megadomeGarageBack, MMS_LANGUAGE_SETTING_MEGADOMEPARKINGGARAGE);

	p_spikeFuckTalk(MMS3_LANGUAGE_SCENEK09);

	PLEX_hideActor(p_spikeFuck);
	MMS3_pollockUnhideActor();
	MMS3_setBackgroundCodellisLivingRoom();

	MMS3_pollockTalk(MMS3_LANGUAGE_SCENEK10);

	PLEX_unhideActor(p_spikeFuck);
	MMS3_pollockHideActor();
	PLEX_changeSpriteTheaterBackground(p_megadomeGarageBack, MMS_LANGUAGE_SETTING_MEGADOMEPARKINGGARAGE);

	p_spikeFuckTalk(MMS3_LANGUAGE_SCENEK11);

	PLEX_hideActor(p_spikeFuck);
	MMS3_pollockUnhideActor();
	MMS3_setBackgroundCodellisLivingRoom();

	MMS3_pollockTalk(MMS3_LANGUAGE_SCENEK12);

	PLEX_unhideActor(p_spikeFuck);
	MMS3_pollockHideActor();
	PLEX_changeSpriteTheaterBackground(p_megadomeGarageBack, MMS_LANGUAGE_SETTING_MEGADOMEPARKINGGARAGE);

	p_spikeFuckTalk(MMS3_LANGUAGE_SCENEK13);

	PLEX_hideActor(p_spikeFuck);
	MMS3_pollockUnhideActor();
	MMS3_setBackgroundCodellisLivingRoom();

	MMS3_pollockTalk(MMS3_LANGUAGE_SCENEK14);

	PLEX_unhideActor(p_spikeFuck);
	MMS3_pollockHideActor();
	PLEX_changeSpriteTheaterBackground(p_megadomeGarageBack, MMS_LANGUAGE_SETTING_MEGADOMEPARKINGGARAGE);

	p_spikeFuckTalk(MMS3_LANGUAGE_SCENEK15);

	PLEX_hideActor(p_spikeFuck);
	MMS3_pollockUnhideActor();
	MMS3_setBackgroundCodellisLivingRoom();

	MMS3_pollockTalk(MMS3_LANGUAGE_SCENEK16);
}

void MMS3_addTeenPamaleana(const double x, const double y, const bool hidden)
{
	p_teenPamaleana = PLEX_createActor(p_teenPamaleanaSprite, 0, PLEX_convRect(PLEX_convPoint(x, y), PLEX_convDimens(2, 4)), hidden);
}

void MMS3_teenPamPamTalkWait(const char* const message, const uint64_t wait)
{
	PLEX_addSpriteTheaterSlide(29, 180, 255, message, p_teenPamaleana, wait, false);
}

void MMS3_teenPamPamTalk(const char* const message)
{
	MMS3_teenPamPamTalkWait(message, 0);
}

void MMS3_teenPamPamActorAnimationActionChange(const size_t index)
{
	PLEX_changeActor(p_teenPamaleana, index);
}

void MMS3_hideTeenPamPam()
{
	PLEX_hideActor(p_teenPamaleana);
}

void MMS3_unhideTeenPamPam()
{
	PLEX_unhideActor(p_teenPamaleana);
}

void MMS3_moveTeenPamPam(const double x, const double y)
{
	PLEX_moveActor(p_teenPamaleana, x, y);
}

void MMS3_resizeTeenPamPam(const double w, const double h)
{
	PLEX_actorResizeActionChange(p_teenPamaleana, w, h);
}

void MMS3_createSection3(const size_t chapter3SpriteTex)
{
	p_createTeenPamaleana(chapter3SpriteTex);
	p_createSpikeFuck(chapter3SpriteTex);
	p_createCarBack(chapter3SpriteTex);
	p_createCarFront(chapter3SpriteTex);
	p_createTraffic(chapter3SpriteTex);
	p_createBlackVan(chapter3SpriteTex);
	p_createThugOne(chapter3SpriteTex);
	p_createThugTwo(chapter3SpriteTex);
}

void MMS3_freeSection3()
{
	if(p_highschoolBack) PLEX_destroyTexture(p_highschoolBack);
	if(p_highwayBack) PLEX_destroyTexture(p_highwayBack);
	if(p_megadomeGarageBack) PLEX_destroyTexture(p_megadomeGarageBack);

	p_highschoolBack = 0;
	p_highwayBack = 0;
	p_megadomeGarageBack = 0;
}

void MMS3_finalFreeSection3()
{
	PLEX_destroySprite(&p_teenPamaleanaSprite);
	PLEX_destroySprite(&p_spikeFuckSprite);
	PLEX_destroySprite(&p_stephinaCarBackSprite);
	PLEX_destroySprite(&p_stephinaCarFrontSprite);
	PLEX_destroySprite(&p_bikerSprite);

	for(size_t ze = 0; ze < 4; ++ze)
	{
		PLEX_SPRITE* trafficSprite = p_trafficSprite[ze];

		PLEX_destroySprite(&trafficSprite);

		p_trafficSprite[ze] = NULL;
	}

	PLEX_destroySprite(&p_blackVanSprite);
	PLEX_destroySprite(&p_thug1Sprite);
	PLEX_destroySprite(&p_thug2Sprite);
}
