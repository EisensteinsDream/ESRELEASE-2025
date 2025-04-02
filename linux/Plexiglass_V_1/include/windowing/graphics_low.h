#ifndef PLEX_GRAPHICS_LOW_H
#define PLEX_GRAPHICS_LOW_H

#include "windowing/texture_low.h"

// This is the header for the low level graphics system. This is a branch of multiple potential graphics systems which can be switched through the macro PLEX_RENDER_TYPE. At the moment only SDL is supported but future versions will likely have opengl and directx branches.

// NOTE: This is an independent unit. Not a unit with an accompanying state machine. It has no 'start, update, or end' functions that need to be called to operate.

// definitions for sdl renderer ---------------------------------------------------------------------------------------------

#if (PLEX_RENDERER_TYPE == PLEX_RENDERER_TYPE_SDL)
	#define PLEX_LOW_NOTARGET NULL
#endif

// NOTE: more definitions in texture_low.h

// macro functions and macros -----------------------------------------------------------------------------------------------

// ARGUMENTS: (const char* const title, const uint32_t width, const uint32_t height, const bool allowResize)- returns SDL_Window*

#define PLEX_low_createSDLWindow(title, width, height, allowResize) PLEX_low_createSDLWindowInt(title, width, height, allowResize, __LINE__, __FILE__)

// ARGUMENTS: (SDL_Window* const window)

#define PLEX_low_destroySDLWindow(window) PLEX_low_destroySDLWindowInt(window, __LINE__, __FILE__)

// ARGUMENTS: (SDL_Window* const window, const uint32_t w, const uint32_t h)

#define PLEX_low_updateRenderer(window, w, h) PLEX_low_updateRendererInt(window, w, h, __LINE__, __FILE__)

// ARGUMENTS: (PLEX_LOW_TEXTURE* texture, const uint8_t r, const uint8_t g, const uint8_t b)

#define PLEX_low_tintTexturesRGB(texture, r, g, b) PLEX_low_tintTexturesRGBInt(texture, r, g, b, __LINE__, __FILE__)

// ARGUMENTS: (PLEX_LOW_TEXTURE texture, uint8_t* r, uint8_t* g, uint8_t* b)

#define PLEX_low_getTintTexturesRGB(texture, r, g, b) PLEX_low_getTintTexturesRGBInt(texture, r, g, b, __LINE__, __FILE__)

// NO ARGUMENTS - returns PLEX_LOW_TEXTURE

#define PLEX_low_getRenderTarget() PLEX_low_getRenderTargetInt(__LINE__, __FILE__)

// NO ARGUMENTS - returns SDL_BlendMode

#define PLEX_low_getRenderBlendMode() PLEX_low_getRenderBlendModeInt(__LINE__, __FILE__)

// public functions ---------------------------------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C"
{
#endif
// specialized functions ----------------------------------------------------------------------------------------------------

	// creates the window based on whatever designated renderer

	extern SDL_Window* PLEX_low_createSDLWindowInt(const char* const title, const uint32_t width, const uint32_t height, const bool allowResize, const size_t errorline, const char* const errorfile);

	// destroys the window based on whatever designated renderer

	extern void PLEX_low_destroySDLWindowInt(SDL_Window* const window, const size_t errorline, const char* const errorfile);

	// updates the window based on whatever designated renderer

	extern void PLEX_low_updateRendererInt(SDL_Window* const window, const uint32_t w, const uint32_t h, const size_t errorline, const char* const errorfile);

	// low level filling of an sdl rect rgba

	extern void PLEX_low_fillRect(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a, const SDL_Rect* s, const SDL_BlendMode blendMode);

	// low level filling of an array of sdl rects

	extern void PLEX_low_fillRects(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a, const SDL_Rect* s, const size_t count, const SDL_BlendMode blendMode);

	// tints the texture passed in

	extern void PLEX_low_tintTexturesRGBInt(PLEX_LOW_TEXTURE* texture, const uint8_t r, const uint8_t g, const uint8_t b, const size_t errorline, const char* const errorfile);

	// draws the texture onto the screen

	extern void PLEX_low_copyTexture(PLEX_LOW_TEXTURE texture, const SDL_Rect* from, const SDL_Rect* to, const SDL_BlendMode blendMode);

	// draws the texture on the screen but rotated

	extern void PLEX_low_copyTextureRotated(PLEX_LOW_TEXTURE texture, const SDL_Rect* from, const SDL_Rect* to, const double angle, const SDL_BlendMode blendMode);

	// clears the screen texture

	extern void PLEX_low_clear(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a);

// setters ------------------------------------------------------------------------------------------------------------------

	// sets the rendering target (PLEX_LOW_NOTARGET ==d the screen)

	extern void PLEX_low_setRenderTarget(PLEX_LOW_TEXTURE target);

	// sets the rendering blend mode based on SDL blend mode (whether the renderer is SDL or not it is expected to figure it out)

	extern void PLEX_low_setBlendTarget(const SDL_BlendMode blendMode);

// getters ------------------------------------------------------------------------------------------------------------------

	// extern SDL_Renderer* PLEX_low_getRenderer(); < forward declared in texture_low. doesn't exist in all implementations.

	// returns the tint rgb of a texture

	extern void PLEX_low_getTintTexturesRGBInt(PLEX_LOW_TEXTURE texture, uint8_t* r, uint8_t* g, uint8_t* b, const size_t errorline, const char* const errorfile);

	// returns the render target

	extern PLEX_LOW_TEXTURE PLEX_low_getRenderTargetInt(const size_t errorline, const char* const errorfile);

	// returns the current target's blend mode

	extern SDL_BlendMode PLEX_low_getRenderBlendModeInt(const size_t errorline, const char* const errorfile);
#ifdef __cplusplus
}
#endif

#endif
