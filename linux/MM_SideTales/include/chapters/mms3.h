#ifndef MMS_MMS3_H
#define MMS_MMS3_H

#include "game.h"

#include "mms0.h"

#ifdef __cplusplus
extern "C"
{
#endif
	// SECTION 1

	extern void MMS3_startSceneA(const size_t chapter3SpriteTex, const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow);
	extern void MMS3_startSceneB(const size_t chapter3SpriteTex, const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow);
	extern void MMS3_startSceneC(const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow);
	extern void MMS3_startSceneD(const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow);

	extern void MMS3_addPollockCodelli(const double x, const double y, const bool seated, bool hidden);
	extern void MMS3_pollockCodelliActorAnimationActionChange(const size_t index);
	extern void MMS3_pollockTalkWait(const char* const message, const uint64_t wait);
	extern void MMS3_pollockTalk(const char* const message);

	extern void MMS3_pollockHideActor();
	extern void MMS3_pollockUnhideActor();

	extern void MMS3_createSection1(const size_t chapter3SpriteTex);
	extern void MMS3_freeSection1();
	extern void MMS3_finalFreeSection1();

	// SECTION 2

	extern void MMS3_startSceneE(const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow);
	extern void MMS3_startSceneF(const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow);
	extern void MMS3_startSceneG(const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow);
	extern void MMS3_startSceneH(const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow);

	extern void MMS3_addStephinaCodelli(const double x, const double y, bool hidden);
	extern void MMS3_stephinaCodelliTalk(const char* const message);
	extern void MMS3_stephinaCodelliActorAnimationActionChange(const size_t index);

	extern void MMS3_loadCodellisLivingRoomBack();
	extern void MMS3_setBackgroundCodellisLivingRoom();

	extern void MMS3_setSceneCodellisLivingRoom(const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow);

	extern void MMS3_createSection2(const size_t chapter3SpriteTex);
	extern void MMS3_freeSection2();
	extern void MMS3_finalFreeSection2();

	// SECTION 3

	extern void MMS3_startSceneI(const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow);
	extern void MMS3_startSceneJ(const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow);
	extern void MMS3_startSceneK(const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow);
	extern void MMS3_startSceneL(const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow);
	extern void MMS3_startSceneM(const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow);

	extern void MMS3_addTeenPamaleana(const double x, const double y, const bool hidden);
	extern void MMS3_teenPamPamTalkWait(const char* const message, const uint64_t wait);
	extern void MMS3_teenPamPamTalk(const char* const message);
	extern void MMS3_teenPamPamActorAnimationActionChange(const size_t index);

	extern void MMS3_hideTeenPamPam();
	extern void MMS3_unhideTeenPamPam();

	extern void MMS3_moveTeenPamPam(const double x, const double y);
	extern void MMS3_resizeTeenPamPam(const double w, const double h);

	extern void MMS3_createSection3(const size_t chapter3SpriteTex);
	extern void MMS3_freeSection3();
	extern void MMS3_finalFreeSection3();

	// SECTION 4

	extern void MMS3_startSceneN(const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow);
	extern void MMS3_startSceneO(const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow);
	extern void MMS3_startSceneP(const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow);
	extern void MMS3_startSceneQ(const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow);
	extern void MMS3_startSceneR(const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow);

	extern size_t MMS3_createLightCone(const double x, const double y);
	extern void MMS3_addLightCone(const double x, const double y);

	extern void MMS3_hideLightCone();
	extern void MMS3_unhideLightCone();

	extern void MMS3_addHelldemon666();

	extern void MMS3_drDeeblockTalkWait(const char* const message, const uint64_t wait);
	extern void MMS3_drDeeblockTalk(const char* const message);
	extern void MMS3_hideDeeblockPamaleana();
	extern void MMS3_unhideDeeblockPamaleana();

	extern void MMS3_addDrDeeblock(const double x, const double y);
	extern void MMS3_changeDeeblockAnimation(const size_t index);
	extern void MMS3_hideDeeblock();
	extern void MMS3_unhideDeeblock();
	extern void MMS3_moveDeeblock(const double x, const double y);
	extern void MMS3_changeDeeblockAnimation(const size_t index);

	extern void MMS3_addDeeblockPamaleana();
	extern void MMS3_changeDeeblockPamaleana(const size_t index);
	extern void MMS3_moveDeeblockPamaleana(const double x, const double y);
	extern void MMS3_deeblockPamPamTalk(const char* const message);

	extern void MMS3_hideHellDemon666();
	extern void MMS3_unhideHellDemon666();

	extern void MMS3_changeActorHellDemon666(const size_t index);
	extern void MMS3_moveHellDemon666(const double x, const double y);
	extern void MMS3_hellDemon666Talk(const char* const message);

	extern void MMS3_changeActorHellDemon666(const size_t index);

	extern void MMS3_addDeeblockChairs();

	extern void MMS3_loadDeeblockOfficeBack();
	extern void MMS3_setSceneDeeblockOffice(const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow);

	extern void MMS3_createSection4(const size_t chapter3SpriteTex, const size_t tvShowTex);
	extern void MMS3_freeSection4();
	extern void MMS3_finalFreeSection4();

	// SECTION 5

	extern void MMS3_startSceneS(const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow);
	extern void MMS3_startSceneT(const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow);
	extern void MMS3_startSceneU(const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow);

	extern void MMS3_createSection5(const size_t chapter3SpriteTex);
	extern void MMS3_freeSection5();
	extern void MMS3_finalFreeSection5();

	// MAIN

	extern void MMS3_clearBackTextures();

	extern void MMS3_startChapter();
	extern bool MMS3_updateChapter(const size_t pamaleanaSpriteTex, const size_t cubicleBackdrop, const size_t venariusSpriteTex, const size_t extraplocanSpriteTex, const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow);
	extern void MMS3_endChapter();

	void MMS3_outro(const size_t pamaleanaSpriteTex, const size_t cubicleBackdrop, const size_t venariusSpriteTex, const size_t extraplocanSpriteTex, const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow);
#ifdef __cplusplus
}
#endif

#endif
