#include "minigame/minigame0/minigame0.h"

static PLEX_SPRITE* p_thePrize = NULL;

static PLEX_RECT p_prizeRect;

static PLEX_MPREC p_prizeMomentum = 0;
static uint8_t p_prizeDirection = MMS0_DIRECTION_NONE;

static double p_theLine = 0;
static double p_theLine2 = 0;

static double p_coffee = 1;

void MMS0_startCoffee(){ p_coffee = 1; }

void MMS0_createThePrizeSprite(const size_t chapter0spriteTex, const uint64_t time)
{
	PLEX_ANIMATION_PLATE prize = PLEX_createAnimationPlate(0.125, 0.125, chapter0spriteTex);

	PLEX_ANIMATION* prizeAnim = NULL;

	if(p_thePrize != NULL) return;

	p_thePrize = PLEX_genSprite(&prize);

	PLEX_addAnimation(p_thePrize, 1, PLEX_getGameTime());

	prizeAnim = PLEX_getAnimation(0, p_thePrize);

	PLEX_addAnimationFrame(34, prizeAnim);
}

void MMS0_startThePrizePositions()
{
	p_prizeRect.dimens = PLEX_convDimens(4, 3);
	p_prizeRect.origin = PLEX_convPoint(PLEX_WIDTHUNITMAX()/2 - p_prizeRect.dimens.w/2, 0);

	p_prizeDirection = MMS0_DIRECTION_NONE;
}

void MMS0_startCrashPositions()
{
	const PLEX_RECT playerSpace = MMS0_getPlayerSpace();

	p_theLine = p_prizeRect.dimens.h + playerSpace.dimens.h + 2;
	p_theLine2 = PLEX_HEIGHTUNITMAX() - p_theLine;
}

void MMS0_updateThePrize(const double momentum, const double tableMomentum, const uint64_t time)
{
	const PLEX_RECT playerSpace = MMS0_getPlayerSpace();
	const size_t playerDirection = MMS0_getPlayerDirection();

	const size_t lastPrizeDirec = p_prizeDirection;

	PLEX_POINT newPrizeOrigin = p_prizeRect.origin;

	if(p_prizeDirection != MMS0_DIRECTION_NONE)
	{
		if(p_prizeDirection == MMS0_DIRECTION_LEFT) p_prizeMomentum -= tableMomentum;
		else p_prizeMomentum += tableMomentum;

		newPrizeOrigin.x += p_prizeMomentum;
	}

	if(newPrizeOrigin.x < playerSpace.dimens.w)
	{
		newPrizeOrigin.x = playerSpace.dimens.w + momentum;
		p_prizeMomentum = 0;
		p_prizeDirection = MMS0_DIRECTION_NONE;
	}

	if(newPrizeOrigin.x + p_prizeRect.dimens.w > PLEX_WIDTHUNITMAX() - playerSpace.dimens.w)
	{
		newPrizeOrigin.x = PLEX_WIDTHUNITMAX() - playerSpace.dimens.w - p_prizeRect.dimens.w - momentum;
		p_prizeMomentum = 0;
		p_prizeDirection = MMS0_DIRECTION_NONE;
	}

	// do not get rid of the equals in the 'playerSpace.origin.x >= newPrizeOrigin.x + p_prizeRect.dimens.w' here
	if(playerDirection == MMS0_DIRECTION_LEFT && MMS0_isPlayerPushing() && playerSpace.origin.x >= newPrizeOrigin.x + p_prizeRect.dimens.w && playerSpace.origin.y < p_prizeRect.dimens.h) p_prizeDirection = MMS0_DIRECTION_LEFT;

	if(playerDirection == MMS0_DIRECTION_RIGHT && MMS0_isPlayerPushing() && playerSpace.origin.x < newPrizeOrigin.x && playerSpace.origin.y < p_prizeRect.dimens.h) p_prizeDirection = MMS0_DIRECTION_RIGHT;

	if(lastPrizeDirec == MMS0_DIRECTION_NONE && p_prizeDirection != lastPrizeDirec) MM_COMMON_playSoundEffectVolume(0.5, MM_COMMON_SOUNDEFFECT_TABLESCREECH);

	p_prizeRect.origin = newPrizeOrigin;

	PLEX_drawSprite(MMS0_drawLayer(p_prizeRect), 0, PLEX_UNIT(p_prizeRect.origin.x), PLEX_UNIT(p_prizeRect.origin.y), PLEX_UNIT(p_prizeRect.dimens.w), PLEX_UNIT(p_prizeRect.dimens.h), p_thePrize, true, time);
}

void MMS0_factorCoffeeDrink(){ p_coffee -= MMS0_COFFEEDRINKSPEED * PLEX_getGameSecondsPassed(); }

void MMS0_freePrizeSprite(){ if(p_thePrize != NULL) PLEX_destroySprite(&p_thePrize); }

double MMS0_theLine(){ return p_theLine; }
double MMS0_theLine2(){ return p_theLine2; }

PLEX_RECT MMS0_prizeRect(){ return p_prizeRect; }
uint8_t MMS0_prizeDirection(){ return p_prizeDirection; }

double MMS0_coffeePerc(){ return p_coffee; }
