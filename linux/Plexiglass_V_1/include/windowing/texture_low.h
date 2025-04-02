#ifndef PLEX_TEXTURE_LOW_H
#define PLEX_TEXTURE_LOW_H

#include "utility/defaults.h"

// This is the header for the low level texturing system. This is a branch of multiple potential graphics systems which can be switched through the macro PLEX_RENDER_TYPE. More information at graphics_low.h. At the moment only SDL is supported. In very few cases will you have to interface with these functions directly. Instead, using the indexed 'texture.h' is much preferred.

// NOTE: This is an independent unit. Not a unit with an accompanying state machine. It has no 'start, update, or end' functions that need to be called to operate.

// macro functions and macros -----------------------------------------------------------------------------------------------

// Indices for different rendering types:

#define PLEX_RENDERER_TYPE_SDL 0
  
// defaults to SDL rendering type if the compiler hasn't set one:

#ifndef PLEX_RENDERER_TYPE
	#define PLEX_RENDERER_TYPE PLEX_RENDERER_TYPE_SDL // < defaults to sdl hardware
#endif

// definitions if SDL rendering:

#if (PLEX_RENDERER_TYPE == PLEX_RENDERER_TYPE_SDL)
	#define PLEX_LOW_TEXTURE SDL_Texture*
	#define PLEX_LOW_NOTEXTURE NULL
#endif

// ARGUMENTS: (SDL_Surface* surface, PLEX_LOW_TEXTURE* texture, const uint8_t a)

#define PLEX_low_textureFromSurface(surface, texture, a) PLEX_low_textureFromSurfaceInt(surface, texture, a, __LINE__, __FILE__)

// ARGUMENTS: (PLEX_LOW_TEXTURE* texture)

#define PLEX_low_destroyTexture(texture) PLEX_low_destroyTextureInt(texture, __LINE__, __FILE__)

// ARGUMENTS: (PLEX_LOW_TEXTURE texture, uint32_t* w, uint32_t* h)

#define PLEX_low_textureWH(texture, w, h) PLEX_low_textureWHInt(texture, w, h, __LINE__, __FILE__)

// ARGUMENTS: (PLEX_LOW_TEXTURE texture) - returns SDL_BlendMode

#define PLEX_low_getTextureBlendMode(texture) PLEX_low_getTextureBlendModeInt(texture, __LINE__, __FILE__)

// public functions ---------------------------------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C"
{
#endif
// specialized functions ----------------------------------------------------------------------------------------------------

	// generate low level blank texture

	extern PLEX_LOW_TEXTURE PLEX_low_generateTexture(const Uint32 format, const int access, const int w, const int h);

	// generates a texture of color r, g, b, a

	extern void PLEX_low_makeGeneratedTexture(PLEX_LOW_TEXTURE texture, const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a);

	// converts 'SDL surface' into 'texture' with alpha (should not need to be SDL rendering to work)

	extern void PLEX_low_textureFromSurfaceInt(SDL_Surface* surface, PLEX_LOW_TEXTURE* texture, const uint8_t a, const size_t errorline, const char* const errorfile);

	// destroys the low level texture

	extern void PLEX_low_destroyTextureInt(PLEX_LOW_TEXTURE* texture, const size_t errorline, const char* const errorfile);

	// clears low level texture to blank (0, 0, 0, 0 color)

	extern void PLEX_low_clearTexture(PLEX_LOW_TEXTURE texture);

	// copies texture 'from' onto 'to'

	extern void PLEX_low_copyTextureOntoTexture(PLEX_LOW_TEXTURE from, PLEX_LOW_TEXTURE to, SDL_Rect area, SDL_Rect toArea);

	// compares whether texture a or b are equal, or whether a is less than b. This is mostly for sorting

	extern bool PLEX_low_compTextures(const PLEX_LOW_TEXTURE a, const PLEX_LOW_TEXTURE b);

	// compares a and b and if a is a 'lesser' texture (ie. smaller texture ID dependent on how the current context figures that) than it returns it as a (for sorting)

	extern bool PLEX_low_lessTextures(const PLEX_LOW_TEXTURE a, const PLEX_LOW_TEXTURE b);

// setters ------------------------------------------------------------------------------------------------------------------

	// alpha mods the texture to draw translucent

	extern void PLEX_low_textureSetAlpha(PLEX_LOW_TEXTURE* toSet, const uint8_t alpha);

// getters ------------------------------------------------------------------------------------------------------------------

	// returns the width and height of a texture

	extern void PLEX_low_textureWHInt(PLEX_LOW_TEXTURE texture, uint32_t* w, uint32_t* h, const size_t errorline, const char* const errorfile);

	// returns the blend mode of a texture

	extern SDL_BlendMode PLEX_low_getTextureBlendModeInt(PLEX_LOW_TEXTURE texture, const size_t errorline, const char* const errorfile);

	// returns whether or not a texture is null

	extern bool PLEX_low_isTextureNull(const PLEX_LOW_TEXTURE texture);

// SDL Renderer specific functions ------------------------------------------------------------------------------------------

	#if (PLEX_RENDERER_TYPE == PLEX_RENDERER_TYPE_SDL)
		extern SDL_Renderer* PLEX_low_getRenderer(); // < defined in graphics_low_SDL.c.h
	#endif
#ifdef __cplusplus
}
#endif

#endif
