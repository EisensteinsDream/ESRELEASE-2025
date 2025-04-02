#include "windowing/animation.h"

// NOTE: global function descriptions in header.

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

// specialized functions ----------------------------------------------------------------------------------------------------

void PLEX_drawFrameInt(const size_t order, const double tx, const double ty, const double tw, const double th, const PLEX_ANIMATION* animation, const PLEX_ANIMATION_PLATE plate, const bool offset, const uint64_t time,  const size_t errorline, const char* const errorfile)
{
	uint32_t fx = 0;
	uint32_t fy = 0;
	uint32_t fw = 0;
	uint32_t fh = 0;

	if(animation == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ANIMATION, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_ANIMATION_ONDRAWFRAME, PLEX_ERRORMESS_ANIMATION_ANIMATION, errorline, errorfile);
		return;
	}

	PLEX_getFrameInt(&fx, &fy, &fw, &fh, animation, plate, time, errorline, errorfile);

	PLEX_printTextureInt(order, plate.base, fx, fy, fw, fh, tx, ty, tw, th, offset, errorline, errorfile);
}

void PLEX_drawFrameTintedInt(const size_t order, const double tx, const double ty, const double tw, const double th, const uint8_t r, const uint8_t g, const uint8_t b, const PLEX_ANIMATION* animation, const PLEX_ANIMATION_PLATE plate, const bool offset, const uint64_t time,  const size_t errorline, const char* const errorfile)
{
	uint32_t fx = 0;
	uint32_t fy = 0;
	uint32_t fw = 0;
	uint32_t fh = 0;

	if(animation == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ANIMATION, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_ANIMATION_ONDRAWFRAMETINTED, PLEX_ERRORMESS_ANIMATION_ANIMATION, errorline, errorfile);
		return;
	}

	PLEX_getFrameInt(&fx, &fy, &fw, &fh, animation, plate, time, errorline, errorfile);

	PLEX_printTextureTintedInt(order, plate.base, fx, fy, fw, fh, tx, ty, tw, th, r, g, b, offset, errorline, errorfile);
}

void PLEX_drawFrameRotateInt(const size_t order, const double tx, const double ty, const double tw, const double th, const PLEX_ANIMATION* animation, const PLEX_ANIMATION_PLATE plate, const double angle, const bool offset, const uint64_t time,  const size_t errorline, const char* const errorfile)
{
	uint32_t fx = 0;
	uint32_t fy = 0;
	uint32_t fw = 0;
	uint32_t fh = 0;

	if(animation == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ANIMATION, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_ANIMATION_ONDRAWFRAMEROTATED, PLEX_ERRORMESS_ANIMATION_ANIMATION, errorline, errorfile);
		return;
	}

	PLEX_getFrameInt(&fx, &fy, &fw, &fh, animation, plate, time, errorline, errorfile);

	PLEX_printTextureRotatedInt(order, plate.base, fx, fy, fw, fh, tx, ty, tw, th, angle, offset, errorline, errorfile);
}

void PLEX_drawFrameRotateTintedInt(const size_t order, const double tx, const double ty, const double tw, const double th, const PLEX_ANIMATION* animation, const PLEX_ANIMATION_PLATE plate, const uint8_t r, const uint8_t g, const uint8_t b, const double angle, const bool offset, const uint64_t time,  const size_t errorline, const char* const errorfile)
{
	uint32_t fx = 0;
	uint32_t fy = 0;
	uint32_t fw = 0;
	uint32_t fh = 0;

	if(animation == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ANIMATION, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_ANIMATION_ONDRAWFRAMEROTATEDTINTED, PLEX_ERRORMESS_ANIMATION_ANIMATION, errorline, errorfile);
		return;
	}

	PLEX_getFrameInt(&fx, &fy, &fw, &fh, animation, plate, time, errorline, errorfile);

	PLEX_printTextureRotatedTintedInt(order, plate.base, fx, fy, fw, fh, tx, ty, tw, th, angle, r, g, b, offset, errorline, errorfile);
}

void PLEX_addAnimationFrameInt(const size_t frame, PLEX_ANIMATION* animation, const size_t errorline, const char* const errorfile)
{
	size_t* framePtr = NULL;

	if(animation == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ANIMATION, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_ANIMATION_ONADDFRAME, PLEX_ERRORMESS_ANIMATIONPLATE_PLATE, errorline, errorfile);
		return;
	}

	if(!PLEX_incrementExpandArrayInt(animation->frames, errorline, errorfile))
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ANIMATION, PLEX_ERROR_INCREMENT, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_ANIMATION_ONADDFRAME, PLEX_ERRORMESS_ANIMATION_FRAMES, errorline, errorfile);
		return;
	}

	framePtr = PLEX_getExpandArrayLastInt(animation->frames, errorline, errorfile);

	if(framePtr == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ANIMATION, PLEX_ERROR_ACQUIRELAST, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_ANIMATION_ONADDFRAME, PLEX_ERRORMESS_ANIMATION_FRAMES, errorline, errorfile);
		return;
	}

	*framePtr = frame;
}

void PLEX_startAnimationInt(const uint64_t start, PLEX_ANIMATION* animation, const size_t errorline, const char* const errorfile)
{
	if(animation == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ANIMATION, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_ANIMATION_ONSTART, PLEX_ERRORMESS_ANIMATION_ANIMATION, errorline, errorfile);
		return;
	}

	if(animation->stopped) animation->start = start;
	animation->stopped = false;
}

void PLEX_stopAnimationInt(PLEX_ANIMATION* animation, const size_t errorline, const char* const errorfile)
{
	if(animation == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ANIMATION, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_ANIMATION_ONSTOP, PLEX_ERRORMESS_ANIMATION_ANIMATION, errorline, errorfile);
		return;
	}

	animation->stopped = true;
}

// setters ------------------------------------------------------------------------------------------------------------------

void PLEX_changeAnimationCycleSpeedInt(const uint64_t cycle, PLEX_ANIMATION* animation, const uint64_t time, const size_t errorline, const char* const errorfile)
{
	uint64_t frameLen = 0;
	uint64_t newFrameLen = 0;

	uint64_t frameStartCount = 0;

	size_t frameCount = 0;

	if(animation == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ANIMATION, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_ANIMATION_ONCYCLESPEEDCHANGE, PLEX_ERRORMESS_ANIMATION_ANIMATION, errorline, errorfile);
		return;
	}

	if(animation->cycle == cycle) return;

	frameCount = PLEX_expandArrayCountInt(animation->frames, errorline, errorfile);

	if(!frameCount)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ANIMATION, PLEX_ERROR_ZEROVALUE, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_ANIMATION_ONCYCLESPEEDCHANGE, PLEX_ERRORMESS_ANIMATION_FRAMES, errorline, errorfile);

		animation->cycle = 0;
		animation->start = 0;
		return;
	}

	frameLen = animation->cycle/frameCount;
	newFrameLen = cycle/frameCount;

	frameStartCount = animation->start/(double)frameLen;

	animation->cycle = cycle;
	animation->start = frameStartCount * newFrameLen;

	if(animation->start > time) animation->start = time - newFrameLen;
}

bool PLEX_syncAnimationsInt(const PLEX_ANIMATION a, PLEX_ANIMATION* b, const size_t errorline, const char* const errorfile)
{
	if(b == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ANIMATION, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_SPRITE_ONSYNCANIMATIONS, PLEX_ERRORMESS_ANIMATION_ANIMATION2, errorline, errorfile);
		return false;
	}

	b->start = a.start;
	b->cycle = a.cycle;
	b->stopped = a.stopped;

	return true;
}

// getters ------------------------------------------------------------------------------------------------------------------

size_t PLEX_getFrameInt(uint32_t* x, uint32_t* y, uint32_t* w, uint32_t* h, const PLEX_ANIMATION* animation, const PLEX_ANIMATION_PLATE plate, const uint64_t time, const size_t errorline, const char* const errorfile)
{
	uint64_t runTime = 0;

	uint64_t frameLen = 0;

	size_t frameCount = 0;
	size_t frameIndex = 0;

	size_t index = 0;
	size_t column = 0;
	size_t row = 0;

	size_t* indexPtr = NULL;

	if(animation == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ANIMATION, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_ANIMATION_ONGETFRAME, PLEX_ERRORMESS_ANIMATION_ANIMATION, errorline, errorfile);
		return 0;
	}

	runTime = animation->cycle ? (time - animation->start) % animation->cycle : 0;

	if(x == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ANIMATION, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_ANIMATION_ONGETFRAME, PLEX_ERRORMESS_GENERIC_DIMENX, errorline, errorfile);
		return 0;
	}

	*x = 0;

	if(y == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ANIMATION, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_ANIMATION_ONGETFRAME, PLEX_ERRORMESS_GENERIC_DIMENY, errorline, errorfile);
		return 0;
	}

	*y = 0;

	if(w == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ANIMATION, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_ANIMATION_ONGETFRAME, PLEX_ERRORMESS_GENERIC_DIMENW, errorline, errorfile);
		return 0;
	}

	*w = 0;

	if(h == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ANIMATION, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_ANIMATION_ONGETFRAME, PLEX_ERRORMESS_GENERIC_DIMENH, errorline, errorfile);
		return 0;
	}

	*h = 0;

	frameCount = PLEX_expandArrayCountInt(animation->frames, errorline, errorfile);

	if(!frameCount)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ANIMATION, PLEX_ERROR_ZEROVALUE, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_ANIMATION_ONGETFRAME, PLEX_ERRORMESS_GENERIC_COUNT, errorline, errorfile);
		return 0;
	}

	frameLen = animation->cycle/frameCount;

	if(!animation->stopped)
	{
		frameIndex = frameLen ? runTime/frameLen : 0;
		frameIndex %= frameCount;
	}

	indexPtr = (size_t*)PLEX_getExpandArrayEntryInt(frameIndex, animation->frames, errorline, errorfile);

	if(indexPtr == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ANIMATION, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_ANIMATION_ONGETFRAME, PLEX_ERRORMESS_GENERIC_INDEX, errorline, errorfile);
		return 0;
	}

	index = *indexPtr;
	column = plate.wcount ? index % plate.wcount : 0;
	row = plate.wcount ? index/plate.wcount : 0;

	*x = column * plate.fw;
	*y = row * plate.fh;
	*w = plate.fw;
	*h = plate.fh;

	return index;
}

bool PLEX_isAnimationStoppedInt(const PLEX_ANIMATION* animation, const size_t errorline, const char* const errorfile)
{
	if(animation == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ANIMATION, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_ANIMATION_ONISSTOPPED, PLEX_ERRORMESS_ANIMATION_ANIMATION, errorline, errorfile);
		return false;
	}

	return animation->stopped;
}

uint64_t PLEX_animationCycleLenInt(const PLEX_ANIMATION* animation, const size_t errorline, const char* const errorfile)
{
	if(animation == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ANIMATION, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_ANIMATION_ONGETCYCLE, PLEX_ERRORMESS_ANIMATION_ANIMATION, errorline, errorfile);
		return 0;
	}

	return animation->cycle;
}

uint64_t PLEX_animationStartLenInt(const PLEX_ANIMATION* animation, const size_t errorline, const char* const errorfile)
{
	if(animation == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_ANIMATION, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_ANIMATION_ONGETSTART, PLEX_ERRORMESS_ANIMATION_ANIMATION, errorline, errorfile);
		return 0;
	}

	return animation->start;
}

size_t PLEX_animationFrameCountInt(const PLEX_ANIMATION* animation, const size_t errorline, const char* const errorfile)
{
	if(animation == NULL)
	{
		// errpr
		return 0;
	}

	return PLEX_expandArrayCountInt(animation->frames, errorline, errorfile);
}
