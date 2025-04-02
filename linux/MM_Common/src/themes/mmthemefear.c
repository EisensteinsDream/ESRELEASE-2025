#include "mmthemes.h"

// NOTE: global function descriptions in header.

// static values ------------------------------------------------------------------------------------------------------------

static int64_t p_fearBufferList[40];

static int64_t p_fearAmsynthA = -1;
static int64_t p_fearAmsynthB = -1;
static int64_t p_fearAmsynthC = -1;
static int64_t p_fearAmsynthD = -1;
static int64_t p_fearAmsynthE = -1;
static int64_t p_fearAmsynthF = -1;
static int64_t p_fearAmsynthG = -1;
static int64_t p_fearAmsynthH = -1;
static int64_t p_fearAmsynthI = -1;
static int64_t p_fearAmsynthJ = -1;

static int64_t p_fearOrganA = -1;
static int64_t p_fearOrganB = -1;
static int64_t p_fearOrganC = -1;
static int64_t p_fearOrganD = -1;
static int64_t p_fearOrganE = -1;
static int64_t p_fearOrganF = -1;
static int64_t p_fearOrganG = -1;
static int64_t p_fearOrganH = -1;
static int64_t p_fearOrganI = -1;
static int64_t p_fearOrganJ = -1;

static int64_t p_fearHarpA = -1;
static int64_t p_fearHarpB = -1;
static int64_t p_fearHarpC = -1;
static int64_t p_fearHarpD = -1;
static int64_t p_fearHarpE = -1;
static int64_t p_fearHarpF = -1;
static int64_t p_fearHarpG = -1;
static int64_t p_fearHarpH = -1;
static int64_t p_fearHarpI = -1;
static int64_t p_fearHarpJ = -1;

static int64_t p_fearViolinA = -1;
static int64_t p_fearViolinB = -1;
static int64_t p_fearViolinC = -1;
static int64_t p_fearViolinD = -1;
static int64_t p_fearViolinE = -1;
static int64_t p_fearViolinF = -1;
static int64_t p_fearViolinG = -1;
static int64_t p_fearViolinH = -1;
static int64_t p_fearViolinI = -1;
static int64_t p_fearViolinJ = -1;

static size_t p_fearIt = 0;

static PLEX_FAKESTRING_50 p_fearThemeStr;

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

// specialized functions ----------------------------------------------------------------------------------------------------

void MM_COMMON_THEME_FEAR_start()
{
	p_fearThemeStr = PLEX_createString50("Fear");
}

void MM_COMMON_THEME_FEAR_playTheme()
{
	p_fearAmsynthA = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_FEAR_AMSYNTHA);
	p_fearAmsynthB = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_FEAR_AMSYNTHB);
	p_fearAmsynthC = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_FEAR_AMSYNTHC);
	p_fearAmsynthD = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_FEAR_AMSYNTHD);
	p_fearAmsynthE = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_FEAR_AMSYNTHE);
	p_fearAmsynthF = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_FEAR_AMSYNTHF);
	p_fearAmsynthG = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_FEAR_AMSYNTHG);
	p_fearAmsynthH = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_FEAR_AMSYNTHH);
	p_fearAmsynthI = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_FEAR_AMSYNTHI);
	p_fearAmsynthJ = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_FEAR_AMSYNTHJ);

	p_fearOrganA = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_FEAR_ORGANA);
	p_fearOrganB = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_FEAR_ORGANB);
	p_fearOrganC = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_FEAR_ORGANC);
	p_fearOrganD = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_FEAR_ORGAND);
	p_fearOrganE = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_FEAR_ORGANE);
	p_fearOrganF = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_FEAR_ORGANF);
	p_fearOrganG = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_FEAR_ORGANG);
	p_fearOrganH = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_FEAR_ORGANH);
	p_fearOrganI = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_FEAR_ORGANI);
	p_fearOrganJ = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_FEAR_ORGANJ);

	p_fearHarpA = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_FEAR_HARPA);
	p_fearHarpB = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_FEAR_HARPB);
	p_fearHarpC = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_FEAR_HARPC);
	p_fearHarpD = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_FEAR_HARPD);
	p_fearHarpE = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_FEAR_HARPE);
	p_fearHarpF = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_FEAR_HARPF);
	p_fearHarpG = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_FEAR_HARPG);
	p_fearHarpH = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_FEAR_HARPH);
	p_fearHarpI = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_FEAR_HARPI);
	p_fearHarpJ = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_FEAR_HARPJ);

	p_fearViolinA = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_FEAR_VIOLINA);
	p_fearViolinB = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_FEAR_VIOLINB);
	p_fearViolinC = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_FEAR_VIOLINC);
	p_fearViolinD = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_FEAR_VIOLIND);
	p_fearViolinE = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_FEAR_VIOLINE);
	p_fearViolinF = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_FEAR_VIOLINF);
	p_fearViolinG = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_FEAR_VIOLING);
	p_fearViolinH = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_FEAR_VIOLINH);
	p_fearViolinI = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_FEAR_VIOLINI);
	p_fearViolinJ = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_FEAR_VIOLINJ);

	if(p_fearAmsynthA != -1 && MM_COMMON_musicAssignBuffer(p_fearAmsynthA, 0)) MM_COMMON_musicChannelOn(false, 0);
	if(p_fearOrganA != -1 && MM_COMMON_musicAssignBuffer(p_fearOrganA, 1)) MM_COMMON_musicChannelOn(false, 1);
	if(p_fearHarpA != -1 && MM_COMMON_musicAssignBuffer(p_fearHarpA, 2)) MM_COMMON_musicChannelOn(false, 2);
	if(p_fearViolinA != -1 && MM_COMMON_musicAssignBuffer(p_fearViolinA, 3)) MM_COMMON_musicChannelOn(false, 3);

	p_fearBufferList[0] = p_fearAmsynthA;
	p_fearBufferList[1] = p_fearAmsynthB;
	p_fearBufferList[2] = p_fearAmsynthC;
	p_fearBufferList[3] = p_fearAmsynthD;
	p_fearBufferList[4] = p_fearAmsynthE;
	p_fearBufferList[5] = p_fearAmsynthF;
	p_fearBufferList[6] = p_fearAmsynthG;
	p_fearBufferList[7] = p_fearAmsynthH;
	p_fearBufferList[8] = p_fearAmsynthI;
	p_fearBufferList[9] = p_fearAmsynthJ;

	p_fearBufferList[10] = p_fearOrganA;
	p_fearBufferList[11] = p_fearOrganB;
	p_fearBufferList[12] = p_fearOrganC;
	p_fearBufferList[13] = p_fearOrganD;
	p_fearBufferList[14] = p_fearOrganE;
	p_fearBufferList[15] = p_fearOrganF;
	p_fearBufferList[16] = p_fearOrganG;
	p_fearBufferList[17] = p_fearOrganH;
	p_fearBufferList[18] = p_fearOrganI;
	p_fearBufferList[19] = p_fearOrganJ;

	p_fearBufferList[20] = p_fearHarpA;
	p_fearBufferList[21] = p_fearHarpB;
	p_fearBufferList[22] = p_fearHarpC;
	p_fearBufferList[23] = p_fearHarpD;
	p_fearBufferList[24] = p_fearHarpE;
	p_fearBufferList[25] = p_fearHarpF;
	p_fearBufferList[26] = p_fearHarpG;
	p_fearBufferList[27] = p_fearHarpH;
	p_fearBufferList[28] = p_fearHarpI;
	p_fearBufferList[29] = p_fearHarpJ;

	p_fearBufferList[30] = p_fearViolinA;
	p_fearBufferList[31] = p_fearViolinB;
	p_fearBufferList[32] = p_fearViolinC;
	p_fearBufferList[33] = p_fearViolinD;
	p_fearBufferList[34] = p_fearViolinE;
	p_fearBufferList[35] = p_fearViolinF;
	p_fearBufferList[36] = p_fearViolinG;
	p_fearBufferList[37] = p_fearViolinH;
	p_fearBufferList[38] = p_fearViolinI;
	p_fearBufferList[39] = p_fearViolinJ;

	p_fearIt = 1;
}

void MM_COMMON_THEME_FEAR_updateTheme()
{
	if(!PLEX_isSoundPlaying(0))
	{
		MM_COMMON_musicChannelOff(0);
		MM_COMMON_musicChannelOff(1);
		MM_COMMON_musicChannelOff(2);
		MM_COMMON_musicChannelOff(3);

		switch(p_fearIt)
		{
			case 0:
				if(p_fearAmsynthA != -1 && MM_COMMON_musicAssignBuffer(p_fearAmsynthA, 0)) MM_COMMON_musicChannelOn(false, 0);
				if(p_fearOrganA != -1 && MM_COMMON_musicAssignBuffer(p_fearOrganA, 1)) MM_COMMON_musicChannelOn(false, 1);
				if(p_fearHarpA != -1 && MM_COMMON_musicAssignBuffer(p_fearHarpA, 2)) MM_COMMON_musicChannelOn(false, 2);
				if(p_fearViolinA != -1 && MM_COMMON_musicAssignBuffer(p_fearViolinA, 3)) MM_COMMON_musicChannelOn(false, 3);

				++p_fearIt;
			break;

			case 1:
				if(p_fearAmsynthB != -1 && MM_COMMON_musicAssignBuffer(p_fearAmsynthB, 0)) MM_COMMON_musicChannelOn(false, 0);
				if(p_fearOrganB != -1 && MM_COMMON_musicAssignBuffer(p_fearOrganB, 1)) MM_COMMON_musicChannelOn(false, 1);
				if(p_fearHarpB != -1 && MM_COMMON_musicAssignBuffer(p_fearHarpB, 2)) MM_COMMON_musicChannelOn(false, 2);
				if(p_fearViolinB != -1 && MM_COMMON_musicAssignBuffer(p_fearViolinB, 3)) MM_COMMON_musicChannelOn(false, 3);

				++p_fearIt;
			break;

			case 2:
				if(p_fearAmsynthC != -1 && MM_COMMON_musicAssignBuffer(p_fearAmsynthC, 0)) MM_COMMON_musicChannelOn(false, 0);
				if(p_fearOrganC != -1 && MM_COMMON_musicAssignBuffer(p_fearOrganC, 1)) MM_COMMON_musicChannelOn(false, 1);
				if(p_fearHarpC != -1 && MM_COMMON_musicAssignBuffer(p_fearHarpC, 2)) MM_COMMON_musicChannelOn(false, 2);
				if(p_fearViolinC != -1 && MM_COMMON_musicAssignBuffer(p_fearViolinC, 3)) MM_COMMON_musicChannelOn(false, 3);

				++p_fearIt;
			break;

			case 3:
				if(p_fearAmsynthD != -1 && MM_COMMON_musicAssignBuffer(p_fearAmsynthD, 0)) MM_COMMON_musicChannelOn(false, 0);
				if(p_fearOrganD != -1 && MM_COMMON_musicAssignBuffer(p_fearOrganD, 1)) MM_COMMON_musicChannelOn(false, 1);
				if(p_fearHarpD != -1 && MM_COMMON_musicAssignBuffer(p_fearHarpD, 2)) MM_COMMON_musicChannelOn(false, 2);
				if(p_fearViolinD != -1 && MM_COMMON_musicAssignBuffer(p_fearViolinD, 3)) MM_COMMON_musicChannelOn(false, 3);

				++p_fearIt;
			break;

			case 4:
				if(p_fearAmsynthE != -1 && MM_COMMON_musicAssignBuffer(p_fearAmsynthE, 0)) MM_COMMON_musicChannelOn(false, 0);
				if(p_fearOrganE != -1 && MM_COMMON_musicAssignBuffer(p_fearOrganE, 1)) MM_COMMON_musicChannelOn(false, 1);
				if(p_fearHarpE != -1 && MM_COMMON_musicAssignBuffer(p_fearHarpE, 2)) MM_COMMON_musicChannelOn(false, 2);
				if(p_fearViolinE != -1 && MM_COMMON_musicAssignBuffer(p_fearViolinE, 3)) MM_COMMON_musicChannelOn(false, 3);

				++p_fearIt;
			break;

			case 5:
				if(p_fearAmsynthF != -1 && MM_COMMON_musicAssignBuffer(p_fearAmsynthF, 0)) MM_COMMON_musicChannelOn(false, 0);
				if(p_fearOrganF != -1 && MM_COMMON_musicAssignBuffer(p_fearOrganF, 1)) MM_COMMON_musicChannelOn(false, 1);
				if(p_fearHarpF != -1 && MM_COMMON_musicAssignBuffer(p_fearHarpF, 2)) MM_COMMON_musicChannelOn(false, 2);
				if(p_fearViolinF != -1 && MM_COMMON_musicAssignBuffer(p_fearViolinF, 3)) MM_COMMON_musicChannelOn(false, 3);

				++p_fearIt;
			break;

			case 6:
				if(p_fearAmsynthG != -1 && MM_COMMON_musicAssignBuffer(p_fearAmsynthG, 0)) MM_COMMON_musicChannelOn(false, 0);
				if(p_fearOrganG != -1 && MM_COMMON_musicAssignBuffer(p_fearOrganG, 1)) MM_COMMON_musicChannelOn(false, 1);
				if(p_fearHarpG != -1 && MM_COMMON_musicAssignBuffer(p_fearHarpG, 2)) MM_COMMON_musicChannelOn(false, 2);
				if(p_fearViolinG != -1 && MM_COMMON_musicAssignBuffer(p_fearViolinG, 3)) MM_COMMON_musicChannelOn(false, 3);

				++p_fearIt;
			break;

			case 7:
				if(p_fearAmsynthH != -1 && MM_COMMON_musicAssignBuffer(p_fearAmsynthH, 0)) MM_COMMON_musicChannelOn(false, 0);
				if(p_fearOrganH != -1 && MM_COMMON_musicAssignBuffer(p_fearOrganH, 1)) MM_COMMON_musicChannelOn(false, 1);
				if(p_fearHarpH != -1 && MM_COMMON_musicAssignBuffer(p_fearHarpH, 2)) MM_COMMON_musicChannelOn(false, 2);
				if(p_fearViolinH != -1 && MM_COMMON_musicAssignBuffer(p_fearViolinH, 3)) MM_COMMON_musicChannelOn(false, 3);

				++p_fearIt;
			break;

			case 8:
				if(p_fearAmsynthI != -1 && MM_COMMON_musicAssignBuffer(p_fearAmsynthI, 0)) MM_COMMON_musicChannelOn(false, 0);
				if(p_fearOrganI != -1 && MM_COMMON_musicAssignBuffer(p_fearOrganI, 1)) MM_COMMON_musicChannelOn(false, 1);
				if(p_fearHarpI != -1 && MM_COMMON_musicAssignBuffer(p_fearHarpI, 2)) MM_COMMON_musicChannelOn(false, 2);
				if(p_fearViolinI != -1 && MM_COMMON_musicAssignBuffer(p_fearViolinI, 3)) MM_COMMON_musicChannelOn(false, 3);

				++p_fearIt;
			break;

			case 9:
				if(p_fearAmsynthJ != -1 && MM_COMMON_musicAssignBuffer(p_fearAmsynthJ, 0)) MM_COMMON_musicChannelOn(false, 0);
				if(p_fearOrganJ != -1 && MM_COMMON_musicAssignBuffer(p_fearOrganJ, 1)) MM_COMMON_musicChannelOn(false, 1);
				if(p_fearHarpJ != -1 && MM_COMMON_musicAssignBuffer(p_fearHarpJ, 2)) MM_COMMON_musicChannelOn(false, 2);
				if(p_fearViolinJ != -1 && MM_COMMON_musicAssignBuffer(p_fearViolinJ, 3)) MM_COMMON_musicChannelOn(false, 3);

				++p_fearIt;
			break;

			case 10:
				for(size_t ze = 0; ze < 40; ++ze)
				{
					const int64_t buffer = p_fearBufferList[ze];

					const double perc = PLEX_randomPercentage();

					if(buffer < 0) continue;

					if(perc >= 0.75) PLEX_soundReverse(buffer, 0, 0.99);
				}

				p_fearIt = PLEX_randomNumber(0, 9);
			break;
		};
	}
}

// getters ------------------------------------------------------------------------------------------------------------------

PLEX_FAKESTRING_50 MM_COMMON_THEME_fearThemeStr()
{
	return p_fearThemeStr;
}
