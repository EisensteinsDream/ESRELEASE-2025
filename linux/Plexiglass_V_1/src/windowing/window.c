#include "windowing/window.h"

// NOTE: global function descriptions in header.

// static values ------------------------------------------------------------------------------------------------------------

static uint32_t p_widthMax = 0;

static double p_widthRatio = 0;
static double p_heightRatio = 0;
static double p_screenRatio = 0;

static uint32_t p_width = 0;
static uint32_t p_height = 0;
static uint32_t p_woffset = 0;
static uint32_t p_hoffset = 0;

static SDL_Window* p_window = NULL;

static double p_unit = 0;

static const char* p_title = NULL;

static bool p_sizing = false;

static bool p_running = false;

// static functions ---------------------------------------------------------------------------------------------------------

// readjusts window and unit values to the width, height, and ratio passed in

static void p_readjustWindow(const uint32_t width, const uint32_t height, const double ratio, const size_t errorline, const char* const errorfile)
{
	uint32_t screenUnitW = 0;
	uint32_t screenUnitH = 0;

	if(!ratio)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_WINDOW, PLEX_ERROR_ZEROVALUE, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_WINDOW_ONREADJUST, PLEX_ERRORMESS_WINDOW_WINDOWRATIO, errorline, errorfile);
		return;
	}

	if(!width)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_WINDOW, PLEX_ERROR_ZEROVALUE, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_WINDOW_ONREADJUST, PLEX_ERRORMESS_GENERIC_DIMENW, errorline, errorfile);
		return;
	}

	if(!height)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_WINDOW, PLEX_ERROR_ZEROVALUE, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_WINDOW_ONREADJUST, PLEX_ERRORMESS_GENERIC_DIMENH, errorline, errorfile);
		return;
	}

	p_widthMax = round(PLEX_HEIGHTUNITMAXBASE * ratio);

	p_widthRatio = PLEX_SCREENUNITBASE/(PLEX_SCREENRATIOBASE * ratio);
	p_heightRatio = PLEX_SCREENUNITBASE/PLEX_SCREENRATIOBASE;

	p_width = width;
	p_height = height;
	p_screenRatio = ratio;

	// screen units are 25x25 on a resolution 600 pixels tall

	if(width > height)
	{
		p_unit = height * p_heightRatio;

		screenUnitW = p_unit * p_widthMax;

		if(screenUnitW < p_width)
		{
			p_woffset = (p_width - screenUnitW)/2; // < size of border
			p_hoffset = 0;
		}else{
			p_unit = width * p_widthRatio;

			screenUnitH = p_unit * PLEX_HEIGHTUNITMAXBASE;

			p_woffset = 0;
			p_hoffset = (p_height - screenUnitH)/2; // < size of border
		}
	}else{
		p_unit = width * p_widthRatio;

		screenUnitH = p_unit * PLEX_HEIGHTUNITMAXBASE;

		if(screenUnitH < p_width)
		{
			p_woffset = 0;
			p_hoffset = (p_height - screenUnitH)/2; // < size of border
		}else{
			p_unit = height * p_heightRatio;

			screenUnitW = p_unit * p_widthMax;

			p_woffset = (p_width - screenUnitW)/2; // < size of border
			p_hoffset = 0;
		}
	}
}

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

// specialized functions ----------------------------------------------------------------------------------------------------

void PLEX_showErrorPopup(const char* const title, const char* const message) // < declared in error.h
{
	if(p_window == NULL) return;

	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title, message, p_window);
}

void PLEX_updateWindowResizeInt(const size_t errorline, const char* const errorfile)
{
	int width = 0;
	int height = 0;

	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_WINDOW, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_WINDOW_ONUPDATERESIZE, errorline, errorfile);
		return;
	}

	SDL_GetWindowSize(p_window, &width, &height);
	p_readjustWindow(width, height, p_screenRatio, errorline, errorfile);
}

void PLEX_restoreWindowInt(const size_t errorline, const char* const errorfile)
{
	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_WINDOW, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_WINDOW_ONRESTORE, errorline, errorfile);
		return;
	}

	SDL_RestoreWindow(p_window);
	PLEX_updateWindowResizeInt(errorline, errorfile);
}

// start, update, end functions ---------------------------------------------------------------------------------------------

bool PLEX_startWindowInt(const char* const title, const uint32_t width, const uint32_t height, const double ratio, const size_t errorline, const char* const errorfile)
{
	if(p_running)
	{
		PLEX_errorInt0A(PLEX_ERROR_CATEGORY_WINDOW, PLEX_ERROR_DOUBLESTART, PLEX_ERROR_SEVERITY_BADSTYLE, errorline, errorfile);
		return true;
	}

	if(SDL_InitSubSystem(SDL_INIT_VIDEO)) // remember 0 == success with this method
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SDL, PLEX_ERROR_LOADEXTERNALMODULE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_WINDOW_ONSTART, PLEX_ERRORMESS_SDLMODULE_VIDEO, errorline, errorfile);
		PLEX_errorSDLInt(PLEX_ERROR_SEVERITY_MINOR, errorline, errorfile); // < doesn't need to be fatal because the error above is
		return false;
	}

	PLEX_flagSDLError();

	#if (PLEX_CORE_OS == PLEX_CORE_WINDOWS)
		SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl"); // < direct3d messes up the resize
	#endif

	p_window = PLEX_low_createSDLWindow(title, width, height, PLEX_DEF_allowResize());

	if(p_window == NULL)
	{
		IMG_Quit();
		SDL_QuitSubSystem(SDL_INIT_EVENTS);
		SDL_QuitSubSystem(SDL_INIT_VIDEO);
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SDL, PLEX_ERROR_CREATE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_WINDOW_ONSTART, PLEX_ERRORMESS_WINDOW_WINDOW, errorline, errorfile);
		PLEX_errorSDLInt(PLEX_ERROR_SEVERITY_MINOR, errorline, errorfile); // < doesn't need to be fatal because the error above is
		return false;
	}

	SDL_SetWindowMinimumSize(p_window, PLEX_DEF_minWindowW(), PLEX_DEF_minWindowH());
	SDL_SetWindowMaximumSize(p_window, PLEX_DEF_maxWindowW(), PLEX_DEF_maxWindowH());

	if(PLEX_DEF_allowResize() && PLEX_DEF_allowMaximize() && PLEX_DEF_startMaximized())
	{
		SDL_MaximizeWindow(p_window);
		PLEX_updateWindowResize();
		PLEX_markSizingInt(errorline, errorfile);
	}

	p_readjustWindow(width, height, 1.3333333333, errorline, errorfile);

	p_title = title;
	p_sizing = false;
	p_running = true;

	return true;
}

bool PLEX_updateWindowInt(const size_t errorline, const char* const errorfile)
{
	if(!p_running)
	{
		PLEX_errorInt0A(PLEX_ERROR_CATEGORY_WINDOW, PLEX_ERROR_UPDATEBEFORESTART, PLEX_ERROR_SEVERITY_BADSTYLE, errorline, errorfile);
		return false;
	}

	if(p_window == NULL)
	{
		PLEX_errorInt0A(PLEX_ERROR_CATEGORY_SCREENEFFECTS, PLEX_ERROR_UPDATEBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, errorline, errorfile);
		return false;
	}

	return true;
}

void PLEX_endWindowInt(const size_t errorline, const char* const errorfile)
{
	if(!p_running)
	{
		PLEX_errorInt0A(PLEX_ERROR_CATEGORY_WINDOW, PLEX_ERROR_ENDBEFORESTART, PLEX_ERROR_SEVERITY_BADSTYLE, errorline, errorfile);
		return;
	}

	if(p_window != NULL)
	{
		PLEX_low_destroySDLWindowInt(p_window, errorline, errorfile);
	}else{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_WINDOW, PLEX_ERROR_FREENULL, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_WINDOW_ONENDING, PLEX_ERRORMESS_WINDOW_WINDOW, errorline, errorfile);
	}

	SDL_QuitSubSystem(SDL_INIT_VIDEO);

	PLEX_unflagSDLError();

	p_window = NULL;
	p_width = 0;
	p_height = 0;
	p_unit = 0;

	p_woffset = 0;

	p_running = false;
}

// setters ------------------------------------------------------------------------------------------------------------------

void PLEX_markSizingInt(const size_t errorline, const char* const errorfile)
{
	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_WINDOW, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_WINDOW_ONMARKSIZING, errorline, errorfile);
		return;
	}

	p_sizing = true;
}

void PLEX_unmarkSizingInt(const size_t errorline, const char* const errorfile)
{
	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_WINDOW, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_WINDOW_ONUNMARKSIZING, errorline, errorfile);
		return;
	}

	p_sizing = false;
}

void PLEX_changeScreenRatioInt(const double ratio, const size_t errorline, const char* const errorfile)
{
	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_WINDOW, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_WINDOW_ONCHANGESCREENRATIO, errorline, errorfile);
		return;
	}

	p_readjustWindow(p_width, p_height, ratio, errorline, errorfile);
}

void PLEX_setWindowTitleInt(const char* const title, const size_t errorline, const char* const errorfile)
{
	const char* aTitle = "";

	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_WINDOW, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_WINDOW_ONSETTITLE, errorline, errorfile);
		return;
	}

	if(p_window == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_WINDOW, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_WINDOW_ONSETTITLE, PLEX_ERRORMESS_WINDOW_WINDOW, errorline, errorfile);
		return;
	}

	if(title != NULL) aTitle = title;
	else aTitle = "";

	SDL_SetWindowTitle(p_window, aTitle);
}

// getters ------------------------------------------------------------------------------------------------------------------

double PLEX_ONEUNIT(){ return p_unit; }

double PLEX_UNITPIXEL(){ return p_unit ? 1/p_unit : 0; }

double PLEX_UNIT(const double count){ return count * p_unit; }

uint32_t PLEX_TRANS_W(const double perc)
{
	const uint32_t mw = PLEX_WW(true);
	const uint32_t ret = perc * mw;

	if(ret > mw) return mw;

	return ret;
}

uint32_t PLEX_TRANS_H(const double perc)
{
	const uint32_t mh = PLEX_WH(true);
	const uint32_t ret = perc * mh;

	if(ret > mh) return mh;

	return ret;
}

uint32_t PLEX_WW(const bool offset){ return p_width - (p_woffset * 2 * offset); }
uint32_t PLEX_WH(const bool offset){ return p_height - (p_hoffset * 2 * offset); }

uint32_t PLEX_WOFFSET(){ return p_woffset; }
uint32_t PLEX_HOFFSET(){ return p_hoffset; }

double PLEX_WOFFSETPERC(){ return p_woffset/(double)p_width; }
double PLEX_HOFFSETPERC(){ return p_hoffset/(double)p_height; }

double PLEX_WCROPPERC(){ return (p_width - p_woffset * 2)/(double)p_width; }
double PLEX_HCROPPERC(){ return (p_height - p_hoffset * 2)/(double)p_height; }

uint32_t PLEX_WIDTHUNITMAX(){ return p_widthMax; }
uint32_t PLEX_HEIGHTUNITMAX(){ return PLEX_HEIGHTUNITMAXBASE; }

bool PLEX_isSizing(){ return p_sizing; }

SDL_Window* PLEX_getWindowContents(){ return p_window; }

const char* PLEX_getWindowTitleInt(const size_t errorline, const char* const errorfile)
{
	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_WINDOW, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_WINDOW_ONGETTITLE, errorline, errorfile);
		return "";
	}

	if(p_window == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_WINDOW, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_WINDOW_ONGETTITLE, PLEX_ERRORMESS_WINDOW_WINDOW, errorline, errorfile);
		return "";
	}

	return SDL_GetWindowTitle(p_window);
}
