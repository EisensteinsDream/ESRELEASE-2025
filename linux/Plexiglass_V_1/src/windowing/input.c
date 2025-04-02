#include "windowing/input.h"

// NOTE: global function descriptions in header.

// static values ------------------------------------------------------------------------------------------------------------

static bool p_keyDown[PLEX_LIMIT_KEYCAP];
static bool p_keyPress[PLEX_LIMIT_KEYCAP];
static bool p_fkeyPress[PLEX_LIMIT_FKEYCAP];
static bool p_fkeyDown[PLEX_LIMIT_FKEYCAP];

static bool p_shift = false;
static bool p_lshift = false;
static bool p_rshift = false;
static bool p_ctrl = false;
static bool p_lctrl = false;
static bool p_rctrl = false;

static bool p_upKey = false;
static bool p_downKey = false;
static bool p_leftKey = false;
static bool p_rightKey = false;

static bool p_upKeyPress = false;
static bool p_downKeyPress = false;
static bool p_leftKeyPress = false;
static bool p_rightKeyPress = false;

static bool p_backspacePress = false;
static bool p_backspace = false;

static bool p_anyKeyPress = false;

static bool p_left = false;
static bool p_leftClick = false;
static bool p_right = false;
static bool p_rightClick = false;
static bool p_midButton = false;
static bool p_midButtonClick = false;

static bool p_mouseMove = false;

static bool p_disablePause = false;

static int64_t p_mx = 0;
static int64_t p_my = 0;

static double p_mouseScroll = 0;

static int16_t p_axis[PLEX_LIMIT_CONTROLLERS][SDL_CONTROLLER_AXIS_MAX];

static SDL_GameController* p_controller[PLEX_LIMIT_CONTROLLERS];
static size_t p_controllerCount = 0;

static size_t p_regularCursor = 0;
static size_t p_regularCursorClick = 0;
static size_t p_regularCursorDown = 0;

static size_t p_customCursor = 0;
static size_t p_customCursorClick = 0;
static size_t p_customCursorDown = 0;

static uint32_t p_cursorW = 0;
static uint32_t p_cursorH = 0;

static uint32_t p_cursorFX = 0;
static uint32_t p_cursorFY = 0;
static uint32_t p_cursorFW = 0;
static uint32_t p_cursorFH = 0;

static uint32_t p_cursorClickFX = 0;
static uint32_t p_cursorClickFY = 0;
static uint32_t p_cursorClickFW = 0;
static uint32_t p_cursorClickFH = 0;

static uint32_t p_cursorDownFX = 0;
static uint32_t p_cursorDownFY = 0;
static uint32_t p_cursorDownFW = 0;
static uint32_t p_cursorDownFH = 0;

static uint8_t p_cursorR = 0;
static uint8_t p_cursorG = 0;
static uint8_t p_cursorB = 0;

static uint32_t p_customCursorW = 0;
static uint32_t p_customCursorH = 0;

static uint32_t p_customCursorFX = 0;
static uint32_t p_customCursorFY = 0;
static uint32_t p_customCursorFW = 0;
static uint32_t p_customCursorFH = 0;

static uint32_t p_customCursorClickFX = 0;
static uint32_t p_customCursorClickFY = 0;
static uint32_t p_customCursorClickFW = 0;
static uint32_t p_customCursorClickFH = 0;

static uint32_t p_customCursorDownFX = 0;
static uint32_t p_customCursorDownFY = 0;
static uint32_t p_customCursorDownFW = 0;
static uint32_t p_customCursorDownFH = 0;

static uint8_t p_customCursorR = 0;
static uint8_t p_customCursorG = 0;
static uint8_t p_customCursorB = 0;

static bool p_hideCursor = false;

static bool p_controllerButtonDown[PLEX_LIMIT_CONTROLLERS][SDL_CONTROLLER_BUTTON_MAX];
static bool p_controllerButtonPress[PLEX_LIMIT_CONTROLLERS][SDL_CONTROLLER_BUTTON_MAX];

static bool p_running = false;

// static functions ---------------------------------------------------------------------------------------------------------

// polls the number of controllers read by SDL

static void p_pollController()
{
	p_controllerCount = 0;

	// do not give error for this
	if(PLEX_DEF_disableController()) return;

	for(size_t ze = 0; ze < SDL_NumJoysticks(); ++ze)
	{
		if(SDL_IsGameController(ze))
		{
			p_controller[ze] = SDL_GameControllerOpen(ze);
			++p_controllerCount;
		}
	}

	for(size_t ze = 0; ze < PLEX_LIMIT_CONTROLLERS; ++ze)
	{
		memset(p_controllerButtonDown + ze, false, SDL_CONTROLLER_BUTTON_MAX);
		memset(p_controllerButtonPress + ze, false, SDL_CONTROLLER_BUTTON_MAX);
	}
}

// looks at a set of utf8 symbols from 'start' to 'end' and returns a boolean from a 'target' buffer at a correlative position of 'start2'. This is a way to check the buffers that read input data from the keys in the update loop.

static void p_checkNextKey(const size_t nextKey, const uint64_t start, const uint64_t end, const size_t start2, const bool result, bool* target)
{
	for(uint64_t ze = start; ze <= end; ++ze)
	{
		const uint64_t it = ze - start;

		if(nextKey == ze)
		{
			target[start2 + it] = result;
			return;
		}
	}
}

// the same as checkNextKey except for function keys

static void p_checkFKey(const uint64_t nextKey, const bool result, bool* target)
{
	static const uint64_t f1Key = SDLK_F1;

	for(uint64_t ze = 0; ze < PLEX_LIMIT_FKEYCAP; ++ze)
	{
		if(nextKey == f1Key + ze)
		{
			target[ze] = result;
			return;
		}
	}
}

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

// specialized functions ----------------------------------------------------------------------------------------------------

void PLEX_clearMouseClicks()
{
	p_left = false;
	p_right = false;
	p_leftClick = false;
	p_rightClick = false;
	p_midButton = false;
	p_midButtonClick = false;
}

void PLEX_clearKeyInput()
{
	p_rshift = false;
	p_lshift = false;
	p_shift = false;

	p_rctrl = false;
	p_lctrl = false;
	p_ctrl = false;

	p_upKey = false;
	p_leftKey = false;
	p_downKey = false;
	p_rightKey = false;

	p_upKeyPress = false;
	p_leftKeyPress = false;
	p_downKeyPress = false;
	p_rightKeyPress = false;

	p_anyKeyPress = false;

	memset(p_fkeyDown, false, PLEX_LIMIT_FKEYCAP);
	memset(p_fkeyPress, false, PLEX_LIMIT_FKEYCAP);
	memset(p_keyDown, false, PLEX_LIMIT_KEYCAP);
	memset(p_keyPress, false, PLEX_LIMIT_KEYCAP);
}

bool PLEX_mouseInside(const int64_t x, const int64_t y, const uint32_t w, const uint32_t h, const bool offset)
{
	PLEX_POINT mousePoint;

	PLEX_RECT region;

	if(PLEX_DEF_disableMouse()) return false;

	mousePoint = PLEX_convPoint(p_mx, p_my);

	region = PLEX_convRect(PLEX_convPoint(x + (offset * PLEX_WOFFSET()), y + (offset * PLEX_HOFFSET())), PLEX_convDimens(w, h));

	return PLEX_insideRect(mousePoint, region);
}

// start, update, end functions ---------------------------------------------------------------------------------------------

bool PLEX_startInputInt(const size_t errorline, const char* const errorfile)
{
	if(p_running)
	{
		PLEX_errorInt0A(PLEX_ERROR_CATEGORY_INPUT, PLEX_ERROR_DOUBLESTART, PLEX_ERROR_SEVERITY_BADSTYLE, errorline, errorfile);
		return true;
	}

	if(SDL_InitSubSystem(SDL_INIT_EVENTS)) // remember 0 == success with this method
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SDL, PLEX_ERROR_LOADEXTERNALMODULE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_INPUT_ONSTART, PLEX_ERRORMESS_SDLMODULE_INPUT, errorline, errorfile);
		PLEX_errorSDLInt(PLEX_ERROR_SEVERITY_MINOR, errorline, errorfile);
		return false;
	}

	if(SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER))
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_SDL, PLEX_ERROR_LOADEXTERNALMODULE, PLEX_ERROR_SEVERITY_MAJOR, PLEX_ERRORMESS_INPUT_ONSTART, PLEX_ERRORMESS_SDLMODULE_CONTROLLER, errorline, errorfile);
		PLEX_errorSDLInt(PLEX_ERROR_SEVERITY_MINOR, errorline, errorfile);
	}

	p_disablePause = false;

	memset(p_fkeyDown, false, PLEX_LIMIT_FKEYCAP);
	memset(p_keyDown, false, PLEX_LIMIT_KEYCAP);

	p_upKey = false;
	p_rightKey = false;
	p_downKey = false;
	p_leftKey = false;

	p_pollController();

	if(!PLEX_DEF_disableMouse())
	{
		const double w = PLEX_UNIT(PLEX_DEF_cursorW());
		const double h = PLEX_UNIT(PLEX_DEF_cursorH());

		uint32_t tw = 0;
		uint32_t th = 0;

		p_regularCursor = PLEX_loadTextureFromFileInt(64, 64, 255, 255, 255, 255, 0, PLEX_RECDIRECTORY "plex/cursor.png", errorline, errorfile);

		if(!p_regularCursor)
		{
			PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ISNULLTEXTURE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_GRAPHICS_ONGRAPHICSSTART, PLEX_ERRORMESS_WINDOW_CURSORGRAPHIC, errorline, errorfile);
			return false;
		}

		PLEX_textureWHInt(p_regularCursor, &tw, &th, errorline, errorfile);

		PLEX_cursorFCoorInt(tw, th, errorline, errorfile);

		p_regularCursorClick = PLEX_loadTextureFromFileInt(64, 64, 255, 255, 255, 255, 0, PLEX_RECDIRECTORY "plex/cursorclick.png", errorline, errorfile);

		if(!p_regularCursorClick)
		{
			PLEX_destroyTextureInt(p_regularCursor, errorline, errorfile);

			p_regularCursor = 0;

			PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ISNULLTEXTURE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_GRAPHICS_ONGRAPHICSSTART, PLEX_ERRORMESS_WINDOW_CURSORGRAPHICCLICK, errorline, errorfile);
			return false;
		}

		PLEX_textureWHInt(p_regularCursorClick, &tw, &th, errorline, errorfile);

		PLEX_cursorFCoorClickInt(tw, th, errorline, errorfile);

		p_regularCursorDown = PLEX_loadTextureFromFileInt(64, 64, 255, 255, 255, 255, 0, PLEX_RECDIRECTORY "plex/cursordown.png", errorline, errorfile);

		if(!p_regularCursorDown)
		{
			PLEX_destroyTextureInt(p_regularCursor, errorline, errorfile);
			PLEX_destroyTextureInt(p_regularCursorClick, errorline, errorfile);

			p_regularCursor = 0;
			p_regularCursorClick = 0;

			PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ISNULLTEXTURE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_GRAPHICS_ONGRAPHICSSTART, PLEX_ERRORMESS_WINDOW_CURSORGRAPHICDOWN, errorline, errorfile);
			return false;
		}

		PLEX_textureWHInt(p_regularCursorDown, &tw, &th, errorline, errorfile);

		PLEX_cursorFCoorDownInt(tw, th, errorline, errorfile);

		PLEX_cursorWHInt(w, h, errorline, errorfile);
	}

	p_customCursor = 0;
	p_customCursorClick = 0;
	p_customCursorDown = 0;

	p_cursorR = PLEX_DEF_cursorR();
	p_cursorG = PLEX_DEF_cursorG();
	p_cursorB = PLEX_DEF_cursorB();

	p_hideCursor = false;

	#ifndef PLEX_DEBUGMOUSEMODE
		SDL_ShowCursor(SDL_DISABLE);
	#endif

	p_running = true;

	return true;
}

bool PLEX_updateInputInt(const size_t errorline, const char* const errorfile)
{
	const bool keyDisable = PLEX_DEF_disableKeyboard() && ((!PLEX_DEF_disableController() && p_controllerCount) || !PLEX_DEF_disableMouse());

	int mx = 0;
	int my = 0;

	double amx = 0;
	double amy = 0;
	double amw = 0;
	double amh = 0;

	double mpw = 0;
	double mph = 0;

	SDL_Event ev;

	Uint32 nextKey = 0;

	bool pauseToggle = false;

	if(!p_running)
	{
		PLEX_errorInt0A(PLEX_ERROR_CATEGORY_INPUT, PLEX_ERROR_UPDATEBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, errorline, errorfile);
		return false;
	}

	if(!p_controllerCount) p_pollController();

	SDL_GetMouseState(&mx, &my);

	amx = (double)mx - PLEX_WOFFSET();
	amy = (double)my - PLEX_HOFFSET();

	amw = PLEX_WW(true);
	amh = PLEX_WH(true);

	mpw = amx/amw;
	mph = amy/amh;

	p_mx = mpw * PLEX_WW(false);
	p_my = mph * PLEX_WH(false);

	memset(p_keyPress, false, PLEX_LIMIT_KEYCAP);
	memset(p_fkeyPress, false, PLEX_LIMIT_FKEYCAP);

	p_keyDown['\n'] = false;

	for(size_t ze = 0; ze < PLEX_LIMIT_CONTROLLERS; ++ze) memset(p_controllerButtonPress + ze, false, SDL_CONTROLLER_BUTTON_MAX);

	p_shift = false;
	p_ctrl = false;

	p_upKeyPress = false;
	p_downKeyPress = false;
	p_leftKeyPress = false;
	p_rightKeyPress = false;

	p_backspacePress = false;

	p_leftClick = false;
	p_rightClick = false;

	p_mouseMove = false;

	p_anyKeyPress = false;

	p_mouseScroll = 0;

	SDL_PumpEvents();

	PLEX_unmarkSizing(); // < keep before polling

	while(SDL_PollEvent(&ev))
	{
		switch(ev.type)
		{
			case SDL_WINDOWEVENT:
				if(PLEX_DEF_killOnClose() && ev.window.event == SDL_WINDOWEVENT_CLOSE) PLEX_askQuit();

				if(ev.window.event == SDL_WINDOWEVENT_RESIZED)
				{
					PLEX_updateWindowResize();
					PLEX_markSizing();
				}

				if(!PLEX_DEF_allowMaximize() && ev.window.event == SDL_WINDOWEVENT_MAXIMIZED)
				{
					PLEX_restoreWindow();
					PLEX_markSizing();
				}
			break;

			case SDL_KEYDOWN:
				nextKey = ev.key.keysym.sym;

				if(PLEX_DEF_killOnEscape() && nextKey == SDLK_ESCAPE) PLEX_askQuit();

				if(!keyDisable)
				{
					if(nextKey == SDLK_SPACE)
					{
						if(p_disablePause) p_keyPress[' '] = true;
						else pauseToggle = true;
					}

					if(nextKey == SDLK_RSHIFT) p_rshift = true;
					if(nextKey == SDLK_LSHIFT) p_lshift = true;
					if(nextKey == SDLK_RCTRL) p_rctrl = true;
					if(nextKey == SDLK_LCTRL) p_lctrl = true;

					p_checkNextKey(nextKey, SDLK_0, SDLK_9, '0', true, p_keyPress);
					p_checkNextKey(nextKey, SDLK_a, SDLK_z, 'a', true, p_keyPress);

					p_checkNextKey(nextKey, SDLK_0, SDLK_9, '0', true, p_keyDown);
					p_checkNextKey(nextKey, SDLK_a, SDLK_z, 'a', true, p_keyDown);

					p_checkFKey(nextKey, true, p_fkeyPress);
					p_checkFKey(nextKey, true, p_fkeyDown);

					if(nextKey == SDLK_PERIOD)
					{
						p_keyPress['.'] = true;
						p_keyDown['.'] = true;
					}

					if(nextKey == SDLK_COMMA)
					{
						p_keyPress[','] = true;
						p_keyDown[','] = true;
					}

					if(nextKey == SDLK_RETURN || nextKey == SDLK_KP_ENTER)
					{
						p_keyPress['\n'] = true;
						p_keyDown['\n'] = true;
					}

					if(nextKey == SDLK_LEFT){ p_leftKey  = true; p_leftKeyPress = true; }
					if(nextKey == SDLK_RIGHT){ p_rightKey = true; p_rightKeyPress = true; }
					if(nextKey == SDLK_UP){ p_upKey = true; p_upKeyPress = true; }
					if(nextKey == SDLK_DOWN){ p_downKey = true; p_downKeyPress = true; }

					if(nextKey == SDLK_BACKSPACE){ p_backspace = true; p_backspacePress = true; }
				}

				p_anyKeyPress = true;
			break;

			case SDL_KEYUP:
				nextKey = ev.key.keysym.sym;

				if(!keyDisable)
				{
					if(nextKey == SDLK_SPACE && p_disablePause) p_keyDown[' '] = false;

					p_checkNextKey(nextKey, SDLK_0, SDLK_9, '0', false, p_keyDown);
					p_checkNextKey(nextKey, SDLK_a, SDLK_z, 'a', false, p_keyDown);

					p_checkFKey(nextKey, false, p_fkeyDown);

					if(nextKey == SDLK_RSHIFT) p_rshift = false;
					if(nextKey == SDLK_LSHIFT) p_lshift = false;

					if(nextKey == SDLK_LEFT) p_leftKey = false;
					if(nextKey == SDLK_RIGHT) p_rightKey = false;
					if(nextKey == SDLK_UP) p_upKey = false;
					if(nextKey == SDLK_DOWN) p_downKey = false;

					if(nextKey == SDLK_COMMA) p_keyDown[','] = false;
					if(nextKey == SDLK_PERIOD) p_keyDown['.'] = false;

					if(nextKey == SDLK_RETURN || nextKey == SDLK_KP_ENTER) p_keyDown['\n'] = false;

					if(nextKey == SDLK_BACKSPACE) p_backspace = false;
				}
			break;

			case SDL_MOUSEBUTTONDOWN:
				if(ev.button.button == SDL_BUTTON_LEFT) p_left = true;
				if(ev.button.button == SDL_BUTTON_RIGHT) p_right = true;
				if(ev.button.button == SDL_BUTTON_MIDDLE) p_midButton = true;
			break;

			case SDL_MOUSEBUTTONUP:
				if(ev.button.button == SDL_BUTTON_LEFT)
				{
					p_left = false;
					p_leftClick = true;
				}

				if(ev.button.button == SDL_BUTTON_RIGHT)
				{
					p_right = false;
					p_rightClick = true;
				}

				if(ev.button.button == SDL_BUTTON_MIDDLE)
				{
					p_midButton = false;
					p_midButtonClick = true;
				}
			break;

			case SDL_MOUSEWHEEL:
				p_mouseScroll = ev.wheel.preciseY;
			break;

			case SDL_MOUSEMOTION:
				p_mouseMove = true;
			break;

			case SDL_CONTROLLERBUTTONDOWN:
				if(ev.cbutton.which < p_controllerCount)
				{
					p_controllerButtonDown[ev.cbutton.which][ev.cbutton.button] = true;
					p_controllerButtonPress[ev.cbutton.which][ev.cbutton.button] = true;
				}
			break;

			case SDL_CONTROLLERBUTTONUP:
				if(ev.cbutton.which < p_controllerCount)
				{
					if(PLEX_DEF_controllerPause() && ev.cbutton.button == SDL_CONTROLLER_BUTTON_START) pauseToggle = true;
					else p_controllerButtonDown[ev.cbutton.which][ev.cbutton.button] = false;
				}
			break;

			case SDL_CONTROLLERAXISMOTION:
				p_axis[ev.caxis.which][ev.caxis.axis] = ev.caxis.value;
			break;
		};
	};

	if(pauseToggle)
	{
		if(PLEX_getGameTimePausedInt(errorline, errorfile)) PLEX_unpauseGameTimeInt(errorline, errorfile);
		else PLEX_pauseGameTimeInt(errorline, errorfile);
	}

	p_shift = p_rshift || p_lshift;
	p_ctrl = p_rctrl || p_lctrl;

	return true;
}

void PLEX_endInputInt(const size_t errorline, const char* const errorfile)
{
	if(!p_running)
	{
		PLEX_errorInt0A(PLEX_ERROR_CATEGORY_INPUT, PLEX_ERROR_ENDBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, errorline, errorfile);
		return;
	}

	PLEX_destroyTextureInt(p_regularCursor, errorline, errorfile);
	PLEX_destroyTextureInt(p_regularCursorClick, errorline, errorfile);
	PLEX_destroyTextureInt(p_regularCursorDown, errorline, errorfile);

	for(size_t ze = 0; ze < p_controllerCount; ++ze)
	{
		if(SDL_IsGameController(ze)) SDL_GameControllerClose(p_controller[ze]);
	}

	p_regularCursor = 0;
	p_regularCursorClick = 0;
	p_regularCursorDown = 0;

	p_controllerCount = 0;

	SDL_QuitSubSystem(SDL_INIT_EVENTS);

	p_running = false;
}

// setters ------------------------------------------------------------------------------------------------------------------

void PLEX_setCustomCursorInt(const size_t tex, const int64_t w, const int64_t h, const int64_t fx, const int64_t fy, const int64_t fw, const int64_t fh, const int64_t fxc, const int64_t fyc, const int64_t fwc, const int64_t fhc, const int64_t fxd, const int64_t fyd, const int64_t fwd, const int64_t fhd, const size_t errorline, const char* const errorfile)
{
	if(!p_running)
	{
		PLEX_errorInt1A(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ACTIONBEFORESTART, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_GRAPHICS_ONSETCUSTOMCURSOR, errorline, errorfile);
		return;
	}

	if(!tex)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ISNULLTEXTURE, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_GRAPHICS_ONSETCUSTOMCURSOR, PLEX_ERRORMESS_INPUT_CURSORTEX, errorline, errorfile);
		return;
	}

	PLEX_setCustomCursorTintedInt(tex, w, h, fx, fy, fw, fh, fxc, fyc, fwc, fhc, fxd, fyd, fwd, fhd, 255, 255, 255, errorline, errorfile);
}

void PLEX_setCustomCursorTintedInt(const size_t tex, const int64_t w, const int64_t h, const int64_t fx, const int64_t fy, const int64_t fw, const int64_t fh, const int64_t fxc, const int64_t fyc, const int64_t fwc, const int64_t fhc, const int64_t fxd, const int64_t fyd, const int64_t fwd, const int64_t fhd, const uint8_t r, const uint8_t g, const uint8_t b, const size_t errorline, const char* const errorfile)
{
	// doesn't need to be running

	if(!tex)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ISNULLTEXTURE, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_GRAPHICS_ONSETCUSTOMCURSORTINTED, PLEX_ERRORMESS_INPUT_CURSORTEX, errorline, errorfile);
		return;
	}

	p_customCursor = tex;
	p_customCursorClick = tex;
	p_customCursorDown = tex;

	p_customCursorR = r;
	p_customCursorG = g;
	p_customCursorB = b;

	p_customCursorW = w;
	p_customCursorH = h;

	p_customCursorFX = fx;
	p_customCursorFY = fy;
	p_customCursorFW = fw;
	p_customCursorFH = fh;

	p_customCursorClickFX = fxc;
	p_customCursorClickFY = fyc;
	p_customCursorClickFW = fwc;
	p_customCursorClickFH = fhc;

	p_customCursorDownFX = fxd;
	p_customCursorDownFY = fyd;
	p_customCursorDownFW = fwd;
	p_customCursorDownFH = fhd;
}

void PLEX_setCustomCursorClickInt(const size_t tex, const int64_t fx, const int64_t fy, const int64_t fw, const int64_t fh, const size_t errorline, const char* const errorfile)
{
	// doesn't need to be running

	if(!p_customCursor)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ISNULLTEXTURE, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_GRAPHICS_ONSETCUSTOMCURSORCLICK, PLEX_ERRORMESS_INPUT_CUSTOMCURSOR, errorline, errorfile);
		return;
	}

	p_customCursorClick = tex;

	p_customCursorClickFX = fx;
	p_customCursorClickFY = fy;
	p_customCursorClickFW = fw;
	p_customCursorClickFH = fh;
}

void PLEX_setCustomCursorDownInt(const size_t tex, const int64_t fx, const int64_t fy, const int64_t fw, const int64_t fh, const size_t errorline, const char* const errorfile)
{
	// doesn't need to be running

	if(!p_customCursor)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ZEROVALUE, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_GRAPHICS_ONSETCUSTOMCURSORDOWN, PLEX_ERRORMESS_INPUT_CUSTOMCURSOR, errorline, errorfile);
		return;
	}

	p_customCursorDown = tex;

	p_customCursorDownFX = fx;
	p_customCursorDownFY = fy;
	p_customCursorDownFW = fw;
	p_customCursorDownFH = fh;
}

void PLEX_unsetCustomCursor()
{
	p_customCursor = 0;
	p_customCursorClick = 0;
	p_customCursorDown = 0;

	p_customCursorFX = 0;
	p_customCursorFY = 0;
	p_customCursorFW = 0;
	p_customCursorFH = 0;

	p_customCursorClickFX = 0;
	p_customCursorClickFY = 0;
	p_customCursorClickFW = 0;
	p_customCursorClickFH = 0;

	p_customCursorDownFX = 0;
	p_customCursorDownFY = 0;
	p_customCursorDownFW = 0;
	p_customCursorDownFH = 0;
}

void PLEX_cursorWHInt(const uint32_t w, const uint32_t h, const size_t errorline, const char* const errorfile)
{
	// doesn't need to be running

	if(!w)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ZEROVALUE, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GRAPHICS_ONLOADCURSORWH, PLEX_ERRORMESS_GENERIC_WIDTH, errorline, errorfile);
		return;
	}

	if(!h)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ZEROVALUE, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GRAPHICS_ONLOADCURSORWH, PLEX_ERRORMESS_GENERIC_HEIGHT, errorline, errorfile);
		return;
	}

	p_cursorW = w;
	p_cursorH = h;
}

void PLEX_cursorFCoorInt(const uint32_t w, const uint32_t h, const size_t errorline, const char* const errorfile)
{
	// doesn't need to be running

	if(!w)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ZEROVALUE, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GRAPHICS_ONLOADCURSORFCOORDINATES, PLEX_ERRORMESS_GENERIC_WIDTH, errorline, errorfile);
		return;
	}

	if(!h)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ZEROVALUE, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GRAPHICS_ONLOADCURSORFCOORDINATES, PLEX_ERRORMESS_GENERIC_HEIGHT, errorline, errorfile);
		return;
	}

	p_cursorFW = w;
	p_cursorFH = h;
}

void PLEX_cursorFCoorClickInt(const uint32_t w, const uint32_t h, const size_t errorline, const char* const errorfile)
{
	// doesn't need to be running

	if(!w)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ZEROVALUE, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GRAPHICS_ONLOADCURSORCLICKFCOORDINATES, PLEX_ERRORMESS_GENERIC_WIDTH, errorline, errorfile);
		return;
	}

	if(!h)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ZEROVALUE, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GRAPHICS_ONLOADCURSORCLICKFCOORDINATES, PLEX_ERRORMESS_GENERIC_HEIGHT, errorline, errorfile);
		return;
	}

	p_cursorClickFW = w;
	p_cursorClickFH = h;
}

void PLEX_cursorFCoorDownInt(const uint32_t w, const uint32_t h, const size_t errorline, const char* const errorfile)
{
	// doesn't need to be running

	if(!w)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ZEROVALUE, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GRAPHICS_ONLOADCURSORDOWNFCOORDINATES, PLEX_ERRORMESS_GENERIC_WIDTH, errorline, errorfile);
		return;
	}

	if(!h)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ZEROVALUE, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GRAPHICS_ONLOADCURSORDOWNFCOORDINATES, PLEX_ERRORMESS_GENERIC_HEIGHT, errorline, errorfile);
		return;
	}

	p_cursorDownFW = w;
	p_cursorDownFH = h;
}

void PLEX_disablePause(){ p_disablePause = true; }
void PLEX_enablePause(){ p_disablePause = false; }

void PLEX_hideCursor(){ p_hideCursor = true; }
void PLEX_unhideCursor(){ p_hideCursor = false; }
void PLEX_toggleHideCursor(){ p_hideCursor = !p_hideCursor; }

// getters ------------------------------------------------------------------------------------------------------------------

void PLEX_cursorDimensInt(uint32_t* w, uint32_t* h, uint32_t* fx, uint32_t* fy, uint32_t* fw, uint32_t* fh, const size_t errorline, const char* const errorfile)
{
	if(!w)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ZEROVALUE, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GRAPHICS_ONGETCURSORDIMENSIONS, PLEX_ERRORMESS_GENERIC_WIDTH, errorline, errorfile);
		return;
	}

	if(!h)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ZEROVALUE, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GRAPHICS_ONGETCURSORDIMENSIONS, PLEX_ERRORMESS_GENERIC_HEIGHT, errorline, errorfile);
		return;
	}

	if(!fx)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ZEROVALUE, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GRAPHICS_ONGETCURSORDIMENSIONS, PLEX_ERRORMESS_GRAPHICS_FROMX, errorline, errorfile);
		return;
	}

	if(!fy)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ZEROVALUE, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GRAPHICS_ONGETCURSORDIMENSIONS, PLEX_ERRORMESS_GRAPHICS_FROMY, errorline, errorfile);
		return;
	}

	if(!fw)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ZEROVALUE, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GRAPHICS_ONGETCURSORDIMENSIONS, PLEX_ERRORMESS_GRAPHICS_FROMW, errorline, errorfile);
		return;
	}

	if(!fh)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GRAPHICS, PLEX_ERROR_ZEROVALUE, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GRAPHICS_ONGETCURSORDIMENSIONS, PLEX_ERRORMESS_GRAPHICS_FROMH, errorline, errorfile);
		return;
	}

	if(!PLEX_usingCustomCursor())
	{
		*w = p_cursorW;
		*h = p_cursorH;

		if(PLEX_leftClick())
		{
			*fx = p_cursorClickFX;
			*fy = p_cursorClickFY;
			*fw = p_cursorClickFW;
			*fh = p_cursorClickFH;
			return;
		}

		if(PLEX_left())
		{
			*fx = p_cursorDownFX;
			*fy = p_cursorDownFY;
			*fw = p_cursorDownFW;
			*fh = p_cursorDownFH;
			return;
		}

		*fx = p_cursorFX;
		*fy = p_cursorFY;
		*fw = p_cursorFW;
		*fh = p_cursorFH;
		return;
	}else{
		*w = p_customCursorW;
		*h = p_customCursorH;

		if(PLEX_leftClick())
		{
			*fx = p_customCursorClickFX;
			*fy = p_customCursorClickFY;
			*fw = p_customCursorClickFW;
			*fh = p_customCursorClickFH;
			return;
		}

		if(PLEX_left())
		{
			*fx = p_customCursorDownFX;
			*fy = p_customCursorDownFY;
			*fw = p_customCursorDownFW;
			*fh = p_customCursorDownFH;
			return;
		}

		*fx = p_customCursorFX;
		*fy = p_customCursorFY;
		*fw = p_customCursorFW;
		*fh = p_customCursorFH;
	}
}

uint8_t PLEX_cursorR(){ return p_cursorR; }
uint8_t PLEX_cursorG(){ return p_cursorG; }
uint8_t PLEX_cursorB(){ return p_cursorB; }

uint8_t PLEX_customCursorR(){ return p_customCursorR; }
uint8_t PLEX_customCursorG(){ return p_customCursorG; }
uint8_t PLEX_customCursorB(){ return p_customCursorB; }

bool PLEX_cursorIsHidden(){ return p_hideCursor; }

bool PLEX_usingCustomCursor(){ return p_customCursor; }

size_t PLEX_customCursor()
{
	if(PLEX_leftClick()) return p_customCursorClick;
	if(PLEX_left()) return p_customCursorDown;

	return p_customCursor;
}

size_t PLEX_regularCursor(){ return p_regularCursor; }
size_t PLEX_regularCursorClick(){ return p_regularCursorClick; }
size_t PLEX_regularCursorDown(){ return p_regularCursorDown; }

bool PLEX_pauseDisabled(){ return p_disablePause; }

bool PLEX_KEY_rshift(){ return p_rshift; }
bool PLEX_KEY_lshift(){ return p_lshift; }
bool PLEX_KEY_shift(){ return p_shift; }

bool PLEX_KEY_rctrl(){ return p_rctrl; }
bool PLEX_KEY_lctrl(){ return p_lctrl; }
bool PLEX_KEY_ctrl(){ return p_ctrl; }

bool PLEX_KEY_down(const uint8_t key){ return p_keyDown[key]; }
bool PLEX_KEY_press(const uint8_t key){ return p_keyPress[key]; }

bool PLEX_KEY_fdown(const size_t number){ if(!number || number >= PLEX_LIMIT_FKEYCAP) return false; return p_fkeyDown[number - 1]; }
bool PLEX_KEY_fpress(const size_t number){ if(!number || number >= PLEX_LIMIT_FKEYCAP) return false; return p_fkeyPress[number - 1]; }

bool PLEX_backspace(){ return p_backspace; }
bool PLEX_backspacePress(){ return p_backspacePress; }

bool PLEX_upKey(){ return p_upKey; }
bool PLEX_leftKey(){ return p_leftKey; }
bool PLEX_downKey(){ return p_downKey; }
bool PLEX_rightKey(){ return p_rightKey; }

bool PLEX_upKeyPress(){ return p_upKeyPress; }
bool PLEX_leftKeyPress(){ return p_leftKeyPress; }
bool PLEX_downKeyPress(){ return p_downKeyPress; }
bool PLEX_rightKeyPress(){ return p_rightKeyPress; }

bool PLEX_KEY_anyPress(){ return p_anyKeyPress; }

bool PLEX_KEY_anyKey()
{
	if(p_rshift) return true;
	if(p_lshift) return true;
	if(p_shift) return true;

	if(p_rctrl) return true;
	if(p_lctrl) return true;
	if(p_ctrl) return true;

	if(p_upKey) return true;
	if(p_leftKey) return true;
	if(p_downKey) return true;
	if(p_rightKey) return true;

	if(p_upKeyPress) return true;
	if(p_leftKeyPress) return true;
	if(p_downKeyPress) return true;
	if(p_rightKeyPress) return true;

	if(p_anyKeyPress) return true;

	for(size_t ze = 0; ze < PLEX_LIMIT_FKEYCAP; ++ze)
	{
		if(p_fkeyDown[ze] || p_fkeyPress[ze]) return true;
	}

	for(size_t ze = 0; ze < PLEX_LIMIT_KEYCAP; ++ze)
	{
		if(p_keyDown[ze] || p_keyPress[ze]) return true;
	}

	return false;
}

int64_t PLEX_MX()
{
	if(PLEX_DEF_disableMouse()) return 0;

	return p_mx;
}

int64_t PLEX_MY()
{
	if(PLEX_DEF_disableMouse()) return 0;

	return p_my;
}

bool PLEX_left(){ if(PLEX_DEF_disableMouse()) return false; return p_left; }
bool PLEX_leftClick(){ if(PLEX_DEF_disableMouse()) return false; return p_leftClick; }

bool PLEX_right(){ if(PLEX_DEF_disableMouse()) return false; return p_right; }
bool PLEX_rightClick(){ if(PLEX_DEF_disableMouse()) return false; return p_rightClick; }

bool PLEX_midButton(){ if(PLEX_DEF_disableMouse()) return false; return p_midButton; }
bool PLEX_midButtonClick(){ if(PLEX_DEF_disableMouse()) return false; return p_midButtonClick; }

bool PLEX_mouseMoved(){ if(PLEX_DEF_disableMouse()) return false; return p_mouseMove; }

double PLEX_mouseScroll(){ if(PLEX_DEF_disableMouse()) return 0; return p_mouseScroll; }

bool PLEX_CONTROLLER_downInt(const size_t controller, const uint8_t button, const size_t errorline, const char* const errorfile)
{
	if(controller >= PLEX_LIMIT_CONTROLLERS)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_INPUT, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_INPUT_ONUPDATE, PLEX_ERRORMESS_INPUT_CONTROLLER, errorline, errorfile);
		return false;
	}

	if(button >= SDL_CONTROLLER_BUTTON_MAX)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_INPUT, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_INPUT_ONUPDATE, PLEX_ERRORMESS_INPUT_CONTROLLERBUTTON, errorline, errorfile);
		return false;
	}

	if(PLEX_DEF_disableController())
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_INPUT, PLEX_ERROR_DISABLED, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_INPUT_ONUPDATE, PLEX_ERRORMESS_INPUT_CONTROLLER, errorline, errorfile);
		return false;
	}

	return p_controllerButtonDown[controller][button];
}

bool PLEX_CONTROLLER_pressInt(const size_t controller, const uint8_t button, const size_t errorline, const char* const errorfile)
{
	if(controller >= PLEX_LIMIT_CONTROLLERS)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_INPUT, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_INPUT_ONCONTROLLERPRESS, PLEX_ERRORMESS_INPUT_CONTROLLER, errorline, errorfile);
		return false;
	}

	if(button >= SDL_CONTROLLER_BUTTON_MAX)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_INPUT, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_INPUT_ONCONTROLLERPRESS, PLEX_ERRORMESS_INPUT_CONTROLLERBUTTON, errorline, errorfile);
		return false;
	}

	if(PLEX_DEF_disableController())
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_INPUT, PLEX_ERROR_DISABLED, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_INPUT_ONCONTROLLERPRESS, PLEX_ERRORMESS_INPUT_CONTROLLER, errorline, errorfile);
		return false;
	}

	return p_controllerButtonPress[controller][button];
}

bool PLEX_CONTROLLER_axisInt(const size_t controller, const size_t axisNum, const double sensitivity, const size_t errorline, const char* const errorfile)
{
	if(controller >= p_controllerCount)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_INPUT, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_INPUT_ONCONTROLLERAXIS, PLEX_ERRORMESS_INPUT_CONTROLLERCOUNT, errorline, errorfile);
		return 0;
	}

	if(axisNum >= SDL_CONTROLLER_AXIS_MAX)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_INPUT, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_INPUT_ONCONTROLLERAXIS, PLEX_ERRORMESS_INPUT_AXISVALUE, errorline, errorfile);
		return 0;
	}

	if(PLEX_DEF_disableController())
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_INPUT, PLEX_ERROR_DISABLED, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_INPUT_ONCONTROLLERAXIS, PLEX_ERRORMESS_INPUT_CONTROLLER, errorline, errorfile);
		return 0;
	}

	return sensitivity < 0 ? p_axis[controller][axisNum] < sensitivity : p_axis[controller][axisNum] > sensitivity;
}

bool PLEX_CONTROLLER_axisUpInt(const size_t controller, const size_t errorline, const char* const errorfile)
{
	if(controller >= p_controllerCount)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_INPUT, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_INPUT_ONCONTROLLERAXISUP, PLEX_ERRORMESS_INPUT_CONTROLLERCOUNT, errorline, errorfile);
		return 0;
	}

	if(PLEX_DEF_disableController())
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_INPUT, PLEX_ERROR_DISABLED, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_INPUT_ONCONTROLLERAXISUP, PLEX_ERRORMESS_INPUT_CONTROLLER, errorline, errorfile);
		return 0;
	}

	return PLEX_CONTROLLER_axisUp2Int(controller, PLEX_STANDNUM_CONTROLLERSENSE, errorline, errorfile);
}

bool PLEX_CONTROLLER_axisRightInt(const size_t controller, const size_t errorline, const char* const errorfile)
{
	if(controller >= p_controllerCount)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_INPUT, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_INPUT_ONCONTROLLERAXISRIGHT, PLEX_ERRORMESS_INPUT_CONTROLLERCOUNT, errorline, errorfile);
		return 0;
	}

	if(PLEX_DEF_disableController())
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_INPUT, PLEX_ERROR_DISABLED, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_INPUT_ONCONTROLLERAXISRIGHT, PLEX_ERRORMESS_INPUT_CONTROLLER, errorline, errorfile);
		return 0;
	}

	return PLEX_CONTROLLER_axisRight2Int(controller, PLEX_STANDNUM_CONTROLLERSENSE, errorline, errorfile);
}

bool PLEX_CONTROLLER_axisDownInt(const size_t controller, const size_t errorline, const char* const errorfile)
{
	if(controller >= p_controllerCount)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_INPUT, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_INPUT_ONCONTROLLERAXISDOWN, PLEX_ERRORMESS_INPUT_CONTROLLERCOUNT, errorline, errorfile);
		return 0;
	}

	if(PLEX_DEF_disableController())
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_INPUT, PLEX_ERROR_DISABLED, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_INPUT_ONCONTROLLERAXISDOWN, PLEX_ERRORMESS_INPUT_CONTROLLER, errorline, errorfile);
		return 0;
	}

	return PLEX_CONTROLLER_axisDown2Int(controller, PLEX_STANDNUM_CONTROLLERSENSE, errorline, errorfile);
}

bool PLEX_CONTROLLER_axisLeftInt(const size_t controller, const size_t errorline, const char* const errorfile)
{
	if(controller >= p_controllerCount)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_INPUT, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_INPUT_ONCONTROLLERAXISLEFT, PLEX_ERRORMESS_INPUT_CONTROLLERCOUNT, errorline, errorfile);
		return 0;
	}

	if(PLEX_DEF_disableController())
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_INPUT, PLEX_ERROR_DISABLED, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_INPUT_ONCONTROLLERAXISLEFT, PLEX_ERRORMESS_INPUT_CONTROLLER, errorline, errorfile);
		return 0;
	}

	return PLEX_CONTROLLER_axisLeft2Int(controller, PLEX_STANDNUM_CONTROLLERSENSE, errorline, errorfile);
}

bool PLEX_CONTROLLER_axisUp2Int(const size_t controller, const double sensitivity, const size_t errorline, const char* const errorfile)
{
	if(controller >= p_controllerCount)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_INPUT, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_INPUT_ONCONTROLLERAXISUP, PLEX_ERRORMESS_INPUT_CONTROLLERCOUNT, errorline, errorfile);
		return 0;
	}

	if(PLEX_DEF_disableController())
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_INPUT, PLEX_ERROR_DISABLED, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_INPUT_ONCONTROLLERAXISUP, PLEX_ERRORMESS_INPUT_CONTROLLER, errorline, errorfile);
		return 0;
	}

	return PLEX_CONTROLLER_axisInt(controller, 1, 0 - sensitivity, errorline, errorfile);
}

bool PLEX_CONTROLLER_axisRight2Int(const size_t controller, const double sensitivity, const size_t errorline, const char* const errorfile)
{
	if(controller >= p_controllerCount)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_INPUT, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_INPUT_ONCONTROLLERAXISRIGHT, PLEX_ERRORMESS_INPUT_CONTROLLERCOUNT, errorline, errorfile);
		return 0;
	}

	if(PLEX_DEF_disableController())
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_INPUT, PLEX_ERROR_DISABLED, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_INPUT_ONCONTROLLERAXISRIGHT, PLEX_ERRORMESS_INPUT_CONTROLLER, errorline, errorfile);
		return 0;
	}

	return PLEX_CONTROLLER_axisInt(controller, 0, sensitivity, errorline, errorfile);
}

bool PLEX_CONTROLLER_axisDown2Int(const size_t controller, const double sensitivity, const size_t errorline, const char* const errorfile)
{
	if(controller >= p_controllerCount)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_INPUT, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_INPUT_ONCONTROLLERAXISDOWN, PLEX_ERRORMESS_INPUT_CONTROLLERCOUNT, errorline, errorfile);
		return 0;
	}

	if(PLEX_DEF_disableController())
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_INPUT, PLEX_ERROR_DISABLED, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_INPUT_ONCONTROLLERAXISDOWN, PLEX_ERRORMESS_INPUT_CONTROLLER, errorline, errorfile);
		return 0;
	}

	return PLEX_CONTROLLER_axisInt(controller, 1, sensitivity, errorline, errorfile);
}

bool PLEX_CONTROLLER_axisLeft2Int(const size_t controller, const double sensitivity, const size_t errorline, const char* const errorfile)
{
	if(controller >= p_controllerCount)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_INPUT, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_INPUT_ONCONTROLLERAXISLEFT, PLEX_ERRORMESS_INPUT_CONTROLLERCOUNT, errorline, errorfile);
		return 0;
	}

	if(PLEX_DEF_disableController())
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_INPUT, PLEX_ERROR_DISABLED, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_INPUT_ONCONTROLLERAXISLEFT, PLEX_ERRORMESS_INPUT_CONTROLLER, errorline, errorfile);
		return 0;
	}

	return PLEX_CONTROLLER_axisInt(controller, 0, 0 - sensitivity, errorline, errorfile);
}

size_t PLEX_CONTROLLER_countInt(const size_t errorline, const char* const errorfile)
{
	if(PLEX_DEF_disableController())
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_INPUT, PLEX_ERROR_DISABLED, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_INPUT_ONCONTROLLERCOUNT, PLEX_ERRORMESS_INPUT_CONTROLLER, errorline, errorfile);
		return 0;
	}

	return p_controllerCount;
}
