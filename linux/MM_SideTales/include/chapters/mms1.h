#ifndef MMS_MMS1_H
#define MMS_MMS1_H

#include "game.h"

#include "minigame/minigame1/minigame1.h"

#ifdef __cplusplus
extern "C"
{
#endif
	extern void MMS1_startChapter();
	extern bool MMS1_updateChapter(const size_t pamaleanaSpriteTex, const size_t levineSpriteTex, const size_t cubicleBackdrop, const size_t venariusSpriteTex, const size_t extraplocanSpriteTex, const size_t fontPlate, const size_t label, const size_t bubble, const size_t arrow);
	extern void MMS1_endChapter();
#ifdef __cplusplus
}
#endif

#endif
