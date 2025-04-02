#include "windowing/texture_low.h"

// NOTE: this file is intended to simply fork different low level texture rendering. If the PLEX_RENDERER_TYPE is anything except what's listed below there will be compilation problems.

#if (PLEX_RENDERER_TYPE == PLEX_RENDERER_TYPE_SDL)
	#include "texture_low/texture_low_SDL.c.h"
#endif
