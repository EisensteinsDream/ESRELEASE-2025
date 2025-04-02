#include "chapters/mms0.h"

static size_t p_stageBack = 0;

static int64_t p_actor = -1;
static int64_t p_director = -1;

static PLEX_SPRITE* p_actorSprite = NULL;
static PLEX_SPRITE* p_directorSprite = NULL;

static void p_actorVoice(const char* message)
{
	PLEX_addSpriteTheaterSlide(205, 108, 69, message, p_actor, 0, true);
}

static void p_directorVoiceWait(const char* message, const uint64_t wait)
{
	PLEX_addSpriteTheaterSlide(225, 220, 127, message, p_director, wait, false); // has a pause gag that does not pause song
}

static void p_directorVoice(const char* message)
{
	p_directorVoiceWait(message, 0);
}

void MMS_startIntroB(const size_t pamaleanaSpriteTex, const size_t chapter0SpriteTex, const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow)
{
	PLEX_ANIMATION_PLATE actorPlate = PLEX_createAnimationPlate(0.0625, 0.125, chapter0SpriteTex);
	PLEX_ANIMATION_PLATE directorPlate = PLEX_createAnimationPlate(0.0625, 0.125, chapter0SpriteTex);

	PLEX_ANIMATION* actorSkullAnim = NULL;
	PLEX_ANIMATION* actorScriptAnim = NULL;
	PLEX_ANIMATION* actorShameAnim = NULL;
	PLEX_ANIMATION* actorPrideAnim = NULL;
	PLEX_ANIMATION* actorStandingAnim = NULL;
	PLEX_ANIMATION* actorShockedAnim = NULL;

	PLEX_ANIMATION* pamaleanaRightAnim = NULL;
	PLEX_ANIMATION* pamaleanaOfferScript = NULL;

	PLEX_ANIMATION* directorLeftAnim = NULL;
	PLEX_ANIMATION* directorScriptAnim = NULL;

	p_actorSprite = PLEX_genSprite(&actorPlate);
	p_directorSprite = PLEX_genSprite(&directorPlate);

	MMS_genSpritePamaleana(pamaleanaSpriteTex);

	p_stageBack = PLEX_loadTextureFromFileOrHeaderless(3840, 1640, 255, 255, 255, 255, 0, MMS_FILEPATH_TEX_THEATERSTAGE, MMS_FILEPATH_HEADERLESS_THEATERSTAGE);

	// ACTOR SPRITE

	PLEX_addAnimation(p_actorSprite, 2000, PLEX_getGameTime());
	PLEX_addAnimation(p_actorSprite, 200, PLEX_getGameTime());
	PLEX_addAnimation(p_actorSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_actorSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_actorSprite, 1, PLEX_getGameTime());
	PLEX_addAnimation(p_actorSprite, 1, PLEX_getGameTime());

	actorSkullAnim = PLEX_getAnimation(0, p_actorSprite);
	actorScriptAnim = PLEX_getAnimation(1, p_actorSprite);
	actorShameAnim = PLEX_getAnimation(2, p_actorSprite);
	actorPrideAnim = PLEX_getAnimation(3, p_actorSprite);
	actorStandingAnim = PLEX_getAnimation(4, p_actorSprite);
	actorShockedAnim = PLEX_getAnimation(5, p_actorSprite);

	PLEX_addAnimationFrame(0, actorSkullAnim);
	PLEX_addAnimationFrame(1, actorSkullAnim);

	PLEX_addAnimationFrame(2, actorScriptAnim);
	PLEX_addAnimationFrame(3, actorScriptAnim);
	PLEX_addAnimationFrame(4, actorScriptAnim);
	PLEX_addAnimationFrame(5, actorScriptAnim);

	PLEX_addAnimationFrame(6, actorShameAnim);

	PLEX_addAnimationFrame(7, actorPrideAnim);

	PLEX_addAnimationFrame(8, actorStandingAnim);

	PLEX_addAnimationFrame(9, actorShockedAnim);

	// PAMALEANA SPRITE

	MMS_addPamaleanaAnimation(1);
	MMS_addPamaleanaAnimation(1);

	pamaleanaRightAnim = MMS_getPamaleanaAnimation(0);

	PLEX_addAnimationFrame(9, pamaleanaRightAnim);

	pamaleanaOfferScript = MMS_getPamaleanaAnimation(1);

	PLEX_addAnimationFrame(32, pamaleanaOfferScript);

	// DIRECTOR SPRITE

	PLEX_addAnimation(p_directorSprite, 1000, PLEX_getGameTime());
	PLEX_addAnimation(p_directorSprite, 500, PLEX_getGameTime());

	directorLeftAnim = PLEX_getAnimation(0, p_directorSprite);
	directorScriptAnim = PLEX_getAnimation(1, p_directorSprite);

	PLEX_addAnimationFrame(10, directorLeftAnim);
	PLEX_addAnimationFrame(11, directorLeftAnim);
	PLEX_addAnimationFrame(12, directorLeftAnim);
	PLEX_addAnimationFrame(13, directorLeftAnim);
	PLEX_addAnimationFrame(10, directorLeftAnim);
	PLEX_addAnimationFrame(11, directorLeftAnim);
	PLEX_addAnimationFrame(12, directorLeftAnim);
	PLEX_addAnimationFrame(13, directorLeftAnim);
	PLEX_addAnimationFrame(14, directorLeftAnim);
	PLEX_addAnimationFrame(15, directorLeftAnim);
	PLEX_addAnimationFrame(16, directorLeftAnim);
	PLEX_addAnimationFrame(17, directorLeftAnim);

	PLEX_addAnimationFrame(18, directorScriptAnim);
	PLEX_addAnimationFrame(19, directorScriptAnim);
	PLEX_addAnimationFrame(20, directorScriptAnim);
	PLEX_addAnimationFrame(21, directorScriptAnim);

	// START SPRITES

	PLEX_startSprite(PLEX_getGameTime(), p_actorSprite);
	PLEX_startSprite(PLEX_getGameTime(), p_directorSprite);

	// BEGIN SPRITE THEATER

	PLEX_startSpriteTheater(MMS_LANGUAGE_SETTING_COMMUNITYTHEATER, p_stageBack, 0, 0, 400, 100, 255, 255, 255, fontPlate, label, bubble, arrow, PLEX_getGameTime());

	// CREATE ACTORS

	MMS_createActorPamaleana(PLEX_WIDTHUNITMAX()/2 - 4, PLEX_HEIGHTUNITMAX() - 6, true);

	p_actor = PLEX_createActor(p_actorSprite, 0, PLEX_convRect(PLEX_convPoint(PLEX_WIDTHUNITMAX()/2 - 0.1, PLEX_HEIGHTUNITMAX() - 10), PLEX_convDimens(2, 4)), false);
	p_director = PLEX_createActor(p_directorSprite, 0, PLEX_convRect(PLEX_convPoint(PLEX_WIDTHUNITMAX()/2 + 4, PLEX_HEIGHTUNITMAX() - 6), PLEX_convDimens(2, 4)), true);

	// SPRITE THEATER EVENTS

	PLEX_changeSpriteTheaterMusic((size_t)MM_COMMON_THEMEID_COMEDY);

	p_actorVoice(MMS_LANGUAGE_INTROB_LINE1);

	PLEX_changeActor(p_actor, 1);

	p_actorVoice(MMS_LANGUAGE_INTROB_LINE2);

	MMS_pamUnhide();
	PLEX_changeActor(p_actor, 2);

	p_actorVoice(MMS_LANGUAGE_INTROB_LINE3);

	MMS_pamTalk(MMS_LANGUAGE_INTROB_LINE4);

	PLEX_changeActor(p_actor, 3);

	p_actorVoice(MMS_LANGUAGE_INTROB_LINE5);

	PLEX_unhideActor(p_director);

	PLEX_changeActor(p_actor, 4);

	p_directorVoice(MMS_LANGUAGE_INTROB_LINE6);

	MMS_pamTalk(MMS_LANGUAGE_INTROB_LINE7);

	PLEX_changeActor(p_actor, 5);

	p_actorVoice(MMS_LANGUAGE_INTROB_LINE8);

	PLEX_changeActor(p_actor, 4);

	MMS_pamTalk(MMS_LANGUAGE_INTROB_LINE9);

	p_actorVoice(MMS_LANGUAGE_INTROB_LINE10);

	p_directorVoice(MMS_LANGUAGE_INTROB_LINE11);

	p_actorVoice(MMS_LANGUAGE_INTROB_LINE12);

	p_directorVoice(MMS_LANGUAGE_INTROB_LINE13);

	MMS_pamTalk(MMS_LANGUAGE_INTROB_LINE14);

	p_directorVoice(MMS_LANGUAGE_INTROB_LINE15);

	MMS_pamTalk(MMS_LANGUAGE_INTROB_LINE16);

	p_directorVoiceWait(MMS_LANGUAGE_INTROB_LINE17, 1000);

	MMS_pamChangeAnimation(1);

	MMS_pamTalk(MMS_LANGUAGE_INTROB_LINE18);

	MMS_pamChangeAnimation(0);

	PLEX_changeActor(p_director, 1);

	p_directorVoice(MMS_LANGUAGE_INTROB_LINE19);

	MMS_pamTalk(MMS_LANGUAGE_INTROB_LINE20);

	p_directorVoice(MMS_LANGUAGE_INTROB_LINE21);

	MMS_pamTalk(MMS_LANGUAGE_INTROB_LINE22);

	PLEX_changeActor(p_director, 0);

	p_directorVoice(MMS_LANGUAGE_INTROB_LINE23);

	MMS_pamTalk(MMS_LANGUAGE_INTROB_LINE24);

	p_directorVoice(MMS_LANGUAGE_INTROB_LINE25);

	MMS_pamTalk(MMS_LANGUAGE_INTROB_LINE26);

	p_directorVoice(MMS_LANGUAGE_INTROB_LINE27);

	MMS_pamTalk(MMS_LANGUAGE_INTROB_LINE28);

	p_directorVoice(MMS_LANGUAGE_INTROB_LINE29);

	MMS_pamTalk(MMS_LANGUAGE_INTROB_LINE30);

	p_directorVoice(MMS_LANGUAGE_INTROB_LINE31);
}

void MMS_freeIntroB()
{
	if(p_actorSprite != NULL) PLEX_destroySprite(&p_actorSprite);
	if(p_directorSprite != NULL) PLEX_destroySprite(&p_directorSprite);

	PLEX_destroyTexture(p_stageBack);

	p_stageBack = 0;
}
