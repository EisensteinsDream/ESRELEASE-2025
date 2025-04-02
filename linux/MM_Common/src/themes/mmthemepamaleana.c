#include "mmthemes.h"

// NOTE: global function descriptions in header.

// static values ------------------------------------------------------------------------------------------------------------

static int64_t p_pamThemePiano0 = -1;
static int64_t p_pamThemePiano1 = -1;
static int64_t p_pamThemePiano2 = -1;
static int64_t p_pamThemePiano3 = -1;
static int64_t p_pamThemePiano4 = -1;
static int64_t p_pamThemePiano5 = -1;
static int64_t p_pamThemePiano6 = -1;
static int64_t p_pamThemePiano7 = -1;
static int64_t p_pamThemePiano8 = -1;
static int64_t p_pamThemePiano9 = -1;

static int64_t p_pamThemeContrabass0 = -1;
static int64_t p_pamThemeContrabass1 = -1;
static int64_t p_pamThemeContrabass2 = -1;
static int64_t p_pamThemeContrabass3 = -1;
static int64_t p_pamThemeContrabass4 = -1;
static int64_t p_pamThemeContrabass5 = -1;
static int64_t p_pamThemeContrabass7 = -1;
static int64_t p_pamThemeContrabass8 = -1;
static int64_t p_pamThemeContrabass9 = -1;

static int64_t p_pamThemeViolin0 = -1;
static int64_t p_pamThemeViolin1 = -1;
static int64_t p_pamThemeViolin2 = -1;
static int64_t p_pamThemeViolin3 = -1;
static int64_t p_pamThemeViolin4 = -1;
static int64_t p_pamThemeViolin5 = -1;
static int64_t p_pamThemeViolin7 = -1;
static int64_t p_pamThemeViolin8 = -1;
static int64_t p_pamThemeViolin9 = -1;

static int64_t p_pamThemeMarimba0 = -1;
static int64_t p_pamThemeMarimba1 = -1;
static int64_t p_pamThemeMarimba2 = -1;
static int64_t p_pamThemeMarimba3 = -1;
static int64_t p_pamThemeMarimba4 = -1;
static int64_t p_pamThemeMarimba5 = -1;
static int64_t p_pamThemeMarimba7 = -1;
static int64_t p_pamThemeMarimba8 = -1;
static int64_t p_pamThemeMarimba9 = -1;

static int64_t p_pamThemeWavetable0 = -1;
static int64_t p_pamThemeWavetable1 = -1;
static int64_t p_pamThemeWavetable2 = -1;
static int64_t p_pamThemeWavetable3 = -1;
static int64_t p_pamThemeWavetable4 = -1;
static int64_t p_pamThemeWavetable5 = -1;
static int64_t p_pamThemeWavetable6 = -1;
static int64_t p_pamThemeWavetable7 = -1;
static int64_t p_pamThemeWavetable8 = -1;
static int64_t p_pamThemeWavetable9 = -1;

static int64_t p_pamThemeAMSynth0 = -1;
static int64_t p_pamThemeAMSynth1 = -1;
static int64_t p_pamThemeAMSynth2 = -1;
static int64_t p_pamThemeAMSynth3 = -1;
static int64_t p_pamThemeAMSynth4 = -1;
static int64_t p_pamThemeAMSynth5 = -1;
static int64_t p_pamThemeAMSynth6 = -1;
static int64_t p_pamThemeAMSynth7 = -1;
static int64_t p_pamThemeAMSynth8 = -1;
static int64_t p_pamThemeAMSynth9 = -1;

static size_t p_pamThemeIteration = 0;

static PLEX_FAKESTRING_50 p_pamaleanaThemeStr;

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

// specialized functions ----------------------------------------------------------------------------------------------------

void MM_COMMON_THEME_PAMALEANA_start()
{
	p_pamaleanaThemeStr = PLEX_createString50("Pamaleana");
}

void MM_COMMON_THEME_PAMALEANA_playTheme()
{
	p_pamThemePiano0 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PAMALEANA_PIANOA);
	p_pamThemePiano1 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PAMALEANA_PIANOB);
	p_pamThemePiano2 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PAMALEANA_PIANOC);
	p_pamThemePiano3 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PAMALEANA_PIANOD);
	p_pamThemePiano4 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PAMALEANA_PIANOE);
	p_pamThemePiano5 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PAMALEANA_PIANOF);
	p_pamThemePiano6 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PAMALEANA_PIANOG);
	p_pamThemePiano7 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PAMALEANA_PIANOH);
	p_pamThemePiano8 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PAMALEANA_PIANOI);
	p_pamThemePiano9 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PAMALEANA_PIANOJ);

	p_pamThemeContrabass0 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PAMALEANA_CONTRABASSA);
	p_pamThemeContrabass1 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PAMALEANA_CONTRABASSB);
	p_pamThemeContrabass2 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PAMALEANA_CONTRABASSC);
	p_pamThemeContrabass3 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PAMALEANA_CONTRABASSD);
	p_pamThemeContrabass4 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PAMALEANA_CONTRABASSE);
	p_pamThemeContrabass5 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PAMALEANA_CONTRABASSF);
	p_pamThemeContrabass7 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PAMALEANA_CONTRABASSH);
	p_pamThemeContrabass8 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PAMALEANA_CONTRABASSI);
	p_pamThemeContrabass9 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PAMALEANA_CONTRABASSJ);

	p_pamThemeViolin0 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PAMALEANA_VIOLINA);
	p_pamThemeViolin1 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PAMALEANA_VIOLINB);
	p_pamThemeViolin2 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PAMALEANA_VIOLINC);
	p_pamThemeViolin3 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PAMALEANA_VIOLIND);
	p_pamThemeViolin4 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PAMALEANA_VIOLINE);
	p_pamThemeViolin5 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PAMALEANA_VIOLINF);
	p_pamThemeViolin7 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PAMALEANA_VIOLINH);
	p_pamThemeViolin8 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PAMALEANA_VIOLINI);
	p_pamThemeViolin9 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PAMALEANA_VIOLINJ);

	p_pamThemeMarimba0 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PAMALEANA_MARIMBAA);
	p_pamThemeMarimba1 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PAMALEANA_MARIMBAB);
	p_pamThemeMarimba2 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PAMALEANA_MARIMBAC);
	p_pamThemeMarimba3 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PAMALEANA_MARIMBAD);
	p_pamThemeMarimba4 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PAMALEANA_MARIMBAE);
	p_pamThemeMarimba5 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PAMALEANA_MARIMBAF);
	p_pamThemeMarimba7 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PAMALEANA_MARIMBAH);
	p_pamThemeMarimba8 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PAMALEANA_MARIMBAI);
	p_pamThemeMarimba9 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PAMALEANA_MARIMBAJ);

	p_pamThemeWavetable0 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PAMALEANA_WAVETABLEA);
	p_pamThemeWavetable1 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PAMALEANA_WAVETABLEB);
	p_pamThemeWavetable2 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PAMALEANA_WAVETABLEC);
	p_pamThemeWavetable3 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PAMALEANA_WAVETABLED);
	p_pamThemeWavetable4 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PAMALEANA_WAVETABLEE);
	p_pamThemeWavetable5 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PAMALEANA_WAVETABLEF);
	p_pamThemeWavetable6 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PAMALEANA_WAVETABLEG);
	p_pamThemeWavetable7 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PAMALEANA_WAVETABLEH);
	p_pamThemeWavetable8 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PAMALEANA_WAVETABLEI);
	p_pamThemeWavetable9 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PAMALEANA_WAVETABLEJ);

	p_pamThemeAMSynth0 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PAMALEANA_AMSYNTHA);
	p_pamThemeAMSynth1 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PAMALEANA_AMSYNTHB);
	p_pamThemeAMSynth2 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PAMALEANA_AMSYNTHC);
	p_pamThemeAMSynth3 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PAMALEANA_AMSYNTHD);
	p_pamThemeAMSynth4 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PAMALEANA_AMSYNTHE);
	p_pamThemeAMSynth5 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PAMALEANA_AMSYNTHF);
	p_pamThemeAMSynth6 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PAMALEANA_AMSYNTHG);
	p_pamThemeAMSynth7 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PAMALEANA_AMSYNTHH);
	p_pamThemeAMSynth8 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PAMALEANA_AMSYNTHI);
	p_pamThemeAMSynth9 = MM_COMMON_preloadMusicFile(MM_COMMON_MUSICPATH_PAMALEANA_AMSYNTHJ);

	if(p_pamThemePiano0 != -1 && MM_COMMON_musicAssignBuffer(p_pamThemePiano0, 0)) MM_COMMON_musicChannelOn(false, 0);
	if(p_pamThemeContrabass0 != -1 && MM_COMMON_musicAssignBuffer(p_pamThemeContrabass0, 1)) MM_COMMON_musicChannelOn(false, 1);
	if(p_pamThemeViolin0 != -1 && MM_COMMON_musicAssignBuffer(p_pamThemeViolin0, 2)) MM_COMMON_musicChannelOn(false, 2);
	if(p_pamThemeMarimba0 != -1 && MM_COMMON_musicAssignBuffer(p_pamThemeMarimba0, 3)) MM_COMMON_musicChannelOn(false, 3);
	if(p_pamThemeWavetable0 != -1 && MM_COMMON_musicAssignBuffer(p_pamThemeWavetable0, 4)) MM_COMMON_musicChannelOn(false, 4);
	if(p_pamThemeAMSynth0 != -1 && MM_COMMON_musicAssignBuffer(p_pamThemeAMSynth0, 5)) MM_COMMON_musicChannelOn(false, 5);

	p_pamThemeIteration = 0;
}

void MM_COMMON_THEME_PAMALEANA_updateTheme()
{
	if(!PLEX_isSoundPlaying(0))
	{
		switch(p_pamThemeIteration)
		{
			case 0:
				if(p_pamThemePiano1 != -1 && MM_COMMON_musicAssignBuffer(p_pamThemePiano1, 0)) MM_COMMON_musicChannelOn(false, 0);
				if(p_pamThemeContrabass1 != -1 && MM_COMMON_musicAssignBuffer(p_pamThemeContrabass1, 1)) MM_COMMON_musicChannelOn(false, 1);
				if(p_pamThemeViolin1 != -1 && MM_COMMON_musicAssignBuffer(p_pamThemeViolin1, 2)) MM_COMMON_musicChannelOn(false, 2);
				if(p_pamThemeMarimba1 != -1 && MM_COMMON_musicAssignBuffer(p_pamThemeMarimba1, 3)) MM_COMMON_musicChannelOn(false, 3);
				if(p_pamThemeWavetable1 != -1 && MM_COMMON_musicAssignBuffer(p_pamThemeWavetable1, 4)) MM_COMMON_musicChannelOn(false, 4);
				if(p_pamThemeAMSynth1 != -1 && MM_COMMON_musicAssignBuffer(p_pamThemeAMSynth1, 5)) MM_COMMON_musicChannelOn(false, 5);
			break;

			case 1:
				if(p_pamThemePiano2 != -1 && MM_COMMON_musicAssignBuffer(p_pamThemePiano2, 0)) MM_COMMON_musicChannelOn(false, 0);
				if(p_pamThemeContrabass2 != -1 && MM_COMMON_musicAssignBuffer(p_pamThemeContrabass2, 1)) MM_COMMON_musicChannelOn(false, 1);
				if(p_pamThemeViolin2 != -1 && MM_COMMON_musicAssignBuffer(p_pamThemeViolin2, 2)) MM_COMMON_musicChannelOn(false, 2);
				if(p_pamThemeMarimba2 != -1 && MM_COMMON_musicAssignBuffer(p_pamThemeMarimba2, 3)) MM_COMMON_musicChannelOn(false, 3);
				if(p_pamThemeWavetable2 != -1 && MM_COMMON_musicAssignBuffer(p_pamThemeWavetable2, 4)) MM_COMMON_musicChannelOn(false, 4);
				if(p_pamThemeAMSynth2 != -1 && MM_COMMON_musicAssignBuffer(p_pamThemeAMSynth2, 5)) MM_COMMON_musicChannelOn(false, 5);
			break;

			case 2:
				if(p_pamThemePiano3 != -1 && MM_COMMON_musicAssignBuffer(p_pamThemePiano3, 0)) MM_COMMON_musicChannelOn(false, 0);
				if(p_pamThemeContrabass3 != -1 && MM_COMMON_musicAssignBuffer(p_pamThemeContrabass3, 1)) MM_COMMON_musicChannelOn(false, 1);
				if(p_pamThemeViolin3 != -1 && MM_COMMON_musicAssignBuffer(p_pamThemeViolin3, 3)) MM_COMMON_musicChannelOn(false, 2);
				if(p_pamThemeMarimba3 != -1 && MM_COMMON_musicAssignBuffer(p_pamThemeMarimba3, 3)) MM_COMMON_musicChannelOn(false, 3);
				if(p_pamThemeWavetable3 != -1 && MM_COMMON_musicAssignBuffer(p_pamThemeWavetable3, 4)) MM_COMMON_musicChannelOn(false, 4);
				if(p_pamThemeAMSynth3 != -1 && MM_COMMON_musicAssignBuffer(p_pamThemeAMSynth3, 5)) MM_COMMON_musicChannelOn(false, 5);
			break;

			case 3:
				if(p_pamThemePiano4 != -1 && MM_COMMON_musicAssignBuffer(p_pamThemePiano4, 0)) MM_COMMON_musicChannelOn(false, 0);
				if(p_pamThemeContrabass4 != -1 && MM_COMMON_musicAssignBuffer(p_pamThemeContrabass4, 1)) MM_COMMON_musicChannelOn(false, 1);
				if(p_pamThemeViolin4 != -1 && MM_COMMON_musicAssignBuffer(p_pamThemeViolin4, 4)) MM_COMMON_musicChannelOn(false, 2);
				if(p_pamThemeMarimba4 != -1 && MM_COMMON_musicAssignBuffer(p_pamThemeMarimba4, 4)) MM_COMMON_musicChannelOn(false, 3);
				if(p_pamThemeWavetable4 != -1 && MM_COMMON_musicAssignBuffer(p_pamThemeWavetable4, 4)) MM_COMMON_musicChannelOn(false, 4);
				if(p_pamThemeAMSynth4 != -1 && MM_COMMON_musicAssignBuffer(p_pamThemeAMSynth4, 5)) MM_COMMON_musicChannelOn(false, 5);
			break;

			case 4:
				if(p_pamThemePiano5 != -1 && MM_COMMON_musicAssignBuffer(p_pamThemePiano5, 0)) MM_COMMON_musicChannelOn(false, 0);
				if(p_pamThemeContrabass5 != -1 && MM_COMMON_musicAssignBuffer(p_pamThemeContrabass5, 1)) MM_COMMON_musicChannelOn(false, 1);
				if(p_pamThemeViolin5 != -1 && MM_COMMON_musicAssignBuffer(p_pamThemeViolin5, 2)) MM_COMMON_musicChannelOn(false, 2);
				if(p_pamThemeMarimba5 != -1 && MM_COMMON_musicAssignBuffer(p_pamThemeMarimba5, 3)) MM_COMMON_musicChannelOn(false, 3);
				if(p_pamThemeWavetable5 != -1 && MM_COMMON_musicAssignBuffer(p_pamThemeWavetable5, 4)) MM_COMMON_musicChannelOn(false, 4);
				if(p_pamThemeAMSynth5 != -1 && MM_COMMON_musicAssignBuffer(p_pamThemeAMSynth5, 5)) MM_COMMON_musicChannelOn(false, 5);
			break;

			case 5:
				if(p_pamThemePiano6 != -1 && MM_COMMON_musicAssignBuffer(p_pamThemePiano6, 0)) MM_COMMON_musicChannelOn(false, 0);
				if(p_pamThemeWavetable6 != -1 && MM_COMMON_musicAssignBuffer(p_pamThemeWavetable6, 4)) MM_COMMON_musicChannelOn(false, 4);
				if(p_pamThemeAMSynth6 != -1 && MM_COMMON_musicAssignBuffer(p_pamThemeAMSynth6, 5)) MM_COMMON_musicChannelOn(false, 5);
			break;

			case 6:
				if(p_pamThemePiano7 != -1 && MM_COMMON_musicAssignBuffer(p_pamThemePiano7, 0)) MM_COMMON_musicChannelOn(false, 0);
				if(p_pamThemeContrabass7 != -1 && MM_COMMON_musicAssignBuffer(p_pamThemeContrabass7, 1)) MM_COMMON_musicChannelOn(false, 1);
				if(p_pamThemeViolin7 != -1 && MM_COMMON_musicAssignBuffer(p_pamThemeViolin7, 2)) MM_COMMON_musicChannelOn(false, 2);
				if(p_pamThemeMarimba7 != -1 && MM_COMMON_musicAssignBuffer(p_pamThemeMarimba7, 3)) MM_COMMON_musicChannelOn(false, 3);
				if(p_pamThemeWavetable7 != -1 && MM_COMMON_musicAssignBuffer(p_pamThemeWavetable7, 4)) MM_COMMON_musicChannelOn(false, 4);
				if(p_pamThemeAMSynth7 != -1 && MM_COMMON_musicAssignBuffer(p_pamThemeAMSynth7, 5)) MM_COMMON_musicChannelOn(false, 5);
			break;

			case 7:
				if(p_pamThemePiano8 != -1 && MM_COMMON_musicAssignBuffer(p_pamThemePiano8, 0)) MM_COMMON_musicChannelOn(false, 0);
				if(p_pamThemeContrabass8 != -1 && MM_COMMON_musicAssignBuffer(p_pamThemeContrabass8, 1)) MM_COMMON_musicChannelOn(false, 1);
				if(p_pamThemeViolin8 != -1 && MM_COMMON_musicAssignBuffer(p_pamThemeViolin8, 2)) MM_COMMON_musicChannelOn(false, 2);
				if(p_pamThemeMarimba8 != -1 && MM_COMMON_musicAssignBuffer(p_pamThemeMarimba8, 3)) MM_COMMON_musicChannelOn(false, 3);
				if(p_pamThemeWavetable8 != -1 && MM_COMMON_musicAssignBuffer(p_pamThemeWavetable8, 4)) MM_COMMON_musicChannelOn(false, 4);
				if(p_pamThemeAMSynth8 != -1 && MM_COMMON_musicAssignBuffer(p_pamThemeAMSynth8, 5)) MM_COMMON_musicChannelOn(false, 5);
			break;

			case 8:
				if(p_pamThemePiano9 != -1 && MM_COMMON_musicAssignBuffer(p_pamThemePiano9, 0)) MM_COMMON_musicChannelOn(false, 0);
				if(p_pamThemeContrabass9 != -1 && MM_COMMON_musicAssignBuffer(p_pamThemeContrabass9, 1)) MM_COMMON_musicChannelOn(false, 1);
				if(p_pamThemeViolin9 != -1 && MM_COMMON_musicAssignBuffer(p_pamThemeViolin9, 2)) MM_COMMON_musicChannelOn(false, 2);
				if(p_pamThemeMarimba9 != -1 && MM_COMMON_musicAssignBuffer(p_pamThemeMarimba9, 3)) MM_COMMON_musicChannelOn(false, 3);
				if(p_pamThemeWavetable9 != -1 && MM_COMMON_musicAssignBuffer(p_pamThemeWavetable9, 4)) MM_COMMON_musicChannelOn(false, 4);
				if(p_pamThemeAMSynth9 != -1 && MM_COMMON_musicAssignBuffer(p_pamThemeAMSynth9, 5)) MM_COMMON_musicChannelOn(false, 5);
			break;
		};

		p_pamThemeIteration = (p_pamThemeIteration + 1) % 9;
	}
}

// getters ------------------------------------------------------------------------------------------------------------------

PLEX_FAKESTRING_50 MM_COMMON_THEME_pamaleanaThemeStr()
{
	return p_pamaleanaThemeStr;
}
