#ifndef PLEX_TEXTURES_H
#define PLEX_TEXTURES_H

#include "windowing/window.h"

#include "utility/fakestrings.h"

#include "mem/mem.h"

// this unit contains PLEX's texture management system. The way that PLEX manages textures is mostly internally. So everything is managed by index's as size_t indices returned as they are created. These indices are the same used in draw, sprite, and animation functions. It also recycles textures whenever it can get away with it.

// NOTE: This is a unit with a state machine affiliated therefore has a start, update, and end function. Some functions will not work if the 'start' function is not called successfully. PLEX_start, PLEX_update, and PLEX_end should call the start, update, and end functions of the state machine so they don't need to be called manually.

// macro functions and macros -----------------------------------------------------------------------------------------------

// ARGUMENTS: (const uint32_t w, const uint32_t h, const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a) - returns size_t

#define PLEX_createGeneratedTexture(w, h, r, g, b, a) PLEX_createGeneratedTextureInt(w, h, r, g, b, a, __LINE__, __FILE__)

// ARGUMENTS: (const uint32_t w, const uint32_t h, const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a, const double tint, const char* const fileloc) - returns size_t

#define PLEX_loadTextureFromFile(w, h, r, g, b, a, tint, fileloc) PLEX_loadTextureFromFileInt(w, h, r, g, b, a, tint, fileloc, __LINE__, __FILE__)

// ARGUMENTS: (const char* const filelocFrom, const char* const filelocTo) - returns bool

#define PLEX_convToHeaderlessImage(filelocFrom, filelocTo) PLEX_convToHeaderlessImageInt(filelocFrom, filelocTo, __LINE__, __FILE__)

// ARGUMENTS: (const char* const fileloc) - returns size_t

#define PLEX_loadTextureFromHeaderless(fileloc) PLEX_loadTextureFromHeaderlessInt(fileloc,  __LINE__, __FILE__)

// ARGUMENTS: (const uint32_t w, const uint32_t h, const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a, const double tint, const char* const fileloc, const char* const headerlessLoc) - returns size_t

#define PLEX_loadTextureFromFileOrHeaderless(w, h, r, g, b, a, tint, fileloc, headerlessLoc) PLEX_loadTextureFromFileOrHeaderlessInt(w, h, r, g, b, a, tint, fileloc, headerlessLoc, __LINE__, __FILE__)

// ARGUMENTS: (const size_t from, const uint32_t cx, const uint32_t cy, const uint32_t cw, const uint32_t ch) - returns size_t

#define PLEX_copyTexture(from, cx, cy, cw, ch) PLEX_copyTextureInt(from, cx, cy, cw, ch, __LINE__, __FILE__)

// ARGUMENTS: (const size_t index)

#define PLEX_destroyTexture(index) PLEX_destroyTextureInt(index, __LINE__, __FILE__)

// ARGUMENTS: (const size_t index)

#define PLEX_clearTexture(index) PLEX_clearTextureInt(index, __LINE__, __FILE__)

// ARGUMENTS: (const size_t index)

#define PLEX_unclearTexture(index) PLEX_unclearTextureInt(index, __LINE__, __FILE__)

// NO ARGUMENTS - returns bool

#define PLEX_startTextures() PLEX_startTexturesInt(__LINE__, __FILE__)

// NO ARGUMENTS - returns bool

#define PLEX_updateTextures() PLEX_updateTexturesInt(__LINE__, __FILE__)

// NO ARGUMENTS

#define PLEX_endTextures() PLEX_endTexturesInt(__LINE__, __FILE__)

// ARGUMENTS: (const size_t texture, const uint8_t a)

#define PLEX_setTextureAlpha(texture, a) PLEX_setTextureAlphaInt(texture, a, __LINE__, __FILE__)

// ARGUMENTS: (const size_t index) - returns bool

#define PLEX_textureIsNull(index) PLEX_textureIsNullInt(index, __LINE__, __FILE__)

// ARGUMENTS: (const size_t index, uint32_t* w, uint32_t* h)

#define PLEX_textureWH(index, w, h) PLEX_textureWHInt(index, w, h, __LINE__, __FILE__)

// ARGUMENTS: (const size_t index) - returns PLEX_LOW_TEXTURE

#define PLEX_innerTexture(index) PLEX_innerTextureInt(index, __LINE__, __FILE__)

// ARGUMENTS: (const size_t index) - returns bool

#define PLEX_textureIsCleared(index) PLEX_textureIsClearedInt(index, __LINE__, __FILE__)

// public functions ---------------------------------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C"
{
#endif
// specialized functions ---------------------------------------------------------------------------------------------------

	// internally creates a blank texture filled with rgba and returns the index of the created texture

	extern size_t PLEX_createGeneratedTextureInt(const uint32_t w, const uint32_t h, const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a, const size_t errorline, const char* const errorfile);

	// internally creates a texture from an image file and returns the index of the created texture

	extern size_t PLEX_loadTextureFromFileInt(const uint32_t w, const uint32_t h, const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a, const double tint, const char* const fileloc, const size_t errorline, const char* const errorfile);

	// converts a surface loaded from an image into a headerless uncompressed image

	extern bool PLEX_convToHeaderlessImageInt(const char* const filelocFrom, const char* const filelocTo, const size_t errorline, const char* const errorfile);

	// loads a headerless image file into a texture

	extern size_t PLEX_loadTextureFromHeaderlessInt(const char* const fileloc, const size_t errorline, const char* const errorfile);

	// loads headerless image if it's available, otherwise loads it from a non-headerless file

	extern size_t PLEX_loadTextureFromFileOrHeaderlessInt(const uint32_t w, const uint32_t h, const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a, const double tint, const char* const fileloc, const char* const headerlessLoc, const size_t errorline, const char* const errorfile);

	// copies a texture from the range cx, cy, cw, ch into a new texture and returns it's index. This hasn't been tested for awhile, so it's technically considered experimental.

	extern size_t PLEX_copyTextureInt(const size_t from, const uint32_t cx, const uint32_t cy, const uint32_t cw, const uint32_t ch, const size_t errorline, const char* const errorfile);

	// internally destroys the texture by index. Of course, doesn't clear the size_t index is passed into it

	extern void PLEX_destroyTextureInt(const size_t index, const size_t errorline, const char* const errorfile);

	// destroys a texture without destroying it's meta information so it can be regenerated (untested/experimental)

	extern void PLEX_clearTextureInt(const size_t index, const size_t errorline, const char* const errorfile);

	// regenerates a cleared texture (untested/experimental)

	extern void PLEX_unclearTextureInt(const size_t index, const size_t errorline, const char* const errorfile);

// start, update, end functions ---------------------------------------------------------------------------------------------

	// starts the texture manager. Returns false on failure. If this fails in PLEX_start the entire program terminates. You don't need to manually call this.

	extern bool PLEX_startTexturesInt(const size_t errorline, const char* const errorfile);

	// updates the texture manager. Returns false on failure. If this fails in PLEX_update the entire program terminates. You don't need to manually call this.

	extern bool PLEX_updateTexturesInt(const size_t errorline, const char* const errorfile);

	// ends the texture manager. You don't need to manually call this.

	extern void PLEX_endTexturesInt(const size_t errorline, const char* const errorfile);

// setters ------------------------------------------------------------------------------------------------------------------

	// sets an alpha mod to the texture

	extern void PLEX_setTextureAlphaInt(const size_t texture, const uint8_t a, const size_t errorline, const char* const errorfile);

// getters ------------------------------------------------------------------------------------------------------------------

	// returns a 'null' texture. Not a blank texture but a signifier of a non-texture,

	extern size_t PLEX_nullTexture();

	// returns true if a texture at index is NULL

	extern bool PLEX_textureIsNullInt(const size_t index, const size_t errorline, const char* const errorfile);

	// reads the width and height of a texture at index

	extern void PLEX_textureWHInt(const size_t index, uint32_t* w, uint32_t* h, const size_t errorline, const char* const errorfile);

	// returns the low level texture inside the texture at index

	extern PLEX_LOW_TEXTURE PLEX_innerTextureInt(const size_t index, const size_t errorline, const char* const errorfile);

	// returns whether or not the texture at index is cleared

	extern bool PLEX_textureIsClearedInt(const size_t index, const size_t errorline, const char* const errorfile);
#ifdef __cplusplus
}
#endif

#endif
