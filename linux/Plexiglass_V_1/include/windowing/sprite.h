#ifndef PLEX_SPRITE_H
#define PLEX_SPRITE_H

// This unit contains the sprites. Sprites essentially are a collection of animations that can be determined by a simple positive integer index known as the aniIndex. If you want to deal in animations it's easiest to simply use sprites. Sprites are allocated on the heap using PLEX virtual memory and therefore must be destroyed. They can also be copied. All you need in order to generate a sprite is an animation plate which can be created with the PLEX_createAnimationPlate described in 'window/animationplate.h'.

// NOTE: This is an independent unit. Not a unit with an accompanying state machine. It has no 'start, update, or end' functions that need to be called to operate.

#include "windowing/animation.h"

// macro functions and macros -----------------------------------------------------------------------------------------------

// ARGUMENTS: (const PLEX_ANIMATION_PLATE* plate) - returns PLEX_SPRITE*

#define PLEX_genSprite(plate) PLEX_genSpriteInt(plate, __LINE__, __FILE__)

// ARGUMENTS: (PLEX_SPRITE** sprite)

#define PLEX_destroySprite(sprite) PLEX_destroySpriteInt(sprite, __LINE__, __FILE__)

// ARGUMENTS: (PLEX_SPRITE** sprite) - returns PLEX_SPRITE*

#define PLEX_copySprite(sprite) PLEX_copySpriteInt(sprite, __LINE__, __FILE__)

// ARGUMENTS: (PLEX_SPRITE* sprite, const uint64_t cycle, const uint64_t start)

#define PLEX_addAnimation(sprite, cycle, start) PLEX_addAnimationInt(sprite, cycle, start, __LINE__, __FILE__)

// ARGUMENTS: (const size_t order, const size_t index, const double tx, const double ty, const double tw, const double th, const PLEX_SPRITE* sprite, const bool offset, const uint64_t time)

#define PLEX_drawSprite(order, index, tx, ty, tw, th, sprite, offset, time) PLEX_drawSpriteInt(order, index, tx, ty, tw, th, sprite, offset, time, __LINE__, __FILE__)

// ARGUMENTS: (const size_t order, const size_t index, const double tx, const double ty, const double tw, const double th, const uint8_t r, const uint8_t g, const uint8_t b, const PLEX_SPRITE* sprite, const bool offset, const uint64_t time)

#define PLEX_drawSpriteTinted(order, index, tx, ty, tw, th, r, g, b, sprite, offset, time) PLEX_drawSpriteTintedInt(order, index, tx, ty, tw, th, r, g, b, sprite, offset, time, __LINE__, __FILE__)

// ARGUMENTS: (const size_t order, const size_t index, const double tx, const double ty, const double tw, const double th, const double angle, const PLEX_SPRITE* sprite, const bool offset, const uint64_t time)

#define PLEX_drawSpriteRotated(order, index, tx, ty, tw, th, angle, sprite, offset, time) PLEX_drawSpriteRotatedInt(order, index, tx, ty, tw, th, angle, sprite, offset, time, __LINE__, __FILE__)

// ARGUMENTS: (const size_t order, const size_t index, const double tx, const double ty, const double tw, const double th, const uint8_t r, const uint8_t g, const uint8_t b, const double angle, const PLEX_SPRITE* sprite, const bool offset, const uint64_t time)

#define PLEX_drawSpriteTintedRotated(order, index, tx, ty, tw, th, r, g, b, angle, sprite, offset, time) PLEX_drawSpriteTintedRotatedInt(order, index, tx, ty, tw, th, r, g, b, angle, sprite, offset, time, __LINE__, __FILE__)

// ARGUMENTS: (const uint64_t start, PLEX_SPRITE* sprite)

#define PLEX_startSprite(start, sprite) PLEX_startSpriteInt(start, sprite, __LINE__, __FILE__)

// ARGUMENTS: (PLEX_SPRITE* sprite)

#define PLEX_stopSprite(sprite) PLEX_stopSpriteInt(sprite, __LINE__, __FILE__)

// ARGUMENTS: (PLEX_SPRITE* sprite)

#define PLEX_clearSprite(sprite) PLEX_clearSpriteInt(sprite, __LINE__, __FILE__)

// ARGUMENTS: (PLEX_SPRITE* sprite)

#define PLEX_unclearSprite(sprite) PLEX_unclearSpriteInt(sprite, __LINE__, __FILE__)

// ARGUMENTS: (const size_t index, const uint64_t cycle, PLEX_SPRITE* sprite, const uint64_t time)

#define PLEX_changeSpriteCycleSpeed(index, cycle, sprite, time) PLEX_changeSpriteCycleSpeedInt(index, cycle, sprite, time, __LINE__, __FILE__)

// ARGUMENTS: (const PLEX_SPRITE* sprite) - returns bool

#define PLEX_isSpriteStopped(sprite) PLEX_isSpriteStoppedInt(sprite, __LINE__, __FILE__)

// ARGUMENTS: (const size_t index, const PLEX_SPRITE* sprite) - returns uint64_t

#define PLEX_spriteCycleLen(index, sprite) PLEX_spriteCycleLenInt(index, sprite, __LINE__, __FILE__)

// ARGUMENTS: (const size_t index, const PLEX_SPRITE* a, PLEX_SPRITE* b) - returns bool

#define PLEX_syncSprites(index, a, b) PLEX_syncSpritesInt(index, a, b, __LINE__, __FILE__)

// ARGUMENTS: (const size_t index, PLEX_SPRITE* sprite) - returns PLEX_ANIMATION*

#define PLEX_getAnimation(index, sprite) PLEX_getAnimationInt(index, sprite, __LINE__, __FILE__)

// ARGUMENTS: (const PLEX_SPRITE* sprite) - returns size_t

#define PLEX_spriteTex(sprite) PLEX_spriteTexInt(sprite, __LINE__, __FILE__)

// ARGUMENTS: (const PLEX_SPRITE* sprite) - returns double

#define PLEX_spriteWPerc(sprite) PLEX_spriteWPercInt(sprite, __LINE__, __FILE__)

// ARGUMENTS: (const PLEX_SPRITE* sprite) - returns double

#define PLEX_spriteHPerc(sprite) PLEX_spriteHPercInt(sprite, __LINE__, __FILE__)

// ARGUMENTS: (const PLEX_SPRITE* sprite) - returns size_t

#define PLEX_spriteAnimationCount(sprite) PLEX_spriteAnimationCountInt(sprite, __LINE__, __FILE__)

// structs, unions, enums, function prototypes ------------------------------------------------------------------------------

typedef struct
{
	PLEX_ANIMATION_PLATE plate;
	PLEX_EXPANDARRAY* animations;
	bool stopped;
} PLEX_SPRITE;

// public functions ---------------------------------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C"
{
#endif

// specialized functions ----------------------------------------------------------------------------------------------------

	// allocate a sprite based on plate

	extern PLEX_SPRITE* PLEX_genSpriteInt(const PLEX_ANIMATION_PLATE* plate, const size_t errorline, const char* const errorfile);

	// destroy a sprite that's been allocated

	extern void PLEX_destroySpriteInt(PLEX_SPRITE** sprite, const size_t errorline, const char* const errorfile);

	// allocate a copy of a sprite

	extern PLEX_SPRITE* PLEX_copySpriteInt(const PLEX_SPRITE* const sprite, const size_t errorline, const char* const errorfile);

	// adds an animation to the sprite at duration cycle and start animation time all microseconds

	extern void PLEX_addAnimationInt(PLEX_SPRITE* sprite, const uint64_t cycle, const uint64_t start, const size_t errorline, const char* const errorfile);

	// draws sprite which means it draw the internal animation at 'index', look at drawAnimation above for more information. Also a tinted sprite draw function just like the drawAnimationTinted function.

	extern void PLEX_drawSpriteInt(const size_t order, const size_t index, const double tx, const double ty, const double tw, const double th, const PLEX_SPRITE* sprite, const bool offset, const uint64_t time, const size_t errorline, const char* const errorfile);

	// draw sprite but tinted r, g, b

	extern void PLEX_drawSpriteTintedInt(const size_t order, const size_t index, const double tx, const double ty, const double tw, const double th, const uint8_t r, const uint8_t g, const uint8_t b, const PLEX_SPRITE* sprite, const bool offset, const uint64_t time, const size_t errorline, const char* const errorfile);

	// draw a sprite rotated at the angle of 'angle'

	extern void PLEX_drawSpriteRotatedInt(const size_t order, const size_t index, const double tx, const double ty, const double tw, const double th, const double angle, const PLEX_SPRITE* sprite, const bool offset, const uint64_t time,  const size_t errorline, const char* const errorfile);

	// draw a rotate sprite that is also tinted r, g, b

	extern void PLEX_drawSpriteTintedRotatedInt(const size_t order, const size_t index, const double tx, const double ty, const double tw, const double th, const uint8_t r, const uint8_t g, const uint8_t b, const double angle, const PLEX_SPRITE* sprite, const bool offset, const uint64_t time,  const size_t errorline, const char* const errorfile);

	// starts the sprite animation cycle at 'start' microseconds

	extern void PLEX_startSpriteInt(const uint64_t start, PLEX_SPRITE* sprite, const size_t errorline, const char* const errorfile);

	// stops the sprite animation cycle

	extern void PLEX_stopSpriteInt(PLEX_SPRITE* sprite, const size_t errorline, const char* const errorfile);

	// clears the texture plate in sprite as described above in clearAnimation (clear is a way to mark a texture for possible deletion but to bring it back if it doesn't end up being deleted) (untested/experimental)

	extern void PLEX_clearSpriteInt(PLEX_SPRITE* sprite, const size_t errorline, const char* const errorfile);

	// unclears the texture plate in sprite as described above in unclearAnimation (untested/experimental)

	extern void PLEX_unclearSpriteInt(PLEX_SPRITE* sprite, const size_t errorline, const char* const errorfile);

// setters ------------------------------------------------------------------------------------------------------------------

	// changes the animation cycle speed

	extern void PLEX_changeSpriteCycleSpeedInt(const size_t index, const uint64_t cycle, PLEX_SPRITE* sprite, const uint64_t time, const size_t errorline, const char* const errorfile);

	// attempts to synchronize the animations in sprite a and b at aniIndex 'index' so they have the same cycle speed and start

	extern bool PLEX_syncSpritesInt(const size_t index, const PLEX_SPRITE* a, PLEX_SPRITE* b, const size_t errorline, const char* const errorfile);

// getters ------------------------------------------------------------------------------------------------------------------

	// returns the animation cycle in seconds of animation at 'index' in sprite

	extern uint64_t PLEX_spriteCycleLenInt(const size_t index, const PLEX_SPRITE* sprite, const size_t errorline, const char* const errorfile);

	// returns whether or not the sprite animation is stopped

	extern bool PLEX_isSpriteStoppedInt(const PLEX_SPRITE* sprite, const size_t errorline, const char* const errorfile);

	// returns the animation inside sprite at index 'index'

	extern PLEX_ANIMATION* PLEX_getAnimationInt(const size_t index, PLEX_SPRITE* sprite, const size_t errorline, const char* const errorfile);

	// gets the inner texture of a sprite's plate

	extern size_t PLEX_spriteTexInt(const PLEX_SPRITE* sprite, const size_t errorline, const char* const errorfile);

	// gets the frame width percentage of sprite's plate

	extern double PLEX_spriteWPercInt(const PLEX_SPRITE* sprite, const size_t errorline, const char* const errorfile);

	// gets the frame height percentage of sprite's plate

	extern double PLEX_spriteHPercInt(const PLEX_SPRITE* sprite, const size_t errorline, const char* const errorfile);

	// get the number of animations in a sprite

	extern size_t PLEX_spriteAnimationCountInt(const PLEX_SPRITE* sprite, const size_t errorline, const char* const errorfile);

#ifdef __cplusplus
}
#endif

#endif
