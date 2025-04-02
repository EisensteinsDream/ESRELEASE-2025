// NOTE: this should already have the graphics_low header included before this is compiled. No need to include it here. This is attached to the texture_low.c source file which is why I designate it as a .c.h.

// specialized functions ----------------------------------------------------------------------------------------------------

PLEX_LOW_TEXTURE PLEX_low_generateTexture(const Uint32 format, const int access, const int w, const int h)
{
	return SDL_CreateTexture(PLEX_low_getRenderer(), format, access, w, h);
}

void PLEX_low_makeGeneratedTexture(PLEX_LOW_TEXTURE texture, const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a)
{
	SDL_Texture* originalTarget = SDL_GetRenderTarget(PLEX_low_getRenderer());

	SDL_SetRenderTarget(PLEX_low_getRenderer(), texture);
	SDL_SetRenderDrawBlendMode(PLEX_low_getRenderer(), SDL_BLENDMODE_NONE);
	SDL_SetRenderDrawColor(PLEX_low_getRenderer(), r, g, b, a);
	SDL_RenderFillRect(PLEX_low_getRenderer(), NULL);
	SDL_SetRenderTarget(PLEX_low_getRenderer(), originalTarget);
	SDL_SetRenderDrawBlendMode(PLEX_low_getRenderer(), SDL_BLENDMODE_BLEND);

	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
}

void PLEX_low_textureFromSurfaceInt(SDL_Surface* surface, PLEX_LOW_TEXTURE* texture, const uint8_t a, const size_t errorline, const char* const errorfile)
{
	PLEX_LOW_TEXTURE copy = PLEX_LOW_NOTEXTURE;

	SDL_Texture* originalTarget = NULL;

	PLEX_LOW_TEXTURE lTexture = *texture;

	if(surface == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_LOWTEXTURE_ONGETFROMSURFACE, PLEX_ERRORMESS_LOWGRAPHICS_SDLSURFACE, errorline, errorfile);
		return;
	}

	copy = SDL_CreateTextureFromSurface(PLEX_low_getRenderer(), surface);

	if(copy == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_CREATE, PLEX_ERROR_SEVERITY_MAJOR, PLEX_ERRORMESS_LOWTEXTURE_ONGETFROMSURFACE, PLEX_ERRORMESS_TEXTURE_TEXTURECOPY, errorline, errorfile);
		return;
	}

	originalTarget = SDL_GetRenderTarget(PLEX_low_getRenderer());

	// clear the texture to pure invisible
	SDL_SetRenderTarget(PLEX_low_getRenderer(), lTexture);
	SDL_SetRenderDrawBlendMode(PLEX_low_getRenderer(), SDL_BLENDMODE_NONE);
	SDL_SetRenderDrawColor(PLEX_low_getRenderer(), 0, 0, 0, 0);
	SDL_RenderFillRect(PLEX_low_getRenderer(), NULL);

	// copy the copytex loaded from file to new texture
	SDL_RenderCopy(PLEX_low_getRenderer(), copy, NULL, NULL);

	SDL_SetRenderTarget(PLEX_low_getRenderer(), originalTarget);

	SDL_DestroyTexture(copy);

	SDL_SetTextureBlendMode(lTexture, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(lTexture, a);
	SDL_SetRenderDrawBlendMode(PLEX_low_getRenderer(), SDL_BLENDMODE_BLEND);

	*texture = lTexture;
}

void PLEX_low_destroyTextureInt(PLEX_LOW_TEXTURE* texture, const size_t errorline, const char* const errorfile)
{
	if(texture == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_FREENULLPTR, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_LOWTEXTURE_ONDESTROY, PLEX_ERRORMESS_TEXTURE_TEXTURE, errorline, errorfile);
		return;
	}

	if(*texture == PLEX_LOW_NOTEXTURE)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_FREENULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_LOWTEXTURE_ONDESTROY, PLEX_ERRORMESS_TEXTURE_TEXTURE, errorline, errorfile);
		return;
	}

	SDL_DestroyTexture(*texture);
}

void PLEX_low_clearTexture(PLEX_LOW_TEXTURE texture)
{
	SDL_Texture* originalTarget = SDL_GetRenderTarget(PLEX_low_getRenderer());

	SDL_SetRenderTarget(PLEX_low_getRenderer(), texture);
	SDL_SetRenderDrawBlendMode(PLEX_low_getRenderer(), SDL_BLENDMODE_NONE);
	SDL_SetRenderDrawColor(PLEX_low_getRenderer(), 0, 0, 0, 0); // < alpha clear
	SDL_RenderFillRect(PLEX_low_getRenderer(), NULL);
	SDL_SetRenderTarget(PLEX_low_getRenderer(), originalTarget);
	SDL_SetRenderDrawBlendMode(PLEX_low_getRenderer(), SDL_BLENDMODE_BLEND);
}

void PLEX_low_copyTextureOntoTexture(PLEX_LOW_TEXTURE from, PLEX_LOW_TEXTURE to, SDL_Rect area, SDL_Rect toArea)
{
	SDL_Texture* originalTarget = SDL_GetRenderTarget(PLEX_low_getRenderer());

	SDL_SetTextureBlendMode(to, SDL_BLENDMODE_NONE);

	SDL_SetRenderTarget(PLEX_low_getRenderer(), to);

	SDL_RenderCopy(PLEX_low_getRenderer(), from, &area, &toArea);

	SDL_SetRenderTarget(PLEX_low_getRenderer(), originalTarget);
}

bool PLEX_low_compTextures(const PLEX_LOW_TEXTURE a, const PLEX_LOW_TEXTURE b)
{
	return a == b;
}

bool PLEX_low_lessTextures(const PLEX_LOW_TEXTURE a, const PLEX_LOW_TEXTURE b)
{
	return a < b;
}

// setters ------------------------------------------------------------------------------------------------------------------

void PLEX_low_textureSetAlpha(PLEX_LOW_TEXTURE* toSet, const uint8_t alpha)
{
	SDL_SetTextureAlphaMod(*toSet, alpha);
}

// getters ------------------------------------------------------------------------------------------------------------------

void PLEX_low_textureWHInt(PLEX_LOW_TEXTURE texture, uint32_t* w, uint32_t* h, const size_t errorline, const char* const errorfile)
{
	int tw = 0;
	int th = 0;

	if(texture == PLEX_LOW_NOTEXTURE)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_ISNULLTEXTURE, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_LOWTEXTURE_ONGETWIDTHHEIGHT, PLEX_ERRORMESS_TEXTURE_TEXTURE, errorline, errorfile);

		*w = 0;
		*h = 0;
		return;
	}

	SDL_QueryTexture(texture, NULL, NULL, &tw, &th);
	*w = tw;
	*h = th;
}

SDL_BlendMode PLEX_low_getTextureBlendModeInt(PLEX_LOW_TEXTURE texture, const size_t errorline, const char* const errorfile)
{
	SDL_BlendMode ret;

	if(texture == PLEX_LOW_NOTEXTURE)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_ISNULLTEXTURE, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_LOWTEXTURE_ONGETBLENDMODE, PLEX_ERRORMESS_TEXTURE_TEXTURE, errorline, errorfile);
		return SDL_BLENDMODE_NONE;
	}

	SDL_GetTextureBlendMode(texture, &ret);

	return ret;
}

bool PLEX_low_isTextureNull(const PLEX_LOW_TEXTURE texture)
{
	return texture == PLEX_LOW_NOTEXTURE;
}
