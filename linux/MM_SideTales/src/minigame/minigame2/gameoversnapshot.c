#include "minigame/minigame2/minigame2.h"

static bool p_gameOverMode = false;

static bool p_terminate = false;
static bool p_terminateConfirm = false;

// do not make these size_t
static uint32_t p_lastTownPoints = 0;
static uint32_t p_lastTownCash = 0;
static double p_lastTownHealth = 0;
//

static int64_t p_lastTownAmmoAmount[MMS2_GUNCOUNT];
static int64_t p_lastTownClipAmount[MMS2_GUNCOUNT];

static bool p_lastTownHasGun[MMS2_GUNCOUNT];

static bool p_lastTownGotBoss = false;
static bool p_canRestoreTown = false;

// loads the savefile (ie. snapshot) if it exists

static bool p_checkLoadSnapshot(const size_t chapter2SpriteTex, const size_t chapter2SpriteTex2, const uint64_t time)
{
	FILE* load = fopen("mg2town", "r");

	if(load == NULL)
	{
		// no error
		return false;
	}

	if(fread(&p_lastTownPoints, sizeof(uint32_t), 1, load) == EOF)
	{
		PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_CONTENTCORRUPTION, PLEX_ERROR_SEVERITY_MINOR, MMS2_ERRORMESS_ONLOADSNAPSHOT, MMS2_ERRORMESS_SNAPSHOTFILE);
		fclose(load);
		return false;
	}

	if(fread(&p_lastTownCash, sizeof(uint32_t), 1, load) == EOF)
	{
		PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_CONTENTCORRUPTION, PLEX_ERROR_SEVERITY_MINOR, MMS2_ERRORMESS_ONLOADSNAPSHOT, MMS2_ERRORMESS_SNAPSHOTFILE);
		fclose(load);
		return false;
	}

	if(fread(&p_lastTownHealth, sizeof(double), 1, load) == EOF)
	{
		PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_CONTENTCORRUPTION, PLEX_ERROR_SEVERITY_MINOR, MMS2_ERRORMESS_ONLOADSNAPSHOT, MMS2_ERRORMESS_SNAPSHOTFILE);
		fclose(load);
		return false;
	}

	for(size_t ze = 0; ze < MMS2_GUNCOUNT; ++ze)
	{
		uint8_t loadGun = 0;

		int64_t clipAmount = 0;
		int64_t ammoAmount = 0;

		if(fread(&loadGun, sizeof(uint8_t), 1, load) == EOF)
		{
			PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_CONTENTCORRUPTION, PLEX_ERROR_SEVERITY_MINOR, MMS2_ERRORMESS_ONLOADSNAPSHOT, MMS2_ERRORMESS_SNAPSHOTFILE);
			fclose(load);
			return false;
		}

		if(fread(&ammoAmount, sizeof(int64_t), 1, load) == EOF)
		{
			PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_CONTENTCORRUPTION, PLEX_ERROR_SEVERITY_MINOR, MMS2_ERRORMESS_ONLOADSNAPSHOT, MMS2_ERRORMESS_SNAPSHOTFILE);
			fclose(load);
			return false;
		}

		if(fread(&clipAmount, sizeof(int64_t), 1, load) == EOF)
		{
			PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_CONTENTCORRUPTION, PLEX_ERROR_SEVERITY_MINOR, MMS2_ERRORMESS_ONLOADSNAPSHOT, MMS2_ERRORMESS_SNAPSHOTFILE);
			fclose(load);
			return false;
		}

		p_lastTownHasGun[ze] = loadGun;

		p_lastTownAmmoAmount[ze] = ammoAmount;
		p_lastTownClipAmount[ze] = clipAmount;
	}

	if(fread(&p_lastTownGotBoss, sizeof(uint8_t), 1, load) == EOF)
	{
		PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_CONTENTCORRUPTION, PLEX_ERROR_SEVERITY_MINOR, MMS2_ERRORMESS_ONLOADSNAPSHOT, MMS2_ERRORMESS_SNAPSHOTFILE);
		fclose(load);
		return false;
	}

	fclose(load);

	MMS2_restoreTown();

	MMS2_pointCheckTown(chapter2SpriteTex, chapter2SpriteTex2, time);

	return true;
}

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

bool MMS2_setSystemGameoverSnapshot(const size_t chapter2SpriteTex, const size_t chapter2SpriteTex2, const uint64_t time)
{
	// do not restore town here //

	if(!MMS2_pointCheckTown(chapter2SpriteTex, chapter2SpriteTex2, time))
	{
		PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_BADOPERATION, PLEX_ERROR_SEVERITY_FATAL, MMS2_ERRORMESS_ONSTARTINGGAMEOVERSNAPSHOT, MMS2_ERRORMESS_OP_POINTCHECKTOWN);
		return false;
	}

	return true;
}

void MMS2_initSystemGameoverSnapshot()
{
	p_lastTownCash = 10;
	p_lastTownPoints = 0;
	p_lastTownHealth = 1;

	for(size_t ze = 0; ze < MMS2_GUNCOUNT; ++ze) p_lastTownClipAmount[ze] = -1;
}

bool MMS2_checkRunSystemGameoverSnapshot(const size_t chapter2SpriteTex, const size_t chapter2SpriteTex2, const size_t fontPlate, const uint64_t time)
{
	if(MMS2_checkTerminated(fontPlate)) return false;

	if(MMS2_runGameoverMode(chapter2SpriteTex, chapter2SpriteTex2, time)) return false;

	return true;
}

void MMS2_endSystemGameoverSnapshot()
{

}

void MMS2_snapshotTown()
{
	p_lastTownCash = MMS2_cash();
	p_lastTownPoints = MMS2_points();
	p_lastTownHealth = MMS2_health();

	for(size_t ze = 0; ze < MMS2_GUNCOUNT; ++ze)
	{
		if(MMS2_hasGun(ze))
		{
			p_lastTownAmmoAmount[ze] = MMS2_gun(ze)->ammoAmount;
			p_lastTownClipAmount[ze] = MMS2_gun(ze)->ammoClip;

			p_lastTownHasGun[ze] = true;
		}else{
			p_lastTownAmmoAmount[ze] = -1;
			p_lastTownClipAmount[ze] = -1;

			if(ze != 1) p_lastTownHasGun[ze] = false;
		}
	}
}

void MMS2_restoreTown()
{
	MMS2_clearEnemyCount();
	MMS2_clearCoverCount();

	MMS2_setCash(p_lastTownCash);
	MMS2_setPoints(p_lastTownPoints);
	MMS2_setHealth(p_lastTownHealth);

	for(size_t ze = 0; ze < MMS2_GUNCOUNT; ++ze)
	{
		MMS_MINIGAME2GUN* gun = MMS2_gun(ze);

		if(gun->ammoMaximum != -1)
		{
			if(p_lastTownClipAmount[ze] == -1)
			{
				p_lastTownAmmoAmount[ze] = gun->ammoMaximum;
				p_lastTownClipAmount[ze] = gun->ammoClipMaximum;
			}

			gun->ammoAmount = p_lastTownAmmoAmount[ze];
			gun->ammoClip = p_lastTownClipAmount[ze];

			if(!gun->ammoAmount && gun->ammoClip)
			{
				gun->ammoAmount = gun->ammoMaximum;
				--gun->ammoClip;
			}
		}

		if(ze > 1)
		{
			if(MMS2_hasGun(ze) && !p_lastTownHasGun[ze]) MMS2_takeGun(ze);
			if(!MMS2_hasGun(ze) && p_lastTownHasGun[ze]) MMS2_addGun(ze);
		}else MMS2_addGun(ze);
	}

	MMS2_clearFinalBoss();
	MMS2_clearPenultimateCutscene();

	MMS2_setTownArea(0);
}

void MMS2_dumpSnapshot()
{
	FILE* save = fopen("mg2town", "w+");

	if(save == NULL)
	{
		PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_FILESAVE, PLEX_ERROR_SEVERITY_MINOR, MMS2_ERRORMESS_ONDUMPSNAPSHOT, MMS2_ERRORMESS_SNAPSHOTFILE);
		return;
	}

	if(fwrite(&p_lastTownPoints, sizeof(uint32_t), 1, save) == EOF)
	{
		PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_FILESAVE, PLEX_ERROR_SEVERITY_MINOR, MMS2_ERRORMESS_ONDUMPSNAPSHOT, MMS2_ERRORMESS_SNAPSHOTFILE);
		fclose(save);
		return;
	}

	if(fwrite(&p_lastTownCash, sizeof(uint32_t), 1, save) == EOF)
	{
		PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_FILESAVE, PLEX_ERROR_SEVERITY_MINOR, MMS2_ERRORMESS_ONDUMPSNAPSHOT, MMS2_ERRORMESS_SNAPSHOTFILE);
		fclose(save);
		return;
	}

	if(fwrite(&p_lastTownHealth, sizeof(double), 1, save) == EOF)
	{
		PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_FILESAVE, PLEX_ERROR_SEVERITY_MINOR, MMS2_ERRORMESS_ONDUMPSNAPSHOT, MMS2_ERRORMESS_SNAPSHOTFILE);
		fclose(save);
		return;
	}

	for(size_t ze = 0; ze < MMS2_GUNCOUNT; ++ze)
	{
		const uint8_t saveGun = p_lastTownHasGun[ze];

		const int64_t ammoAmount = p_lastTownAmmoAmount[ze];
		const int64_t clipAmount = p_lastTownClipAmount[ze];

		if(fwrite(&saveGun, sizeof(uint8_t), 1, save) == EOF)
		{
			PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_FILESAVE, PLEX_ERROR_SEVERITY_MINOR, MMS2_ERRORMESS_ONDUMPSNAPSHOT, MMS2_ERRORMESS_SNAPSHOTFILE);
			fclose(save);
			return;
		}

		if(fwrite(&ammoAmount, sizeof(int64_t), 1, save) == EOF)
		{
			PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_FILESAVE, PLEX_ERROR_SEVERITY_MINOR, MMS2_ERRORMESS_ONDUMPSNAPSHOT, MMS2_ERRORMESS_SNAPSHOTFILE);
			fclose(save);
			return;
		}

		if(fwrite(&clipAmount, sizeof(int64_t), 1, save) == EOF)
		{
			PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_FILESAVE, PLEX_ERROR_SEVERITY_MINOR, MMS2_ERRORMESS_ONDUMPSNAPSHOT, MMS2_ERRORMESS_SNAPSHOTFILE);
			fclose(save);
			return;
		}
	}

	if(!p_lastTownGotBoss) p_lastTownGotBoss = MMS2_beginFinalBossIntro() || MMS2_activateFinalBoss() || MMS2_beginFinalBossOutro();

	if(fwrite(&p_lastTownGotBoss, sizeof(uint8_t), 1, save) == EOF)
	{
		PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_FILESAVE, PLEX_ERROR_SEVERITY_MINOR, MMS2_ERRORMESS_ONDUMPSNAPSHOT, MMS2_ERRORMESS_SNAPSHOTFILE);
		fclose(save);
		return;
	}

	fclose(save);
}

void MMS2_gameOverScene(const size_t pamaleanaSpriteTex, const size_t cubicleBackdrop, const size_t venariusSpriteTex, const size_t extraplocanSpriteTex, const size_t label, const size_t bubble, const size_t arrow, const size_t fontPlate, const uint64_t time)
{
	MM_COMMON_playTheme(MM_COMMON_THEMEID_NONE);

	MMS2_unsetCustomCursor();

	MMS_startPamaleanasCubicle(pamaleanaSpriteTex, cubicleBackdrop, venariusSpriteTex, extraplocanSpriteTex, fontPlate, label, bubble, arrow);

	MMS_extrapTalk(MMS2_LANGUAGE_GAMEOVER_LINE1);
	MMS_pamTalk(MMS2_LANGUAGE_GAMEOVER_LINE2);
	MMS_extrapTalk(MMS2_LANGUAGE_GAMEOVER_LINE3);
	MMS_pamTalk(MMS2_LANGUAGE_GAMEOVER_LINE4);
	MMS_extrapTalk(MMS2_LANGUAGE_GAMEOVER_LINE5);
	MMS_pamTalk(MMS2_LANGUAGE_GAMEOVER_LINE6);

	p_gameOverMode = true;
}

bool MMS2_runGameoverMode(const size_t chapter2SpriteTex, const size_t chapter2SpriteTex2, const uint64_t time)
{
	if(p_gameOverMode)
	{
		if(!PLEX_isSpriteTheaterOver() && !p_terminateConfirm)
		{
			PLEX_updateSpriteTheater(time);
			return true;
		}else{
			p_gameOverMode = false;
			PLEX_endSpriteTheater();

			if(!p_terminateConfirm)
			{
				MMS2_restoreTown();
				MMS2_pointCheckTown(chapter2SpriteTex, chapter2SpriteTex2, time);
			}
		}
	}

	return false;
}

void MMS2_checkHasSnapshotFile()
{
	FILE* load = fopen("mg2town", "r");

	if(load != NULL)
	{
		p_canRestoreTown = true;
		fclose(load);
	}
}

void MMS2_checkRestoreTown(const size_t chapter2SpriteTex, const size_t chapter2SpriteTex2, const uint64_t time)
{
	if(!p_canRestoreTown) return;

	if(!p_checkLoadSnapshot(chapter2SpriteTex, chapter2SpriteTex2, time))
	{
		PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_BADOPERATION, PLEX_ERROR_SEVERITY_MAJOR, MMS2_ERRORMESS_ONUPDATEGAME, MMS2_ERRORMESS_OP_LOADSNAPSHOT);
		return;
	}

	p_canRestoreTown = false;
}

bool MMS2_checkTerminated(const size_t fontPlate)
{
	if(!p_terminate)
	{
		if(PLEX_isTerminated()) p_terminate = true;
	}else{
		PLEX_drawTextBox(MMS2_DRAWLAYER_GUI, MMS2_LANGUAGE_CONFIRMTOWNSAVE, PLEX_STANDNUM_FW, PLEX_STANDNUM_FH, 255, 255, 255, 255, PLEX_UNIT(3), PLEX_UNIT(2), PLEX_WW(true) - PLEX_UNIT(6), PLEX_UNIT(12), PLEX_UNIT(1), PLEX_UNIT(1.5), 0, 0, 1, 1, 0, PLEX_LANGUAGE_ALPHASTRING, fontPlate, 0, 0, 0, 0, 0, 0.5, true);

		if(PLEX_drawButton(MMS2_DRAWLAYER_GUI, MMS2_LANGUAGE_SAVETOWNMARKER, PLEX_STANDNUM_FW, PLEX_STANDNUM_FH, PLEX_UNIT(3), PLEX_WH(true) * 0.75, PLEX_WW(true) - PLEX_UNIT(6), PLEX_UNIT(2), 255, 255, 255, 255, 0, 0, 0, 255, PLEX_UNIT(0.05), PLEX_LANGUAGE_ALPHASTRING, fontPlate, 0, 0, 0, 0, 0, true))
		{
			MMS2_dumpSnapshot();
			p_terminateConfirm = true;
		}else{
			if(PLEX_leftClick()) p_terminateConfirm = true;
		}

		return true;
	}

	return false;
}

bool MMS2_lastTownGotBoss(){ return p_lastTownGotBoss; }

bool MMS2_terminateConfirm(){ return p_terminateConfirm; }

bool MMS2_canRestoreTown(){ return p_canRestoreTown; }
