#include "mem/memprofile.h"

// NOTE: global function descriptions in header.

// structs ------------------------------------------------------------------------------------------------------------------

typedef enum
{
	P_MEMPROFILE_LOW = 0,
	P_MEMPROFILE_MEDIUM = 1,
	P_MEMPROFILE_HIGH = 2,
	P_MEMPROFILE_VERYHIGH = 3
} P_MEMPROFILE;

// static values ------------------------------------------------------------------------------------------------------------

static P_MEMPROFILE p_profile = P_MEMPROFILE_LOW;

// setters ------------------------------------------------------------------------------------------------------------------

void PLEX_setMemProfile(const uint8_t profile)
{
	p_profile = P_MEMPROFILE_LOW;

	switch(profile)
	{
		case 1: p_profile = P_MEMPROFILE_MEDIUM; return;
		case 2: p_profile = P_MEMPROFILE_HIGH; return;
		case 3: p_profile = P_MEMPROFILE_VERYHIGH; return;
	};
}

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

// getters ------------------------------------------------------------------------------------------------------------------

size_t PLEX_getMemProfilePreload()
{
	switch(p_profile)
	{
		case P_MEMPROFILE_MEDIUM: return PLEX_MEMLIMIT_MEM_PRELOAD_MEDIUM;
		case P_MEMPROFILE_HIGH: return PLEX_MEMLIMIT_MEM_PRELOAD_HIGH;
		case P_MEMPROFILE_VERYHIGH: return PLEX_MEMLIMIT_MEM_PRELOAD_VERYHIGH;
		default: break;
	};

	return PLEX_MEMLIMIT_MEM_PRELOAD_LOW;
}

size_t PLEX_getMemProfileMemReuse()
{
	switch(p_profile)
	{
		case P_MEMPROFILE_MEDIUM: return PLEX_MEMLIMIT_MEM_REUSE_MEDIUM;
		case P_MEMPROFILE_HIGH: return PLEX_MEMLIMIT_MEM_REUSE_HIGH;
		case P_MEMPROFILE_VERYHIGH: return PLEX_MEMLIMIT_MEM_REUSE_VERYHIGH;
		default: break;
	};

	return PLEX_MEMLIMIT_MEM_REUSE_LOW;
}

size_t PLEX_getMemProfileExpandArrayCap()
{
	switch(p_profile)
	{
		case P_MEMPROFILE_MEDIUM: return PLEX_MEMLIMIT_EXPANDCAP_REUSE_MEDIUM;
		case P_MEMPROFILE_HIGH: return PLEX_MEMLIMIT_EXPANDCAP_REUSE_HIGH;
		case P_MEMPROFILE_VERYHIGH: return PLEX_MEMLIMIT_EXPANDCAP_REUSE_VERYHIGH;
		default: break;
	};

	return PLEX_MEMLIMIT_EXPANDCAP_REUSE_LOW;
}

size_t PLEX_getMemProfileDefaultPreload()
{
	switch(p_profile)
	{
		case P_MEMPROFILE_MEDIUM: return PLEX_MEMLIMIT_DEFAULTS_DEFAULTS_MEDIUM;
		case P_MEMPROFILE_HIGH: return PLEX_MEMLIMIT_DEFAULTS_DEFAULTS_HIGH;
		case P_MEMPROFILE_VERYHIGH: return PLEX_MEMLIMIT_DEFAULTS_DEFAULTS_VERYHIGH;
		default: break;
	};

	return PLEX_MEMLIMIT_DEFAULTS_DEFAULTS_LOW;
}

size_t PLEX_getMemProfileDrawlistPreload()
{
	switch(p_profile)
	{
		case P_MEMPROFILE_MEDIUM: return PLEX_MEMLIMIT_GRAPHICS_DRAWLIST_MEDIUM;
		case P_MEMPROFILE_HIGH: return PLEX_MEMLIMIT_GRAPHICS_DRAWLIST_HIGH;
		case P_MEMPROFILE_VERYHIGH: return PLEX_MEMLIMIT_GRAPHICS_DRAWLIST_VERYHIGH;
		default: break;
	};

	return PLEX_MEMLIMIT_GRAPHICS_DRAWLIST_LOW;
}

size_t PLEX_getMemProfileFramePreload()
{
	switch(p_profile)
	{
		case P_MEMPROFILE_MEDIUM: return PLEX_MEMLIMIT_ANIMATION_FRAMEPRELOAD_MEDIUM;
		case P_MEMPROFILE_HIGH: return PLEX_MEMLIMIT_ANIMATION_FRAMEPRELOAD_HIGH;
		case P_MEMPROFILE_VERYHIGH: return PLEX_MEMLIMIT_ANIMATION_FRAMEPRELOAD_VERYHIGH;
		default: break;
	};

	return PLEX_MEMLIMIT_ANIMATION_FRAMEPRELOAD_LOW;
}

size_t PLEX_getMemProfileAnimationPreload()
{
	switch(p_profile)
	{
		case P_MEMPROFILE_MEDIUM: return PLEX_MEMLIMIT_SPRITE_ANIMATIONMAX_MEDIUM;
		case P_MEMPROFILE_HIGH: return PLEX_MEMLIMIT_SPRITE_ANIMATIONMAX_HIGH;
		case P_MEMPROFILE_VERYHIGH: return PLEX_MEMLIMIT_SPRITE_ANIMATIONMAX_VERYHIGH;
		default: break;
	};

	return PLEX_MEMLIMIT_SPRITE_ANIMATIONMAX_LOW;
}

size_t PLEX_getMemProfileScreenEffectsPreload()
{
	switch(p_profile)
	{
		case P_MEMPROFILE_MEDIUM: return PLEX_MEMLIMIT_SCREENEFFECT_MEDIUM;
		case P_MEMPROFILE_HIGH: return PLEX_MEMLIMIT_SCREENEFFECT_HIGH;
		case P_MEMPROFILE_VERYHIGH: return PLEX_MEMLIMIT_SCREENEFFECT_VERYHIGH;
		default: break;
	};

	return PLEX_MEMLIMIT_SCREENEFFECT_LOW;
}

size_t PLEX_getMemProfileTexturePreload()
{
	switch(p_profile)
	{
		case P_MEMPROFILE_MEDIUM: return PLEX_MEMLIMIT_TEXTURE_TEXTUREPRELOAD_MEDIUM;
		case P_MEMPROFILE_HIGH: return PLEX_MEMLIMIT_TEXTURE_TEXTUREPRELOAD_HIGH;
		case P_MEMPROFILE_VERYHIGH: return PLEX_MEMLIMIT_TEXTURE_TEXTUREPRELOAD_VERYHIGH;
		default: break;
	};

	return PLEX_MEMLIMIT_TEXTURE_TEXTUREPRELOAD_LOW;
}

size_t PLEX_getMemProfileLineParsePreload()
{
	switch(p_profile)
	{
		case P_MEMPROFILE_MEDIUM: return PLEX_MEMLIMIT_FILEPARSE_LINELIMIT_MEDIUM;
		case P_MEMPROFILE_HIGH: return PLEX_MEMLIMIT_FILEPARSE_LINELIMIT_HIGH;
		case P_MEMPROFILE_VERYHIGH: return PLEX_MEMLIMIT_FILEPARSE_LINELIMIT_VERYHIGH;
		default: break;
	};

	return PLEX_MEMLIMIT_FILEPARSE_LINELIMIT_LOW;
}

size_t PLEX_getMemProfileTokenPreload()
{
	switch(p_profile)
	{
		case P_MEMPROFILE_MEDIUM: return PLEX_MEMLIMIT_FILEPARSE_TOKENLIMIT_MEDIUM;
		case P_MEMPROFILE_HIGH: return PLEX_MEMLIMIT_FILEPARSE_TOKENLIMIT_HIGH;
		case P_MEMPROFILE_VERYHIGH: return PLEX_MEMLIMIT_FILEPARSE_TOKENLIMIT_VERYHIGH;
		default: break;
	};

	return PLEX_MEMLIMIT_FILEPARSE_TOKENLIMIT_LOW;
}

size_t PLEX_getMemProfileSpriteTheaterSlide()
{
	switch(p_profile)
	{
		case P_MEMPROFILE_MEDIUM: return PLEX_MEMLIMIT_SPRITETHEATER_SLIDE_MEDIUM;
		case P_MEMPROFILE_HIGH: return PLEX_MEMLIMIT_SPRITETHEATER_SLIDE_HIGH;
		case P_MEMPROFILE_VERYHIGH: return PLEX_MEMLIMIT_SPRITETHEATER_SLIDE_VERYHIGH;
		default: break;
	};

	return PLEX_MEMLIMIT_SPRITETHEATER_SLIDE_LOW;
}

size_t PLEX_getMemProfileActor()
{
	switch(p_profile)
	{
		case P_MEMPROFILE_MEDIUM: return PLEX_MEMLIMIT_SPRITETHEATER_ACTOR_MEDIUM;
		case P_MEMPROFILE_HIGH: return PLEX_MEMLIMIT_SPRITETHEATER_ACTOR_HIGH;
		case P_MEMPROFILE_VERYHIGH: return PLEX_MEMLIMIT_SPRITETHEATER_ACTOR_VERYHIGH;
		default: break;
	};

	return PLEX_MEMLIMIT_SPRITETHEATER_ACTOR_LOW;
}

size_t PLEX_getMemProfileActionChange()
{
	switch(p_profile)
	{
		case P_MEMPROFILE_MEDIUM: return PLEX_MEMLIMIT_SPRITETHEATER_ACTIONCHANGE_MEDIUM;
		case P_MEMPROFILE_HIGH: return PLEX_MEMLIMIT_SPRITETHEATER_ACTIONCHANGE_HIGH;
		case P_MEMPROFILE_VERYHIGH: return PLEX_MEMLIMIT_SPRITETHEATER_ACTIONCHANGE_VERYHIGH;
		default: break;
	};

	return PLEX_MEMLIMIT_SPRITETHEATER_ACTIONCHANGE_LOW;
}

size_t PLEX_getMemProfileMusicChange()
{
	switch(p_profile)
	{
		case P_MEMPROFILE_MEDIUM: return PLEX_MEMLIMIT_SPRITETHEATER_MUSICCHANGE_MEDIUM;
		case P_MEMPROFILE_HIGH: return PLEX_MEMLIMIT_SPRITETHEATER_MUSICCHANGE_HIGH;
		case P_MEMPROFILE_VERYHIGH: return PLEX_MEMLIMIT_SPRITETHEATER_MUSICCHANGE_VERYHIGH;
		default: break;
	};

	return PLEX_MEMLIMIT_SPRITETHEATER_MUSICCHANGE_LOW;
}

size_t PLEX_getMemProfileGenStart()
{
	switch(p_profile)
	{
		case P_MEMPROFILE_MEDIUM: return PLEX_MEMLIMIT_GENERATOR_GENSTART_MEDIUM;
		case P_MEMPROFILE_HIGH: return PLEX_MEMLIMIT_GENERATOR_GENSTART_HIGH;
		case P_MEMPROFILE_VERYHIGH: return PLEX_MEMLIMIT_GENERATOR_GENSTART_VERYHIGH;
		default: break;
	};

	return PLEX_MEMLIMIT_GENERATOR_GENSTART_LOW;
}

size_t PLEX_getMemProfilePromPreload()
{
	switch(p_profile)
	{
		case P_MEMPROFILE_MEDIUM: return PLEX_MEMLIMIT_PROMINENCEMACHINE_PROMPRELOAD_MEDIUM;
		case P_MEMPROFILE_HIGH: return PLEX_MEMLIMIT_PROMINENCEMACHINE_PROMPRELOAD_HIGH;
		case P_MEMPROFILE_VERYHIGH: return PLEX_MEMLIMIT_PROMINENCEMACHINE_PROMPRELOAD_VERYHIGH;
		default: break;
	};

	return PLEX_MEMLIMIT_PROMINENCEMACHINE_PROMPRELOAD_LOW;
}
