#ifndef PLEX_ANIMATION_H
#define PLEX_ANIMATION_H

// This unit contains animations. The animations themselves have a variable amounts of frames, custom cycle length. They can also be drawn tinted or at different sizes multiple times. In most cases you won't access these directly except for to add frames, and to do that you want to draw the animations from a generated sprite. More information in 'window/sprite.h'

// NOTE: This is an independent unit. Not a unit with an accompanying state machine. It has no 'start, update, or end' functions that need to be called to operate.

#include "windowing/animationplate.h"

// macro functions and macros -----------------------------------------------------------------------------------------------

// ARGUMENTS: (const size_t order, const double tx, const double ty, const double tw, const double th, const PLEX_ANIMATION* animation, const PLEX_ANIMATION_PLATE plate, const uint64_t time, const bool offset)

#define PLEX_drawFrame(order, tx, ty, tw, th, animation, plate, offset, time) PLEX_drawFrameInt(order, tx, ty, tw, th, animation, plate, offset, time, __LINE__, __FILE__)

// ARGUMENTS: (const size_t order, const double tx, const double ty, const double tw, const double th, const uint8_t r, const uint8_t g, const uint8_t b, const PLEX_ANIMATION* animation, const PLEX_ANIMATION_PLATE plate, const uint64_t time, const bool offset)

#define PLEX_drawFrameTinted(order, tx, ty, tw, th, r, g, b, animation, plate, offset, time) PLEX_drawFrameTintedInt(order, tx, ty, tw, th, r, g, b, animation, plate, offset, time, __LINE__, __FILE__)

// ARGUMENTS: (const size_t order, const double tx, const double ty, const double tw, const double th, const PLEX_ANIMATION* animation, const PLEX_ANIMATION_PLATE plate, const double angle, const uint64_t time, const bool offset)

#define PLEX_drawFrameRotate(order, tx, ty, tw, th, animation, plate, angle, time, offset) PLEX_drawFrameRotateInt(order, tx, ty, tw, th, animation, plate, angle, time, offset, __LINE__, __FILE__)

// ARGUMENTS: (const size_t order, const double tx, const double ty, const double tw, const double th, const PLEX_ANIMATION* animation, const PLEX_ANIMATION_PLATE plate, const uint8_t r, const uint8_t g, const uint8_t b, const double angle, const uint64_t time, const bool offset)

#define PLEX_drawFrameRotateTinted(order, tx, ty, tw, th, animation, plate, angle, r, g, b, time, offset) PLEX_drawFrameRotateTintedInt(order, tx, ty, tw, th, animation, plate, angle, r, g, b, time, offset, __LINE__, __FILE__)

// ARGUMENTS: (const size_t frame, PLEX_ANIMATION* animation)

#define PLEX_addAnimationFrame(frame, animation) PLEX_addAnimationFrameInt(frame, animation, __LINE__, __FILE__)

// ARGUMENTS: (const uint64_t start, PLEX_ANIMATION* animation)

#define PLEX_startAnimation(start, animation) PLEX_startAnimationInt(start, animation, __LINE__, __FILE__)

// ARGUMENTS: (PLEX_ANIMATION* animation)

#define PLEX_stopAnimation(animation) PLEX_stopAnimationInt(animation, __LINE__, __FILE__)

// ARGUMENTS: (const uint64_t cycle, PLEX_ANIMATION* animation, const uint64_t time)

#define PLEX_changeAnimationCycleSpeed(cycle, animation, time) PLEX_changeAnimationCycleSpeedInt(cycle, animation, time, __LINE__, __FILE__)

// ARGUMENTS: (const PLEX_ANIMATION a, PLEX_ANIMATION* b) - returns bool

#define PLEX_syncAnimations(a, b) PLEX_syncAnimationsInt(a, b, __LINE__, __FILE__)

// ARGUMENTS: (uint32_t* x, uint32_t* y, uint32_t* w, uint32_t* h, const PLEX_ANIMATION* animation, const PLEX_ANIMATION_PLATE plate, const uint64_t time) - returns size_t

#define PLEX_getFrame(x, y, w, h, animation, plate, time) PLEX_getFrameInt(x, y, w, h, animation, plate, time, __LINE__, __FILE__)

// ARGUMENTS: (const PLEX_ANIMATION* animation) - returns bool

#define PLEX_isAnimationStopped(animation) PLEX_isAnimationStoppedInt(animation, __LINE__, __FILE__)

// ARGUMENTS: (const PLEX_ANIMATION* animation) - returns uint64_t

#define PLEX_animationCycleLen(animation) PLEX_animationCycleLenInt(animation, __LINE__, __FILE__)

// ARGUMENTS: (const PLEX_ANIMATION* animation) - returns uint64_t

#define PLEX_animationStartLen(animation) PLEX_animationStartLenInt(animation, __LINE__, __FILE__)

// ARGUMENTS: (const PLEX_ANIMATION* animation) - returns size_t

#define PLEX_animationFrameCount(animation) PLEX_animationFrameCountInt(animation, __LINE__, __FILE__)

// structs, unions, enums, function prototypes ------------------------------------------------------------------------------

typedef struct
{
	PLEX_EXPANDARRAY* frames;
	uint64_t cycle, start;
	bool stopped;
} PLEX_ANIMATION;

// public functions ---------------------------------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C"
{
#endif

// specialized functions ----------------------------------------------------------------------------------------------------

	// draws a frame of an animation to tx, ty, tw, th

	extern void PLEX_drawFrameInt(const size_t order, const double tx, const double ty, const double tw, const double th, const PLEX_ANIMATION* animation, const PLEX_ANIMATION_PLATE plate, const bool offset, const uint64_t time,  const size_t errorline, const char* const errorfile);

	// draws a frame of an animation to tx, ty, tw, th and tinted r, g, b

	extern void PLEX_drawFrameTintedInt(const size_t order, const double tx, const double ty, const double tw, const double th, const uint8_t r, const uint8_t g, const uint8_t b, const PLEX_ANIMATION* animation, const PLEX_ANIMATION_PLATE plate, const bool offset, const uint64_t time,  const size_t errorline, const char* const errorfile);

	// draws a frame of animation to tx, ty, tw, th and rotated at the degree of 'angle'

	extern void PLEX_drawFrameRotateInt(const size_t order, const double tx, const double ty, const double tw, const double th, const PLEX_ANIMATION* animation, const PLEX_ANIMATION_PLATE plate, const double angle, const bool offset, const uint64_t time,  const size_t errorline, const char* const errorfile);

	// draws a frame of animation to tx, ty, tw, th and rotated at the degree of 'angle' plus tinted r, g, b

	extern void PLEX_drawFrameRotateTintedInt(const size_t order, const double tx, const double ty, const double tw, const double th, const PLEX_ANIMATION* animation, const PLEX_ANIMATION_PLATE plate, const uint8_t r, const uint8_t g, const uint8_t b, const double angle, const bool offset, const uint64_t time,  const size_t errorline, const char* const errorfile);

	// adds the texture 'frame' to the animation.

	extern void PLEX_addAnimationFrameInt(const size_t frame, PLEX_ANIMATION* animation, const size_t errorline, const char* const errorfile);

	// starts animation at microsecond time 'start'

	extern void PLEX_startAnimationInt(const uint64_t start, PLEX_ANIMATION* animation, const size_t errorline, const char* const errorfile);

	// stops animation

	extern void PLEX_stopAnimationInt(PLEX_ANIMATION* animation, const size_t errorline, const char* const errorfile);

// setters ------------------------------------------------------------------------------------------------------------------

	// changes the animation cycle speed

	extern void PLEX_changeAnimationCycleSpeedInt(const uint64_t cycle, PLEX_ANIMATION* animation, const uint64_t time, const size_t errorline, const char* const errorfile);

	// synchronizes two animations so that they start at the same place and have the same cycle speed

	extern bool PLEX_syncAnimationsInt(const PLEX_ANIMATION a, PLEX_ANIMATION* b, const size_t errorline, const char* const errorfile);

// getters ------------------------------------------------------------------------------------------------------------------

	// gets the internal x, y, w, h for the current frame of the animation

	extern size_t PLEX_getFrameInt(uint32_t* x, uint32_t* y, uint32_t* w, uint32_t* h, const PLEX_ANIMATION* animation, const PLEX_ANIMATION_PLATE plate, const uint64_t time, const size_t errorline, const char* const errorfile);

	// returns whether or not the animation is stopped

	extern bool PLEX_isAnimationStoppedInt(const PLEX_ANIMATION* animation, const size_t errorline, const char* const errorfile);

	// returns the entire microsecond length of the animation cycle

	extern uint64_t PLEX_animationCycleLenInt(const PLEX_ANIMATION* animation, const size_t errorline, const char* const errorfile);

	// returns the start of the animation in microseconds

	extern uint64_t PLEX_animationStartLenInt(const PLEX_ANIMATION* animation, const size_t errorline, const char* const errorfile);

	// returns the number of frames in an animation

	extern size_t PLEX_animationFrameCountInt(const PLEX_ANIMATION* animation, const size_t errorline, const char* const errorfile);

#ifdef __cplusplus
}
#endif

#endif
