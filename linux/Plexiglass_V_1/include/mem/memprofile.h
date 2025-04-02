#ifndef PLEX_MEMPROFILE_H
#define PLEX_MEMPROFILE_H

#include "meta/cinclude.h"

// This is basically a unit that handles the default amount of memory allocated dependent on the memory profile 0-3 set in the config file. No reason to manually run any of the functions in this unit as PLEX automatically handles all of it.

// NOTE: This is an independent unit. Not a unit with an accompanying state machine. It has no 'start, update, or end' functions that need to be called to operate.

// macro functions and macros -----------------------------------------------------------------------------------------------

// MEMORY

#define PLEX_MEMLIMIT_MEM_PRELOAD_LOW 16
#define PLEX_MEMLIMIT_MEM_PRELOAD_MEDIUM 64
#define PLEX_MEMLIMIT_MEM_PRELOAD_HIGH 256
#define PLEX_MEMLIMIT_MEM_PRELOAD_VERYHIGH 1024

#define PLEX_MEMLIMIT_MEM_REUSE_LOW 8
#define PLEX_MEMLIMIT_MEM_REUSE_MEDIUM 16
#define PLEX_MEMLIMIT_MEM_REUSE_HIGH 128
#define PLEX_MEMLIMIT_MEM_REUSE_VERYHIGH 512

// EXPAND ARRAY

#define PLEX_MEMLIMIT_EXPANDCAP_REUSE_LOW 8
#define PLEX_MEMLIMIT_EXPANDCAP_REUSE_MEDIUM 16
#define PLEX_MEMLIMIT_EXPANDCAP_REUSE_HIGH 128
#define PLEX_MEMLIMIT_EXPANDCAP_REUSE_VERYHIGH 256

// DEFAULTS

#define PLEX_MEMLIMIT_DEFAULTS_DEFAULTS_LOW 16
#define PLEX_MEMLIMIT_DEFAULTS_DEFAULTS_MEDIUM 24
#define PLEX_MEMLIMIT_DEFAULTS_DEFAULTS_HIGH 64
#define PLEX_MEMLIMIT_DEFAULTS_DEFAULTS_VERYHIGH 128

// GRAPHICS

#define PLEX_MEMLIMIT_GRAPHICS_DRAWLIST_LOW 128
#define PLEX_MEMLIMIT_GRAPHICS_DRAWLIST_MEDIUM 512
#define PLEX_MEMLIMIT_GRAPHICS_DRAWLIST_HIGH 1024
#define PLEX_MEMLIMIT_GRAPHICS_DRAWLIST_VERYHIGH 2048

#define PLEX_MEMLIMIT_ANIMATION_FRAMEPRELOAD_LOW 8
#define PLEX_MEMLIMIT_ANIMATION_FRAMEPRELOAD_MEDIUM 16
#define PLEX_MEMLIMIT_ANIMATION_FRAMEPRELOAD_HIGH 32
#define PLEX_MEMLIMIT_ANIMATION_FRAMEPRELOAD_VERYHIGH 128

#define PLEX_MEMLIMIT_SPRITE_ANIMATIONMAX_LOW 4
#define PLEX_MEMLIMIT_SPRITE_ANIMATIONMAX_MEDIUM 8
#define PLEX_MEMLIMIT_SPRITE_ANIMATIONMAX_HIGH 32
#define PLEX_MEMLIMIT_SPRITE_ANIMATIONMAX_VERYHIGH 128

#define PLEX_MEMLIMIT_SCREENEFFECT_LOW 4
#define PLEX_MEMLIMIT_SCREENEFFECT_MEDIUM 8
#define PLEX_MEMLIMIT_SCREENEFFECT_HIGH 32
#define PLEX_MEMLIMIT_SCREENEFFECT_VERYHIGH 128

// TEXTURE

#define PLEX_MEMLIMIT_TEXTURE_TEXTUREPRELOAD_LOW 8
#define PLEX_MEMLIMIT_TEXTURE_TEXTUREPRELOAD_MEDIUM 32
#define PLEX_MEMLIMIT_TEXTURE_TEXTUREPRELOAD_HIGH 128
#define PLEX_MEMLIMIT_TEXTURE_TEXTUREPRELOAD_VERYHIGH 256

// FILE PARSING

#define PLEX_MEMLIMIT_FILEPARSE_LINELIMIT_LOW 4
#define PLEX_MEMLIMIT_FILEPARSE_LINELIMIT_MEDIUM 16
#define PLEX_MEMLIMIT_FILEPARSE_LINELIMIT_HIGH 32
#define PLEX_MEMLIMIT_FILEPARSE_LINELIMIT_VERYHIGH 128

#define PLEX_MEMLIMIT_FILEPARSE_TOKENLIMIT_LOW 4
#define PLEX_MEMLIMIT_FILEPARSE_TOKENLIMIT_MEDIUM 8
#define PLEX_MEMLIMIT_FILEPARSE_TOKENLIMIT_HIGH 16
#define PLEX_MEMLIMIT_FILEPARSE_TOKENLIMIT_VERYHIGH 128

// SPRITE THEATER

#define PLEX_MEMLIMIT_SPRITETHEATER_SLIDE_LOW 4
#define PLEX_MEMLIMIT_SPRITETHEATER_SLIDE_MEDIUM 8
#define PLEX_MEMLIMIT_SPRITETHEATER_SLIDE_HIGH 32
#define PLEX_MEMLIMIT_SPRITETHEATER_SLIDE_VERYHIGH 128

#define PLEX_MEMLIMIT_SPRITETHEATER_ACTOR_LOW 4
#define PLEX_MEMLIMIT_SPRITETHEATER_ACTOR_MEDIUM 8
#define PLEX_MEMLIMIT_SPRITETHEATER_ACTOR_HIGH 32
#define PLEX_MEMLIMIT_SPRITETHEATER_ACTOR_VERYHIGH 128

#define PLEX_MEMLIMIT_SPRITETHEATER_ACTIONCHANGE_LOW 4
#define PLEX_MEMLIMIT_SPRITETHEATER_ACTIONCHANGE_MEDIUM 8
#define PLEX_MEMLIMIT_SPRITETHEATER_ACTIONCHANGE_HIGH 32
#define PLEX_MEMLIMIT_SPRITETHEATER_ACTIONCHANGE_VERYHIGH 128

#define PLEX_MEMLIMIT_SPRITETHEATER_MUSICCHANGE_LOW 4
#define PLEX_MEMLIMIT_SPRITETHEATER_MUSICCHANGE_MEDIUM 8
#define PLEX_MEMLIMIT_SPRITETHEATER_MUSICCHANGE_HIGH 32
#define PLEX_MEMLIMIT_SPRITETHEATER_MUSICCHANGE_VERYHIGH 128

// GENERATOR

#define PLEX_MEMLIMIT_GENERATOR_GENSTART_LOW 8
#define PLEX_MEMLIMIT_GENERATOR_GENSTART_MEDIUM 16
#define PLEX_MEMLIMIT_GENERATOR_GENSTART_HIGH 32
#define PLEX_MEMLIMIT_GENERATOR_GENSTART_VERYHIGH 128

// PROMINENCE MACHINE

#define PLEX_MEMLIMIT_PROMINENCEMACHINE_PROMPRELOAD_LOW 8
#define PLEX_MEMLIMIT_PROMINENCEMACHINE_PROMPRELOAD_MEDIUM 16
#define PLEX_MEMLIMIT_PROMINENCEMACHINE_PROMPRELOAD_HIGH 32
#define PLEX_MEMLIMIT_PROMINENCEMACHINE_PROMPRELOAD_VERYHIGH 128

// public functions ---------------------------------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C"
{
#endif
// setters ------------------------------------------------------------------------------------------------------------------

	// sets the memory profile from 0-3 with 3 being the most memory allocation

	extern void PLEX_setMemProfile(const uint8_t profile);

// getters ------------------------------------------------------------------------------------------------------------------

	// returns how much memory is preloaded for the internal memory

	extern size_t PLEX_getMemProfilePreload();

	// returns how much memory is allocated for expanding recycled memory

	extern size_t PLEX_getMemProfileMemReuse();

	// returns how much memory is preloaded for the internal protoarray allocation

	extern size_t PLEX_getMemProfileExpandArrayCap();

	// returns how much memory is preloaded for the internal default stack

	extern size_t PLEX_getMemProfileDefaultPreload();

	// returns how much memory is preloaded for the internal draw list

	extern size_t PLEX_getMemProfileDrawlistPreload();

	// returns how much memory is preloaded for the allocation of frames in a new animation

	extern size_t PLEX_getMemProfileFramePreload();

	// returns how much memory is preloaded for the allocation of animations in a new sprite

	extern size_t PLEX_getMemProfileAnimationPreload();

	// returns how much memory is preloaded for the internal screen effects stack

	extern size_t PLEX_getMemProfileScreenEffectsPreload();

	// returns how much memory is preloaded for the allocation of internal texture stack

	extern size_t PLEX_getMemProfileTexturePreload();

	// returns how much memory is preloaded for lines in a new file

	extern size_t PLEX_getMemProfileLineParsePreload();

	// returns how much memory is preloaded for tokens in a new line

	extern size_t PLEX_getMemProfileTokenPreload();

	// returns how much memory is preloaded for slides in the sprite theater

	extern size_t PLEX_getMemProfileSpriteTheaterSlide();

	// returns how much memory is preloaded for actors in the sprite theater

	extern size_t PLEX_getMemProfileActor();

	// returns how much memory is preloaded for action changes in the sprite theater

	extern size_t PLEX_getMemProfileActionChange();

	// returns how much memory is preloaded for music changes in the sprite theater

	extern size_t PLEX_getMemProfileMusicChange();

	// returns how much memory is preloaded for generated values in a generator

	extern size_t PLEX_getMemProfileGenStart();

	// returns how much memory is preloaded for prominence values in a prominence machine

	extern size_t PLEX_getMemProfilePromPreload();

#ifdef __cplusplus
}
#endif


#endif
