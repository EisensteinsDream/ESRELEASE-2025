#ifndef MMS2_STRUCTBODIES_H
#define MMS2_STRUCTBODIES_H

#include "minigame/minigame2/function.h"

// CALM AREA

struct MMS_MINIGAME2NPC
{
	size_t tex;
	PLEX_RECT space;
	PLEX_SPRITE* sprite;
	PLEX_FAKESTRING_50 message;
};

typedef struct MMS_MINIGAME2NPC MMS_MINIGAME2NPC;

struct MMS_MINIGAME2NPCSET
{
	size_t count;
	MMS_MINIGAME2NPC npc0, npc1, npc2, npc3, npc4;
};

typedef struct MMS_MINIGAME2NPCSET MMS_MINIGAME2NPCSET;

// PLAYER

struct MMS_MINIGAME2GUN
{
	PLEX_FAKESTRING_25 name;
	size_t icon, cursor, shotCursor, clipIcon, cost;
	int64_t ammoAmount, ammoMaximum, ammoClip, ammoClipMaximum, reloadTime;
	uint64_t shootTime, reloadDuration;
	double innerDamage, outerDamage;

	MM_COMMON_SOUNDEFFECT soundEffect, outOfAmmoSoundEffect;
	PLEX_SPRITE* shotAnimation;
};

typedef struct MMS_MINIGAME2GUN MMS_MINIGAME2GUN;

// ENEMY

struct MMS_MINIGAME2ENEMY
{
	PLEX_FAKESTRING_25 name;

	MMS_MINIGAME2ENEMYPHASE phase;

	PLEX_RECT space, adaptSpace;

	bool coverLocked;

	uint8_t shootDirec;

	double health, maxMoveSpeed, minMoveSpeed, treasureChance, likelyCashTreasure, likelyHealthTreasure, cashTreasureAmount, damagePotential, accuracyPotential, speedPerc, wperc, hperc;

	int64_t closestCover, coverDistance;

	uint64_t birthTime, lastActionTime, lastHitTime, lastShotTime, phaseCheckTime, thoughtDelay, rollStart, diveStart, shootTime, shootDuration, reloadTime, reloadDuration;

	size_t pointGain, aniIndex, shotCount, shotMax, startImage, tex;

	PLEX_SPRITE* sprite;

	MMS_F_AIPATTERN aiPattern;
};

typedef struct MMS_MINIGAME2ENEMY MMS_MINIGAME2ENEMY;

struct MMS_MINIGAME2AIPATTERNCONTAINER
{
	MMS_F_AIPATTERN contents;
};

typedef struct MMS_MINIGAME2AIPATTERNCONTAINER MMS_MINIGAME2AIPATTERNCONTAINER;

struct MMS_MINIGAME2ENEMYGENERATOR
{
	uint64_t minDuration, maxDuration;

	size_t start, max, aiPatternCount, typeCount, enemyCount;

	size_t generatorTypes[MMS2_GENERATORINDEXCOUNT];

	PLEX_GENERATOR* contents;

	MMS_MINIGAME2AIPATTERNCONTAINER aiPatterns[MMS2_AIPATTERNCOUNT];
};

typedef struct MMS_MINIGAME2ENEMYGENERATOR MMS_MINIGAME2ENEMYGENERATOR;

// COVER

struct MMS_MINIGAME2COVER
{
	size_t tex, texStart, killPenalty;
	bool beingDamaged, bleeds, moving, revFlight;
	double health, wperc, hperc, moveSpeed;
	uint64_t moveAnimSpeed;

	MMS_MINIGAME2MOVEPATTERN movePattern;
	PLEX_SPRITE* sprite;
	PLEX_RECT space, adaptSpace;
	PLEX_POINT startPoint;
	bool reverseAnim, gravesite;
};

typedef struct MMS_MINIGAME2COVER MMS_MINIGAME2COVER;

struct MMS_MINIGAME2COVERGENERATOR
{
	size_t minCount, maxCount, typeCount;

	size_t generatorTypes[MMS2_GENERATORINDEXCOUNT];
};

typedef struct MMS_MINIGAME2COVERGENERATOR MMS_MINIGAME2COVERGENERATOR;

// TREASURE

struct MMS_MINIGAME2TREASUREBOX
{
	size_t treasureAmmoIcon;
	double x, y, cash;
	bool hasAmmo, hasHealth, taken, opened;
	uint64_t openTime;
};

typedef struct MMS_MINIGAME2TREASUREBOX MMS_MINIGAME2TREASUREBOX;

// ROOM

struct MMS_MINIGAME2ROOMCONTENTS
{
	PLEX_FAKESTRING_25 name;

	PLEX_FAKESTRING_500 mayorMessage;

	bool calm, hasSheriff, hasDoc, hasMayor, mayorSpeech, pathFlag;
	size_t floor, sky;

	MMS_MINIGAME2ENEMYGENERATOR enemGenerator;
	MMS_MINIGAME2COVERGENERATOR coverGenerator;

	MMS_MINIGAME2NPC mayor, olDoc, olDog;

	MMS_MINIGAME2NPCSET townSquareNPCs, saloonNPCs, jailNPCs;
};

typedef struct MMS_MINIGAME2ROOMCONTENTS MMS_MINIGAME2ROOMCONTENTS;

struct MMS_MINIGAME2PATH
{
	MMS_MINIGAME2ROOMCONTENTS* upContents, *downContents, *rightContents, *leftContents;
	bool up, down, right, left;
};

typedef struct MMS_MINIGAME2PATH MMS_MINIGAME2PATH;

struct MMS_MINIGAME2ROOM
{
	MMS_MINIGAME2ROOMCONTENTS* contents;
	MMS_MINIGAME2PATH *path, *upPath, *downPath, *rightPath, *leftPath;
};

typedef struct MMS_MINIGAME2ROOM MMS_MINIGAME2ROOM;

// FINAL BOSS

struct MMS_MINIGAME2FINALBOSSDROPBOX
{
	bool isCover, active;
	size_t index;
	double distance, maxDistance;
	PLEX_POINT point, endPoint;
};

typedef struct MMS_MINIGAME2FINALBOSSDROPBOX MMS_MINIGAME2FINALBOSSDROPBOX;

#endif
