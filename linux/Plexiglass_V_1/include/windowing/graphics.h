#ifndef PLEX_GRAPHICS_H
#define PLEX_GRAPHICS_H

#include "windowing/input.h"

#include "mem/expandarray.h"

// This unit is where all the functions that are used to draw on the screen (with the exception of sprites and animation)

// NOTE: This is an independent unit. Not a unit with an accompanying state machine. It has no 'start, update, or end' functions that need to be called to operate.

// macro functions and macros -----------------------------------------------------------------------------------------------

// ARGUMENTS: (const size_t order, const uint8_t r, const uint8_t g, const uint8_t b)

#define PLEX_clear(order, r, g, b) PLEX_clearInt(order, r, g, b, __LINE__, __FILE__)

// ARGUMENTS: (const size_t order, const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a)

#define PLEX_clearAlpha(order, r, g, b, a) PLEX_clearAlphaInt(order, r, g, b, a, __LINE__, __FILE__)

// ARGUMENTS: (const size_t order, const uint8_t r, const uint8_t g, const uint8_t b)

#define PLEX_clearOffsetArea(order, r, g, b) PLEX_clearOffsetAreaInt(order, r, g, b, __LINE__, __FILE__)

// ARGUMENTS: (const size_t order, const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a)

#define PLEX_clearOffsetAreaAlpha(order, r, g, b, a) PLEX_clearOffsetAreaAlphaInt(order, r, g, b, a, __LINE__, __FILE__)

// ARGUMENTS: (const size_t order, const int64_t x, const int64_t y, const int64_t x2, const int64_t y2, const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a, const uint8_t thickness, const bool offset)

#define PLEX_drawLine(order, x, y, x2, y2, r, g, b, a, thickness, offset) PLEX_drawLineInt(order, x, y, x2, y2, r, g, b, a, thickness, offset, __LINE__, __FILE__)

// ARGUMENTS: (const size_t order, const int64_t x, int64_t y, const int64_t length, const double direction, const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a, const uint8_t thickness, const bool offset)

#define PLEX_drawLine2(order, x, y, length, direction, r, g, b, a, thickness, offset) PLEX_drawLine2Int(order, x, y, length, direction, r, g, b, a, thickness, offset, __LINE__, __FILE__)

// ARGUMENTS: (const size_t order, const PLEX_LINE line, const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a, const uint8_t thickness, const bool offset)

#define PLEX_drawLine3(order, line, r, g, b, a, thickness, offset) PLEX_drawLine3Int(order, line, r, g, b, a, thickness, offset, __LINE__, __FILE__)

// ARGUMENTS: (const size_t order, const int64_t x, const int64_t y, const int64_t w, const int64_t h, const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a, const uint8_t thickness, const bool offset)

#define PLEX_drawRect(order, x, y, w, h, r, g, b, a, thickness, offset) PLEX_drawRectInt(order, x, y, w, h, r, g, b, a, thickness, offset, __LINE__, __FILE__)

// ARGUMENTS: (const size_t order, const int64_t x, const int64_t y, const int64_t w, const int64_t h, const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a, const bool offset)

#define PLEX_fillRect(order, x, y, w, h, r, g, b, a, offset) PLEX_fillRectInt(order, x, y, w, h, r, g, b, a, offset, __LINE__, __FILE__)

// ARGUMENTS: (const size_t order, const size_t texture, const int64_t fx, const int64_t fy, const int64_t fw, const int64_t fh, const int64_t tx, const int64_t ty, const int64_t tw, const int64_t th, const bool offset)

#define PLEX_printTexture(order, texture, fx, fy, fw, fh, tx, ty, tw, th, offset) PLEX_printTextureInt(order, texture, fx, fy, fw, fh, tx, ty, tw, th, offset, __LINE__, __FILE__)

// ARGUMENTS: (const size_t order, const size_t texture, const int64_t fx, const int64_t fy, const int64_t fw, const int64_t fh, const int64_t tx, const int64_t ty, const int64_t tw, const int64_t th, const uint8_t r, const uint8_t g, const uint8_t b, const bool offset)

#define PLEX_printTextureTinted(order, texture, fx, fy, fw, fh, tx, ty, tw, th, r, g, b, offset) PLEX_printTextureTintedInt(order, texture, fx, fy, fw, fh, tx, ty, tw, th, r, g, b, offset, __LINE__, __FILE__)

// ARGUMENTS: (const size_t order, const size_t texture, const int64_t fx, const int64_t fy, const int64_t fw, const int64_t fh, const int64_t tx, const int64_t ty, const int64_t tw, const int64_t th, const double angle, const bool offset)

#define PLEX_printTextureRotated(order, texture, fx, fy, fw, fh, tx, ty, tw, th, angle, offset) PLEX_printTextureRotatedInt(order, texture, fx, fy, fw, fh, tx, ty, tw, th, angle, offset, __LINE__, __FILE__)

// ARGUMENTS: (const size_t order, const size_t texture, const int64_t fx, const int64_t fy, const int64_t fw, const int64_t fh, const int64_t tx, const int64_t ty, const int64_t tw, const int64_t th, const uint8_t r, const uint8_t g, const uint8_t b, const double angle,  const bool offset)

#define PLEX_printTextureRotatedTinted(order, texture, fx, fy, fw, fh, tx, ty, tw, th, r, g, b, angle, offset) PLEX_printTextureRotatedTintedInt(order, texture, fx, fy, fw, fh, tx, ty, tw, th, r, g, b, angle, offset, __LINE__, __FILE__)

// ARGUMENTS: (const size_t order, const double wPerc, const double hPerc, const int64_t ox, const int64_t oy, const int64_t ow, const int64_t oh, const uint8_t symbol, const char* const alphaString, const size_t texture, const bool offset)

#define PLEX_printFontLetter(order, wPerc, hPerc, ox, oy, ow, oh, symbol, alphaString, texture, offset) PLEX_printFontLetterInt(order, wPerc, hPerc, ox, oy, ow, oh, symbol, alphaString, texture, offset, __LINE__, __FILE__)

// ARGUMENTS: (const size_t order, const double wPerc, const double hPerc, const int64_t ox, const int64_t oy, const int64_t ow, const int64_t oh, const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t symbol, const char* const alphaString, const size_t texture, const bool offset)

#define PLEX_printFontLetterTinted(order, wPerc, hPerc, ox, oy, ow, oh, r, g, b, symbol, alphaString, texture, offset) PLEX_printFontLetterTintedInt(order, wPerc, hPerc, ox, oy, ow, oh, r, g, b, symbol, alphaString, texture, offset, __LINE__, __FILE__)

// ARGUMENTS: (const size_t order, const double wPerc, const double hPerc, const int64_t ox, const int64_t oy, const int64_t ow, const int64_t oh, const char* const string, const char* const alphaString, const size_t texture, const bool offset)

#define PLEX_printFontString(order, wPerc, hPerc, ox, oy, ow, oh, string, alphaString, texture, offset) PLEX_printFontStringInt(order, wPerc, hPerc, ox, oy, ow, oh, string, alphaString, texture, offset, __LINE__, __FILE__)

// ARGUMENTS: (const size_t order, const double wPerc, const double hPerc, const int64_t ox, const int64_t oy, const int64_t ow, const int64_t oh, const uint8_t r, const uint8_t g, const uint8_t b, const char* const string, const char* const alphaString, const size_t texture, const bool offset)

#define PLEX_printFontStringTinted(order, wPerc, hPerc, ox, oy, ow, oh, r, g, b, string, alphaString, texture, offset) PLEX_printFontStringTintedInt(order, wPerc, hPerc, ox, oy, ow, oh, r, g, b, string, alphaString, texture, offset, __LINE__, __FILE__)

// ARGUMENTS: (const size_t order, const int64_t x, const int64_t y, const int64_t w, const int64_t h, const uint8_t br, const uint8_t bg, const uint8_t bb, const uint8_t ba, const size_t texture, const int64_t tx, const int64_t ty, const int64_t tw, const int64_t th, const uint8_t thickness, const bool offset)

#define PLEX_drawIcon(order, x, y, w, h, br, bg, bb, ba, texture, tx, ty, tw, th, thickness, offset) PLEX_drawIconInt(order, x, y, w, h, br, bg, bb, ba, texture, tx, ty, tw, th, thickness, offset, __LINE__, __FILE__)

// ARGUMENTS: (const size_t order, const int64_t x, const int64_t y, const int64_t w, const int64_t h, const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t br, const uint8_t bg, const uint8_t bb, const uint8_t ba, const size_t texture, const int64_t tx, const int64_t ty, const int64_t tw, const int64_t th, const uint8_t thickness, const bool offset)

#define PLEX_drawIconTinted(order, x, y, w, h, r, g, b, br, bg, bb, ba, texture, tx, ty, tw, th, thickness, offset) PLEX_drawIconTintedInt(order, x, y, w, h, r, g, b, br, bg, bb, ba, texture, tx, ty, tw, th, thickness, offset, __LINE__, __FILE__)

// ARGUMENTS: (const size_t order, const char* const message, const double wPerc, const double hPerc, const uint8_t fr, const uint8_t fg, const uint8_t fb, const uint8_t fa, const int64_t x, const int64_t y, const int64_t w, const int64_t h, const double ipx, const double ipy, const double ipw, const double iph, const uint8_t thickness, const char* const alphaString, const size_t fontTexture, const size_t texture, const int64_t tx, const int64_t ty, const int64_t tw, const int64_t th, const bool offset)

#define PLEX_drawLabel(order, message, wPerc, hPerc, fr, fg, fb, fa, x, y, w, h, ipx, ipy, ipw, iph, thickness, alphaString, fontTexture, texture, tx, ty, tw, th, offset) PLEX_drawLabelInt(order, message, wPerc, hPerc, fr, fg, fb, fa, x, y, w, h, ipx, ipy, ipw, iph, thickness, alphaString, fontTexture, texture, tx, ty, tw, th, offset, __LINE__, __FILE__)

// ARGUMENTS: (const size_t order, const char* const message, const double wPerc, const double hPerc, const int64_t x, const int64_t y, const int64_t w, const int64_t h, const int64_t tx, const int64_t ty, const int64_t tw, const int64_t th, const uint8_t fr, const uint8_t fg, const uint8_t fb, const uint8_t fa, const uint8_t br, const uint8_t bg, const uint8_t bb, const uint8_t ba, const uint8_t thickness, const char* const alphaString, const size_t font, const size_t texture, const bool offset) - returns bool

#define PLEX_drawButton(order, message, wPerc, hPerc, x, y, w, h, fr, fg, fb, fa, br, bg, bb, ba, thickness, alphaString, font, texture, tx, ty, tw, th, offset) PLEX_drawButtonInt(order, message, wPerc, hPerc, x, y, w, h, fr, fg, fb, fa, br, bg, bb, ba, thickness, alphaString, font, texture, tx, ty, tw, th, offset, __LINE__, __FILE__)

// ARGUMENTS: (const size_t order, const int64_t x, const int64_t y, const int64_t w, const int64_t h, const uint8_t fr, const uint8_t fg, const uint8_t fb, const uint8_t fa, const uint8_t br, const uint8_t bg, const uint8_t bb, const uint8_t ba, const uint8_t thickness, const bool flip, const bool offset) - returns bool

#define PLEX_drawArrowButton(order, x, y, w, h, fr, fg, fb, fa, br, bg, bb, ba, thickness, flip, offset) PLEX_drawArrowButtonInt(order, x, y, w, h, fr, fg, fb, fa, br, bg, bb, ba, thickness, flip, offset, __LINE__, __FILE__)

// ARGUMENTS: (const size_t order, const bool selected, const int64_t x, const int64_t y, const int64_t w, const int64_t h, const int64_t tx, const int64_t ty, const int64_t tw, const int64_t th, const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a, const uint8_t sr, const uint8_t sg, const uint8_t sb, const uint8_t sa, const uint8_t ovr, const int64_t ovb, const int64_t ovg, const int64_t ova, const uint8_t sovr, const int64_t sovb, const int64_t sovg, const int64_t sova, const uint8_t thickness, const size_t texture, const bool offset) - returns bool

#define PLEX_drawIconButton(order, selected, x, y, w, h, tx, ty, tw, th, r, g, b, a, sr, sg, sb, sa, ovr, ovb, ovg, ova, sovr, sovb, sovg, sova, thickness, texture, offset) PLEX_drawIconButtonInt(order, selected, x, y, w, h, tx, ty, tw, th, r, g, b, a, sr, sg, sb, sa, ovr, ovb, ovg, ova, sovr, sovb, sovg, sova, thickness, texture, offset, __LINE__, __FILE__)

// ARGUMENTS: (const size_t order, const bool selected, const int64_t x, const int64_t y, const int64_t w, const int64_t h, const int64_t tx, const int64_t ty, const int64_t tw, const int64_t th, const int64_t tx2, const int64_t ty2, const int64_t tw2, const int64_t th2, const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a, const uint8_t sr, const uint8_t sg, const uint8_t sb, const uint8_t sa, const uint8_t thickness, const size_t texture1, const size_t texture2, const bool offset) - returns bool

#define PLEX_twoImageButton(order, selected, x, y, w, h, tx, ty, tw, th, tx2, ty2, tw2, th2, r, g, b, a, sr, sg, sb, sa, thickness, texture1, texture2, offset) PLEX_twoImageButtonInt(order, selected, x, y, w, h, tx, ty, tw, th, tx2, ty2, tw2, th2, r, g, b, a, sr, sg, sb, sa, thickness, texture1, texture2, offset, __LINE__, __FILE__)

// ARGUMENTS: (const size_t order, const char* const message, const double wPerc, const double hPerc, const uint8_t fr, const uint8_t fg, const uint8_t fb, const uint8_t fa, const int64_t hx, const int64_t hy, const int64_t hw, const int64_t hh, const uint32_t fw, const uint32_t fh, const double ipx, const double ipy, const double ipw, const double iph, const uint8_t thickness, const char* const alphaString, const size_t fontTexture, const size_t texture, const int64_t tx, const int64_t ty, const int64_t tw, const int64_t th, const double lineSpacePerc, const bool offset) - returns bool

#define PLEX_drawTextBox(order, message, wPerc, hPerc, fr, fg, fb, fa, x, y, w, h, fw, fh, ipx, ipy, ipw, iph, thickness, alphaString, fontTexture, texture, tx, ty, tw, th, lineSpacePerc, offset) PLEX_drawTextBoxInt(order, message, wPerc, hPerc, fr, fg, fb, fa, x, y, w, h, fw, fh, ipx, ipy, ipw, iph, thickness, alphaString, fontTexture, texture, tx, ty, tw, th, lineSpacePerc, offset, __LINE__, __FILE__)

// ARGUMENTS: (const size_t order, const char* const message, const double wPerc, const double hPerc, const uint8_t fr, const uint8_t fg, const uint8_t fb, const uint8_t fa, const uint8_t br, const uint8_t bg, const uint8_t bb, const uint8_t ba, const int64_t x, const int64_t y, const int64_t w, const int64_t h, const uint32_t fw, const uint32_t fh, const double ipx, const double ipy, const double ipw, const double iph, const uint8_t thickness, const char* const alphaString, const size_t fontTexture, const size_t texture, const int64_t tx, const int64_t ty, const int64_t tw, const int64_t th, const double lineSpacePerc, const bool offset)

#define PLEX_drawTextBoxTinted(order, message, wPerc, hPerc, fr, fg, fb, fa, br, bg, bb, ba, x, y, w, h, fw, fh, ipx, ipy, ipw, iph, thickness, alphaString, fontTexture, texture, tx, ty, tw, th, lineSpacePerc, offset) PLEX_drawTextBoxTintedInt(order, message, wPerc, hPerc, fr, fg, fb, fa, br, bg, bb, ba, x, y, w, h, fw, fh, ipx, ipy, ipw, iph, thickness, alphaString, fontTexture, texture, tx, ty, tw, th, lineSpacePerc, offset, __LINE__, __FILE__)

// ARGUMENTS: (const size_t order, const char* const message, const double wPerc, const double hPerc, const uint8_t fr, const uint8_t fg, const uint8_t fb, const uint8_t fa, const int64_t x, const int64_t y, const int64_t w, const int64_t h, const uint32_t fw, const uint32_t fh, const double ipx, const double ipy, const double ipw, const double iph, const uint8_t thickness, const char* const alphaString, const size_t fontTexture, const size_t texture, const int64_t tx, const int64_t ty, const int64_t tw, const int64_t th, const double lineSpacePerc, const size_t pageScroll, const bool offset) - returns size_t

#define PLEX_drawTextBoxScrolling(order, message, wPerc, hPerc, fr, fg, fb, fa, x, y, w, h, fw,  fh, ipx, ipy, ipw, iph, thickness, alphaString, fontTexture, texture, tx, ty, tw, th, lineSpacePerc, pageScroll, offset) PLEX_drawTextBoxScrollingInt(order, message, wPerc, hPerc, fr, fg, fb, fa, x, y, w, h, fw, fh, ipx, ipy, ipw, iph, thickness, alphaString, fontTexture, texture, tx, ty, tw, th, lineSpacePerc, pageScroll, offset, __LINE__, __FILE__)

// ARGUMENTS: (const size_t order, const char* const message, const double wPerc, const double hPerc, const uint8_t fr, const uint8_t fg, const uint8_t fb, const uint8_t fa, const uint8_t br, const uint8_t bg, const uint8_t bb, const uint8_t ba, const int64_t x, const int64_t y, const int64_t w, const int64_t h, const uint32_t fw, const uint32_t fh, const double ipx, const double ipy, const double ipw, const double iph, const uint8_t thickness, const char* const alphaString, const size_t fontTexture, const size_t texture, const int64_t tx, const int64_t ty, const int64_t tw, const int64_t th, const double lineSpacePerc, const size_t pageScroll, const bool offset) - returns size_t

#define PLEX_drawTextBoxScrollingTinted(order, message, wPerc, hPerc, fr, fg, fb, fa, br, bg, bb, ba, x, y, w, h, fw, fh, ipx, ipy, ipw, iph, thickness, alphaString, fontTexture, texture, tx, ty, tw, th, lineSpacePerc, pageScroll, offset) PLEX_drawTextBoxScrollingTintedInt(order, message, wPerc, hPerc, fr, fg, fb, fa, br, bg, bb, ba, x, y, w, h, fw, fh, ipx, ipy, ipw, iph, thickness, alphaString, fontTexture, texture, tx, ty, tw, th, lineSpacePerc, pageScroll, offset, __LINE__, __FILE__)

// ARGUMENTS: (const size_t order, const char* const message, const double wPerc, const double hPerc, const uint8_t br, const uint8_t bg, const uint8_t bb, const uint8_t ba, const int64_t mx, const int64_t my, const int64_t mw, const int64_t mh, const int64_t dx, const int64_t dy, const int64_t lw, const int64_t lh, const double ipx, const double ipy, const double ipw, const double iph, const uint8_t thickness, const char* const alphaString, const size_t fontTexture, const size_t texture, const int64_t tx, const int64_t ty, const int64_t tw, const int64_t th, const bool offset)

#define PLEX_drawTooltip(order, message, wPerc, hPerc, br, bg, bb, ba, hx, hy, hw, hh, dx, dy, lw, lh, ipx, ipy, ipw, iph, thickness, alphaString, fontTexture, texture, tx, ty, tw, th, offset) PLEX_drawTooltipInt(order, message, wPerc, hPerc, br, bg, bb, ba, hx, hy, hw, hh, dx, dy, lw, lh, ipx, ipy, ipw, iph, thickness, alphaString, fontTexture, texture, tx, ty, tw, th, offset, __LINE__, __FILE__)

// ARGUMENTS: (const size_t order, const double fullness, const int64_t x, const int64_t y, const int64_t w, const int64_t h, const uint8_t fr, const uint8_t fg, const uint8_t fb, const uint8_t fa, const uint8_t br, const uint8_t bg, const uint8_t bb, const uint8_t ba, const uint8_t thickness, const bool vertical, const bool offset)

#define PLEX_drawChargeBar(order, fullness, x, y, w, h, fr, fg, fb, fa, br, bg, bb, ba, thickness, vertical, offset) PLEX_drawChargeBarInt(order, fullness, x, y, w, h, fr, fg, fb, fa, br, bg, bb, ba, thickness, vertical, offset, __LINE__, __FILE__)

// ARGUMENTS: (const size_t order, const size_t texture)

#define PLEX_drawPanorama(order, texture) PLEX_drawPanoramaInt(order, texture, __LINE__, __FILE__)

// ARGUMENTS: (const bool offset) - returns size_t

#define PLEX_takeScreencap(offset) PLEX_takeScreencapInt(offset, __LINE__, __FILE__)

// NO ARGUMENTS - returns bool

#define PLEX_startGraphics() PLEX_startGraphicsInt(__LINE__, __FILE__)

// ARGUMENTS: (SDL_Window* window, const uint32_t w, const uint32_t h) - returns bool

#define PLEX_updateGraphics(window, w, h) PLEX_updateGraphicsInt(window, w, h, __LINE__, __FILE__)

// NO ARGUMENTS

#define PLEX_endGraphics() PLEX_endGraphicsInt(__LINE__, __FILE__)

// ARGUMENTS (const size_t texture)

#define PLEX_setTextureTarget(texture) PLEX_setTextureTargetInt(texture, __LINE__, __FILE__)

// ARGUMENTS (const uint8_t r, const uint8_t g, const uint8_t b)

#define PLEX_setRefreshColor(r, g, b)  PLEX_setRefreshColorInt(r, g, b, __LINE__, __FILE__)

// ARGUMENTS (const SDL_BlendMode mode)

#define PLEX_drawBlendMode(mode) PLEX_drawBlendModeInt(mode, __LINE__, __FILE__)

// NO ARGUMENTS

#define PLEX_unsetTextureTarget() PLEX_unsetTextureTargetInt(__LINE__, __FILE__)

// public functions ---------------------------------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C"
{
#endif

// specialized functions ----------------------------------------------------------------------------------------------------

	// clears the entire screen with r, g, b values

	extern void PLEX_clearInt(const size_t order, const uint8_t r, const uint8_t g, const uint8_t b, const size_t line, const char* const errorfile);

	// clears the entire screen with r, g, b values and alpha translucency

	extern void PLEX_clearAlphaInt(const size_t order, const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a, const size_t line, const char* const errorfile);

	// clears the entire offset area of the screen with r, g, b values

	extern void PLEX_clearOffsetAreaInt(const size_t order, const uint8_t r, const uint8_t g, const uint8_t b, const size_t line, const char* const errorfile);

	// clears the entire offset area of the screen with r, g, b values and alpha translucency

	extern void PLEX_clearOffsetAreaAlphaInt(const size_t order, const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a, const size_t line, const char* const errorfile);

	// draws a line from 2 x, y coordinates

	extern void PLEX_drawLineInt(const size_t order, const int64_t x, const int64_t y, const int64_t x2, const int64_t y2, const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a, const uint8_t thickness, const bool offset, const size_t line, const char* const errorfile);

	// draws a line with an x, y, length, and angle (direction)

	extern void PLEX_drawLine2Int(const size_t order, const int64_t x, const int64_t y, const int64_t length, const double direction, const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a, const uint8_t thickness, const bool offset, const size_t line, const char* const errorfile);

	// draws a line from a PLEX_LINE struct

	extern void PLEX_drawLine3Int(const size_t order, const PLEX_LINE line, const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a, const uint8_t thickness, const bool offset, const size_t errorline, const char* const errorfile);

	// draws a rectangle with a thickness

	extern void PLEX_drawRectInt(const size_t order, const int64_t x, const int64_t y, const int64_t w, const int64_t h, const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a, const uint8_t thickness, const bool offset, const size_t line, const char* const errorfile);

	// fills a rectangle a solid color

	extern void PLEX_fillRectInt(const size_t order, const int64_t x, const int64_t y, const int64_t w, const int64_t h, const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a, const bool offset, const size_t line, const char* const errorfile);

	// copies a piece of a texture (fx, fy, fw, fh) to the screen (tx, ty, tw, th)

	extern void PLEX_printTextureInt(const size_t order, const size_t texture, const int64_t fx, const int64_t fy, const int64_t fw, const int64_t fh, const int64_t tx, const int64_t ty, const int64_t tw, const int64_t th, const bool offset, const size_t line, const char* const errorfile);

	// copies a piece of a texture (fx, fy, fw, fh) to the screen (tx, ty, tw, th) but tinted by uint8 r, g, b values

	extern void PLEX_printTextureTintedInt(const size_t order, const size_t texture, const int64_t fx, const int64_t fy, const int64_t fw, const int64_t fh, const int64_t tx, const int64_t ty, const int64_t tw, const int64_t th, const uint8_t r, const uint8_t g, const uint8_t b, const bool offset, const size_t line, const char* const errorfile);

	// copies a piece of a texture (fx, fy, fw, fh) to the screen (tx, ty, tw, th) but rotated at angle degrees

	extern void PLEX_printTextureRotatedInt(const size_t order, const size_t texture, const int64_t fx, const int64_t fy, const int64_t fw, const int64_t fh, const int64_t tx, const int64_t ty, const int64_t tw, const int64_t th, const double angle, const bool offset, const size_t line, const char* const errorfile);

	// copies a piece of a texture (fx, fy, fw, fh) to the screen (tx, ty, tw, th) but rotated at angle degrees and tinted uint8 r, g, b values

	extern void PLEX_printTextureRotatedTintedInt(const size_t order, const size_t texture, const int64_t fx, const int64_t fy, const int64_t fw, const int64_t fh, const int64_t tx, const int64_t ty, const int64_t tw, const int64_t th, const uint8_t r, const uint8_t g, const uint8_t b, const double angle, const bool offset, const size_t errorline, const char* const errorfile);

	// prints a font letter of width ow and height oh at point ox, oy from a bitmap font

	extern void PLEX_printFontLetterInt(const size_t order, const double wPerc, const double hPerc, const int64_t ox, const int64_t oy, const int64_t ow, const int64_t oh, const uint8_t symbol, const char* const alphaString, const size_t texture, const bool offset, const size_t line, const char* const errorfile);

	// prints a font letter of width ow and height oh at point ox, oy from a bitmap font but tinted by uint8 r, g, b values

	extern void PLEX_printFontLetterTintedInt(const size_t order, const double wPerc, const double hPerc, const int64_t ox, const int64_t oy, const int64_t ow, const int64_t oh, const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t symbol, const char* const alphaString, const size_t texture, const bool offset, const size_t line, const char* const errorfile);

	// draws an entire string at ox, oy with letter width of oh and height of oh

	extern void PLEX_printFontStringInt(const size_t order, const double wPerc, const double hPerc, const int64_t ox, const int64_t oy, const int64_t ow, const int64_t oh, const char* const string, const char* const alphaString, const size_t texture, const bool offset, const size_t line, const char* const errorfile);

	// draws an entire string at ox, oy with letter width of oh and height of oh but tinted by uint8 r, g, b values

	extern void PLEX_printFontStringTintedInt(const size_t order, const double wPerc, const double hPerc, const int64_t ox, const int64_t oy, const int64_t ow, const int64_t oh, const uint8_t r, const uint8_t g, const uint8_t b, const char* const string, const char* const alphaString, const size_t texture, const bool offset, const size_t line, const char* const errorfile);

	// prints a texture but also gives it a border colored br, bg, bb, ba.

	extern void PLEX_drawIconInt(const size_t order, const int64_t x, const int64_t y, const int64_t w, const int64_t h, const uint8_t br, const uint8_t bg, const uint8_t bb, const uint8_t ba, const size_t texture, const int64_t tx, const int64_t ty, const int64_t tw, const int64_t th, const uint8_t thickness, const bool offset, const size_t line, const char* const errorfile);

	// prints a texture tinted r, g, b but also gives it a border colored br, bg, bb, ba.

	extern void PLEX_drawIconTintedInt(const size_t order, const int64_t x, const int64_t y, const int64_t w, const int64_t h, const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t br, const uint8_t bg, const uint8_t bb, const uint8_t ba, const size_t texture, const int64_t tx, const int64_t ty, const int64_t tw, const int64_t th, const uint8_t thickness, const bool offset, const size_t line, const char* const errorfile);

	// draws a text label at x, y, w, h with optional skinning from texture from tx, ty, tw, th

	extern void PLEX_drawLabelInt(const size_t order, const char* const message, const double wPerc, const double hPerc, const uint8_t fr, const uint8_t fg, const uint8_t fb, const uint8_t fa, const int64_t x, const int64_t y, const int64_t w, const int64_t h, const double ipx, const double ipy, const double ipw, const double iph, const uint8_t thickness, const char* const alphaString, const size_t fontTexture, const size_t texture, const int64_t tx, const int64_t ty, const int64_t tw, const int64_t th, const bool offset, const size_t line, const char* const errorfile);

	// draws a button at x, y, w, h with optional skinning from texture from tx, ty, tw, th and returns true if clicked

	extern bool PLEX_drawButtonInt(const size_t order, const char* const message, const double wPerc, const double hPerc, const int64_t x, const int64_t y, const int64_t w, const int64_t h, const uint8_t fr, const uint8_t fg, const uint8_t fb, const uint8_t fa, const uint8_t br, const uint8_t bg, const uint8_t bb, const uint8_t ba, const uint8_t thickness, const char* const alphaString, const size_t font, const size_t texture, const int64_t tx, const int64_t ty, const int64_t tw, const int64_t th, const bool offset, const size_t line, const char* const errorfile);

	// draws a horizontal button at x, y, w, h returns true if clicked

	extern bool PLEX_drawArrowButtonInt(const size_t order, const int64_t x, const int64_t y, const int64_t w, const int64_t h, const uint8_t fr, const uint8_t fg, const uint8_t fb, const uint8_t fa, const uint8_t br, const uint8_t bg, const uint8_t bb, const uint8_t ba, const uint8_t thickness, const bool flip, const bool offset, const size_t line, const char* const errorfile);

	// draws an button created from an icon (ie. printed texture with border) and returns true if clicked

	extern bool PLEX_drawIconButtonInt(const size_t order, const bool selected, const int64_t x, const int64_t y, const int64_t w, const int64_t h, const int64_t tx, const int64_t ty, const int64_t tw, const int64_t th, const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a, const uint8_t sr, const uint8_t sg, const uint8_t sb, const uint8_t sa, const uint8_t ovr, const int64_t ovb, const int64_t ovg, const int64_t ova, const uint8_t sovr, const int64_t sovb, const int64_t sovg, const int64_t sova, const uint8_t thickness, const size_t texture, const bool offset, const size_t line, const char* const errorfile);

	// draws a button from two different textures (can technically be the same texture) from points tx, ty, tw, th and tx2, ty2, tw2, th2 and shows the latter when highlighted. Returns true if clicked.

	extern bool PLEX_twoImageButtonInt(const size_t order, const bool selected, const int64_t x, const int64_t y, const int64_t w, const int64_t h, const int64_t tx, const int64_t ty, const int64_t tw, const int64_t th, const int64_t tx2, const int64_t ty2, const int64_t tw2, const int64_t th2, const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a, const uint8_t sr, const uint8_t sg, const uint8_t sb, const uint8_t sa, const uint8_t thickness, const size_t texture1, const size_t texture2, const bool offset, const size_t line, const char* const errorfile);

	// draws a multiline text box

	extern void PLEX_drawTextBoxInt(const size_t order, const char* const message, const double wPerc, const double hPerc, const uint8_t fr, const uint8_t fg, const uint8_t fb, const uint8_t fa, const int64_t x, const int64_t y, const int64_t w, const int64_t h, const uint32_t fw, const uint32_t fh, const double ipx, const double ipy, const double ipw, const double iph, const uint8_t thickness, const char* const alphaString, const size_t fontTexture, const size_t texture, const int64_t tx, const int64_t ty, const int64_t tw, const int64_t th, const double lineSpacePerc, const bool offset, const size_t line, const char* const errorfile);

	// draws a multiline text box but with control over the foreground and background color (fr, fg, fb, fa for foreground; br, bg, ba for background)

	extern void PLEX_drawTextBoxTintedInt(const size_t order, const char* const message, const double wPerc, const double hPerc, const uint8_t fr, const uint8_t fg, const uint8_t fb, const uint8_t fa, const uint8_t br, const uint8_t bg, const uint8_t bb, const uint8_t ba, const int64_t x, const int64_t y, const int64_t w, const int64_t h, const uint32_t fw, const uint32_t fh, const double ipx, const double ipy, const double ipw, const double iph, const uint8_t thickness, const char* const alphaString, const size_t fontTexture, const size_t texture, const int64_t tx, const int64_t ty, const int64_t tw, const int64_t th, const double lineSpacePerc, const bool offset, const size_t line, const char* const errorfile);

	// draws a multiline textbox but with scrolling. Is passed a scrolling value of pageScroll and returns an incremented or decremented value if scrolled forward or back

	extern size_t PLEX_drawTextBoxScrollingInt(const size_t order, const char* const message, const double wPerc, const double hPerc, const uint8_t fr, const uint8_t fg, const uint8_t fb, const uint8_t fa, const int64_t x, const int64_t y, const int64_t w, const int64_t h, const uint32_t fw, const uint32_t fh, const double ipx, const double ipy, const double ipw, const double iph, const uint8_t thickness, const char* const alphaString, const size_t fontTexture, const size_t texture, const int64_t tx, const int64_t ty, const int64_t tw, const int64_t th, const double lineSpacePerc, const size_t pageScroll, const bool offset, const size_t line, const char* const errorfile);

	// draws a multiline textbox but with scrolling. Is passed a scrolling value of pageScroll and returns an incremented or decremented value if scrolled forward or back but with control over the foreground and background color (fr, fg, fb, fa for foreground; br, bg, ba for background)

	extern size_t PLEX_drawTextBoxScrollingTintedInt(const size_t order, const char* const message, const double wPerc, const double hPerc, const uint8_t fr, const uint8_t fg, const uint8_t fb, const uint8_t fa, const uint8_t br, const uint8_t bg, const uint8_t bb, const uint8_t ba, const int64_t x, const int64_t y, const int64_t w, const int64_t h, const uint32_t fw, const uint32_t fh, const double ipx, const double ipy, const double ipw, const double iph, const uint8_t thickness, const char* const alphaString, const size_t fontTexture, const size_t texture, const int64_t tx, const int64_t ty, const int64_t tw, const int64_t th, const double lineSpacePerc, const size_t pageScroll, const bool offset, const size_t line, const char* const errorfile);

	// draws a floating tooltip offset from the mouse by dx and dy if the mouse is over spot hx, hy, hw, hh.

	extern void PLEX_drawTooltipInt(const size_t order, const char* const message, const double wPerc, const double hPerc, const uint8_t br, const uint8_t bg, const uint8_t bb, const uint8_t ba, const int64_t hx, const int64_t hy, const int64_t hw, const int64_t hh, const int64_t dx, const int64_t dy, const int64_t lw, const int64_t lh, const double ipx, const double ipy, const double ipw, const double iph, const uint8_t thickness, const char* const alphaString, const size_t fontTexture, const size_t texture, const int64_t tx, const int64_t ty, const int64_t tw, const int64_t th, const bool offset, const size_t line, const char* const errorfile);

	// draws a horizontal or vertical charge bar with percentage of fullness

	extern void PLEX_drawChargeBarInt(const size_t order, const double fullness, const int64_t x, const int64_t y, const int64_t w, const int64_t h, const uint8_t fr, const uint8_t fg, const uint8_t fb, const uint8_t fa, const uint8_t br, const uint8_t bg, const uint8_t bb, const uint8_t ba, const uint8_t thickness, const bool vertical, const bool offset, const size_t line, const char* const errorfile);

	// draws a panorama shot. What this does is it keeps the middle part of a texture adjusted to the size of the offset and stretches the sides to fit over the parts outside of the offset.

	extern void PLEX_drawPanoramaInt(const size_t order, const size_t texture, const size_t line, const char* const errorfile);

	// takes and returns the index of a screencap

	extern size_t PLEX_takeScreencapInt(const bool offset, const size_t errorline, const char* const errorfile);

// start, update, end functions ---------------------------------------------------------------------------------------------

	// starts the graphics system. Returns false on failure (which will terminate execution). You likely never need to manually call this as PLEX_start does.

	extern bool PLEX_startGraphicsInt(const size_t errorline, const char* const errorfile);

	// updates the graphics system. Returns false on failure (which will terminate execution). You likely never need to manually call this as PLEX_update does.

	extern bool PLEX_updateGraphicsInt(SDL_Window* window, const uint32_t w, const uint32_t h, const size_t errorline, const char* const errorfile);

	// ends the graphics system. You likely never need to manually call this as PLEX_end does.

	extern void PLEX_endGraphicsInt(const size_t errorline, const char* const errorfile);

// setters ------------------------------------------------------------------------------------------------------------------

	// sets the target for texture drawing PLEX_LOW_NOTARGET puts it on the screen

	extern void PLEX_setTextureTargetInt(const size_t texture, const size_t errorline, const char* const errorfile);

	// sets the screen refresh color by r, g, b

	extern void PLEX_setRefreshColorInt(const uint8_t r, const uint8_t g, const uint8_t b, const size_t errorline, const char* const errorfile);

	// sets the blend mode based on SDL_BlendMode. Even if not an SDL backend the graphics system should be expected to compensate.

	extern void PLEX_drawBlendModeInt(const SDL_BlendMode mode, const size_t errorline, const char* const errorfile);

// getters ------------------------------------------------------------------------------------------------------------------

	// sets the texture drawing target back to the screen

	extern void PLEX_unsetTextureTargetInt(const size_t errorline, const char* const errorfile);

	// shows all tooltips at once even if not highlighted. Good for debugging.

	extern void PLEX_showAllTooltips();

	// toggles tooltips to be all shown at once or not. Also for debugging.

	extern void PLEX_toggleTooltips();

	// highlights all clickables for debugging purposes.

	extern void PLEX_showAllClickables();

#ifdef __cplusplus
}
#endif

#endif
