#include "chapters/mms1.h"

// NOTE: this has not been split into multiple source files because it is less than 1000 lines

static size_t p_phase = 0;

static size_t p_chapter1SpriteTex = 0;

static size_t p_mibsOffice = 0;

static size_t p_levineManor = 0;
static size_t p_levineOffice = 0;

static size_t p_outsideSchool = 0;
static size_t p_outsideSchoolBlurry = 0;

static size_t p_mcConnimon = 0;

static size_t p_pamaleana2 = 0;
static size_t p_kids = 0;

static PLEX_SPRITE* p_mcConnimonSprite = NULL;

static PLEX_SPRITE* p_pamaleanaSprite2 = NULL;
static PLEX_SPRITE* p_kidsSprite = NULL;

static void p_mcConnTalk(const char* message)
{
	PLEX_addSpriteTheaterSlide(200, 150, 50, message, p_mcConnimon, 0, true);
}

static void p_pamCarTalkWait(const char* message, const uint64_t by)
{
	PLEX_addSpriteTheaterSlide(29, 180, 255, message, p_pamaleana2, by, true);
}

static void p_pamCarTalk(const char* message)
{
	p_pamCarTalkWait(message, 0);
}

static void p_kidsTalk(const char* message)
{
	PLEX_addSpriteTheaterSlide(180, 180, 180, message, p_kids, 0, true);
}

void MMS1_startChapter()
{
	p_phase = 0;

	p_chapter1SpriteTex = PLEX_loadTextureFromFileOrHeaderless(320, 960, 255, 255, 255, 255, 0, MMS1_FILEPATH_TEX_CHAPTER1SPRITEPLATE, MMS1_FILEPATH_HEADERLESS_CHAPTER1SPRITEPLATE);

	p_mibsOffice = PLEX_loadTextureFromFileOrHeaderless(3840, 1644, 255, 255, 255, 255, 0, MMS1_FILEPATH_TEX_MIBSOFFICE, MMS1_FILEPATH_HEADERLESS_MIBSOFFICE);

	p_levineManor = PLEX_loadTextureFromFileOrHeaderless(3840, 1644, 255, 255, 255, 255, 0, MMS1_FILEPATH_TEX_LEVINEMANOR, MMS1_FILEPATH_HEADERLESS_LEVINEMANOR);
	p_levineOffice = PLEX_loadTextureFromFileOrHeaderless(3840, 1644, 255, 255, 255, 255, 0, MMS1_FILEPATH_TEX_LEVINEOFFICE, MMS1_FILEPATH_HEADERLESS_LEVINEOFFICE);

	p_outsideSchool = PLEX_loadTextureFromFileOrHeaderless(3840, 1644, 255, 255, 255, 255, 0, MMS1_FILEPATH_TEX_OUTSIDESCHOOL, MMS1_FILEPATH_HEADERLESS_OUTSIDESCHOOL);
	p_outsideSchoolBlurry = PLEX_loadTextureFromFileOrHeaderless(3840, 1644, 255, 255, 255, 255, 0, MMS1_FILEPATH_TEX_OUTSIDESCHOOLBLURRY, MMS1_FILEPATH_HEADERLESS_OUTSIDESCHOOLBLURRY);
}

static void p_startIntroA(const size_t pamaleanaSpriteTex, const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow)
{
	PLEX_ANIMATION_PLATE mcConnimonPlate = PLEX_createAnimationPlate(0.1, 0.0667, p_chapter1SpriteTex);

	PLEX_ANIMATION* pamStartAnim = NULL;
	PLEX_ANIMATION* pamJoyAnim = NULL;
	PLEX_ANIMATION* pamSadAnim = NULL;

	PLEX_ANIMATION* mcConnimonAnim = NULL;

	p_mcConnimonSprite = PLEX_genSprite(&mcConnimonPlate);

	MMS_genSpritePamaleana(pamaleanaSpriteTex);

	PLEX_startSpriteTheater(MMS1_LANGUAGE_SETTING_MIBS, p_mibsOffice, 0, 0, 400, 100, 255, 255, 255, fontPlate, label, bubble, arrow, PLEX_getGameTime());

	MMS_addPamaleanaAnimation(1);

	pamStartAnim = MMS_getPamaleanaAnimation(0);

	PLEX_addAnimationFrame(50, pamStartAnim);

	MMS_addPamaleanaAnimation(2000);

	pamJoyAnim = MMS_getPamaleanaAnimation(1);

	PLEX_addAnimationFrame(51, pamJoyAnim);
	PLEX_addAnimationFrame(52, pamJoyAnim);
	PLEX_addAnimationFrame(51, pamJoyAnim);
	PLEX_addAnimationFrame(53, pamJoyAnim);

	MMS_addPamaleanaAnimation(1);

	pamSadAnim = MMS_getPamaleanaAnimation(2);

	PLEX_addAnimationFrame(54, pamSadAnim);

	PLEX_addAnimation(p_mcConnimonSprite, 1, PLEX_getGameTime());

	mcConnimonAnim = PLEX_getAnimation(0, p_mcConnimonSprite);

	PLEX_addAnimationFrame(80, mcConnimonAnim);

	MMS_createActorPamaleana(PLEX_WIDTHUNITMAX()/2 - 1, PLEX_HEIGHTUNITMAX() * 0.75 + 1, false);

	p_mcConnimon = PLEX_createActor(p_mcConnimonSprite, 0, PLEX_convRect(PLEX_convPoint(PLEX_WIDTHUNITMAX()/2 - 1, PLEX_HEIGHTUNITMAX() * 0.75 - 6), PLEX_convDimens(2, 4)), false);

	PLEX_changeSpriteTheaterMusic((size_t)MM_COMMON_THEMEID_MAIN);

	MMS_narration(MMS1_LANGUAGE_INTROA_LINE1);

	PLEX_changeSpriteTheaterMusic((size_t)MM_COMMON_THEMEID_PAMALEANA);

	MMS_pamNarration(MMS1_LANGUAGE_INTROA_LINE2);

	p_mcConnTalk(MMS1_LANGUAGE_INTROA_LINE3);

	MMS_pamTalk(MMS1_LANGUAGE_INTROA_LINE4);

	MMS_pamTalk(MMS1_LANGUAGE_INTROA_LINE5);

	MMS_pamTalk(MMS1_LANGUAGE_INTROA_LINE6);

	MMS_pamChangeAnimation(1);

	p_mcConnTalk(MMS1_LANGUAGE_INTROA_LINE7);

	MMS_pamChangeAnimation(2);

	p_mcConnTalk(MMS1_LANGUAGE_INTROA_LINE8);

	MMS_pamChangeAnimation(0);

	p_mcConnTalk(MMS1_LANGUAGE_INTROA_LINE9);

	p_mcConnTalk(MMS1_LANGUAGE_INTROA_LINE10);

	MMS_pamTalk(MMS1_LANGUAGE_INTROA_LINE11);

	MMS_pamChangeAnimation(1);

	p_mcConnTalk(MMS1_LANGUAGE_INTROA_LINE12);

	MMS_pamChangeAnimation(2);

	p_mcConnTalk(MMS1_LANGUAGE_INTROA_LINE13);
}

static void p_startIntroB(const size_t pamaleanaSpriteTex, const size_t levineSpriteTex, const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow)
{
	PLEX_ANIMATION* pamStudyAnim = NULL;
	PLEX_ANIMATION* pamStudyAngryAnim = NULL;
	PLEX_ANIMATION* pamStudyNoPhoneAnim = NULL;

	PLEX_ANIMATION* levineSitAnim = NULL;
	PLEX_ANIMATION* levineHangUpAnim = NULL;
	PLEX_ANIMATION* levineSitNoPhoneAnim = NULL;
	PLEX_ANIMATION* levineLeanForwardAnim = NULL;

	MMS_genSpritePamaleana(pamaleanaSpriteTex);
	MMS_genSpriteLevine(levineSpriteTex);

	// PAMALEANA ANIMATIONS

	MMS_addPamaleanaAnimation(1);

	pamStudyAnim = MMS_getPamaleanaAnimation(0);

	PLEX_addAnimationFrame(55, pamStudyAnim);

	MMS_addPamaleanaAnimation(1);

	pamStudyAngryAnim = MMS_getPamaleanaAnimation(1);

	PLEX_addAnimationFrame(57, pamStudyAngryAnim);

	MMS_addPamaleanaAnimation(1);

	pamStudyNoPhoneAnim = MMS_getPamaleanaAnimation(2);

	PLEX_addAnimationFrame(56, pamStudyNoPhoneAnim);

	// LEVINE ANIMATIONS

	MMS_addLevineAnimation(1);

	levineSitAnim = MMS_getLevineAnimation(0);

	PLEX_addAnimationFrame(5, levineSitAnim);

	MMS_addLevineAnimation(1000);

	levineHangUpAnim = MMS_getLevineAnimation(1);

	PLEX_addAnimationFrame(5, levineHangUpAnim);
	PLEX_addAnimationFrame(6, levineHangUpAnim);
	PLEX_addAnimationFrame(6, levineHangUpAnim);
	PLEX_addAnimationFrame(6, levineHangUpAnim);

	MMS_addLevineAnimation(1);

	levineSitNoPhoneAnim = MMS_getLevineAnimation(2);

	PLEX_addAnimationFrame(6, levineSitNoPhoneAnim);

	MMS_addLevineAnimation(1);

	levineLeanForwardAnim = MMS_getLevineAnimation(3);

	PLEX_addAnimationFrame(7, levineLeanForwardAnim);

	// START SPRITE THEATER

	PLEX_startSpriteTheater(MMS1_LANGUAGE_SETTING_LEVINEMANOR, p_levineManor, 0, 0, 400, 100, 255, 255, 255, fontPlate, label, bubble, arrow, PLEX_getGameTime());

	MMS_createActorPamaleana(PLEX_WIDTHUNITMAX()/2, PLEX_HEIGHTUNITMAX() * 0.75 - 4, false);
	MMS_createActorLevine(PLEX_WIDTHUNITMAX()/2 - 1, PLEX_HEIGHTUNITMAX() * 0.5 - 1, true);

	PLEX_changeSpriteTheaterMusic((size_t)MM_COMMON_THEMEID_DAYTODAY);

	MMS_narration(MMS1_LANGUAGE_INTROB_LINE1);

	MMS_pamTalk(MMS1_LANGUAGE_INTROB_LINE2);

	PLEX_changeSpriteTheaterBackground(p_levineOffice, MMS1_LANGUAGE_SETTING_LEVINEOFFICE);
	MMS_pamHide();
	MMS_levineUnhide();

	MMS_levineTalk(MMS1_LANGUAGE_INTROB_LINE3);

	PLEX_changeSpriteTheaterBackground(p_levineManor, MMS1_LANGUAGE_SETTING_LEVINEMANOR);
	MMS_pamUnhide();
	MMS_levineHide();

	MMS_pamTalk(MMS1_LANGUAGE_INTROB_LINE4);

	PLEX_changeSpriteTheaterBackground(p_levineOffice, MMS1_LANGUAGE_SETTING_LEVINEOFFICE);
	MMS_pamHide();
	MMS_levineUnhide();

	MMS_levineTalk(MMS1_LANGUAGE_INTROB_LINE5);

	PLEX_changeSpriteTheaterBackground(p_levineManor, MMS1_LANGUAGE_SETTING_LEVINEMANOR);
	MMS_pamUnhide();
	MMS_levineHide();

	MMS_pamTalk(MMS1_LANGUAGE_INTROB_LINE6);

	PLEX_changeSpriteTheaterBackground(p_levineOffice, MMS1_LANGUAGE_SETTING_LEVINEOFFICE);
	MMS_pamHide();
	MMS_levineUnhide();

	MMS_levineTalk(MMS1_LANGUAGE_INTROB_LINE7);

	MMS_pamChangeAnimation(1);

	PLEX_changeSpriteTheaterBackground(p_levineManor, MMS1_LANGUAGE_SETTING_LEVINEMANOR);
	MMS_pamUnhide();
	MMS_levineHide();

	MMS_pamTalk(MMS1_LANGUAGE_INTROB_LINE8);

	PLEX_changeSpriteTheaterBackground(p_levineOffice, MMS1_LANGUAGE_SETTING_LEVINEOFFICE);
	MMS_pamHide();
	MMS_levineUnhide();

	MMS_levineTalk(MMS1_LANGUAGE_INTROB_LINE9);

	PLEX_changeSpriteTheaterBackground(p_levineManor, MMS1_LANGUAGE_SETTING_LEVINEMANOR);
	MMS_pamUnhide();
	MMS_levineHide();

	MMS_pamTalk(MMS1_LANGUAGE_INTROB_LINE10);

	MMS_levineChangeAnimation(1);

	PLEX_changeSpriteTheaterBackground(p_levineOffice, MMS1_LANGUAGE_SETTING_LEVINEOFFICE);
	MMS_pamHide();
	MMS_levineUnhide();

	MMS_levineTalk(MMS1_LANGUAGE_INTROB_LINE11);

	MMS_levineChangeAnimation(2);

	MMS_levineTalkWait(MMS1_LANGUAGE_INTROB_LINE12, 1000, false);

	MMS_levineChangeAnimation(3);

	MMS_levineTalk(MMS1_LANGUAGE_INTROB_LINE13);

	MMS_levineTalk(MMS1_LANGUAGE_INTROB_LINE14);

	MMS_levineTalk(MMS1_LANGUAGE_INTROB_LINE15);

	MMS_pamChangeAnimation(2);

	PLEX_changeSpriteTheaterBackground(p_levineManor, MMS1_LANGUAGE_SETTING_LEVINEMANOR);
	MMS_pamUnhide();
	MMS_levineHide();

	MMS_pamTalk(MMS1_LANGUAGE_INTROB_LINE16);
}

static void p_startIntroC(const size_t pamaleanaSpriteTex, const size_t venariusSpriteTex, const size_t extraplocanSpriteTex, const size_t cubicleBackdrop, const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow)
{
	MMS_startPamaleanasCubicle(pamaleanaSpriteTex, cubicleBackdrop, venariusSpriteTex, extraplocanSpriteTex, fontPlate, label, bubble, arrow);

	MMS_extrapTalk(MMS1_LANGUAGE_INTROC_LINE1);

	MMS_pamTalk(MMS1_LANGUAGE_INTROC_LINE2);

	MMS_extrapTalk(MMS1_LANGUAGE_INTROC_LINE3);

	MMS_pamTalk(MMS1_LANGUAGE_INTROC_LINE4);

	MMS_extrapTalk(MMS1_LANGUAGE_INTROC_LINE5);

	MMS_pamTalk(MMS1_LANGUAGE_INTROC_LINE6);

	MMS_extrapTalk(MMS1_LANGUAGE_INTROC_LINE7);

	MMS_pamTalk(MMS1_LANGUAGE_INTROC_LINE8);
}

static void p_startIntroD(const size_t pamaleanaSpriteTex, const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow)
{
	PLEX_ANIMATION_PLATE pamaleanaPlate2 = PLEX_createAnimationPlate(0.2, 0.03334, p_chapter1SpriteTex);
	PLEX_ANIMATION_PLATE kidsPlate = PLEX_createAnimationPlate(0.1, 0.03334, p_chapter1SpriteTex);

	PLEX_ANIMATION* pamInCarAnim = NULL;

	PLEX_ANIMATION* kidsShadowAnim = NULL;
	PLEX_ANIMATION* kidsAnim = NULL;

	p_pamaleanaSprite2 = PLEX_genSprite(&pamaleanaPlate2);
	p_kidsSprite = PLEX_genSprite(&kidsPlate);

	PLEX_addAnimation(p_pamaleanaSprite2, 1, PLEX_getGameTime());

	pamInCarAnim = PLEX_getAnimation(0, p_pamaleanaSprite2);

	PLEX_addAnimationFrame(75, pamInCarAnim);

	PLEX_addAnimation(p_kidsSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_kidsSprite, 1, PLEX_getGameTime());

	kidsShadowAnim = PLEX_getAnimation(0, p_kidsSprite);

	PLEX_addAnimationFrame(152, kidsShadowAnim);

	kidsAnim = PLEX_getAnimation(1, p_kidsSprite);

	PLEX_addAnimationFrame(153, kidsAnim);

	PLEX_startSpriteTheater(MMS1_LANGUAGE_SETTING_OUTSIDESCHOOLBLURRY, p_outsideSchoolBlurry, 0, 0, 400, 100, 255, 255, 255, fontPlate, label, bubble, arrow, PLEX_getGameTime());

	p_pamaleana2 = PLEX_createActor(p_pamaleanaSprite2, 0, PLEX_convRect(PLEX_convPoint(PLEX_WIDTHUNITMAX() * 0.75, PLEX_HEIGHTUNITMAX() * 0.5), PLEX_convDimens(4, 2)), false);

	p_kids = PLEX_createActor(p_kidsSprite, 0, PLEX_convRect(PLEX_convPoint(PLEX_WIDTHUNITMAX() * 0.75 + 4, PLEX_HEIGHTUNITMAX() * 0.5), PLEX_convDimens(2, 2)), false);

	PLEX_changeSpriteTheaterMusic(MM_COMMON_THEMEID_DREAM);

	MMS_narration(MMS1_LANGUAGE_INTROD_LINE1);

	p_pamCarTalk(MMS1_LANGUAGE_INTROD_LINE2);

	PLEX_changeSpriteTheaterMusic(MM_COMMON_THEMEID_DAYTODAY);

	PLEX_changeSpriteTheaterBackground(p_outsideSchool, MMS1_LANGUAGE_SETTING_OUTSIDESCHOOL);

	PLEX_changeActor(p_kids, 1);

	p_kidsTalk(MMS1_LANGUAGE_INTROD_LINE3);

	PLEX_hideActor(p_kids);

	PLEX_changeSpriteTheaterMusic(MM_COMMON_THEMEID_DREAM);

	PLEX_changeSpriteTheaterBackground(p_outsideSchoolBlurry, MMS1_LANGUAGE_SETTING_OUTSIDESCHOOLBLURRY);

	p_pamCarTalk(MMS1_LANGUAGE_INTROD_LINE4);

	PLEX_changeSpriteTheaterMusic(MM_COMMON_THEMEID_DAYTODAY);

	PLEX_changeSpriteTheaterBackground(p_outsideSchool, MMS1_LANGUAGE_SETTING_OUTSIDESCHOOL);

	p_pamCarTalkWait(MMS1_LANGUAGE_INTROD_LINE5, 3000);

	p_pamCarTalk(MMS1_LANGUAGE_INTROD_LINE6);
}

static void p_startOutro(const size_t pamaleanaSpriteTex, const size_t cubicleBackdrop, const size_t venariusSpriteTex, const size_t extraplocanSpriteTex, const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow)
{
	MMS_startPamaleanasCubicle(pamaleanaSpriteTex, cubicleBackdrop, venariusSpriteTex, extraplocanSpriteTex, fontPlate, label, bubble, arrow);

	PLEX_changeSpriteTheaterMusic((size_t)MM_COMMON_THEMEID_NEWSROOM);

	MMS_pamTalk(MMS1_LANGUAGE_OUTRO_LINE1);

	MMS_extrapTalk(MMS1_LANGUAGE_OUTRO_LINE2);

	MMS_pamChangeAnimation(2);

	MMS_pamTalk(MMS1_LANGUAGE_OUTRO_LINE3);

	MMS_pamChangeAnimation(0);

	MMS_extrapTalk(MMS1_LANGUAGE_OUTRO_LINE4);

	MMS_pamTalk(MMS1_LANGUAGE_OUTRO_LINE5);

	MMS_extrapTalk(MMS1_LANGUAGE_OUTRO_LINE6);

	MMS_pamTalk(MMS1_LANGUAGE_OUTRO_LINE7);

	MMS_extrapTalk(MMS1_LANGUAGE_OUTRO_LINE8);

	MMS_pamTalk(MMS1_LANGUAGE_OUTRO_LINE9);

	MMS_extrapTalk(MMS1_LANGUAGE_OUTRO_LINE10);

	MMS_extrapTalk(MMS1_LANGUAGE_OUTRO_LINE11);

	MMS_extrapTalk(MMS1_LANGUAGE_OUTRO_LINE12);

	MMS_pamTalk(MMS1_LANGUAGE_OUTRO_LINE13);

	MMS_extrapTalk(MMS1_LANGUAGE_OUTRO_LINE14);

	MMS_pamTalk(MMS1_LANGUAGE_OUTRO_LINE15);

	MMS_extrapTalk(MMS1_LANGUAGE_OUTRO_LINE16);

	MMS_extrapTalk(MMS1_LANGUAGE_OUTRO_LINE17);

	MMS_pamTalk(MMS1_LANGUAGE_OUTRO_LINE18);

	MMS_extrapTalk(MMS1_LANGUAGE_OUTRO_LINE19);

	MMS_pamTalk(MMS1_LANGUAGE_OUTRO_LINE20);

	MMS_extrapTalk(MMS1_LANGUAGE_OUTRO_LINE21);

	MMS_pamChangeAnimation(2);

	MMS_pamTalk(MMS1_LANGUAGE_OUTRO_LINE22);

	MMS_pamChangeAnimation(0);

	MMS_extrapTalk(MMS1_LANGUAGE_OUTRO_LINE23);

	PLEX_changeSpriteTheaterMusic((size_t)MM_COMMON_THEMEID_MAIN);

	MMS_narration(MMS1_LANGUAGE_OUTRO_LINE24);
}

bool MMS1_updateChapter(const size_t pamaleanaSpriteTex, const size_t levineSpriteTex, const size_t cubicleBackdrop, const size_t venariusSpriteTex, const size_t extraplocanSpriteTex, const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow)
{
	switch(p_phase)
	{
		case 0:
			if(!PLEX_inSpriteTheater()) p_startIntroA(pamaleanaSpriteTex, fontPlate, label, bubble, arrow);
			PLEX_updateSpriteTheater(PLEX_getGameTime());
			if(PLEX_isSpriteTheaterOver() || (MMS_MMS1MinigameUnlocked() && MM_COMMON_skipButton(fontPlate))){ ++p_phase; PLEX_endSpriteTheater(); }
		break;

		case 1:
			if(!PLEX_inSpriteTheater()) p_startIntroB(pamaleanaSpriteTex, levineSpriteTex, fontPlate, label, bubble, arrow);
			PLEX_updateSpriteTheater(PLEX_getGameTime());
			if(PLEX_isSpriteTheaterOver() || (MMS_MMS1MinigameUnlocked() && MM_COMMON_skipButton(fontPlate))){ ++p_phase; PLEX_endSpriteTheater(); }
		break;

		case 2:
			if(!PLEX_inSpriteTheater()) p_startIntroC(pamaleanaSpriteTex, venariusSpriteTex, extraplocanSpriteTex, cubicleBackdrop, fontPlate, label, bubble, arrow);
			PLEX_updateSpriteTheater(PLEX_getGameTime());
			if(PLEX_isSpriteTheaterOver() || (MMS_MMS1MinigameUnlocked() && MM_COMMON_skipButton(fontPlate))){ ++p_phase; PLEX_endSpriteTheater(); }
		break;

		case 3:
			if(!PLEX_inSpriteTheater()) p_startIntroD(pamaleanaSpriteTex, fontPlate, label, bubble, arrow);
			PLEX_updateSpriteTheater(PLEX_getGameTime());
			if(PLEX_isSpriteTheaterOver() || (MMS_MMS1MinigameUnlocked() && MM_COMMON_skipButton(fontPlate))){ ++p_phase; PLEX_endSpriteTheater(); }
		break;

		case 4:
			MMS_runMinigame1(p_chapter1SpriteTex, pamaleanaSpriteTex, cubicleBackdrop, venariusSpriteTex, extraplocanSpriteTex, fontPlate, label, bubble, arrow);
			++p_phase;
		break;

		case 5:
			if(!PLEX_inSpriteTheater()) p_startOutro(pamaleanaSpriteTex, cubicleBackdrop, venariusSpriteTex, extraplocanSpriteTex, fontPlate, label, bubble, arrow);
			PLEX_updateSpriteTheater(PLEX_getGameTime());
			if(PLEX_isSpriteTheaterOver() || (MMS_MMS2MinigameUnlocked() && MM_COMMON_skipButton(fontPlate))){ ++p_phase; PLEX_endSpriteTheater(); }
		break;

		default: return false;
	}

	return true;
}

void MMS1_endChapter()
{
	if(p_mcConnimonSprite != NULL) PLEX_destroySprite(&p_mcConnimonSprite);
	if(p_pamaleanaSprite2 != NULL) PLEX_destroySprite(&p_pamaleanaSprite2);
	if(p_kidsSprite != NULL) PLEX_destroySprite(&p_kidsSprite);

	PLEX_destroyTexture(p_chapter1SpriteTex);

	PLEX_destroyTexture(p_mibsOffice);

	PLEX_destroyTexture(p_levineManor);
	PLEX_destroyTexture(p_levineOffice);

	PLEX_destroyTexture(p_outsideSchool);
	PLEX_destroyTexture(p_outsideSchoolBlurry);

	p_chapter1SpriteTex = 0;

	p_mibsOffice = 0;

	p_levineManor = 0;
	p_levineOffice = 0;

	p_outsideSchool = 0;
	p_outsideSchoolBlurry = 0;
}
