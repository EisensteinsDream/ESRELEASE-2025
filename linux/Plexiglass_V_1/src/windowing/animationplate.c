#include "windowing/animationplate.h"

// NOTE: global function descriptions in header.

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

// specialized functions ----------------------------------------------------------------------------------------------------

PLEX_ANIMATION_PLATE PLEX_createAnimationPlateInt(const double wPerc, const double hPerc, const size_t base, const size_t errorline, const char* const errorfile)
{
	PLEX_ANIMATION_PLATE ret;

	uint32_t w = 0;
	uint32_t h = 0;

	memset(&ret, 0, sizeof(ret));

	if(!wPerc)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ANIMATION_PLATE, PLEX_ERROR_ZEROVALUE, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_ANIMATIONPLATE_ONCREATE, PLEX_ERRORMESS_GENERIC_WPERC, errorline, errorfile);
		return ret;
	}

	if(!hPerc)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ANIMATION_PLATE, PLEX_ERROR_ZEROVALUE, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_ANIMATIONPLATE_ONCREATE, PLEX_ERRORMESS_GENERIC_HPERC, errorline, errorfile);
		return ret;
	}

	if(!base)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ANIMATION_PLATE, PLEX_ERROR_ISNULLTEXTURE, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_ANIMATIONPLATE_ONCREATE, PLEX_ERRORMESS_TEXTURE_TEXTURE, errorline, errorfile);
		return ret;
	}

	ret.base = base;

	PLEX_textureWHInt(base, &w, &h, errorline, errorfile);

	if(!w)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ANIMATION_PLATE, PLEX_ERROR_ZEROVALUE, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_ANIMATIONPLATE_ONCREATE, PLEX_ERRORMESS_GENERIC_WIDTH, errorline, errorfile);
		return ret;
	}

	if(!h)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ANIMATION_PLATE, PLEX_ERROR_ZEROVALUE, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_ANIMATIONPLATE_ONCREATE, PLEX_ERRORMESS_GENERIC_HEIGHT, errorline, errorfile);
		return ret;
	}

	ret.fw = w * wPerc;
	ret.fh = h * hPerc;
	ret.wcount = w/ret.fw;
	ret.wperc = wPerc;
	ret.hperc = hPerc;

	return ret;
}

void PLEX_clearAnimationPlateInt(PLEX_ANIMATION_PLATE* plate, const size_t errorline, const char* const errorfile)
{
	if(plate == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ANIMATION_PLATE, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_ANIMATIONPLATE_ONCLEARING, PLEX_ERRORMESS_ANIMATIONPLATE_PLATE, errorline, errorfile);
		return;
	}

	if(!plate->base)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ANIMATION_PLATE, PLEX_ERROR_ISNULLTEXTURE, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_ANIMATIONPLATE_ONCLEARING, PLEX_ERRORMESS_TEXTURE_TEXTURE, errorline, errorfile);
		return;
	}

	PLEX_clearTextureInt(plate->base, errorline, errorfile);
}

void PLEX_unclearAnimationPlateInt(PLEX_ANIMATION_PLATE* plate, const size_t errorline, const char* const errorfile)
{
	if(plate == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ANIMATION_PLATE, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_ANIMATIONPLATE_ONUNCLEARING, PLEX_ERRORMESS_ANIMATIONPLATE_PLATE, errorline, errorfile);
		return;
	}

	if(!plate->base)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ANIMATION_PLATE, PLEX_ERROR_ISNULLTEXTURE, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_ANIMATIONPLATE_ONUNCLEARING, PLEX_ERRORMESS_TEXTURE_TEXTURE, errorline, errorfile);
		return;
	}

	PLEX_unclearTextureInt(plate->base, errorline, errorfile);
}

void PLEX_destroyAnimationPlateInt(PLEX_ANIMATION_PLATE** plate, const size_t errorline, const char* const errorfile)
{
	PLEX_ANIMATION_PLATE* platePtr = NULL;

	if(plate == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ANIMATION_PLATE, PLEX_ERROR_FREENULLPTR, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_ANIMATIONPLATE_ONDESTROY, PLEX_ERRORMESS_ANIMATIONPLATE_PLATE, errorline, errorfile);
		return;
	}

	platePtr = *plate;

	if(platePtr == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ANIMATION_PLATE, PLEX_ERROR_FREENULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_ANIMATIONPLATE_ONDESTROY, PLEX_ERRORMESS_ANIMATIONPLATE_PLATEPTR, errorline, errorfile);
		return;
	}

	PLEX_destroyTextureInt(platePtr->base, errorline, errorfile);

	platePtr->base = 0;

	*plate = NULL;
}

// getters ------------------------------------------------------------------------------------------------------------------

size_t PLEX_animationPlateTex(const PLEX_ANIMATION_PLATE plate)
{
	return plate.base;
}

size_t PLEX_animationPlateFW(const PLEX_ANIMATION_PLATE plate)
{
	return plate.fw;
}

size_t PLEX_animationPlateFH(const PLEX_ANIMATION_PLATE plate)
{
	return plate.fh;
}

size_t PLEX_animationPlateWCount(const PLEX_ANIMATION_PLATE plate)
{
	return plate.wcount;
}

double PLEX_animationPlateWPerc(const PLEX_ANIMATION_PLATE plate)
{
	return plate.wperc;
}

double PLEX_animationPlateHPerc(const PLEX_ANIMATION_PLATE plate)
{
	return plate.hperc;
}
