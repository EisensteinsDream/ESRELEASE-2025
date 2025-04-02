#include "minigame/minigame2/minigame2.h"

static size_t p_arrows = 0;

static uint32_t p_cursorD = 0;

static size_t p_menuBack = 0;
static size_t p_menuFront = 0;

static size_t p_leftBorder = 0;
static size_t p_rightBorder = 0;

static size_t p_pauseBanner = 0;

static size_t p_townSquareCalmIcon = 0;
static size_t p_saloonCalmIcon = 0;
static size_t p_jailCalmIcon = 0;
static size_t p_mayorsOfficeCalmIcon = 0;
static size_t p_armoryCalmIcon = 0;
static size_t p_townMedicCalmIcon = 0;

static size_t p_selectCursor = 0;
static size_t p_selectCursorShoot = 0;

static size_t p_areaNameBack = 0;
static size_t p_areaFront = 0;

static size_t p_shotIcon = 0;

static PLEX_RECT p_pamIconSpace;

static size_t p_gunScroll = 0;
static size_t p_showGunCount = 0;

static size_t p_selectGun = 0;
static size_t p_selectGunSlot = 0;
static size_t p_selectGunIndex[MMS2_GUNSCROLLUNIT];

static PLEX_RECT p_shotArea, p_innerShotArea;

static bool p_usingGunCursor = false;

// draws menu (aspects that are non-specific to whether it is a town or the field)

static void p_drawMenu()
{
	PLEX_printTexture(MMS2_DRAWLAYER_MENUBACK, p_menuBack, 0, 0, 1024, 128, 0, PLEX_WH(true) - PLEX_UNIT(4), PLEX_WW(true), PLEX_UNIT(4), true);
	PLEX_printTexture(MMS2_DRAWLAYER_MENUFRONT, p_menuFront, 0, 0, 1024, 640, 0, PLEX_WH(true) - PLEX_UNIT(4), PLEX_WW(true), PLEX_UNIT(4), true);
}

// draws borders to keep the 4:3 aspect ratio

void p_checkDrawBorders()
{
	if(PLEX_WOFFSET())
	{
		PLEX_printTexture(MMS2_DRAWLAYER_BORDER, p_leftBorder, 0, 0, 800, 1644, 0, 0, PLEX_WOFFSET(), PLEX_WH(false), false);
		PLEX_printTexture(MMS2_DRAWLAYER_BORDER, p_rightBorder, 0, 0, 800, 1644, PLEX_WW(false) -  PLEX_WOFFSET(), 0, PLEX_WOFFSET(), PLEX_WH(false), false);
	}
}

// factors in a 'calm'

static bool p_factorCalmIcon(const uint32_t ix, const uint32_t iy, const uint32_t id, const uint32_t lh, const char* const label, const size_t fontPlate, const size_t tex, const size_t it)
{
	const uint32_t ix2 = MMS2_menuIx(id, ix, it);

	MMS2_printMenuItem(ix2, iy, id, tex);

	return MMS2_factorMenuItem(ix2, iy, id, lh, label, fontPlate);
}

// draws the area front border

static void p_drawAreaFront()
{
	PLEX_printTexture(MMS2_DRAWLAYER_AREAGUI, p_areaFront, 0, 0, 1024, 128, 0, 0, PLEX_WW(true), PLEX_WH(true), true);
}

// draws the player health bar

static void p_drawHealthBar()
{
	PLEX_drawChargeBar(MMS2_DRAWLAYER_AREAGUI, MMS2_health(), PLEX_UNIT(13), PLEX_UNIT(0.75), PLEX_WW(true) - PLEX_UNIT(13.5), PLEX_UNIT(2), 255, 255, 255, 255, 100, 0, 0, 255, PLEX_UNIT(0.05), false, true);
}

// draws the current room name

static void p_drawRoomName(const size_t fontPlate)
{
	PLEX_FAKESTRING_25 roomName = MMS2_currentRoomName();

	PLEX_drawLabel(MMS2_DRAWLAYER_AREAGUI, PLEX_fts(roomName), PLEX_STANDNUM_FW, PLEX_STANDNUM_FH, 255, 255, 255, 255, PLEX_UNIT(0.5), PLEX_UNIT(0.75), PLEX_UNIT(12), PLEX_UNIT(2), 0.05, 0.05, 0.9, 0.9, PLEX_UNIT(0.05), PLEX_LANGUAGE_ALPHASTRING, fontPlate, p_areaNameBack, 0, 0, 256, 64, true);
}

// draws a label that shows how much cash the player has

static void p_drawCashBox(const size_t fontPlate)
{
	PLEX_FAKESTRING_25 cashString = PLEX_mergeString25(PLEX_createString25(MMS2_LANGUAGE_CASHSTRING_START), PLEX_createStringFromNumber25(MMS2_cash()));

	PLEX_drawLabel(MMS2_DRAWLAYER_AREAGUI, PLEX_fts(cashString), PLEX_STANDNUM_FW, PLEX_STANDNUM_FH, 0, 100, 0, 255, PLEX_UNIT(0.5), PLEX_UNIT(3.25), PLEX_UNIT(8), PLEX_UNIT(1.5), 0.1, 0.15, 0.8, 0.8, PLEX_UNIT(0.05), PLEX_LANGUAGE_ALPHASTRING, fontPlate, p_areaNameBack, 0, 0, 256, 64, true);
}

// draws a label that shows how many points the player has

static void p_drawPointBox(const size_t fontPlate)
{
	PLEX_FAKESTRING_25 pointString = PLEX_mergeString25(PLEX_createString25(MMS2_LANGUAGE_POINT_START), PLEX_createStringFromNumber25(MMS2_points()));

	PLEX_drawLabel(MMS2_DRAWLAYER_AREAGUI, PLEX_fts(pointString), PLEX_STANDNUM_FW, PLEX_STANDNUM_FH, 100, 100, 0, 255, PLEX_WW(true) - PLEX_UNIT(8.5), PLEX_UNIT(3.25), PLEX_UNIT(8), PLEX_UNIT(1.5), 0.1, 0.05, 0.8, 0.9, PLEX_UNIT(0.05), PLEX_LANGUAGE_ALPHASTRING, fontPlate, p_areaNameBack, 0, 0, 256, 64, true);
}

// draws the entire area

static void p_drawArea(const size_t fontPlate)
{
	p_drawAreaFront();

	if(!MMS2_currentRoomCalm()) p_drawHealthBar();

	p_drawRoomName(fontPlate);
	p_drawCashBox(fontPlate);
	p_drawPointBox(fontPlate);
}

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

void MMS2_setSystemGUI()
{

}

void MMS2_initSystemGUI()
{
	if(!p_arrows) p_arrows = PLEX_loadTextureFromFileOrHeaderless(768, 128, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_GUIARROWS, MMS2_FILEPATH_HEADERLESS_GUIARROWS);

	if(!p_menuBack) p_menuBack = PLEX_loadTextureFromFileOrHeaderless(1024, 128, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_GUIMENUBACK, MMS2_FILEPATH_HEADERLESS_GUIMENUBACK);
	if(!p_menuFront) p_menuFront = PLEX_loadTextureFromFileOrHeaderless(1024, 128, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_GUIMENUFRONT, MMS2_FILEPATH_HEADERLESS_GUIMENUFRONT);

	if(!p_leftBorder) p_leftBorder = PLEX_loadTextureFromFileOrHeaderless(800, 1644, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_LEFTBORDER, MMS2_FILEPATH_HEADERLESS_LEFTBORDER);
	if(!p_rightBorder) p_rightBorder = PLEX_loadTextureFromFileOrHeaderless(800, 1644, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_RIGHTBORDER, MMS2_FILEPATH_HEADERLESS_RIGHTBORDER);

	if(!p_pauseBanner) p_pauseBanner = PLEX_loadTextureFromFileOrHeaderless(1600, 400, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_PAUSE, MMS2_FILEPATH_HEADERLESS_PAUSE);

	if(!p_townSquareCalmIcon) p_townSquareCalmIcon = PLEX_loadTextureFromFileOrHeaderless(256, 256, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_TOWNSQUARECALMICONS, MMS2_FILEPATH_HEADERLESS_TOWNSQUARECALMICONS);
	if(!p_saloonCalmIcon) p_saloonCalmIcon = PLEX_loadTextureFromFileOrHeaderless(256, 256, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_SALOONCALMICONS, MMS2_FILEPATH_HEADERLESS_SALOONCALMICONS);
	if(!p_jailCalmIcon) p_jailCalmIcon = PLEX_loadTextureFromFileOrHeaderless(256, 256, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_JAILCALMICONS, MMS2_FILEPATH_HEADERLESS_JAILCALMICONS);
	if(!p_mayorsOfficeCalmIcon) p_mayorsOfficeCalmIcon = PLEX_loadTextureFromFileOrHeaderless(256, 256, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_MAYORSOFFICECALMICONS, MMS2_FILEPATH_HEADERLESS_MAYORSOFFICECALMICONS);
	if(!p_armoryCalmIcon) p_armoryCalmIcon = PLEX_loadTextureFromFileOrHeaderless(256, 256, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_ARMORYCALMICONS, MMS2_FILEPATH_HEADERLESS_ARMORYCALMICONS);
	if(!p_townMedicCalmIcon) p_townMedicCalmIcon = PLEX_loadTextureFromFileOrHeaderless(256, 256, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_DOCSHOUSECALMICONS, MMS2_FILEPATH_HEADERLESS_DOCSHOUSECALMICONS);

	if(!p_selectCursor) p_selectCursor = PLEX_loadTextureFromFileOrHeaderless(64, 64, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_SELECTCURSOR, MMS2_FILEPATH_HEADERLESS_SELECTCURSOR);
	if(!p_selectCursorShoot) p_selectCursorShoot = PLEX_loadTextureFromFileOrHeaderless(64, 64, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_SELECTCURSOR2, MMS2_FILEPATH_HEADERLESS_SELECTCURSOR2);

	if(!p_areaNameBack) p_areaNameBack = PLEX_loadTextureFromFileOrHeaderless(256, 64, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_AREANAMEBACK, MMS2_FILEPATH_HEADERLESS_AREANAMEBACK);
	if(!p_areaFront) p_areaFront = PLEX_loadTextureFromFileOrHeaderless(1024, 768, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_AREAFRONT, MMS2_FILEPATH_HEADERLESS_AREAFRONT);

	p_cursorD = PLEX_UNIT(1.5);

	p_selectGun = 0;
	p_selectGunSlot = 0;
	p_showGunCount = 0;

	p_usingGunCursor = false;
}

bool MMS2_checkRunSystemGUIA(const size_t fontPlate, bool* success, const uint64_t time)
{
	if(MMS_MMS3Unlocked() && MM_COMMON_skipButton(fontPlate))
	{
		if(MMS2_penultimateCutIsPlaying()) PLEX_endSpriteTheater();

		*success = true;
		return false;
	}

	return true;
}

void MMS2_checkRunSystemGUIB(const size_t chapter2SpriteTex, const size_t chapter2SpriteTex2, const size_t fontPlate, const uint64_t time)
{
	if(PLEX_KEY_fpress(1))
	{
		MMS2_restoreTown();
		MMS2_pointCheckTown(chapter2SpriteTex, chapter2SpriteTex2, time);
		return;
	}

	p_drawMenu();
	p_drawArea(fontPlate);
	p_checkDrawBorders();

	if(!MMS2_currentRoomCalm())
	{
		MMS2_setPamalenaIconSpace(PLEX_convRect(PLEX_convPoint(PLEX_UNIT(0.25), PLEX_WH(true) - PLEX_UNIT(8.25)), PLEX_convDimens(PLEX_UNIT(3), PLEX_UNIT(4))));
	}

	if(PLEX_getGameTimePaused()) PLEX_printTexture(0, p_pauseBanner, 0, 0, 1600, 400, 0, PLEX_WH(false)/2 - PLEX_WW(false)/8, PLEX_WW(false), PLEX_WW(false)/4, false);

	if(MMS2_isNotMoving())
	{
		if(!MMS2_currentRoomCalm())
		{
			const PLEX_RECT pamIconSpace = MMS2_getPamaleanaIconSpace();

			PLEX_fillRect(99, pamIconSpace.origin.x - PLEX_UNIT(0.25), pamIconSpace.origin.y - PLEX_UNIT(0.25), pamIconSpace.dimens.w + PLEX_UNIT(0.5), pamIconSpace.dimens.h + PLEX_UNIT(0.5), 50, 50, 0, 127, true);

			if(MMS2_getPlayerShotTime())
			{
				const double adjust = MMS2_isDodgePhase(MMS_MINIGAME2DODGEPHASE_CROUCHLEFT) || MMS2_isDodgePhase(MMS_MINIGAME2DODGEPHASE_CROUCHRIGHT) || MMS2_isDodgePhase(MMS_MINIGAME2DODGEPHASE_CROUCHLEFT) ? 7 : 6;

				PLEX_printTexture(98, chapter2SpriteTex, 64 * adjust, 576, 64, 64, pamIconSpace.origin.x, pamIconSpace.origin.y, pamIconSpace.dimens.w, pamIconSpace.dimens.h, true);
			}else{
				PLEX_printTexture(98, chapter2SpriteTex, 64 * MMS2_dodgePhaseAsNumber(), 576, 64, 64, pamIconSpace.origin.x, pamIconSpace.origin.y, pamIconSpace.dimens.w, pamIconSpace.dimens.h, true);
			}

			PLEX_drawRect(MMS2_DRAWLAYER_GUI, pamIconSpace.origin.x - PLEX_UNIT(0.25), pamIconSpace.origin.y - PLEX_UNIT(0.25), pamIconSpace.dimens.w + PLEX_UNIT(0.5), pamIconSpace.dimens.h + PLEX_UNIT(0.5), 255, 255, 255, 255, PLEX_UNIT(0.1), true);
		}
	}

	if(!MMS2_beginFinalBossIntro() && !MMS2_beginFinalBossOutro() && !MMS2_currentRoomCalm()) MMS2_runUncalmMenu(fontPlate, time);

	if(MMS2_playerIsShooting(time))
	{
		const PLEX_RECT shotArea = MMS2_shotArea();
		const PLEX_RECT innerShotArea = MMS2_innerShotArea();

		PLEX_printTexture(MMS2_DRAWLAYER_SHOTICON, MMS2_shotIcon(), 0, 0, 1024, 128, innerShotArea.origin.x, innerShotArea.origin.y, innerShotArea.dimens.w, innerShotArea.dimens.h, true);

		PLEX_drawSprite(MMS2_DRAWLAYER_SHOTICONBACK, 0, shotArea.origin.x, shotArea.origin.y, shotArea.dimens.w, shotArea.dimens.h, MMS2_selectedGun()->shotAnimation, true, time);
	}else{
		if(MMS2_isNotMoving())
		{
			MMS_MINIGAME2GUN* selectedGun = MMS2_selectedGun();

			if(!MMS2_currentRoomCalm())
			{
				if(PLEX_MY() < PLEX_WH(true) - PLEX_UNIT(4))
				{
					PLEX_unsetCustomCursor();
					PLEX_setCustomCursor(selectedGun->cursor, p_cursorD, p_cursorD, 0, 0, 64, 64, 0, 0, 64, 64, 0, 0, 64, 64);

					if(selectedGun->ammoMaximum != -1 && !MMS2_isReloading(time) && !selectedGun->ammoAmount && selectedGun->ammoClip > 0)
					{
						selectedGun->ammoAmount = selectedGun->ammoMaximum;
						--selectedGun->ammoClip;
						MM_COMMON_playSoundEffect(MM_COMMON_SOUNDEFFECT_RELOAD);
						selectedGun->reloadTime = time;
					}

					if(PLEX_left() && !MMS2_isReloading(time) && !MMS2_getPlayerShotTime() && !MMS2_beginFinalBossIntro() && !MMS2_beginFinalBossOutro())
					{
						bool shoot = true;

						if(selectedGun->ammoMaximum != -1)
						{
							if(!selectedGun->ammoAmount)
							{
								shoot = false;
								MMS2_setEmptyChamberSE(selectedGun->outOfAmmoSoundEffect);
							}else --selectedGun->ammoAmount;
						}

						if(shoot)
						{
							const int64_t cx = PLEX_MX() - PLEX_WOFFSET();
							const int64_t cy = PLEX_MY() - PLEX_HOFFSET();

							const int64_t od = p_cursorD * 2;

							MMS2_setShotTime(time);
							MMS2_setShotDuration(selectedGun->shootTime);
							MMS2_setShotIcon(selectedGun->shotCursor);

							MMS2_setShotArea(PLEX_convRect(PLEX_convPoint(cx - od/4, cy - od/4), PLEX_convDimens(od, od)));

							MMS2_setInnerShotArea(PLEX_convRect(PLEX_convPoint(cx, cy), PLEX_convDimens(p_cursorD, p_cursorD)));

							PLEX_hideCursor();
							PLEX_unsetCustomCursor();

							MM_COMMON_playSoundEffect(selectedGun->soundEffect);

							PLEX_startSprite(time, selectedGun->shotAnimation);
						}
					}
				}else{
					if(PLEX_MX() > PLEX_UNIT(6) + PLEX_WOFFSET())
					{
						MMS2_setCustomCursorSelect();
					}else MMS2_unsetCustomCursor();
				}
			}

			p_showGunCount = 0;

			for(size_t ze = p_gunScroll; ze < MMS2_GUNCOUNT; ++ze)
			{
				if(!MMS2_hasGun(ze)) continue;

				p_selectGunIndex[p_showGunCount] = ze;
				++p_showGunCount;

				if(p_showGunCount >= MMS2_GUNSCROLLUNIT) break;
			}
		}
	}
}

void MMS2_endSystemGUI()
{
	PLEX_destroyTexture(p_arrows);

	PLEX_destroyTexture(p_menuBack);
	PLEX_destroyTexture(p_menuFront);

	PLEX_destroyTexture(p_leftBorder);
	PLEX_destroyTexture(p_rightBorder);

	PLEX_destroyTexture(p_pauseBanner);

	PLEX_destroyTexture(p_townSquareCalmIcon);
	PLEX_destroyTexture(p_saloonCalmIcon);
	PLEX_destroyTexture(p_jailCalmIcon);
	PLEX_destroyTexture(p_mayorsOfficeCalmIcon);
	PLEX_destroyTexture(p_armoryCalmIcon);
	PLEX_destroyTexture(p_townMedicCalmIcon);

	PLEX_destroyTexture(p_selectCursor);
	PLEX_destroyTexture(p_selectCursorShoot);

	PLEX_destroyTexture(p_areaNameBack);
	PLEX_destroyTexture(p_areaFront);

	p_arrows = 0;
	p_menuBack = 0;
	p_menuFront = 0;

	p_leftBorder = 0;
	p_rightBorder = 0;

	p_pauseBanner = 0;

	p_townSquareCalmIcon = 0;
	p_saloonCalmIcon = 0;
	p_jailCalmIcon = 0;
	p_mayorsOfficeCalmIcon = 0;
	p_armoryCalmIcon = 0;
	p_townMedicCalmIcon = 0;

	p_selectCursor = 0;
	p_selectCursorShoot = 0;

	p_areaNameBack = 0;
	p_areaFront = 0;
}

uint32_t MMS2_menuIx(const uint32_t id, const uint32_t ix, const size_t it)
{
	return ix + (id * it);
}

void MMS2_startMenu(uint32_t* id, uint32_t* ix, uint32_t* iy, uint32_t* lh)
{
	const uint32_t lid = PLEX_UNIT(4);

	const uint32_t lix = PLEX_UNIT(7);
	const uint32_t liy = PLEX_WH(true) - PLEX_UNIT(4);

	const size_t llh = PLEX_UNIT(1);

	*id = lid;
	*ix = lix;
	*iy = liy;

	*lh = llh;
}

bool MMS2_drawArrow(const uint32_t fx, const uint32_t fy, const uint32_t fw, const uint32_t fh, const uint32_t x, const uint32_t y, const uint8_t direc, const uint64_t time)
{
	const uint8_t over = PLEX_mouseInside(x, y, PLEX_UNIT(2), PLEX_UNIT(2), true);
	const uint8_t click = over && PLEX_leftClick();

	const size_t moveDirec = MMS2_moveDirec();

	uint64_t adjust = 0;

	uint8_t isDirec = 0;

	uint8_t r, g, b;

	bool calmDirec = false;

	if(MMS2_mayorCutaway()) return false;

	if(!MMS2_pathOpen(direc)) return false;

	calmDirec = MMS2_pathCalm(direc);

	if(MMS2_isMoving() && direc != moveDirec) return false;

	if(click && MMS2_isNotMoving()) MMS2_startMoving(direc, time);

	isDirec = moveDirec == direc;

	adjust = over * 192 + isDirec * 192 + (isDirec && !over) * 192;

	if(!over)
	{
		if(calmDirec)
		{
			r = 100;
			g = 255;
			b = 255;
		}else{
			r = 100;
			g = 100;
			b = 100;
		}
	}else{
		if(calmDirec)
		{
			r = 100;
			g = 100;
			b = 255;
		}else{
			r = 255;
			g = 255;
			b = 100;
		}
	}

	PLEX_printTextureTinted(50, p_arrows, fx + adjust, fy, fw, fh, x, y, PLEX_UNIT(2), PLEX_UNIT(2), r, g, b, true);

	return click;
}

void MMS2_bloodSplatter(const uint64_t time)
{
	PLEX_RECT bloodSplatterRange;

	bloodSplatterRange.origin.x = PLEX_MX() - PLEX_UNIT(2);
	bloodSplatterRange.origin.y = PLEX_MY() - PLEX_UNIT(2);
	bloodSplatterRange.dimens.w = PLEX_UNIT(4);
	bloodSplatterRange.dimens.h = PLEX_UNIT(4);

	PLEX_doScreenEffectRanged(PLEX_SCREENEFFECT_SPLATTER, 100, 0, 0, 50, false, false, MMS2_SHOTDURATION, 0.1, bloodSplatterRange, time);
}

bool MMS2_factorMenuItem(const uint32_t ix2, const uint32_t iy, const uint32_t id, const uint32_t lh, const char* const label, const size_t fontPlate)
{
	if(PLEX_mouseInside(ix2, iy, id, id, true))
	{
		PLEX_drawLabel(MMS2_DRAWLAYER_GUI, label, PLEX_STANDNUM_FW, PLEX_STANDNUM_FH, 255, 255, 255, 255, ix2, iy - lh, id, lh, 0.05, 0.05, 0.9, 0.9, PLEX_UNIT(0.05), PLEX_LANGUAGE_ALPHASTRING, fontPlate, 0, 0, 0, 0, 0, true);

		if(PLEX_leftClick()) return true;
	}

	return false;
}

void MMS2_printMenuItem(const uint32_t ix2, const uint32_t iy, const uint32_t id, const size_t tex)
{
	PLEX_printTexture(2, tex, 0, 0, 256, 256, ix2, iy, id, id, true);
}

void MMS2_runCalmMenu(const size_t fontPlate, const uint64_t time)
{
	uint32_t id = 0;

	uint32_t ix = 0;
	uint32_t iy = 0;

	uint32_t lh = 0;

	MMS2_startMenu(&id, &ix, &iy, &lh);

	if(p_factorCalmIcon(ix, iy, id, lh, MMS2_LANGUAGE_TOWNICON_TOWNSQUARE, fontPlate, p_townSquareCalmIcon, 0)) MMS2_setTownArea(0);
	if(p_factorCalmIcon(ix, iy, id, lh, MMS2_LANGUAGE_TOWNICON_SALOON, fontPlate, p_saloonCalmIcon, 1)) MMS2_setTownArea(1);
	if(p_factorCalmIcon(ix, iy, id, lh, MMS2_LANGUAGE_TOWNICON_JAIL, fontPlate, p_jailCalmIcon, 2)) MMS2_setTownArea(2);
	if(p_factorCalmIcon(ix, iy, id, lh, MMS2_LANGUAGE_TOWNICON_MAYOR, fontPlate, p_mayorsOfficeCalmIcon, 3)) MMS2_setTownArea(3);
	if(p_factorCalmIcon(ix, iy, id, lh, MMS2_LANGUAGE_TOWNICON_ARMORY, fontPlate, p_armoryCalmIcon, 4)) MMS2_setTownArea(4);
	if(p_factorCalmIcon(ix, iy, id, lh, MMS2_LANGUAGE_TOWNICON_MEDIC, fontPlate, p_townMedicCalmIcon, 5)) MMS2_setTownArea(5);

	if(PLEX_KEY_press('l')) MMS2_goNextTownArea();
	else{ if(PLEX_KEY_press('j')) MMS2_goLastTownArea(); }

	PLEX_drawRect(MMS2_DRAWLAYER_GUI, ix + (id * MMS2_townArea()), iy, id, id, 255, 255, 0, 255, PLEX_UNIT(0.2), true);
}

void MMS2_runUncalmMenu(const size_t fontPlate, const uint64_t time)
{
	const size_t gunScrollEnd = MMS2_gunScroll() + 6;

	uint32_t id = PLEX_UNIT(4);

	uint32_t ix = PLEX_UNIT(7);
	uint32_t iy = PLEX_WH(true) - PLEX_UNIT(4);

	uint32_t ix2 = 0;

	uint32_t lh = 0;

	if(MMS2_isReloading(time))
	{
		PLEX_drawLabel(MMS2_DRAWLAYER_GUI, MMS2_LANGUAGE_RELOADING, PLEX_STANDNUM_FW, PLEX_STANDNUM_FH, 255, 255, 255, 255, PLEX_UNIT(7), PLEX_WH(true) - PLEX_UNIT(3), PLEX_UNIT(10), PLEX_UNIT(2), 0.1, 0.1, 0.8, 0.8, PLEX_UNIT(0.1), PLEX_LANGUAGE_ALPHASTRING, fontPlate, 0, 0, 0, 0, 0, true);
		return;
	}

	MMS2_startMenu(&id, &ix, &iy, &lh);

	for(size_t ze = 0; ze < MMS2_showGunCount(); ++ze)
	{
		const size_t index = MMS2_gunSlotIndex(ze);

		uint32_t cx = 0;
		uint32_t cd = 0;

		MMS_MINIGAME2GUN* nextGun = MMS2_gun(index);

		ix2 = MMS2_menuIx(id, ix, ze);

		if(nextGun->ammoClipMaximum > 0) cd = PLEX_UNIT(3)/nextGun->ammoClipMaximum;

		if(cd > PLEX_UNIT(0.75)) cd = PLEX_UNIT(0.75);

		MMS2_printMenuItem(ix2, iy, id, nextGun->icon);

		if(index == p_selectGun) PLEX_drawRect(MMS2_DRAWLAYER_GUI, ix2, iy, id, id, 255, 255, 0, 255, PLEX_UNIT(0.2), true);
		else PLEX_drawRect(MMS2_DRAWLAYER_GUI, ix2, iy, id, id, 255, 255, 255, 255, PLEX_UNIT(0.2), true);

		if(nextGun->ammoClip > 0)
		{
			for(size_t uh = 0; uh < nextGun->ammoClip; ++uh)
			{
				cx = ix2 + cd * uh + PLEX_UNIT(0.2);

				PLEX_printTexture(MMS2_DRAWLAYER_GUI, nextGun->clipIcon, 0, 0, 64, 64, cx, iy + PLEX_UNIT(0.2), cd, cd, true);
			}
		}

		if(nextGun->ammoMaximum != -1)
		{
			const PLEX_FAKESTRING_25 ammoMaxString = PLEX_createStringFromNumber25(nextGun->ammoMaximum);

			PLEX_FAKESTRING_25 ammoString = PLEX_createStringFromNumber25(nextGun->ammoAmount);

			ammoString = PLEX_concatString25(ammoString, ':', 1);
			ammoString = PLEX_mergeString25(ammoString, ammoMaxString);

			PLEX_drawLabel(MMS2_DRAWLAYER_GUI, PLEX_fts(ammoString), PLEX_STANDNUM_FW, PLEX_STANDNUM_FH, 255, 255, 255, 255, ix2, iy + id - lh, id, lh, 0.05, 0.05, 0.9, 0.9, PLEX_UNIT(0.05), PLEX_LANGUAGE_ALPHASTRING, fontPlate, 0, 0, 0, 0, 0, true);
		}

		if(MMS2_factorMenuItem(ix2, iy, id, lh, PLEX_fts(nextGun->name), fontPlate)) MMS2_selectGunSlotAt(ze, time);
	}

	if(MMS2_gunScroll())
	{
		if(PLEX_drawArrowButton(MMS2_DRAWLAYER_GUI, PLEX_UNIT(6), PLEX_WH(true) - PLEX_UNIT(4), PLEX_UNIT(1), PLEX_UNIT(4), 255, 0, 240, 255, 60, 37, 0, 255, PLEX_UNIT(0.1), true, true)) MMS2_gunMenuBack();
	}

	if(gunScrollEnd <= MMS2_GUNCOUNT)
	{
		if(PLEX_drawArrowButton(MMS2_DRAWLAYER_GUI, PLEX_WW(true) - PLEX_UNIT(1), PLEX_WH(true) - PLEX_UNIT(4), PLEX_UNIT(1), PLEX_UNIT(4), 255, 0, 240, 255, 60, 37, 0, 255, PLEX_UNIT(0.1), false, true)) MMS2_gunMenuForward();
	}
}

void MMS2_drawEnemyOffscreenArrow(const bool left)
{
	const double arrowWidth = PLEX_UNIT(2);
	const double arrowHeight = (PLEX_WH(true) - PLEX_UNIT(4))/6;

	if(left) PLEX_printTexture(50, p_arrows, 575, 65, 65, 63, 0, PLEX_WH(true)/2 - PLEX_UNIT(2) - arrowWidth/2, arrowWidth, arrowHeight, true);
	else PLEX_printTexture(50, p_arrows, 705, 65, 65, 63, PLEX_WW(true) - arrowWidth, PLEX_WH(true)/2 - PLEX_UNIT(2) - arrowWidth/2, arrowWidth, arrowHeight, true);
}

void MMS2_drawRestoreTownButton(const size_t chapter2SpriteTex, const size_t chapter2SpriteTex2, const size_t fontPlate, const uint64_t time)
{
	if(!MMS2_canRestoreTown()) return;

	if(PLEX_drawButton(MMS2_DRAWLAYER_GUI, "Restore Save", PLEX_STANDNUM_FW, PLEX_STANDNUM_FH, PLEX_WW(false) - PLEX_UNIT(5), PLEX_UNIT(1.5), PLEX_UNIT(5), PLEX_UNIT(1), 255, 255, 255, 255, 0, 0, 0, 255, PLEX_UNIT(0.08), PLEX_LANGUAGE_ALPHASTRING, fontPlate, 0, 0, 0, 0, 0, false))
	{
		MMS2_checkRestoreTown(chapter2SpriteTex, chapter2SpriteTex2, time);
		MMS2_endTutorial();
	}
}

void MMS2_setCustomCursorSelect()
{
	PLEX_unsetCustomCursor();

	PLEX_setCustomCursor(p_selectCursor, p_cursorD, p_cursorD, 0, 0, 64, 64, 0, 0, 64, 64, 0, 0, 64, 64);
	PLEX_setCustomCursorClick(p_selectCursorShoot, 0, 0, 64, 64);
	PLEX_setCustomCursorDown(p_selectCursorShoot, 0, 0, 64, 64);
}

void MMS2_unsetCustomCursor()
{
	PLEX_unsetCustomCursor();
	MM_COMMON_loadMMCursor();
}

void MMS2_gunMenuBack()
{
	p_gunScroll -= MMS2_GUNSCROLLUNIT;
}

void MMS2_gunMenuForward()
{
	p_gunScroll += MMS2_GUNSCROLLUNIT;
}

void MMS2_selectLastGun(const uint64_t time)
{
	if(MMS2_isReloading(time)) return;

	if(p_selectGunSlot) --p_selectGunSlot;
	else p_selectGunSlot = p_showGunCount - 1;

	MMS2_updateSelectGun(time);
}

void MMS2_selectNextGun(const uint64_t time)
{
	if(MMS2_isReloading(time)) return;

	if(p_selectGunSlot < p_showGunCount - 1) ++p_selectGunSlot;
	else p_selectGunSlot = 0;

	MMS2_updateSelectGun(time);
}

void MMS2_selectGunSlotAt(const size_t at, const uint64_t time)
{
	if(MMS2_isReloading(time)) return;

	p_selectGunSlot = at;

	MMS2_updateSelectGun(time);
}

void MMS2_updateSelectGun(const uint64_t time)
{
	if(MMS2_isReloading(time)) return;

	if(!p_showGunCount)
	{
		PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_ZEROVALUE, PLEX_ERROR_SEVERITY_MINOR, MMS2_ERRORMESS_ONUPDATESELECTGUN, MMS2_ERRORMESS_SELECTGUNCOUNT);
		return;
	}

	p_selectGun = p_selectGunIndex[p_selectGunSlot];
}

void MMS2_setPamalenaIconSpace(const PLEX_RECT pamIconSpace){ p_pamIconSpace = pamIconSpace; }

size_t MMS2_selectedGunIndex(){ return p_selectGun; }
size_t MMS2_selectedGunSlot(){ return p_selectGunSlot; }
size_t MMS2_selectedGunSlotIndex(){ return p_selectGunIndex[p_selectGunSlot]; }

size_t MMS2_showGunCount(){ return p_showGunCount; }

void MMS2_setShotArea(const PLEX_RECT shotArea){ p_shotArea = shotArea; }
void MMS2_setInnerShotArea(const PLEX_RECT innerShotArea){ p_innerShotArea = innerShotArea; }
void MMS2_setShotIcon(const size_t icon){ p_shotIcon = icon; }

size_t MMS2_gunSlotIndex(const size_t slot)
{
	if(slot >= p_showGunCount)
	{
		PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, MMS2_ERRORMESS_ONRETURNSLOTINDEX, MMS2_ERRORMESS_SELECTGUNINDEX);
		return 0;
	}

	return p_selectGunIndex[slot];
}

size_t MMS2_shotIcon(){ return p_shotIcon; }

size_t MMS2_gunScroll(){ return p_gunScroll; }

struct MMS_MINIGAME2GUN* MMS2_selectedGun(){ return MMS2_gun(p_selectGun); }

PLEX_RECT MMS2_getPamaleanaIconSpace(){ return p_pamIconSpace; }

PLEX_RECT MMS2_shotArea(){ return p_shotArea; }
PLEX_RECT MMS2_innerShotArea(){ return p_innerShotArea; }
