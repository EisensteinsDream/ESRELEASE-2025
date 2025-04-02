#ifndef MMS_MMS2_H
#define MMS_MMS2_H

#include "game.h"

#include "mms0.h"

#include "minigame/minigame2/minigame2.h"

#ifdef __cplusplus
extern "C"
{
#endif
	extern void MMS2_startChapter();
	extern bool MMS2_updateChapter(const size_t pamaleanaSpriteTex, const size_t cubicleBackdrop, const size_t venariusSpriteTex, const size_t extraplocanSpriteTex, const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow);
	extern void MMS2_endChapter();
#ifdef __cplusplus
}
#endif

#endif
