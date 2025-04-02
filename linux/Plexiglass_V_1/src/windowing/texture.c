#include "windowing/texture.h"

// NOTE: global function descriptions in header

// structs ------------------------------------------------------------------------------------------------------------------

typedef struct
{
	PLEX_FAKESTRING_100 fileloc;
	uint32_t w, h;
	uint8_t r, g, b, a, tint;
} PLEX_TEXTURE_KEY_DATA;

typedef enum
{
	PLEX_TEXTURE_KEY_TYPE_BLANK = 0, // << this should always be 0
	PLEX_TEXTURE_KEY_TYPE_GENERATED = 1,
	PLEX_TEXTURE_KEY_TYPE_FILE = 2,
	PLEX_TEXTURE_KEY_TYPE_HEADERLESS = 3
} PLEX_TEXTURE_KEY_TYPE;

typedef struct
{
	PLEX_TEXTURE_KEY_TYPE type;
	PLEX_TEXTURE_KEY_DATA data;
} PLEX_TEXTURE_KEY;

typedef struct
{
	PLEX_TEXTURE_KEY key;
	PLEX_LOW_TEXTURE contents;
	size_t count;
	bool cleared;
} PLEX_TEXTURE;

// static values ------------------------------------------------------------------------------------------------------------

static PLEX_EXPANDARRAY* p_texBank = NULL;

static bool p_running = false;

// static functions ---------------------------------------------------------------------------------------------------------

// generates a blank texture struct

static PLEX_TEXTURE p_genBlankTexture()
{
	PLEX_TEXTURE ret;

	memset(&ret, 0, sizeof(ret));

	return ret;
}

// Loads an image from a file. PLEX only deals in 32-bit true color images. This function ensures that images that do not fit that description are converted.

static SDL_Surface* p_loadImage(const char* const fileloc, const size_t errorline, const char* const errorfile)
{
	SDL_Surface* loadSurf = IMG_Load(fileloc);
	SDL_Surface* copySurf = NULL;

	if(loadSurf == NULL)
	{
		const PLEX_FAKESTRING_100 targMessage = PLEX_fileLoadErrorPath(fileloc, PLEX_ERRORMESS_LOWGRAPHICS_SDLSURFACELOADED);

		PLEX_errorInt(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_FILELOAD, PLEX_ERROR_SEVERITY_MAJOR, PLEX_ERRORMESS_TEXTURE_ONLOADFROMFILE, PLEX_fts(targMessage), errorline, errorfile);
		PLEX_errorSDLImageInt(PLEX_ERROR_SEVERITY_MINOR, errorline, errorfile);
		return NULL;
	}

	if(!loadSurf->w)
	{
		SDL_FreeSurface(loadSurf);

		PLEX_errorInt(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_ZEROVALUE, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_TEXTURE_ONLOADFROMFILE, PLEX_ERRORMESS_GENERIC_WIDTH, errorline, errorfile);
		PLEX_errorSDLImageInt(PLEX_ERROR_SEVERITY_MINOR, errorline, errorfile);
		return NULL;
	}

	if(!loadSurf->h)
	{
		SDL_FreeSurface(loadSurf);

		PLEX_errorInt(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_ZEROVALUE, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_TEXTURE_ONLOADFROMFILE, PLEX_ERRORMESS_GENERIC_HEIGHT, errorline, errorfile);
		PLEX_errorSDLImageInt(PLEX_ERROR_SEVERITY_MINOR, errorline, errorfile);
		return NULL;
	}

	copySurf = SDL_CreateRGBSurface(0, loadSurf->w, loadSurf->h, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);

	if(copySurf == NULL)
	{
		SDL_FreeSurface(loadSurf);

		PLEX_errorInt(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_CREATE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_TEXTURE_ONLOADFROMFILE, PLEX_ERRORMESS_TEXTURE_TEXTURE2, errorline, errorfile);
		PLEX_errorSDLImageInt(PLEX_ERROR_SEVERITY_MINOR, errorline, errorfile);

		return NULL;
	}

	SDL_BlitSurface(loadSurf, NULL, copySurf, NULL);

	SDL_FreeSurface(loadSurf);

	return copySurf;
}

// tints an SDL surface by percentage of 'tint' and color values of rgba

static void p_tintSurface(SDL_Surface* toTint, const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a, const double tint)
{
	uint8_t* pixels = (uint8_t*)toTint->pixels;

	size_t pixCount = toTint->pitch * toTint->h;

	size_t inc = toTint->pitch/toTint->w;

	SDL_LockSurface(toTint);

	for(size_t ze = 0; ze < pixCount; ze += inc)
	{
		Uint8 cr, cg, cb, ca, nr, ng, nb, na;

		Uint32 nextCol = 0;

		memcpy(&nextCol, pixels + ze, inc);

		SDL_GetRGBA(nextCol, toTint->format, &cr, &cg, &cb, &ca);

		if(ca)
		{
			nr = (r * tint) + (cr * (1 - tint));
			ng = (g * tint) + (cg * (1 - tint));
			nb = (b * tint) + (cb * (1 - tint));
			na = a;

			nextCol = SDL_MapRGBA(toTint->format, nr, ng, nb, na);
		}

		memcpy(pixels + ze, &nextCol, inc);
	}

	SDL_UnlockSurface(toTint);
}

// dumps a surface to a headerless file. A file that is uncompressed and unencrypted. Takes more disk space but is much faster to load. Assumes a 32 bit RGBA surface with a pitch equal to w times 4 (ie. 32-bit with no packing)

static void p_dumpHeaderlessSurface(SDL_Surface* toDump, FILE* file)
{
	const uint32_t w = toDump->w;
	const uint32_t h = toDump->h;

	uint8_t* pixels = (uint8_t*)toDump->pixels;

	uint32_t pixCount = toDump->pitch * toDump->h;

	SDL_LockSurface(toDump);

	fwrite(&w, sizeof(uint32_t), 1, file);
	fwrite(&h, sizeof(uint32_t), 1, file);

	fwrite(pixels, pixCount, 1, file);

	SDL_UnlockSurface(toDump);
}

// generates a new texture by the argument specifications. The PLEX_TEXTURE_KEY_TYPE determines how

static bool p_genProcess(PLEX_TEXTURE* target, const PLEX_TEXTURE_KEY_TYPE type, const char* const fileloc, const uint32_t w, const uint32_t h, const uint8_t tint, const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a, const size_t errorline, const char* const errorfile)
{
	const SDL_BlendMode startBlendMode = PLEX_low_getRenderBlendMode();

	const uint32_t limit = PLEX_DEF_textureDimensLimit();

	if(type != PLEX_TEXTURE_KEY_TYPE_HEADERLESS)
	{
		uint32_t aw = w;
		uint32_t ah = h;

		if(aw > ah)
		{
			if(aw > limit)
			{
				const double ratio = ah/(double)aw;

				aw = limit;
				ah = limit * ratio;
			}
		}else{
			if(ah > limit)
			{
				const double ratio = aw/(double)ah;

				aw = limit * ratio;
				ah = limit;
			}
		}

		target->contents = PLEX_low_generateTexture(SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, aw, ah);

		if(PLEX_low_isTextureNull(target->contents))
		{
			PLEX_errorInt(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_CREATE, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_LOWTEXTURE_ONPROCESSGEN, PLEX_ERRORMESS_LOWTEXTURE_INNERTEXTURE, errorline, errorfile);
			return false;
		}
	}

	if(type == PLEX_TEXTURE_KEY_TYPE_GENERATED)
	{
		PLEX_low_makeGeneratedTexture(target->contents, r, g, b, a);
	}else{
		if(type == PLEX_TEXTURE_KEY_TYPE_FILE)
		{
			SDL_Surface* copySurf = p_loadImage(fileloc, errorline, errorfile);

			if(copySurf == NULL)
			{
				const PLEX_FAKESTRING_100 targMessage = PLEX_fileLoadErrorPath(fileloc, PLEX_ERRORMESS_LOWGRAPHICS_SDLSURFACE);

				PLEX_errorInt(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_FILELOAD, PLEX_ERROR_SEVERITY_MAJOR, PLEX_ERRORMESS_LOWTEXTURE_ONPROCESSGEN, PLEX_fts(targMessage), errorline, errorfile);
				return false;
			}

			if(tint) p_tintSurface(copySurf, r, g, b, a, tint/255.0);

			PLEX_low_textureFromSurfaceInt(copySurf, &target->contents, a, errorline, errorfile);

			SDL_FreeSurface(copySurf);
		}else{
			uint32_t w = 0;
			uint32_t h = 0;

			uint64_t size = 0;

			uint8_t* pixels = NULL;

			FILE* file = fopen(fileloc, "rb");

			SDL_Surface* copySurf = NULL;

			if(file == NULL)
			{
				const PLEX_FAKESTRING_100 targMessage = PLEX_fileLoadErrorPath(fileloc, PLEX_ERRORMESS_LOWGRAPHICS_SDLSURFACE);

				PLEX_errorInt(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_FILELOAD, PLEX_ERROR_SEVERITY_MAJOR, PLEX_ERRORMESS_LOWTEXTURE_ONPROCESSGEN, PLEX_fts(targMessage), errorline, errorfile);
				return false;
			}

			fread(&w, sizeof(uint32_t), 1, file);
			fread(&h, sizeof(uint32_t), 1, file);

			copySurf = SDL_CreateRGBSurface(0, w, h, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);

			size = w * h * sizeof(uint32_t);

			if(copySurf == NULL)
			{
				PLEX_errorInt(PLEX_ERROR_CATEGORY_SDL, PLEX_ERROR_CREATE, PLEX_ERROR_SEVERITY_MAJOR, PLEX_ERRORMESS_LOWTEXTURE_ONPROCESSGEN, PLEX_ERRORMESS_LOWGRAPHICS_SDLSURFACE, errorline, errorfile);
				fclose(file);
				return false;
			}

			pixels = (uint8_t*)copySurf->pixels;

			SDL_LockSurface(copySurf);

			fread(pixels, size, 1, file);

			target->contents = PLEX_low_generateTexture(SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, w, h);

			SDL_UnlockSurface(copySurf);

			fclose(file);

			PLEX_low_textureFromSurfaceInt(copySurf, &target->contents, a, errorline, errorfile);

			SDL_FreeSurface(copySurf);
		}
	}

	PLEX_low_setBlendTarget(startBlendMode);

	return true;
}

// generates a texture in a new texture spot or tries to reuse it if it can as specified by the arguments

static size_t p_genTexture(const PLEX_TEXTURE_KEY_TYPE type, const char* const fileloc, const uint32_t w, const uint32_t h, const uint8_t tint, const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a, const size_t errorline, const char* const errorfile)
{
	const size_t texBankCount = PLEX_expandArrayCount(p_texBank);

	PLEX_TEXTURE base;

	PLEX_TEXTURE* target = NULL;

	size_t index = PLEX_expandArrayCount(p_texBank);

	index = texBankCount;

	if(type == PLEX_TEXTURE_KEY_TYPE_BLANK) return 0;

	memset(&base, 0, sizeof(base));

	base.key.type = type;
	base.key.data.fileloc = PLEX_createString100Int(fileloc, errorline, errorfile);
	base.key.data.w = w;
	base.key.data.h = h;
	base.key.data.tint = tint;
	base.key.data.r = r;
	base.key.data.g = g;
	base.key.data.b = b;
	base.key.data.a = a;
	base.cleared = false;

	// searches to see if identical texture already exists, returns that if so. Does not do this with generated textures.

	if(type != PLEX_TEXTURE_KEY_TYPE_GENERATED)
	{
		for(size_t ze = 1; ze < texBankCount; ++ze)
		{
			target = PLEX_getExpandArrayEntryInt(ze, p_texBank, errorline, errorfile);

			if(target == NULL)
			{
				PLEX_errorInt(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_TEXTURE_ONGENHIGHLEVEL, PLEX_ERRORMESS_TEXTURE_TEXTURE, errorline, errorfile);
				return 0;
			}

			if(target->count || target->cleared)
			{
				if(!memcmp(&base.key, &target->key, sizeof(PLEX_TEXTURE_KEY)))
				{
					if(target->cleared) // unclears texture if it's identical but cleared
					{
						p_genProcess(target, target->key.type, PLEX_fts(target->key.data.fileloc), target->key.data.w, target->key.data.h, target->key.data.tint, target->key.data.r, target->key.data.g, target->key.data.b, target->key.data.a, errorline, errorfile);
						target->cleared = false;
					}

					++(target->count);
					return ze;
				}
			}else{
				PLEX_low_destroyTextureInt(&target->contents, errorline, errorfile);
				target->contents = PLEX_LOW_NOTEXTURE;
				index = ze;
				continue;
			}
		}
	}

	if(index == texBankCount)
	{
		if(!PLEX_incrementExpandArrayInt(p_texBank, errorline, errorfile))
		{
			PLEX_errorInt(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_INCREMENT, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_TEXTURE_ONGENHIGHLEVEL, PLEX_ERRORMESS_TEXTURE_TEXTUREBANK, errorline, errorfile);
			return 0;
		}
	}

	target = PLEX_getExpandArrayEntryInt(index, p_texBank, errorline, errorfile);

	if(target == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_TEXTURE_ONGENHIGHLEVEL, PLEX_ERRORMESS_TEXTURE_TEXTURE, errorline, errorfile);
		return 0;
	}

	*target = base;

	target->count = 1;

	if(!p_genProcess(target, type, fileloc, w, h, tint, r, g, b, a, errorline, errorfile)) return 0;

	return index;
}

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

// specialized functions ----------------------------------------------------------------------------------------------------

size_t PLEX_createGeneratedTextureInt(const uint32_t w, const uint32_t h, const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a, const size_t errorline, const char* const errorfile)
{
	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_TEXTURE_ONCREATE, errorline, errorfile);
		return 0;
	}

	if(p_texBank == NULL)
	{
		// keep impossible
		PLEX_errorInt(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_IMPOSSIBLE, PLEX_ERRORMESS_TEXTURE_ONCREATE, PLEX_ERRORMESS_TEXTURE_TEXTUREBANK, errorline, errorfile);
		return 0;
	}

	return p_genTexture(PLEX_TEXTURE_KEY_TYPE_GENERATED, "\0", w, h, a, r, g, b, a, errorline, errorfile);
}

size_t PLEX_loadTextureFromFileInt(const uint32_t w, const uint32_t h, const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a, const double tint, const char* const fileloc, const size_t errorline, const char* const errorfile)
{
	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_TEXTURE_ONLOADFROMFILE, errorline, errorfile);
		return 0;
	}

	if(p_texBank == NULL)
	{
		// keep impossible
		PLEX_errorInt(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_IMPOSSIBLE, PLEX_ERRORMESS_TEXTURE_ONLOADFROMFILE, PLEX_ERRORMESS_TEXTURE_TEXTUREBANK, errorline, errorfile);
		return 0;
	}

	if(fileloc == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_TEXTURE_ONLOADFROMFILE, PLEX_ERRORMESS_GENERIC_FILEPATH, errorline, errorfile);
		return 0;
	}

	if(fileloc[0] == '\0')
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_NOSTRINGLEN, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_TEXTURE_ONLOADFROMFILE, PLEX_ERRORMESS_GENERIC_FILEPATH, errorline, errorfile);
		return 0;
	}

	return p_genTexture(PLEX_TEXTURE_KEY_TYPE_FILE, fileloc, w, h, tint * 255, r, g, b, a, errorline, errorfile);
}

bool PLEX_convToHeaderlessImageInt(const char* const filelocFrom, const char* const filelocTo, const size_t errorline, const char* const errorfile)
{
	FILE* to = NULL;

	SDL_Surface* from = NULL;

	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_TEXTURE_ONCONVHEADERLESSIMAGE, errorline, errorfile);
		return false;
	}

	if(filelocFrom == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_TEXTURE_ONCONVHEADERLESSIMAGE, PLEX_ERRORMESS_GENERIC_FILEPATH, errorline, errorfile);
		return false;
	}

	if(filelocFrom[0] == '\0')
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_NOSTRINGLEN, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_TEXTURE_ONCONVHEADERLESSIMAGE, PLEX_ERRORMESS_GENERIC_FILEPATH, errorline, errorfile);
		return false;
	}

	if(filelocTo == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_TEXTURE_ONCONVHEADERLESSIMAGE, PLEX_ERRORMESS_GENERIC_FILEPATH2, errorline, errorfile);
		return false;
	}

	if(filelocTo[0] == '\0')
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_NOSTRINGLEN, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_TEXTURE_ONCONVHEADERLESSIMAGE, PLEX_ERRORMESS_GENERIC_FILEPATH2, errorline, errorfile);
		return false;
	}

	from = p_loadImage(filelocFrom, errorline, errorfile);

	if(from == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_CREATE, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_TEXTURE_ONCONVHEADERLESSIMAGE, PLEX_ERRORMESS_TEXTURE_TEXTURE, errorline, errorfile);
		return false;
	}

	to = fopen(filelocTo, "wb+");

	if(to == NULL)
	{
		SDL_FreeSurface(from);
		PLEX_errorInt(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_CREATE, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_TEXTURE_ONCONVHEADERLESSIMAGE, PLEX_ERRORMESS_TEXTURE_TEXTURE2, errorline, errorfile);
		return false;
	}

	p_dumpHeaderlessSurface(from, to);

	SDL_FreeSurface(from);

	fclose(to);

	return true;
}

size_t PLEX_loadTextureFromHeaderlessInt(const char* const fileloc, const size_t errorline, const char* const errorfile)
{
	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_TEXTURE_LOADFROMHEADERLESS, errorline, errorfile);
		return 0;
	}

	if(fileloc == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_TEXTURE_LOADFROMHEADERLESS, PLEX_ERRORMESS_GENERIC_FILEPATH, errorline, errorfile);
		return 0;
	}

	if(fileloc[0] == '\0')
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_NOSTRINGLEN, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_TEXTURE_LOADFROMHEADERLESS, PLEX_ERRORMESS_GENERIC_FILEPATH, errorline, errorfile);
		return 0;
	}

	return p_genTexture(PLEX_TEXTURE_KEY_TYPE_HEADERLESS, fileloc, 0, 0, 0, 0, 0, 0, 255, errorline, errorfile);
}

size_t PLEX_loadTextureFromFileOrHeaderlessInt(const uint32_t w, const uint32_t h, const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a, const double tint, const char* const fileloc, const char* const headerlessLoc, const size_t errorline, const char* const errorfile)
{
	FILE* headerlessFile = NULL;

	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_TEXTURE_LOADFROMFILEORHEADERLESS, errorline, errorfile);
		return 0;
	}

	if(fileloc == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_TEXTURE_LOADFROMFILEORHEADERLESS, PLEX_ERRORMESS_GENERIC_FILEPATH, errorline, errorfile);
		return 0;
	}

	if(fileloc[0] == '\0')
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_NOSTRINGLEN, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_TEXTURE_LOADFROMFILEORHEADERLESS, PLEX_ERRORMESS_GENERIC_FILEPATH, errorline, errorfile);
		return 0;
	}

	if(headerlessLoc == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_TEXTURE_LOADFROMFILEORHEADERLESS, PLEX_ERRORMESS_GENERIC_FILEPATH2, errorline, errorfile);
		return 0;
	}

	if(headerlessLoc[0] == '\0')
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_NOSTRINGLEN, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_TEXTURE_LOADFROMFILEORHEADERLESS, PLEX_ERRORMESS_GENERIC_FILEPATH2, errorline, errorfile);
		return 0;
	}

	headerlessFile = fopen(headerlessLoc, "rb");

	if(headerlessFile != NULL)
	{
		fclose(headerlessFile);

		return PLEX_loadTextureFromHeaderlessInt(headerlessLoc, errorline, errorfile);
	}else{
		// check for default that enables/disables dumping headerless images

		SDL_Surface* toDump = NULL;

		if(!PLEX_DEF_headerlessCopy()) return PLEX_loadTextureFromFileInt(w, h, r, g, b, a, tint, fileloc, errorline, errorfile);

		headerlessFile = fopen(headerlessLoc, "wb+");

		if(headerlessFile != NULL)
		{
			toDump = p_loadImage(fileloc, errorline, errorfile);

			if(toDump == NULL)
			{
				const PLEX_FAKESTRING_100 targMessage = PLEX_fileLoadErrorPath(headerlessLoc, PLEX_ERRORMESS_TEXTURE_TEXTURE);

				fclose(headerlessFile);
				remove(headerlessLoc);

				PLEX_errorInt(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_FILELOAD, PLEX_ERROR_SEVERITY_MAJOR, PLEX_ERRORMESS_TEXTURE_LOADFROMFILEORHEADERLESS, PLEX_fts(targMessage), errorline, errorfile);
				return 0;
			}

			if(tint) p_tintSurface(toDump, r, g, b, a, tint);

			p_dumpHeaderlessSurface(toDump, headerlessFile);

			fclose(headerlessFile);

			SDL_FreeSurface(toDump);

			return PLEX_loadTextureFromHeaderlessInt(headerlessLoc, errorline, errorfile);
		}else{
			const PLEX_FAKESTRING_100 targMessage = PLEX_fileLoadErrorPath(headerlessLoc, PLEX_ERRORMESS_GRAPHICS_HEADERLESSTEX);

			PLEX_errorInt(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_FILELOAD, PLEX_ERROR_SEVERITY_MAJOR, PLEX_ERRORMESS_TEXTURE_LOADFROMFILEORHEADERLESS, PLEX_fts(targMessage), errorline, errorfile);

			/* do not return */
		}
	}

	return PLEX_loadTextureFromFileInt(w, h, r, g, b, a, tint, fileloc, errorline, errorfile);
}

size_t PLEX_copyTextureInt(const size_t from, const uint32_t cx, const uint32_t cy, const uint32_t cw, const uint32_t ch, const size_t errorline, const char* const errorfile)
{
	size_t ret = 0;

	size_t texBankCount = 0;

	SDL_Rect area;
	SDL_Rect toArea;

	PLEX_TEXTURE* copied = NULL;

	PLEX_LOW_TEXTURE copiedInnerTexture = PLEX_LOW_NOTEXTURE;
	PLEX_LOW_TEXTURE innerTexture = PLEX_LOW_NOTEXTURE;

	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_TEXTURE_ONCOPY, errorline, errorfile);
		return 0;
	}

	if(p_texBank == NULL)
	{
		// keep impossible
		PLEX_errorInt(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_IMPOSSIBLE, PLEX_ERRORMESS_TEXTURE_ONCOPY, PLEX_ERRORMESS_TEXTURE_TEXTUREBANK, errorline, errorfile);
		return 0;
	}

	if(!from)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_ISNULLTEXTURE, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_TEXTURE_ONCOPY, PLEX_ERRORMESS_TEXTURE_FROMTEXTURE, errorline, errorfile);
		return 0;
	}

	texBankCount = PLEX_expandArrayCountInt(p_texBank, errorline, errorfile);

	if(from >= texBankCount)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_TEXTURE_ONCOPY, PLEX_ERRORMESS_TEXTURE_FROMTEXTURE, errorline, errorfile);
		return false;
	}

	copied = PLEX_getExpandArrayEntryInt(from, p_texBank, errorline, errorfile);

	if(copied == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_TEXTURE_ONCOPY, PLEX_ERRORMESS_TEXTURE_TEXTURE, errorline, errorfile);
		return 0;
	}

	ret = PLEX_createGeneratedTextureInt(cw, ch, 0, 0, 0, 0, errorline, errorfile);

	area.x = cx;
	area.y = cy;
	area.w = cw;
	area.h = ch;

	toArea.x = 0;
	toArea.y = 0;
	toArea.w = cw;
	toArea.h = ch;

	copiedInnerTexture = copied->contents;
	innerTexture = PLEX_innerTexture(ret);

	PLEX_low_copyTextureOntoTexture(copiedInnerTexture, innerTexture, area, toArea); // < don't use PLEX_innerTexture for the target pointer

	return ret;
}

void PLEX_destroyTextureInt(const size_t index, const size_t errorline, const char* const errorfile)
{
	PLEX_TEXTURE* target = NULL;

	size_t texBankCount = 0;

	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_TEXTURE_ONDESTROY, errorline, errorfile);
		return;
	}

	if(p_texBank == NULL)
	{
		// keep impossible
		PLEX_errorInt(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_IMPOSSIBLE, PLEX_ERRORMESS_TEXTURE_ONDESTROY, PLEX_ERRORMESS_TEXTURE_TEXTUREBANK, errorline, errorfile);
		return;
	}

	texBankCount = PLEX_expandArrayCountInt(p_texBank, errorline, errorfile);

	if(!index)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_ISNULLTEXTURE, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_TEXTURE_ONDESTROY, PLEX_ERRORMESS_TEXTURE_TEXTURE, errorline, errorfile);
		return;
	}

	if(index >= texBankCount)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_TEXTURE_ONDESTROY,  PLEX_ERRORMESS_GENERIC_INDEX, errorline, errorfile);
		return;
	}

	target = PLEX_getExpandArrayEntryInt(index, p_texBank, errorline, errorfile);

	if(target == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_TEXTURE_LOADFROMHEADERLESS, PLEX_ERRORMESS_TEXTURE_TEXTUREBANK, errorline, errorfile);
		return;
	}

	if(!target->count)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_ZEROVALUE, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_TEXTURE_ONDESTROY, PLEX_ERRORMESS_GENERIC_COUNT, errorline, errorfile);
		return;
	}

	--(target->count);
}

void PLEX_clearTextureInt(const size_t index, const size_t errorline, const char* const errorfile)
{
	PLEX_TEXTURE* target = NULL;

	size_t texBankCount = 0;

	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_TEXTURE_ONCLEAR, errorline, errorfile);
		return;
	}

	if(p_texBank == NULL)
	{
		// keep impossible
		PLEX_errorInt(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_IMPOSSIBLE, PLEX_ERRORMESS_TEXTURE_ONCLEAR, PLEX_ERRORMESS_TEXTURE_TEXTUREBANK, errorline, errorfile);
		return;
	}

	texBankCount = PLEX_expandArrayCountInt(p_texBank, errorline, errorfile);

	if(index >= texBankCount)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_TEXTURE_ONCLEAR,  PLEX_ERRORMESS_GENERIC_INDEX, errorline, errorfile);
		return;
	}

	target = PLEX_getExpandArrayEntryInt(index, p_texBank, errorline, errorfile);

	if(target == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_TEXTURE_ONCLEAR, PLEX_ERRORMESS_TEXTURE_TEXTUREBANK, errorline, errorfile);
		return;
	}

	if(target->cleared)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_BADOPERATION, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_TEXTURE_ONCLEAR, PLEX_ERRORMESS_OP_CLEARCLEAREDTEXTURE, errorline, errorfile);

		return;
	}

	target->cleared = true;
}

void PLEX_unclearTextureInt(const size_t index, const size_t errorline, const char* const errorfile)
{
	PLEX_TEXTURE* target = NULL;

	size_t texBankCount = 0;

	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_TEXTURE_ONUNCLEAR, errorline, errorfile);
		return;
	}

	if(p_texBank == NULL)
	{
		// keep impossible
		PLEX_errorInt(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_IMPOSSIBLE, PLEX_ERRORMESS_TEXTURE_ONUNCLEAR, PLEX_ERRORMESS_TEXTURE_TEXTUREBANK, errorline, errorfile);
		return;
	}

	texBankCount = PLEX_expandArrayCountInt(p_texBank, errorline, errorfile);

	if(index >= texBankCount)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_TEXTURE_ONUNCLEAR,  PLEX_ERRORMESS_GENERIC_INDEX, errorline, errorfile);
		return;
	}

	target = PLEX_getExpandArrayEntryInt(index, p_texBank, errorline, errorfile);

	if(target == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_TEXTURE_ONCLEAR, PLEX_ERRORMESS_TEXTURE_TEXTUREBANK, errorline, errorfile);
		return;
	}

	if(!target->cleared)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_BADOPERATION, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_TEXTURE_ONUNCLEAR, PLEX_ERRORMESS_OP_CLEARCLEAREDTEXTURE, errorline, errorfile);
		return;
	}

	p_genProcess(target, target->key.type, PLEX_fts(target->key.data.fileloc), target->key.data.w, target->key.data.h, target->key.data.tint, target->key.data.r, target->key.data.g, target->key.data.b, target->key.data.a, errorline, errorfile);

	target->cleared = false; // < must be at end of function
}

// start, update, end functions ---------------------------------------------------------------------------------------------

bool PLEX_startTexturesInt(const size_t errorline, const char* const errorfile)
{
	PLEX_TEXTURE* blankTexture = NULL;

	if(p_running)
	{
		PLEX_errorInt0A(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_DOUBLESTART, PLEX_ERROR_SEVERITY_BADSTYLE, errorline, errorfile);
		return true;
	}

	if(IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		SDL_QuitSubSystem(SDL_INIT_EVENTS);
		SDL_QuitSubSystem(SDL_INIT_VIDEO);
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_SDL, PLEX_ERROR_LOADEXTERNALMODULE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_SDLMODULE_IMAGE, errorline, errorfile);
		PLEX_errorSDLInt(PLEX_ERROR_SEVERITY_FATAL, errorline, errorfile);
		return false;
	}

	p_texBank = PLEX_genExpandArrayInt(PLEX_getMemProfileTexturePreload(), sizeof(PLEX_TEXTURE), errorline, errorfile);

	if(p_texBank == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_ALLOCFAIL, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_TEXTURE_ONSTART, PLEX_ERRORMESS_TEXTURE_TEXTUREBANK, errorline, errorfile);
		return false;
	}

	if(!PLEX_incrementExpandArrayInt(p_texBank, errorline, errorfile))
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_INCREMENT, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_TEXTURE_ONSTART, PLEX_ERRORMESS_TEXTURE_TEXTUREBANK, errorline, errorfile);
		return false;
	}

	blankTexture = PLEX_getExpandArrayLastInt(p_texBank, errorline, errorfile);

	*blankTexture = p_genBlankTexture();

	p_running = true;

	return true;
}

bool PLEX_updateTexturesInt(const size_t errorline, const char* const errorfile)
{
	if(!p_running)
	{
		PLEX_errorInt0A(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_UPDATEBEFORESTART, PLEX_ERROR_SEVERITY_BADSTYLE, errorline, errorfile);
		return false;
	}

	if(p_texBank == NULL)
	{
		// keep impossible
		PLEX_errorInt(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_IMPOSSIBLE, PLEX_ERRORMESS_TEXTURE_ONUPDATE, PLEX_ERRORMESS_TEXTURE_TEXTUREBANK, errorline, errorfile);
		return false;
	}

	return true;
}

void PLEX_endTexturesInt(const size_t errorline, const char* const errorfile)
{
	size_t texBankCount = 0;

	if(!p_running)
	{
		PLEX_errorInt0A(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_ENDBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, errorline, errorfile);
		return;
	}

	if(p_texBank == NULL)
	{
		// keep impossible
		PLEX_errorInt(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_IMPOSSIBLE, PLEX_ERRORMESS_TEXTURE_ONEND, PLEX_ERRORMESS_TEXTURE_TEXTUREBANK, errorline, errorfile);
		return;
	}

	texBankCount = PLEX_expandArrayCount(p_texBank);

	for(size_t ze = 1; ze < texBankCount; ++ze)
	{
		PLEX_TEXTURE* target = PLEX_getExpandArrayEntryInt(ze, p_texBank, errorline, errorfile);
		PLEX_LOW_TEXTURE lowTarg = PLEX_LOW_NOTEXTURE;

		if(target == NULL)
		{
			PLEX_errorInt(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_TEXTURE_ONEND, PLEX_ERRORMESS_TEXTURE_TEXTUREBANK, errorline, errorfile);
			return;
		}

		lowTarg = target->contents;

		if(!PLEX_low_isTextureNull(lowTarg)) PLEX_low_destroyTextureInt(&lowTarg, errorline, errorfile);
	}

	if(p_texBank != NULL)
	{
		PLEX_destroyExpandArrayInt(&p_texBank, errorline, errorfile);
	}else{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_FREENULL, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_TEXTURE_ONEND, PLEX_ERRORMESS_TEXTURE_TEXTUREBANK, errorline, errorfile);
	}

	IMG_Quit();

	p_running = false;
}

// setters ------------------------------------------------------------------------------------------------------------------

void PLEX_setTextureAlphaInt(const size_t index, const uint8_t a, const size_t errorline, const char* const errorfile)
{
	PLEX_LOW_TEXTURE lowTex = PLEX_LOW_NOTEXTURE;

	size_t texBankCount = 0;

	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_TEXTURE_ONSETALPHA, errorline, errorfile);
		return;
	}

	if(p_texBank == NULL)
	{
		// keep impossible
		PLEX_errorInt(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_IMPOSSIBLE, PLEX_ERRORMESS_TEXTURE_TEXTUREBANK, PLEX_ERRORMESS_TEXTURE_ONSETALPHA, errorline, errorfile);
		return;
	}

	texBankCount = PLEX_expandArrayCountInt(p_texBank, errorline, errorfile);

	if(index >= texBankCount)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_TEXTURE_ONSETALPHA,  PLEX_ERRORMESS_GENERIC_INDEX, errorline, errorfile);
		return;
	}

	lowTex = PLEX_innerTextureInt(index, errorline, errorfile);

	if(PLEX_low_isTextureNull(lowTex))
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_ISNULLTEXTURE, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_TEXTURE_ONSETALPHA, PLEX_ERRORMESS_TEXTURE_TEXTURE, errorline, errorfile);
		return;
	}

	PLEX_low_textureSetAlpha(&lowTex, a);
}

// getters ------------------------------------------------------------------------------------------------------------------

size_t PLEX_nullTexture()
{
	return 0;
}

bool PLEX_textureIsNullInt(const size_t index, const size_t errorline, const char* const errorfile)
{
	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_TEXTURE_ONNULLCHECK, errorline, errorfile);
		return true;
	}

	if(p_texBank == NULL)
	{
		// keep impossible
		PLEX_errorInt(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_IMPOSSIBLE, PLEX_ERRORMESS_TEXTURE_ONNULLCHECK, PLEX_ERRORMESS_TEXTURE_TEXTUREBANK, errorline, errorfile);
		return true;
	}

	return index == PLEX_nullTexture();
}

void PLEX_textureWHInt(const size_t index, uint32_t* w, uint32_t* h, const size_t errorline, const char* const errorfile)
{
	size_t texBankCount = 0;

	PLEX_TEXTURE* target = NULL;

	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_TEXTURE_ONGETWIDTHHEIGHT, errorline, errorfile);
		return;
	}

	if(p_texBank == NULL)
	{
		// keep impossible
		PLEX_errorInt(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_IMPOSSIBLE, PLEX_ERRORMESS_TEXTURE_ONGETWIDTHHEIGHT, PLEX_ERRORMESS_TEXTURE_TEXTUREBANK, errorline, errorfile);
		return;
	}

	texBankCount = PLEX_expandArrayCountInt(p_texBank, errorline, errorfile);

	if(index >= texBankCount)
	{
		*w = 0;
		*h = 0;
		PLEX_errorInt(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_TEXTURE_ONGETWIDTHHEIGHT,  PLEX_ERRORMESS_GENERIC_INDEX, errorline, errorfile);
		return;
	}

	if(!index)
	{
		*w = 0;
		*h = 0;
		return;
	}

	target = PLEX_getExpandArrayEntryInt(index, p_texBank, errorline, errorfile);

	if(target == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_TEXTURE_ONGETWIDTHHEIGHT, PLEX_ERRORMESS_TEXTURE_TEXTUREBANK, errorline, errorfile);
		return;
	}

	PLEX_low_textureWH(target->contents, w, h);
}

PLEX_LOW_TEXTURE PLEX_innerTextureInt(const size_t index, const size_t errorline, const char* const errorfile)
{
	size_t texBankCount = 0;

	PLEX_TEXTURE* target = NULL;

	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_TEXTURE_ONGETINNER, errorline, errorfile);
		return PLEX_LOW_NOTEXTURE;
	}

	if(p_texBank == NULL)
	{
		// keep impossible
		PLEX_errorInt(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_IMPOSSIBLE, PLEX_ERRORMESS_TEXTURE_ONGETINNER, PLEX_ERRORMESS_TEXTURE_TEXTUREBANK, errorline, errorfile);
		return PLEX_LOW_NOTEXTURE;
	}

	texBankCount = PLEX_expandArrayCountInt(p_texBank, errorline, errorfile);

	if(index >= texBankCount)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_TEXTURE_ONGETINNER,  PLEX_ERRORMESS_GENERIC_INDEX, errorline, errorfile);
		return PLEX_LOW_NOTEXTURE;
	}

	if(!index) return PLEX_LOW_NOTEXTURE;

	target = PLEX_getExpandArrayEntryInt(index, p_texBank, errorline, errorfile);

	if(target == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_TEXTURE_ONGETINNER, PLEX_ERRORMESS_TEXTURE_TEXTURE, errorline, errorfile);
		return PLEX_LOW_NOTEXTURE;
	}

	return target->contents;
}

bool PLEX_textureIsClearedInt(const size_t index, const size_t errorline, const char* const errorfile)
{
	size_t texBankCount = 0;

	PLEX_TEXTURE* target = NULL;

	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_TEXTURE_ONGETCLEAR, errorline, errorfile);
		return false;
	}

	if(p_texBank == NULL)
	{
		// keep impossible
		PLEX_errorInt(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_IMPOSSIBLE, PLEX_ERRORMESS_TEXTURE_ONGETCLEAR, PLEX_ERRORMESS_TEXTURE_TEXTUREBANK, errorline, errorfile);
		return false;
	}

	texBankCount = PLEX_expandArrayCountInt(p_texBank, errorline, errorfile);

	if(index >= texBankCount)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_TEXTURE_ONGETCLEAR,  PLEX_ERRORMESS_GENERIC_INDEX, errorline, errorfile);
		return false;
	}

	if(!index) return false;

	target = PLEX_getExpandArrayEntryInt(index, p_texBank, errorline, errorfile);

	if(target == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_TEXTURE, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_TEXTURE_ONGETCLEAR, PLEX_ERRORMESS_TEXTURE_TEXTUREBANK, errorline, errorfile);
		return false;
	}

	return target->cleared;
}
