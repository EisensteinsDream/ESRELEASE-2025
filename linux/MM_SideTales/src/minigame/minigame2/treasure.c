#include "minigame/minigame2/minigame2.h"

static size_t p_treasureIcon = 0;
static size_t p_cashTreasureIcon = 0;
static size_t p_healthTreasureIcon = 0;

static size_t p_treasureCount = 0;
static MMS_MINIGAME2TREASUREBOX p_treasure[MMS2_TREASURECOUNT];

// adds a new treasure box to the map

static void p_addTreasureBox(const double x, const double y, const double cash, const bool hasAmmo, const bool hasHealth)
{
	MMS_MINIGAME2TREASUREBOX* newBox = NULL;

	size_t spot = p_treasureCount;

	for(size_t ze = 0; ze < p_treasureCount; ++ze)
	{
		if(p_treasure[ze].taken)
		{
			spot = ze;
			break;
		}
	}

	if(spot >= MMS2_TREASURECOUNT) return;

	newBox = p_treasure + spot;

	memset(newBox, 0, sizeof(MMS_MINIGAME2TREASUREBOX));

	newBox->x = x;
	newBox->y = y;
	newBox->cash = cash;
	newBox->hasHealth = hasHealth;
	newBox->hasAmmo = hasAmmo;
	newBox->taken = false;
	newBox->opened = false;
	newBox->openTime = 0;

	newBox->treasureAmmoIcon = 0;

	if(spot == p_treasureCount) ++p_treasureCount;
}

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

void MMS2_setSystemTreasure()
{
	p_treasureCount = 0;
}

void MMS2_initSystemTreasure()
{
	if(!p_treasureIcon) p_treasureIcon = PLEX_loadTextureFromFileOrHeaderless(64, 64, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_TREASURE, MMS2_FILEPATH_HEADERLESS_TREASURE);
	if(!p_cashTreasureIcon) p_cashTreasureIcon = PLEX_loadTextureFromFileOrHeaderless(64, 64, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_CASHTREASURE, MMS2_FILEPATH_HEADERLESS_CASHTREASURE);
	if(!p_healthTreasureIcon) p_healthTreasureIcon = PLEX_loadTextureFromFileOrHeaderless(64, 64, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_HEALTHTREASURE, MMS2_FILEPATH_HEADERLESS_HEALTHTREASURE);
}

void MMS2_checkRunSystemTreasure(const uint64_t time)
{
	PLEX_RECT dr;

	double openTimePerc = 1;

	if(MMS2_currentRoomCalm()) return;

	for(size_t ze = 0; ze < p_treasureCount; ++ze)
	{
		MMS_MINIGAME2TREASUREBOX* treasureBox = p_treasure + ze;

		size_t drawIcon = p_treasureIcon;

		if(treasureBox->taken) continue;

		if(treasureBox->opened)
		{
			openTimePerc = 1 - (time - treasureBox->openTime)/1000.0;

			if(openTimePerc < 0) openTimePerc = 0;

			if(openTimePerc <= 0)
			{
				treasureBox->taken = true;
				continue;
			}
		}

		dr.origin.x = PLEX_UNIT(treasureBox->x + MMS2_leanX());
		dr.origin.y = PLEX_UNIT(treasureBox->y + MMS2_leanY());
		dr.dimens.w = PLEX_UNIT(1);
		dr.dimens.h = PLEX_UNIT(1);

		if(treasureBox->opened)
		{
			if(treasureBox->hasAmmo) drawIcon = treasureBox->treasureAmmoIcon;
			else if(treasureBox->hasHealth) drawIcon = p_healthTreasureIcon;
			else drawIcon = p_cashTreasureIcon;
		}

		PLEX_printTextureTinted(150, drawIcon, 0, 0, 64, 64, dr.origin.x, dr.origin.y, dr.dimens.w, dr.dimens.h, 255 * openTimePerc, 255 * openTimePerc, 255 * openTimePerc, true);

		if(treasureBox->opened) continue;

		if(MMS2_playerIsNotShooting(time))
		{
			if(PLEX_rectCollisionNoMove(MMS2_shotArea(), dr))
			{
				MMS_MINIGAME2GUN* selectedGun = MMS2_selectedGun();

				MMS2_incrementCash(treasureBox->cash);

				if(treasureBox->hasHealth) MMS2_setHealth(1);

				if(treasureBox->hasAmmo)
				{
					MMS_MINIGAME2GUN* ammoGun = selectedGun;

					if(ammoGun->ammoAmount == -1)
					{
						size_t currentGun = MMS2_selectedGunIndex() + 1;

						ammoGun = MMS2_gun(currentGun);

						while(!MMS2_hasGun(currentGun) || ammoGun->ammoAmount == -1)
						{
							++currentGun;

							if(currentGun >= MMS2_GUNCOUNT) currentGun = 0;

							ammoGun = MMS2_gun(currentGun);

							if(currentGun == MMS2_selectedGunIndex()) break;
						}
					}

					treasureBox->treasureAmmoIcon = ammoGun->clipIcon;

					if(ammoGun->ammoAmount != ammoGun->ammoMaximum) ammoGun->ammoAmount = ammoGun->ammoMaximum;
					else{ if(ammoGun->ammoClip != ammoGun->ammoClipMaximum) ++ammoGun->ammoClip; }
				}

				treasureBox->opened = true;
				treasureBox->openTime = time;
			}
		}
	}
}

void MMS2_endSystemTreasure()
{
	PLEX_destroyTexture(p_treasureIcon);
	PLEX_destroyTexture(p_cashTreasureIcon);
	PLEX_destroyTexture(p_healthTreasureIcon);

	p_treasureIcon = 0;
	p_cashTreasureIcon = 0;
	p_healthTreasureIcon = 0;
}

void MMS2_addTreasureBoxCash(const double x, const double y, const double cash)
{
	p_addTreasureBox(x, y, cash, false, false);
}

void MMS2_addTreasureBoxHealth(const double x, const double y)
{
	p_addTreasureBox(x, y, 0, false, true);
}

void MMS2_addTreasureBoxAmmo(const double x, const double y)
{
	p_addTreasureBox(x, y, 0, true, false);
}

void MMS2_clearTreasureCount(){ p_treasureCount = 0; }
