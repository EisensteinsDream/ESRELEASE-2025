#include "minigame/minigame2/minigame2.h"

static MMS_MINIGAME2COVER p_covers[MMS2_COVERCOUNT];
static size_t p_coverCount = 0;

static MMS_MINIGAME2COVER p_coverGens[MMS2_COVERGENCOUNT];

// sets the values of a cover

static void p_setCover(MMS_MINIGAME2COVER* cover, const bool bleeds, const size_t killPenalty, const bool moving, const MMS_MINIGAME2MOVEPATTERN movePattern, const double moveSpeed, const uint64_t moveAnimSpeed, const size_t tex, const size_t texStart, const double wperc, const double hperc, const PLEX_RECT space, const bool gravesite, const uint64_t time)
{
	PLEX_ANIMATION_PLATE animPlate = PLEX_createAnimationPlate(wperc, hperc, tex);

	PLEX_ANIMATION* destroyState0 = NULL;
	PLEX_ANIMATION* destroyState1 = NULL;
	PLEX_ANIMATION* destroyState2 = NULL;
	PLEX_ANIMATION* destroyState3 = NULL;

	if(cover->gravesite && cover->sprite != NULL) PLEX_destroySprite(&cover->sprite);

	memset(cover, 0, sizeof(MMS_MINIGAME2COVER));

	cover->health = 1;
	cover->beingDamaged = false;

	cover->tex = tex;
	cover->texStart = texStart;
	cover->wperc = wperc;
	cover->hperc = hperc;

	cover->space = space;
	cover->adaptSpace = space;

	cover->bleeds = bleeds;
	cover->killPenalty = killPenalty;
	cover->moving = moving;
	cover->movePattern = movePattern;
	cover->moveSpeed = moveSpeed;
	cover->moveAnimSpeed = moveAnimSpeed;
	cover->reverseAnim = false;

	cover->startPoint = space.origin;

	cover->gravesite = gravesite;

	cover->sprite = PLEX_genSprite(&animPlate);

	PLEX_addAnimation(cover->sprite, moveAnimSpeed, time);
	PLEX_addAnimation(cover->sprite, moveAnimSpeed, time);
	PLEX_addAnimation(cover->sprite, moveAnimSpeed, time);
	PLEX_addAnimation(cover->sprite, moveAnimSpeed, time);

	destroyState0 = PLEX_getAnimation(0, cover->sprite);
	destroyState1 = PLEX_getAnimation(1, cover->sprite);
	destroyState2 = PLEX_getAnimation(2, cover->sprite);
	destroyState3 = PLEX_getAnimation(3, cover->sprite);

	if(!moving)
	{
		PLEX_addAnimationFrame(texStart, destroyState0);
		PLEX_addAnimationFrame(texStart + 1, destroyState1);
		PLEX_addAnimationFrame(texStart + 2, destroyState2);
		PLEX_addAnimationFrame(texStart + 3, destroyState3);
	}else{
		PLEX_ANIMATION* destroyState0Rev = NULL;
		PLEX_ANIMATION* destroyState1Rev = NULL;
		PLEX_ANIMATION* destroyState2Rev = NULL;
		PLEX_ANIMATION* destroyState3Rev = NULL;

		PLEX_addAnimation(cover->sprite, moveAnimSpeed, time);
		PLEX_addAnimation(cover->sprite, moveAnimSpeed, time);
		PLEX_addAnimation(cover->sprite, moveAnimSpeed, time);
		PLEX_addAnimation(cover->sprite, moveAnimSpeed, time);

		destroyState0Rev = PLEX_getAnimation(4, cover->sprite);
		destroyState1Rev = PLEX_getAnimation(5, cover->sprite);
		destroyState2Rev = PLEX_getAnimation(6, cover->sprite);
		destroyState3Rev = PLEX_getAnimation(7, cover->sprite);

		PLEX_addAnimationFrame(texStart, destroyState0);
		PLEX_addAnimationFrame(texStart + 1, destroyState0);
		PLEX_addAnimationFrame(texStart + 2, destroyState0);
		PLEX_addAnimationFrame(texStart + 3, destroyState0);

		PLEX_addAnimationFrame(texStart + 4, destroyState1);
		PLEX_addAnimationFrame(texStart + 5, destroyState1);
		PLEX_addAnimationFrame(texStart + 6, destroyState1);
		PLEX_addAnimationFrame(texStart + 7, destroyState1);

		PLEX_addAnimationFrame(texStart + 8, destroyState2);
		PLEX_addAnimationFrame(texStart + 9, destroyState2);
		PLEX_addAnimationFrame(texStart + 10, destroyState2);
		PLEX_addAnimationFrame(texStart + 11, destroyState2);

		PLEX_addAnimationFrame(texStart + 12, destroyState3);
		PLEX_addAnimationFrame(texStart + 13, destroyState3);
		PLEX_addAnimationFrame(texStart + 14, destroyState3);
		PLEX_addAnimationFrame(texStart + 15, destroyState3);

		PLEX_addAnimationFrame(texStart + 16, destroyState0Rev);
		PLEX_addAnimationFrame(texStart + 17, destroyState0Rev);
		PLEX_addAnimationFrame(texStart + 18, destroyState0Rev);
		PLEX_addAnimationFrame(texStart + 19, destroyState0Rev);

		PLEX_addAnimationFrame(texStart + 20, destroyState1Rev);
		PLEX_addAnimationFrame(texStart + 21, destroyState1Rev);
		PLEX_addAnimationFrame(texStart + 22, destroyState1Rev);
		PLEX_addAnimationFrame(texStart + 23, destroyState1Rev);

		PLEX_addAnimationFrame(texStart + 24, destroyState2Rev);
		PLEX_addAnimationFrame(texStart + 25, destroyState2Rev);
		PLEX_addAnimationFrame(texStart + 26, destroyState2Rev);
		PLEX_addAnimationFrame(texStart + 27, destroyState2Rev);

		PLEX_addAnimationFrame(texStart + 28, destroyState3Rev);
		PLEX_addAnimationFrame(texStart + 29, destroyState3Rev);
		PLEX_addAnimationFrame(texStart + 30, destroyState3Rev);
		PLEX_addAnimationFrame(texStart + 31, destroyState3Rev);
	}

	PLEX_startSprite(time, cover->sprite);

	if(cover->movePattern != MMS_MINIGAME2MOVEPATTERN_ASTROIDFALL && cover->space.origin.y < 4) cover->space.origin.y = 4;
}

// adds a new cover to the map

static void p_addCover(const PLEX_POINT point, const size_t index)
{
	MMS_MINIGAME2COVER* cover = NULL;

	if(p_coverCount >= MMS2_COVERCOUNT) return;

	cover = p_covers + p_coverCount;

	*cover = p_coverGens[index];

	cover->space.origin = point;

	++p_coverCount;
}

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

void MMS2_setSystemCover()
{
	MMS2_clearCoverCount();
}

void MMS2_initSystemCover(const size_t chapter2SpriteTex, const size_t chapter2SpriteTex2, const size_t chapter2SpriteTex3, const uint64_t time)
{
	// no-move cover generators

	// trail 0

	MMS2_placeCoverGenNoMove(0, false, 0, chapter2SpriteTex, 80, 0.125, 0.03125, PLEX_convDimens(2, 4), time);
	MMS2_placeCoverGenNoMove(1, false, 0, chapter2SpriteTex, 84, 0.125, 0.03125, PLEX_convDimens(1, 2), time);

	// trail 1

	MMS2_placeCoverGenNoMove(4, false, 0, chapter2SpriteTex2, 46, 0.125, 0.03125, PLEX_convDimens(3, 2), time);
	MMS2_placeCoverGenNoMove(5, false, 0, chapter2SpriteTex2, 50, 0.125, 0.03125, PLEX_convDimens(4, 4), time);

	// trail 2

	MMS2_placeCoverGenNoMove(8, false, 0, chapter2SpriteTex2, 54, 0.125, 0.03125, PLEX_convDimens(3, 7), time);
	MMS2_placeCoverGenNoMove(9, false, 0, chapter2SpriteTex2, 58, 0.125, 0.03125, PLEX_convDimens(1.5, 3), time);

	// trail 3

	MMS2_placeCoverGenNoMove(10, false, 0, chapter2SpriteTex2, 62, 0.125, 0.03125, PLEX_convDimens(2, 2), time);
	MMS2_placeCoverGenNoMove(11, false, 0, chapter2SpriteTex2, 66, 0.125, 0.03125, PLEX_convDimens(3, 3), time);

	// moving cover generators

	// trail 0

	MMS2_placeCoverGen(2, false, 0, true, MMS_MINIGAME2MOVEPATTERN_DRIFTRIGHT, 2, 500, chapter2SpriteTex, 88, 0.125, 0.03125, PLEX_convDimens(2, 2), time);

	MMS2_placeCoverGen(3, true, 10, true, MMS_MINIGAME2MOVEPATTERN_BIRDFLIGHTLEFT, 5, 500, chapter2SpriteTex, 120, 0.125, 0.03125, PLEX_convDimens(2, 2), time);

	// trail 1

	MMS2_placeCoverGen(6, false, 0, true, MMS_MINIGAME2MOVEPATTERN_DRIFTLEFT, 5, 500, chapter2SpriteTex2, 70, 0.125, 0.03125, PLEX_convDimens(0.75, 0.75), time);
	MMS2_placeCoverGen(7, true, 50, true, MMS_MINIGAME2MOVEPATTERN_SNAKESLITHER, 2, 500, chapter2SpriteTex2, 102, 0.125, 0.03125, PLEX_convDimens(2, 2), time);

	// trail 2

	MMS2_placeCoverGen(12, false, 0, true, MMS_MINIGAME2MOVEPATTERN_DRIFTLEFT, 10, 500, chapter2SpriteTex2, 198, 0.125, 0.03125, PLEX_convDimens(4, 3), time);

	// trail 3

	MMS2_placeCoverGen(13, false, 500, true, MMS_MINIGAME2MOVEPATTERN_DRIFTRIGHT, 3, 500, chapter2SpriteTex2, 166, 0.125, 0.03125, PLEX_convDimens(2, 2), time);
	MMS2_placeCoverGen(14, false, 0, true, MMS_MINIGAME2MOVEPATTERN_ASTROIDFALL, 20, 500, chapter2SpriteTex2, 134, 0.125, 0.03125, PLEX_convDimens(2, 2), time);
	MMS2_placeCoverGen(15, true, 1000, true, MMS_MINIGAME2MOVEPATTERN_DRIFTLEFT, 15, 500, chapter2SpriteTex3, 0, 0.125, 0.03125, PLEX_convDimens(2, 2), time); // < lizard
	MMS2_placeCoverGen(16, false, 0, true, MMS_MINIGAME2MOVEPATTERN_DRIFTRIGHT, 5, 2000, chapter2SpriteTex3, 24, 0.125, 0.03125, PLEX_convDimens(2, 2), time); // < stormcloud
	MMS2_placeCoverGen(17, false, 1000, true, MMS_MINIGAME2MOVEPATTERN_DRIFTLEFT, 2, 500, chapter2SpriteTex3, 64, 0.125, 0.03125, PLEX_convDimens(2, 2), time); // < mechanical horse
}

void MMS2_checkRunSystemCover(bool* coverHit, PLEX_RECT* coverRect, double* coverLayer, double* coverAbsorb, const uint64_t time)
{
	if(MMS2_currentRoomCalm()) return;

	*coverHit = false;

	for(size_t ze = 0; ze < p_coverCount; ++ze)
	{
		MMS_MINIGAME2COVER* cover = p_covers + ze;

		size_t healthStage = 4 - cover->health/0.25;

		size_t revAdjust = 0;

		PLEX_RECT dr;

		double layer = 0;

		uint8_t col = 0;

		size_t aniIndex = 0;

		if(!cover->health) continue;

		cover->adaptSpace.origin.x = cover->space.origin.x + MMS2_leanX();
		cover->adaptSpace.origin.y = cover->space.origin.y + MMS2_leanY();

		dr.origin.x = PLEX_UNIT(cover->adaptSpace.origin.x);
		dr.origin.y = PLEX_UNIT(cover->adaptSpace.origin.y);
		dr.dimens.w = PLEX_UNIT(cover->adaptSpace.dimens.w);
		dr.dimens.h = PLEX_UNIT(cover->adaptSpace.dimens.h);

		layer = MMS2_getEnemyLayer(dr);

		if(cover->moving && cover->reverseAnim) revAdjust = 4;

		if(!cover->beingDamaged) col = 255;

		if(!cover->moving) PLEX_stopSprite(cover->sprite);

		aniIndex = healthStage + revAdjust;

		if(PLEX_spriteAnimationCount(cover->sprite) <= aniIndex) continue; // < corrects a very rare, small, error

		PLEX_drawSpriteTinted(layer, aniIndex, dr.origin.x, dr.origin.y, dr.dimens.w, dr.dimens.h, 255, col, col, cover->sprite, true, time);

		if(MMS2_playerIsShooting(time))
		{
			if(PLEX_rectCollisionNoMove(dr, MMS2_shotArea()) && cover->health)
			{
				*coverHit = true;
				*coverRect = MMS2_innerShotArea();
				*coverLayer = layer;
				*coverAbsorb = cover->health;

				if(!cover->beingDamaged)
				{
					const MMS_MINIGAME2GUN* const gun = MMS2_selectedGun();

					double damage = gun->outerDamage;

					if(PLEX_rectCollisionNoMove(MMS2_innerShotArea(), dr)) damage += gun->innerDamage;

					cover->health -= damage;

					if(cover->health <= 0)
					{
						if(MMS2_points() > cover->killPenalty) MMS2_decrementPoints(cover->killPenalty);
						else MMS2_clearPoints();

						cover->health = 0;
					}

					if(cover->bleeds) MMS2_bloodSplatter(time);

					cover->beingDamaged = true;
				}
			}
		}else cover->beingDamaged = false;

		if(!PLEX_getGameTimePaused() && cover->moving && !cover->beingDamaged)
		{
			const double secondsPass = PLEX_getGameSecondsPassed();
			const double velocity = secondsPass * cover->moveSpeed;

			switch(cover->movePattern)
			{
				case MMS_MINIGAME2MOVEPATTERN_NOMOVE:
					cover->reverseAnim = false;
					break;

				case MMS_MINIGAME2MOVEPATTERN_DRIFTLEFT:
					cover->space.origin.x -= velocity;

					cover->reverseAnim = false;

					if(cover->space.origin.x < -5) cover->space.origin.x = PLEX_WIDTHUNITMAX(true) + 5;
					break;

				case MMS_MINIGAME2MOVEPATTERN_DRIFTRIGHT:
					cover->space.origin.x += velocity;

					cover->reverseAnim = true;

					if(cover->space.origin.x > PLEX_WIDTHUNITMAX(true) + 5) cover->space.origin.x = -5;
					break;

				case MMS_MINIGAME2MOVEPATTERN_BIRDFLIGHTLEFT:
					cover->space.origin.x -= velocity;

					if(cover->space.origin.y < 4) cover->revFlight = false;

					if(cover->space.origin.y > 8) cover->revFlight = true;

					if(cover->revFlight) cover->space.origin.y -= velocity/2;
					else cover->space.origin.y += velocity/2;

					cover->reverseAnim = false;

				if(cover->space.origin.x < 0) cover->movePattern = MMS_MINIGAME2MOVEPATTERN_BIRDFLIGHTRIGHT;
				break;

				case MMS_MINIGAME2MOVEPATTERN_BIRDFLIGHTRIGHT:
					cover->space.origin.x += velocity;

					if(cover->space.origin.y < 4) cover->revFlight = false;

					if(cover->space.origin.y > 8) cover->revFlight = true;

					if(cover->revFlight) cover->space.origin.y -= velocity/2;
					else cover->space.origin.y += velocity/2;

					cover->reverseAnim = true;

				if(cover->space.origin.x > PLEX_WIDTHUNITMAX(true)) cover->movePattern = MMS_MINIGAME2MOVEPATTERN_BIRDFLIGHTLEFT;
				break;

				case MMS_MINIGAME2MOVEPATTERN_SNAKESLITHER:

					if(cover->space.origin.x < 0)
					{
						cover->space.origin.x += velocity * 4;
						break;
					}

					if(cover->space.origin.x > PLEX_WW(true))
					{
						cover->space.origin.x -= velocity * 4;
						break;
					}

					if(cover->space.origin.y < 5)
					{
						cover->space.origin.y += velocity * 2;
						break;
					}

					if(cover->space.origin.y > PLEX_HEIGHTUNITMAX(true) - 6)
					{
						cover->space.origin.y -= velocity * 2;
						break;
					}

					if(PLEX_randomNumber(0, 4) != 1)
					{
						if(PLEX_randomNumber(0, 10) > 5)
						{
							if(PLEX_randomNumber(0, 10) > 5) cover->space.origin.y -= velocity * 2;
							else cover->space.origin.y += velocity * 2;
						}else{
							if(PLEX_randomNumber(0, 10) > 5) cover->space.origin.x -= velocity * 4;
							else cover->space.origin.x += velocity * 4;
						}
					}
					break;

				case MMS_MINIGAME2MOVEPATTERN_ASTROIDFALL:

					cover->space.origin.x += velocity/2;
					cover->space.origin.y += velocity/2;

					if(cover->space.origin.y > PLEX_HEIGHTUNITMAX(true) - 4)
					{
						cover->space.origin.x = PLEX_randomNumber(-4, PLEX_WIDTHUNITMAX(true));
						cover->space.origin.y = 0;
						cover->health = 1;
					}
				break;
			};
		}
	}
}

void MMS2_endSystemCover()
{
	MMS2_clearCoverCount();
	MMS2_clearCoverSprites();
}

void MMS2_clearCoverSprites()
{
	for(size_t ze = 0; ze < MMS2_COVERGENCOUNT; ++ze)
	{
		MMS_MINIGAME2COVER* cover = p_coverGens + ze;

		if(cover->sprite != NULL) PLEX_destroySprite(&cover->sprite);
	}
}

void MMS2_setCoverGenerator(const double minCount, const double maxCount, const size_t initialCover, struct MMS_MINIGAME2ROOM* room, const uint64_t time)
{
	MMS_MINIGAME2COVERGENERATOR* coverGenerator = NULL;

	if(room == NULL)
	{
		PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MINOR, MMS2_ERRORMESS_ONSETCOVERGENERATOR, MMS2_ERRORMESS_ROOM);
		return;
	}

	coverGenerator = &room->contents->coverGenerator;

	coverGenerator->minCount = minCount;
	coverGenerator->maxCount = maxCount;

	coverGenerator->generatorTypes[0] = initialCover;
	coverGenerator->typeCount = 1;
}

void MMS2_addCoverTypeIndex(struct MMS_MINIGAME2ROOM* room, const size_t index)
{
	MMS_MINIGAME2COVERGENERATOR* coverGenerator = &room->contents->coverGenerator;

	if(coverGenerator->typeCount >= MMS2_GENERATORINDEXCOUNT) return;

	coverGenerator->generatorTypes[coverGenerator->typeCount] = index;
	++coverGenerator->typeCount;
}

void MMS2_useCoverGenerator(MMS_MINIGAME2ROOM* room, const uint64_t time)
{
	MMS_MINIGAME2COVERGENERATOR* coverGenerator = NULL;

	size_t genCount = 0;

	if(room == NULL)
	{
		PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_MINOR, MMS2_ERRORMESS_ONUSECOVERGENERATOR, MMS2_ERRORMESS_ROOM);
		return;
	}

	coverGenerator = &room->contents->coverGenerator;

	genCount = PLEX_randomNumber(coverGenerator->minCount, coverGenerator->maxCount);

	for(size_t ze = 0; ze < genCount; ++ze)
	{
		MMS_MINIGAME2COVER* cover = NULL;

		const size_t index = PLEX_randomNumber(0, coverGenerator->typeCount);

		const size_t genIndex = coverGenerator->generatorTypes[index];

		double x = 0;
		double y = 0;

		cover = p_coverGens + genIndex;

		x = PLEX_randomNumber(-4, PLEX_WIDTHUNITMAX(true) - 1 - cover->space.dimens.w);
		y = PLEX_randomNumber(4 + cover->space.dimens.h, PLEX_HEIGHTUNITMAX(true) - 4 - cover->space.dimens.h);

		p_addCover(PLEX_convPoint(x, y), genIndex);
	}
}

void MMS2_placeCoverGen(const size_t index, const bool bleeds, const size_t killPenalty, const bool moving, const MMS_MINIGAME2MOVEPATTERN movePattern, const double moveSpeed, const uint64_t moveAnimSpeed, const size_t tex, const size_t texStart, const double wperc, const double hperc, const PLEX_DIMENS dimens, const uint64_t time)
{
	MMS_MINIGAME2COVER* cover = NULL;

	PLEX_RECT space;

	if(index >= MMS2_COVERGENCOUNT)
	{
		PLEX_error2(PLEX_ERROR_CATEGORY_INPROJECT, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, MMS2_ERRORMESS_ONPLACECOVERGENERATOR, MMS2_ERRORMESS_COVERCOUNT);
		return;
	}

	space = PLEX_convRect(PLEX_convPoint(0, 0), dimens);

	cover = p_coverGens + index;

	p_setCover(cover, bleeds, killPenalty, moving, movePattern, moveSpeed, moveAnimSpeed, tex, texStart, wperc, hperc, space, false, time);
}

void MMS2_placeCoverGenNoMove(const size_t index, const bool bleeds, const size_t killPenalty, const size_t tex, const size_t texStart, const double wperc, const double hperc, const PLEX_DIMENS dimens, const uint64_t time)
{
	MMS2_placeCoverGen(index, bleeds, killPenalty, false, MMS_MINIGAME2MOVEPATTERN_NOMOVE, 0, 0, tex, texStart, wperc, hperc, dimens, time);
}

void MMS2_addGravesite(const size_t tex, const size_t texStart, const PLEX_RECT space, const double wperc, const double hperc, const uint64_t time)
{
	MMS_MINIGAME2COVER* cover = NULL;

	if(p_coverCount >= MMS2_COVERCOUNT) return;

	cover = p_covers + p_coverCount;

	p_setCover(cover, false, 0, false, MMS_MINIGAME2MOVEPATTERN_NOMOVE, 0, 0, tex, texStart, wperc, hperc, space, true, time);

	++p_coverCount;
}

void MMS2_incrementCoverCount()
{
	if(p_coverCount >= MMS2_COVERCOUNT) return;

	++p_coverCount;
}

void MMS2_clearCoverCount()
{
	for(size_t ze = 0; ze < p_coverCount; ++ze)
	{
		MMS_MINIGAME2COVER* cover = p_covers + ze;

		if(cover->gravesite) PLEX_destroySprite(&cover->sprite);
		cover->gravesite = false;
	}

	p_coverCount = 0;
}

size_t MMS2_coverCount(){ return p_coverCount; }

struct MMS_MINIGAME2COVER* MMS2_cover(const size_t index){ return p_covers + index % (MMS2_COVERCOUNT); }

struct MMS_MINIGAME2COVER* MMS2_coverGen(const size_t index){ return p_coverGens + index % (MMS2_COVERCOUNT); }
