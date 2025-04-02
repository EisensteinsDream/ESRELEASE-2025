// NOTE: this should already have the graphics_low header included before this is compiled. No need to include it here. This is attached to the graphics_low.c source file which is why I designate it as a .c.h.

// NOTE: global function descriptions in header.

// static values ------------------------------------------------------------------------------------------------------------

static SDL_Renderer* p_renderer = NULL;

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

// specialized functions ----------------------------------------------------------------------------------------------------

SDL_Window* PLEX_low_createSDLWindowInt(const char* const title, const uint32_t width, const uint32_t height, const bool allowResize, const size_t errorline, const char* const errorfile)
{
	int32_t flags = 0;

	const char* aTitle = "";

	SDL_Window* window = NULL;

	if(allowResize) flags |= SDL_WINDOW_RESIZABLE;

	if(title != NULL) aTitle = title;

	window = SDL_CreateWindow(aTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);

	if(window == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_LOWLEVELGRAPHICS_SDL, PLEX_ERROR_CREATE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_WINDOW_ONCREATELOWLEVEL, PLEX_ERRORMESS_WINDOW_WINDOW, errorline, errorfile);
		return NULL;
	}

	#if PLEX_RENDERER_SOFTWARE_ONLY
		p_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE | SDL_RENDERER_TARGETTEXTURE);
	#else
		p_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
	#endif

	if(p_renderer == NULL)
	{
		SDL_DestroyWindow(window);

		PLEX_errorInt(PLEX_ERROR_CATEGORY_LOWLEVELGRAPHICS_SDL, PLEX_ERROR_CREATE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_WINDOW_ONCREATELOWLEVEL, PLEX_ERRORMESS_LOWGRAPHICS_SDLRENDERER, errorline, errorfile);

		return NULL;
	}

	return window;
}

void PLEX_low_destroySDLWindowInt(SDL_Window* const window, const size_t errorline, const char* const errorfile)
{
	if(p_renderer == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_LOWLEVELGRAPHICS_SDL, PLEX_ERROR_FREENULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_WINDOW_ONDESTROYLOWLEVEL, PLEX_ERRORMESS_LOWGRAPHICS_SDLRENDERER, errorline, errorfile);
	}else{
		SDL_DestroyRenderer(p_renderer);
		p_renderer = NULL;
	}

	if(window == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_LOWLEVELGRAPHICS_SDL, PLEX_ERROR_FREENULL, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_WINDOW_ONDESTROYLOWLEVEL, PLEX_ERRORMESS_WINDOW_WINDOW, errorline, errorfile);
	}else SDL_DestroyWindow(window);
}

void PLEX_low_updateRendererInt(SDL_Window* const window, const uint32_t w, const uint32_t h, const size_t errorline, const char* const errorfile)
{
	SDL_Rect renderArea;

	if(window == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_LOWLEVELGRAPHICS_SDL, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_LOWTEXTURE_ONLOWLEVELGRAPHICSUPDATE, PLEX_ERRORMESS_WINDOW_WINDOW, errorline, errorfile);
		return;
	}

	if(p_renderer == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_LOWLEVELGRAPHICS_SDL, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_LOWTEXTURE_ONLOWLEVELGRAPHICSUPDATE, PLEX_ERRORMESS_LOWGRAPHICS_SDLRENDERER, errorline, errorfile);
		return;
	}

	SDL_RenderGetViewport(p_renderer, &renderArea);

	if(renderArea.w != w || renderArea.h != h)
	{
		renderArea.w = w;
		renderArea.h = h;

		SDL_RenderSetViewport(p_renderer, &renderArea);
	}

	SDL_RenderPresent(p_renderer);
	SDL_SetRenderDrawColor(p_renderer, 0, 0, 0, 255);
	SDL_RenderClear(p_renderer);
}

void PLEX_low_fillRect(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a, const SDL_Rect* s, const SDL_BlendMode blendMode)
{
	// no error if s is null

	SDL_SetRenderDrawBlendMode(p_renderer, blendMode);
	SDL_SetRenderDrawColor(p_renderer, r, g, b, a);
	SDL_RenderFillRect(p_renderer, s);

	SDL_SetRenderDrawBlendMode(p_renderer, SDL_BLENDMODE_BLEND);
}

void PLEX_low_fillRects(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a, const SDL_Rect* s, const size_t count, const SDL_BlendMode blendMode)
{
	// no error if s is null

	SDL_SetRenderDrawBlendMode(p_renderer, blendMode);
	SDL_SetRenderDrawColor(p_renderer, r, g, b, a);
	SDL_RenderFillRects(p_renderer, s, count);

	SDL_SetRenderDrawBlendMode(p_renderer, SDL_BLENDMODE_BLEND);
}

void PLEX_low_tintTexturesRGBInt(PLEX_LOW_TEXTURE* texture, const uint8_t r, const uint8_t g, const uint8_t b, const size_t errorline, const char* const errorfile)
{
	if(texture != PLEX_LOW_NOTEXTURE) SDL_SetTextureColorMod(*texture, r, g, b);
	else PLEX_errorInt(PLEX_ERROR_CATEGORY_LOWLEVELGRAPHICS_SDL, PLEX_ERROR_ISNULLTEXTURE, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_TEXTURE_ONTINTING, PLEX_ERRORMESS_LOWTEXTURE_INNERTEXTURE, errorline, errorfile);
}

void PLEX_low_copyTexture(PLEX_LOW_TEXTURE texture, const SDL_Rect* from, const SDL_Rect* to, const SDL_BlendMode blendMode)
{
	// Do not null check from or to

	SDL_SetTextureBlendMode(texture, blendMode);
	SDL_RenderCopy(p_renderer, texture, from, to);
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
}

void PLEX_low_copyTextureRotated(PLEX_LOW_TEXTURE texture, const SDL_Rect* from, const SDL_Rect* to, const double angle, const SDL_BlendMode blendMode)
{
	// Do not null check from or to

	SDL_SetTextureBlendMode(texture, blendMode);
	SDL_RenderCopyEx(p_renderer, texture, from, to, angle, NULL, SDL_FLIP_NONE);
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
}

void PLEX_low_clear(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a)
{
	SDL_SetRenderDrawColor(p_renderer, r, g, b, a);
	SDL_RenderClear(p_renderer);
}

// setters ------------------------------------------------------------------------------------------------------------------

void PLEX_low_setRenderTarget(PLEX_LOW_TEXTURE target){ SDL_SetRenderTarget(p_renderer, target); }

void PLEX_low_setBlendTarget(const SDL_BlendMode blendMode){ SDL_SetRenderDrawBlendMode(p_renderer, blendMode); }

// getters ------------------------------------------------------------------------------------------------------------------

SDL_Renderer* PLEX_low_getRenderer(){ return p_renderer; } // < declared in texture_low.h

void PLEX_low_getTintTexturesRGBInt(PLEX_LOW_TEXTURE texture, uint8_t* r, uint8_t* g, uint8_t* b, const size_t errorline, const char* const errorfile)
{
	Uint8 lr = 0, lg = 0, lb = 0;

	if(r == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_LOWLEVELGRAPHICS_SDL, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_LOWTEXTURE_ONGETTINT, PLEX_ERRORMESS_GENERIC_RED, errorline, errorfile);
		return;
	}

	*r = 0;

	if(g == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_LOWLEVELGRAPHICS_SDL, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_LOWTEXTURE_ONGETTINT, PLEX_ERRORMESS_GENERIC_GREEN, errorline, errorfile);
		return;
	}

	*g = 0;

	if(b == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_LOWLEVELGRAPHICS_SDL, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_LOWTEXTURE_ONGETTINT, PLEX_ERRORMESS_GENERIC_BLUE, errorline, errorfile);
		return;
	}

	*b = 0;

	if(texture == PLEX_LOW_NOTEXTURE)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_LOWLEVELGRAPHICS_SDL, PLEX_ERROR_ISNULLTEXTURE, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_LOWTEXTURE_ONGETTINT, PLEX_ERRORMESS_LOWTEXTURE_INNERTEXTURE, errorline, errorfile);
		return;
	}

	SDL_GetTextureColorMod(texture, &lr, &lg, &lb);

	*r = lr;
	*g = lg;
	*b = lb;
}

PLEX_LOW_TEXTURE PLEX_low_getRenderTargetInt(const size_t errorline, const char* const errorfile)
{
	if(p_renderer == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_LOWLEVELGRAPHICS_SDL, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_LOWGRAPHICS_ONGETRENDERER, PLEX_ERRORMESS_LOWGRAPHICS_SDLRENDERER, errorline, errorfile);
		return PLEX_LOW_NOTARGET;
	}

	return SDL_GetRenderTarget(p_renderer);
}

SDL_BlendMode PLEX_low_getRenderBlendModeInt(const size_t errorline, const char* const errorfile)
{
	SDL_BlendMode blendMode;

	if(p_renderer == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_LOWLEVELGRAPHICS_SDL, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_LOWGRAPHICS_ONGETBLENDMODE, PLEX_ERRORMESS_LOWGRAPHICS_SDLRENDERER, errorline, errorfile);
		return SDL_BLENDMODE_NONE;
	}

	SDL_GetRenderDrawBlendMode(p_renderer, &blendMode);

	return blendMode;
}
