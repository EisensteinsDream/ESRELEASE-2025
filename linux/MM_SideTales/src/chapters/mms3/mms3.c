#include "chapters/mms3.h"

static size_t p_phase = 0;

static size_t p_chapter3SpriteTex = 0;

static size_t p_tvShowTex = 0;

// outro

void MMS3_clearBackTextures()
{
	MMS3_freeSection1();
	MMS3_freeSection2();
	MMS3_freeSection3();
	MMS3_freeSection4();
	MMS3_freeSection5();
}

// scenes

void MMS3_startChapter()
{
	p_phase = 0;

	p_chapter3SpriteTex = PLEX_loadTextureFromFileOrHeaderless(512, 2048, 255, 255, 255, 255, 0, MMS3_FILEPATH_TEX_CHAPTER3SPRITEPLATE, MMS3_FILEPATH_HEADERLESS_CHAPTER3SPRITEPLATE);

	p_tvShowTex = PLEX_loadTextureFromFileOrHeaderless(5759, 256, 255, 255, 255, 255, 0, MMS3_FILEPATH_TEX_TVSHOW, MMS3_FILEPATH_HEADERLESS_TVSHOW);

	MMS3_createSection1(p_chapter3SpriteTex);
	MMS3_createSection2(p_chapter3SpriteTex);
	MMS3_createSection3(p_chapter3SpriteTex);
	MMS3_createSection4(p_chapter3SpriteTex, p_tvShowTex);
	MMS3_createSection5(p_chapter3SpriteTex);
}

bool MMS3_updateChapter(const size_t pamaleanaSpriteTex, const size_t cubicleBackdrop, const size_t venariusSpriteTex, const size_t extraplocanSpriteTex, const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow)
{
	switch(p_phase)
	{
		case 0:
			if(!PLEX_inSpriteTheater()) MMS3_startSceneA(p_chapter3SpriteTex, fontPlate, label, bubble, arrow);
			PLEX_updateSpriteTheater(PLEX_getGameTime());
			if(PLEX_isSpriteTheaterOver()){ ++p_phase; PLEX_endSpriteTheater(); }
		break;

		case 1:
			if(!PLEX_inSpriteTheater()) MMS3_startSceneB(p_chapter3SpriteTex, fontPlate, label, bubble, arrow);
			PLEX_updateSpriteTheater(PLEX_getGameTime());
			if(PLEX_isSpriteTheaterOver()){ ++p_phase; PLEX_endSpriteTheater(); }
		break;

		case 2:
			if(!PLEX_inSpriteTheater()) MMS3_startSceneC(fontPlate, label, bubble, arrow);
			PLEX_updateSpriteTheater(PLEX_getGameTime());
			if(PLEX_isSpriteTheaterOver()){ ++p_phase; PLEX_endSpriteTheater(); }
		break;

		case 3:
			if(!PLEX_inSpriteTheater()) MMS3_startSceneD(fontPlate, label, bubble, arrow);
			PLEX_updateSpriteTheater(PLEX_getGameTime());
			if(PLEX_isSpriteTheaterOver()){ ++p_phase; PLEX_endSpriteTheater(); }
		break;

		case 4:
			if(!PLEX_inSpriteTheater()) MMS3_startSceneE(fontPlate, label, bubble, arrow);
			PLEX_updateSpriteTheater(PLEX_getGameTime());
			if(PLEX_isSpriteTheaterOver()){ ++p_phase; PLEX_endSpriteTheater(); }
		break;

		case 5:
			if(!PLEX_inSpriteTheater()) MMS3_startSceneF(fontPlate, label, bubble, arrow);
			PLEX_updateSpriteTheater(PLEX_getGameTime());
			if(PLEX_isSpriteTheaterOver()){ ++p_phase; PLEX_endSpriteTheater(); }
		break;

		case 6:
			if(!PLEX_inSpriteTheater()) MMS3_startSceneG(fontPlate, label, bubble, arrow);
			PLEX_updateSpriteTheater(PLEX_getGameTime());
			if(PLEX_isSpriteTheaterOver()){ ++p_phase; PLEX_endSpriteTheater(); }
		break;

		case 7:
			if(!PLEX_inSpriteTheater()) MMS3_startSceneH(fontPlate, label, bubble, arrow);
			PLEX_updateSpriteTheater(PLEX_getGameTime());
			if(PLEX_isSpriteTheaterOver()){ ++p_phase; PLEX_endSpriteTheater(); }
		break;

		case 8:
			if(!PLEX_inSpriteTheater()) MMS3_startSceneI(fontPlate, label, bubble, arrow);
			PLEX_updateSpriteTheater(PLEX_getGameTime());
			if(PLEX_isSpriteTheaterOver()){ ++p_phase; PLEX_endSpriteTheater(); }
		break;

		case 9:
			if(!PLEX_inSpriteTheater()) MMS3_startSceneJ(fontPlate, label, bubble, arrow);
			PLEX_updateSpriteTheater(PLEX_getGameTime());
			if(PLEX_isSpriteTheaterOver()){ ++p_phase; PLEX_endSpriteTheater(); }
		break;

		case 10:
			if(!PLEX_inSpriteTheater()) MMS3_startSceneK(fontPlate, label, bubble, arrow);
			PLEX_updateSpriteTheater(PLEX_getGameTime());
			if(PLEX_isSpriteTheaterOver()){ ++p_phase; PLEX_endSpriteTheater(); }
		break;

		case 11:
			if(!PLEX_inSpriteTheater()) MMS3_startSceneL(fontPlate, label, bubble, arrow);
			PLEX_updateSpriteTheater(PLEX_getGameTime());
			if(PLEX_isSpriteTheaterOver()){ ++p_phase; PLEX_endSpriteTheater(); }
		break;

		case 12:
			if(!PLEX_inSpriteTheater()) MMS3_startSceneM(fontPlate, label, bubble, arrow);
			PLEX_updateSpriteTheater(PLEX_getGameTime());
			if(PLEX_isSpriteTheaterOver()){ ++p_phase; PLEX_endSpriteTheater(); }
		break;

		case 13:
			if(!PLEX_inSpriteTheater()) MMS3_startSceneN(fontPlate, label, bubble, arrow);
			PLEX_updateSpriteTheater(PLEX_getGameTime());
			if(PLEX_isSpriteTheaterOver()){ ++p_phase; PLEX_endSpriteTheater(); }
		break;

		case 14:
			if(!PLEX_inSpriteTheater()) MMS3_startSceneO(fontPlate, label, bubble, arrow);
			PLEX_updateSpriteTheater(PLEX_getGameTime());
			if(PLEX_isSpriteTheaterOver()){ ++p_phase; PLEX_endSpriteTheater(); }
		break;

		case 15:
			if(!PLEX_inSpriteTheater()) MMS3_startSceneP(fontPlate, label, bubble, arrow);
			PLEX_updateSpriteTheater(PLEX_getGameTime());
			if(PLEX_isSpriteTheaterOver()){ ++p_phase; PLEX_endSpriteTheater(); }
		break;

		case 16:
			if(!PLEX_inSpriteTheater()) MMS3_startSceneQ(fontPlate, label, bubble, arrow);
			PLEX_updateSpriteTheater(PLEX_getGameTime());
			if(PLEX_isSpriteTheaterOver()){ ++p_phase; PLEX_endSpriteTheater(); }
		break;

		case 17:
			if(!PLEX_inSpriteTheater()) MMS3_startSceneR(fontPlate, label, bubble, arrow);
			PLEX_updateSpriteTheater(PLEX_getGameTime());
			if(PLEX_isSpriteTheaterOver()){ ++p_phase; PLEX_endSpriteTheater(); }
		break;

		case 18:
			if(!PLEX_inSpriteTheater()) MMS3_startSceneS(fontPlate, label, bubble, arrow);
			PLEX_updateSpriteTheater(PLEX_getGameTime());
			if(PLEX_isSpriteTheaterOver()){ ++p_phase; PLEX_endSpriteTheater(); }
		break;

		case 19:
			if(!PLEX_inSpriteTheater()) MMS3_startSceneT(fontPlate, label, bubble, arrow);
			PLEX_updateSpriteTheater(PLEX_getGameTime());
			if(PLEX_isSpriteTheaterOver()){ ++p_phase; PLEX_endSpriteTheater(); }
		break;

		case 20:
			if(!PLEX_inSpriteTheater()) MMS3_startSceneU(fontPlate, label, bubble, arrow);
			PLEX_updateSpriteTheater(PLEX_getGameTime());
			if(PLEX_isSpriteTheaterOver()){ ++p_phase; PLEX_endSpriteTheater(); }
		break;

		case 21:
			if(!PLEX_inSpriteTheater()) MMS3_outro(pamaleanaSpriteTex, cubicleBackdrop, venariusSpriteTex, extraplocanSpriteTex, fontPlate, label, bubble, arrow);
			PLEX_updateSpriteTheater(PLEX_getGameTime());
			if(PLEX_isSpriteTheaterOver()){ ++p_phase; PLEX_endSpriteTheater(); }
		break;

		default: return false;
	};

	return true;
}

void MMS3_endChapter()
{
	MMS3_finalFreeSection1();
	MMS3_finalFreeSection2();
	MMS3_finalFreeSection3();
	MMS3_finalFreeSection4();
	MMS3_finalFreeSection5();

	MMS3_clearBackTextures();

	PLEX_destroyTexture(p_chapter3SpriteTex);

	if(p_tvShowTex) PLEX_destroyTexture(p_tvShowTex);

	p_chapter3SpriteTex = 0;

	p_tvShowTex = 0;
}
