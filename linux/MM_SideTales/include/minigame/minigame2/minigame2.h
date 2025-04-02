#ifndef MMS_MINIGAME2_H
#define MMS_MINIGAME2_H

#include "plex.h"

#include "mmcommon.h"

#include "chapters/mms2.h"

#include "chapters/unlock.h"

#include "minigame/minigame2/structbodies.h"

#ifdef __cplusplus
extern "C"
{
#endif
	extern bool MMS_beginMinigame2(const size_t chapter2SpriteTex, const size_t chapter2SpriteTex2, const size_t chapter2SpriteTex3, const size_t chapter2SpriteTex4, const uint64_t time);

	extern bool MMS_updateMinigame2(const size_t pamaleanaSpriteTex, const size_t cubicleBackdrop, const size_t venariusSpriteTex, const size_t extraplocanSpriteTex, const size_t label, const size_t bubble, const size_t arrow, const size_t chapter2SpriteTex, const size_t chapter2SpriteTex2, const size_t chapter2SpriteTex3, const size_t chapter2SpriteTex4, const size_t fontPlate, const uint64_t time, bool* success);

	extern void MMS_endMinigame2();

	extern void MMS_runMinigame2(const size_t pamaleanaSpriteTex, const size_t cubicleBackdrop, const size_t venariusSpriteTex, const size_t extraplocanSpriteTex, const size_t label, const size_t bubble, const size_t arrow, const size_t chapter2SpriteTex, const size_t chapter2SpriteTex2, const size_t chapter2SpriteTex3, const size_t chapter2SpriteTex4, const size_t fontPlate);

	extern bool MMS_isMinigame2Running();
#ifdef __cplusplus
}
#endif

#endif
