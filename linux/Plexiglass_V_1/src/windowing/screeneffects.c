#include "windowing/screeneffects.h"

// NOTE: global function descriptions in header.

// structs ------------------------------------------------------------------------------------------------------------------

typedef struct
{
	PLEX_SCREENEFFECT_TYPE type;
	PLEX_RECT range, propRange;
	size_t drawLayer, aniIndex;
	bool loop, active, screenOffset, ranged, initial, over, hidden;
	uint64_t start, duration;
	uint8_t r, g, b, a;
	double minPerc;
	PLEX_RECT particles[100];

	PLEX_SPRITE* sprite;
} P_SCREENEFFECT;

// static values ------------------------------------------------------------------------------------------------------------

static bool p_running = false;

static PLEX_EXPANDARRAY* p_effects = NULL;

static bool p_disableScreenEffects = false;

static int64_t p_nextIndex = -1;

// static functions ---------------------------------------------------------------------------------------------------------

// the static function to run a screen fade effect

static void p_tintFadeEffect(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a, const double perc, const double minPerc, const PLEX_RECT range, const bool screenOffset, const size_t drawLayer, const size_t errorline, const char* const errorfile)
{
	const double alpha = a * minPerc + a * perc * (1 - minPerc);

	const uint32_t x = range.origin.x;
	const uint32_t y = range.origin.y;
	const uint32_t w = range.dimens.w;
	const uint32_t h = range.dimens.h;

	PLEX_fillRectInt(drawLayer, x, y, w, h, r, g, b, alpha, screenOffset, errorline, errorfile);
}

// the static function to utilize a splatter (usually blood) effect

static void p_splatterEffect(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a, const double perc, const double minPerc, const PLEX_RECT range, const bool screenOffset, const bool initial, PLEX_RECT* particles, const size_t drawLayer, const size_t errorline, const char* const errorfile)
{
	const double mx = range.dimens.w/2;
	const double my = range.dimens.h/2;

	for(size_t ze = 0; ze < 16; ++ze)
	{
		const size_t direc = ze % 8;

		double vx = 0;
		double vy = 0;

		double dx = 0;
		double dy = 0;
		double dw = 0;
		double dh = 0;

		PLEX_RECT* splatterRect = particles + ze;

		if(initial)
		{
			splatterRect->origin.x = mx;
			splatterRect->origin.y = my;
			splatterRect->dimens.w = range.dimens.w * PLEX_randomNumberInt(0.05, 0.1, errorline, errorfile);
			splatterRect->dimens.h = range.dimens.h * PLEX_randomNumberInt(0.05, 0.1, errorline, errorfile);
		}

		splatterRect->dimens.w *= PLEX_randomNumberInt(1, 1.25, errorline, errorfile);
		splatterRect->dimens.h *= PLEX_randomNumberInt(1, 1.25, errorline, errorfile);

		vx = splatterRect->dimens.w * PLEX_randomNumberInt(0.1, 0.5, errorline, errorfile);
		vy = splatterRect->dimens.h * PLEX_randomNumberInt(0.1, 0.2, errorline, errorfile);

		if(!PLEX_getGameTimePaused())
		{
			switch(direc)
			{
				case 0:
					splatterRect->origin.x -= vx/2;
					splatterRect->origin.y -= vy/2;
				break;

				case 1:
					splatterRect->origin.y -= vx;
				break;

				case 2:
					splatterRect->origin.x += vx/2;
					splatterRect->origin.y -= vy/2;
				break;

				case 3:
					splatterRect->origin.x += vx;
				break;

				case 4:
					splatterRect->origin.x += vx/2;
					splatterRect->origin.y += vy/2;
				break;

				case 5:
					splatterRect->origin.y -= vy;
				break;

				case 6:
					splatterRect->origin.x -= vx/2;
					splatterRect->origin.y += vy/2;
				break;

				case 7:
					splatterRect->origin.x -= vx;
				break;
			};
		}

		dx = range.origin.x + splatterRect->origin.x;
		dy = range.origin.y + splatterRect->origin.y;
		dw = splatterRect->dimens.w;
		dh = splatterRect->dimens.h;

		if(dx < range.origin.x) dx = range.origin.x;
		if(dy < range.origin.y) dy = range.origin.y;

		if(dx + dw > range.origin.x + range.dimens.w) dx = (range.origin.x + range.dimens.w) - dw;
		if(dy + dh > range.origin.y + range.dimens.h) dy = (range.origin.y + range.dimens.h) - dh;

		PLEX_fillRectInt(drawLayer, dx, dy, dw, dh, r, g, b, a, screenOffset, errorline, errorfile);
	}
}

// the static function to run a screen tint effect

static void p_tintEffect(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a, const PLEX_RECT range, const bool screenOffset, const size_t drawLayer, const size_t errorline, const char* const errorfile)
{
	const uint32_t x = range.origin.x;
	const uint32_t y = range.origin.y;
	const uint32_t w = range.dimens.w;
	const uint32_t h = range.dimens.h;

	PLEX_fillRectInt(drawLayer, x, y, w, h, r, g, b, a, screenOffset, errorline, errorfile);
}

// the static function to run the rain effect

static void p_rainEffect(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a, const double perc, const double minPerc, const PLEX_RECT range, const bool screenOffset, const bool initial, PLEX_RECT* particles, const size_t drawLayer, const size_t errorline, const char* const errorfile)
{
	static const double minSpurts = 3;
	static const double addedSpurts = 20;

	const double heaviness = minSpurts + (minPerc * addedSpurts);

	const double min = minPerc * heaviness;
	const double max = (minPerc + perc) * heaviness;

	const double spurts = PLEX_randomNumberInt(min, max, errorline, errorfile);

	const double xUnit = range.dimens.w/spurts;

	double xUnitMin = 0;
	double xUnitMax = xUnit;

	double x = 0;

	if(initial && !PLEX_getGameTimePaused()) return;

	if(!PLEX_getGameTimePaused()) x = PLEX_randomNumberInt(xUnitMin, xUnitMax, errorline, errorfile);

	for(size_t ze = 0; ze < spurts; ++ze)
	{
		double y = 0;

		double lenPerc = 0;

		double minLength = 0;
		double maxLength = 0;

		double length = 0;

		if(!PLEX_getGameTimePaused())
		{
			y = PLEX_randomNumberInt(0, range.dimens.h, errorline, errorfile);

			lenPerc = y/(double)range.dimens.h;

			minLength = PLEX_UNIT(1) + (lenPerc + PLEX_UNIT(2));
			maxLength = range.dimens.h/4;

			length = PLEX_randomNumberInt(minLength, maxLength, errorline, errorfile);

			particles[ze].origin.x = x;
			particles[ze].origin.y = y;
		}else{
			lenPerc = particles[ze].origin.y/(double)range.dimens.h;

			minLength = PLEX_UNIT(1) + (lenPerc + PLEX_UNIT(4));
			maxLength = range.dimens.h/4;

			length = minLength + (maxLength - minLength)/2.0;
		}

		PLEX_drawLine2Int(drawLayer, range.origin.x + particles[ze].origin.x, range.origin.y + particles[ze].origin.y, length, 270, r, g, b, a, PLEX_UNIT(0.05), screenOffset, errorline, errorfile);

		if(!PLEX_getGameTimePaused())
		{
			x += PLEX_randomNumberInt(xUnitMin, xUnitMax, errorline, errorfile);

			xUnitMin += xUnit;
			xUnitMax += xUnit;
		}
	}
}

// the static function to run the snow effect

static void p_snowEffect(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a, const double perc, const double minPerc, const PLEX_RECT range, const bool screenOffset, const bool initial, PLEX_RECT* particles, const size_t drawLayer, const size_t errorline, const char* const errorfile)
{
	double minAccelX = 0;
	double maxAccelX = 0;

	double minAccelY = 0;
	double maxAccelY = 0;

	minAccelX = 0 - PLEX_UNIT(0.2);
	minAccelX = PLEX_UNIT(0.2);

	minAccelY = PLEX_UNIT(0.2);
	maxAccelY = PLEX_UNIT(5);

	if(initial)
	{
		for(size_t ze = 0; ze < 100; ++ze)
		{
			const double x = PLEX_WW(false)/100 * ze;

			particles[ze].origin = PLEX_convPoint(x, 0);
		}
	}

	for(size_t ze = 0; ze < 100; ++ze)
	{
		const PLEX_POINT point = particles[ze].origin;
		const double d = PLEX_UNIT(0.08);

		const double accelX = PLEX_randomNumberInt(minAccelX, maxAccelX, errorline, errorfile);
		const double accelY = PLEX_randomNumberInt(minAccelY, maxAccelY, errorline, errorfile);

		PLEX_fillRectInt(drawLayer, range.origin.x + point.x, range.origin.y + point.y, d, d, r, g, b, a, screenOffset, errorline, errorfile);

		if(!PLEX_getGameTimePaused())
		{
			particles[ze].origin.x += accelX;
			particles[ze].origin.y += accelY;

			if(particles[ze].origin.x >= range.dimens.w) particles[ze].origin.x = range.dimens.w - particles[ze].origin.x;
			if(particles[ze].origin.x < 0) particles[ze].origin.x = range.dimens.w + particles[ze].origin.x;

			if(particles[ze].origin.y >= range.dimens.h)
			{
				particles[ze].origin.x = PLEX_WW(false)/100 * ze;
				particles[ze].origin.y = 0;
			}
		}
	}
}

// the static function to run the wind effect

static void p_windEffect(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a, const double perc, const double minPerc, const PLEX_RECT range, const bool screenOffset, const bool initial, PLEX_RECT* particles, const size_t drawLayer, const size_t errorline, const char* const errorfile)
{
	static const double minSpurts = 3;
	static const double addedSpurts = 22;

	const uint32_t heaviness = minSpurts + (minPerc * addedSpurts);

	const double yDiff = range.dimens.h/heaviness;

	const double minLen = range.dimens.w/20;
	const double maxLen = minLen * 3;

	const double minAccelX = PLEX_UNIT(0.01);
	const double maxAccelX = PLEX_UNIT(4);

	if(initial)
	{
		for(size_t ze = 0; ze < heaviness; ++ze) particles[ze].origin.x = PLEX_randomNumberInt(0, range.dimens.w/8, errorline, errorfile);
	}

	for(size_t ze = 0; ze < heaviness; ++ze)
	{
		const double xPerc = particles[ze].origin.x/range.dimens.w;

		const double len = minLen + (maxLen - minLen) * xPerc;

		if(!PLEX_getGameTimePaused())
		{
			const double accelX = PLEX_randomNumberInt(minAccelX, maxAccelX, errorline, errorfile);

			particles[ze].origin.x += accelX;
			particles[ze].origin.y = yDiff * ze;

			if(particles[ze].origin.x + len > range.dimens.w)
			{
				particles[ze].origin.x = PLEX_randomNumberInt(0, range.dimens.w/8, errorline, errorfile);
				continue;
			}
		}

		PLEX_drawLine2Int(drawLayer, range.origin.x + particles[ze].origin.x, range.origin.y + particles[ze].origin.y, len, 0, r, g, b, a, PLEX_UNIT(0.1), screenOffset, errorline, errorfile);
	}
}

// the static function to run the proj rain effect

static void p_projRainEffect(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a, const double perc, const double minPerc, const PLEX_RECT range, const bool screenOffset, const bool initial, PLEX_RECT* particles, const size_t drawLayer, PLEX_SPRITE* sprite, const size_t aniIndex, const uint64_t time, const size_t errorline, const char* const errorfile)
{
	static const double minSpurts = 3;
	static const double addedSpurts = 22;

	uint32_t heaviness = 0;

	double unit = 0;

	double yUnit = 0;

	size_t tex = 0;

	if(sprite == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SCREENEFFECTS, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SCREENEFFECT_ONPROJRAIN, PLEX_ERRORMESS_SPRITE_SPRITE, errorline, errorfile);
		return;
	}

	if(aniIndex >= PLEX_spriteAnimationCountInt(sprite, errorline, errorfile))
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SCREENEFFECTS, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SCREENEFFECT_ONPROJRAIN, PLEX_ERRORMESS_SPRITE_ANIINDEX, errorline, errorfile);
		return;
	}

	tex = PLEX_spriteTexInt(sprite, errorline, errorfile);

	if(!tex)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SCREENEFFECTS, PLEX_ERROR_ISNULLTEXTURE, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SCREENEFFECT_ONPROJRAIN, PLEX_ERRORMESS_TEXTURE_TEXTURE, errorline, errorfile);
		return;
	}

	heaviness = minSpurts + (minPerc * addedSpurts);

	unit = range.dimens.w/heaviness;

	yUnit = range.dimens.h/heaviness;

	if(initial)
	{
		for(size_t ze = 0; ze < heaviness; ++ze)
		{
			const double minX = ze * unit;
			const double maxX = ze + 1 * unit;

			particles[ze].origin.x = PLEX_randomNumberInt(minX, maxX, errorline, errorfile);
			particles[ze].origin.y = PLEX_randomNumberInt(0, (range.dimens.h - yUnit * ze), errorline, errorfile);
		}
	}

	for(size_t ze = 0; ze < heaviness; ++ze)
	{
		const double x = particles[ze].origin.x;
		const double y = particles[ze].origin.y;

		const double screenPerc = y/range.dimens.h;

		const double d = PLEX_UNIT(0.5) + PLEX_UNIT(3 * screenPerc);

		const double speed = PLEX_UNIT(0.1) + PLEX_randomNumberInt(PLEX_UNIT(0.35), PLEX_UNIT(0.5), errorline, errorfile) * screenPerc;

		PLEX_drawSpriteTintedInt(drawLayer, aniIndex, range.origin.x + x, range.origin.y + y, d, d, r, g, b, sprite, screenOffset, time, errorline, errorfile);

		if(!PLEX_getGameTimePaused())
		{
			particles[ze].origin.x += speed;
			particles[ze].origin.y += speed;

			if(particles[ze].origin.x > range.dimens.w)
			{
				const double minX = ze * unit;
				const double maxX = ze + 1 * unit;

				particles[ze].origin.x = PLEX_randomNumberInt(minX, maxX, errorline, errorfile);
				particles[ze].origin.y = PLEX_randomNumberInt(0, (range.dimens.h - yUnit * ze), errorline, errorfile);
			}
		}
	}
}

// the static function to run the paintover effect

static void p_paintoverEffect(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a, const double perc, const double minPerc, const PLEX_RECT range, const bool screenOffset, const bool initial, PLEX_RECT* particles, const size_t drawLayer, PLEX_SPRITE* sprite, const size_t aniIndex, const uint64_t time, const size_t errorline, const char* const errorfile)
{
	size_t tex = 0;

	if(sprite == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SCREENEFFECTS, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SCREENEFFECT_ONPAINTOVER, PLEX_ERRORMESS_SPRITE_SPRITE, errorline, errorfile);
		return;
	}

	if(aniIndex >= PLEX_spriteAnimationCountInt(sprite, errorline, errorfile))
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SCREENEFFECTS, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SCREENEFFECT_ONPAINTOVER, PLEX_ERRORMESS_SPRITE_ANIINDEX, errorline, errorfile);
		return;
	}

	tex = PLEX_spriteTexInt(sprite, errorline, errorfile);

	if(!tex)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SCREENEFFECTS, PLEX_ERROR_ISNULLTEXTURE, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SCREENEFFECT_ONPAINTOVER, PLEX_ERRORMESS_TEXTURE_TEXTURE, errorline, errorfile);
		return;
	}

	PLEX_setTextureAlphaInt(tex, a, errorline, errorfile);

	PLEX_drawSpriteTintedInt(drawLayer, aniIndex, range.origin.x, range.origin.y, range.dimens.w, range.dimens.h, r, g, b, sprite, screenOffset, time, errorline, errorfile);
}

// the static function to run the smoke effect

static void p_smokeEffect(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a, const double perc, const double minPerc, const PLEX_RECT range, const bool screenOffset, const bool initial, PLEX_RECT* particles, const size_t drawLayer, PLEX_SPRITE* sprite, const size_t aniIndex, const uint64_t time, const size_t errorline, const char* const errorfile)
{
	static const double minPlumes = 5;
	static const double maxPlumes = 100; // < cannot be over 100

	const double minD = range.dimens.w/10;
	const double maxD = range.dimens.w/5;

	const double startX = range.dimens.w/2;
	const double startY = range.dimens.h * 0.9;

	const double minUp = range.dimens.h/100;
	const double maxUp = range.dimens.h/20;

	const double minSide = 0 - range.dimens.w/10;
	const double maxSide = range.dimens.w/10;

	size_t tex = 0;

	uint32_t heaviness = 0;

	if(sprite == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SCREENEFFECTS, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SCREENEFFECT_ONSMOKE, PLEX_ERRORMESS_SPRITE_SPRITE, errorline, errorfile);
		return;
	}

	if(aniIndex >= PLEX_spriteAnimationCountInt(sprite, errorline, errorfile))
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SCREENEFFECTS, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SCREENEFFECT_ONSMOKE, PLEX_ERRORMESS_SPRITE_ANIINDEX, errorline, errorfile);
		return;
	}

	tex = PLEX_spriteTexInt(sprite, errorline, errorfile);

	if(!tex)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SCREENEFFECTS, PLEX_ERROR_ISNULLTEXTURE, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SCREENEFFECT_ONSMOKE, PLEX_ERRORMESS_TEXTURE_TEXTURE, errorline, errorfile);
		return;
	}

	heaviness = minPlumes + ((1 - perc) * minPerc * (maxPlumes - minPlumes));

	if(initial)
	{
		for(size_t ze = 0; ze < maxPlumes; ++ze)
		{
			particles[ze].origin.x = startX;
			particles[ze].origin.y = startY;
			particles[ze].dimens.w = minD;
			particles[ze].dimens.h = minD;
		}
	}

	for(size_t ze = 0; ze < heaviness; ++ze)
	{
		double distPerc = 1 - particles[ze].origin.y/range.dimens.h;

		double d = minD + (distPerc * (maxD - minD));

		particles[ze].origin.x -= PLEX_randomNumberInt(minSide, maxSide, errorline, errorfile);
		particles[ze].origin.y -= PLEX_randomNumberInt(minUp, maxUp, errorline, errorfile);

		particles[ze].dimens.w = d;
		particles[ze].dimens.h = d;

		if(particles[ze].origin.x < 0) particles[ze].origin.x = 0;

		if(particles[ze].origin.x + d > range.dimens.w) particles[ze].origin.x = range.dimens.w - d;

		if(particles[ze].origin.y < 0)
		{
			particles[ze].origin.x = startX;
			particles[ze].origin.y = startY;
			particles[ze].dimens.w = minD;
			particles[ze].dimens.h = minD;
			continue;
		}

		PLEX_drawSpriteTintedInt(drawLayer, aniIndex, range.origin.x + particles[ze].origin.x, range.origin.y + particles[ze].origin.y, particles[ze].dimens.w, particles[ze].dimens.h, r * distPerc, g * distPerc, b * distPerc, sprite, screenOffset, time, errorline, errorfile);
	}
}

// a static function to do the lasershow effect

static void p_laserShowEffect(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a, const double perc, const double minPerc, const PLEX_RECT range, const bool screenOffset, const bool initial, const size_t drawLayer, const uint64_t time, const size_t errorline, const char* const errorfile)
{
	const size_t phase = time % 10000;

	if(phase % 4)
	{
		const double laserDist = range.dimens.w/4.0;

		for(size_t ze = 0; ze < 4; ++ze)
		{
			const double x1 = laserDist/2 + range.origin.x + ze * laserDist;

			double x2 = x1;

			if(ze % 2)
			{
				if(perc < 0.5) x2 -= laserDist/2 - perc * laserDist * 2;
				else x2 += laserDist/2 - (perc - 0.5) * laserDist * 2;
			}else{
				if(perc < 0.5) x2 += laserDist/2 - perc * laserDist * 2;
				else x2 -= laserDist/2 - (perc - 0.5) * laserDist * 2;
			}

			PLEX_drawLine(1, x1, range.origin.y, x2, range.origin.y + range.dimens.h, r, g, b, a, PLEX_UNIT(0.1), false);
		}
	}
}

// creates a percentage based range so the screen range can adjust to screen size changes

static PLEX_RECT p_propRange(const PLEX_RECT range)
{
	PLEX_RECT ret;

	ret.origin.x = range.origin.x/(double)PLEX_WW(false);
	ret.origin.y = range.origin.y/(double)PLEX_WH(false);
	ret.dimens.w = range.dimens.w/(double)PLEX_WW(false);
	ret.dimens.h = range.dimens.h/(double)PLEX_WH(false);

	return ret;
}

// the static function to differentiate  between different effects

static void p_triggerEffect(const PLEX_SCREENEFFECT_TYPE type, const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a, const double perc, const double minPerc, const bool ranged, const PLEX_RECT range, const bool screenOffset, const bool initial, PLEX_RECT* particles, const size_t drawLayer, PLEX_SPRITE* sprite, const size_t aniIndex, const uint64_t time, const size_t errorline, const char* const errorfile)
{
	PLEX_RECT arange;

	if(p_disableScreenEffects) return;

	arange = ranged ? range : PLEX_convRect(PLEX_convPoint(0, 0), PLEX_convDimens(PLEX_WW(screenOffset), PLEX_WH(screenOffset)));

	switch(type)
	{
		case PLEX_SCREENEFFECT_TINTFADE:
			p_tintFadeEffect(r, g, b, a, perc, minPerc, arange, screenOffset, drawLayer, errorline, errorfile);
		break;

		case PLEX_SCREENEFFECT_SPLATTER:
			p_splatterEffect(r, g, b, a, perc, minPerc, arange, screenOffset, initial, particles, drawLayer, errorline, errorfile);
		break;

		case PLEX_SCREENEFFECT_TINT:
			p_tintEffect(r, g, b, a, arange, screenOffset, drawLayer, errorline, errorfile);
		break;

		case PLEX_SCREENEFFECT_RAIN:
			p_rainEffect(r, g, b, a, perc, minPerc, arange, screenOffset, initial, particles, drawLayer, errorline, errorfile);
		break;

		case PLEX_SCREENEFFECT_SNOW:
			p_snowEffect(r, g, b, a, perc, minPerc, arange, screenOffset, initial, particles, drawLayer, errorline, errorfile);
		break;

		case PLEX_SCREENEFFECT_WIND:
			p_windEffect(r, g, b, a, perc, minPerc, arange, screenOffset, initial, particles, drawLayer, errorline, errorfile);
		break;

		case PLEX_SCREENEFFECT_PROJECTILERAIN:
			p_projRainEffect(r, g, b, a, perc, minPerc, arange, screenOffset, initial, particles, drawLayer, sprite, aniIndex, time, errorline, errorfile);
		break;

		case PLEX_SCREENEFFECT_PAINTOVER:
			p_paintoverEffect(r, g, b, a, perc, minPerc, arange, screenOffset, initial, particles, drawLayer, sprite, aniIndex, time, errorline, errorfile);
		break;

		case PLEX_SCREENEFFECT_SMOKE:
			p_smokeEffect(r, g, b, a, perc, minPerc, arange, screenOffset, initial, particles, drawLayer, sprite, aniIndex, time, errorline, errorfile);
		break;

		case PLEX_SCREENEFFECT_LASERSHOW:
			p_laserShowEffect(r, g, b, a, perc, minPerc, arange, screenOffset, initial, drawLayer, time, errorline, errorfile);
		break;
	};
}

// the base function to fork doing a screen effect

static int64_t p_doScreenEffectBase(const PLEX_SCREENEFFECT_TYPE type, const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a, const bool loop, const bool screenOffset, const uint64_t duration, const double minPerc, const uint64_t time, const bool ranged, const PLEX_RECT range, const size_t errorline, const char* const errorfile)
{
	P_SCREENEFFECT* effect = NULL;

	size_t index = 0;

	if(p_nextIndex != -1)
	{
		index = p_nextIndex;

		effect = PLEX_getExpandArrayEntryInt(index, p_effects, errorline, errorfile);

		if(effect == NULL)
		{
			PLEX_errorInt(PLEX_ERROR_CATEGORY_SCREENEFFECTS, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SCREENEFFECT_ONDOING, PLEX_ERRORMESS_SCREENEFFECT_SCREENEFFECT, errorline, errorfile);
			return 0;
		}

		if(effect->sprite != NULL) PLEX_destroySpriteInt(&effect->sprite, errorline, errorfile);

		p_nextIndex = -1;
	}else{
		if(!PLEX_incrementExpandArrayInt(p_effects, errorline, errorfile))
		{
			PLEX_errorInt(PLEX_ERROR_CATEGORY_SCREENEFFECTS, PLEX_ERROR_INCREMENT, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SCREENEFFECT_ONDOING, PLEX_ERRORMESS_SCREENEFFECT_SCREENEFFECTSTACK, errorline, errorfile);
			return 0;
		}

		index = PLEX_expandArrayCountInt(p_effects, errorline, errorfile) - 1;

		effect = PLEX_getExpandArrayLastInt(p_effects, errorline, errorfile);

		if(effect == NULL)
		{
			PLEX_errorInt(PLEX_ERROR_CATEGORY_SCREENEFFECTS, PLEX_ERROR_ACQUIRELAST, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SCREENEFFECT_ONDOING, PLEX_ERRORMESS_SCREENEFFECT_SCREENEFFECT, errorline, errorfile);
			return 0;
		}
	}

	memset(effect, 0, sizeof(P_SCREENEFFECT));

	effect->type = type;
	effect->loop = loop;
	effect->screenOffset = screenOffset;
	effect->duration = duration;
	effect->start = time;
	effect->r = r;
	effect->g = g;
	effect->b = b;
	effect->a = a;
	effect->minPerc = minPerc;
	effect->ranged = ranged;
	effect->range = range;
	effect->propRange = p_propRange(range);
	effect->active = true;
	effect->initial = true;
	effect->hidden = false;
	effect->drawLayer = 0;
	effect->sprite = NULL;
	effect->aniIndex = 0;

	return index;
}

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

// specialized functions ----------------------------------------------------------------------------------------------------

int64_t PLEX_doScreenEffectInt(const PLEX_SCREENEFFECT_TYPE type, const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a, const bool loop, const bool screenOffset, const uint64_t duration, const double minPerc, const uint64_t time, const size_t errorline, const char* const errorfile)
{
	PLEX_RECT range;

	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_SCREENEFFECTS, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SCREENEFFECT_ONDOING, errorline, errorfile);
		return -1;
	}

	range = PLEX_convRect(PLEX_convPoint(0,0), PLEX_convDimens(PLEX_WW(screenOffset), PLEX_WH(screenOffset)));

	return p_doScreenEffectBase(type, r, g, b, a, loop, screenOffset, duration, minPerc, time, false, range, errorline, errorfile);
}

int64_t PLEX_doScreenEffectRangedInt(const PLEX_SCREENEFFECT_TYPE type, const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a, const bool loop, const bool screenOffset, const uint64_t duration, const double minPerc, const PLEX_RECT range, const uint64_t time, const size_t errorline, const char* const errorfile)
{
	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_SCREENEFFECTS, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SCREENEFFECT_ONDOINGRANGED, errorline, errorfile);
		return -1;
	}

	return p_doScreenEffectBase(type, r, g, b, a, loop, screenOffset, duration, minPerc, time, true, range, errorline, errorfile);
}

void PLEX_hideScreenEffectInt(const int64_t index, const size_t errorline, const char* const errorfile)
{
	P_SCREENEFFECT* effect = NULL;

	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_SCREENEFFECTS, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SCREENEFFECT_ONHIDING, errorline, errorfile);
		return;
	}

	if(index < 0)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SCREENEFFECTS, PLEX_ERROR_UNDERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SCREENEFFECT_ONHIDING, PLEX_ERRORMESS_GENERIC_INDEX, errorline, errorfile);
		return;
	}

	if(index >= PLEX_expandArrayCountInt(p_effects, errorline, errorfile))
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SCREENEFFECTS, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SCREENEFFECT_ONHIDING, PLEX_ERRORMESS_GENERIC_INDEX, errorline, errorfile);
		return;
	}

	effect = PLEX_getExpandArrayEntryInt(index, p_effects, errorline, errorfile);

	if(effect == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SCREENEFFECTS, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SCREENEFFECT_ONHIDING, PLEX_ERRORMESS_SCREENEFFECT_SCREENEFFECT, errorline, errorfile);
		return;
	}

	if(!effect->active)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SCREENEFFECTS, PLEX_ERROR_DISABLED, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_SCREENEFFECT_ONHIDING, PLEX_ERRORMESS_SCREENEFFECT_SCREENEFFECT, errorline, errorfile);
		return;
	}

	if(effect->hidden)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_SCREENEFFECTS, PLEX_ERROR_BADOPERATION, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_OP_HIDEHIDDENSCREENEFFECT, errorline, errorfile);
		return;
	}

	effect->hidden = true;
}

void PLEX_unhideScreenEffectInt(const int64_t index, const size_t errorline, const char* const errorfile)
{
	P_SCREENEFFECT* effect = NULL;

	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_SCREENEFFECTS, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SCREENEFFECT_ONUNHIDING, errorline, errorfile);
		return;
	}

	if(index < 0)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SCREENEFFECTS, PLEX_ERROR_UNDERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SCREENEFFECT_ONUNHIDING, PLEX_ERRORMESS_GENERIC_INDEX, errorline, errorfile);
		return;
	}

	if(index >= PLEX_expandArrayCountInt(p_effects, errorline, errorfile))
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SCREENEFFECTS, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SCREENEFFECT_ONUNHIDING, PLEX_ERRORMESS_GENERIC_INDEX, errorline, errorfile);
		return;
	}

	effect = PLEX_getExpandArrayEntryInt(index, p_effects, errorline, errorfile);

	if(effect == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SCREENEFFECTS, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SCREENEFFECT_ONUNHIDING, PLEX_ERRORMESS_SCREENEFFECT_SCREENEFFECT, errorline, errorfile);
		return;
	}

	if(!effect->active)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SCREENEFFECTS, PLEX_ERROR_DISABLED, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_SCREENEFFECT_ONUNHIDING, PLEX_ERRORMESS_SCREENEFFECT_SCREENEFFECT, errorline, errorfile);
		return;
	}

	if(!effect->hidden)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_SCREENEFFECTS, PLEX_ERROR_BADOPERATION, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_OP_UNHIDESHOWINGSCREENEFFECT, errorline, errorfile);
		return;
	}

	effect->hidden = false;
}

void PLEX_ceaseScreenEffectInt(const int64_t index, const size_t errorline, const char* const errorfile)
{
	P_SCREENEFFECT* effect = NULL;

	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_SCREENEFFECTS, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SCREENEFFECT_ONCEASING, errorline, errorfile);
		return;
	}

	if(index < 0)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SCREENEFFECTS, PLEX_ERROR_UNDERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SCREENEFFECT_ONCEASING, PLEX_ERRORMESS_GENERIC_INDEX, errorline, errorfile);
		return;
	}

	if(index >= PLEX_expandArrayCountInt(p_effects, errorline, errorfile))
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SCREENEFFECTS, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SCREENEFFECT_ONCEASING, PLEX_ERRORMESS_GENERIC_INDEX, errorline, errorfile);
		return;
	}

	effect = PLEX_getExpandArrayEntryInt(index, p_effects, errorline, errorfile);

	if(effect == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SCREENEFFECTS, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SCREENEFFECT_ONCEASING, PLEX_ERRORMESS_SCREENEFFECT_SCREENEFFECT, errorline, errorfile);
		return;
	}

	if(!effect->active)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SCREENEFFECTS, PLEX_ERROR_DISABLED, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_SCREENEFFECT_ONCEASING, PLEX_ERRORMESS_SCREENEFFECT_SCREENEFFECT, errorline, errorfile);
		return;
	}

	p_nextIndex = index;

	effect->active = false;
}

void PLEX_seedSpriteInt(PLEX_SPRITE* sprite, const size_t aniIndex, const size_t index, const uint64_t time, const size_t errorline, const char* const errorfile)
{
	P_SCREENEFFECT* effect = NULL;

	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_SCREENEFFECTS, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SCREENEFFECT_ONSEEDSPRITE, errorline, errorfile);
		return;
	}

	if(p_effects == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SCREENEFFECTS, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SCREENEFFECT_ONSEEDSPRITE, PLEX_ERRORMESS_SCREENEFFECT_SCREENEFFECTSTACK, errorline, errorfile);
		return;
	}

	if(sprite == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SCREENEFFECTS, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_SCREENEFFECT_ONSEEDSPRITE, PLEX_ERRORMESS_SPRITE_SPRITE, errorline, errorfile);
		return;
	}

	if(aniIndex >= PLEX_spriteAnimationCountInt(sprite, errorline, errorfile))
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SCREENEFFECTS, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_SCREENEFFECT_ONSEEDSPRITE, PLEX_ERRORMESS_SPRITE_ANIINDEX, errorline, errorfile);
		return;
	}

	effect = PLEX_getExpandArrayEntryInt(index, p_effects, errorline, errorfile);

	if(effect == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SCREENEFFECTS, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SCREENEFFECT_ONSEEDSPRITE, PLEX_ERRORMESS_SCREENEFFECT_SCREENEFFECT, errorline, errorfile);
		return;
	}

	if(effect->sprite != NULL) PLEX_destroySpriteInt(&effect->sprite, errorline, errorfile);

	effect->sprite = PLEX_copySpriteInt(sprite, errorline, errorfile);
	effect->aniIndex = aniIndex;

	if(PLEX_isSpriteStoppedInt(sprite, errorline, errorfile)) PLEX_startSpriteInt(time, effect->sprite, errorline, errorfile);
}

void PLEX_repositionScreenEffectInt(const size_t index, const PLEX_RECT range, const size_t errorline, const char* const errorfile)
{
	P_SCREENEFFECT* effect = NULL;

	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_SCREENEFFECTS, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SCREENEFFECT_ONREPOSITION, errorline, errorfile);
		return;
	}

	if(p_effects == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SCREENEFFECTS, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SCREENEFFECT_ONREPOSITION, PLEX_ERRORMESS_SCREENEFFECT_SCREENEFFECTSTACK, errorline, errorfile);
		return;
	}

	if(index >= PLEX_expandArrayCountInt(p_effects, errorline, errorfile))
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SCREENEFFECTS, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_SCREENEFFECT_ONREPOSITION, PLEX_ERRORMESS_SPRITE_ANIINDEX, errorline, errorfile);
		return;
	}

	effect = PLEX_getExpandArrayEntryInt(index, p_effects, errorline, errorfile);

	if(effect == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SCREENEFFECTS, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SCREENEFFECT_ONREPOSITION, PLEX_ERRORMESS_SCREENEFFECT_SCREENEFFECT, errorline, errorfile);
		return;
	}

	effect->ranged = true;
	effect->range = range;
	effect->propRange = p_propRange(range);
}

void PLEX_screenEffectDrawLayerInt(const size_t index, const size_t drawLayer, const size_t errorline, const char* const errorfile)
{
	P_SCREENEFFECT* effect = NULL;

	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_SCREENEFFECTS, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SCREENEFFECT_ONSETDRAWLAYER, errorline, errorfile);
		return;
	}

	if(p_effects == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SCREENEFFECTS, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SCREENEFFECT_ONSETDRAWLAYER, PLEX_ERRORMESS_SCREENEFFECT_SCREENEFFECTSTACK, errorline, errorfile);
		return;
	}

	if(index >= PLEX_expandArrayCountInt(p_effects, errorline, errorfile))
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SCREENEFFECTS, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_SCREENEFFECT_ONSETDRAWLAYER, PLEX_ERRORMESS_SPRITE_ANIINDEX, errorline, errorfile);
		return;
	}

	effect = PLEX_getExpandArrayEntryInt(index, p_effects, errorline, errorfile);

	if(effect == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SCREENEFFECTS, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SCREENEFFECT_ONSETDRAWLAYER, PLEX_ERRORMESS_SCREENEFFECT_SCREENEFFECT, errorline, errorfile);
		return;
	}

	effect->drawLayer = drawLayer;
}

// start, update, end functions ---------------------------------------------------------------------------------------------

bool PLEX_startScreenEffectsInt(const uint64_t time, const size_t errorline, const char* const errorfile)
{
	if(p_running)
	{
		PLEX_errorInt0A(PLEX_ERROR_CATEGORY_SCREENEFFECTS, PLEX_ERROR_DOUBLESTART, PLEX_ERROR_SEVERITY_BADSTYLE, errorline, errorfile);
		return true;
	}

	p_effects = PLEX_genExpandArrayInt(PLEX_getMemProfileScreenEffectsPreload(), sizeof(P_SCREENEFFECT), errorline, errorfile);

	p_running = true;

	return true;
}

bool PLEX_updateScreenEffectsInt(const uint64_t time, const size_t errorline, const char* const errorfile)
{
	size_t count = 0;

	if(!p_running)
	{
		PLEX_errorInt0A(PLEX_ERROR_CATEGORY_SCREENEFFECTS, PLEX_ERROR_UPDATEBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, errorline, errorfile);
		return false;
	}

	count = PLEX_expandArrayCountInt(p_effects, errorline, errorfile);

	// p_nextIndex = -1;

	for(size_t ze = 0; ze < count; ++ze)
	{
		P_SCREENEFFECT* effect = PLEX_getExpandArrayEntryInt(ze, p_effects, errorline, errorfile);

		double duration = 0;

		if(PLEX_isSizing())
		{
			effect->initial = true;
			effect->start = time;

			effect->range.origin.x = PLEX_UNIT(effect->propRange.origin.x);
			effect->range.origin.y = PLEX_UNIT(effect->propRange.origin.y);
			effect->range.dimens.w = PLEX_UNIT(effect->propRange.dimens.w);
			effect->range.dimens.h = PLEX_UNIT(effect->propRange.dimens.h);
		}

		if(effect == NULL)
		{
			PLEX_errorInt(PLEX_ERROR_CATEGORY_SCREENEFFECTS, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SCREENEFFECT_ONUPDATE, PLEX_ERRORMESS_SCREENEFFECT_SCREENEFFECT, errorline, errorfile);
			return false;
		}

		if(!effect->active)
		{
			if(p_nextIndex == -1) p_nextIndex = ze;
			continue;
		}

		if(effect->hidden) continue;

		duration = time - effect->start;

		if(duration <= effect->duration)
		{
			const double perc = duration/(double)effect->duration;

			p_triggerEffect(effect->type, effect->r, effect->g, effect->b, effect->a, perc, effect->minPerc, effect->ranged, effect->range, effect->screenOffset, effect->initial, (PLEX_RECT*)effect->particles, effect->drawLayer, effect->sprite, effect->aniIndex, time, errorline, errorfile);
		}else{
			p_triggerEffect(effect->type, effect->r, effect->g, effect->b, effect->a, 1, effect->minPerc, effect->ranged, effect->range, effect->screenOffset, effect->initial, (PLEX_RECT*)effect->particles, effect->drawLayer, effect->sprite, effect->aniIndex, time, errorline, errorfile);

			if(effect->loop) effect->start = time;
			else
			{
				effect->active = false;
				effect->over = true;
			}
		}

		effect->initial = false;
	}

	return true;
}

void PLEX_endScreenEffectsInt(const size_t errorline, const char* const errorfile)
{
	size_t count = 0;

	if(!p_running)
	{
		PLEX_errorInt0A(PLEX_ERROR_CATEGORY_SCREENEFFECTS, PLEX_ERROR_ENDBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, errorline, errorfile);
		return;
	}

	count = PLEX_expandArrayCountInt(p_effects, errorline, errorfile);

	for(size_t ze = 0; ze < count; ++ze)
	{
		P_SCREENEFFECT* next = PLEX_getExpandArrayEntryInt(ze, p_effects, errorline, errorfile);

		if(next == NULL)
		{
			PLEX_errorInt(PLEX_ERROR_CATEGORY_SCREENEFFECTS, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SCREENEFFECT_ONENDING, PLEX_ERRORMESS_SCREENEFFECT_SCREENEFFECT, errorline, errorfile);
			continue;
		}

		if(next->sprite != NULL) PLEX_destroySpriteInt(&next->sprite, errorline, errorfile);
	}

	PLEX_destroyExpandArrayInt(&p_effects, errorline, errorfile);
}

// setters ------------------------------------------------------------------------------------------------------------------

void PLEX_disableScreenEffects(){ p_disableScreenEffects = true; }
void PLEX_enableScreenEffects(){ p_disableScreenEffects = false; }

// getters ------------------------------------------------------------------------------------------------------------------

bool PLEX_screenEffectHiddenInt(const int64_t index, const size_t errorline, const char* const errorfile)
{
	size_t count = 0;

	P_SCREENEFFECT* screen = NULL;

	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_SCREENEFFECTS, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SCREENEFFECT_ONHIDDEN, errorline, errorfile);
		return false;
	}

	if(p_effects == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SCREENEFFECTS, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SCREENEFFECT_ONHIDDEN, PLEX_ERRORMESS_SCREENEFFECT_SCREENEFFECT, errorline, errorfile);
		return false;
	}

	if(index < 0)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SCREENEFFECTS, PLEX_ERROR_UNDERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SCREENEFFECT_ONHIDDEN, PLEX_ERRORMESS_GENERIC_INDEX, errorline, errorfile);
		return false;
	}

	count = PLEX_expandArrayCountInt(p_effects, errorline, errorfile);

	if(index >= count)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SCREENEFFECTS, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SCREENEFFECT_ONHIDDEN, PLEX_ERRORMESS_GENERIC_INDEX, errorline, errorfile);
		return false;
	}

	screen = PLEX_getExpandArrayEntryInt(index, p_effects, errorline, errorfile);

	return screen->hidden;
}

bool PLEX_screenEffectOverInt(const int64_t index, const uint64_t time, const size_t errorline, const char* const errorfile)
{
	P_SCREENEFFECT* effect = NULL;

	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_SCREENEFFECTS, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_SCREENEFFECT_ONOVER, errorline, errorfile);
		return false;
	}

	if(index < 0 || p_disableScreenEffects) return true;

	effect = PLEX_getExpandArrayEntryInt(index, p_effects, errorline, errorfile);

	return effect->over;
}

bool PLEX_screenEffectsDisabled(){ return p_disableScreenEffects; }
