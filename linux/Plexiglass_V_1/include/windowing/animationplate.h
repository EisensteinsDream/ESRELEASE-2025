#ifndef PLEX_ANIMATIONPLATE_H
#define PLEX_ANIMATIONPLATE_H

// This is the animation plate unit. Animation plates contain the basic data an animation needs to decide where the frames are located. In order to generate a new animation (or sprite for that matter) it must be passed an animation plate. Animation plates are not expected to be allocated on the heap and contain no pointers or abstract data. They do not need to be allocated or free'd.

#include "windowing/graphics.h"

// macro functions and macros -----------------------------------------------------------------------------------------------

// ARGUMENTS: (const double wPerc, const double hPerc, const size_t base) - returns PLEX_ANIMATION_PLATE

#define PLEX_createAnimationPlate(wPerc, hPerc, base) PLEX_createAnimationPlateInt(wPerc, hPerc, base, __LINE__, __FILE__)

// ARGUMENTS: (PLEX_ANIMATION_PLATE* plate)

#define PLEX_clearAnimationPlate(plate) PLEX_clearAnimationPlateInt(plate, __LINE__, __FILE__)

// ARGUMENTS: (PLEX_ANIMATION_PLATE* plate)

#define PLEX_unclearAnimationPlate(plate) PLEX_unclearAnimationPlateInt(plate, __LINE__, __FILE__)

// ARGUMENTS: (PLEX_ANIMATION_PLATE* plate)

#define PLEX_destroyAnimationPlate(plate) PLEX_destroyAnimationPlateInt(plate, __LINE__, __FILE__)

// structs, unions, enums, function prototypes ------------------------------------------------------------------------------

typedef struct
{
	size_t base;
	uint32_t fw, fh, wcount;
	double wperc, hperc;
} PLEX_ANIMATION_PLATE;

// public functions ---------------------------------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C"
{
#endif

// specialized functions ----------------------------------------------------------------------------------------------------

	// creates an animation plate based off image index 'base' and then frame width by percentage.

	extern PLEX_ANIMATION_PLATE PLEX_createAnimationPlateInt(const double wPerc, const double hPerc, const size_t base, const size_t errorline, const char* const errorfile);

	// clears the texture inside an animation plate. clearing/unclearing explained more clearly in texture.h (untested/experimental)

	extern void PLEX_clearAnimationPlateInt(PLEX_ANIMATION_PLATE* plate, const size_t errorline, const char* const errorfile);

	// unclears the texture inside an animation plate. clearing/unclearing explained more clearly in texture.h (untested/experimental)

	extern void PLEX_unclearAnimationPlateInt(PLEX_ANIMATION_PLATE* plate, const size_t errorline, const char* const errorfile);

	// destroys the texture inside animation plate.

	extern void PLEX_destroyAnimationPlateInt(PLEX_ANIMATION_PLATE** plate, const size_t errorline, const char* const errorfile);

// getters ------------------------------------------------------------------------------------------------------------------

	// gets the inner texture of a plate

	extern size_t PLEX_animationPlateTex(const PLEX_ANIMATION_PLATE plate);

	// gets the frame width of an animation plate

	extern size_t PLEX_animationPlateFW(const PLEX_ANIMATION_PLATE plate);

	// gets the frame height of an animation plate

	extern size_t PLEX_animationPlateFH(const PLEX_ANIMATION_PLATE plate);

	// gets the width count (how many frames within the width of the contained texture)

	extern size_t PLEX_animationPlateWCount(const PLEX_ANIMATION_PLATE plate);

	// gets the frame width percentage of plate

	extern double PLEX_animationPlateWPerc(const PLEX_ANIMATION_PLATE plate);

	// gets the frame height percentage of plate

	extern double PLEX_animationPlateHPerc(const PLEX_ANIMATION_PLATE plate);

#ifdef __cplusplus
}
#endif

#endif
