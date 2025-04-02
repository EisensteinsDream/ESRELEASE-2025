#ifndef PLEX_SCREENEFFECT_H
#define PLEX_SCREENEFFECT_H

#include "windowing/sprite.h"

// this unit controls graphical screen effects that show on the screen over time. At the moment there aren't many but there will be more.

// NOTE: This is a unit with a state machine affiliated therefore has a start, update, and end function. Some functions will not work if the 'start' function is not called successfully. PLEX_start, PLEX_update, and PLEX_end should call the start, update, and end functions of the state machine so they don't need to be called manually.

// macro functions and macros -----------------------------------------------------------------------------------------------

// ARGUMENTS: (const PLEX_SCREENEFFECT_TYPE type, const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a, const bool loop, const bool screenOffset, const uint64_t duration, const double minPerc, const uint64_t time) - returns int64_t

#define PLEX_doScreenEffect(type, r, g, b, a, loop, screenOffset, duration, minPerc, time) PLEX_doScreenEffectInt(type, r, g, b, a, loop, screenOffset, duration, minPerc, time, __LINE__, __FILE__)

// ARGUMENTS: (const PLEX_SCREENEFFECT_TYPE type, const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a, const bool loop, const bool screenOffset, const uint64_t duration, const double minPerc, const PLEX_RECT range, const uint64_t time) - returns int64_t

#define PLEX_doScreenEffectRanged(type, r, g, b, a, loop, screenOffset, duration, minPerc, range, time) PLEX_doScreenEffectRangedInt(type, r, g, b, a, loop, screenOffset, duration, minPerc, range, time, __LINE__, __FILE__)

// ARGUMENTS: (const size_t index)

#define PLEX_hideScreenEffect(index) PLEX_hideScreenEffectInt(index, __LINE__, __FILE__)

// ARGUMENTS: (const size_t index)

#define PLEX_unhideScreenEffect(index) PLEX_unhideScreenEffectInt(index,__LINE__, __FILE__)

// ARGUMENTS: (const int64_t index, const uint64_t time)

#define PLEX_ceaseScreenEffect(index) PLEX_ceaseScreenEffectInt(index, __LINE__, __FILE__)

// ARGUMENTS: (PLEX_SPRITE* sprite, const size_t aniIndex, const size_t index, const uint64_t time)

#define PLEX_seedSprite(sprite, aniIndex, index, time) PLEX_seedSpriteInt(sprite, aniIndex, index, time, __LINE__, __FILE__)

// ARGUMENTS: (const size_t index, const PLEX_RECT range)

#define PLEX_repositionScreenEffect(index, range) PLEX_repositionScreenEffectInt(index, range, __LINE__, __FILE__)

// ARGUMENTS: (const size_t index, const size_t drawLayer)

#define PLEX_screenEffectDrawLayer(index, drawLayer) PLEX_screenEffectDrawLayerInt(index, drawLayer, __LINE__, __FILE__)

// ARGUMENTS: (const uint64_t time) - returns bool

#define PLEX_startScreenEffects(time) PLEX_startScreenEffectsInt(time, __LINE__, __FILE__)

// ARGUMENTS: (const uint64_t time) - returns bool

#define PLEX_updateScreenEffects(time) PLEX_updateScreenEffectsInt(time, __LINE__, __FILE__)

// NO ARGUMENTS

#define PLEX_endScreenEffects() PLEX_endScreenEffectsInt(__LINE__, __FILE__)

// ARGUMENTS: (const int64_t index, const uint64_t time) - returns bool

#define PLEX_screenEffectOver(index, time) PLEX_screenEffectOverInt(index, time, __LINE__, __FILE__)

// ARGUMENTS: (const int64_t index) - return bool

#define PLEX_screenEffectHidden(index) PLEX_screenEffectHiddenInt(index, __LINE__, __FILE__)

// structs, unions, enums, function prototypes ------------------------------------------------------------------------------

typedef enum
{
	PLEX_SCREENEFFECT_TINTFADE = 0,
	PLEX_SCREENEFFECT_SPLATTER = 1,
	PLEX_SCREENEFFECT_TINT = 2,
	PLEX_SCREENEFFECT_RAIN = 3,
	PLEX_SCREENEFFECT_SNOW = 4,
	PLEX_SCREENEFFECT_WIND = 5,
	PLEX_SCREENEFFECT_PROJECTILERAIN = 6,
	PLEX_SCREENEFFECT_PAINTOVER = 7,
	PLEX_SCREENEFFECT_SMOKE = 8,
	PLEX_SCREENEFFECT_LASERSHOW = 9
} PLEX_SCREENEFFECT_TYPE;

// public functions ---------------------------------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C"
{
#endif
// specialized functions ----------------------------------------------------------------------------------------------------

	// does a screen effect over the entire screen

	extern int64_t PLEX_doScreenEffectInt(const PLEX_SCREENEFFECT_TYPE type, const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a, const bool loop, const bool screenOffset, const uint64_t duration, const double minPerc, const uint64_t time, const size_t errorline, const char* const errorfile);

	// does a screen effect within a ranged area

	extern int64_t PLEX_doScreenEffectRangedInt(const PLEX_SCREENEFFECT_TYPE type, const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a, const bool loop, const bool screenOffset, const uint64_t duration, const double minPerc, const PLEX_RECT range, const uint64_t time, const size_t errorline, const char* const errorfile);

	// hides screen effect at index

	extern void PLEX_hideScreenEffectInt(const int64_t index, const size_t errorline, const char* const errorfile);

	// unhides screen effect at index

	extern void PLEX_unhideScreenEffectInt(const int64_t index, const size_t errorline, const char* const errorfile);

	// kills screen effect at index, setting it to be recycled

	extern void PLEX_ceaseScreenEffectInt(const int64_t index, const size_t errorline, const char* const errorfile);

	// seeds the sprite to an effect, some effects need sprites to draw.

	extern void PLEX_seedSpriteInt(PLEX_SPRITE* sprite, const size_t aniIndex, const size_t index, const uint64_t time, const size_t errorline, const char* const errorfile);

	// change the 'range' of a screen effect, setting it to 'ranged' if it's not already set that way

	extern void PLEX_repositionScreenEffectInt(const size_t index, const PLEX_RECT range, const size_t errorline, const char* const errorfile);

	// change the 'draw layer' of a screen effect. Screeneffects still overlay the screen but this prevents it from overlaying other screen effects. The higher the number the further from the user it's drawn.

	extern void PLEX_screenEffectDrawLayerInt(const size_t index, const size_t drawLayer, const size_t errorline, const char* const errorfile);

// start, update, end functions ---------------------------------------------------------------------------------------------

	// starts the screen effect subsystem. You don't need to manually call this as it's called in PLEX_start. On returning false will likely terminate the program.

	extern bool PLEX_startScreenEffectsInt(const uint64_t time, const size_t errorline, const char* const errorfile);

	// updates the screen effect subsystem. You don't need to manually call this as it's called in PLEX_update. On returning false will likely terminate the program.

	extern bool PLEX_updateScreenEffectsInt(const uint64_t time, const size_t errorline, const char* const errorfile);

	// ends the screen effect subsystem. You don't need to manually call this as it's called in PLEX_end.

	extern void PLEX_endScreenEffectsInt(const size_t errorline, const char* const errorfile);

// setters ------------------------------------------------------------------------------------------------------------------

	// disables or enables screen effects

	extern void PLEX_disableScreenEffects();
	extern void PLEX_enableScreenEffects();

// getters ------------------------------------------------------------------------------------------------------------------

	// returns whether or not screen effect is hidden

	extern bool PLEX_screenEffectHiddenInt(const int64_t index, const size_t errorline, const char* const errorfile);

	// returns whether or not a screen effect is over

	extern bool PLEX_screenEffectOverInt(const int64_t index, const uint64_t time, const size_t errorline, const char* const errorfile);

	// returns whether or not screen effects are disabled

	extern bool PLEX_screenEffectsDisabled();
#ifdef __cplusplus
}
#endif

#endif
