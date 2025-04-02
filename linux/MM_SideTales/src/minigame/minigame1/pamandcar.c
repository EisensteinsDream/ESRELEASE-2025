#include "minigame/minigame1/function.h"

static PLEX_SPRITE* p_pamaleanaSprite = NULL;

static PLEX_SPRITE* p_carBack = NULL;
static PLEX_SPRITE* p_carSeat = NULL;
static PLEX_SPRITE* p_carWindshield = NULL;
static PLEX_SPRITE* p_carWingLeft = NULL;
static PLEX_SPRITE* p_carWingRight = NULL;

static size_t p_windshieldAniIndex = 0;

static size_t p_pamAniIndex = 0;

// CAR BACK

static void p_createCarBackSprite(const PLEX_ANIMATION_PLATE carPlate, const uint64_t time)
{
	PLEX_ANIMATION* carBackHealthyAnim = NULL;
	PLEX_ANIMATION* carBackBroken1Anim = NULL;
	PLEX_ANIMATION* carBackBroken2Anim = NULL;
	PLEX_ANIMATION* carBackBroken3Anim = NULL;

	PLEX_ANIMATION* carBackHealthyBackingAnim = NULL;
	PLEX_ANIMATION* carBackBroken1BackingAnim = NULL;
	PLEX_ANIMATION* carBackBroken2BackingAnim = NULL;
	PLEX_ANIMATION* carBackBroken3BackingAnim = NULL;

	p_carBack = PLEX_genSprite(&carPlate);

	PLEX_addAnimation(p_carBack, 200, time);

	carBackHealthyAnim = PLEX_getAnimation(0, p_carBack);

	PLEX_addAnimationFrame(0, carBackHealthyAnim);
	PLEX_addAnimationFrame(5, carBackHealthyAnim);
	PLEX_addAnimationFrame(10, carBackHealthyAnim);
	PLEX_addAnimationFrame(15, carBackHealthyAnim);
	PLEX_addAnimationFrame(20, carBackHealthyAnim);

	PLEX_addAnimation(p_carBack, 200, time);

	carBackBroken1Anim = PLEX_getAnimation(1, p_carBack);

	PLEX_addAnimationFrame(25, carBackBroken1Anim);
	PLEX_addAnimationFrame(30, carBackBroken1Anim);
	PLEX_addAnimationFrame(35, carBackBroken1Anim);
	PLEX_addAnimationFrame(40, carBackBroken1Anim);
	PLEX_addAnimationFrame(45, carBackBroken1Anim);

	PLEX_addAnimation(p_carBack, 200, time);

	carBackBroken2Anim = PLEX_getAnimation(2, p_carBack);

	PLEX_addAnimationFrame(26, carBackBroken2Anim);
	PLEX_addAnimationFrame(31, carBackBroken2Anim);
	PLEX_addAnimationFrame(36, carBackBroken2Anim);
	PLEX_addAnimationFrame(41, carBackBroken2Anim);
	PLEX_addAnimationFrame(46, carBackBroken2Anim);

	PLEX_addAnimation(p_carBack, 200, time);

	carBackBroken3Anim = PLEX_getAnimation(3, p_carBack);

	PLEX_addAnimationFrame(27, carBackBroken3Anim);
	PLEX_addAnimationFrame(32, carBackBroken3Anim);
	PLEX_addAnimationFrame(37, carBackBroken3Anim);
	PLEX_addAnimationFrame(42, carBackBroken3Anim);
	PLEX_addAnimationFrame(47, carBackBroken3Anim);

	PLEX_addAnimation(p_carBack, 200, time);

	carBackHealthyBackingAnim = PLEX_getAnimation(4, p_carBack);

	PLEX_addAnimationFrame(20, carBackHealthyBackingAnim);

	PLEX_addAnimation(p_carBack, 200, time);

	carBackBroken1BackingAnim = PLEX_getAnimation(5, p_carBack);

	PLEX_addAnimationFrame(45, carBackBroken1BackingAnim);

	PLEX_addAnimation(p_carBack, 200, time);

	carBackBroken2BackingAnim = PLEX_getAnimation(6, p_carBack);

	PLEX_addAnimationFrame(46, carBackBroken2BackingAnim);

	PLEX_addAnimation(p_carBack, 200, time);

	carBackBroken3BackingAnim = PLEX_getAnimation(7, p_carBack);

	PLEX_addAnimationFrame(47, carBackBroken3BackingAnim);

	PLEX_startSprite(time, p_carBack);
}

static void p_createCarSeatSprite(const PLEX_ANIMATION_PLATE carPlate, const uint64_t time)
{
	PLEX_ANIMATION* carSeatHealthyAnim = NULL;
	PLEX_ANIMATION* carSeatBroken1Anim = NULL;
	PLEX_ANIMATION* carSeatBroken2Anim = NULL;
	PLEX_ANIMATION* carSeatBroken3Anim = NULL;

	p_carSeat = PLEX_genSprite(&carPlate);

	PLEX_addAnimation(p_carSeat, 800, time);

	carSeatHealthyAnim = PLEX_getAnimation(0, p_carSeat);

	PLEX_addAnimationFrame(1, carSeatHealthyAnim);

	PLEX_addAnimation(p_carSeat, 800, time);

	carSeatBroken1Anim = PLEX_getAnimation(1, p_carSeat);

	PLEX_addAnimationFrame(6, carSeatBroken1Anim);

	PLEX_addAnimation(p_carSeat, 800, time);

	carSeatBroken2Anim = PLEX_getAnimation(2, p_carSeat);

	PLEX_addAnimationFrame(11, carSeatBroken2Anim);

	PLEX_addAnimation(p_carSeat, 800, time);

	carSeatBroken3Anim = PLEX_getAnimation(3, p_carSeat);

	PLEX_addAnimationFrame(16, carSeatBroken3Anim);
}

static void p_createCarWindshieldSprite(const PLEX_ANIMATION_PLATE carPlate, const uint64_t time)
{
	PLEX_ANIMATION* carWindshieldHealthyAnim = NULL;
	PLEX_ANIMATION* carWindshieldBroken1Anim = NULL;
	PLEX_ANIMATION* carWindshieldBroken2Anim = NULL;
	PLEX_ANIMATION* carWindshieldBroken3Anim = NULL;

	p_carWindshield = PLEX_genSprite(&carPlate);

	PLEX_addAnimation(p_carWindshield, 800, time);

	carWindshieldHealthyAnim = PLEX_getAnimation(0, p_carWindshield);

	PLEX_addAnimationFrame(2, carWindshieldHealthyAnim);

	PLEX_addAnimation(p_carWindshield, 800, time);

	carWindshieldBroken1Anim = PLEX_getAnimation(1, p_carWindshield);

	PLEX_addAnimationFrame(7, carWindshieldBroken1Anim);

	PLEX_addAnimation(p_carWindshield, 800, time);

	carWindshieldBroken2Anim = PLEX_getAnimation(2, p_carWindshield);

	PLEX_addAnimationFrame(12, carWindshieldBroken2Anim);

	PLEX_addAnimation(p_carWindshield, 800, time);

	carWindshieldBroken3Anim = PLEX_getAnimation(3, p_carWindshield);

	PLEX_addAnimationFrame(17, carWindshieldBroken3Anim);
}

static void p_createCarWingLeftSprite(const PLEX_ANIMATION_PLATE carPlate, const uint64_t time)
{
	PLEX_ANIMATION* carWingLeftHealthyAnim = NULL;
	PLEX_ANIMATION* carWingLeftBroken1Anim = NULL;
	PLEX_ANIMATION* carWingLeftBroken2Anim = NULL;
	PLEX_ANIMATION* carWingLeftBroken3Anim = NULL;

	PLEX_ANIMATION* carWingLeftHealthyBackingAnim = NULL;
	PLEX_ANIMATION* carWingLeftBroken1BackingAnim = NULL;
	PLEX_ANIMATION* carWingLeftBroken2BackingAnim = NULL;
	PLEX_ANIMATION* carWingLeftBroken3BackingAnim = NULL;

	p_carWingLeft = PLEX_genSprite(&carPlate);

	PLEX_addAnimation(p_carWingLeft, 200, time);

	carWingLeftHealthyAnim = PLEX_getAnimation(0, p_carWingLeft);

	PLEX_addAnimationFrame(3, carWingLeftHealthyAnim);
	PLEX_addAnimationFrame(8, carWingLeftHealthyAnim);
	PLEX_addAnimationFrame(13, carWingLeftHealthyAnim);
	PLEX_addAnimationFrame(18, carWingLeftHealthyAnim);
	PLEX_addAnimationFrame(23, carWingLeftHealthyAnim);

	PLEX_addAnimation(p_carWingLeft, 200, time);

	carWingLeftBroken1Anim = PLEX_getAnimation(1, p_carWingLeft);

	PLEX_addAnimationFrame(50, carWingLeftBroken1Anim);
	PLEX_addAnimationFrame(55, carWingLeftBroken1Anim);
	PLEX_addAnimationFrame(60, carWingLeftBroken1Anim);
	PLEX_addAnimationFrame(65, carWingLeftBroken1Anim);
	PLEX_addAnimationFrame(70, carWingLeftBroken1Anim);

	PLEX_addAnimation(p_carWingLeft, 200, time);

	carWingLeftBroken2Anim = PLEX_getAnimation(2, p_carWingLeft);

	PLEX_addAnimationFrame(51, carWingLeftBroken2Anim);
	PLEX_addAnimationFrame(56, carWingLeftBroken2Anim);
	PLEX_addAnimationFrame(61, carWingLeftBroken2Anim);
	PLEX_addAnimationFrame(66, carWingLeftBroken2Anim);
	PLEX_addAnimationFrame(71, carWingLeftBroken2Anim);

	PLEX_addAnimation(p_carWingLeft, 200, time);

	carWingLeftBroken3Anim = PLEX_getAnimation(3, p_carWingLeft);

	PLEX_addAnimationFrame(52, carWingLeftBroken3Anim);
	PLEX_addAnimationFrame(57, carWingLeftBroken3Anim);
	PLEX_addAnimationFrame(62, carWingLeftBroken3Anim);
	PLEX_addAnimationFrame(67, carWingLeftBroken3Anim);
	PLEX_addAnimationFrame(72, carWingLeftBroken3Anim);

	PLEX_addAnimation(p_carWingLeft, 200, time);

	carWingLeftHealthyBackingAnim = PLEX_getAnimation(4, p_carWingLeft);

	PLEX_addAnimationFrame(23, carWingLeftHealthyBackingAnim);

	PLEX_addAnimation(p_carWingLeft, 200, time);

	carWingLeftBroken1BackingAnim = PLEX_getAnimation(5, p_carWingLeft);

	PLEX_addAnimationFrame(70, carWingLeftBroken1BackingAnim);

	PLEX_addAnimation(p_carWingLeft, 200, time);

	carWingLeftBroken2BackingAnim = PLEX_getAnimation(6, p_carWingLeft);

	PLEX_addAnimationFrame(71, carWingLeftBroken2BackingAnim);

	PLEX_addAnimation(p_carWingLeft, 200, time);

	carWingLeftBroken3BackingAnim = PLEX_getAnimation(7, p_carWingLeft);

	PLEX_addAnimationFrame(72, carWingLeftBroken3BackingAnim);

	PLEX_startSprite(time, p_carWingLeft);
}

static void p_createCarWingRightSprite(const PLEX_ANIMATION_PLATE carPlate, const uint64_t time)
{
	PLEX_ANIMATION* carWingRightHealthyAnim = NULL;
	PLEX_ANIMATION* carWingRightBroken1Anim = NULL;
	PLEX_ANIMATION* carWingRightBroken2Anim = NULL;
	PLEX_ANIMATION* carWingRightBroken3Anim = NULL;

	PLEX_ANIMATION* carWingRightHealthyBackingAnim = NULL;
	PLEX_ANIMATION* carWingRightBroken1BackingAnim = NULL;
	PLEX_ANIMATION* carWingRightBroken2BackingAnim = NULL;
	PLEX_ANIMATION* carWingRightBroken3BackingAnim = NULL;

	p_carWingRight = PLEX_genSprite(&carPlate);

	PLEX_addAnimation(p_carWingRight, 200, time);

	carWingRightHealthyAnim = PLEX_getAnimation(0, p_carWingRight);

	PLEX_addAnimationFrame(4, carWingRightHealthyAnim);
	PLEX_addAnimationFrame(9, carWingRightHealthyAnim);
	PLEX_addAnimationFrame(14, carWingRightHealthyAnim);
	PLEX_addAnimationFrame(19, carWingRightHealthyAnim);
	PLEX_addAnimationFrame(24, carWingRightHealthyAnim);

	PLEX_addAnimation(p_carWingRight, 200, time);

	carWingRightBroken1Anim = PLEX_getAnimation(1, p_carWingRight);

	PLEX_addAnimationFrame(28, carWingRightBroken1Anim);
	PLEX_addAnimationFrame(33, carWingRightBroken1Anim);
	PLEX_addAnimationFrame(38, carWingRightBroken1Anim);
	PLEX_addAnimationFrame(43, carWingRightBroken1Anim);
	PLEX_addAnimationFrame(48, carWingRightBroken1Anim);

	PLEX_addAnimation(p_carWingRight, 200, time);

	carWingRightBroken2Anim = PLEX_getAnimation(2, p_carWingRight);

	PLEX_addAnimationFrame(29, carWingRightBroken2Anim);
	PLEX_addAnimationFrame(34, carWingRightBroken2Anim);
	PLEX_addAnimationFrame(39, carWingRightBroken2Anim);
	PLEX_addAnimationFrame(44, carWingRightBroken2Anim);
	PLEX_addAnimationFrame(49, carWingRightBroken2Anim);

	PLEX_addAnimation(p_carWingRight, 200, time);

	carWingRightBroken3Anim = PLEX_getAnimation(3, p_carWingRight);

	PLEX_addAnimationFrame(53, carWingRightBroken3Anim);
	PLEX_addAnimationFrame(58, carWingRightBroken3Anim);
	PLEX_addAnimationFrame(63, carWingRightBroken3Anim);
	PLEX_addAnimationFrame(68, carWingRightBroken3Anim);
	PLEX_addAnimationFrame(73, carWingRightBroken3Anim);

	PLEX_addAnimation(p_carWingRight, 200, time);

	carWingRightHealthyBackingAnim = PLEX_getAnimation(4, p_carWingRight);

	PLEX_addAnimationFrame(24, carWingRightHealthyBackingAnim);

	PLEX_addAnimation(p_carWingRight, 200, time);

	carWingRightBroken1BackingAnim = PLEX_getAnimation(5, p_carWingRight);

	PLEX_addAnimationFrame(48, carWingRightBroken1BackingAnim);

	PLEX_addAnimation(p_carWingRight, 200, time);

	carWingRightBroken2BackingAnim = PLEX_getAnimation(6, p_carWingRight);

	PLEX_addAnimationFrame(49, carWingRightBroken2BackingAnim);

	PLEX_addAnimation(p_carWingRight, 200, time);

	carWingRightBroken3BackingAnim = PLEX_getAnimation(7, p_carWingRight);

	PLEX_addAnimationFrame(73, carWingRightBroken3BackingAnim);

	PLEX_startSprite(time, p_carWingRight);
}

static void p_updateCarBackSprites(const size_t backing, const PLEX_RECT carDrawArea, const uint64_t time)
{
	const double carWingLeftHealth = MMS1_carWingLeftHealth();
	const double carWingRightHealth = MMS1_carWingRightHealth();
	const double backHealth = MMS1_carBackHealth();

	size_t carWingLeftAniIndex = carWingLeftHealth ? (1 - carWingLeftHealth)/0.25 : 3;
	size_t carWingRightAniIndex = carWingRightHealth ? (1 - carWingRightHealth)/0.25 : 3;

	size_t backAniIndex = backHealth ? (1 - backHealth)/0.25 : 3;

	PLEX_changeSpriteCycleSpeed(carWingLeftAniIndex + backing, MMS1_calcAnimationCycle(MMS1_FASTESTCYCLE_CARWINGANIMATION, MMS1_SLOWESTCYCLE_CARWINGANIMATION), p_carWingLeft, time);
	PLEX_changeSpriteCycleSpeed(carWingRightAniIndex + backing, MMS1_calcAnimationCycle(MMS1_FASTESTCYCLE_CARWINGANIMATION, MMS1_SLOWESTCYCLE_CARWINGANIMATION), p_carWingRight, time);
	PLEX_changeSpriteCycleSpeed(backAniIndex + backing, MMS1_calcAnimationCycle(MMS1_FASTESTCYCLE_CARBACKANIMATION, MMS1_SLOWESTCYCLE_CARBACKANIMATION), p_carBack, time);

	PLEX_drawSprite(MMS1_calcOverroadLayer(carDrawArea.origin.y, carDrawArea.dimens.h, MMS1_SPRITELAYER_WING), carWingLeftAniIndex + backing, PLEX_UNIT(carDrawArea.origin.x), PLEX_UNIT(carDrawArea.origin.y), PLEX_UNIT(carDrawArea.dimens.w), PLEX_UNIT(carDrawArea.dimens.h), p_carWingLeft, true, time);

	PLEX_drawSprite(MMS1_calcOverroadLayer(carDrawArea.origin.y, carDrawArea.dimens.h, MMS1_SPRITELAYER_WING), carWingRightAniIndex + backing, PLEX_UNIT(carDrawArea.origin.x), PLEX_UNIT(carDrawArea.origin.y), PLEX_UNIT(carDrawArea.dimens.w), PLEX_UNIT(carDrawArea.dimens.h), p_carWingRight, true, time);

	PLEX_drawSprite(MMS1_calcOverroadLayer(carDrawArea.origin.y, carDrawArea.dimens.h, MMS1_SPRITELAYER_BACK), backAniIndex + backing, PLEX_UNIT(carDrawArea.origin.x), PLEX_UNIT(carDrawArea.origin.y), PLEX_UNIT(carDrawArea.dimens.w), PLEX_UNIT(carDrawArea.dimens.h), p_carBack, true, time);
}

static void p_updateCarFrontSprites(const PLEX_RECT carDrawArea, const uint64_t time)
{
	const double carSeatHealth = MMS1_carSeatHealth();
	const double windshieldHealth = MMS1_windshieldHealth();

	size_t carSeatAniIndex = carSeatHealth ? (1 - carSeatHealth)/0.25 : 3;

	p_windshieldAniIndex = windshieldHealth ? (1 - windshieldHealth)/0.25 : 3;

	PLEX_drawSprite(MMS1_calcOverroadLayer(carDrawArea.origin.y, carDrawArea.dimens.h, MMS1_SPRITELAYER_FRONT), carSeatAniIndex, PLEX_UNIT(carDrawArea.origin.x), PLEX_UNIT(carDrawArea.origin.y), PLEX_UNIT(carDrawArea.dimens.w), PLEX_UNIT(carDrawArea.dimens.h), p_carSeat, true, time);
	PLEX_drawSprite(MMS1_calcOverroadLayer(carDrawArea.origin.y, carDrawArea.dimens.h, MMS1_SPRITELAYER_WINDSHIELD), p_windshieldAniIndex, PLEX_UNIT(carDrawArea.origin.x), PLEX_UNIT(carDrawArea.origin.y), PLEX_UNIT(carDrawArea.dimens.w), PLEX_UNIT(carDrawArea.dimens.h), p_carWindshield, true, time);
}

static void p_destroyCarSprites()
{
	if(p_carBack != NULL) PLEX_destroySprite(&p_carBack);
	if(p_carSeat != NULL) PLEX_destroySprite(&p_carSeat);
	if(p_carWindshield != NULL) PLEX_destroySprite(&p_carWindshield);
	if(p_carWingLeft != NULL) PLEX_destroySprite(&p_carWingLeft);
	if(p_carWingRight != NULL) PLEX_destroySprite(&p_carWingRight);
}

// PAMALEANA SPRITES

static void p_createPamaleanaSprite(const size_t pamaleanaSpriteTex, const uint64_t time)
{
	PLEX_ANIMATION* pamaleanaStoppedAnim = NULL;

	PLEX_ANIMATION* pamaleanaDriftLeft = NULL;
	PLEX_ANIMATION* pamaleanaDriftRight = NULL;
	PLEX_ANIMATION* pamaleanaDriftForward = NULL;
	PLEX_ANIMATION* pamaleanaDriftBackward = NULL;

	PLEX_ANIMATION* pamaleanaAccelForward = NULL;

	PLEX_ANIMATION* pamaleanaCrash = NULL;

	PLEX_ANIMATION_PLATE pamaleanaPlate = PLEX_createAnimationPlate(0.0625, 0.125, pamaleanaSpriteTex);

	p_pamaleanaSprite = PLEX_genSprite(&pamaleanaPlate);

	PLEX_addAnimation(p_pamaleanaSprite, 800, time);

	pamaleanaStoppedAnim = PLEX_getAnimation(0, p_pamaleanaSprite);

	PLEX_addAnimationFrame(33, pamaleanaStoppedAnim);

	PLEX_addAnimation(p_pamaleanaSprite, 1000, time);

	pamaleanaDriftLeft = PLEX_getAnimation(1, p_pamaleanaSprite);

	PLEX_addAnimationFrame(37, pamaleanaDriftLeft);
	PLEX_addAnimationFrame(38, pamaleanaDriftLeft);
	PLEX_addAnimationFrame(39, pamaleanaDriftLeft);
	PLEX_addAnimationFrame(38, pamaleanaDriftLeft);

	PLEX_addAnimation(p_pamaleanaSprite, 1000, time);

	pamaleanaDriftRight = PLEX_getAnimation(2, p_pamaleanaSprite);

	PLEX_addAnimationFrame(34, pamaleanaDriftRight);
	PLEX_addAnimationFrame(35, pamaleanaDriftRight);
	PLEX_addAnimationFrame(36, pamaleanaDriftRight);
	PLEX_addAnimationFrame(35, pamaleanaDriftRight);

	PLEX_addAnimation(p_pamaleanaSprite, 1000, time);

	pamaleanaDriftForward = PLEX_getAnimation(3, p_pamaleanaSprite);

	PLEX_addAnimationFrame(40, pamaleanaDriftForward);
	PLEX_addAnimationFrame(41, pamaleanaDriftForward);
	PLEX_addAnimationFrame(42, pamaleanaDriftForward);
	PLEX_addAnimationFrame(41, pamaleanaDriftForward);

	PLEX_addAnimation(p_pamaleanaSprite, 1000, time);

	pamaleanaDriftBackward = PLEX_getAnimation(4, p_pamaleanaSprite);

	PLEX_addAnimationFrame(43, pamaleanaDriftBackward);
	PLEX_addAnimationFrame(44, pamaleanaDriftBackward);
	PLEX_addAnimationFrame(45, pamaleanaDriftBackward);
	PLEX_addAnimationFrame(44, pamaleanaDriftBackward);

	PLEX_addAnimation(p_pamaleanaSprite, 250, time);

	pamaleanaAccelForward = PLEX_getAnimation(5, p_pamaleanaSprite);

	PLEX_addAnimationFrame(40, pamaleanaAccelForward);
	PLEX_addAnimationFrame(46, pamaleanaAccelForward);
	PLEX_addAnimationFrame(47, pamaleanaAccelForward);
	PLEX_addAnimationFrame(46, pamaleanaAccelForward);

	PLEX_addAnimation(p_pamaleanaSprite, 500, time);

	pamaleanaCrash = PLEX_getAnimation(6, p_pamaleanaSprite);

	PLEX_addAnimationFrame(48, pamaleanaCrash);
	PLEX_addAnimationFrame(49, pamaleanaCrash);
	PLEX_addAnimationFrame(48, pamaleanaCrash);

	PLEX_startSprite(time, p_pamaleanaSprite);
}

static void p_updatePamaleanaSprite(const double pamLayer, const PLEX_RECT carDrawArea, const uint64_t time)
{
	const PLEX_RECT playerRegion = MMS1_playerRegion();

	PLEX_drawSprite(pamLayer, p_pamAniIndex, PLEX_UNIT(playerRegion.origin.x), PLEX_UNIT(playerRegion.origin.y), PLEX_UNIT(playerRegion.dimens.w), PLEX_UNIT(playerRegion.dimens.h), p_pamaleanaSprite, true, time);
}

static void p_destroyPamaleanaSprite()
{
	if(p_pamaleanaSprite != NULL) PLEX_destroySprite(&p_pamaleanaSprite);
}

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

void MMS1_updatePamaleanaCycleSpeed(const uint64_t time)
{
	PLEX_changeSpriteCycleSpeed(p_pamAniIndex, MMS1_calcAnimationCycle(MMS1_FASTESTCYCLE_PAMALEANAANIMATION, MMS1_SLOWESTCYCLE_PAMALEANAANIMATION), p_pamaleanaSprite, time);
}

void MMS1_updatePamaleanaCrashCycle(const uint64_t crashCycle)
{
	if(!crashCycle || p_pamAniIndex == 6) return;

	if(crashCycle < PLEX_spriteCycleLen(6, p_pamaleanaSprite)) p_pamAniIndex = 6;
}

void MMS1_startCarSprites(const uint64_t time)
{
	PLEX_startSprite(time, p_carBack);
	PLEX_startSprite(time, p_carSeat);
	PLEX_startSprite(time, p_carWindshield);
	PLEX_startSprite(time, p_carWingLeft);
	PLEX_startSprite(time, p_carWingRight);
}

void MMS1_stopCarSprites()
{
	PLEX_stopSprite(p_carBack);
	PLEX_stopSprite(p_carSeat);
	PLEX_stopSprite(p_carWindshield);
	PLEX_stopSprite(p_carWingLeft);
	PLEX_stopSprite(p_carWingRight);
}

bool MMS1_beginPamAndCar(const size_t chapter1SpriteTex, const size_t pamaleanaSpriteTex, const uint64_t time)
{
	PLEX_ANIMATION_PLATE carPlate = PLEX_createAnimationPlate(0.2, 0.0334, chapter1SpriteTex);

	p_createPamaleanaSprite(pamaleanaSpriteTex, time);

	p_createCarWingLeftSprite(carPlate, time);
	p_createCarWingRightSprite(carPlate, time);
	p_createCarBackSprite(carPlate, time);
	p_createCarSeatSprite(carPlate, time);
	p_createCarWindshieldSprite(carPlate, time);

	p_pamAniIndex = 0;

	return true;
}

bool MMS1_updatePamAndCar(const size_t backing, const uint64_t time)
{
	const PLEX_RECT carDrawArea = MMS1_carDrawArea();

	const size_t drawLayer = MMS1_calcOverroadLayer(carDrawArea.origin.y, carDrawArea.dimens.h, MMS1_SPRITELAYER_PAMALEANA);

	p_updateCarBackSprites(backing, carDrawArea, time);
	p_updatePamaleanaSprite(drawLayer, carDrawArea, time);
	p_updateCarFrontSprites(carDrawArea, time);

	return true;
}

void MMS1_endPamAndCar()
{
	p_destroyPamaleanaSprite();

	p_destroyCarSprites();
}

void MMS1_setPamAniIndex(const size_t index){ p_pamAniIndex = index; }

size_t MMS1_windshieldAniIndex(){ return p_windshieldAniIndex; }
size_t MMS1_pamAniIndex(){ return p_pamAniIndex; }
