#include "windowing/graphics.h"

// NOTE: global function descriptions in header.

// structs ------------------------------------------------------------------------------------------------------------------

typedef struct
{
	int64_t x, y, w, h;
	uint8_t r, g, b, a, thickness;
} PLEX_GRAPHICS_INSTRUCT_RECT;

typedef struct
{
	int64_t x, y, x2, y2;
	uint8_t r, g, b, a, thickness;
} PLEX_GRAPHICS_INSTRUCT_LINE;

typedef struct
{
	int64_t x, y;
	int64_t length;
	double direction;
	uint8_t r, g, b, a, thickness;
} PLEX_GRAPHICS_INSTRUCT_LINE2;

typedef struct
{
	int64_t x, y, w, h;
	uint8_t r, g, b, a;
} PLEX_GRAPHICS_INSTRUCT_FILL_RECT;

typedef struct
{
	size_t texture;
	int64_t fx, fy, fw, fh, tx, ty, tw, th;
	uint8_t r, g, b;
	SDL_BlendMode textureBlendMode;
} PLEX_GRAPHICS_INSTRUCT_TEXTURE;

typedef struct
{
	size_t texture;
	int64_t fx, fy, fw, fh, tx, ty, tw, th;
	uint8_t r, g, b;
	double angle;
	SDL_BlendMode textureBlendMode;
} PLEX_GRAPHICS_INSTRUCT_TEXTURE_ROTATED;

typedef struct
{
	double wPerc, hPerc;
	int64_t ox, oy, ow, oh;
	uint8_t symbol, r, g, b;
	const char* alphaString;
	size_t texture;
	bool offset;
	SDL_BlendMode textureBlendMode;
} PLEX_GRAPHICS_INSTRUCT_FONT_LETTER;

typedef struct
{
	uint8_t r, g, b, a;
} PLEX_GRAPHICS_INSTRUCT_CLEAR;

typedef union
{
	PLEX_GRAPHICS_INSTRUCT_RECT rect;
	PLEX_GRAPHICS_INSTRUCT_LINE line;
	PLEX_GRAPHICS_INSTRUCT_LINE2 line2;
	PLEX_GRAPHICS_INSTRUCT_FILL_RECT fillRect;
	PLEX_GRAPHICS_INSTRUCT_TEXTURE texture;
	PLEX_GRAPHICS_INSTRUCT_TEXTURE_ROTATED textureRotated;
	PLEX_GRAPHICS_INSTRUCT_FONT_LETTER letter;
	PLEX_GRAPHICS_INSTRUCT_CLEAR clear;
} PLEX_GRAPHICS_INSTRUCT_CONTENTS;

typedef enum
{
	PLEX_GRAPHICS_INSTRUCT_TYPE_RECT = 0,
	PLEX_GRAPHICS_INSTRUCT_TYPE_LINE = 1,
	PLEX_GRAPHICS_INSTRUCT_TYPE_LINE2 = 2,
	PLEX_GRAPHICS_INSTRUCT_TYPE_FILL_RECT = 3,
	PLEX_GRAPHICS_INSTRUCT_TYPE_TEXTURE = 4,
	PLEX_GRAPHICS_INSTRUCT_TYPE_TEXTURE_ROTATE = 5,
	PLEX_GRAPHICS_INSTRUCT_TYPE_FONT_LETTER = 6,
	PLEX_GRAPHICS_INSTRUCT_TYPE_CLEAR = 7
} PLEX_GRAPHICS_INSTRUCT_TYPE;

typedef struct
{
	size_t order;
	bool offset;
	SDL_BlendMode drawBlendMode;
	PLEX_LOW_TEXTURE target;
	PLEX_GRAPHICS_INSTRUCT_TYPE type;
	PLEX_GRAPHICS_INSTRUCT_CONTENTS contents;
} PLEX_GRAPHICS_INSTRUCT;

// static values ------------------------------------------------------------------------------------------------------------

static bool p_running = false;

static PLEX_EXPANDARRAY* p_drawList = NULL;

static size_t p_screenPlate = 0;

static bool p_showClickables = false;
static bool p_showTooltips = false;
static bool p_toggleTooltips = false;

static uint8_t p_refreshR = 0;
static uint8_t p_refreshG = 0;
static uint8_t p_refreshB = 0;

// static functions ---------------------------------------------------------------------------------------------------------

// NOTE: any function that is labeled as 'as called from the draw stack' is a function that is called normally during the cycling through the drawstack. PLEX does not draw anything when it's immediately called but rather stores instructions as in the 'INSTRUCT' structs and enums above. This way instructions can be sorted by the 'order' index rather than drawn in order of call. These functions manage the direct drawing of both tinted and non-tinted variations.

// draws line from two points as called from the draw stack

static void p_drawLine(const int64_t x, const int64_t y, const int64_t x2, const int64_t y2, const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a, const uint8_t thickness, const bool offset, const SDL_BlendMode blendMode)
{
	const double sideX = x2 - (double)x;
	const double sideY = y2 - (double)y;

	const double len = sqrt((sideY * sideY) + (sideX * sideX));
	const double rad = atan2(sideY, sideX);
	const double xshift = cos(rad);
	const double yshift = sin(rad);

	const int64_t ilen = len;

	double xIt = x;
	double yIt = y;

	SDL_Rect dots[ilen];

	for(size_t z = 0; z < ilen; ++z)
	{
		dots[z].x = xIt - thickness/2 + (offset * PLEX_WOFFSET());
		dots[z].y = yIt - thickness/2 + (offset * PLEX_HOFFSET());
		dots[z].w = thickness;
		dots[z].h = thickness;

		xIt += xshift;
		yIt += yshift;
	}

	PLEX_low_fillRects(r, g, b, a, dots, ilen, blendMode);
}

// draws line from a point, length, and direction as called from the draw stack

static void p_drawLine2(const int64_t x, const int64_t y, const int64_t length, const double direction, const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a, const uint8_t thickness, const bool offset, const SDL_BlendMode blendMode)
{
	const double rads = PLEX_radians(direction);

	const int64_t x2 = x + length * cos(rads);
	const int64_t y2 = y + length * sin(rads);

	p_drawLine(x, y, x2, y2, r, g, b, a, thickness, offset, blendMode);
}

// draws rectangle as called from the draw stack

static void p_drawRect(const int64_t x, const int64_t y, const int64_t w, const int64_t h, const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a, const uint8_t thickness, const bool offset, const SDL_BlendMode blendMode)
{
	const int64_t aX = x + (offset * PLEX_WOFFSET());
	const int64_t aY = y + (offset * PLEX_HOFFSET());

	SDL_Rect s[4];

	s[0].x = aX;
	s[0].y = aY;
	s[0].w = w;
	s[0].h = thickness;

	s[1].x = aX + w - thickness;
	s[1].y = aY;
	s[1].w = thickness;
	s[1].h = h;

	s[2].x = aX;
	s[2].y = aY + h - thickness;
	s[2].w = w;
	s[2].h = thickness;

	s[3].x = aX;
	s[3].y = aY;
	s[3].w = thickness;
	s[3].h = h;

	PLEX_low_fillRects(r, g, b, a, s, 4, blendMode);
}

// fills a rectangle as called from the draw stack

static void p_fillRect(const int64_t x, const int64_t y, const int64_t w, const int64_t h, const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a, const bool offset, const SDL_BlendMode blendMode)
{
	const int64_t aX = x + (offset * PLEX_WOFFSET());
	const int64_t aY = y + (offset * PLEX_HOFFSET());

	SDL_Rect area;

	area.x = aX;
	area.y = aY;
	area.w = w;
	area.h = h;

	PLEX_low_fillRect(r, g, b, a, &area, blendMode);
}

// prints a texture as called from the draw stack

static void p_printTexture(const size_t texture, const int64_t fx, const int64_t fy, const int64_t fw, const int64_t fh, const int64_t tx, const int64_t ty, const int64_t tw, const int64_t th, const uint8_t r, const uint8_t g, const uint8_t b, const bool offset, const SDL_BlendMode blendMode, const size_t errorline, const char* const errorfile)
{
	PLEX_LOW_TEXTURE target = PLEX_innerTextureInt(texture, errorline, errorfile);

	SDL_Rect from, to;

	uint8_t or = 255, og = 255, ob = 255;

	if(PLEX_low_isTextureNull(target))
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ISNULLTEXTURE, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_TEXTURE_TEXTURE, PLEX_ERRORMESS_GRAPHICS_ONPRINTINGTEXTURE_DRAWSTACK, errorline, errorfile);
		return;
	}

	from.x = fx;
	from.y = fy;
	from.w = fw;
	from.h = fh;

	to.x = tx + (offset * PLEX_WOFFSET());
	to.y = ty + (offset * PLEX_HOFFSET());
	to.w = tw;
	to.h = th;

	PLEX_low_getTintTexturesRGBInt(target, &or, &og, &ob, errorline, errorfile);

	PLEX_low_tintTexturesRGBInt(&target, r, g, b, errorline, errorfile);
	PLEX_low_copyTexture(target, &from, &to, blendMode);
	PLEX_low_tintTexturesRGBInt(&target, or, og, ob, errorline, errorfile);
}

// prints a rotated texture as called from the drawstack

static void p_printTextureRotated(const size_t texture, const int64_t fx, const int64_t fy, const int64_t fw, const int64_t fh, const int64_t tx, const int64_t ty, const int64_t tw, const int64_t th, const uint8_t r, const uint8_t g, const uint8_t b, const double angle,  const bool offset, const SDL_BlendMode blendMode, const size_t errorline, const char* const errorfile)
{
	PLEX_LOW_TEXTURE target = PLEX_innerTextureInt(texture, errorline, errorfile);

	SDL_Rect from, to;

	uint8_t or = 255, og = 255, ob = 255;

	if(PLEX_low_isTextureNull(target))
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ISNULLTEXTURE, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_TEXTURE_TEXTURE, PLEX_ERRORMESS_GRAPHICS_ONPRINTINGTEXTUREROTATED_DRAWSTACK, errorline, errorfile);
		return;
	}

	from.x = fx;
	from.y = fy;
	from.w = fw;
	from.h = fh;

	to.x = tx + (offset * PLEX_WOFFSET());
	to.y = ty + (offset * PLEX_HOFFSET());
	to.w = tw;
	to.h = th;

	PLEX_low_getTintTexturesRGBInt(target, &or, &og, &ob, errorline, errorfile);

	PLEX_low_tintTexturesRGBInt(&target, r, g, b, errorline, errorfile);
	PLEX_low_copyTextureRotated(target, &from, &to, angle, blendMode);
	PLEX_low_tintTexturesRGBInt(&target, or, og, ob, errorline, errorfile);
}

// prints a font letter as called from the drawstack

static void p_printFontLetter(const double wPerc, const double hPerc, const int64_t ox, const int64_t oy, const int64_t ow, const int64_t oh, const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t symbol, const char* const alphaString, const size_t texture, const bool offset, const SDL_BlendMode blendMode, const size_t errorline, const char* const errorfile)
{
	PLEX_LOW_TEXTURE target = PLEX_innerTextureInt(texture, errorline, errorfile);

	size_t symbolIt = 0;

	char next = 0;

	// must be uint32_t type:
	uint32_t tW = 0;
	uint32_t tH = 0;

	int64_t lW = 0;

	uint8_t or = 0;
	uint8_t og = 0;
	uint8_t ob = 0;

	SDL_Rect crop, output;

	next = alphaString[symbolIt];

	while(next != '\0')
	{
		if(symbol == next) break;
		symbolIt++;
		next = alphaString[symbolIt];
	}

	if(next == '\0') return;

	PLEX_textureWHInt(texture, &tW, &tH, errorline, errorfile);

	lW = 1/wPerc;

	crop.x = (symbolIt % lW) * wPerc * tW;
	crop.y = (symbolIt/lW) * hPerc * tH;
	crop.w = tW * wPerc;
	crop.h = tH * hPerc;

	output.x = ox + (offset * PLEX_WOFFSET());
	output.y = oy + (offset * PLEX_HOFFSET());
	output.w = ow * PLEX_STANDNUM_LETTERBUFF;
	output.h = oh * PLEX_STANDNUM_LETTERBUFF;

	PLEX_low_getTintTexturesRGBInt(target, &or, &og, &ob, errorline, errorfile);

	PLEX_low_tintTexturesRGBInt(&target, r, g, b, errorline, errorfile);
	PLEX_low_copyTexture(target, &crop, &output, blendMode);
	PLEX_low_tintTexturesRGBInt(&target, or, og, ob, errorline, errorfile);
}

// clears the entire screen as called from the drawstack

static void p_clear(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a, const size_t errorline, const char* const errorfile)
{
	const SDL_BlendMode oldMode = PLEX_low_getRenderBlendModeInt(errorline, errorfile);

	p_fillRect(0, 0, PLEX_WW(true), PLEX_WH(true), r, g, b, a, true, SDL_BLENDMODE_NONE);

	PLEX_low_setBlendTarget(oldMode);
}

// adds an instruction to the drawlist to later be drawn

static void p_addDrawList(PLEX_GRAPHICS_INSTRUCT_TYPE type, PLEX_GRAPHICS_INSTRUCT_CONTENTS contents, const size_t order, const bool offset, const size_t errorline, const char* const errorfile)
{
	PLEX_LOW_TEXTURE renderTarget = PLEX_low_getRenderTargetInt(errorline, errorfile);

	PLEX_GRAPHICS_INSTRUCT* instruct = NULL;

	size_t insert = PLEX_expandArrayCount(p_drawList) - 1;

	for(size_t z = 0; z < p_drawList->count; ++z)
	{
		PLEX_GRAPHICS_INSTRUCT* entry = (PLEX_GRAPHICS_INSTRUCT*)PLEX_getExpandArrayEntryInt(z, p_drawList, errorline, errorfile);

		if(entry == NULL)
		{
			PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_GRAPHICS_ONADDINGTODRAWLIST, PLEX_ERRORMESS_GENERIC_ENTRY, errorline, errorfile);
			return;
		}

		if((!PLEX_low_compTextures(entry->target, renderTarget) && PLEX_low_lessTextures(entry->target, renderTarget)) || (PLEX_low_compTextures(entry->target, renderTarget) && entry->order < order))
		{
			insert = z;

			PLEX_incrementExpandArrayInt(p_drawList, errorline, errorfile);

			for(size_t u = p_drawList->count - 1; u > z; --u)
			{
				PLEX_GRAPHICS_INSTRUCT* entry2 = (PLEX_GRAPHICS_INSTRUCT*)PLEX_getExpandArrayEntryInt(u, p_drawList, errorline, errorfile);
				PLEX_GRAPHICS_INSTRUCT* entry3 = (PLEX_GRAPHICS_INSTRUCT*)PLEX_getExpandArrayEntryInt(u - 1, p_drawList, errorline, errorfile);

				memcpy(entry2, entry3, sizeof(PLEX_GRAPHICS_INSTRUCT));
			}

			break;
		}
	};

	if(!p_drawList->count || insert == p_drawList->count - 1)
	{
		if(!PLEX_incrementExpandArrayInt(p_drawList, errorline, errorfile))
		{
			PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_INCREMENT, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_GRAPHICS_ONADDINGTODRAWLIST, PLEX_ERRORMESS_GENERIC_ENTRY, errorline, errorfile);
			return;
		}

		instruct = (PLEX_GRAPHICS_INSTRUCT*)PLEX_getExpandArrayLastInt(p_drawList, errorline, errorfile);

		if(instruct == NULL)
		{
			PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ACQUIRELAST, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_GRAPHICS_ONADDINGTODRAWLIST, PLEX_ERRORMESS_GENERIC_ENTRY, errorline, errorfile);
			return;
		}
	}else{
		instruct = (PLEX_GRAPHICS_INSTRUCT*)PLEX_getExpandArrayEntryInt(insert, p_drawList, errorline, errorfile);

		if(instruct == NULL)
		{
			PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_GRAPHICS_ONADDINGTODRAWLIST, PLEX_ERRORMESS_GENERIC_ENTRY, errorline, errorfile);
			return;
		}
	}

	instruct->order = order;
	instruct->offset = offset;
	instruct->type = type;
	instruct->target = renderTarget;
	instruct->drawBlendMode = PLEX_low_getRenderBlendModeInt(errorline, errorfile);
	memcpy(&instruct->contents, &contents, sizeof(contents));
}

// draws the drawlist (called in update graphics function)

static void p_drawDrawList(const size_t errorline, const char* const errorfile)
{
	for(size_t ze = 0; ze < PLEX_expandArrayCount(p_drawList); ++ze)
	{
		PLEX_GRAPHICS_INSTRUCT* entry = (PLEX_GRAPHICS_INSTRUCT*)PLEX_getExpandArrayEntryInt(ze, p_drawList, errorline, errorfile);

		if(entry == NULL)
		{
			PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_GRAPHICS_ONDRAWDRAWLIST, PLEX_ERRORMESS_GENERIC_ENTRY, errorline, errorfile);
			return;
		}

		PLEX_low_setRenderTarget(entry->target);

		switch(entry->type)
		{
			case PLEX_GRAPHICS_INSTRUCT_TYPE_RECT:
				p_drawRect(entry->contents.rect.x, entry->contents.rect.y, entry->contents.rect.w, entry->contents.rect.h, entry->contents.rect.r, entry->contents.rect.g, entry->contents.rect.b, entry->contents.rect.a, entry->contents.rect.thickness, entry->offset, entry->drawBlendMode);
			break;

			case PLEX_GRAPHICS_INSTRUCT_TYPE_LINE:
				p_drawLine(entry->contents.line.x, entry->contents.line.y, entry->contents.line.x2, entry->contents.line.y2, entry->contents.line.r, entry->contents.line.g, entry->contents.line.b, entry->contents.line.a, entry->contents.line.thickness, entry->offset, entry->drawBlendMode);
			break;

			case PLEX_GRAPHICS_INSTRUCT_TYPE_LINE2:
				p_drawLine2(entry->contents.line2.x, entry->contents.line2.y, entry->contents.line2.length, entry->contents.line2.direction, entry->contents.line2.r, entry->contents.line2.g, entry->contents.line2.b, entry->contents.line2.a, entry->contents.line2.thickness, entry->offset, entry->drawBlendMode);
			break;

			case PLEX_GRAPHICS_INSTRUCT_TYPE_FILL_RECT:
				p_fillRect(entry->contents.fillRect.x, entry->contents.fillRect.y, entry->contents.fillRect.w, entry->contents.fillRect.h, entry->contents.fillRect.r, entry->contents.fillRect.g, entry->contents.fillRect.b, entry->contents.fillRect.a, entry->offset, entry->drawBlendMode);
			break;

			case PLEX_GRAPHICS_INSTRUCT_TYPE_TEXTURE:
				p_printTexture(entry->contents.texture.texture, entry->contents.texture.fx, entry->contents.texture.fy, entry->contents.texture.fw, entry->contents.texture.fh, entry->contents.texture.tx, entry->contents.texture.ty, entry->contents.texture.tw, entry->contents.texture.th, entry->contents.texture.r, entry->contents.texture.g, entry->contents.texture.b, entry->offset, entry->drawBlendMode, errorline, errorfile);
			break;

			case PLEX_GRAPHICS_INSTRUCT_TYPE_TEXTURE_ROTATE:
				p_printTextureRotated(entry->contents.textureRotated.texture, entry->contents.textureRotated.fx, entry->contents.textureRotated.fy, entry->contents.textureRotated.fw, entry->contents.textureRotated.fh, entry->contents.textureRotated.tx, entry->contents.textureRotated.ty, entry->contents.textureRotated.tw, entry->contents.textureRotated.th, entry->contents.textureRotated.r, entry->contents.textureRotated.g, entry->contents.textureRotated.b, entry->contents.textureRotated.angle, entry->offset, entry->drawBlendMode, errorline, errorfile);
			break;

			case PLEX_GRAPHICS_INSTRUCT_TYPE_FONT_LETTER:
				p_printFontLetter(entry->contents.letter.wPerc, entry->contents.letter.hPerc, entry->contents.letter.ox, entry->contents.letter.oy, entry->contents.letter.ow, entry->contents.letter.oh, entry->contents.letter.r, entry->contents.letter.g, entry->contents.letter.b, entry->contents.letter.symbol, entry->contents.letter.alphaString, entry->contents.letter.texture, entry->offset, entry->drawBlendMode, errorline, errorfile);
			break;

			case PLEX_GRAPHICS_INSTRUCT_TYPE_CLEAR:
				p_clear(entry->contents.clear.r, entry->contents.clear.g, entry->contents.clear.b, entry->contents.clear.a, errorline, errorfile);
			break;
		}
	}

	PLEX_low_setRenderTarget(PLEX_innerTextureInt(p_screenPlate, errorline, errorfile));

	PLEX_destroyExpandArrayInt(&p_drawList, errorline, errorfile);
	p_drawList = PLEX_genExpandArrayInt(PLEX_getMemProfileDrawlistPreload(), sizeof(PLEX_GRAPHICS_INSTRUCT), errorline, errorfile);

	if(p_drawList == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ALLOCFAIL, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_GRAPHICS_ONDRAWDRAWLIST, PLEX_ERRORMESS_GRAPHICS_DRAWLIST, errorline, errorfile);
		return;
	}
}

// gets the grayscale value of an rgb color. pass as uint16_t rather than uint8_t to prevent cast overflow issues

static uint8_t p_getTintAmount(const uint16_t r, const uint16_t g, const uint16_t b)
{
	const uint16_t tintDeficit = (r + g + b)/3.0;

	return tintDeficit;
}

// gets the inverted grayscale value of an rgb color.

static uint8_t p_getReverseTintAmount(const uint16_t r, const uint16_t g, const uint16_t b)
{
	return 255 - p_getTintAmount(r, g, b);
}

// a base function to manage all variations when it comes to drawing a tinted textbox

static size_t p_drawTextBoxTintedBase(const size_t order, const char* const message, const double wPerc, const double hPerc, const uint8_t fr, const uint8_t fg, const uint8_t fb, const uint8_t fa, const uint8_t br, const uint8_t bg, const uint8_t bb, const uint8_t ba, const int64_t x, const int64_t y, const int64_t w, const int64_t h, const uint32_t fw, const uint32_t fh, const double ipx, const double ipy, const double ipw, const double iph, const uint8_t thickness, const char* const alphaString, const size_t fontTexture, const size_t texture, const int64_t tx, const int64_t ty, const int64_t tw, const int64_t th, const double lineSpacePerc, const bool scroll, const size_t lineAmount, const bool offset, const size_t errorline, const char* const errorfile)
{
	const int64_t ix = x + ipx * w;
	const int64_t iy = y + ipy * h;
	const int64_t iw = ipw * w;
	const int64_t ih = iph * h;

	char word[1024];
	size_t wordLen = 0;

	int64_t px = ix;
	int64_t py = iy;
	int64_t apy = iy;

	size_t it = 0;
	size_t wordEnd = 0;

	uint64_t next = 0;

	size_t pageScroll = lineAmount;
	size_t page = 0;

	bool scrollForward = false;

	if(texture) PLEX_printTextureTintedInt(order, texture, tx, ty, tw, th, x, y, w, h, br, bg, bb, offset, errorline, errorfile);
	else PLEX_fillRectInt(order, x, y, w, h, br, bg, bb, ba, offset, errorline, errorfile);

	word[0] = '\0';
	next = message[0];
	++it;

	while(next != '\0' || wordLen)
	{
		if(next != ' ' && next != '\r' && next != '\t' && next != '\n' && next != '\0')
		{
			if(wordLen < 1023)
			{
				word[wordLen] = next;
				word[wordLen + 1] = '\0';
				++wordLen;
			}else break;
		}else{
			if(wordLen)
			{
				const uint32_t wordWidth = wordLen * fw;

				const bool onPage = page >= pageScroll;

				if(px + wordWidth > x + iw)
				{
					const double lh = fh * (1 + lineSpacePerc);

					px = ix;
					py += lh;
					if(onPage) apy += lh;

					if(py + lh > iy + ih)
					{
						if(onPage)
						{
							scrollForward = true;
							wordLen = 0;
							it = wordEnd;
							break;
						}else{
							py = apy;
							++page;
							continue;
						}
					}
				}

				if(onPage) PLEX_printFontStringTintedInt(order, wPerc, hPerc, px, apy, fw, fh, fr, fg, fb, (char*)word, alphaString, fontTexture, offset, errorline, errorfile);

				px += wordWidth + fw;
				wordEnd = it;

				word[0] = '\0';
				wordLen = 0;
			}
		}

		if(next != '\0')
		{
			next = message[it];

			++it;
		}
	}

	PLEX_drawRectInt(order, x, y, w, h, fr, fg, fb, fa, thickness, offset, errorline, errorfile);

	if(PLEX_mouseInside(x, y, w, h, offset))
	{
		if(scroll)
		{
			if(scrollForward)
			{
				if(PLEX_drawArrowButtonInt(order, x + w - fh, y + h - fh, fh, fh, fr, fg, fb, fa, br, bg, bb, ba, thickness, false, offset, errorline, errorfile)) ++pageScroll;
			}

			if(pageScroll >= page && pageScroll)
			{
				if(PLEX_drawArrowButtonInt(order, x + w - (fh * 2), y + h - fh, fh, fh, fr, fg, fb, fa, br, bg, bb, ba, thickness, true, offset, errorline, errorfile)) --pageScroll;
			}
		}
	}

	return pageScroll;
}

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

// specialized functions ----------------------------------------------------------------------------------------------------=

void PLEX_clearInt(const size_t order, const uint8_t r, const uint8_t g, const uint8_t b, const size_t errorline, const char* const errorfile)
{
	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_GRAPHICS_ONCLEARSCREEN, errorline, errorfile);
		return;
	}

	PLEX_clearAlphaInt(order, r, g, b, 255, errorline, errorfile);
}

void PLEX_clearAlphaInt(const size_t order, const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a, const size_t errorline, const char* const errorfile)
{
	PLEX_GRAPHICS_INSTRUCT_CONTENTS contents;

	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_GRAPHICS_ONCLEARSCREENALPHA, errorline, errorfile);
		return;
	}

	contents.clear.r = r;
	contents.clear.g = g;
	contents.clear.b = b;
	contents.clear.a = a;

	p_addDrawList(PLEX_GRAPHICS_INSTRUCT_TYPE_CLEAR, contents, order, true, errorline, errorfile); // offset is irrelevant
}

void PLEX_clearOffsetAreaInt(const size_t order, const uint8_t r, const uint8_t g, const uint8_t b, const size_t errorline, const char* const errorfile)
{
	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_GRAPHICS_ONCLEARSCREENOFFSET, errorline, errorfile);
		return;
	}

	PLEX_clearOffsetAreaAlphaInt(order, r, g, b, 255, errorline, errorfile);
}

void PLEX_clearOffsetAreaAlphaInt(const size_t order, const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a, const size_t errorline, const char* const errorfile)
{
	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_GRAPHICS_ONCLEARSCREENOFFSETALPHA, errorline, errorfile);
		return;
	}

	PLEX_fillRectInt(order, 0, 0, PLEX_WOFFSET(), PLEX_WH(false), r, g, b, a, false, errorline, errorfile);
	PLEX_fillRectInt(order, PLEX_WW(false) - PLEX_WOFFSET(), 0, PLEX_WOFFSET(), PLEX_WH(false), r, g, b, a, false, errorline, errorfile);
	PLEX_fillRectInt(order, 0, 0, PLEX_WW(false), PLEX_HOFFSET(), r, g, b, a, false, errorline, errorfile);
	PLEX_fillRectInt(order, 0, PLEX_WH(false) - PLEX_HOFFSET(), PLEX_WW(false), PLEX_HOFFSET(), r, g, b, a, false, errorline, errorfile);
}

void PLEX_drawLineInt(const size_t order, const int64_t x, const int64_t y, const int64_t x2, const int64_t y2, const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a, const uint8_t thickness, const bool offset, const size_t errorline, const char* const errorfile)
{
	PLEX_GRAPHICS_INSTRUCT_CONTENTS contents;

	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_GRAPHICS_ONDRAWLINE1, errorline, errorfile);
		return;
	}

	contents.line.x = x > 0 ? x : 0;
	contents.line.y = y > 0 ? y : 0;
	contents.line.x2 = x2 > 0 ? x2 : 0;
	contents.line.y2 = y2 > 0 ? y2 : 0;

	contents.line.r = r;
	contents.line.g = g;
	contents.line.b = b;
	contents.line.a = a;

	contents.line.thickness = thickness;

	p_addDrawList(PLEX_GRAPHICS_INSTRUCT_TYPE_LINE, contents, order, offset, errorline, errorfile);
}

void PLEX_drawLine2Int(const size_t order, const int64_t x, int64_t y, const int64_t length, const double direction, const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a, const uint8_t thickness, const bool offset, const size_t errorline, const char* const errorfile)
{
	PLEX_GRAPHICS_INSTRUCT_CONTENTS contents;

	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_GRAPHICS_ONDRAWLINE2, errorline, errorfile);
		return;
	}

	contents.line2.x = x;
	contents.line2.y = y;
	contents.line2.length = length;
	contents.line2.direction = direction;

	contents.line2.r = r;
	contents.line2.g = g;
	contents.line2.b = b;
	contents.line2.a = a;

	contents.line2.thickness = thickness;

	p_addDrawList(PLEX_GRAPHICS_INSTRUCT_TYPE_LINE2, contents, order, offset, errorline, errorfile);
}

void PLEX_drawLine3Int(const size_t order, const PLEX_LINE line, const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a, const uint8_t thickness, const bool offset, const size_t errorline, const char* const errorfile)
{
	PLEX_MPREC rads = 0;

	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_GRAPHICS_ONDRAWLINE3, errorline, errorfile);
		return;
	}

	rads = PLEX_slopeToRads2(line.rise, line.run);

	PLEX_drawLine2Int(order, line.origin.x, line.origin.y, line.length, PLEX_degrees(rads), r, g, b, a, thickness, offset, errorline, errorfile);
}

void PLEX_drawRectInt(const size_t order, const int64_t x, const int64_t y, const int64_t w, const int64_t h, const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a, const uint8_t thickness, const bool offset, const size_t errorline, const char* const errorfile)
{
	PLEX_GRAPHICS_INSTRUCT_CONTENTS contents;

	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_GRAPHICS_ONDRAWRECT, errorline, errorfile);
		return;
	}

	contents.rect.x = x;
	contents.rect.y = y;
	contents.rect.w = w;
	contents.rect.h = h;

	contents.rect.r = r;
	contents.rect.g = g;
	contents.rect.b = b;
	contents.rect.a = a;

	contents.rect.thickness = thickness;

	p_addDrawList(PLEX_GRAPHICS_INSTRUCT_TYPE_RECT, contents, order, offset, errorline, errorfile);
}

void PLEX_fillRectInt(const size_t order, const int64_t x, const int64_t y, const int64_t w, const int64_t h, const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a, const bool offset, const size_t errorline, const char* const errorfile)
{
	PLEX_GRAPHICS_INSTRUCT_CONTENTS contents;

	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_GRAPHICS_ONFILLRECT, errorline, errorfile);
		return;
	}

	contents.fillRect.x = x;
	contents.fillRect.y = y;
	contents.fillRect.w = w;
	contents.fillRect.h = h;

	contents.fillRect.r = r;
	contents.fillRect.g = g;
	contents.fillRect.b = b;
	contents.fillRect.a = a;

	p_addDrawList(PLEX_GRAPHICS_INSTRUCT_TYPE_FILL_RECT, contents, order, offset, errorline, errorfile);
}

void PLEX_printTextureInt(const size_t order, const size_t texture, const int64_t fx, const int64_t fy, const int64_t fw, const int64_t fh, const int64_t tx, const int64_t ty, const int64_t tw, const int64_t th, const bool offset, const size_t errorline, const char* const errorfile)
{
	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_GRAPHICS_ONPRINTINGTEXTURE, errorline, errorfile);
		return;
	}

	PLEX_printTextureTintedInt(order, texture, fx, fy, fw, fh, tx, ty, tw, th, 255, 255, 255, offset, errorline, errorfile);
}

void PLEX_printTextureTintedInt(const size_t order, const size_t texture, const int64_t fx, const int64_t fy, const int64_t fw, const int64_t fh, const int64_t tx, const int64_t ty, const int64_t tw, const int64_t th, const uint8_t r, const uint8_t g, const uint8_t b, const bool offset, const size_t errorline, const char* const errorfile)
{
	PLEX_GRAPHICS_INSTRUCT_CONTENTS contents;

	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_GRAPHICS_ONPRINTINGTEXTURETINTED, errorline, errorfile);
		return;
	}

	contents.texture.texture = texture;

	contents.texture.fx = fx;
	contents.texture.fy = fy;
	contents.texture.fw = fw;
	contents.texture.fh = fh;

	contents.texture.tx = tx;
	contents.texture.ty = ty;
	contents.texture.tw = tw;
	contents.texture.th = th;

	contents.texture.r = r;
	contents.texture.g = g;
	contents.texture.b = b;

	contents.texture.textureBlendMode = PLEX_low_getTextureBlendModeInt(PLEX_innerTextureInt(texture, errorline, errorfile), errorline, errorfile);

	p_addDrawList(PLEX_GRAPHICS_INSTRUCT_TYPE_TEXTURE, contents, order, offset, errorline, errorfile);
}

void PLEX_printTextureRotatedInt(const size_t order, const size_t texture, const int64_t fx, const int64_t fy, const int64_t fw, const int64_t fh, const int64_t tx, const int64_t ty, const int64_t tw, const int64_t th, const double angle, const bool offset, const size_t errorline, const char* const errorfile)
{
	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_GRAPHICS_ONPRINTINGTEXTUREROTATED, errorline, errorfile);
		return;
	}

	PLEX_printTextureRotatedTintedInt(order, texture, fx, fy, fw, fh, tx, ty, tw, th, 255, 255, 255, angle, offset, errorline, errorfile);
}

void PLEX_printTextureRotatedTintedInt(const size_t order, const size_t texture, const int64_t fx, const int64_t fy, const int64_t fw, const int64_t fh, const int64_t tx, const int64_t ty, const int64_t tw, const int64_t th, const uint8_t r, const uint8_t g, const uint8_t b, const double angle, const bool offset, const size_t errorline, const char* const errorfile)
{
	PLEX_GRAPHICS_INSTRUCT_CONTENTS contents;

	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_GRAPHICS_ONPRINTINGTEXTUREROTATEDTINTED, errorline, errorfile);
		return;
	}

	contents.textureRotated.texture = texture;

	contents.textureRotated.fx = fx;
	contents.textureRotated.fy = fy;
	contents.textureRotated.fw = fw;
	contents.textureRotated.fh = fh;

	contents.textureRotated.tx = tx;
	contents.textureRotated.ty = ty;
	contents.textureRotated.tw = tw;
	contents.textureRotated.th = th;

	contents.textureRotated.r = r;
	contents.textureRotated.g = g;
	contents.textureRotated.b = b;

	contents.textureRotated.angle = angle;

	contents.textureRotated.textureBlendMode = PLEX_low_getTextureBlendModeInt(PLEX_innerTextureInt(texture, errorline, errorfile), errorline, errorfile);

	p_addDrawList(PLEX_GRAPHICS_INSTRUCT_TYPE_TEXTURE_ROTATE, contents, order, offset, errorline, errorfile);
}

void PLEX_printFontLetterInt(const size_t order, const double wPerc, const double hPerc, const int64_t ox, const int64_t oy, const int64_t ow, const int64_t oh, const uint8_t symbol, const char* const alphaString, const size_t texture, const bool offset, const size_t errorline, const char* const errorfile)
{
	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_GRAPHICS_ONLETTERPRINTING, errorline, errorfile);
		return;
	}

	if(hPerc <= 0)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_UNDERLIMIT, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GRAPHICS_ONLETTERPRINTING, PLEX_ERRORMESS_GENERIC_HPERC, errorline, errorfile);
		return;
	}

	if(hPerc > 1)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GRAPHICS_ONLETTERPRINTING, PLEX_ERRORMESS_GENERIC_HPERC, errorline, errorfile);
		return;
	}

	if(wPerc <= 0)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_UNDERLIMIT, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GRAPHICS_ONLETTERPRINTING, PLEX_ERRORMESS_GENERIC_WPERC, errorline, errorfile);
		return;
	}

	if(wPerc > 1)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GRAPHICS_ONLETTERPRINTING, PLEX_ERRORMESS_GENERIC_WPERC, errorline, errorfile);
		return;
	}

	if(alphaString == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GRAPHICS_ONLETTERPRINTING, PLEX_ERRORMESS_GENERIC_ALPHASTRING, errorline, errorfile);
		return;
	}

	if(alphaString[0] == '\0')
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_NOSTRINGLEN, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GRAPHICS_ONLETTERPRINTING, PLEX_ERRORMESS_GENERIC_ALPHASTRING, errorline, errorfile);
		return;
	}

	if(!texture)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ISNULLTEXTURE, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GRAPHICS_ONLETTERPRINTING, PLEX_ERRORMESS_TEXTURE_TEXTURE, errorline, errorfile);
		return;
	}

	PLEX_printFontLetterTintedInt(order, wPerc, hPerc, ox, oy, ow, oh, 255, 255, 255, symbol, alphaString, texture, offset, errorline, errorfile);
}

void PLEX_printFontLetterTintedInt(const size_t order, const double wPerc, const double hPerc, const int64_t ox, const int64_t oy, const int64_t ow, const int64_t oh, const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t symbol, const char* const alphaString, const size_t texture, const bool offset, const size_t errorline, const char* const errorfile)
{
	PLEX_GRAPHICS_INSTRUCT_CONTENTS contents;

	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_GRAPHICS_ONLETTERPRINTINGTINTED, errorline, errorfile);
		return;
	}

	if(alphaString == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GRAPHICS_ONLETTERPRINTINGTINTED, PLEX_ERRORMESS_GENERIC_ALPHASTRING, errorline, errorfile);
		return;
	}

	if(alphaString[0] == '\0')
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_NOSTRINGLEN, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GRAPHICS_ONLETTERPRINTINGTINTED, PLEX_ERRORMESS_GENERIC_ALPHASTRING, errorline, errorfile);
		return;
	}

	contents.letter.wPerc = wPerc;
	contents.letter.hPerc = hPerc;

	contents.letter.ox = ox;
	contents.letter.oy = oy;
	contents.letter.ow = ow;
	contents.letter.oh = oh;

	contents.letter.r = r;
	contents.letter.g = g;
	contents.letter.b = b;

	contents.letter.symbol = symbol;

	contents.letter.alphaString = alphaString;

	contents.letter.texture = texture;

	contents.letter.textureBlendMode = PLEX_low_getTextureBlendModeInt(PLEX_innerTextureInt(texture, errorline, errorfile), errorline, errorfile);

	if(contents.letter.ox + contents.letter.ow > PLEX_WW(false)) return;
	if(contents.letter.oy + contents.letter.oh > PLEX_WH(false)) return;

	p_addDrawList(PLEX_GRAPHICS_INSTRUCT_TYPE_FONT_LETTER, contents, order, offset, errorline, errorfile);
}

void PLEX_printFontStringInt(const size_t order, const double wPerc, const double hPerc, const int64_t ox, const int64_t oy, const int64_t ow, const int64_t oh, const char* const string, const char* const alphaString, const size_t texture, const bool offset, const size_t errorline, const char* const errorfile)
{
	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_GRAPHICS_ONSTRINGPRINTING, errorline, errorfile);
		return;
	}

	if(string == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GRAPHICS_ONSTRINGPRINTING, PLEX_ERRORMESS_GENERIC_STRING, errorline, errorfile);
		return;
	}

	if(string[0] == '\0')
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_NOSTRINGLEN, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GRAPHICS_ONSTRINGPRINTING, PLEX_ERRORMESS_GENERIC_STRING, errorline, errorfile);
		return;
	}

	if(alphaString == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GRAPHICS_ONSTRINGPRINTING, PLEX_ERRORMESS_GENERIC_ALPHASTRING, errorline, errorfile);
		return;
	}

	if(alphaString[0] == '\0')
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_NOSTRINGLEN, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GRAPHICS_ONSTRINGPRINTING, PLEX_ERRORMESS_GENERIC_ALPHASTRING, errorline, errorfile);
		return;
	}

	PLEX_printFontStringTintedInt(order, wPerc, hPerc, ox, oy, ow, oh, 255, 255, 255, string, alphaString, texture, offset, errorline, errorfile);
}

void PLEX_printFontStringTintedInt(const size_t order, const double wPerc, const double hPerc, const int64_t ox, const int64_t oy, const int64_t ow, const int64_t oh, const uint8_t r, const uint8_t g, const uint8_t b, const char* const string, const char* const alphaString, const size_t texture, const bool offset, const size_t errorline, const char* const errorfile)
{
	int64_t aoX = ox;

	size_t it = 0;

	char next = 0;

	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_GRAPHICS_ONSTRINGPRINTINGTINTED, errorline, errorfile);
		return;
	}

	if(string == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GRAPHICS_ONSTRINGPRINTINGTINTED, PLEX_ERRORMESS_GENERIC_STRING, errorline, errorfile);
		return;
	}

	if(string[0] == '\0')
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_NOSTRINGLEN, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GRAPHICS_ONSTRINGPRINTINGTINTED, PLEX_ERRORMESS_GENERIC_STRING, errorline, errorfile);
		return;
	}

	if(alphaString == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GRAPHICS_ONSTRINGPRINTINGTINTED, PLEX_ERRORMESS_GENERIC_ALPHASTRING, errorline, errorfile);
		return;
	}

	if(alphaString[0] == '\0')
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_NOSTRINGLEN, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GRAPHICS_ONSTRINGPRINTINGTINTED, PLEX_ERRORMESS_GENERIC_ALPHASTRING, errorline, errorfile);
		return;
	}

	next = string[it];

	while(next != '\0')
	{
		PLEX_printFontLetterTintedInt(order, wPerc, hPerc, aoX, oy, ow, oh, r, g, b, next, alphaString, texture, offset, errorline, errorfile);

		aoX += ow;
		it++;
		next = string[it];
	}
}

void PLEX_drawIconInt(const size_t order, const int64_t x, const int64_t y, const int64_t w, const int64_t h, const uint8_t br, const uint8_t bg, const uint8_t bb, const uint8_t ba, const size_t texture, const int64_t tx, const int64_t ty, const int64_t tw, const int64_t th, const uint8_t thickness, const bool offset, const size_t errorline, const char* const errorfile)
{
	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_GRAPHICS_ONDRAWICON, errorline, errorfile);
		return;
	}

	PLEX_printTextureInt(order, texture, tx, ty, tw, th, x, y, w, h, offset, errorline, errorfile);
	PLEX_drawRectInt(order, x, y, w, h, br, bg, bb, ba, thickness, offset, errorline, errorfile);
}

void PLEX_drawIconTintedInt(const size_t order, const int64_t x, const int64_t y, const int64_t w, const int64_t h, const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t br, const uint8_t bg, const uint8_t bb, const uint8_t ba, const size_t texture, const int64_t tx, const int64_t ty, const int64_t tw, const int64_t th, const uint8_t thickness, const bool offset, const size_t errorline, const char* const errorfile)
{
	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_GRAPHICS_ONDRAWICONTINTED, errorline, errorfile);
		return;
	}

	PLEX_printTextureTintedInt(order, texture, tx, ty, tw, th, x, y, w, h, r, g, b, offset, errorline, errorfile);
	PLEX_drawRectInt(order, x, y, w, h, br, bg, bb, ba, thickness, offset, errorline, errorfile);
}

void PLEX_drawLabelInt(const size_t order, const char* const message, const double wPerc, const double hPerc, const uint8_t fr, const uint8_t fg, const uint8_t fb, const uint8_t fa, const int64_t x, const int64_t y, const int64_t w, const int64_t h, const double ipx, const double ipy, const double ipw, const double iph, const uint8_t thickness, const char* const alphaString, const size_t fontTexture, const size_t texture, const int64_t tx, const int64_t ty, const int64_t tw, const int64_t th, const bool offset, const size_t errorline, const char* const errorfile)
{
	const int64_t ix = x + ipx * w;
	const int64_t iy = y + ipy * h;
	const int64_t iw = ipw * w;
	const int64_t ih = iph * h;

	size_t messLen = 0;

	int64_t letW = 0;

	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_GRAPHICS_ONLABELDRAWING, errorline, errorfile);
		return;
	}

	if(message == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GRAPHICS_ONLABELDRAWING, PLEX_ERRORMESS_GENERIC_MESSAGE, errorline, errorfile);
		return;
	}

	if(message[0] == '\0')
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_NOSTRINGLEN, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GRAPHICS_ONLABELDRAWING, PLEX_ERRORMESS_GENERIC_MESSAGE, errorline, errorfile);
		return;
	}

	if(alphaString == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GRAPHICS_ONLABELDRAWING, PLEX_ERRORMESS_GENERIC_ALPHASTRING, errorline, errorfile);
		return;
	}

	if(alphaString[0] == '\0')
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_NOSTRINGLEN, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GRAPHICS_ONLABELDRAWING, PLEX_ERRORMESS_GENERIC_ALPHASTRING, errorline, errorfile);
		return;
	}

	messLen = strlen(message);

	if(messLen < 8) messLen = 8;

	letW = iw/messLen;

	if(letW > h/2.0) letW = h/2.0;

	if(texture) PLEX_printTextureInt(order, texture, tx, ty, tw, th, x, y, w, h, offset, errorline, errorfile);
	else
	{
		const uint8_t tint = p_getReverseTintAmount(fr, fg, fb);

		PLEX_fillRectInt(order, x, y, w, h, tint, tint, tint, 255, offset, errorline, errorfile);
	}

	PLEX_printFontStringTintedInt(order, wPerc, hPerc, ix, iy, letW, ih, fr, fg, fb, message, alphaString, fontTexture, offset, errorline, errorfile);
	PLEX_drawRectInt(order, x, y, w, h, fr, fg, fb, fa, thickness, offset, errorline, errorfile);
}

bool PLEX_drawButtonInt(const size_t order, const char* const message, const double wPerc, const double hPerc, const int64_t x, const int64_t y, const int64_t w, const int64_t h, const uint8_t fr, const uint8_t fg, const uint8_t fb, const uint8_t fa, const uint8_t br, const uint8_t bg, const uint8_t bb, const uint8_t ba, const uint8_t thickness, const char* const alphaString, const size_t font, const size_t texture, const int64_t tx, const int64_t ty, const int64_t tw, const int64_t th, const bool offset, const size_t errorline, const char* const errorfile)
{
	bool inside = false;

	uint32_t fh = 0;
	uint32_t fw = 0;
	uint32_t hi = 0;

	size_t mlen = 0;
	uint32_t bw = 0;

	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_GRAPHICS_ONBUTTONDDRAWING, errorline, errorfile);
		return false;
	}

	if(message == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GRAPHICS_ONBUTTONDDRAWING, PLEX_ERRORMESS_GENERIC_MESSAGE, errorline, errorfile);
		return false;
	}

	if(message[0] == '\0')
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_NOSTRINGLEN, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GRAPHICS_ONBUTTONDDRAWING, PLEX_ERRORMESS_GENERIC_MESSAGE, errorline, errorfile);
		return false;
	}

	if(alphaString == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GRAPHICS_ONBUTTONDDRAWING, PLEX_ERRORMESS_GENERIC_ALPHASTRING, errorline, errorfile);
		return false;
	}

	if(alphaString[0] == '\0')
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_NOSTRINGLEN, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GRAPHICS_ONBUTTONDDRAWING, PLEX_ERRORMESS_GENERIC_ALPHASTRING, errorline, errorfile);
		return false;
	}

	inside = PLEX_mouseInside(x, y, w, h, offset);

	fh = (h - thickness) * 0.8;
	fw = fh * 0.5;
	hi = (h - fh)/2;

	mlen = message == NULL ? 0 : strlen(message);
	bw = 0;

	if(mlen && mlen < 8) mlen = 8;

	bw = mlen * fw;

	if(bw + (fw * 2) >= w)
	{
		fw = w/(mlen + 2);
		fh = fw * 2;

		bw = mlen * fw;
	}

	if(texture)
	{
		PLEX_printTextureTintedInt(order, texture, tx, ty, tw, th, x, y, w, h, br, bg, bb, offset, errorline, errorfile);

		if(inside) PLEX_fillRectInt(order, x, y, w, h, fr, fg, fb, fa * 0.5, offset, errorline, errorfile);
	}else{
		PLEX_fillRectInt(order, x, y, w, h, br, bg, bb, ba, offset, errorline, errorfile);

		if(inside)
		{
			PLEX_fillRectInt(order, x, y, w, h, fr, fg, fb, fa, offset, errorline, errorfile);
		}else{
			if(texture) PLEX_fillRectInt(order, x, y, w, h, fr, fg, fb, fa * 0.25, offset, errorline, errorfile);
		}
	}

	if(inside)
	{
		PLEX_drawRectInt(order, x, y, w, h, br, bg, bb, ba, thickness, offset, errorline, errorfile);

		PLEX_printFontStringTintedInt(order, wPerc, hPerc, x + (w - bw)/2, y + hi, fw, fh, br, bg, bb, message, alphaString, font, offset, errorline, errorfile);

		return PLEX_leftClick();
	}else{
		PLEX_drawRectInt(order, x, y, w, h, fr, fg, fb, fa, thickness, offset, errorline, errorfile);

		PLEX_printFontStringTintedInt(order, wPerc, hPerc, x + (w - bw)/2, y + hi, fw, fh, fr, fg, fb, message, alphaString, font, offset, errorline, errorfile);
	}

	if(p_showClickables) PLEX_fillRectInt(0, x, y, w, h, fr, fg, fb, fa * 0.5, offset, errorline, errorfile);

	return false;
}

bool PLEX_drawArrowButtonInt(const size_t order, const int64_t x, const int64_t y, const int64_t w, const int64_t h, const uint8_t fr, const uint8_t fg, const uint8_t fb, const uint8_t fa, const uint8_t br, const uint8_t bg, const uint8_t bb, const uint8_t ba, const uint8_t thickness, const bool flip, const bool offset, const size_t errorline, const char* const errorfile)
{
	bool inside = false;

	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_GRAPHICS_ONARROWDRAWING, errorline, errorfile);
		return false;
	}

	inside = PLEX_mouseInside(x, y, w, h, offset);

	if(inside)
	{
		PLEX_fillRectInt(order, x, y, w, h, fr, fg, fb, fa, offset, errorline, errorfile);

		if(!flip)
		{
			PLEX_fillRectInt(order, x + w * 0.2, y + h * 0.2,  w * 0.2, h - h * 0.4, br, bg, bb, ba, offset, errorline, errorfile);
			PLEX_fillRectInt(order, x + w * 0.3, y + h * 0.25, w * 0.2, h - h * 0.5, br, bg, bb, ba, offset, errorline, errorfile);
			PLEX_fillRectInt(order, x + w * 0.4, y + h * 0.3,  w * 0.2, h - h * 0.6, br, bg, bb, ba, offset, errorline, errorfile);
			PLEX_fillRectInt(order, x + w * 0.5, y + h * 0.35, w * 0.2, h - h * 0.7, br, bg, bb, ba, offset, errorline, errorfile);
			PLEX_fillRectInt(order, x + w * 0.6, y + h * 0.4,  w * 0.2, h - h * 0.8, br, bg, bb, ba, offset, errorline, errorfile);
		}else{
			PLEX_fillRectInt(order, x + w * 0.2, y + h * 0.4,  w * 0.2, h - h * 0.8, br, bg, bb, ba, offset, errorline, errorfile);
			PLEX_fillRectInt(order, x + w * 0.3, y + h * 0.35, w * 0.2, h - h * 0.7, br, bg, bb, ba, offset, errorline, errorfile);
			PLEX_fillRectInt(order, x + w * 0.4, y + h * 0.3,  w * 0.2, h - h * 0.6, br, bg, bb, ba, offset, errorline, errorfile);
			PLEX_fillRectInt(order, x + w * 0.5, y + h * 0.25, w * 0.2, h - h * 0.5, br, bg, bb, ba, offset, errorline, errorfile);
			PLEX_fillRectInt(order, x + w * 0.6, y + h * 0.2,  w * 0.2, h - h * 0.4, br, bg, bb, ba, offset, errorline, errorfile);
		}

		PLEX_drawRectInt(order, x, y, w, h, br, bg, bb, ba, thickness, offset, errorline, errorfile);
		return PLEX_leftClick();
	}else{
		PLEX_fillRectInt(order, x, y, w, h, br, bg, bb, ba, offset, errorline, errorfile);

		if(!flip)
		{
			PLEX_fillRectInt(order, x + w * 0.2, y + h * 0.2,  w * 0.2, h - h * 0.4, fr, fg, fb, fa, offset, errorline, errorfile);
			PLEX_fillRectInt(order, x + w * 0.3, y + h * 0.25, w * 0.2, h - h * 0.5, fr, fg, fb, fa, offset, errorline, errorfile);
			PLEX_fillRectInt(order, x + w * 0.4, y + h * 0.3,  w * 0.2, h - h * 0.6, fr, fg, fb, fa, offset, errorline, errorfile);
			PLEX_fillRectInt(order, x + w * 0.5, y + h * 0.35, w * 0.2, h - h * 0.7, fr, fg, fb, fa, offset, errorline, errorfile);
			PLEX_fillRectInt(order, x + w * 0.6, y + h * 0.4,  w * 0.2, h - h * 0.8, fr, fg, fb, fa, offset, errorline, errorfile);
		}else{
			PLEX_fillRectInt(order, x + w * 0.2, y + h * 0.4,  w * 0.2, h - h * 0.8, fr, fg, fb, fa, offset, errorline, errorfile);
			PLEX_fillRectInt(order, x + w * 0.3, y + h * 0.35, w * 0.2, h - h * 0.7, fr, fg, fb, fa, offset, errorline, errorfile);
			PLEX_fillRectInt(order, x + w * 0.4, y + h * 0.3,  w * 0.2, h - h * 0.6, fr, fg, fb, fa, offset, errorline, errorfile);
			PLEX_fillRectInt(order, x + w * 0.5, y + h * 0.25, w * 0.2, h - h * 0.5, fr, fg, fb, fa, offset, errorline, errorfile);
			PLEX_fillRectInt(order, x + w * 0.6, y + h * 0.2,  w * 0.2, h - h * 0.4, fr, fg, fb, fa, offset, errorline, errorfile);
		}

		PLEX_drawRectInt(order, x, y, w, h, fr, fg, fb, fa, thickness, offset, errorline, errorfile);
	}

	if(p_showClickables) PLEX_fillRectInt(0, x, y, w, h, fr, fg, fb, fa * 0.5, offset, errorline, errorfile);

	return false;
}

bool PLEX_drawIconButtonInt(const size_t order, const bool selected, const int64_t x, const int64_t y, const int64_t w, const int64_t h, const int64_t tx, const int64_t ty, const int64_t tw, const int64_t th, const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a, const uint8_t sr, const uint8_t sg, const uint8_t sb, const uint8_t sa, const uint8_t ovr, const int64_t ovb, const int64_t ovg, const int64_t ova, const uint8_t sovr, const int64_t sovb, const int64_t sovg, const int64_t sova, const uint8_t thickness, const size_t texture, const bool offset, const size_t errorline, const char* const errorfile)
{
	bool inside = false;

	uint8_t dr = 0;
	uint8_t dg = 0;
	uint8_t db = 0;
	uint8_t da = 0;

	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_GRAPHICS_ONDRAWINGICONBUTTON, errorline, errorfile);
		return false;
	}

	inside = PLEX_mouseInside(x, y, w, h, offset);

	if(texture)
	{
		if(inside) PLEX_printTextureTintedInt(order, texture, tx, ty, tw, th, x, y, w, h, r, g, b, offset, errorline, errorfile);
		else PLEX_printTextureInt(order, texture, tx, ty, tw, th, x, y, w, h, offset, errorline, errorfile);
	}

	if(selected)
	{
		if(inside){ dr = sovr; dg = sovg; db = sovb; da = sova; }
		else { dr = sr; dg = sg; db = sb; da = sa; };
	}else{
		if(inside){ dr = ovr; dg = ovg; db = ovb; da = ova; }
		else{ dr = r; dg = g; db = b; da = a; };
	}

	PLEX_drawRectInt(order, x, y, w, h, dr, dg, db, da, thickness, offset, errorline, errorfile);

	if(p_showClickables) PLEX_fillRectInt(0, x, y, w, h, dr, dg, db, da * 0.5, offset, errorline, errorfile);

	return PLEX_leftClick() && inside;
}

bool PLEX_twoImageButtonInt(const size_t order, const bool selected, const int64_t x, const int64_t y, const int64_t w, const int64_t h, const int64_t tx, const int64_t ty, const int64_t tw, const int64_t th, const int64_t tx2, const int64_t ty2, const int64_t tw2, const int64_t th2, const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a, const uint8_t sr, const uint8_t sg, const uint8_t sb, const uint8_t sa, const uint8_t thickness, const size_t texture1, const size_t texture2, const bool offset, const size_t errorline, const char* const errorfile)
{
	bool inside = false;

	uint8_t dr = 0;
	uint8_t dg = 0;
	uint8_t db = 0;
	uint8_t da = 0;

	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_GRAPHICS_ONTWOIMAGEBUTTONDDRAWING, errorline, errorfile);
		return false;
	}

	inside = PLEX_mouseInside(x, y, w, h, offset);

	if(!texture1)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ISNULLTEXTURE, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_GRAPHICS_ONTWOIMAGEBUTTONDDRAWING, PLEX_ERRORMESS_TEXTURE_TEXTURE, errorline, errorfile);
		return false;
	}

	if(!texture2)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ISNULLTEXTURE, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_GRAPHICS_ONTWOIMAGEBUTTONDDRAWING, PLEX_ERRORMESS_TEXTURE_TEXTURE2, errorline, errorfile);
		return false;
	}

	if(inside) PLEX_printTextureInt(order, texture2, tx2, ty2, tw2, th2, x, y, w, h, offset, errorline, errorfile);
	else PLEX_printTextureInt(order, texture1, tx, ty, tw, th, x, y, w, h, offset, errorline, errorfile);

	if(selected)
	{
		dr = sr;
		dg = sg;
		db = sb;
		da = sa;
	}else{
		dr = r;
		dg = g;
		db = b;
		da = a;
	}

	PLEX_drawRectInt(order, x, y, w, h, dr, dg, db, da, thickness, offset, errorline, errorfile);

	if(p_showClickables) PLEX_fillRectInt(0, x, y, w, h, dr, dg, db, da * 0.5, offset, errorline, errorfile);

	return PLEX_leftClick() && inside;
}

void PLEX_drawTextBoxInt(const size_t order, const char* const message, const double wPerc, const double hPerc, const uint8_t fr, const uint8_t fg, const uint8_t fb, const uint8_t fa, const int64_t hx, const int64_t hy, const int64_t hw, const int64_t hh, const uint32_t fw, const uint32_t fh, const double ipx, const double ipy, const double ipw, const double iph, const uint8_t thickness, const char* const alphaString, const size_t fontTexture, const size_t texture, const int64_t tx, const int64_t ty, const int64_t tw, const int64_t th, const double lineSpacePerc, const bool offset, const size_t errorline, const char* const errorfile)
{
	uint8_t tint = 0;

	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_GRAPHICS_ONTEXTBOXDRAWING, errorline, errorfile);
		return;
	}

	if(message == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GRAPHICS_ONTEXTBOXDRAWING, PLEX_ERRORMESS_GENERIC_MESSAGE, errorline, errorfile);
		return;
	}

	if(message[0] == '\0')
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_NOSTRINGLEN, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GRAPHICS_ONTEXTBOXDRAWING, PLEX_ERRORMESS_GENERIC_MESSAGE, errorline, errorfile);
		return;
	}

	if(alphaString == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GRAPHICS_ONTEXTBOXDRAWING, PLEX_ERRORMESS_GENERIC_MESSAGE, errorline, errorfile);
		return;
	}

	if(alphaString[0] == '\0')
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_NOSTRINGLEN, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GRAPHICS_ONTEXTBOXDRAWING, PLEX_ERRORMESS_GENERIC_ALPHASTRING, errorline, errorfile);
		return;
	}

	tint = p_getReverseTintAmount(fr, fg, fb)/2.0;

	PLEX_drawTextBoxTintedInt(order, message, wPerc, hPerc, fr, fg, fb, fa, tint, tint, tint, 255, hx, hy, hw, hh, fw, fh, ipx, ipy, ipw, iph, thickness, alphaString, fontTexture, texture, tx, ty, tw, th, lineSpacePerc, offset, errorline, errorfile);
}

void PLEX_drawTextBoxTintedInt(const size_t order, const char* const message, const double wPerc, const double hPerc, const uint8_t fr, const uint8_t fg, const uint8_t fb, const uint8_t fa, const uint8_t br, const uint8_t bg, const uint8_t bb, const uint8_t ba, const int64_t x, const int64_t y, const int64_t w, const int64_t h, const uint32_t fw, const uint32_t fh, const double ipx, const double ipy, const double ipw, const double iph, const uint8_t thickness, const char* const alphaString, const size_t fontTexture, const size_t texture, const int64_t tx, const int64_t ty, const int64_t tw, const int64_t th, const double lineSpacePerc, const bool offset, const size_t errorline, const char* const errorfile)
{
	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_GRAPHICS_ONTEXTBOXTINTEDDRAWING, errorline, errorfile);
		return;
	}

	if(message == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GRAPHICS_ONTEXTBOXTINTEDDRAWING, PLEX_ERRORMESS_GENERIC_MESSAGE, errorline, errorfile);
		return;
	}

	if(message[0] == '\0')
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_NOSTRINGLEN, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GRAPHICS_ONTEXTBOXTINTEDDRAWING, PLEX_ERRORMESS_GENERIC_MESSAGE, errorline, errorfile);
		return;
	}

	if(alphaString == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GRAPHICS_ONTEXTBOXTINTEDDRAWING, PLEX_ERRORMESS_GENERIC_ALPHASTRING, errorline, errorfile);
		return;
	}

	if(alphaString[0] == '\0')
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_NOSTRINGLEN, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GRAPHICS_ONTEXTBOXTINTEDDRAWING, PLEX_ERRORMESS_GENERIC_ALPHASTRING, errorline, errorfile);
		return;
	}

	p_drawTextBoxTintedBase(order, message, wPerc, hPerc, fr, fg, fb, fa, br, bg, bb, ba, x, y, w, h, fw, fh, ipx, ipy, ipw, iph, thickness, alphaString, fontTexture, texture, tx, ty, tw, th, lineSpacePerc, false, 0, offset, errorline, errorfile);
}

size_t PLEX_drawTextBoxScrollingInt(const size_t order, const char* const message, const double wPerc, const double hPerc, const uint8_t fr, const uint8_t fg, const uint8_t fb, const uint8_t fa, const int64_t x, const int64_t y, const int64_t w, const int64_t h, const uint32_t fw, const uint32_t fh, const double ipx, const double ipy, const double ipw, const double iph, const uint8_t thickness, const char* const alphaString, const size_t fontTexture, const size_t texture, const int64_t tx, const int64_t ty, const int64_t tw, const int64_t th, const double lineSpacePerc, const size_t pageScroll, const bool offset, const size_t errorline, const char* const errorfile)
{
	uint8_t tint = 0;

	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_GRAPHICS_ONSCROLLINGTEXTBOXDRAWING, errorline, errorfile);
		return 0;
	}

	if(message == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GRAPHICS_ONSCROLLINGTEXTBOXDRAWING, PLEX_ERRORMESS_GENERIC_MESSAGE, errorline, errorfile);
		return pageScroll;
	}

	if(message[0] == '\0')
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_NOSTRINGLEN, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GRAPHICS_ONSCROLLINGTEXTBOXDRAWING, PLEX_ERRORMESS_GENERIC_MESSAGE, errorline, errorfile);
		return pageScroll;
	}

	if(alphaString == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GRAPHICS_ONSCROLLINGTEXTBOXDRAWING, PLEX_ERRORMESS_GENERIC_ALPHASTRING, errorline, errorfile);
		return pageScroll;
	}

	if(alphaString[0] == '\0')
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_NOSTRINGLEN, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GRAPHICS_ONSCROLLINGTEXTBOXDRAWING, PLEX_ERRORMESS_GENERIC_ALPHASTRING, errorline, errorfile);
		return pageScroll;
	}

	tint = p_getReverseTintAmount(fr, fg, fb)/2.0;

	return PLEX_drawTextBoxScrollingTintedInt(order, message, wPerc, hPerc, fr, fg, fb, fa, tint, tint, tint, 255, x, y, w, h, fw, fh, ipx, ipy, ipw, iph, thickness, alphaString, fontTexture, texture, tx, ty, tw, th, lineSpacePerc, pageScroll, offset, errorline, errorfile);
}

size_t PLEX_drawTextBoxScrollingTintedInt(const size_t order, const char* const message, const double wPerc, const double hPerc, const uint8_t fr, const uint8_t fg, const uint8_t fb, const uint8_t fa, const uint8_t br, const uint8_t bg, const uint8_t bb, const uint8_t ba, const int64_t x, const int64_t y, const int64_t w, const int64_t h, const uint32_t fw, const uint32_t fh, const double ipx, const double ipy, const double ipw, const double iph, const uint8_t thickness, const char* const alphaString, const size_t fontTexture, const size_t texture, const int64_t tx, const int64_t ty, const int64_t tw, const int64_t th, const double lineSpacePerc, const size_t pageScroll, const bool offset, const size_t errorline, const char* const errorfile)
{
	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_GRAPHICS_ONSCROLLINGTEXTBOXTINTEDDRAWING, errorline, errorfile);
		return 0;
	}

	if(message == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GRAPHICS_ONSCROLLINGTEXTBOXTINTEDDRAWING, PLEX_ERRORMESS_GENERIC_MESSAGE, errorline, errorfile);
		return pageScroll;
	}

	if(message[0] == '\0')
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_NOSTRINGLEN, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GRAPHICS_ONSCROLLINGTEXTBOXTINTEDDRAWING, PLEX_ERRORMESS_GENERIC_MESSAGE, errorline, errorfile);
		return pageScroll;
	}

	if(alphaString == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GRAPHICS_ONSCROLLINGTEXTBOXTINTEDDRAWING, PLEX_ERRORMESS_GENERIC_ALPHASTRING, errorline, errorfile);
		return pageScroll;
	}

	if(alphaString[0] == '\0')
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_NOSTRINGLEN, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GRAPHICS_ONSCROLLINGTEXTBOXTINTEDDRAWING, PLEX_ERRORMESS_GENERIC_ALPHASTRING, errorline, errorfile);
		return pageScroll;
	}

	return p_drawTextBoxTintedBase(order, message, wPerc, hPerc, fr, fg, fb, fa, br, bg, bb, ba, x, y, w, h, fw, fh, ipx, ipy, ipw, iph, thickness, alphaString, fontTexture, texture, tx, ty, tw, th, lineSpacePerc, true, pageScroll, offset, errorline, errorfile);
}

void PLEX_drawTooltipInt(const size_t order, const char* const message, const double wPerc, const double hPerc, const uint8_t br, const uint8_t bg, const uint8_t bb, const uint8_t ba, const int64_t mx, const int64_t my, const int64_t mw, const int64_t mh, const int64_t dx, const int64_t dy, const int64_t lw, const int64_t lh, const double ipx, const double ipy, const double ipw, const double iph, const uint8_t thickness, const char* const alphaString, const size_t fontTexture, const size_t texture, const int64_t tx, const int64_t ty, const int64_t tw, const int64_t th, const bool offset, const size_t errorline, const char* const errorfile)
{
	bool inside = false;

	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_GRAPHICS_ONTOOLTIPDRAWING, errorline, errorfile);
		return;
	}

	if(message == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GRAPHICS_ONTOOLTIPDRAWING, PLEX_ERRORMESS_GENERIC_MESSAGE, errorline, errorfile);
		return;
	}

	if(message[0] == '\0')
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_NOSTRINGLEN, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GRAPHICS_ONTOOLTIPDRAWING, PLEX_ERRORMESS_GENERIC_MESSAGE, errorline, errorfile);
		return;
	}

	if(alphaString == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GRAPHICS_ONTOOLTIPDRAWING, PLEX_ERRORMESS_GENERIC_ALPHASTRING, errorline, errorfile);
		return;
	}

	if(alphaString[0] == '\0')
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_NOSTRINGLEN, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GRAPHICS_ONTOOLTIPDRAWING, PLEX_ERRORMESS_GENERIC_ALPHASTRING, errorline, errorfile);
		return;
	}

	inside = PLEX_mouseInside(mx, my, mw, mh, offset) || p_showTooltips || p_toggleTooltips;

	if(inside)
	{
		int64_t lx = PLEX_MX() - (PLEX_WOFFSET() * offset) + dx;
		int64_t ly = PLEX_MY() - (PLEX_HOFFSET() * offset) - dy;

		PLEX_drawLabelInt(order, message, wPerc, hPerc, br, bg, bb, ba, lx, ly, lw, lh, ipx, ipy, ipw, iph, thickness, alphaString, fontTexture, texture, tx, ty, tw, th, offset, errorline, errorfile);
	}
}

void PLEX_drawChargeBarInt(const size_t order, const double fullness, const int64_t x, const int64_t y, const int64_t w, const int64_t h, const uint8_t fr, const uint8_t fg, const uint8_t fb, const uint8_t fa, const uint8_t br, const uint8_t bg, const uint8_t bb, const uint8_t ba, const uint8_t thickness, const bool vertical, const bool offset, const size_t errorline, const char* const errorfile)
{
	double trueFullness = 0;

	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_GRAPHICS_ONCHARGEBARDRAWING, errorline, errorfile);
		return;
	}

	trueFullness = fullness < 1 ? fullness : 1;

	if(fullness > 0)
	{
		if(vertical)
		{
			const double revFullness = 1 - trueFullness;

			PLEX_fillRectInt(order, x, y + h * revFullness, w, h - (h * revFullness), br, bg, bb, ba, offset, errorline, errorfile);
			PLEX_drawRectInt(order, x, y + h * revFullness, w, h - (h * revFullness), fr, fg, fb, fa, thickness, offset, errorline, errorfile);
		}else{
			PLEX_fillRectInt(order, x, y, w * trueFullness, h, br, bg, bb, ba, offset, errorline, errorfile);
			PLEX_drawRectInt(order, x, y, w * trueFullness, h, fr, fg, fb, fa, thickness, offset, errorline, errorfile);
		}
	}

	PLEX_drawRectInt(order, x, y, w, h, fr, fg, fb, fa, thickness, offset, errorline, errorfile);
}

void PLEX_drawPanoramaInt(const size_t order, const size_t texture, const size_t errorline, const char* const errorfile)
{
	const double panjust = 1.3333;

	uint32_t aw = 0, ow = 0;

	uint32_t tw = 0, th = 0, atw = 0, otw = 0;

	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_GRAPHICS_ONPANORAMADRAWING, errorline, errorfile);
		return;
	}

	if(!texture)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ISNULLTEXTURE, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GRAPHICS_ONPANORAMADRAWING, PLEX_ERRORMESS_TEXTURE_TEXTURE, errorline, errorfile);
		return;
	}

	PLEX_textureWHInt(texture, &tw, &th, errorline, errorfile);

	atw = th * panjust;
	aw = PLEX_WH(true) * panjust;

	if(atw > tw)
	{
		atw = tw;
		aw = PLEX_WW(true);
	}

	ow = (PLEX_WW(true) - aw)/2 + PLEX_WOFFSET();
	otw = (tw - atw)/2 + PLEX_WOFFSETPERC();

	if(ow > PLEX_WW(true))
	{
		ow = PLEX_WW(true);
		otw = tw;
	}

	PLEX_printTextureInt(order, texture, tw/2 - atw/2, 0, atw, th, PLEX_WW(true)/2  - aw/2, 0, aw, PLEX_WH(true), true, errorline, errorfile);

	PLEX_printTextureInt(order, texture, 0, 0, otw, th, 0, 0, ow + 1, PLEX_WH(true), false, errorline, errorfile);

	PLEX_printTextureInt(order, texture, tw - otw, 0, otw, th, PLEX_WW(false) - (ow + 1), 0, ow + 1, PLEX_WH(true), false, errorline, errorfile);
}

size_t PLEX_takeScreencapInt(const bool offset, const size_t errorline, const char* const errorfile)
{
	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_GRAPHICS_ONTAKINGSCREENCAP, errorline, errorfile);
		return 0;
	}

	return PLEX_copyTextureInt(p_screenPlate, offset * PLEX_WOFFSET(), offset * PLEX_HOFFSET(), PLEX_WW(offset), PLEX_WH(offset), errorline, errorfile);
}

void PLEX_reloadGraphicsDefaults()
{

}

// start, update, end functions ---------------------------------------------------------------------------------------------

bool PLEX_startGraphicsInt(const size_t errorline, const char* const errorfile)
{
	if(p_running)
	{
		PLEX_errorInt0A(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_DOUBLESTART, PLEX_ERROR_SEVERITY_BADSTYLE, errorline, errorfile);
		return true;
	}

	p_drawList = PLEX_genExpandArrayInt(PLEX_getMemProfileDrawlistPreload(), sizeof(PLEX_GRAPHICS_INSTRUCT), errorline, errorfile);

	PLEX_low_setBlendTarget(SDL_BLENDMODE_BLEND);

	p_screenPlate = PLEX_createGeneratedTextureInt(PLEX_WW(false), PLEX_WH(false), 0, 0, 0, 255, errorline, errorfile);

	PLEX_low_setRenderTarget(PLEX_innerTextureInt(p_screenPlate, errorline, errorfile));

	PLEX_low_setBlendTarget(SDL_BLENDMODE_BLEND);

	p_running = true;

	return true;
}

bool PLEX_updateGraphicsInt(SDL_Window* window, const uint32_t w, const uint32_t h, const size_t errorline, const char* const errorfile)
{
	PLEX_LOW_TEXTURE innerPlate = PLEX_LOW_NOTEXTURE;

	uint32_t pw = 0;
	uint32_t ph = 0;

	if(!p_running)
	{
		PLEX_errorInt0A(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_UPDATEBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, errorline, errorfile);
		return false;
	}

	if(window == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GRAPHICS_ONGRAPHICSUPDATE, PLEX_ERRORMESS_WINDOW_WINDOW, errorline, errorfile);
		return false;
	}

	innerPlate = PLEX_innerTextureInt(p_screenPlate, errorline, errorfile);

	if(!PLEX_isSizing())
	{
		uint32_t cw = 0;
		uint32_t ch = 0;

		uint32_t fx = 0;
		uint32_t fy = 0;
		uint32_t fw = 0;
		uint32_t fh = 0;

		innerPlate = PLEX_innerTextureInt(p_screenPlate, errorline, errorfile);

		PLEX_low_setRenderTarget(innerPlate);

		PLEX_low_fillRect(p_refreshR, p_refreshG, p_refreshB, 255, NULL, SDL_BLENDMODE_NONE);
		PLEX_low_setBlendTarget(SDL_BLENDMODE_BLEND);

		p_drawDrawList(errorline, errorfile);

		PLEX_low_setRenderTarget(PLEX_LOW_NOTEXTURE);

		PLEX_low_textureWH(innerPlate, &pw, &ph);

		if(pw != PLEX_WW(false) || ph != PLEX_WH(false))
		{
			p_screenPlate = PLEX_createGeneratedTextureInt(PLEX_WW(false), PLEX_WH(false), 0, 0, 0, 255, errorline, errorfile);
			innerPlate = PLEX_innerTextureInt(p_screenPlate, errorline, errorfile);
		}

		PLEX_low_updateRendererInt(window, w, h, errorline, errorfile);
		PLEX_low_copyTexture(innerPlate, NULL, NULL, SDL_BLENDMODE_BLEND);

		if(!PLEX_DEF_disableMouse())
		{
			PLEX_cursorDimensInt(&cw, &ch, &fx, &fy, &fw, &fh, errorline, errorfile);

			if(PLEX_usingCustomCursor())
			{
				const size_t tex = PLEX_customCursor();

				PLEX_printTextureTintedInt(0, tex, fx, fy, fw, fh, PLEX_MX(), PLEX_MY(), cw, ch, PLEX_customCursorR(), PLEX_customCursorG(), PLEX_customCursorB(), false, errorline, errorfile);
			}else{
				if(!PLEX_cursorIsHidden())
				{
					size_t regularCursor = 0;

					if(PLEX_leftClick()) regularCursor = PLEX_regularCursorClick();
					else if(PLEX_left()) regularCursor = PLEX_regularCursorDown();
					else regularCursor = PLEX_regularCursor();

					PLEX_printTextureTintedInt(0, regularCursor, fx, fy, fw, fh, PLEX_MX(), PLEX_MY(), cw, ch, PLEX_cursorR(), PLEX_cursorG(), PLEX_cursorB(), false, errorline, errorfile);
				}
			}
		}

		PLEX_low_setRenderTarget(innerPlate);
	}else{
		PLEX_destroyTextureInt(p_screenPlate, errorline, errorfile);
		p_screenPlate = PLEX_createGeneratedTextureInt(PLEX_WW(false), PLEX_WH(false), 0, 0, 0, 255, errorline, errorfile);
		return true;
	}

	p_showClickables = false;
	p_showTooltips = false;

	return true;
}

void PLEX_endGraphicsInt(const size_t errorline, const char* const errorfile)
{
	if(!p_running)
	{
		PLEX_errorInt0A(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ENDBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, errorline, errorfile);
		return;
	}

	if(p_drawList == NULL) PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_FREENULL, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_GRAPHICS_ONGRAPHICSEND, PLEX_ERRORMESS_GRAPHICS_DRAWLIST, errorline, errorfile);

	PLEX_destroyExpandArrayInt(&p_drawList, errorline, errorfile);

	p_running = false;
}

// setters ------------------------------------------------------------------------------------------------------------------

void PLEX_setTextureTargetInt(const size_t texture, const size_t errorline, const char* const errorfile)
{
	PLEX_LOW_TEXTURE target;

	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_GRAPHICS_ONSETTEXTURETARGET, errorline, errorfile);
		return;
	}

	target = PLEX_innerTextureInt(texture, errorline, errorfile);

	PLEX_low_setRenderTarget(target);
}

void PLEX_setRefreshColorInt(const uint8_t r, const uint8_t g, const uint8_t b, const size_t errorline, const char* const errorfile)
{
	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_GRAPHICS_ONSETREFRESHRGB, errorline, errorfile);
		return;
	}

	p_refreshR = r;
	p_refreshG = g;
	p_refreshB = b;
}

void PLEX_drawBlendModeInt(const SDL_BlendMode mode, const size_t errorline, const char* const errorfile)
{
	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_GRAPHICS_ONSETBLENDRGB, errorline, errorfile);
		return;
	}

	PLEX_low_setBlendTarget(mode);
}

// getters ------------------------------------------------------------------------------------------------------------------

void PLEX_unsetTextureTargetInt(const size_t errorline, const char* const errorfile)
{
	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_GRAPHICS_ONUNSETTEXTURETARGET, errorline, errorfile);
		return;
	}

	PLEX_setTextureTargetInt(p_screenPlate, errorline, errorfile);
}

void PLEX_showAllTooltips(){ p_showTooltips = true; }
void PLEX_toggleTooltips(){ p_toggleTooltips = !p_toggleTooltips; }
void PLEX_showAllClickables(){ p_showClickables = true; }
