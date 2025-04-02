#ifndef MMS_MINIGAME0_H
#define MMS_MINIGAME0_H

#include "minigame/minigame0/function.h"

extern bool MMS_beginMinigame0(const size_t chapter0spriteTex, const size_t pamaleanaSpriteTex, const uint64_t time);
extern bool MMS_updateMinigame0(bool* victory, const size_t fontPlate, const uint64_t time);
extern void MMS_endMinigame0();

extern bool MMS_isMinigame0Running();

extern void MMS_runMinigame0(const size_t chapter0spriteTex, const size_t pamaleanaSpriteTex, const size_t fontPlate);

#endif
