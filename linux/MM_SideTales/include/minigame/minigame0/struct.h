#ifndef MMS_MINIGAME0_STRUCT_H
#define MMS_MINIGAME0_STRUCT_H

#include "minigame/minigame0/meta.h"

typedef struct
{
	PLEX_RECT rect;
	bool dead, vert, drinking;
	uint8_t direction;
} MMS0_ENEMY;

#endif
