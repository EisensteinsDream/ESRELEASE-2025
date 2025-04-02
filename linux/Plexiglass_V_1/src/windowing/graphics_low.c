#include "windowing/graphics_low.h"

// NOTE: this file is intended to simply fork different low level renderers. If the PLEX_RENDERER_TYPE is anything except what's listed below there will be compilation problems.

#if (PLEX_RENDERER_TYPE == PLEX_RENDERER_TYPE_SDL)
	#include "graphics_low/graphics_low_SDL.c.h"
#endif
