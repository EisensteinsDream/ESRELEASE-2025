#include "windowing/sprite.h"

// NOTE: global function descriptions in header.

// structs ------------------------------------------------------------------------------------------------------------------

typedef struct
{
	PLEX_ANIMATION* animation;
} P_ANIMATION_CONTAINER;

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

// specialized functions ----------------------------------------------------------------------------------------------------

PLEX_SPRITE* PLEX_genSpriteInt(const PLEX_ANIMATION_PLATE* plate, const size_t errorline, const char* const errorfile)
{
	PLEX_SPRITE* ret = NULL;

	if(plate == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITE, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_SPRITE_ONGEN, PLEX_ERRORMESS_ANIMATIONPLATE_PLATE, errorline, errorfile);
		return ret;
	}

	ret = PLEX_allocInt(sizeof(PLEX_SPRITE), errorline, errorfile);

	if(ret == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITE, PLEX_ERROR_ALLOCFAIL, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SPRITE_ONGEN, PLEX_ERRORMESS_ANIMATION_ANIMATION, errorline, errorfile);
		return NULL;
	}

	ret->animations = PLEX_genExpandArrayInt(PLEX_getMemProfileAnimationPreload(), sizeof(P_ANIMATION_CONTAINER), errorline, errorfile);

	if(ret->animations == NULL)
	{
		PLEX_deallocInt((void**)&ret, errorline, errorfile);

		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITE, PLEX_ERROR_ALLOCFAIL, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SPRITE_ONGEN, PLEX_ERRORMESS_ANIMATION_ANIMATION, errorline, errorfile);
		return NULL;
	}

	memcpy(&ret->plate, plate, sizeof(ret->plate));

	ret->stopped = true;

	return ret;
}

void PLEX_destroySpriteInt(PLEX_SPRITE** sprite, const size_t errorline, const char* const errorfile)
{
	PLEX_SPRITE* spritePtr = NULL;

	size_t animationCount = 0;

	if(sprite == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITE, PLEX_ERROR_FREENULLPTR, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_SPRITE_ONDESTROY, PLEX_ERRORMESS_SPRITE_SPRITE, errorline, errorfile);
		return;
	}

	spritePtr = *sprite;

	if(spritePtr == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITE, PLEX_ERROR_FREENULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_SPRITE_ONDESTROY, PLEX_ERRORMESS_SPRITE_SPRITEPTR, errorline, errorfile);
		return;
	}

	animationCount = PLEX_expandArrayCountInt(spritePtr->animations, errorline, errorfile);

	for(size_t ze = 0; ze < animationCount; ++ze)
	{
		P_ANIMATION_CONTAINER* animation = PLEX_getExpandArrayEntry(ze, spritePtr->animations);

		if(animation == NULL)
		{
			PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITE, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SPRITE_ONDESTROY, PLEX_ERRORMESS_ANIMATION_ANIMATION, errorline, errorfile);
			continue;
		}

		if(animation->animation == NULL)
		{
			PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITE, PLEX_ERROR_CONTENTCORRUPTION, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SPRITE_ONDESTROY, PLEX_ERRORMESS_ANIMATION_ANIMATION, errorline, errorfile);
			continue;
		}

		PLEX_destroyExpandArrayInt(&animation->animation->frames, errorline, errorfile);

		PLEX_deallocInt((void**)&animation->animation, errorline, errorfile);
	}

	PLEX_destroyExpandArrayInt(&spritePtr->animations, errorline, errorfile);

	PLEX_deallocInt((void**)sprite, errorline, errorfile);
}

PLEX_SPRITE* PLEX_copySpriteInt(const PLEX_SPRITE* const sprite, const size_t errorline, const char* const errorfile)
{
	PLEX_SPRITE* ret = 0;

	if(sprite == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITE, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_SPRITE_ONCOPY, PLEX_ERRORMESS_SPRITE_SPRITE, errorline, errorfile);
		return NULL;
	}

	if(sprite->animations == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITE, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_SPRITE_ONCOPY, PLEX_ERRORMESS_SPRITE_SPRITE, errorline, errorfile);
		// do not return here
	}

	ret = PLEX_allocInt(sizeof(PLEX_SPRITE), errorline, errorfile);

	if(ret == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITE, PLEX_ERROR_ALLOCFAIL, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SPRITE_ONCOPY, PLEX_ERRORMESS_SPRITE_SPRITE, errorline, errorfile);
		return NULL;
	}

	ret->plate = sprite->plate;
	ret->stopped = sprite->stopped;
	ret->animations = NULL;

	if(sprite->plate.base)
	{
		uint32_t tw = 0;
		uint32_t th = 0;

		PLEX_textureWHInt(sprite->plate.base, &tw, &th, errorline, errorfile);

		ret->plate.base = PLEX_copyTextureInt(sprite->plate.base, 0, 0, tw, th, errorline, errorfile);
	}

	if(sprite->animations != NULL)
	{
		size_t animationCount = PLEX_expandArrayCountInt(sprite->animations, errorline, errorfile);

		ret->animations = PLEX_genExpandArrayInt(PLEX_getMemProfileAnimationPreload(), sizeof(P_ANIMATION_CONTAINER), errorline, errorfile);

		if(ret->animations == NULL)
		{
			PLEX_deallocInt((void**)&ret, errorline, errorfile);

			PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITE, PLEX_ERROR_ALLOCFAIL, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SPRITE_ONCOPY, PLEX_ERRORMESS_ANIMATION_ANIMATIONS, errorline, errorfile);
			return NULL;
		}

		if(!PLEX_multiIncrementExpandArrayInt(animationCount, ret->animations, errorline, errorfile))
		{
			PLEX_destroyExpandArrayInt(&ret->animations, errorline, errorfile);
			PLEX_deallocInt((void**)&ret, errorline, errorfile);

			PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITE, PLEX_ERROR_INCREMENT, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SPRITE_ONCOPY, PLEX_ERRORMESS_SPRITE_SPRITE, errorline, errorfile);
			return NULL;
		}

		for(size_t ze = 0; ze < animationCount; ++ze)
		{
			P_ANIMATION_CONTAINER* from = PLEX_getExpandArrayEntry(ze, sprite->animations);
			P_ANIMATION_CONTAINER* to = NULL;

			size_t frameCount = 0;

			bool incDestroy = false;

			if(from == NULL)
			{
				PLEX_destroyExpandArrayInt(&ret->animations, errorline, errorfile);
				PLEX_deallocInt((void**)&ret, errorline, errorfile);

				PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITE, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SPRITE_ONCOPY, PLEX_ERRORMESS_ANIMATION_ANIMATIONS, errorline, errorfile);

				return NULL;
			}

			frameCount = PLEX_expandArrayCountInt(from->animation->frames, errorline, errorfile);

			to = PLEX_getExpandArrayEntryInt(ze, ret->animations, errorline, errorfile);

			if(to == NULL)
			{
				PLEX_destroyExpandArrayInt(&ret->animations, errorline, errorfile);
				PLEX_deallocInt((void**)&ret, errorline, errorfile);

				PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITE, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SPRITE_ONCOPY, PLEX_ERRORMESS_ANIMATION_ANIMATIONS, errorline, errorfile);

				return NULL;
			}

			to->animation = PLEX_allocInt(sizeof(PLEX_ANIMATION), errorline, errorfile);

			to->animation->cycle = from->animation->cycle;
			to->animation->start = from->animation->start;
			to->animation->stopped = from->animation->stopped;

			if(to->animation == NULL)
			{
				for(size_t uh = 0; uh < ze; ++uh)
				{
					P_ANIMATION_CONTAINER* destroy = PLEX_getExpandArrayEntryInt(uh, ret->animations, errorline, errorfile);

					if(destroy == NULL)
					{
						PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITE, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SPRITE_ONCOPY, PLEX_ERRORMESS_ANIMATION_ANIMATION, errorline, errorfile);
					}

					PLEX_destroyExpandArrayInt(&destroy->animation->frames, errorline, errorfile);
					PLEX_deallocInt((void**)&destroy->animation, errorline, errorfile);
				}

				PLEX_destroyExpandArrayInt(&ret->animations, errorline, errorfile);
				PLEX_deallocInt((void**)&ret, errorline, errorfile);

				PLEX_deallocInt((void**)&to->animation, errorline, errorfile);
				PLEX_deallocInt((void**)&to, errorline, errorfile);

				PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITE, PLEX_ERROR_ALLOCFAIL, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SPRITE_ONCOPY, PLEX_ERRORMESS_ANIMATION_ANIMATION, errorline, errorfile);

				return NULL;
			}

			to->animation->frames = PLEX_genExpandArrayInt(PLEX_getMemProfileFramePreload(), sizeof(size_t), errorline, errorfile);

			if(to->animation->frames == NULL)
			{
				PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITE, PLEX_ERROR_ALLOCFAIL, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SPRITE_ONCOPY, PLEX_ERRORMESS_ANIMATION_FRAMES, errorline, errorfile);
				incDestroy = true;
			}

			if(!PLEX_multiIncrementExpandArrayInt(frameCount, to->animation->frames, errorline, errorfile))
			{
				PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITE, PLEX_ERROR_INCREMENT, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SPRITE_ONCOPY, PLEX_ERRORMESS_ANIMATION_FRAMES, errorline, errorfile);
				incDestroy = true;
			}

			if(incDestroy)
			{
				for(size_t uh = 0; uh < ze; ++uh)
				{
					P_ANIMATION_CONTAINER* destroy = PLEX_getExpandArrayEntryInt(uh, ret->animations, errorline, errorfile);

					if(destroy == NULL)
					{
						PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITE, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SPRITE_ONCOPY, PLEX_ERRORMESS_ANIMATION_ANIMATION, errorline, errorfile);
						continue;
					}

					PLEX_destroyExpandArrayInt(&destroy->animation->frames, errorline, errorfile);
					PLEX_deallocInt((void**)&destroy->animation, errorline, errorfile);
				}

				if(to != NULL) PLEX_deallocInt((void**)&to->animation, errorline, errorfile);
				if(to != NULL) PLEX_deallocInt((void**)&to, errorline, errorfile);

				if(ret != NULL) PLEX_destroyExpandArrayInt(&ret->animations, errorline, errorfile);
				if(ret != NULL) PLEX_deallocInt((void**)&ret, errorline, errorfile);

				return NULL;
			}

			for(size_t uh = 0; uh < frameCount; ++uh)
			{
				const size_t* const fromFrame = PLEX_getExpandArrayEntryInt(uh, from->animation->frames, errorline, errorfile);
				size_t* toFrame = PLEX_getExpandArrayEntryInt(uh, to->animation->frames, errorline, errorfile);

				if(toFrame == NULL)
				{
					for(size_t uh = 0; uh < ze; ++uh)
					{
						P_ANIMATION_CONTAINER* destroy = PLEX_getExpandArrayEntryInt(uh, ret->animations, errorline, errorfile);

						if(destroy == NULL)
						{
							PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITE, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SPRITE_ONCOPY, PLEX_ERRORMESS_ANIMATION_ANIMATION, errorline, errorfile);
							continue;
						}

						PLEX_destroyExpandArrayInt(&destroy->animation->frames, errorline, errorfile);
						PLEX_deallocInt((void**)&destroy->animation, errorline, errorfile);
					}

					if(to != NULL) PLEX_deallocInt((void**)&to->animation, errorline, errorfile);
					if(to != NULL) PLEX_deallocInt((void**)&to, errorline, errorfile);

					if(ret != NULL) PLEX_destroyExpandArrayInt(&ret->animations, errorline, errorfile);
					if(ret != NULL) PLEX_deallocInt((void**)&ret, errorline, errorfile);

					PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITE, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SPRITE_ONCOPY, PLEX_ERRORMESS_ANIMATION_ANIMATION2, errorline, errorfile);
				}

				*toFrame = *fromFrame;
			}
		}
	}

	return ret;
}

void PLEX_addAnimationInt(PLEX_SPRITE* sprite, const uint64_t cycle, const uint64_t start, const size_t errorline, const char* const errorfile)
{
	P_ANIMATION_CONTAINER* target = NULL;

	if(sprite == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITE, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_SPRITE_ONADDANIMATION, PLEX_ERRORMESS_SPRITE_SPRITE, errorline, errorfile);
		return;
	}

	if(sprite->animations == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITE, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SPRITE_ONADDANIMATION, PLEX_ERRORMESS_ANIMATION_ANIMATIONS, errorline, errorfile);
		return;
	}

	if(!PLEX_incrementExpandArrayInt(sprite->animations, errorline, errorfile))
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITE, PLEX_ERROR_INCREMENT, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SPRITE_ONADDANIMATION, PLEX_ERRORMESS_ANIMATION_ANIMATIONS, errorline, errorfile);
		return;
	}

	target = PLEX_getExpandArrayLastInt(sprite->animations, errorline, errorfile);

	if(target == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITE, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SPRITE_ONADDANIMATION, PLEX_ERRORMESS_ANIMATION_ANIMATION, errorline, errorfile);
		return;
	}

	target->animation = PLEX_allocInt(sizeof(PLEX_ANIMATION), errorline, errorfile);

	if(target->animation == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITE, PLEX_ERROR_ALLOCFAIL, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SPRITE_ONADDANIMATION, PLEX_ERRORMESS_ANIMATION_ANIMATION, errorline, errorfile);
		return;
	}

	target->animation->cycle = cycle;
	target->animation->start = start;
	target->animation->stopped = true;

	target->animation->frames = PLEX_genExpandArrayInt(PLEX_getMemProfileFramePreload(), sizeof(size_t), errorline, errorfile);

	if(target->animation->frames == NULL)
	{
		PLEX_deallocInt((void**)&target->animation, errorline, errorfile);

		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITE, PLEX_ERROR_ALLOCFAIL, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SPRITE_ONADDANIMATION, PLEX_ERRORMESS_ANIMATION_FRAMES, errorline, errorfile);
		return;
	}
}

void PLEX_drawSpriteInt(const size_t order, const size_t index, const double tx, const double ty, const double tw, const double th, const PLEX_SPRITE* sprite, const bool offset, const uint64_t time,  const size_t errorline, const char* const errorfile)
{
	P_ANIMATION_CONTAINER* animation = NULL;

	size_t count = 0;

	if(sprite == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITE, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_SPRITE_ONDRAW, PLEX_ERRORMESS_SPRITE_SPRITE, errorline, errorfile);
		return;
	}

	count = PLEX_expandArrayCountInt(sprite->animations, errorline, errorfile);

	if(index >= count)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITE, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SPRITE_ONDRAW, PLEX_ERRORMESS_GENERIC_INDEX, errorline, errorfile);
		return;
	}

	animation = PLEX_getExpandArrayEntryInt(index, sprite->animations, errorline, errorfile);

	if(animation == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITE, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SPRITE_ONDRAW, PLEX_ERRORMESS_ANIMATION_ANIMATION, errorline, errorfile);
		return;
	}

	PLEX_drawFrameInt(order, tx, ty, tw, th, animation->animation, sprite->plate, offset, time, errorline, errorfile);
}

void PLEX_drawSpriteTintedInt(const size_t order, const size_t index, const double tx, const double ty, const double tw, const double th, const uint8_t r, const uint8_t g, const uint8_t b, const PLEX_SPRITE* sprite, const bool offset, const uint64_t time,  const size_t errorline, const char* const errorfile)
{
	P_ANIMATION_CONTAINER* animation = NULL;

	size_t count = 0;

	if(sprite == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITE, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_SPRITE_ONDRAWTINTED, PLEX_ERRORMESS_SPRITE_SPRITE, errorline, errorfile);
		return;
	}

	count = PLEX_expandArrayCountInt(sprite->animations, errorline, errorfile);

	if(index >= count)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITE, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SPRITE_ONDRAWTINTED, PLEX_ERRORMESS_GENERIC_INDEX, errorline, errorfile);
		return;
	}

	animation = PLEX_getExpandArrayEntryInt(index, sprite->animations, errorline, errorfile);

	if(animation == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITE, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SPRITE_ONDRAWTINTED, PLEX_ERRORMESS_ANIMATION_ANIMATION, errorline, errorfile);
		return;
	}

	PLEX_drawFrameTintedInt(order, tx, ty, tw, th, r, g, b, animation->animation, sprite->plate, offset, time, errorline, errorfile);
}

void PLEX_drawSpriteRotatedInt(const size_t order, const size_t index, const double tx, const double ty, const double tw, const double th, const double angle, const PLEX_SPRITE* sprite, const bool offset, const uint64_t time, const size_t errorline, const char* const errorfile)
{
	P_ANIMATION_CONTAINER* animation = NULL;

	size_t count = 0;

	if(sprite == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITE, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_SPRITE_ONDRAWROTATED, PLEX_ERRORMESS_SPRITE_SPRITE, errorline, errorfile);
		return;
	}

	count = PLEX_expandArrayCountInt(sprite->animations, errorline, errorfile);

	if(index >= count)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITE, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SPRITE_ONDRAWROTATED, PLEX_ERRORMESS_GENERIC_INDEX, errorline, errorfile);
		return;
	}

	animation = PLEX_getExpandArrayEntryInt(index, sprite->animations, errorline, errorfile);

	if(animation == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITE, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SPRITE_ONDRAWROTATED, PLEX_ERRORMESS_ANIMATION_ANIMATION, errorline, errorfile);
		return;
	}

	PLEX_drawFrameRotateInt(order, tx, ty, tw, th, animation->animation, sprite->plate, angle, offset, time, errorline, errorfile);
}

void PLEX_drawSpriteTintedRotatedInt(const size_t order, const size_t index, const double tx, const double ty, const double tw, const double th, const uint8_t r, const uint8_t g, const uint8_t b, const double angle, const PLEX_SPRITE* sprite, const bool offset, const uint64_t time, const size_t errorline, const char* const errorfile)
{
	P_ANIMATION_CONTAINER* animation = NULL;

	size_t count = 0;

	if(sprite == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITE, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_SPRITE_ONDRAWROTATEDTINTED, PLEX_ERRORMESS_SPRITE_SPRITE, errorline, errorfile);
		return;
	}

	count = PLEX_expandArrayCountInt(sprite->animations, errorline, errorfile);

	if(index >= count)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITE, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SPRITE_ONDRAWROTATEDTINTED, PLEX_ERRORMESS_GENERIC_INDEX, errorline, errorfile);
		return;
	}

	animation = PLEX_getExpandArrayEntryInt(index, sprite->animations, errorline, errorfile);

	if(animation == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITE, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SPRITE_ONDRAWROTATEDTINTED, PLEX_ERRORMESS_ANIMATION_ANIMATION, errorline, errorfile);
		return;
	}

	PLEX_drawFrameRotateTintedInt(order, tx, ty, tw, th, animation->animation, sprite->plate, r, g, b, angle, offset, time, errorline, errorfile);
}

void PLEX_startSpriteInt(const uint64_t start, PLEX_SPRITE* sprite, const size_t errorline, const char* const errorfile)
{
	size_t animationCount = 0;

	if(sprite == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITE, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_SPRITE_ONSTART, PLEX_ERRORMESS_SPRITE_SPRITE, errorline, errorfile);
		return;
	}

	if(!sprite->stopped) return;

	animationCount = PLEX_expandArrayCountInt(sprite->animations, errorline, errorfile);

	for(size_t ze = 0; ze < animationCount; ++ze)
	{
		P_ANIMATION_CONTAINER* animation = PLEX_getExpandArrayEntryInt(ze, sprite->animations, errorline, errorfile);

		if(animation == NULL)
		{
			PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITE, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SPRITE_ONSTART, PLEX_ERRORMESS_ANIMATION_ANIMATION, errorline, errorfile);
			return;
		}

		PLEX_startAnimationInt(start, animation->animation, errorline, errorfile);
	}

	sprite->stopped = false;
}

void PLEX_stopSpriteInt(PLEX_SPRITE* sprite, const size_t errorline, const char* const errorfile)
{
	size_t animationCount = 0;

	if(sprite == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITE, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_SPRITE_ONSTOP, PLEX_ERRORMESS_SPRITE_SPRITE, errorline, errorfile);
		return;
	}

	animationCount = PLEX_expandArrayCountInt(sprite->animations, errorline, errorfile);

	for(size_t ze = 0; ze < animationCount; ++ze)
	{
		P_ANIMATION_CONTAINER* animation = PLEX_getExpandArrayEntryInt(ze, sprite->animations, errorline, errorfile);

		if(animation == NULL)
		{
			PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITE, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SPRITE_ONSTOP, PLEX_ERRORMESS_ANIMATION_ANIMATION, errorline, errorfile);
			return;
		}

		PLEX_stopAnimationInt(animation->animation, errorline, errorfile);
	}

	sprite->stopped = true;
}

void PLEX_clearSpriteInt(PLEX_SPRITE* sprite, const size_t errorline, const char* const errorfile)
{
	if(sprite == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITE, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_SPRITE_ONCLEAR, PLEX_ERRORMESS_SPRITE_SPRITE, errorline, errorfile);
		return;
	}

	PLEX_clearAnimationPlateInt(&sprite->plate, errorline, errorfile);
}

void PLEX_unclearSpriteInt(PLEX_SPRITE* sprite, const size_t errorline, const char* const errorfile)
{
	if(sprite == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITE, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_SPRITE_ONUNCLEAR, PLEX_ERRORMESS_SPRITE_SPRITE, errorline, errorfile);
		return;
	}

	PLEX_unclearAnimationPlateInt(&sprite->plate, errorline, errorfile);
}

// setters ------------------------------------------------------------------------------------------------------------------

void PLEX_changeSpriteCycleSpeedInt(const size_t index, const uint64_t cycle, PLEX_SPRITE* sprite, const uint64_t time, const size_t errorline, const char* const errorfile)
{
	P_ANIMATION_CONTAINER* animation = NULL;

	size_t animationCount = 0;

	if(sprite == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITE, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_SPRITE_ONCYCLESPEEDCHANGE, PLEX_ERRORMESS_SPRITE_SPRITE, errorline, errorfile);
		return;
	}

	animationCount = PLEX_expandArrayCountInt(sprite->animations, errorline, errorfile);

	if(index >= animationCount)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITE, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SPRITE_ONCYCLESPEEDCHANGE, PLEX_ERRORMESS_GENERIC_INDEX, errorline, errorfile);
		return;
	}

	animation = PLEX_getExpandArrayEntryInt(index, sprite->animations, errorline, errorfile);

	if(animation == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITE, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SPRITE_ONCYCLESPEEDCHANGE, PLEX_ERRORMESS_ANIMATION_ANIMATION, errorline, errorfile);
		return;
	}

	PLEX_changeAnimationCycleSpeedInt(cycle, animation->animation, time, errorline, errorfile);
}

bool PLEX_syncSpritesInt(const size_t index, const PLEX_SPRITE* a, PLEX_SPRITE* b, const size_t errorline, const char* const errorfile)
{
	P_ANIMATION_CONTAINER* animA = NULL;
	P_ANIMATION_CONTAINER* animB = NULL;

	size_t animationCountA = 0;
	size_t animationCountB = 0;

	if(a == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITE, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_SPRITE_ONSYNCING, PLEX_ERRORMESS_ANIMATION_ANIMATION, errorline, errorfile);
		return false;
	}

	if(b == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITE, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_SPRITE_ONSYNCING, PLEX_ERRORMESS_ANIMATION_ANIMATION2, errorline, errorfile);
		return false;
	}

	animationCountA = PLEX_expandArrayCountInt(a->animations, errorline, errorfile);

	if(index >= animationCountA)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITE, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SPRITE_ONSYNCING, PLEX_ERRORMESS_GENERIC_INDEX, errorline, errorfile);
		return false;
	}

	animationCountB = PLEX_expandArrayCountInt(b->animations, errorline, errorfile);

	if(index >= animationCountB)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITE, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SPRITE_ONSYNCING, PLEX_ERRORMESS_GENERIC_INDEX2, errorline, errorfile);
		return false;
	}

	animA = PLEX_getExpandArrayEntryInt(index, a->animations, errorline, errorfile);

	if(animA == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITE, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SPRITE_ONSYNCING, PLEX_ERRORMESS_ANIMATION_ANIMATION, errorline, errorfile);
		return false;
	}

	animB = PLEX_getExpandArrayEntryInt(index, b->animations, errorline, errorfile);

	if(animB == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITE, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SPRITE_ONSYNCING, PLEX_ERRORMESS_ANIMATION_ANIMATION2, errorline, errorfile);
		return false;
	}

	PLEX_syncAnimationsInt(*animA->animation, animB->animation, errorline, errorfile);

	return true;
}

// getters ------------------------------------------------------------------------------------------------------------------

uint64_t PLEX_spriteCycleLenInt(const size_t index, const PLEX_SPRITE* sprite, const size_t errorline, const char* const errorfile)
{
	size_t count = 0;

	P_ANIMATION_CONTAINER* animation = NULL;

	if(sprite == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITE, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_SPRITE_ONGETCYCLELEN, PLEX_ERRORMESS_SPRITE_SPRITE, errorline, errorfile);
		return 0;
	}

	count = PLEX_expandArrayCountInt(sprite->animations, errorline, errorfile);

	if(index >= count)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITE, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SPRITE_ONGETCYCLELEN, PLEX_ERRORMESS_GENERIC_INDEX, errorline, errorfile);
		return 0;
	}

	animation = PLEX_getExpandArrayEntryInt(index, sprite->animations, errorline, errorfile);

	if(animation == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITE, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SPRITE_ONGETCYCLELEN, PLEX_ERRORMESS_ANIMATION_ANIMATION, errorline, errorfile);
		return 0;
	}

	return PLEX_animationCycleLenInt(animation->animation, errorline, errorfile);
}

bool PLEX_isSpriteStoppedInt(const PLEX_SPRITE* sprite, const size_t errorline, const char* const errorfile)
{
	if(sprite == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITE, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_SPRITE_ONGETTOPPED, PLEX_ERRORMESS_SPRITE_SPRITE, errorline, errorfile);
		return false;
	}

	return sprite->stopped;
}

PLEX_ANIMATION* PLEX_getAnimationInt(const size_t index, PLEX_SPRITE* sprite, const size_t errorline, const char* const errorfile)
{
	P_ANIMATION_CONTAINER* container = NULL;

	size_t animationCount = 0;

	if(sprite == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITE, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_ANIMATION_ONGET, PLEX_ERRORMESS_SPRITE_SPRITE, errorline, errorfile);
		return NULL;
	}

	animationCount = PLEX_expandArrayCountInt(sprite->animations, errorline, errorfile);

	if(index >= animationCount)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITE, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_ANIMATION_ONGET, PLEX_ERRORMESS_GENERIC_INDEX, errorline, errorfile);
		return NULL;
	}

	container = PLEX_getExpandArrayEntryInt(index, sprite->animations, errorline, errorfile);

	if(container == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITE, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_ANIMATION_ONGET, PLEX_ERRORMESS_ANIMATION_ANIMATION, errorline, errorfile);
		return NULL;
	}

	return container->animation;
}

size_t PLEX_spriteTexInt(const PLEX_SPRITE* sprite, const size_t errorline, const char* const errorfile)
{
	if(sprite == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITE, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_SPRITE_ONGETTEX, PLEX_ERRORMESS_SPRITE_SPRITE, errorline, errorfile);
		return 0;
	}

	return sprite->plate.base;
}

double PLEX_spriteWPercInt(const PLEX_SPRITE* sprite, const size_t errorline, const char* const errorfile)
{
	if(sprite == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITE, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_SPRITE_ONGETWPERC, PLEX_ERRORMESS_SPRITE_SPRITE, errorline, errorfile);
		return 0;
	}

	return PLEX_animationPlateWPerc(sprite->plate);
}

double PLEX_spriteHPercInt(const PLEX_SPRITE* sprite, const size_t errorline, const char* const errorfile)
{
	if(sprite == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITE, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_SPRITE_ONGETHPERC, PLEX_ERRORMESS_SPRITE_SPRITE, errorline, errorfile);
		return 0;
	}

	return PLEX_animationPlateHPerc(sprite->plate);
}

size_t PLEX_spriteAnimationCountInt(const PLEX_SPRITE* sprite, const size_t errorline, const char* const errorfile)
{
	if(sprite == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SPRITE, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_SPRITE_ONGETCOUNT, PLEX_ERRORMESS_SPRITE_SPRITE, errorline, errorfile);
		return 0;
	}

	return PLEX_expandArrayCountInt(sprite->animations, errorline, errorfile);
}
