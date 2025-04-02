#include "minigame/minigame2/minigame2.h"

static MMS_MINIGAME2ROOM* p_currentRoom = NULL;

static size_t p_trailOn = 0;
static size_t p_lastDirection = 5;
static bool p_flagGen = false;

static size_t p_nameGrow1 = 0;
static size_t p_nameGrow2 = 0;

static size_t p_nameAt1 = 0;
static size_t p_nameAt2 = 0;

static size_t p_background0 = 0;
static size_t p_background1 = 0;
static size_t p_background2 = 0;
static size_t p_background3 = 0;
static size_t p_background4 = 0;

static size_t p_sky0 = 0;
static size_t p_sky1 = 0;
static size_t p_sky2 = 0;
static size_t p_sky3 = 0;
static size_t p_sky4 = 0;

static uint8_t p_moveDirec = 5;
static uint64_t p_startMoveTime = 0;

static const char* const p_names1[MMS2_AREANAMES1COUNT] = { MMS2_LANGUAGE_AREAGEN1_00, MMS2_LANGUAGE_AREAGEN1_01, MMS2_LANGUAGE_AREAGEN1_02, MMS2_LANGUAGE_AREAGEN1_03, MMS2_LANGUAGE_AREAGEN1_04, MMS2_LANGUAGE_AREAGEN1_05, MMS2_LANGUAGE_AREAGEN1_06, MMS2_LANGUAGE_AREAGEN1_07, MMS2_LANGUAGE_AREAGEN1_08, MMS2_LANGUAGE_AREAGEN1_09,MMS2_LANGUAGE_AREAGEN1_10, MMS2_LANGUAGE_AREAGEN1_11, MMS2_LANGUAGE_AREAGEN1_12, MMS2_LANGUAGE_AREAGEN1_13, MMS2_LANGUAGE_AREAGEN1_14, MMS2_LANGUAGE_AREAGEN1_15, MMS2_LANGUAGE_AREAGEN1_16, MMS2_LANGUAGE_AREAGEN1_17, MMS2_LANGUAGE_AREAGEN1_18, MMS2_LANGUAGE_AREAGEN1_19, MMS2_LANGUAGE_AREAGEN1_20, MMS2_LANGUAGE_AREAGEN1_21, MMS2_LANGUAGE_AREAGEN1_22, MMS2_LANGUAGE_AREAGEN1_23, MMS2_LANGUAGE_AREAGEN1_24, MMS2_LANGUAGE_AREAGEN1_25, MMS2_LANGUAGE_AREAGEN1_26, MMS2_LANGUAGE_AREAGEN1_27, MMS2_LANGUAGE_AREAGEN1_28, MMS2_LANGUAGE_AREAGEN1_29, MMS2_LANGUAGE_AREAGEN1_30, MMS2_LANGUAGE_AREAGEN1_31, MMS2_LANGUAGE_AREAGEN1_32, MMS2_LANGUAGE_AREAGEN1_33, MMS2_LANGUAGE_AREAGEN1_34, MMS2_LANGUAGE_AREAGEN1_35, MMS2_LANGUAGE_AREAGEN1_36, MMS2_LANGUAGE_AREAGEN1_37, MMS2_LANGUAGE_AREAGEN1_38, MMS2_LANGUAGE_AREAGEN1_39, MMS2_LANGUAGE_AREAGEN1_40, MMS2_LANGUAGE_AREAGEN1_41, MMS2_LANGUAGE_AREAGEN1_42, MMS2_LANGUAGE_AREAGEN1_43, MMS2_LANGUAGE_AREAGEN1_44, MMS2_LANGUAGE_AREAGEN1_45, MMS2_LANGUAGE_AREAGEN1_46, MMS2_LANGUAGE_AREAGEN1_47, MMS2_LANGUAGE_AREAGEN1_48, MMS2_LANGUAGE_AREAGEN1_49, MMS2_LANGUAGE_AREAGEN1_50, MMS2_LANGUAGE_AREAGEN1_51, MMS2_LANGUAGE_AREAGEN1_52, MMS2_LANGUAGE_AREAGEN1_53, MMS2_LANGUAGE_AREAGEN1_54, MMS2_LANGUAGE_AREAGEN1_55, MMS2_LANGUAGE_AREAGEN1_56, MMS2_LANGUAGE_AREAGEN1_57, MMS2_LANGUAGE_AREAGEN1_58, MMS2_LANGUAGE_AREAGEN1_59, MMS2_LANGUAGE_AREAGEN1_60, MMS2_LANGUAGE_AREAGEN1_61, MMS2_LANGUAGE_AREAGEN1_62, MMS2_LANGUAGE_AREAGEN1_63, MMS2_LANGUAGE_AREAGEN1_64, MMS2_LANGUAGE_AREAGEN1_65, MMS2_LANGUAGE_AREAGEN1_66, MMS2_LANGUAGE_AREAGEN1_67, MMS2_LANGUAGE_AREAGEN1_68, MMS2_LANGUAGE_AREAGEN1_69, MMS2_LANGUAGE_AREAGEN1_70, MMS2_LANGUAGE_AREAGEN1_71, MMS2_LANGUAGE_AREAGEN1_72, MMS2_LANGUAGE_AREAGEN1_73, MMS2_LANGUAGE_AREAGEN1_74, MMS2_LANGUAGE_AREAGEN1_75, MMS2_LANGUAGE_AREAGEN1_76, MMS2_LANGUAGE_AREAGEN1_77, MMS2_LANGUAGE_AREAGEN1_78, MMS2_LANGUAGE_AREAGEN1_79 };

static const char* const p_names2[MMS2_AREANAMES2COUNT] = { MMS2_LANGUAGE_AREAGEN2_00, MMS2_LANGUAGE_AREAGEN2_01, MMS2_LANGUAGE_AREAGEN2_02, MMS2_LANGUAGE_AREAGEN2_03, MMS2_LANGUAGE_AREAGEN2_04, MMS2_LANGUAGE_AREAGEN2_05, MMS2_LANGUAGE_AREAGEN2_06, MMS2_LANGUAGE_AREAGEN2_07, MMS2_LANGUAGE_AREAGEN2_08, MMS2_LANGUAGE_AREAGEN2_09,MMS2_LANGUAGE_AREAGEN2_10, MMS2_LANGUAGE_AREAGEN2_11, MMS2_LANGUAGE_AREAGEN2_12, MMS2_LANGUAGE_AREAGEN2_13, MMS2_LANGUAGE_AREAGEN2_14, MMS2_LANGUAGE_AREAGEN2_15, MMS2_LANGUAGE_AREAGEN2_16, MMS2_LANGUAGE_AREAGEN2_17, MMS2_LANGUAGE_AREAGEN2_18, MMS2_LANGUAGE_AREAGEN2_19, MMS2_LANGUAGE_AREAGEN2_20, MMS2_LANGUAGE_AREAGEN2_21, MMS2_LANGUAGE_AREAGEN2_22, MMS2_LANGUAGE_AREAGEN2_23, MMS2_LANGUAGE_AREAGEN2_24, MMS2_LANGUAGE_AREAGEN2_25, MMS2_LANGUAGE_AREAGEN2_26, MMS2_LANGUAGE_AREAGEN2_27, MMS2_LANGUAGE_AREAGEN2_28, MMS2_LANGUAGE_AREAGEN2_29, MMS2_LANGUAGE_AREAGEN2_30, MMS2_LANGUAGE_AREAGEN2_31, MMS2_LANGUAGE_AREAGEN2_32, MMS2_LANGUAGE_AREAGEN2_33, MMS2_LANGUAGE_AREAGEN2_34, MMS2_LANGUAGE_AREAGEN2_35, MMS2_LANGUAGE_AREAGEN2_36, MMS2_LANGUAGE_AREAGEN2_37, MMS2_LANGUAGE_AREAGEN2_38, MMS2_LANGUAGE_AREAGEN2_39, MMS2_LANGUAGE_AREAGEN2_40, MMS2_LANGUAGE_AREAGEN2_41, MMS2_LANGUAGE_AREAGEN2_42, MMS2_LANGUAGE_AREAGEN2_43, MMS2_LANGUAGE_AREAGEN2_44, MMS2_LANGUAGE_AREAGEN2_45, MMS2_LANGUAGE_AREAGEN2_46, MMS2_LANGUAGE_AREAGEN2_47, MMS2_LANGUAGE_AREAGEN2_48, MMS2_LANGUAGE_AREAGEN2_49, MMS2_LANGUAGE_AREAGEN2_50, MMS2_LANGUAGE_AREAGEN2_51, MMS2_LANGUAGE_AREAGEN2_52, MMS2_LANGUAGE_AREAGEN2_53, MMS2_LANGUAGE_AREAGEN2_54, MMS2_LANGUAGE_AREAGEN2_55, MMS2_LANGUAGE_AREAGEN2_56 };

// allocates a new room info struct that is completely blank

static MMS_MINIGAME2ROOMCONTENTS* p_genBlankRoomInfo()
{
	MMS_MINIGAME2ROOMCONTENTS* ret = PLEX_alloc(sizeof(MMS_MINIGAME2ROOMCONTENTS));

	if(ret == NULL)
	{
		PLEX_error(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_ALLOCFAIL, PLEX_ERROR_SEVERITY_FATAL, MMS2_ERRORMESS_ONGENBLANKROOMINFO);
		return NULL;
	}

	ret->calm = true;

	memset(&ret->enemGenerator, 0, sizeof(MMS_MINIGAME2ENEMYGENERATOR));
	memset(&ret->coverGenerator, 0, sizeof(MMS_MINIGAME2COVERGENERATOR));

	ret->enemGenerator.contents = NULL;

	return ret;
}

// allocates a room info struct based on passed values

static MMS_MINIGAME2ROOMCONTENTS* p_genRoomInfo(const char* const name, const size_t floor, const size_t sky)
{
	MMS_MINIGAME2ROOMCONTENTS* ret = p_genBlankRoomInfo();

	if(ret == NULL)
	{
		PLEX_error(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_ALLOCFAIL, PLEX_ERROR_SEVERITY_FATAL, MMS2_ERRORMESS_ONGENROOMINFO);
		return ret;
	}

	ret->name = PLEX_createString25(name);
	ret->floor = floor;
	ret->sky = sky;

	return ret;
}

//  allocates a new room path

static MMS_MINIGAME2PATH* p_genRoomPath()
{
	MMS_MINIGAME2PATH* ret = PLEX_alloc(sizeof(MMS_MINIGAME2PATH));

	if(ret == NULL)
	{
		PLEX_error(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_ALLOCFAIL, PLEX_ERROR_SEVERITY_FATAL, MMS2_ERRORMESS_ONGENROOMPATH);
		return ret;
	}

	ret->upContents = p_genBlankRoomInfo();
	ret->rightContents = p_genBlankRoomInfo();
	ret->downContents = p_genBlankRoomInfo();
	ret->leftContents = p_genBlankRoomInfo();

	return ret;
}

// allocates a new room based on passed values

static MMS_MINIGAME2ROOM* p_genRoom(const char* const name, const size_t floor, const size_t sky)
{
	MMS_MINIGAME2ROOM* ret = PLEX_alloc(sizeof(MMS_MINIGAME2ROOM));

	if(ret == NULL)
	{
		PLEX_error(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_ALLOCFAIL, PLEX_ERROR_SEVERITY_FATAL, MMS2_ERRORMESS_ONGENROOM);
		return NULL;
	}

	ret->contents = p_genRoomInfo(name, floor, sky);

	if(ret->contents == NULL)
	{
		PLEX_error(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_ALLOCFAIL, PLEX_ERROR_SEVERITY_FATAL, MMS2_ERRORMESS_ONGENROOMCONTENTS);
		return ret;
	}

	ret->path = p_genRoomPath();

	ret->upPath = p_genRoomPath();

	if(ret->upPath == NULL)
	{
		PLEX_error(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_ALLOCFAIL, PLEX_ERROR_SEVERITY_FATAL, MMS2_ERRORMESS_ONGENROOMUPPATH);
		return ret;
	}

	ret->downPath = p_genRoomPath();

	if(ret->downPath == NULL)
	{
		PLEX_error(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_ALLOCFAIL, PLEX_ERROR_SEVERITY_FATAL, MMS2_ERRORMESS_ONGENROOMDOWNPATH);
		return ret;
	}

	ret->leftPath = p_genRoomPath();

	if(ret->leftPath == NULL)
	{
		PLEX_error(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_ALLOCFAIL, PLEX_ERROR_SEVERITY_FATAL, MMS2_ERRORMESS_ONGENROOMLEFTPATH);
		return ret;
	}

	ret->rightPath = p_genRoomPath();

	if(ret->rightPath == NULL)
	{
		PLEX_error(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_ALLOCFAIL, PLEX_ERROR_SEVERITY_FATAL, MMS2_ERRORMESS_ONGENROOMRIGHTPATH);
		return ret;
	}

	return ret;
}

// destroys all NPCs in a room

static void p_clearRoomNPCs(struct MMS_MINIGAME2ROOMCONTENTS* toClear)
{
	MMS2_clearNPC(&toClear->townSquareNPCs.npc0);
	MMS2_clearNPC(&toClear->townSquareNPCs.npc1);
	MMS2_clearNPC(&toClear->townSquareNPCs.npc2);
	MMS2_clearNPC(&toClear->townSquareNPCs.npc3);
	MMS2_clearNPC(&toClear->townSquareNPCs.npc4);

	MMS2_clearNPC(&toClear->saloonNPCs.npc0);
	MMS2_clearNPC(&toClear->saloonNPCs.npc1);
	MMS2_clearNPC(&toClear->saloonNPCs.npc2);
	MMS2_clearNPC(&toClear->saloonNPCs.npc3);
	MMS2_clearNPC(&toClear->saloonNPCs.npc4);

	MMS2_clearNPC(&toClear->jailNPCs.npc0);
	MMS2_clearNPC(&toClear->jailNPCs.npc1);
	MMS2_clearNPC(&toClear->jailNPCs.npc2);
	MMS2_clearNPC(&toClear->jailNPCs.npc3);
	MMS2_clearNPC(&toClear->jailNPCs.npc4);

	MMS2_clearNPC(&toClear->mayor);
	MMS2_clearNPC(&toClear->olDoc);
	MMS2_clearNPC(&toClear->olDog);

	toClear->hasSheriff = false;
	toClear->hasDoc = false;
	toClear->hasMayor = false;
	toClear->mayorSpeech = false;
}

// destroys room info and the enemy generator's internal generator

static void p_destroyRoomInfo(MMS_MINIGAME2ROOMCONTENTS* toDestroy)
{
	if(toDestroy == NULL)
	{
		PLEX_error(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_FREENULL, PLEX_ERROR_SEVERITY_BADSTYLE, MMS2_ERRORMESS_ONDESTROYROOMINFO);
		return;
	}

	p_clearRoomNPCs(toDestroy);

	if(toDestroy->enemGenerator.contents != NULL) PLEX_destroyGenerator(&toDestroy->enemGenerator.contents);

	PLEX_dealloc(&toDestroy);
}

// destroys a room path and all of it's contents

static void p_destroyRoomPath(MMS_MINIGAME2PATH* toDestroy)
{
	if(toDestroy == NULL)
	{
		PLEX_error(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_FREENULL, PLEX_ERROR_SEVERITY_BADSTYLE, MMS2_ERRORMESS_ONDESTROYROOMPATH);
		return;
	}

	p_destroyRoomInfo(toDestroy->upContents);
	p_destroyRoomInfo(toDestroy->rightContents);
	p_destroyRoomInfo(toDestroy->downContents);
	p_destroyRoomInfo(toDestroy->leftContents);

	PLEX_dealloc(&toDestroy);
}

// destroys a room and all of it's contents including paths and info

static void p_destroyRoom(MMS_MINIGAME2ROOM** toDestroy)
{
	MMS_MINIGAME2ROOM* toDestroyPtr = NULL;

	if(toDestroy == NULL)
	{
		PLEX_error(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_FREENULL, PLEX_ERROR_SEVERITY_BADSTYLE, MMS2_ERRORMESS_ONDESTROYROOM);
		return;
	}

	toDestroyPtr = *toDestroy;

	if(toDestroyPtr == NULL)
	{
		PLEX_error(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_FREENULL, PLEX_ERROR_SEVERITY_BADSTYLE, MMS2_ERRORMESS_ONDESTROYROOMPTR);
		return;
	}

	p_destroyRoomPath(toDestroyPtr->upPath);
	p_destroyRoomPath(toDestroyPtr->rightPath);
	p_destroyRoomPath(toDestroyPtr->downPath);
	p_destroyRoomPath(toDestroyPtr->leftPath);

	p_destroyRoomPath(toDestroyPtr->path);

	p_destroyRoomInfo(toDestroyPtr->contents);

	PLEX_dealloc((void**)toDestroy);
}

// sets the room contents based on passed values

static void p_setRoomContents(MMS_MINIGAME2ROOMCONTENTS* set, const MMS_MINIGAME2ROOMCONTENTS* const to, const uint64_t time)
{
	MMS2_copyRoomNPCs(set, to);

	set->pathFlag = false;

	set->name = to->name;
	set->mayorMessage = to->mayorMessage;

	set->calm = to->calm;
	set->floor = to->floor;
	set->sky = to->sky;

	set->enemGenerator.start = to->enemGenerator.start;
	set->enemGenerator.max = to->enemGenerator.max;
	set->enemGenerator.aiPatternCount = to->enemGenerator.aiPatternCount;
	set->enemGenerator.typeCount = to->enemGenerator.typeCount;

	set->enemGenerator.minDuration = to->enemGenerator.minDuration;
	set->enemGenerator.maxDuration = to->enemGenerator.maxDuration;
	set->enemGenerator.enemyCount = to->enemGenerator.enemyCount;

	memcpy(set->enemGenerator.generatorTypes, to->enemGenerator.generatorTypes, to->enemGenerator.typeCount * sizeof(size_t));

	memcpy(set->enemGenerator.aiPatterns, to->enemGenerator.aiPatterns, to->enemGenerator.aiPatternCount * sizeof(MMS_MINIGAME2AIPATTERNCONTAINER));

	set->coverGenerator.minCount = to->coverGenerator.minCount;
	set->coverGenerator.maxCount = to->coverGenerator.maxCount;
	set->coverGenerator.typeCount = to->coverGenerator.typeCount;

	memcpy(set->coverGenerator.generatorTypes, to->coverGenerator.generatorTypes, to->coverGenerator.typeCount * sizeof(size_t));
}

// sets the room path based on passed values

static void p_setRoomPath(MMS_MINIGAME2PATH* set, const MMS_MINIGAME2PATH* const to, const uint64_t time)
{
	set->up = to->up;
	set->right = to->right;
	set->down = to->down;
	set->left = to->left;

	p_setRoomContents(set->upContents, to->upContents, time);
	p_setRoomContents(set->rightContents, to->rightContents, time);
	p_setRoomContents(set->downContents, to->downContents, time);
	p_setRoomContents(set->leftContents, to->leftContents, time);
}

// opens a direction of a room

static void p_openDirection(const size_t direc, MMS_MINIGAME2ROOM* roomA, MMS_MINIGAME2ROOM* roomB, const size_t time)
{
	switch(direc)
	{
		case 0:
			p_setRoomPath(roomB->upPath, roomA->path, time);
			roomB->path->up = true;
			p_setRoomContents(roomB->path->upContents, roomA->contents, time);
			break;

		case 1:
			p_setRoomPath(roomB->rightPath, roomA->path, time);
			roomB->path->right = true;
			p_setRoomContents(roomB->path->rightContents, roomA->contents, time);
			break;

		case 2:
			p_setRoomPath(roomB->downPath, roomA->path, time);
			roomB->path->down = true;
			p_setRoomContents(roomB->path->downContents, roomA->contents, time);
			break;

		case 3:
			p_setRoomPath(roomB->leftPath, roomA->path, time);
			roomB->path->left = true;
			p_setRoomContents(roomB->path->leftContents, roomA->contents, time);
			break;
	};
}

// moves the player north

static void p_moveRoomNorth(MMS_MINIGAME2ROOMCONTENTS* contents, MMS_MINIGAME2PATH* path, MMS_MINIGAME2ROOM* room, const uint64_t time)
{
	p_setRoomContents(contents, room->path->upContents, time);
	p_setRoomPath(path, room->upPath, time);
}

// moves the player east

static void p_moveRoomEast(MMS_MINIGAME2ROOMCONTENTS* contents, MMS_MINIGAME2PATH* path, MMS_MINIGAME2ROOM* room, const uint64_t time)
{
	p_setRoomContents(contents, room->path->rightContents, time);
	p_setRoomPath(path, room->rightPath, time);
}

// moves the player south

static void p_moveRoomSouth(MMS_MINIGAME2ROOMCONTENTS* contents, MMS_MINIGAME2PATH* path, MMS_MINIGAME2ROOM* room, const uint64_t time)
{
	p_setRoomContents(contents, room->path->downContents, time);
	p_setRoomPath(path, room->downPath, time);
}

// moves the player west

static void p_moveRoomWest(MMS_MINIGAME2ROOMCONTENTS* contents, MMS_MINIGAME2PATH* path, MMS_MINIGAME2ROOM* room, const uint64_t time)
{
	p_setRoomContents(contents, room->path->leftContents, time);
	p_setRoomPath(path, room->leftPath, time);
}

// moves the room in direction 'direc'

static void p_moveRoom(const size_t direc, MMS_MINIGAME2ROOM* room, const uint64_t time)
{
	MMS_MINIGAME2ROOMCONTENTS* contents = p_genBlankRoomInfo();
	MMS_MINIGAME2PATH* path = NULL;

	if(contents == NULL)
	{
		PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_ALLOCFAIL, PLEX_ERROR_SEVERITY_MINOR, MMS2_ERRORMESS_ONMOVEROOM, MMS2_ERRORMESS_ROOMINFO);
		return;
	}

	path = p_genRoomPath();

	if(path == NULL)
	{
		p_destroyRoomInfo(contents);
		PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_ALLOCFAIL, PLEX_ERROR_SEVERITY_MINOR, MMS2_ERRORMESS_ONMOVEROOM, MMS2_ERRORMESS_ROOMPATH);
		return;
	}

	switch(direc)
	{
		case 0: p_moveRoomNorth(contents, path, room, time); break;
		case 1: p_moveRoomEast(contents, path, room, time); break;
		case 2: p_moveRoomSouth(contents, path, room, time); break;
		case 3: p_moveRoomWest(contents, path, room, time); break;
	};

	room->path->up = path->up;
	room->path->right = path->right;
	room->path->down = path->down;
	room->path->left = path->left;

	p_setRoomContents(room->path->upContents, path->upContents, time);
	p_setRoomContents(room->path->rightContents, path->rightContents, time);
	p_setRoomContents(room->path->downContents, path->downContents, time);
	p_setRoomContents(room->path->leftContents, path->leftContents, time);

	p_setRoomContents(room->contents, contents, time);

	if(room->contents->calm) MMS2_snapshotTown();

	p_destroyRoomInfo(contents);
	p_destroyRoomPath(path);

	MMS2_setTownArea(0);

	p_lastDirection = direc;
}

// checks for a random available direction to possibly open and returns which one it is

static size_t p_availDirec()
{
	size_t ret = PLEX_randomNumber(0, 3);

	while(ret == p_lastDirection || (!ret && p_currentRoom->path->up) || (ret == 1 && p_currentRoom->path->right) || (ret == 2 && p_currentRoom->path->down) || (ret == 3 && p_currentRoom->path->left)) ret = (ret + 1) % 4;

	return ret;
}

// randomizes the first word in an area name

static PLEX_FAKESTRING_50 p_areaName1()
{
	const char* const name = p_names1[p_nameAt1];

	p_nameAt1 = (p_nameAt1 + p_nameGrow1) % MMS2_AREANAMES1COUNT;

	return PLEX_createString50(name);
}

// randomizes the second word in an area name

static PLEX_FAKESTRING_50 p_areaName2()
{
	const char* const name = p_names2[p_nameAt2];

	p_nameAt2 = (p_nameAt2 + p_nameGrow2) % MMS2_AREANAMES2COUNT;

	return PLEX_createString50(name);
}

// generates a room in trail 0

static MMS_MINIGAME2ROOM* p_genRoom0(const size_t direc, const double trailPerc, const uint64_t time)
{
	PLEX_FAKESTRING_50 areaName = p_areaName1();
	PLEX_FAKESTRING_50 areaName2 = p_areaName2();

	size_t coverBaseNumber = 0;

	MMS_MINIGAME2ROOM* ret = NULL;

	areaName = PLEX_concatString50(areaName, ' ', 1);
	areaName = PLEX_mergeString50(areaName, areaName2);

	ret = p_genRoom(PLEX_fts(areaName), p_background0, p_sky0);

	switch(direc)
	{
		case 0: coverBaseNumber = 10; break;
		case 1: coverBaseNumber = 20; break;
		case 2: coverBaseNumber = 15; break;
		case 3: coverBaseNumber = 30; break;
	};

	MMS2_setEnemyGenerator(5000, 10000, 5, MMS2_ai_sneak, 0, ret, time);

	MMS2_addEnemyGeneratorTypeIndex(ret, 1);

	MMS2_addGeneratorAIPattern(ret, MMS2_ai_dodger);
	MMS2_addGeneratorAIPattern(ret, MMS2_ai_coward);

	MMS2_setCoverGenerator(10 + (coverBaseNumber * trailPerc), 20 + (coverBaseNumber * trailPerc), 0, ret, time);

	MMS2_addCoverTypeIndex(ret, 1);
	MMS2_addCoverTypeIndex(ret, 2);
	MMS2_addCoverTypeIndex(ret, 3);

	return ret;
}

// generates a room in trail 1

static MMS_MINIGAME2ROOM* p_genRoom1(const size_t direc, const double trailPerc, const uint64_t time)
{
	PLEX_FAKESTRING_50 areaName = p_areaName1();
	PLEX_FAKESTRING_50 areaName2 = p_areaName2();

	size_t coverBaseNumber = 0;

	MMS_MINIGAME2ROOM* ret = NULL;

	areaName = PLEX_concatString50(areaName, ' ', 1);
	areaName = PLEX_mergeString50(areaName, areaName2);

	ret = p_genRoom(PLEX_fts(areaName), p_background1, p_sky1);

	switch(direc)
	{
		case 0: coverBaseNumber = 8; break;
		case 1: coverBaseNumber = 16; break;
		case 2: coverBaseNumber = 20; break;
		case 3: coverBaseNumber = 24; break;
	};

	MMS2_setEnemyGenerator(10000, 20000, 5, MMS2_ai_runner, 2, ret, time);

	MMS2_addEnemyGeneratorTypeIndex(ret, 3);

	MMS2_addGeneratorAIPattern(ret, MMS2_ai_diver);

	MMS2_setCoverGenerator(5 + (coverBaseNumber * trailPerc), 10 + (coverBaseNumber * trailPerc), 4, ret, time);

	MMS2_addCoverTypeIndex(ret, 5);
	MMS2_addCoverTypeIndex(ret, 6);
	MMS2_addCoverTypeIndex(ret, 7);

	switch(direc)
	{
		case 0:
			MMS2_addCoverTypeIndex(ret, 3);
			MMS2_addGeneratorAIPattern(ret, MMS2_ai_coward);
		break;

		case 1:
			MMS2_addEnemyGeneratorTypeIndex(ret, 1);
			MMS2_addGeneratorAIPattern(ret, MMS2_ai_sneak);
		break;

		case 2:
			MMS2_addCoverTypeIndex(ret, 0);
			MMS2_addGeneratorAIPattern(ret, MMS2_ai_coward);
		break;

		case 3:
			MMS2_addCoverTypeIndex(ret, 2);
			MMS2_addGeneratorAIPattern(ret, MMS2_ai_sneak);
		break;
	};

	return ret;
}

// generates a room in trail 2

static MMS_MINIGAME2ROOM* p_genRoom2(const size_t direc, const double trailPerc, const uint64_t time)
{
	PLEX_FAKESTRING_50 areaName = p_areaName1();
	PLEX_FAKESTRING_50 areaName2 = p_areaName2();

	size_t coverBaseNumber = 0;

	MMS_MINIGAME2ROOM* ret = NULL;

	areaName = PLEX_concatString50(areaName, ' ', 1);
	areaName = PLEX_mergeString50(areaName, areaName2);

	ret = p_genRoom(PLEX_fts(areaName), p_background2, p_sky2);

	switch(direc)
	{
		case 0: coverBaseNumber = 10; break;
		case 1: coverBaseNumber = 20; break;
		case 2: coverBaseNumber = 15; break;
		case 3: coverBaseNumber = 30; break;
	};

	MMS2_setEnemyGenerator(20000, 30000, 5, MMS2_ai_sharpshooter, 4, ret, time);

	MMS2_addEnemyGeneratorTypeIndex(ret, 5);

	MMS2_addGeneratorAIPattern(ret, MMS2_ai_maniac);

	MMS2_setCoverGenerator(10 + (coverBaseNumber * trailPerc), 20 + (coverBaseNumber * trailPerc), 8, ret, time);

	MMS2_addCoverTypeIndex(ret, 9);
	MMS2_addCoverTypeIndex(ret, 12);

	switch(direc)
	{
		case 0:
			MMS2_addCoverTypeIndex(ret, 3);
			MMS2_addEnemyGeneratorTypeIndex(ret, 2);

			MMS2_addGeneratorAIPattern(ret, MMS2_ai_coward);
			MMS2_addGeneratorAIPattern(ret, MMS2_ai_runner);
		break;

		case 1:
			MMS2_addEnemyGeneratorTypeIndex(ret, 1);
			MMS2_addCoverTypeIndex(ret, 5);

			MMS2_addGeneratorAIPattern(ret, MMS2_ai_sneak);
			MMS2_addGeneratorAIPattern(ret, MMS2_ai_diver);
		break;

		case 2:
			MMS2_addCoverTypeIndex(ret, 0);
			MMS2_addEnemyGeneratorTypeIndex(ret, 3);

			MMS2_addGeneratorAIPattern(ret, MMS2_ai_coward);
			MMS2_addGeneratorAIPattern(ret, MMS2_ai_diver);
		break;

		case 3:
			MMS2_addCoverTypeIndex(ret, 2);
			MMS2_addCoverTypeIndex(ret, 7);

			MMS2_addGeneratorAIPattern(ret, MMS2_ai_sneak);
			MMS2_addGeneratorAIPattern(ret, MMS2_ai_runner);
		break;
	};

	return ret;
}

// generates a room in trail 3

static MMS_MINIGAME2ROOM* p_genRoom3(const size_t direc, const double trailPerc, const uint64_t time)
{
	PLEX_FAKESTRING_50 areaName = p_areaName1();
	PLEX_FAKESTRING_50 areaName2 = p_areaName2();

	size_t coverBaseNumber = 0;

	MMS_MINIGAME2ROOM* ret = NULL;

	areaName = PLEX_concatString50(areaName, ' ', 1);
	areaName = PLEX_mergeString50(areaName, areaName2);

	ret = p_genRoom(PLEX_fts(areaName), p_background2, p_sky2);

	switch(direc)
	{
		case 0: coverBaseNumber = 10; break;
		case 1: coverBaseNumber = 20; break;
		case 2: coverBaseNumber = 15; break;
		case 3: coverBaseNumber = 30; break;
	};

	MMS2_setEnemyGenerator(20000, 30000, 5, MMS2_ai_coward, 4, ret, time);

	MMS2_addGeneratorAIPattern(ret, MMS2_ai_sneak);
	MMS2_addGeneratorAIPattern(ret, MMS2_ai_dodger);
	MMS2_addGeneratorAIPattern(ret, MMS2_ai_runner);
	MMS2_addGeneratorAIPattern(ret, MMS2_ai_diver);
	MMS2_addGeneratorAIPattern(ret, MMS2_ai_sharpshooter);
	MMS2_addGeneratorAIPattern(ret, MMS2_ai_maniac);

	MMS2_addEnemyGeneratorTypeIndex(ret, 0);
	MMS2_addEnemyGeneratorTypeIndex(ret, 5);

	MMS2_setCoverGenerator(10 + (coverBaseNumber * trailPerc), 20 + (coverBaseNumber * trailPerc), 0, ret, time);

	MMS2_addCoverTypeIndex(ret, 1);
	MMS2_addCoverTypeIndex(ret, 4);
	MMS2_addCoverTypeIndex(ret, 6);
	MMS2_addCoverTypeIndex(ret, 8);
	MMS2_addCoverTypeIndex(ret, 9);
	MMS2_addCoverTypeIndex(ret, 10);
	MMS2_addCoverTypeIndex(ret, 11);
	MMS2_addCoverTypeIndex(ret, 12);
	MMS2_addCoverTypeIndex(ret, 13);
	MMS2_addCoverTypeIndex(ret, 14);
	MMS2_addCoverTypeIndex(ret, 15);
	MMS2_addCoverTypeIndex(ret, 16);
	MMS2_addCoverTypeIndex(ret, 17);

	switch(direc)
	{
		case 0:
			MMS2_addCoverTypeIndex(ret, 3);

			MMS2_addEnemyGeneratorTypeIndex(ret, 1);
			MMS2_addEnemyGeneratorTypeIndex(ret, 2);
		break;

		case 1:
			MMS2_addCoverTypeIndex(ret, 5);

			MMS2_addEnemyGeneratorTypeIndex(ret, 1);
			MMS2_addEnemyGeneratorTypeIndex(ret, 3);
		break;

		case 2:
			MMS2_addCoverTypeIndex(ret, 0);

			MMS2_addEnemyGeneratorTypeIndex(ret, 2);
			MMS2_addEnemyGeneratorTypeIndex(ret, 3);
		break;

		case 3:
			MMS2_addCoverTypeIndex(ret, 2);
			MMS2_addCoverTypeIndex(ret, 7);

			MMS2_addEnemyGeneratorTypeIndex(ret, 2);
			MMS2_addEnemyGeneratorTypeIndex(ret, 4);
		break;
	};

	return ret;
}

// generates a path in trail 0

static void p_genTrail0Path(const size_t chapter2SpriteTex, const size_t chapter2SpriteTex2, uint64_t time)
{
	static const double pointRange = MMS2_POINTPATH0;

	const double pointDiff = MMS2_points();

	const double trailPerc = pointDiff < pointRange ? pointDiff/pointRange : 1;

	size_t pathways = 0;

	MMS_MINIGAME2ROOM* newRoom = NULL;

	if(MMS2_points() >= MMS2_POINTPATH0 && !p_currentRoom->contents->calm)
	{
		newRoom = p_genRoom(MMS2_LANGUAGE_TOWN1_TITLE, p_background1, p_sky1);

		MMS2_setAsTown1(chapter2SpriteTex, chapter2SpriteTex2, newRoom, time);

		p_openDirection(p_availDirec(), newRoom, p_currentRoom, time);

		p_destroyRoom(&newRoom);

		MMS2_snapshotTown();

		++p_trailOn;
	}else{
		pathways = (trailPerc/0.4) + 1;

		for(size_t ze = 0; ze < pathways; ++ze)
		{
			const size_t direc = p_availDirec();

			newRoom = p_genRoom0(direc, trailPerc, time);

			p_openDirection(direc, newRoom, p_currentRoom, time);

			p_destroyRoom(&newRoom);
		}
	}
}

// generates a path in trail 1

static void p_genTrail1Path(const size_t chapter2SpriteTex, const size_t chapter2SpriteTex2, const uint64_t time)
{
	static const double pointRange = MMS2_POINTPATH1 - MMS2_POINTPATH0;

	const double pointDiff = MMS2_points() - MMS2_POINTPATH0;

	const double trailPerc = pointDiff < pointRange ? pointDiff/pointRange : 1;

	size_t pathways = 0;

	MMS_MINIGAME2ROOM* newRoom = NULL;

	if(MMS2_points() >= MMS2_POINTPATH1 && !p_currentRoom->contents->calm)
	{
		newRoom = p_genRoom(MMS2_LANGUAGE_TOWN2_TITLE, p_background2, p_sky2);

		MMS2_setAsTown2(chapter2SpriteTex, chapter2SpriteTex2, newRoom, time);

		p_openDirection(p_availDirec(), newRoom, p_currentRoom, time);

		p_destroyRoom(&newRoom);

		MMS2_snapshotTown();

		++p_trailOn;
	}else{
		pathways = (trailPerc/0.4) + 1;

		for(size_t ze = 0; ze < pathways; ++ze)
		{
			const size_t direc = p_availDirec();

			newRoom = p_genRoom1(direc, trailPerc, time);

			p_openDirection(direc, newRoom, p_currentRoom, time);

			p_destroyRoom(&newRoom);
		}
	}
}

// generates a path in trail 2

static void p_genTrail2Path(const size_t chapter2SpriteTex, const size_t chapter2SpriteTex2, const uint64_t time)
{
	static const double pointRange = MMS2_POINTPATH2 - MMS2_POINTPATH1;

	const double pointDiff = MMS2_points() - MMS2_POINTPATH1;

	const double trailPerc = pointDiff < pointRange ? pointDiff/pointRange : 1;

	size_t pathways = 0;

	MMS_MINIGAME2ROOM* newRoom = NULL;

	if(MMS2_points() >= MMS2_POINTPATH2 && !p_currentRoom->contents->calm)
	{
		newRoom = p_genRoom(MMS2_LANGUAGE_TOWN3_TITLE, p_background2, p_sky2);

		MMS2_setAsTown3(chapter2SpriteTex, chapter2SpriteTex2, newRoom, time);

		p_openDirection(p_availDirec(), newRoom, p_currentRoom, time);

		p_destroyRoom(&newRoom);

		MMS2_snapshotTown();

		++p_trailOn;
	}else{
		pathways = (trailPerc/0.4) + 1;

		for(size_t ze = 0; ze < pathways; ++ze)
		{
			const size_t direc = p_availDirec();

			newRoom = p_genRoom2(direc, trailPerc, time);

			p_openDirection(direc, newRoom, p_currentRoom, time);

			p_destroyRoom(&newRoom);
		}
	}
}

// generates a path in trail 3

static void p_genTrail3Path(const size_t chapter2SpriteTex, const size_t chapter2SpriteTex2, const uint64_t time)
{
	static const double pointRange = MMS2_POINTPATH3 - MMS2_POINTPATH2;

	const double pointDiff = MMS2_points() - MMS2_POINTPATH2;

	const double trailPerc = pointDiff < pointRange ? pointDiff/pointRange : 1;

	size_t pathways = 0;

	MMS_MINIGAME2ROOM* newRoom = NULL;

	if(MMS2_points() >= MMS2_POINTPATH3 && !p_currentRoom->contents->calm)
	{
		newRoom = p_genRoom(MMS2_LANGUAGE_TOWN4_TITLE, p_background2, p_sky2);

		MMS2_setAsTown4(chapter2SpriteTex, chapter2SpriteTex2, newRoom, time);

		p_openDirection(p_availDirec(), newRoom, p_currentRoom, time);

		p_destroyRoom(&newRoom);

		MMS2_snapshotTown();

		++p_trailOn;
	}else{
		pathways = (trailPerc/0.4) + 1;

		for(size_t ze = 0; ze < pathways; ++ze)
		{
			const size_t direc = p_availDirec();

			newRoom = p_genRoom3(direc, trailPerc, time);

			p_openDirection(direc, newRoom, p_currentRoom, time);

			p_destroyRoom(&newRoom);
		}
	}
}

// returns the room path contents in 'direc'

static MMS_MINIGAME2ROOMCONTENTS* p_getCurrentRoomPathContents(const size_t direc)
{
	if(p_currentRoom == NULL)
	{
		PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MINOR, MMS2_ERRORMESS_ONGETCURRENTROOMPATH, MMS2_ERRORMESS_CURRENTROOM);
		return NULL;
	}

	switch(direc)
	{
		case 0: return p_currentRoom->path->upContents;
		case 1: return p_currentRoom->path->rightContents;
		case 2: return p_currentRoom->path->downContents;
		case 3: return p_currentRoom->path->leftContents;
	};

	return NULL;
}

// returns the floor image in the room at direc

size_t p_pathFloor(const size_t direc)
{
	MMS_MINIGAME2ROOMCONTENTS* contents = NULL;

	if(p_currentRoom == NULL)
	{
		PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MINOR, MMS2_ERRORMESS_ONRETRIEVINGPATHFLOOR, MMS2_ERRORMESS_CURRENTROOM);
		return false;
	}

	contents = p_getCurrentRoomPathContents(direc);

	if(contents == NULL)
	{
		PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MINOR, MMS2_ERRORMESS_ONRETRIEVINGPATHFLOOR, MMS2_ERRORMESS_CURRENTROOMPATH);
		return false;
	}

	return contents->floor;
}

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

void MMS2_setSystemRoom()
{
	p_flagGen = false;
	p_lastDirection = 5;
}

void MMS2_initSystemRoom()
{
	p_nameGrow1 = PLEX_randomNumber(1, 5);
	p_nameGrow2 = PLEX_randomNumber(1, 5);

	p_nameAt1 = PLEX_randomNumber(0, MMS2_AREANAMES1COUNT);
	p_nameAt2 = PLEX_randomNumber(0, MMS2_AREANAMES2COUNT);

	while(p_nameGrow1 == p_nameGrow2) p_nameGrow2 = PLEX_randomNumber(0, MMS2_AREANAMES2COUNT);
	while(p_nameAt1 == p_nameAt2) p_nameAt1 = PLEX_randomNumber(1, 5);

	if(!p_background0) p_background0 = PLEX_loadTextureFromFileOrHeaderless(1024, 768, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_BACKDROP0, MMS2_FILEPATH_HEADERLESS_BACKDROP0);
	if(!p_background1) p_background1 = PLEX_loadTextureFromFileOrHeaderless(1024, 768, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_BACKDROP1, MMS2_FILEPATH_HEADERLESS_BACKDROP1);
	if(!p_background2) p_background2 = PLEX_loadTextureFromFileOrHeaderless(1024, 768, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_BACKDROP2, MMS2_FILEPATH_HEADERLESS_BACKDROP2);
	if(!p_background3) p_background3 = PLEX_loadTextureFromFileOrHeaderless(1024, 768, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_BACKDROP3, MMS2_FILEPATH_HEADERLESS_BACKDROP3);
	if(!p_background4) p_background4 = PLEX_loadTextureFromFileOrHeaderless(1024, 768, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_BACKDROP4, MMS2_FILEPATH_HEADERLESS_BACKDROP4);

	if(!p_sky0) p_sky0 = PLEX_loadTextureFromFileOrHeaderless(1024, 192, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_SKY0, MMS2_FILEPATH_HEADERLESS_SKY0);
	if(!p_sky1) p_sky1 = PLEX_loadTextureFromFileOrHeaderless(1024, 192, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_SKY1, MMS2_FILEPATH_HEADERLESS_SKY1);
	if(!p_sky2) p_sky2 = PLEX_loadTextureFromFileOrHeaderless(1024, 192, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_SKY2, MMS2_FILEPATH_HEADERLESS_SKY2);
	if(!p_sky3) p_sky3 = PLEX_loadTextureFromFileOrHeaderless(1024, 192, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_SKY3, MMS2_FILEPATH_HEADERLESS_SKY3);
	if(!p_sky4) p_sky4 = PLEX_loadTextureFromFileOrHeaderless(1024, 192, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_SKY4, MMS2_FILEPATH_HEADERLESS_SKY4);

	p_trailOn = 0;
}

bool MMS2_checkRunSystemRoom(const size_t chapter2SpriteTex, const size_t chapter2SpriteTex2, const size_t chapter2SpriteTex3, const size_t chapter2SpriteTex4, const size_t fontPlate, const uint64_t time)
{
	MMS_MINIGAME2ENEMYGENERATOR* enemGenerator = NULL;

	if(MMS2_flagGen())
	{
		MMS2_genNextPath(chapter2SpriteTex, chapter2SpriteTex2, chapter2SpriteTex3, chapter2SpriteTex4, time);
		p_flagGen = false;
	}

	if(MMS2_isNotMoving())
	{
		if(!MMS2_currentRoomCalm())
		{
			PLEX_printTexture(9999, MMS2_currentRoomFloor(), 0, 0, 1024, 768, 0, MMS2_leanY(), PLEX_WW(true), PLEX_WH(true), true);
			PLEX_printTexture(9998, MMS2_currentRoomSky(), 0, 0, 1024, 192, 0, 0, PLEX_WW(true), PLEX_WH(true)/4 + MMS2_leanY(), true);

			if(MMS2_leanX() > 0) PLEX_fillRect(101, 0, 0, PLEX_UNIT(MMS2_leanX()), PLEX_WH(true), 0, 0, 0, 100, true);

			if(MMS2_leanX() < 0)
			{
				const double w = 0 - PLEX_UNIT(MMS2_leanX());

				PLEX_fillRect(101, PLEX_WW(true) - w, 0, w, PLEX_WH(true), 0, 0, 0, 100, true);
			}
		}
	}else{
		const double perc = time > p_startMoveTime ? (time - p_startMoveTime)/1000.0 : 0;

		double fx = 0;
		double fy = 0;
		double fw = PLEX_WW(true);
		double fh = PLEX_WH(true);

		double fx2 = 0;
		double fy2 = 0;
		double fw2 = PLEX_WW(true);
		double fh2 = PLEX_WH(true);

		size_t transitionBackdrop = 0;

		switch(MMS2_moveDirec())
		{
			case 0:
				fh *= (1 - perc);
				fy = PLEX_WH(true) - fh;

				fh2 *= perc;
				break;

			case 1:
				fw *= (1 - perc);

				fx2 = fw;
				fw2 = PLEX_WW(true) - fw;
				break;

			case 2:
				fh *= (1 - perc);

				fh2 *= perc;
				fy2 = PLEX_WH(true) - fh2;
				break;

			case 3:
				fw *= (1 - perc);
				fx = PLEX_WW(true) - fw;

				fw2 *= perc;
				break;
		};

		transitionBackdrop = p_pathFloor(MMS2_moveDirec());

		PLEX_printTexture(499, transitionBackdrop, 0, 0, 1024, 768, fx2, fy2, fw2, fh2, true);
		PLEX_printTexture(9999, MMS2_currentRoomFloor(), 0, 0, 1024, 768, fx, fy, fw, fh, true);
	}

	enemGenerator = MMS2_currentEnemyGenerator(); // < DO NOT ASSIGN THIS ABOVE THIS POINT

	if(enemGenerator == NULL)
	{
		PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MINOR, MMS2_ERRORMESS_ONUPDATEGAME, MMS2_ERRORMESS_ENEMYGENERATOR);
		return false;
	}

	if(MMS2_playerIsNotShooting(time))
	{
		if(enemGenerator->start + enemGenerator->max <= MMS2_defeatedEnemyCount() && !MMS2_activateFinalBoss() && !MMS2_beginFinalBossIntro() && !MMS2_beginFinalBossOutro())
		{
			MMS2_drawArrow(64, 0, 64, 64, PLEX_UNIT(2), PLEX_WH(true) - PLEX_UNIT(4), 0, time);
			MMS2_drawArrow(128, 64, 64, 64, PLEX_UNIT(4), PLEX_WH(true) - PLEX_UNIT(3), 1, time);
			MMS2_drawArrow(64, 64, 64, 64, PLEX_UNIT(2), PLEX_WH(true) - PLEX_UNIT(2), 2, time);
			MMS2_drawArrow(0, 64, 64, 64, 0, PLEX_WH(true) - PLEX_UNIT(3), 3, time);

			if(PLEX_upKeyPress() && MMS2_pathOpen(0)){ MMS2_startMoving(0, time); }
			else if(PLEX_rightKeyPress() && MMS2_pathOpen(1)){ MMS2_startMoving(1, time); }
			else if(PLEX_downKeyPress() && MMS2_pathOpen(2)){ MMS2_startMoving(2, time); }
			else if(PLEX_leftKeyPress() && MMS2_pathOpen(3)){ MMS2_startMoving(3, time); }

			if(!p_currentRoom->contents->pathFlag && !MMS2_currentRoomCalm())
			{
				p_currentRoom->contents->pathFlag = true;
				MMS2_markFlagGen();
			}
		}

		if(MMS2_isNotMoving())
		{
			if(PLEX_isSpriteTheaterOver() && !MMS2_activateFinalBoss() && !MMS2_beginFinalBossIntro() && !MMS2_beginFinalBossOutro())
			{
				if(MMS2_currentRoomCalm()) MM_COMMON_playTheme(MM_COMMON_THEMEID_DESERTTOWN);
				else
				{
					if(MMS2_defeatedEnemyCount() < enemGenerator->start + enemGenerator->max) MM_COMMON_playTheme(MM_COMMON_THEMEID_PANIC);
					else MM_COMMON_playTheme(MM_COMMON_THEMEID_DESERTWINDS);
				}
			}
		}

		MMS2_checkMove(time);
	}

	return true;
}

void MMS2_endSystemRoom()
{
	MMS2_clearRoomSprites();

	if(p_currentRoom != NULL) p_destroyRoom(&p_currentRoom);
}

void MMS2_clearRoomSprites()
{
	PLEX_destroyTexture(p_background0);
	PLEX_destroyTexture(p_background1);
	PLEX_destroyTexture(p_background2);
	PLEX_destroyTexture(p_background3);
	PLEX_destroyTexture(p_background4);

	PLEX_destroyTexture(p_sky0);
	PLEX_destroyTexture(p_sky1);
	PLEX_destroyTexture(p_sky2);
	PLEX_destroyTexture(p_sky3);
	PLEX_destroyTexture(p_sky4);

	p_background0 = 0;
	p_background1 = 0;
	p_background2 = 0;
	p_background3 = 0;
	p_background4 = 0;

	p_sky0 = 0;
	p_sky1 = 0;
	p_sky2 = 0;
	p_sky3 = 0;
	p_sky4 = 0;
}

void MMS2_setCurrentRoom(const char* const title, const size_t background, const size_t skytex, const bool calm)
{
	if(p_currentRoom != NULL) p_destroyRoom(&p_currentRoom);

	p_currentRoom = p_genRoom(title, background, skytex);

	p_currentRoom->contents->calm = calm;
}

void MMS2_copyRoomNPCs(struct MMS_MINIGAME2ROOMCONTENTS* a, const struct MMS_MINIGAME2ROOMCONTENTS* const b)
{
	if(a == NULL)
	{
		PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, MMS2_ERRORMESS_ONCOPYROOMNPCS, MMS2_ERRORMESS_NPCCOPYTO);
		return;
	}

	if(b == NULL)
	{
		PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, MMS2_ERRORMESS_ONCOPYROOMNPCS, MMS2_ERRORMESS_NPCCOPYFROM);
		return;
	}

	p_clearRoomNPCs(a);

	a->townSquareNPCs.count = b->townSquareNPCs.count;

	a->townSquareNPCs.npc0.tex = b->townSquareNPCs.npc0.tex;
	a->townSquareNPCs.npc1.tex = b->townSquareNPCs.npc1.tex;
	a->townSquareNPCs.npc2.tex = b->townSquareNPCs.npc2.tex;
	a->townSquareNPCs.npc3.tex = b->townSquareNPCs.npc3.tex;
	a->townSquareNPCs.npc4.tex = b->townSquareNPCs.npc4.tex;

	a->townSquareNPCs.npc0.sprite = PLEX_copySprite(b->townSquareNPCs.npc0.sprite);
	a->townSquareNPCs.npc1.sprite = PLEX_copySprite(b->townSquareNPCs.npc1.sprite);
	a->townSquareNPCs.npc2.sprite = PLEX_copySprite(b->townSquareNPCs.npc2.sprite);
	a->townSquareNPCs.npc3.sprite = PLEX_copySprite(b->townSquareNPCs.npc3.sprite);
	a->townSquareNPCs.npc4.sprite = PLEX_copySprite(b->townSquareNPCs.npc4.sprite);

	a->townSquareNPCs.npc0.message = b->townSquareNPCs.npc0.message;
	a->townSquareNPCs.npc1.message = b->townSquareNPCs.npc1.message;
	a->townSquareNPCs.npc2.message = b->townSquareNPCs.npc2.message;
	a->townSquareNPCs.npc3.message = b->townSquareNPCs.npc3.message;
	a->townSquareNPCs.npc4.message = b->townSquareNPCs.npc4.message;

	a->townSquareNPCs.npc0.space = b->townSquareNPCs.npc0.space;
	a->townSquareNPCs.npc1.space = b->townSquareNPCs.npc1.space;
	a->townSquareNPCs.npc2.space = b->townSquareNPCs.npc2.space;
	a->townSquareNPCs.npc3.space = b->townSquareNPCs.npc3.space;
	a->townSquareNPCs.npc4.space = b->townSquareNPCs.npc4.space;

	a->saloonNPCs.count = b->saloonNPCs.count;

	a->saloonNPCs.npc0.tex = b->saloonNPCs.npc0.tex;
	a->saloonNPCs.npc1.tex = b->saloonNPCs.npc1.tex;
	a->saloonNPCs.npc2.tex = b->saloonNPCs.npc2.tex;
	a->saloonNPCs.npc3.tex = b->saloonNPCs.npc3.tex;
	a->saloonNPCs.npc4.tex = b->saloonNPCs.npc4.tex;

	a->saloonNPCs.npc0.sprite = PLEX_copySprite(b->saloonNPCs.npc0.sprite);
	a->saloonNPCs.npc1.sprite = PLEX_copySprite(b->saloonNPCs.npc1.sprite);
	a->saloonNPCs.npc2.sprite = PLEX_copySprite(b->saloonNPCs.npc2.sprite);
	a->saloonNPCs.npc3.sprite = PLEX_copySprite(b->saloonNPCs.npc3.sprite);
	a->saloonNPCs.npc4.sprite = PLEX_copySprite(b->saloonNPCs.npc4.sprite);

	a->saloonNPCs.npc0.message = b->saloonNPCs.npc0.message;
	a->saloonNPCs.npc1.message = b->saloonNPCs.npc1.message;
	a->saloonNPCs.npc2.message = b->saloonNPCs.npc2.message;
	a->saloonNPCs.npc3.message = b->saloonNPCs.npc3.message;
	a->saloonNPCs.npc4.message = b->saloonNPCs.npc4.message;

	a->saloonNPCs.npc0.space = b->saloonNPCs.npc0.space;
	a->saloonNPCs.npc1.space = b->saloonNPCs.npc1.space;
	a->saloonNPCs.npc2.space = b->saloonNPCs.npc2.space;
	a->saloonNPCs.npc3.space = b->saloonNPCs.npc3.space;
	a->saloonNPCs.npc4.space = b->saloonNPCs.npc4.space;

	a->jailNPCs.count = b->jailNPCs.count;

	a->jailNPCs.npc0.tex = b->jailNPCs.npc0.tex;
	a->jailNPCs.npc1.tex = b->jailNPCs.npc1.tex;
	a->jailNPCs.npc2.tex = b->jailNPCs.npc2.tex;
	a->jailNPCs.npc3.tex = b->jailNPCs.npc3.tex;
	a->jailNPCs.npc4.tex = b->jailNPCs.npc4.tex;

	a->jailNPCs.npc0.sprite = PLEX_copySprite(b->jailNPCs.npc0.sprite);
	a->jailNPCs.npc1.sprite = PLEX_copySprite(b->jailNPCs.npc1.sprite);
	a->jailNPCs.npc2.sprite = PLEX_copySprite(b->jailNPCs.npc2.sprite);
	a->jailNPCs.npc3.sprite = PLEX_copySprite(b->jailNPCs.npc3.sprite);
	a->jailNPCs.npc4.sprite = PLEX_copySprite(b->jailNPCs.npc4.sprite);

	a->jailNPCs.npc0.message = b->jailNPCs.npc0.message;
	a->jailNPCs.npc1.message = b->jailNPCs.npc1.message;
	a->jailNPCs.npc2.message = b->jailNPCs.npc2.message;
	a->jailNPCs.npc3.message = b->jailNPCs.npc3.message;
	a->jailNPCs.npc4.message = b->jailNPCs.npc4.message;

	a->jailNPCs.npc0.space = b->jailNPCs.npc0.space;
	a->jailNPCs.npc1.space = b->jailNPCs.npc1.space;
	a->jailNPCs.npc2.space = b->jailNPCs.npc2.space;
	a->jailNPCs.npc3.space = b->jailNPCs.npc3.space;
	a->jailNPCs.npc4.space = b->jailNPCs.npc4.space;

	a->mayor.sprite = PLEX_copySprite(b->mayor.sprite);
	a->olDoc.sprite = PLEX_copySprite(b->olDoc.sprite);
	a->olDog.sprite = PLEX_copySprite(b->olDog.sprite);

	a->mayor.message = b->mayor.message;
	a->olDoc.message = b->olDoc.message;
	a->olDog.message = b->olDog.message;

	a->hasSheriff = b->hasSheriff;
	a->hasDoc = b->hasDoc;
	a->hasMayor = b->hasMayor;
	a->mayorSpeech = b->mayorSpeech;
}

void MMS2_genNextPath(const size_t chapter2SpriteTex, const size_t chapter2SpriteTex2, const size_t chapter2SpriteTex3, const size_t chapter2SpriteTex4, const uint64_t time)
{
	switch(p_trailOn)
	{
		case 0: p_genTrail0Path(chapter2SpriteTex, chapter2SpriteTex2, time); break;
		case 1: p_genTrail1Path(chapter2SpriteTex, chapter2SpriteTex2, time); break;
		case 2: p_genTrail2Path(chapter2SpriteTex, chapter2SpriteTex2, time); break;
		case 3: p_genTrail3Path(chapter2SpriteTex, chapter2SpriteTex2, time); break;
		default: MMS2_markPenultimateCutscene(); break;
	}
}

void MMS2_startMoving(const size_t direc, const uint64_t time)
{
	p_moveDirec = direc;
	p_startMoveTime = time;
}

void MMS2_checkMove(const uint64_t time)
{
	uint64_t duration = 0;

	if(p_moveDirec != 5)
	{
		duration = time - p_startMoveTime;

		MMS2_clearCoverCount();
		MMS2_clearTreasureCount();
		MMS2_clearEnemyCount();

		if(duration < MMS2_ROOMMOVEDURATION) return;

		p_moveRoom(p_moveDirec, p_currentRoom, time);

		MMS2_resetEnemyGenerator(p_currentRoom, time);
		MMS2_startEnemyGenerator(p_currentRoom, time);

		MMS2_useCoverGenerator(p_currentRoom, time);

		p_moveDirec = 5;
	}
}

bool MMS2_pointCheckTown(const size_t chapter2SpriteTex, const size_t chapter2SpriteTex2, const uint64_t time)
{
	if(p_currentRoom != NULL) p_destroyRoom(&p_currentRoom);

	if(MMS2_points() < MMS2_POINTPATH0)
	{
		p_currentRoom = p_genRoom(MMS2_LANGUAGE_TOWN0_TITLE, p_background0, p_sky0);

		if(p_currentRoom == NULL)
		{
			PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_FATAL, MMS2_ERRORMESS_ONPOINTCHECKPATH0, MMS2_ERRORMESS_CURRENTROOM);
			return false;
		}

		MMS2_setAsTown0(chapter2SpriteTex, p_currentRoom, time);
		p_trailOn = 0;
	}else if(MMS2_points() < MMS2_POINTPATH1){
		p_currentRoom = p_genRoom(MMS2_LANGUAGE_TOWN1_TITLE, p_background0, p_sky0);

		if(p_currentRoom == NULL)
		{
			PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_FATAL, MMS2_ERRORMESS_ONPOINTCHECKPATH1, MMS2_ERRORMESS_CURRENTROOM);
			return false;
		}

		MMS2_setAsTown1(chapter2SpriteTex, chapter2SpriteTex2, p_currentRoom, time);
		p_trailOn = 1;
	}else if(MMS2_points() < MMS2_POINTPATH2){
		p_currentRoom = p_genRoom(MMS2_LANGUAGE_TOWN2_TITLE, p_background0, p_sky0);

		if(p_currentRoom == NULL)
		{
			PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_FATAL, MMS2_ERRORMESS_ONPOINTCHECKPATH2, MMS2_ERRORMESS_CURRENTROOM);
			return false;
		}

		MMS2_setAsTown2(chapter2SpriteTex, chapter2SpriteTex2, p_currentRoom, time);
		p_trailOn = 2;
	}else if(MMS2_points() < MMS2_POINTPATH3){
		p_currentRoom = p_genRoom(MMS2_LANGUAGE_TOWN3_TITLE, p_background0, p_sky0);

		if(p_currentRoom == NULL)
		{
			PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_FATAL, MMS2_ERRORMESS_ONPOINTCHECKPATH3, MMS2_ERRORMESS_CURRENTROOM);
			return false;
		}

		MMS2_setAsTown3(chapter2SpriteTex, chapter2SpriteTex2, p_currentRoom, time);
		p_trailOn = 3;
	}else{
		p_currentRoom = p_genRoom(MMS2_LANGUAGE_TOWN4_TITLE, p_background0, p_sky0);

		if(p_currentRoom == NULL)
		{
			PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_FATAL, MMS2_ERRORMESS_ONPOINTCHECKPATH4, MMS2_ERRORMESS_CURRENTROOM);
			return false;
		}

		MMS2_setAsTown4(chapter2SpriteTex, chapter2SpriteTex2, p_currentRoom, time);
		p_trailOn = 4;
	}

	return true;
}

void MMS2_markFlagGen(){ p_flagGen = true; }

bool MMS2_flagGen(){ return p_flagGen; }

bool MMS2_pathOpen(const size_t direc)
{
	if(p_currentRoom == NULL)
	{
		PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MINOR, MMS2_ERRORMESS_ONOPENINGPATH, MMS2_ERRORMESS_CURRENTROOM);
		return false;
	}

	switch(direc)
	{
		case 0: return p_currentRoom->path->up;
		case 1: return p_currentRoom->path->right;
		case 2: return p_currentRoom->path->down;
		case 3: return p_currentRoom->path->left;
	};

	return false;
}

bool MMS2_pathCalm(const size_t direc)
{
	MMS_MINIGAME2ROOMCONTENTS* contents = NULL;

	if(p_currentRoom == NULL)
	{
		PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MINOR, MMS2_ERRORMESS_ONCHECKINGPATHCALM, MMS2_ERRORMESS_CURRENTROOM);
		return false;
	}

	contents = p_getCurrentRoomPathContents(direc);

	if(contents == NULL)
	{
		PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MINOR, MMS2_ERRORMESS_ONCHECKINGPATHCALM, MMS2_ERRORMESS_CURRENTROOMPATH);
		return false;
	}

	return contents->calm;
}

PLEX_FAKESTRING_25 MMS2_currentRoomName()
{
	if(p_currentRoom == NULL)
	{
		PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MINOR, MMS2_ERRORMESS_ONRETRIEVINGCURRENTROOMNAME, MMS2_ERRORMESS_CURRENTROOM);
		return PLEX_blankString25();
	}

	return p_currentRoom->contents->name;
}

bool MMS2_currentRoomCalm()
{
	if(!p_currentRoom)
	{
		PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MINOR, MMS2_ERRORMESS_ONRETRIEVINGCURRENTROOMCALMNESS, MMS2_ERRORMESS_CURRENTROOM);
		return false;
	}

	return p_currentRoom->contents->calm;
}

size_t MMS2_currentRoomFloor()
{
	if(!p_currentRoom)
	{
		PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MINOR, MMS2_ERRORMESS_ONRETRIEVINGCURRENTROOMFLOOR, MMS2_ERRORMESS_CURRENTROOM);
		return false;
	}

	return p_currentRoom->contents->floor;
}

size_t MMS2_currentRoomSky()
{
	if(!p_currentRoom)
	{
		PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MINOR, MMS2_ERRORMESS_ONRETRIEVINGCURRENTROOMSKY, MMS2_ERRORMESS_CURRENTROOM);
		return false;
	}

	return p_currentRoom->contents->sky;
}

PLEX_FAKESTRING_500 MMS2_currentMayorMessage()
{
	if(p_currentRoom == NULL)
	{
		PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MINOR, MMS2_ERRORMESS_ONRETRIEVINGCURRENTROOMMAYORMESSAGE, MMS2_ERRORMESS_CURRENTROOM);
		return PLEX_blankString500();
	}

	return p_currentRoom->contents->mayorMessage;
}

struct MMS_MINIGAME2ENEMYGENERATOR* MMS2_currentEnemyGenerator()
{
	if(p_currentRoom == NULL)
	{
		PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MINOR, MMS2_ERRORMESS_ONRETRIEVINGCURRENTENEMYGENERATOR, MMS2_ERRORMESS_CURRENTROOM);
		return NULL;
	}

	return &p_currentRoom->contents->enemGenerator;
}

struct MMS_MINIGAME2ROOM* MMS2_currentRoom(){ return p_currentRoom; }

size_t MMS2_backgroundGraphic(const size_t index)
{
	switch(index)
	{
		case 0: return p_background0;
		case 1: return p_background1;
		case 2: return p_background2;
		case 3: return p_background3;
		case 4: return p_background4;
	};

	return 0;
}

size_t MMS2_skyGraphic(const size_t index)
{
	switch(index)
	{
		case 0: return p_sky0;
		case 1: return p_sky1;
		case 2: return p_sky2;
		case 3: return p_sky3;
		case 4: return p_sky4;
	};

	return 0;
}

size_t MMS2_moveDirec(){ return p_moveDirec; }

bool MMS2_isNotMoving(){ return p_moveDirec == 5; }

bool MMS2_isMoving(){ return p_moveDirec != 5; }
