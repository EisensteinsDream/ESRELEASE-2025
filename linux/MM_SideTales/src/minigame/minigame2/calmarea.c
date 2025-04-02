#include "minigame/minigame2/minigame2.h"

static size_t p_townArea = 0;

static size_t p_quoteBubble = 0;
static size_t p_quoteBubble2 = 0;

static size_t p_townSquareCalmFloor = 0;
static size_t p_saloonCalmFloor = 0;
static size_t p_jailCalmFloor = 0;
static size_t p_jailCalmFloor2 = 0;
static size_t p_mayorsOfficeCalmFloor = 0;
static size_t p_armoryCalmFloor = 0;
static size_t p_townMedicCalmFloor = 0;

static size_t p_mayorStatementBack = 0;

static bool p_mayorCutaway = false;

// selects the NPC from the NPC set by index. A bad index will simply return the NPC at spot 0. This ignores the NPC count.

static MMS_MINIGAME2NPC* p_selectNPC(const size_t index, MMS_MINIGAME2NPCSET* npcSet)
{
	switch(index)
	{
		case 1:
			return &npcSet->npc1;
			break;

		case 2:
			return &npcSet->npc2;
			break;

		case 3:
			return &npcSet->npc3;
			break;

		case 4:
			return &npcSet->npc4;
			break;

		default: break;
	};

	return &npcSet->npc0;
}

// creates a new NPC struct with assigned values in arguments

static MMS_MINIGAME2NPC p_createNPC(const char* const message, const PLEX_RECT space, const double wperc, const double hperc, const size_t tex, const uint64_t animSpeed, const size_t stillFrameStart, const size_t frameStart, const size_t frameCount, const uint64_t time)
{
	MMS_MINIGAME2NPC ret;

	PLEX_ANIMATION_PLATE animPlate;

	PLEX_ANIMATION* still = NULL;
	PLEX_ANIMATION* animated = NULL;

	memset(&ret, 0, sizeof(ret));

	ret.tex = tex;
	ret.space = space;
	ret.message = PLEX_createString50(message);

	if(tex)
	{
		animPlate = PLEX_createAnimationPlate(wperc, hperc, tex);

		ret.sprite = PLEX_genSprite(&animPlate);

		PLEX_addAnimation(ret.sprite, 0, time);
		PLEX_addAnimation(ret.sprite, animSpeed, time);

		still = PLEX_getAnimation(0, ret.sprite);
		animated = PLEX_getAnimation(1, ret.sprite);

		PLEX_addAnimationFrame(stillFrameStart, still);

		for(size_t ze = 0; ze < frameCount; ++ze) PLEX_addAnimationFrame(frameStart + ze, animated);

		PLEX_startSprite(time, ret.sprite);
	}else{
		PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_ZEROVALUE, PLEX_ERROR_SEVERITY_MINOR, MMS2_ERRORMESS_ONCREATENPC, MMS2_ERRORMESS_NPCTEX);
		ret.sprite = NULL;
	}

	return ret;
}

// selects the last NPC in a set

static MMS_MINIGAME2NPC* p_selectLastNPC(MMS_MINIGAME2NPCSET* npcSet)
{
	return p_selectNPC(npcSet->count - 1, npcSet);
}

// draws an npc

static bool p_drawNPC(const size_t layer, const size_t fontPlate, MMS_MINIGAME2NPC* npc, const uint64_t time)
{
	// quote bubble width and height

	const uint32_t qbw = PLEX_WW(true);
	const uint32_t qbh = PLEX_WH(true)/2;

	// draw space

	const uint32_t dx = PLEX_UNIT(npc->space.origin.x);
	const uint32_t dy = PLEX_UNIT(npc->space.origin.y);
	const uint32_t dw = PLEX_UNIT(npc->space.dimens.w);
	const uint32_t dh = PLEX_UNIT(npc->space.dimens.h);

	// quote bubble font width and font height

	uint32_t qfw = 0;
	uint32_t qfh = 0;

	// quote bubble arrow width and height

	uint32_t qbaw = 0;
	uint32_t qbah = 0;

	uint8_t r = 0;
	uint8_t g = 0;
	uint8_t b = 0;

	bool highlight = false;

	if(MMS2_isMoving()) return false;

	qfw = qbw/(npc->message.len + 2);

	if(qfw > qbw/25) qfw = qbw/25;

	qfh = qfw * 2;

	qbah = dy - PLEX_UNIT(0.5) - qbh/2;
	qbaw = qbah * 2;

	if(PLEX_mouseInside(dx, dy, dw, dh, true))
	{
		PLEX_printTexture(0, p_quoteBubble2, 0, 0, 512, 228, dx + dw/2 - qbaw/2, dy - qbah - PLEX_UNIT(0.5), qbaw, qbah, true);

		PLEX_printTexture(0, p_quoteBubble, 0, 0, 512, 512, 0, 0, qbw, qbh, true);

		PLEX_printFontStringTinted(0, PLEX_STANDNUM_FW, PLEX_STANDNUM_FH, qbw/2 - (qfw * npc->message.len)/2, qbh/4, qfw, qfh, 0, 0, 0, PLEX_fts(npc->message), PLEX_LANGUAGE_ALPHASTRING, fontPlate, true);

		if(PLEX_leftClick())
		{
			r = 255;
			g = 255;
			b = 0;
		}else{
			r = 255;
			g = 255;
			b = 255;
		}

		highlight = true;
	}

	if(npc->tex)
	{
		size_t aniIndex = 0;

		if(highlight)
		{
			if(PLEX_isSpriteStopped(npc->sprite)) PLEX_startSprite(time, npc->sprite);

			aniIndex = 1;
		}else PLEX_stopSprite(npc->sprite);

		PLEX_drawSprite(layer, aniIndex, dx, dy, dw, dh, npc->sprite, true, time);
	}else PLEX_drawRect(layer, dx, dy, dw, dh, r, g, b, 255, PLEX_UNIT(0.5), true);

	return highlight;
}

// adds an NPC to the town square

static void p_addNPCTownSquare(const char* const message, const PLEX_RECT space, const double wperc, const double hperc, const size_t tex, const uint64_t animSpeed, const size_t stillFrameStart, const size_t frameStart, const size_t frameCount, MMS_MINIGAME2ROOM* room, const uint64_t time)
{
	MMS_MINIGAME2NPC* npc = NULL;

	if(room->contents->townSquareNPCs.count > 4) return;

	++room->contents->townSquareNPCs.count; // < must be before selectLastNPC

	npc = p_selectLastNPC(&room->contents->townSquareNPCs);

	MMS2_clearNPC(npc);

	*npc = p_createNPC(message, space, wperc, hperc, tex, animSpeed, stillFrameStart, frameStart, frameCount, time);
}

// adds an NPC to the saloon

static void p_addNPCSaloon(const char* const message, const PLEX_RECT space, const double wperc, const double hperc, const size_t tex, const uint64_t animSpeed, const size_t stillFrameStart, const size_t frameStart, const size_t frameCount, MMS_MINIGAME2ROOM* room, const uint64_t time)
{
	MMS_MINIGAME2NPC* npc = NULL;

	if(room->contents->saloonNPCs.count > 4) return;

	++room->contents->saloonNPCs.count; // < must be before selectLastNPC

	npc = p_selectLastNPC(&room->contents->saloonNPCs);

	*npc = p_createNPC(message, space, wperc, hperc, tex, animSpeed, stillFrameStart, frameStart, frameCount, time);
}

// adds an NPC to jail

static void p_addNPCJail(const char* const message, const size_t cell, const double wperc, const double hperc, const size_t tex, const uint64_t animSpeed, const size_t stillFrameStart, const size_t frameStart, const size_t frameCount, MMS_MINIGAME2ROOM* room, const uint64_t time)
{
	MMS_MINIGAME2NPC* npc = NULL;
	PLEX_RECT space;

	if(cell > 2) return;

	if(room->contents->jailNPCs.count > 2) return;

	++room->contents->jailNPCs.count; // < must be before selectLastNPC

	npc = p_selectLastNPC(&room->contents->jailNPCs);

	space.origin.y = PLEX_WIDTHUNITMAX(true)/4 + 2;
	space.origin.x = 10.5 + (cell * 4.5);

	space.dimens = PLEX_convDimens(2, 4);

	*npc = p_createNPC(message, space, wperc, hperc, tex, animSpeed, stillFrameStart, frameStart, frameCount, time);
}

// adds an NPC to sheriff

static void p_addSheriffNPC(const char* const message, const double w, const double wperc, const double hperc, const size_t tex, const uint64_t animSpeed, const size_t stillFrameStart, const size_t frameStart, const size_t frameCount, MMS_MINIGAME2ROOM* room, const uint64_t time)
{
	MMS_MINIGAME2NPC* npc = NULL;
	PLEX_RECT space;

	if(room->contents->hasSheriff) return;

	npc = p_selectNPC(3, &room->contents->jailNPCs);

	space.origin.y = PLEX_HEIGHTUNITMAX(true) - 9;
	space.origin.x = PLEX_WIDTHUNITMAX(true)/2 - w/2.0;

	space.dimens = PLEX_convDimens(w, 4);

	MMS2_clearNPC(npc);

	*npc = p_createNPC(message, space, wperc, hperc, tex, animSpeed, stillFrameStart, frameStart, frameCount, time);

	room->contents->hasSheriff = true;
}

// adds an NPC to ol' doc

static void p_addOlDocNPC(const size_t chapter2SpriteTex, const size_t dogFrame, MMS_MINIGAME2ROOM* room, const uint64_t time)
{
	PLEX_RECT space;
	PLEX_RECT space2;

	if(room->contents->hasDoc) return;

	space = PLEX_convRect(PLEX_convPoint(PLEX_WIDTHUNITMAX()/2 - 2.5, PLEX_HEIGHTUNITMAX() - 10.5), PLEX_convDimens(4, 4));

	room->contents->olDoc = p_createNPC(MMS2_LANGUAGE_OLDDOCDIALOG, space, 0.125, 0.03125, chapter2SpriteTex, 500, 164, 165, 2, time);

	space2 = space;

	space2.origin.x += 4;
	space2.origin.y += 2;
	space2.dimens.w = 3;
	space2.dimens.h = 3;

	MMS2_clearNPC(&room->contents->olDog);

	room->contents->olDog = p_createNPC(MMS2_LANGUAGE_OLDDOGDIALOG, space2, 0.125, 0.03125, chapter2SpriteTex, 0, dogFrame, dogFrame, 1, time);

	room->contents->hasDoc = true;
}

// adds an NPC to mayor

static void p_addMayorNPC(const size_t chapter2SpriteTex, const char* const message, const char* const longMessage, MMS_MINIGAME2ROOM* room, const uint64_t time)
{
	PLEX_RECT space;

	if(room->contents->hasMayor) return;

	space = PLEX_convRect(PLEX_convPoint(PLEX_WIDTHUNITMAX()/2 - 1.5, PLEX_HEIGHTUNITMAX() - 10.5), PLEX_convDimens(3, 4));

	MMS2_clearNPC(&room->contents->mayor);

	room->contents->mayor = p_createNPC(message, space, 0.125, 0.03125, chapter2SpriteTex, 1000, 152, 152, 2, time);

	room->contents->mayorMessage = PLEX_createString500(longMessage);

	room->contents->hasMayor = true;
}

static bool p_placeGunInShop(const size_t index, const size_t spot, const size_t fontPlate)
{
	const PLEX_POINT points[] =
	{
		PLEX_convPoint(6.25, 5),
		PLEX_convPoint(8.75, 4.5),
		PLEX_convPoint(11, 4),
		PLEX_convPoint(18.75, 4),
		PLEX_convPoint(21, 4.5),
		PLEX_convPoint(23.5, 5),
		PLEX_convPoint(6.25, 9),
		PLEX_convPoint(8.75, 8.5),
		PLEX_convPoint(11, 8),
		PLEX_convPoint(18.75, 8),
		PLEX_convPoint(21, 8.5),
		PLEX_convPoint(23.5, 9),
		PLEX_convPoint(14.5, 7)
	};

	uint32_t dx = 0, dy = 0, dw = 0, dh = 0;

	bool highlight = false;
	bool affordable = false;

	MMS_MINIGAME2GUN* const gun = MMS2_gun(index);

	PLEX_RECT place = PLEX_convRect(points[spot], PLEX_convDimens(2.5, 2.5));

	dx = PLEX_UNIT(place.origin.x);
	dy = PLEX_UNIT(place.origin.y);
	dw = PLEX_UNIT(place.dimens.w);
	dh = PLEX_UNIT(place.dimens.h);

	highlight = PLEX_mouseInside(dx, dy, dw, dh, true);

	affordable = gun->cost <= MMS2_cash();

	if(affordable) PLEX_printTexture(1, gun->icon, 0, 0, 256, 256, dx, dy, dw, dh, true);
	else PLEX_printTextureTinted(1, gun->icon, 0, 0, 256, 256, dx, dy, dw, dh, 0, 0, 0, true);

	if(highlight)
	{
		PLEX_FAKESTRING_50 costString = PLEX_createString50(MMS2_LANGUAGE_CASHSTRING_START);
		PLEX_FAKESTRING_50 costString2 = PLEX_createStringFromNumber50(gun->cost);

		costString = PLEX_mergeString50(costString, costString2);

		PLEX_drawRect(MMS2_DRAWLAYER_GUNGUI, dx, dy, dw, dh, 0, 0, 0, 255, PLEX_UNIT(0.25), true);

		PLEX_drawLabel(MMS2_DRAWLAYER_GUNGUI, PLEX_fts(gun->name), PLEX_STANDNUM_FW, PLEX_STANDNUM_FH, 255, 255, 255, 255, PLEX_UNIT(6), PLEX_UNIT(13), PLEX_WW(true)/2, PLEX_UNIT(2), 0.1, 0.15, 0.8, 0.8, PLEX_UNIT(0.05), PLEX_LANGUAGE_ALPHASTRING, fontPlate, 0, 0, 0, 0, 0, true);

		PLEX_drawLabel(MMS2_DRAWLAYER_GUNGUI, PLEX_fts(costString), PLEX_STANDNUM_FW, PLEX_STANDNUM_FH, 255, 255, 255, 255, PLEX_UNIT(6), PLEX_UNIT(15), PLEX_WW(true)/2, PLEX_UNIT(2), 0.1, 0.15, 0.8, 0.8, PLEX_UNIT(0.05), PLEX_LANGUAGE_ALPHASTRING, fontPlate, 0, 0, 0, 0, 0, true);
	}

	return highlight && PLEX_leftClick() && affordable;
}

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

void MMS2_setSystemCalmArea()
{
	p_mayorCutaway = false;

	p_townArea = 0;
}

void MMS2_initSystemCalmArea()
{
	if(!p_quoteBubble) p_quoteBubble = PLEX_loadTextureFromFileOrHeaderless(512, 512, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_QUOTEBUBBLE, MMS2_FILEPATH_HEADERLESS_QUOTEBUBBLE);
	if(!p_quoteBubble2) p_quoteBubble2 = PLEX_loadTextureFromFileOrHeaderless(512, 228, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_QUOTEBUBBLE2, MMS2_FILEPATH_HEADERLESS_QUOTEBUBBLE2);

	if(!p_townSquareCalmFloor) p_townSquareCalmFloor = PLEX_loadTextureFromFileOrHeaderless(1024, 1024, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_TOWNSQUARECALMFLOOR, MMS2_FILEPATH_HEADERLESS_TOWNSQUARECALMFLOOR);
	if(!p_saloonCalmFloor) p_saloonCalmFloor = PLEX_loadTextureFromFileOrHeaderless(1024, 1024, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_SALOONCALMFLOOR, MMS2_FILEPATH_HEADERLESS_SALOONCALMFLOOR);
	if(!p_jailCalmFloor) p_jailCalmFloor = PLEX_loadTextureFromFileOrHeaderless(1024, 1024, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_JAILCALMFLOOR, MMS2_FILEPATH_HEADERLESS_JAILCALMFLOOR);
	if(!p_jailCalmFloor2) p_jailCalmFloor2 = PLEX_loadTextureFromFileOrHeaderless(1024, 1024, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_JAIL2CALMFLOOR, MMS2_FILEPATH_HEADERLESS_JAIL2CALMFLOOR);
	if(!p_mayorsOfficeCalmFloor) p_mayorsOfficeCalmFloor = PLEX_loadTextureFromFileOrHeaderless(1024, 1024, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_MAYORSOFFICECALMFLOOR, MMS2_FILEPATH_HEADERLESS_MAYORSOFFICECALMFLOOR);
	if(!p_armoryCalmFloor) p_armoryCalmFloor = PLEX_loadTextureFromFileOrHeaderless(1024, 1024, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_ARMORYCALMFLOOR, MMS2_FILEPATH_HEADERLESS_ARMORYCALMFLOOR);
	if(!p_townMedicCalmFloor) p_townMedicCalmFloor = PLEX_loadTextureFromFileOrHeaderless(1024, 1024, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_DOCSHOUSECALMFLOOR, MMS2_FILEPATH_HEADERLESS_DOCSHOUSECALMFLOOR);

	if(!p_mayorStatementBack) p_mayorStatementBack = PLEX_loadTextureFromFileOrHeaderless(1024, 1024, 255, 255, 255, 255, 0, MMS2_FILEPATH_TEX_MAYORSTATEMENTBACK, MMS2_FILEPATH_HEADERLESS_MAYORSTATEMENTBACK);

	p_townArea = 0;
}

void MMS2_checkRunSystemCalmArea(const size_t chapter2SpriteTex, const size_t chapter2SpriteTex2, const size_t fontPlate, const uint64_t time)
{
	if(!MMS2_currentRoomCalm()) return;

	MMS2_drawRestoreTownButton(chapter2SpriteTex, chapter2SpriteTex2, fontPlate, time);

	if(!MMS2_mayorCutaway())
	{
		MMS2_runCalmMenu(fontPlate, time);
		MMS2_runCalmNoMayorCutaway(fontPlate, time);
	}else{
		if(MMS2_checkMayorMessage(fontPlate)) return;
	}

	MMS2_unsetCustomCursor();
}

void MMS2_endSystemCalmArea()
{
	MMS2_clearCalmAreaSprites();
}

void MMS2_clearCalmAreaSprites()
{
	PLEX_destroyTexture(p_quoteBubble);
	PLEX_destroyTexture(p_quoteBubble2);

	PLEX_destroyTexture(p_townSquareCalmFloor);
	PLEX_destroyTexture(p_saloonCalmFloor);
	PLEX_destroyTexture(p_jailCalmFloor);
	PLEX_destroyTexture(p_jailCalmFloor2);
	PLEX_destroyTexture(p_mayorsOfficeCalmFloor);
	PLEX_destroyTexture(p_armoryCalmFloor);
	PLEX_destroyTexture(p_townMedicCalmFloor);

	PLEX_destroyTexture(p_mayorStatementBack);

	p_quoteBubble = 0;
	p_quoteBubble2 = 0;

	p_townSquareCalmFloor = 0;
	p_saloonCalmFloor = 0;
	p_jailCalmFloor = 0;
	p_jailCalmFloor2 = 0;
	p_mayorsOfficeCalmFloor = 0;
	p_armoryCalmFloor = 0;
	p_townMedicCalmFloor = 0;

	p_mayorStatementBack = 0;
}

void MMS2_clearNPC(struct MMS_MINIGAME2NPC* npc)
{
	if(npc == NULL)
	{
		PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_ZEROVALUE, PLEX_ERROR_SEVERITY_BADSTYLE, MMS2_ERRORMESS_ONUPDATESELECTGUN, MMS2_ERRORMESS_NPC);
		return;
	}

	if(npc->sprite != NULL) PLEX_destroySprite(&npc->sprite);
}

void MMS2_setAsTown0(const size_t chapter2SpriteTex, struct MMS_MINIGAME2ROOM* room, const uint64_t time)
{
	p_addNPCTownSquare(MMS2_LANGUAGE_TOWN0_TOWNSQUARE0, PLEX_convRect(PLEX_convPoint(15, 10), PLEX_convDimens(2, 4)), 0.0625, 0.03125, chapter2SpriteTex, 500, 308, 309, 2, room, time);

	p_addNPCSaloon(MMS2_LANGUAGE_TOWN0_BAR0, PLEX_convRect(PLEX_convPoint(10, 14), PLEX_convDimens(2, 4)), 0.0625, 0.03125, chapter2SpriteTex, 1000, 316, 317, 2, room, time);

	p_addNPCSaloon(MMS2_LANGUAGE_TOWN0_BAR1, PLEX_convRect(PLEX_convPoint(14, 11.5), PLEX_convDimens(2, 4)), 0.0625, 0.03125, chapter2SpriteTex, 0, 322, 323, 1, room, time);

	p_addNPCSaloon(MMS2_LANGUAGE_TOWN0_BAR2, PLEX_convRect(PLEX_convPoint(16, 11.5), PLEX_convDimens(2, 4)), 0.0625, 0.03125, chapter2SpriteTex, 0, 324, 325, 1, room, time);

	p_addNPCSaloon(MMS2_LANGUAGE_TOWN0_BAR3, PLEX_convRect(PLEX_convPoint(20, 13), PLEX_convDimens(2, 4)), 0.0625, 0.03125, chapter2SpriteTex, 1000, 319, 320, 2, room, time);

	p_addNPCSaloon(MMS2_LANGUAGE_TOWN0_BAR4, PLEX_convRect(PLEX_convPoint(23, 15.5), PLEX_convDimens(2, 4)), 0.0625, 0.03125, chapter2SpriteTex, 0, 326, 327, 1, room, time);

	p_addNPCJail(MMS2_LANGUAGE_TOWN0_JAIL0, 0, 0.0625, 0.03125, chapter2SpriteTex, 0, 314, 315, 1, room, time);
	p_addNPCJail(MMS2_LANGUAGE_TOWN0_JAIL1, 1, 0.0625, 0.03125, chapter2SpriteTex, 0, 314, 315, 1, room, time);
	p_addNPCJail(MMS2_LANGUAGE_TOWN0_JAIL2, 2, 0.0625, 0.03125, chapter2SpriteTex, 0, 314, 315, 1, room, time);

	p_addSheriffNPC(MMS2_LANGUAGE_TOWN0_SHERIFF, 2, 0.0625, 0.03125, chapter2SpriteTex, 250, 311, 312, 2, room, time);

	p_addOlDocNPC(chapter2SpriteTex, 167, room, time);

	p_addMayorNPC(chapter2SpriteTex, MMS2_LANGUAGE_TOWN0_MAYORDIALOG, MMS2_LANGUAGE_TOWN0_MAYORDIALOGMISSION, room, time);
}

void MMS2_setAsTown1(const size_t chapter2SpriteTex, const size_t chapter2SpriteTex2, struct MMS_MINIGAME2ROOM* room, const uint64_t time)
{
	p_addNPCTownSquare(MMS2_LANGUAGE_TOWN1_TOWNSQUARE0, PLEX_convRect(PLEX_convPoint(15, 10), PLEX_convDimens(2, 4)), 0.0625, 0.03125, chapter2SpriteTex, 500, 480, 481, 2, room, time);
	p_addNPCTownSquare(MMS2_LANGUAGE_TOWN1_TOWNSQUARE1, PLEX_convRect(PLEX_convPoint(10, 12), PLEX_convDimens(2, 4)), 0.0625, 0.03125, chapter2SpriteTex, 200, 483, 484, 2, room, time);
	p_addNPCTownSquare(MMS2_LANGUAGE_TOWN1_TOWNSQUARE2, PLEX_convRect(PLEX_convPoint(19, 9), PLEX_convDimens(2, 4)), 0.0625, 0.03125, chapter2SpriteTex, 500, 486, 487, 2, room, time);
	p_addNPCTownSquare(MMS2_LANGUAGE_TOWN1_TOWNSQUARE3, PLEX_convRect(PLEX_convPoint(21.5, 9.5), PLEX_convDimens(2, 4)), 0.0625, 0.03125, chapter2SpriteTex, 500, 489, 490, 2, room, time);
	p_addNPCTownSquare(MMS2_LANGUAGE_TOWN1_TOWNSQUARE4, PLEX_convRect(PLEX_convPoint(20, 13), PLEX_convDimens(2, 4)), 0.0625, 0.03125, chapter2SpriteTex, 500, 492, 493, 2, room, time);

	p_addNPCSaloon(MMS2_LANGUAGE_TOWN1_BAR0, PLEX_convRect(PLEX_convPoint(8, 14), PLEX_convDimens(2, 4)), 0.0625, 0.03125, chapter2SpriteTex, 300, 495, 510, 2, room, time);
	p_addNPCSaloon(MMS2_LANGUAGE_TOWN1_BAR1, PLEX_convRect(PLEX_convPoint(12, 12), PLEX_convDimens(2, 4)), 0.0625, 0.03125, chapter2SpriteTex2, 500, 2, 3, 2, room, time);
	p_addNPCSaloon(MMS2_LANGUAGE_TOWN1_BAR2, PLEX_convRect(PLEX_convPoint(15, 14), PLEX_convDimens(2, 4)), 0.0625, 0.03125, chapter2SpriteTex2, 0, 0, 1, 1, room, time);
	p_addNPCSaloon(MMS2_LANGUAGE_TOWN1_BAR3, PLEX_convRect(PLEX_convPoint(19, 12), PLEX_convDimens(2, 4)), 0.0625, 0.03125, chapter2SpriteTex2, 500, 5, 6, 2, room, time);

	p_addNPCSaloon(MMS2_LANGUAGE_TOWN1_BAR4, PLEX_convRect(PLEX_convPoint(22, 15), PLEX_convDimens(2, 4)), 0.0625, 0.03125, chapter2SpriteTex2, 800, 8, 8, 4, room, time);

	p_addNPCJail(MMS2_LANGUAGE_TOWN1_JAIL0, 0, 0.0625, 0.03125, chapter2SpriteTex, 0, 314, 315, 1, room, time);
	p_addNPCJail(MMS2_LANGUAGE_TOWN1_JAIL1, 1, 0.0625, 0.03125, chapter2SpriteTex, 0, 314, 315, 1, room, time);
	p_addNPCJail(MMS2_LANGUAGE_TOWN1_JAIL2, 2, 0.0625, 0.03125, chapter2SpriteTex, 0, 314, 315, 1, room, time);

	p_addSheriffNPC(MMS2_LANGUAGE_TOWN1_SHERIFF, 4, 0.125, 0.03125, chapter2SpriteTex, 200, 248, 249, 2, room, time);

	p_addOlDocNPC(chapter2SpriteTex, 251, room, time);

	p_addMayorNPC(chapter2SpriteTex, MMS2_LANGUAGE_TOWN1_MAYORDIALOG, MMS2_LANGUAGE_TOWN1_MAYORDIALOGMISSION, room, time);
}

void MMS2_setAsTown2(const size_t chapter2SpriteTex, const size_t chapter2SpriteTex2, struct MMS_MINIGAME2ROOM* room, const uint64_t time)
{
	p_addNPCTownSquare(MMS2_LANGUAGE_TOWN2_TOWNSQUARE0, PLEX_convRect(PLEX_convPoint(15, 10), PLEX_convDimens(2, 4)), 0.0625, 0.03125, chapter2SpriteTex2, 500, 12, 13, 2, room, time);
	p_addNPCTownSquare(MMS2_LANGUAGE_TOWN2_TOWNSQUARE1, PLEX_convRect(PLEX_convPoint(10, 8), PLEX_convDimens(2, 4)), 0.0625, 0.03125, chapter2SpriteTex2, 0, 42, 43, 1, room, time);
	p_addNPCTownSquare(MMS2_LANGUAGE_TOWN2_TOWNSQUARE2, PLEX_convRect(PLEX_convPoint(13, 15), PLEX_convDimens(2, 4)), 0.0625, 0.03125, chapter2SpriteTex2, 0, 44, 45, 1, room, time);
	p_addNPCTownSquare(MMS2_LANGUAGE_TOWN2_TOWNSQUARE3, PLEX_convRect(PLEX_convPoint(17.5, 14), PLEX_convDimens(2, 4)), 0.0625, 0.03125, chapter2SpriteTex2, 0, 46, 47, 1, room, time);
	p_addNPCTownSquare(MMS2_LANGUAGE_TOWN2_TOWNSQUARE4, PLEX_convRect(PLEX_convPoint(20, 9), PLEX_convDimens(2, 4)), 0.0625, 0.03125, chapter2SpriteTex2, 0, 48, 49, 1, room, time);

	p_addNPCSaloon(MMS2_LANGUAGE_TOWN2_BAR0, PLEX_convRect(PLEX_convPoint(10, 15.5), PLEX_convDimens(2, 4)), 0.0625, 0.03125, chapter2SpriteTex2, 1000, 21, 21, 3, room, time);
	p_addNPCSaloon(MMS2_LANGUAGE_TOWN2_BAR1, PLEX_convRect(PLEX_convPoint(14, 15), PLEX_convDimens(2, 4)), 0.0625, 0.03125, chapter2SpriteTex2, 1000, 24, 24, 3, room, time);
	p_addNPCSaloon(MMS2_LANGUAGE_TOWN2_BAR2, PLEX_convRect(PLEX_convPoint(17, 15), PLEX_convDimens(2, 4)), 0.0625, 0.03125, chapter2SpriteTex2, 1000, 27, 28, 2, room, time);
	p_addNPCSaloon(MMS2_LANGUAGE_TOWN2_BAR3, PLEX_convRect(PLEX_convPoint(20, 15.5), PLEX_convDimens(2, 4)), 0.0625, 0.03125, chapter2SpriteTex2, 1000, 30, 31, 2, room, time);

	p_addNPCSaloon(MMS2_LANGUAGE_TOWN2_BAR4, PLEX_convRect(PLEX_convPoint(20, 11), PLEX_convDimens(2, 4)), 0.0625, 0.03125, chapter2SpriteTex2, 1500, 33, 33, 2, room, time);

	p_addNPCJail(MMS2_LANGUAGE_TOWN2_JAIL0, 0, 0.0625, 0.03125, chapter2SpriteTex, 0, 314, 315, 1, room, time);
	p_addNPCJail(MMS2_LANGUAGE_TOWN2_JAIL1, 1, 0.0625, 0.03125, chapter2SpriteTex, 0, 314, 315, 1, room, time);
	p_addNPCJail(MMS2_LANGUAGE_TOWN2_JAIL2, 2, 0.0625, 0.03125, chapter2SpriteTex, 0, 314, 315, 1, room, time);

	p_addSheriffNPC(MMS2_LANGUAGE_TOWN2_SHERIFF, 2, 0.0625, 0.03125, chapter2SpriteTex2, 0, 40, 41, 1, room, time);

	p_addOlDocNPC(chapter2SpriteTex, 252, room, time);

	p_addMayorNPC(chapter2SpriteTex, MMS2_LANGUAGE_TOWN2_MAYORDIALOG, MMS2_LANGUAGE_TOWN2_MAYORDIALOGMISSION, room, time);
}

void MMS2_setAsTown3(const size_t chapter2SpriteTex, const size_t chapter2SpriteTex2, struct MMS_MINIGAME2ROOM* room, const uint64_t time)
{
	p_addNPCTownSquare(MMS2_LANGUAGE_TOWN3_TOWNSQUARE0, PLEX_convRect(PLEX_convPoint(15, 10), PLEX_convDimens(2, 4)), 0.0625, 0.03125, chapter2SpriteTex2, 500, 15, 16, 2, room, time);
	p_addNPCTownSquare(MMS2_LANGUAGE_TOWN3_TOWNSQUARE1, PLEX_convRect(PLEX_convPoint(8, 12), PLEX_convDimens(2, 4)), 0.0625, 0.03125, chapter2SpriteTex2, 0, 72, 73, 1, room, time);
	p_addNPCTownSquare(MMS2_LANGUAGE_TOWN3_TOWNSQUARE2, PLEX_convRect(PLEX_convPoint(18, 15), PLEX_convDimens(2, 4)), 0.0625, 0.03125, chapter2SpriteTex2, 0, 76, 77, 1, room, time);
	p_addNPCTownSquare(MMS2_LANGUAGE_TOWN3_TOWNSQUARE3, PLEX_convRect(PLEX_convPoint(22, 10), PLEX_convDimens(2, 4)), 0.0625, 0.03125, chapter2SpriteTex2, 0, 78, 79, 1, room, time);

	p_addNPCSaloon(MMS2_LANGUAGE_TOWN3_BAR0, PLEX_convRect(PLEX_convPoint(9, 11), PLEX_convDimens(2, 4)), 0.0625, 0.03125, chapter2SpriteTex2, 500, 80, 81, 2, room, time);
	p_addNPCSaloon(MMS2_LANGUAGE_TOWN3_BAR1, PLEX_convRect(PLEX_convPoint(12, 15), PLEX_convDimens(2, 4)), 0.0625, 0.03125, chapter2SpriteTex2, 0, 83, 84, 1, room, time);
	p_addNPCSaloon(MMS2_LANGUAGE_TOWN3_BAR2, PLEX_convRect(PLEX_convPoint(15, 14), PLEX_convDimens(2, 4)), 0.0625, 0.03125, chapter2SpriteTex2, 0, 85, 86, 1, room, time);
	p_addNPCSaloon(MMS2_LANGUAGE_TOWN3_BAR3, PLEX_convRect(PLEX_convPoint(19, 13), PLEX_convDimens(2, 4)), 0.0625, 0.03125, chapter2SpriteTex2, 0, 87, 88, 1, room, time);
	p_addNPCSaloon(MMS2_LANGUAGE_TOWN3_BAR4, PLEX_convRect(PLEX_convPoint(23, 15), PLEX_convDimens(2, 4)), 0.0625, 0.03125, chapter2SpriteTex2, 0, 89, 90, 1, room, time);

	p_addNPCJail(MMS2_LANGUAGE_TOWN3_JAIL0, 0, 0.0625, 0.03125, chapter2SpriteTex, 0, 314, 315, 1, room, time);
	p_addNPCJail(MMS2_LANGUAGE_TOWN3_JAIL1, 1, 0.0625, 0.03125, chapter2SpriteTex, 0, 314, 315, 1, room, time);
	p_addNPCJail(MMS2_LANGUAGE_TOWN3_JAIL2, 2, 0.0625, 0.03125, chapter2SpriteTex, 0, 314, 315, 1, room, time);

	p_addSheriffNPC(MMS2_LANGUAGE_TOWN3_SHERIFF, 2, 0.0625, 0.03125, chapter2SpriteTex2, 500, 37, 38, 2, room, time);

	p_addOlDocNPC(chapter2SpriteTex, 253, room, time);

	p_addMayorNPC(chapter2SpriteTex, MMS2_LANGUAGE_TOWN3_MAYORDIALOG, MMS2_LANGUAGE_TOWN3_MAYORDIALOGMISSION, room, time);
}

void MMS2_setAsTown4(const size_t chapter2SpriteTex, const size_t chapter2SpriteTex2, struct MMS_MINIGAME2ROOM* room, const uint64_t time)
{
	p_addNPCTownSquare(MMS2_LANGUAGE_TOWN4_TOWNSQUARE0, PLEX_convRect(PLEX_convPoint(15, 10), PLEX_convDimens(2, 4)), 0.0625, 0.03125, chapter2SpriteTex2, 500, 18, 19, 2, room, time);
	p_addNPCTownSquare(MMS2_LANGUAGE_TOWN4_TOWNSQUARE1, PLEX_convRect(PLEX_convPoint(8, 12), PLEX_convDimens(2, 4)), 0.0625, 0.03125, chapter2SpriteTex2, 0, 52, 53, 1, room, time);
	p_addNPCTownSquare(MMS2_LANGUAGE_TOWN4_TOWNSQUARE2, PLEX_convRect(PLEX_convPoint(18, 15), PLEX_convDimens(2, 4)), 0.0625, 0.03125, chapter2SpriteTex2, 0, 54, 55, 1, room, time);
	p_addNPCTownSquare(MMS2_LANGUAGE_TOWN4_TOWNSQUARE3, PLEX_convRect(PLEX_convPoint(22, 10), PLEX_convDimens(2, 4)), 0.0625, 0.03125, chapter2SpriteTex2, 800, 56, 57, 2, room, time);

	p_addNPCSaloon(MMS2_LANGUAGE_TOWN4_BAR0, PLEX_convRect(PLEX_convPoint(9, 11), PLEX_convDimens(2, 4)), 0.0625, 0.03125, chapter2SpriteTex2, 500, 59, 60, 2, room, time);
	p_addNPCSaloon(MMS2_LANGUAGE_TOWN4_BAR1, PLEX_convRect(PLEX_convPoint(12, 15), PLEX_convDimens(2, 4)), 0.0625, 0.03125, chapter2SpriteTex2, 500, 62, 63, 2, room, time);
	p_addNPCSaloon(MMS2_LANGUAGE_TOWN4_BAR2, PLEX_convRect(PLEX_convPoint(15, 14), PLEX_convDimens(2, 4)), 0.0625, 0.03125, chapter2SpriteTex2, 0, 65, 66, 1, room, time);
	p_addNPCSaloon(MMS2_LANGUAGE_TOWN4_BAR3, PLEX_convRect(PLEX_convPoint(19, 13), PLEX_convDimens(2, 4)), 0.0625, 0.03125, chapter2SpriteTex2, 0, 67, 68, 1, room, time);
	p_addNPCSaloon(MMS2_LANGUAGE_TOWN4_BAR4, PLEX_convRect(PLEX_convPoint(23, 15), PLEX_convDimens(2, 4)), 0.0625, 0.03125, chapter2SpriteTex2, 50, 69, 70, 2, room, time);

	p_addNPCJail(MMS2_LANGUAGE_TOWN4_JAIL0, 0, 0.0625, 0.03125, chapter2SpriteTex, 0, 314, 315, 1, room, time);
	p_addNPCJail(MMS2_LANGUAGE_TOWN4_JAIL1, 1, 0.0625, 0.03125, chapter2SpriteTex, 0, 314, 315, 1, room, time);
	p_addNPCJail(MMS2_LANGUAGE_TOWN4_JAIL2, 2, 0.0625, 0.03125, chapter2SpriteTex, 0, 314, 315, 1, room, time);

	p_addSheriffNPC(MMS2_LANGUAGE_TOWN4_SHERIFF, 2, 0.0625, 0.03125, chapter2SpriteTex2, 0, 35, 36, 1, room, time);

	p_addOlDocNPC(chapter2SpriteTex, 254, room, time);

	p_addMayorNPC(chapter2SpriteTex, MMS2_LANGUAGE_TOWN4_MAYORDIALOG, MMS2_LANGUAGE_TOWN4_MAYORDIALOGMISSION, room, time);
}

void MMS2_runCalmNoMayorCutaway(const size_t fontPlate, const uint64_t time)
{
	const uint32_t dimens = PLEX_WH(true) - PLEX_UNIT(4);

	size_t armoryGunCount = 0;

	MMS_MINIGAME2ROOM* currentRoom = MMS2_currentRoom();

	if(currentRoom == NULL) return;

	switch(p_townArea)
	{
		case 0:
			for(size_t ze = 0; ze < currentRoom->contents->townSquareNPCs.count; ++ze)
			{
				MMS_MINIGAME2NPC* npc = p_selectNPC(ze, &currentRoom->contents->townSquareNPCs);

				p_drawNPC(MMS2_DRAWLAYER_NPC, fontPlate, npc, time);
			}

			PLEX_printTexture(MMS2_DRAWLAYER_TOWNBACKDROP, p_townSquareCalmFloor, 0, 0, 1024, 1024, (PLEX_WW(true) - dimens)/2, 0, dimens, dimens, true);
		break;

		case 1:
			for(size_t ze = 0; ze < currentRoom->contents->saloonNPCs.count; ++ze)
			{
				MMS_MINIGAME2NPC* npc = p_selectNPC(ze, &currentRoom->contents->saloonNPCs);

				p_drawNPC(MMS2_DRAWLAYER_NPC, fontPlate, npc, time);
			}

			PLEX_printTexture(MMS2_DRAWLAYER_TOWNBACKDROP, p_saloonCalmFloor, 0, 0, 1024, 1024, (PLEX_WW(true) - dimens)/2, 0, dimens, dimens, true);
		break;

		case 2:
			for(size_t ze = 0; ze < currentRoom->contents->jailNPCs.count; ++ze)
			{
				MMS_MINIGAME2NPC* npc = p_selectNPC(ze, &currentRoom->contents->jailNPCs);

				p_drawNPC(MMS2_DRAWLAYER_JAILEDNPC, fontPlate, npc, time);
			}

			if(currentRoom->contents->hasSheriff)
			{
				MMS_MINIGAME2NPC* npc = p_selectNPC(3, &currentRoom->contents->jailNPCs);

				p_drawNPC(MMS2_DRAWLAYER_NPC, fontPlate, npc, time);
			}

			PLEX_printTexture(MMS2_DRAWLAYER_TOWNBACKDROP, p_jailCalmFloor, 0, 0, 1024, 1024, (PLEX_WW(true) - dimens)/2, 0, dimens, dimens, true);

			PLEX_printTexture(MMS2_DRAWLAYER_JAILBARS, p_jailCalmFloor2, 0, 0, 1024, 1024, (PLEX_WW(true) - dimens)/2, 0, dimens, dimens, true);
		break;

		case 3:
			if(currentRoom->contents->hasMayor)
			{
				if(p_drawNPC(MMS2_DRAWLAYER_MAYORNPC, fontPlate, &currentRoom->contents->mayor, time))
				{
					PLEX_drawLabel(MMS2_DRAWLAYER_MAYORCLICKBOX, MMS2_LANGUAGE_MAYORCLICK, PLEX_STANDNUM_FW, PLEX_STANDNUM_FH, 255, 255, 255, 255, PLEX_UNIT(6), PLEX_WH(true) - PLEX_UNIT(6), PLEX_UNIT(20), PLEX_UNIT(2), 0.1, 0.15, 0.8, 0.8, PLEX_UNIT(0.05), PLEX_LANGUAGE_ALPHASTRING, fontPlate, 0, 0, 0, 0, 0, true);

					if(PLEX_leftClick())
					{
						if(!currentRoom->contents->mayorSpeech) MMS2_markFlagGen();
						currentRoom->contents->mayorSpeech = true;

						p_mayorCutaway = true;
					}
				}
			}

			PLEX_printTexture(MMS2_DRAWLAYER_TOWNBACKDROP, p_mayorsOfficeCalmFloor, 0, 0, 1024, 1024, (PLEX_WW(true) - dimens)/2, 0, dimens, dimens, true);
		break;

		case 4:
			if(!MMS2_isMoving())
			{
				for(size_t ze = 0; ze < MMS2_GUNCOUNT; ++ze)
				{
					if(!MMS2_hasGun(ze))
					{
						if(p_placeGunInShop(ze, armoryGunCount, fontPlate)) MMS2_purchaseGun(ze);

						++armoryGunCount;
					}
				}
			}

			PLEX_printTexture(MMS2_DRAWLAYER_TOWNBACKDROP, p_armoryCalmFloor, 0, 0, 1024, 1024, (PLEX_WW(true) - dimens)/2, 0, dimens, dimens, true);

			if(MMS2_cash() >= 10 && PLEX_drawButton(MMS2_DRAWLAYER_GUI, MMS2_LANGUAGE_AMMOCLICK, PLEX_STANDNUM_FW, PLEX_STANDNUM_FH, 0, PLEX_WH(true) - PLEX_UNIT(6), PLEX_WW(true), PLEX_UNIT(2), 255, 255, 255, 255, 0, 0, 0, 255, PLEX_UNIT(0.1), PLEX_LANGUAGE_ALPHASTRING, fontPlate, 0, 0, 0, 0, 0, true))
			{
				if(MMS2_costCash(10))
				{
					for(size_t ze = 0; ze < MMS2_GUNCOUNT; ++ze) if(MMS2_hasGun(ze)) MMS2_refillGun(ze);
				}
			}
		break;

		case 5:
			if(currentRoom->contents->hasDoc)
			{
				p_drawNPC(MMS2_DRAWLAYER_NPC, fontPlate, &currentRoom->contents->olDog, time);

				if(p_drawNPC(MMS2_DRAWLAYER_NPC, fontPlate, &currentRoom->contents->olDoc, time))
				{
					const double health = MMS2_health();
					const double cash = MMS2_cash();

					size_t cost = (1.0 - health) * 10;

					PLEX_FAKESTRING_50 costString;

					bool canBuy = true;

					if(!cost) cost = 1;

					if(health >= 1)
					{
						costString = PLEX_createString50(MMS2_LANGUAGE_OLDDOCFULLHEALTH);
						canBuy = false;
					}else{
						if(!cash)
						{
							costString = PLEX_createString50(MMS2_LANGUAGE_OLDDOCNOMONEY);
							canBuy = false;
						}else{
							PLEX_FAKESTRING_50 costString2 = PLEX_createStringFromNumber50(cost);

							costString = PLEX_createString50(MMS2_LANGUAGE_OLDDOCMAXMONEY);
							costString = PLEX_mergeString50(costString, costString2);
						}
					}

					PLEX_drawChargeBar(MMS2_DRAWLAYER_GUI, health, PLEX_UNIT(6), PLEX_WH(true) - PLEX_UNIT(8), PLEX_UNIT(20), PLEX_UNIT(2), 255, 255, 255, 255, 100, 0, 0, 255, PLEX_UNIT(0.05), false, true);

					PLEX_drawLabel(MMS2_DRAWLAYER_GUI, MMS2_LANGUAGE_OLDDOCCLICK, PLEX_STANDNUM_FW, PLEX_STANDNUM_FH, 255, 255, 255, 255, PLEX_UNIT(6), PLEX_WH(true) - PLEX_UNIT(6), PLEX_UNIT(10), PLEX_UNIT(2), 0.1, 0.15, 0.8, 0.8, PLEX_UNIT(0.05), PLEX_LANGUAGE_ALPHASTRING, fontPlate, 0, 0, 0, 0, 0, true);

					PLEX_drawLabel(MMS2_DRAWLAYER_GUI, PLEX_fts(costString), PLEX_STANDNUM_FW, PLEX_STANDNUM_FH, 255, 255, 255, 255, PLEX_UNIT(16), PLEX_WH(true) - PLEX_UNIT(6), PLEX_UNIT(10), PLEX_UNIT(2), 0.1, 0.15, 0.8, 0.8, PLEX_UNIT(0.05), PLEX_LANGUAGE_ALPHASTRING, fontPlate, 0, 0, 0, 0, 0, true);

					if(PLEX_leftClick() && canBuy)
					{
						if(cost <= cash)
						{
							MMS2_costCash(cost);
							MMS2_fillHealth();
						}else{
							MMS2_cure(cash/10.0);
							MMS2_emptyCash();
						}
					}
				}
			}

			PLEX_printTexture(MMS2_DRAWLAYER_TOWNBACKDROP, p_townMedicCalmFloor, 0, 0, 1024, 1024, (PLEX_WW(true) - dimens)/2, 0, dimens, dimens, true);
		break;
	};
}

bool MMS2_checkMayorMessage(const size_t fontPlate)
{
	const PLEX_FAKESTRING_500 mayorMessage = MMS2_currentMayorMessage();

	PLEX_drawTextBoxTinted(MMS2_DRAWLAYER_MAYORMESSAGE, PLEX_fts(mayorMessage), PLEX_STANDNUM_FW, PLEX_STANDNUM_FH, 0, 0, 0, 255, 255, 255, 255, 255, (PLEX_WW(true) - PLEX_WH(true))/2, PLEX_WH(true) * 0.1, PLEX_WH(true), PLEX_WH(true) * 0.9, PLEX_UNIT(0.55), PLEX_UNIT(1.1), 0.025, 0.17, 0.97, 0.7, 0, PLEX_LANGUAGE_ALPHASTRING, fontPlate, p_mayorStatementBack, 0, 0, 1024, 1024, 0.025, true);

	if(PLEX_leftClick() || MMS2_isMoving())
	{
		p_mayorCutaway = false;
		return false;
	}

	return true;
}

void MMS2_goNextTownArea(){ p_townArea = (p_townArea + 1) % 6; }

void MMS2_goLastTownArea()
{
	if(!p_townArea) p_townArea = 5;
	else --p_townArea;
}

void MMS2_setTownArea(const size_t index) { p_townArea = index % 6; }

bool MMS2_mayorCutaway(){ return p_mayorCutaway; }

size_t MMS2_townArea(){ return p_townArea; }
