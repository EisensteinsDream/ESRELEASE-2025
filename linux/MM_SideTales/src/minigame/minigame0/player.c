#include "minigame/minigame0/minigame0.h"

static PLEX_RECT p_space, p_pushRect;

static PLEX_SPRITE* p_pamaleanaSprite = NULL;

static size_t p_direction = MMS0_DIRECTION_DOWN;
static bool p_moving = false;
static bool p_pushing = false;

static uint64_t p_pushTime = 0;

void MMS0_createPamaleanaSprite(const size_t pamaleanaSpriteTex, const uint64_t time)
{
	PLEX_ANIMATION_PLATE pamaleanaPlate = PLEX_createAnimationPlate(0.0625, 0.125, pamaleanaSpriteTex);

	PLEX_ANIMATION* pamaleanaAnimDown = NULL;
	PLEX_ANIMATION* pamaleanaAnimUp = NULL;
	PLEX_ANIMATION* pamaleanaAnimLeft = NULL;
	PLEX_ANIMATION* pamaleanaAnimRight = NULL;

	PLEX_ANIMATION* pamaleanaAnimPushDown = NULL;
	PLEX_ANIMATION* pamaleanaAnimPushUp = NULL;
	PLEX_ANIMATION* pamaleanaAnimPushLeft = NULL;
	PLEX_ANIMATION* pamaleanaAnimPushRight = NULL;

	if(p_pamaleanaSprite != NULL) return;

	p_pamaleanaSprite = PLEX_genSprite(&pamaleanaPlate);

	PLEX_addAnimation(p_pamaleanaSprite, 800, PLEX_getGameTime());
	PLEX_addAnimation(p_pamaleanaSprite, 800, PLEX_getGameTime());
	PLEX_addAnimation(p_pamaleanaSprite, 800, PLEX_getGameTime());
	PLEX_addAnimation(p_pamaleanaSprite, 800, PLEX_getGameTime());

	PLEX_addAnimation(p_pamaleanaSprite, 300, PLEX_getGameTime());
	PLEX_addAnimation(p_pamaleanaSprite, 300, PLEX_getGameTime());
	PLEX_addAnimation(p_pamaleanaSprite, 300, PLEX_getGameTime());
	PLEX_addAnimation(p_pamaleanaSprite, 300, PLEX_getGameTime());

	// ANIMATIONS

	pamaleanaAnimUp = PLEX_getAnimation(0, p_pamaleanaSprite);
	pamaleanaAnimRight = PLEX_getAnimation(1, p_pamaleanaSprite);
	pamaleanaAnimDown = PLEX_getAnimation(2, p_pamaleanaSprite);
	pamaleanaAnimLeft = PLEX_getAnimation(3, p_pamaleanaSprite);

	// MOVING

	PLEX_addAnimationFrame(4, pamaleanaAnimUp);
	PLEX_addAnimationFrame(5, pamaleanaAnimUp);
	PLEX_addAnimationFrame(6, pamaleanaAnimUp);
	PLEX_addAnimationFrame(5, pamaleanaAnimUp);
	PLEX_addAnimationFrame(4, pamaleanaAnimUp);
	PLEX_addAnimationFrame(7, pamaleanaAnimUp);
	PLEX_addAnimationFrame(8, pamaleanaAnimUp);
	PLEX_addAnimationFrame(7, pamaleanaAnimUp);

	PLEX_addAnimationFrame(9, pamaleanaAnimRight);
	PLEX_addAnimationFrame(10, pamaleanaAnimRight);
	PLEX_addAnimationFrame(11, pamaleanaAnimRight);
	PLEX_addAnimationFrame(12, pamaleanaAnimRight);
	PLEX_addAnimationFrame(11, pamaleanaAnimRight);

	PLEX_addAnimationFrame(13, pamaleanaAnimDown);
	PLEX_addAnimationFrame(14, pamaleanaAnimDown);
	PLEX_addAnimationFrame(15, pamaleanaAnimDown);
	PLEX_addAnimationFrame(14, pamaleanaAnimDown);
	PLEX_addAnimationFrame(13, pamaleanaAnimDown);
	PLEX_addAnimationFrame(16, pamaleanaAnimDown);
	PLEX_addAnimationFrame(13, pamaleanaAnimDown);
	PLEX_addAnimationFrame(16, pamaleanaAnimDown);

	PLEX_addAnimationFrame(18, pamaleanaAnimLeft);
	PLEX_addAnimationFrame(20, pamaleanaAnimLeft);
	PLEX_addAnimationFrame(21, pamaleanaAnimLeft);
	PLEX_addAnimationFrame(19, pamaleanaAnimLeft);

	// PUSHING

	pamaleanaAnimPushUp = PLEX_getAnimation(4, p_pamaleanaSprite);
	pamaleanaAnimPushRight = PLEX_getAnimation(5, p_pamaleanaSprite);
	pamaleanaAnimPushDown = PLEX_getAnimation(6, p_pamaleanaSprite);
	pamaleanaAnimPushLeft = PLEX_getAnimation(7, p_pamaleanaSprite);

	PLEX_addAnimationFrame(22, pamaleanaAnimPushUp);
	PLEX_addAnimationFrame(23, pamaleanaAnimPushUp);

	PLEX_addAnimationFrame(24, pamaleanaAnimPushRight);
	PLEX_addAnimationFrame(25, pamaleanaAnimPushRight);

	PLEX_addAnimationFrame(26, pamaleanaAnimPushDown);
	PLEX_addAnimationFrame(27, pamaleanaAnimPushDown);

	PLEX_addAnimationFrame(28, pamaleanaAnimPushLeft);
	PLEX_addAnimationFrame(29, pamaleanaAnimPushLeft);

	PLEX_startSprite(time, p_pamaleanaSprite);
}

void MMS0_startPlayerPosition()
{
	p_space.origin = PLEX_convPoint(PLEX_WIDTHUNITMAX()/2, PLEX_HEIGHTUNITMAX()/4);
	p_space.dimens = PLEX_convDimens(1.5, 3);

	p_direction = MMS0_DIRECTION_DOWN;
}

void MMS0_updatePlayer(PLEX_MPREC* momX, PLEX_MPREC* momY, const double momentum, const uint64_t time)
{
	p_moving = false;

	// player cannot move while pushing
	if(!p_pushing)
	{
		if(!PLEX_getGameTimePaused())
		{
			// makes player 'push'
			if(PLEX_KEY_press('q') || PLEX_CONTROLLER_press(0, SDL_CONTROLLER_BUTTON_A))
			{
				switch(p_direction)
				{
					case MMS0_DIRECTION_UP:
						p_pushRect.origin.y = p_space.origin.y - 0.5;
						p_pushRect.origin.x = p_space.origin.x + 0.1;
						p_pushRect.dimens.w = 0.8;
						p_pushRect.dimens.h = 0.25;
					break;

					case MMS0_DIRECTION_DOWN:
						p_pushRect.origin.y = p_space.origin.y + p_space.dimens.h + 0.1;
						p_pushRect.origin.x = p_space.origin.x + 0.1;
						p_pushRect.dimens.w = 0.8;
						p_pushRect.dimens.h = 0.25;
					break;

					case MMS0_DIRECTION_RIGHT:
						p_pushRect.origin.y = p_space.origin.y;
						p_pushRect.origin.x = p_space.origin.x + 1.6;

						p_pushRect.dimens.w = 0.4;
						p_pushRect.dimens.h = 1;
					break;

					case MMS0_DIRECTION_LEFT:
						p_pushRect.origin.y = p_space.origin.y;
						p_pushRect.origin.x = p_space.origin.x - 0.8;

						p_pushRect.dimens.w = 0.4;
						p_pushRect.dimens.h = 1;
					break;
				};

				p_pushing = true;
				p_pushTime = time;
			}else{
				const bool controllerUp = PLEX_CONTROLLER_count() && (PLEX_CONTROLLER_axisUp(0) || PLEX_CONTROLLER_down(0, SDL_CONTROLLER_BUTTON_DPAD_UP));
				const bool controllerRight = PLEX_CONTROLLER_count() && (PLEX_CONTROLLER_axisDown(0) || PLEX_CONTROLLER_down(0, SDL_CONTROLLER_BUTTON_DPAD_DOWN));
				const bool controllerDown = PLEX_CONTROLLER_count() && (PLEX_CONTROLLER_axisRight(0) || PLEX_CONTROLLER_down(0, SDL_CONTROLLER_BUTTON_DPAD_RIGHT));
				const bool controllerLeft = PLEX_CONTROLLER_count() && (PLEX_CONTROLLER_axisLeft(0) || PLEX_CONTROLLER_down(0, SDL_CONTROLLER_BUTTON_DPAD_LEFT));

				if(PLEX_KEY_down('w') || controllerUp){ p_direction = MMS0_DIRECTION_UP; p_moving = true; *momY -= momentum; }
				else if(PLEX_KEY_down('s') || controllerRight){ p_direction = MMS0_DIRECTION_DOWN; p_moving = true; *momY += momentum; }

				if(PLEX_KEY_down('d') || controllerDown){ p_direction = MMS0_DIRECTION_RIGHT; p_moving = true; *momX += momentum; }
				else if(PLEX_KEY_down('a') || controllerLeft){ p_direction = MMS0_DIRECTION_LEFT; p_moving = true; *momX -= momentum; }
			}
		}

		if(p_moving)
		{
			if(PLEX_isSpriteStopped(p_pamaleanaSprite)) PLEX_startSprite(time, p_pamaleanaSprite);
		}else{
			if(!PLEX_isSpriteStopped(p_pamaleanaSprite)) PLEX_stopSprite(p_pamaleanaSprite);
		}
	}else{
		if(PLEX_isSpriteStopped(p_pamaleanaSprite)) PLEX_startSprite(time, p_pamaleanaSprite);

		if(time - p_pushTime >= MMS0_PUSHTIME) p_pushing = false;
	}

	if(p_pushing) PLEX_drawSprite(MMS0_drawLayer(p_space), p_direction + 4, PLEX_UNIT(p_space.origin.x), PLEX_UNIT(p_space.origin.y), PLEX_UNIT(p_space.dimens.w), PLEX_UNIT(p_space.dimens.h), p_pamaleanaSprite, true, time);
	else PLEX_drawSprite(MMS0_drawLayer(p_space), p_direction, PLEX_UNIT(p_space.origin.x), PLEX_UNIT(p_space.origin.y), PLEX_UNIT(p_space.dimens.w), PLEX_UNIT(p_space.dimens.h), p_pamaleanaSprite, true, time);
}

void MMS0_setPlayerSpace(const PLEX_RECT playerSpace){ p_space = playerSpace; }

void MMS0_freePlayerSprite(){ if(p_pamaleanaSprite != NULL) PLEX_destroySprite(&p_pamaleanaSprite); }

size_t MMS0_getPlayerDirection(){ return p_direction; }
PLEX_RECT MMS0_getPlayerSpace(){ return p_space; }

bool MMS0_isPlayerPushing(){ return p_pushing; }
PLEX_RECT MMS0_getPlayerPushRect(){ return p_pushRect; }

