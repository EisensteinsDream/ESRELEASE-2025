#include "minigame/minigame1/function.h"

static uint64_t p_objGenMarker[MMS1_PHASE_MAX], p_objGenDuration[MMS1_PHASE_MAX];
static MMS1_OBSTRUCTION p_objGen[MMS1_PHASE_MAX];

static MMS1_OBSTRUCTION p_obstructions[MMS1_OBSTUCTION_LIMIT];
static size_t p_obstructionCount = 0;

static uint64_t p_start = 0;

static bool p_warnPlayer = false;

static bool p_checkObstructionEnd(const PLEX_RECT shape)
{
	const double y = shape.origin.y - shape.dimens.h/2;
	const double y2 = shape.origin.y + shape.dimens.h/2;

	return y2 < PLEX_HEIGHTUNITMAX() * 0.75 || y > PLEX_HEIGHTUNITMAX();
}

static PLEX_POINT p_getLaneStart(const size_t playerLane, const size_t lane)
{
	const PLEX_RECT playerRegion = MMS1_playerRegion();

	PLEX_POINT ret;

	switch(lane)
	{
		case 0: ret = PLEX_convPoint(PLEX_WIDTHUNITMAX() * 0.4, PLEX_HEIGHTUNITMAX() * 0.75); break;

		case 1:
			if(playerLane != 1) ret = PLEX_convPoint(PLEX_WIDTHUNITMAX() * 0.465, PLEX_HEIGHTUNITMAX() * 0.75);
			else{
				const double x = PLEX_randomNumber(playerRegion.origin.x, PLEX_WIDTHUNITMAX() * 0.465);

				ret = PLEX_convPoint(x, PLEX_HEIGHTUNITMAX() * 0.75);
			}
		break;

		case 2:
			if(playerLane != 2) ret = PLEX_convPoint(PLEX_WIDTHUNITMAX() * 0.535, PLEX_HEIGHTUNITMAX() - 1);
			else
			{
				const double x = PLEX_randomNumber(PLEX_WIDTHUNITMAX() * 0.535, playerRegion.origin.x);

				ret = PLEX_convPoint(x, PLEX_HEIGHTUNITMAX() - 1);
			}
		break;

		case 3: ret = PLEX_convPoint(PLEX_WIDTHUNITMAX() * 0.9, PLEX_HEIGHTUNITMAX() - 1); break;
	};

	return ret;
}

static void p_placeObstruction(const size_t playerLane, MMS1_OBSTRUCTION* obstruction)
{
	obstruction->space.origin = p_getLaneStart(playerLane, obstruction->lane);
}

static void p_updateObstruction(const size_t index, MMS1_OBSTRUCTION* obstruction, const uint64_t time, const double secondsPass)
{
	const PLEX_RECT carDrawArea = MMS1_carDrawArea();

	double drift = 0;
	double translation = 0;

	uint8_t windshieldCollide = 0;
	uint8_t seatCollide = 0;
	uint8_t backCollide = 0;
	uint8_t wingLeftCollide = 0;
	uint8_t wingRightCollide = 0;

	bool playerCollide = false;
	bool objCollide = false;

	drift = obstruction->drift * secondsPass;

	if(obstruction->deactivate) return;

	obstruction->space.origin = MMS1_translateLaneMove(obstruction->lane, obstruction->velocity, obstruction->space.origin, drift, &obstruction->totalVelocity);

	translation = MMS1_translateLaneProp(obstruction->space.origin.y, obstruction->translatedSpace.dimens.h);

	obstruction->space.origin = MMS1_translateLaneMove(obstruction->lane, obstruction->velocity, obstruction->space.origin, drift, &obstruction->totalVelocity);

	obstruction->translatedSpace.dimens.w = obstruction->space.dimens.w * translation;
	obstruction->translatedSpace.dimens.h = obstruction->space.dimens.h * translation;
	obstruction->translatedSpace.origin.x = obstruction->space.origin.x - obstruction->translatedSpace.dimens.w/2;
	obstruction->translatedSpace.origin.y = obstruction->space.origin.y - obstruction->translatedSpace.dimens.h/2;

	if(obstruction->crashed)
	{
		const PLEX_RECT carDrawArea = MMS1_carDrawArea();

		PLEX_drawSprite(MMS1_calcOverroadLayer(carDrawArea.origin.y, carDrawArea.dimens.h, MMS1_SPRITELAYER_OBSTRUCTION), 2, PLEX_UNIT(obstruction->translatedSpace.origin.x), PLEX_UNIT(obstruction->translatedSpace.origin.y), PLEX_UNIT(obstruction->translatedSpace.dimens.w), PLEX_UNIT(obstruction->translatedSpace.dimens.h), obstruction->sprite, true, time);

		if(time - obstruction->crashedMarker > 5000 || p_checkObstructionEnd(obstruction->translatedSpace)) obstruction->deactivate = true;
		return;
	}

	obstruction->driftAccum += drift;

	windshieldCollide = PLEX_rectCollisionNoMove(MMS1_carWindshieldArea(), obstruction->translatedSpace) && MMS1_windshieldHealth();
	seatCollide = PLEX_rectCollisionNoMove(MMS1_carSeatArea(), obstruction->translatedSpace) && MMS1_carSeatHealth();
	backCollide = PLEX_rectCollisionNoMove(MMS1_carBackArea(), obstruction->translatedSpace);
	wingLeftCollide = PLEX_rectCollisionNoMove(MMS1_carWingLeftArea(), obstruction->translatedSpace);
	wingRightCollide = PLEX_rectCollisionNoMove(MMS1_carWingRightArea(), obstruction->translatedSpace);

	if(drift < 0 && obstruction->driftAccum < -1 * obstruction->leftDrift)
	{
		drift = 0;
		obstruction->driftAccum = 0;
		obstruction->drift *= -1;
	}

	if(drift > 0 && obstruction->driftAccum > obstruction->rightDrift)
	{
		drift = 0;
		obstruction->driftAccum = 0;
		obstruction->drift *= -1;
	}

	if(windshieldCollide && MMS1_windshieldHealth())
	{
		seatCollide = false;
		backCollide = false;
	}

	if(seatCollide && MMS1_carSeatHealth())
	{
		backCollide = false;
	}

	playerCollide = seatCollide || windshieldCollide || backCollide || wingLeftCollide || wingRightCollide;

	for(size_t ze = 0; ze < p_obstructionCount; ++ze)
	{
		MMS1_OBSTRUCTION* obstruction2 = NULL;

		if(ze == index) continue;

		obstruction2 = p_obstructions + ze;

		if(obstruction->weight < obstruction2->weight && PLEX_rectCollisionNoMove(obstruction->translatedSpace, obstruction2->translatedSpace))
		{
			playerCollide = false;
			objCollide = true;
			break;
		}
	}

	PLEX_drawSprite(MMS1_calcOverroadLayer(carDrawArea.origin.y, carDrawArea.dimens.h, MMS1_SPRITELAYER_OBSTRUCTION), obstruction->lane > 1, PLEX_UNIT(obstruction->translatedSpace.origin.x), PLEX_UNIT(obstruction->translatedSpace.origin.y), PLEX_UNIT(obstruction->translatedSpace.dimens.w), PLEX_UNIT(obstruction->translatedSpace.dimens.h), obstruction->sprite, true, time);

	if(playerCollide || objCollide)
	{
		if(playerCollide)
		{
			const double damage = obstruction->weight/100.0 * (obstruction->totalVelocity/0.33) * 2;

			const double deccel = damage * 3;

			if(backCollide){ MMS1_damageCarBack(damage); }
			if(seatCollide){ MMS1_damageCarSeat(damage); }
			if(windshieldCollide){ MMS1_damageWindshield(damage); }
			if(wingLeftCollide){ MMS1_damageCarLeft(damage); }
			if(wingRightCollide){ MMS1_damageCarRight(damage); }

			if(!MMS1_crashDuration()) MMS1_setCrashMarker(time);

			if(deccel < 1)
			{
				MMS1_controlledDeccelCar(deccel);
				MMS1_incrementCrashDuration(100);
			}else{
				MMS1_stopAccel();
				MMS1_incrementCrashDuration(deccel * 300);
			}

			MM_COMMON_playSoundEffectVolume(obstruction->weight/50.0 + 0.5, MM_COMMON_SOUNDEFFECT_CRASH);
		}

		obstruction->velocity = 0;
		obstruction->crashedMarker = time;
		obstruction->drift = 0;
		obstruction->driftAccum = 0;
		obstruction->crashed = true;
	}

	if(p_checkObstructionEnd(obstruction->translatedSpace)) obstruction->deactivate = true;
}

static void p_checkAddObstruction(const size_t playerLane, const size_t lane, const uint64_t time)
{
	size_t index = p_obstructionCount;

	MMS1_OBSTRUCTION toAdd;

	if(!p_objGenDuration[lane] || time - p_objGenMarker[lane] < p_objGenDuration[lane]) return;

	p_objGenDuration[lane] = 0;

	for(size_t ze = 0; ze < p_obstructionCount; ++ze)
	{
		if(p_obstructions[ze].deactivate)
		{
			index = ze;
			break;
		}
	}

	if(index >= MMS1_OBSTUCTION_LIMIT)
	{
		p_objGenMarker[lane] = time;
		return;
	}

	toAdd = p_objGen[lane];

	p_placeObstruction(playerLane, &toAdd);

	p_obstructions[index] = toAdd;
	if(index == p_obstructionCount) ++p_obstructionCount;

	MM_COMMON_playSoundEffectVolume((lane == 1 || lane == 2) * 0.5 + 0.5, MM_COMMON_SOUNDEFFECT_ZOOMBY);

	p_objGenMarker[lane] = time;
}

static void p_checkObstructionsAllPhases(const size_t playerLane, const uint64_t time)
{
	p_warnPlayer = playerLane > 1 && p_objGenDuration[playerLane];

	for(size_t ze = 0; ze < MMS1_PHASE_MAX; ++ze) p_checkAddObstruction(playerLane, ze, time);

	if(p_obstructionCount && p_obstructions[p_obstructionCount - 1].deactivate) --p_obstructionCount;
}

static void p_checkObstructionPhase0Lane0(const size_t genNum, const bool driftAdjust, const uint64_t time)
{
	if(genNum < 10) MMS1_addObstruction(0, 2, 2, 0.05, 5, 2, 2, 5, driftAdjust, 500, MMS1_OBSTRUCTION_TYPE_BIKE, time);
	else MMS1_addObstruction(0, 2.5, 1.25, 0.5, 0, 0, 0.5, 10, driftAdjust, 2000, MMS1_OBSTRUCTION_TYPE_CAR0, time);
}

static void p_checkObstructionPhase0Lane1(const size_t genNum, const bool driftAdjust, const uint64_t time)
{
	if(genNum < 30) MMS1_addObstruction(1, 2, 2, 0.05, 5, 2, 2, 5, driftAdjust, 500, MMS1_OBSTRUCTION_TYPE_BIKE, time);
	else MMS1_addObstruction(1, 2, 1.5, 0.5, 0, 0, 0, 10, driftAdjust, 2000, MMS1_OBSTRUCTION_TYPE_CAR0, time);
}

static void p_checkObstructionPhase0Lane2(const size_t genNum, const bool driftAdjust, const uint64_t time)
{
	if(genNum < 50) MMS1_addObstruction(2, 2, 2, 0.05, 5, 2, 2, 5, driftAdjust, 3000, MMS1_OBSTRUCTION_TYPE_BIKE, time);
	else MMS1_addObstruction(2, 2, 1.5, 0.5, 0, 0, 0.5, 10, driftAdjust, 3000, MMS1_OBSTRUCTION_TYPE_CAR0, time);
}

static void p_checkObstructionPhase0Lane3(const size_t genNum, const bool driftAdjust, const uint64_t time)
{
	if(genNum < 90) MMS1_addObstruction(3, 2, 2, 0.05, 5, 2, 2, 5, driftAdjust, 500, MMS1_OBSTRUCTION_TYPE_BIKE, time);
	else MMS1_addObstruction(3, 2, 1.5, 0.5, 0, 0, 0, 10, driftAdjust, 2000, MMS1_OBSTRUCTION_TYPE_CAR0, time);
}

static void p_checkObstructionsPhase0(const uint64_t lane0Duration, const uint64_t lane1Duration, const uint64_t lane2Duration, const uint64_t lane3Duration, const size_t genNum, const bool driftAdjust, const uint64_t time)
{
	if(lane0Duration > 500) p_checkObstructionPhase0Lane0(genNum, driftAdjust, time);
	if(lane1Duration > 7500) p_checkObstructionPhase0Lane1(genNum, driftAdjust, time);
	if(lane2Duration > 10000) p_checkObstructionPhase0Lane2(genNum, driftAdjust, time);
	if(lane3Duration > 500) p_checkObstructionPhase0Lane3(genNum, driftAdjust, time);
}

static void p_checkObstructionPhase1Lane0(const size_t genNum, const bool driftAdjust, const uint64_t time)
{
	if(genNum < 10)
	{
		MMS1_addObstruction(0, 1, 2, 0, 0, 0, 0, 10, driftAdjust, 1000, MMS1_OBSTRUCTION_TYPE_CACTUS, time);
	}else{
		if(genNum < 20)
		{
			MMS1_addObstruction(0, 1, 1, 0, 7, 0, 1000, 2, true, 200, MMS1_OBSTRUCTION_TYPE_TUMBLEWEED, time);
		}else{
			if(genNum < 50)
			{
				MMS1_addObstruction(0, 2, 1.5, 0.25, 0, 0, 0, 10, driftAdjust, 2000, MMS1_OBSTRUCTION_TYPE_CAR2, time);
			}else{
				if(genNum < 75) MMS1_addObstruction(0, 3, 1.25, 0.02, 3, 0.5, 0.5, 10, driftAdjust, 500, MMS1_OBSTRUCTION_TYPE_BIKER, time);
				else MMS1_addObstruction(0, 3, 2, 0.01, 0, 0, 0, 25, driftAdjust, 500, MMS1_OBSTRUCTION_TYPE_CAR1, time);
			}
		}
	}
}

static void p_checkObstructionPhase1Lane1(const size_t genNum, const bool driftAdjust, const uint64_t time)
{
	if(genNum < 10)
	{
		MMS1_addObstruction(1, 1, 2, 0, 0, 0, 0, 5, driftAdjust, 1000, MMS1_OBSTRUCTION_TYPE_CACTUS, time);
	}else{
		if(genNum < 20)
		{
			MMS1_addObstruction(1, 1, 1, 0, 7, 0, 1000, 2, true, 200, MMS1_OBSTRUCTION_TYPE_TUMBLEWEED, time);
		}else{
			if(genNum < 70) MMS1_addObstruction(1, 2, 1.5, 0.25, 0, 0, 0, 10, driftAdjust, 2000, MMS1_OBSTRUCTION_TYPE_CAR2, time);
			else MMS1_addObstruction(1, 3, 1.25, 0.02, 3, 0.5, 0.5, 7, driftAdjust, 500, MMS1_OBSTRUCTION_TYPE_BIKER, time);
		}
	}
}

static void p_checkObstructionPhase1Lane2(const size_t genNum, const bool driftAdjust, const uint64_t time)
{
	if(genNum < 50) MMS1_addObstruction(2, 2, 1.5, 0.25, 0, 0, 0, 10, driftAdjust, 2000, MMS1_OBSTRUCTION_TYPE_CAR2, time);
	else MMS1_addObstruction(2, 3, 1.25, 0.02, 3, 0.5, 0.5, 7, driftAdjust, 500, MMS1_OBSTRUCTION_TYPE_BIKER, time);
}

static void p_checkObstructionPhase1Lane3(const size_t genNum, const bool driftAdjust, const uint64_t time)
{
	if(genNum < 70)
	{
		MMS1_addObstruction(3, 3, 2, 0.01, 0, 0, 0, 25, driftAdjust, 500, MMS1_OBSTRUCTION_TYPE_CAR1, time);
	}else{
		if(genNum < 90) MMS1_addObstruction(3, 2, 1.5, 0.25, 0, 0, 0, 10, driftAdjust, 2000, MMS1_OBSTRUCTION_TYPE_CAR2, time);
		else MMS1_addObstruction(3, 3, 1.25, 0.02, 3, 0.5, 0.5, 7, driftAdjust, 500, MMS1_OBSTRUCTION_TYPE_BIKER, time);
	}
}

static void p_checkObstructionsPhase1(const uint64_t lane0Duration, const uint64_t lane1Duration, const uint64_t lane2Duration, const uint64_t lane3Duration, const size_t genNum, const bool driftAdjust, const uint64_t time)
{
	if(lane0Duration > 500) p_checkObstructionPhase1Lane0(genNum, driftAdjust, time);
	if(lane1Duration > 7500) p_checkObstructionPhase1Lane1(genNum, driftAdjust, time);
	if(lane2Duration > 5000) p_checkObstructionPhase1Lane2(genNum, driftAdjust, time);
	if(lane3Duration > 500) p_checkObstructionPhase1Lane3(genNum, driftAdjust, time);
}

static void p_checkObstructionPhase2Lane0(const size_t gen3Num, const bool driftAdjust, const uint64_t time)
{
	switch(gen3Num)
	{
		case 0:
			MMS1_addObstruction(0, 2.5, 1.25, 0.5, 0, 0, 0.5, 10, false, 100, MMS1_OBSTRUCTION_TYPE_CAR0, time);
		break;

		case 1:
			MMS1_addObstruction(0, 3, 2, 0.01, 0, 0, 0, 25, false, 50, MMS1_OBSTRUCTION_TYPE_CAR1, time);
		break;

		case 2:
			MMS1_addObstruction(0, 2, 1.5, 0.25, 0, 0, 0, 10, false, 100, MMS1_OBSTRUCTION_TYPE_CAR2, time);
		break;

		case 3:
			MMS1_addObstruction(0, 2, 1.5, 0.25, 0, 0, 0, 10, false, 100, MMS1_OBSTRUCTION_TYPE_CAR3, time);
		break;

		case 4:
			MMS1_addObstruction(0, 2, 1.5, 0.25, 0, 0, 0, 10, false, 100, MMS1_OBSTRUCTION_TYPE_CAR4, time);
		break;

		case 5:
			MMS1_addObstruction(0, 2, 1.5, 0.25, 0, 0, 0, 10, false, 100, MMS1_OBSTRUCTION_TYPE_CAR5, time);
		break;

		case 6:
			MMS1_addObstruction(0, 2, 1.5, 0.25, 0, 0, 0, 10, false, 50, MMS1_OBSTRUCTION_TYPE_CAR6, time);
		break;

		default: MMS1_addObstruction(0, 2, 1.5, 0.25, 0, 0, 0, 10, false, 50, MMS1_OBSTRUCTION_TYPE_CAR7, time);
	};
}

static void p_checkObstructionPhase2Lane1(const size_t gen3Num, const bool driftAdjust, const uint64_t time)
{
	switch(gen3Num)
	{
		case 0:
			MMS1_addObstruction(1, 2.5, 1.25, 0.5, 0, 0, 0.5, 10, false, 100, MMS1_OBSTRUCTION_TYPE_CAR0, time);
		break;

		case 1:
			MMS1_addObstruction(1, 3, 2, 0.01, 0, 0, 0, 25, false, 50, MMS1_OBSTRUCTION_TYPE_CAR1, time);
		break;

		case 2:
			MMS1_addObstruction(1, 2, 1.5, 0.25, 0, 0, 0, 10, false, 100, MMS1_OBSTRUCTION_TYPE_CAR2, time);
		break;

		case 3:
			MMS1_addObstruction(1, 2, 1.5, 0.25, 0, 0, 0, 10, false, 100, MMS1_OBSTRUCTION_TYPE_CAR3, time);
		break;

		case 4:
			MMS1_addObstruction(1, 2, 1.5, 0.25, 0, 0, 0, 10, false, 100, MMS1_OBSTRUCTION_TYPE_CAR4, time);
		break;

		case 5:
			MMS1_addObstruction(1, 2, 1.5, 0.25, 0, 0, 0, 10, false, 100, MMS1_OBSTRUCTION_TYPE_CAR5, time);
		break;

		case 6:
			MMS1_addObstruction(1, 2, 1.5, 0.25, 0, 0, 0, 10, false, 50, MMS1_OBSTRUCTION_TYPE_CAR6, time);
		break;

		default: MMS1_addObstruction(1, 2, 1.5, 0.25, 0, 0, 0, 10, false, 50, MMS1_OBSTRUCTION_TYPE_CAR7, time);
	};
}

static void p_checkObstructionPhase2Lane2(const size_t gen3Num, const bool driftAdjust, const uint64_t time)
{
	switch(gen3Num)
	{
		case 0:
			MMS1_addObstruction(2, 2.5, 1.25, 0.5, 0, 0, 0.5, 10, false, 500, MMS1_OBSTRUCTION_TYPE_CAR0, time);
		break;

		case 1:
			MMS1_addObstruction(2, 3, 2, 0.01, 0, 0, 0, 25, false, 250, MMS1_OBSTRUCTION_TYPE_CAR1, time);
		break;

		case 2:
			MMS1_addObstruction(2, 2, 1.5, 0.25, 0, 0, 0, 10, false, 500, MMS1_OBSTRUCTION_TYPE_CAR2, time);
		break;

		case 3:
			MMS1_addObstruction(2, 2, 1.5, 0.25, 0, 0, 0, 10, false, 500, MMS1_OBSTRUCTION_TYPE_CAR3, time);
		break;

		case 4:
			MMS1_addObstruction(2, 2, 1.5, 0.25, 0, 0, 0, 10, false, 500, MMS1_OBSTRUCTION_TYPE_CAR4, time);
		break;

		case 5:
			MMS1_addObstruction(2, 2, 1.5, 0.25, 0, 0, 0, 10, false, 500, MMS1_OBSTRUCTION_TYPE_CAR5, time);
		break;

		case 6:
			MMS1_addObstruction(2, 2, 1.5, 0.25, 0, 0, 0, 10, false, 500, MMS1_OBSTRUCTION_TYPE_CAR6, time);
		break;

		default: MMS1_addObstruction(2, 2, 1.5, 0.25, 0, 0, 0, 10, false, 500, MMS1_OBSTRUCTION_TYPE_CAR7, time);
	};
}

static void p_checkObstructionPhase2Lane3(const size_t gen3Num, const bool driftAdjust, const uint64_t time)
{
	switch(gen3Num)
	{
		case 0:
			MMS1_addObstruction(3, 2.5, 1.25, 0.5, 0, 0, 0.5, 10, false, 1000, MMS1_OBSTRUCTION_TYPE_CAR0, time);
		break;

		case 1:
			MMS1_addObstruction(3, 3, 2, 0.01, 0, 0, 0, 25, false, 1000, MMS1_OBSTRUCTION_TYPE_CAR1, time);
		break;

		case 2:
			MMS1_addObstruction(3, 2, 1.5, 0.25, 0, 0, 0, 10, false, 1000, MMS1_OBSTRUCTION_TYPE_CAR2, time);
		break;

		case 3:
			MMS1_addObstruction(3, 2, 1.5, 0.25, 0, 0, 0, 10, false, 1000, MMS1_OBSTRUCTION_TYPE_CAR3, time);
		break;

		case 4:
			MMS1_addObstruction(3, 2, 1.5, 0.25, 0, 0, 0, 10, false, 1000, MMS1_OBSTRUCTION_TYPE_CAR4, time);
		break;

		case 5:
			MMS1_addObstruction(3, 2, 1.5, 0.25, 0, 0, 0, 10, false, 1000, MMS1_OBSTRUCTION_TYPE_CAR5, time);
		break;

		case 6:
			MMS1_addObstruction(3, 2, 1.5, 0.25, 0, 0, 0, 10, false, 1000, MMS1_OBSTRUCTION_TYPE_CAR6, time);
		break;

		default: MMS1_addObstruction(3, 2, 1.5, 0.25, 0, 0, 0, 10, false, 1000, MMS1_OBSTRUCTION_TYPE_CAR7, time);
	};
}

static void p_checkObstructionsPhase2(const uint64_t lane0Duration, const uint64_t lane1Duration, const uint64_t lane2Duration, const uint64_t lane3Duration, const size_t genNum, const bool driftAdjust, const uint64_t time)
{
	const size_t gen3Num = genNum/14;

	if(lane0Duration > 100) p_checkObstructionPhase2Lane0(gen3Num, driftAdjust, time);
	if(lane1Duration > 500) p_checkObstructionPhase2Lane1(gen3Num, driftAdjust, time);
	if(lane2Duration > 10000) p_checkObstructionPhase2Lane2(gen3Num, driftAdjust, time);
	if(lane3Duration > 5000) p_checkObstructionPhase2Lane3(gen3Num, driftAdjust, time);
}

static void p_checkObstructionPhase3Lane0(const size_t genNum, const bool driftAdjust, const uint64_t time)
{
	if(genNum < 75)
	{
		if(genNum < 12)
		{
			MMS1_addObstruction(0, 1, 1, 0, 0, 0, 0, 5, false, 1000, MMS1_OBSTRUCTION_TYPE_BAG, time);
		}else{
			if(genNum < 24)
			{
				MMS1_addObstruction(0, 2, 1.5, 0, 0, 0, 0, 5, false, 1000, MMS1_OBSTRUCTION_TYPE_BAG2, time);
			}else{
				if(genNum < 36)
				{
					MMS1_addObstruction(0, 1, 2.5, 0, 0, 0, 0, 5, false, 1000, MMS1_OBSTRUCTION_TYPE_BARREL, time);
				}else{
					if(genNum < 48)
					{
						MMS1_addObstruction(0, 1, 1, 0, 0, 0, 0, 5, false, 1000, MMS1_OBSTRUCTION_TYPE_BRICKS, time);
					}else{
						if(genNum < 60) MMS1_addObstruction(0, 1, 1, 0, 0, 0, 0, 5, false, 1000, MMS1_OBSTRUCTION_TYPE_CRATE, time);
						else MMS1_addObstruction(0, 2, 2, 0, 0, 0, 0, 5, false, 1000, MMS1_OBSTRUCTION_TYPE_PIPES, time);
					}
				}
			}
		}
	}else{
		if(genNum < 85) MMS1_addObstruction(0, 2, 1.5, 0.1, 0, 0, 0, 25, false, 250, MMS1_OBSTRUCTION_TYPE_CAR8, time);
		else MMS1_addObstruction(0, 2, 1.5, 0.1, 0, 0, 0, 25, false, 250, MMS1_OBSTRUCTION_TYPE_CAR9, time);
	}
}

static void p_checkObstructionPhase3Lane1(const size_t genNum, const bool driftAdjust, const uint64_t time)
{
	if(genNum < 75)
	{
		if(genNum < 12)
		{
			MMS1_addObstruction(1, 1, 1, 0, 0, 0, 0, 5, false, 1000, MMS1_OBSTRUCTION_TYPE_BAG, time);
		}else{
			if(genNum < 24)
			{
				MMS1_addObstruction(1, 2, 1.5, 0, 0, 0, 0, 5, false, 1000, MMS1_OBSTRUCTION_TYPE_BAG2, time);
			}else{
				if(genNum < 36)
				{
					MMS1_addObstruction(1, 1, 3, 0, 0, 0, 0, 5, false, 1000, MMS1_OBSTRUCTION_TYPE_BARREL, time);
				}else{
					if(genNum < 48)
					{
						MMS1_addObstruction(1, 1, 1, 0, 0, 0, 0, 5, false, 1000, MMS1_OBSTRUCTION_TYPE_BRICKS, time);
					}else{
						if(genNum < 60) MMS1_addObstruction(1, 1, 1, 0, 0, 0, 0, 5, false, 1000, MMS1_OBSTRUCTION_TYPE_CRATE, time);
						else MMS1_addObstruction(1, 2, 2, 0, 0, 0, 0, 5, false, 1000, MMS1_OBSTRUCTION_TYPE_PIPES, time);
					}
				}
			}
		}
	}else{
		if(genNum < 85) MMS1_addObstruction(1, 2, 1.5, 0.1, 0, 0, 0, 25, false, 250, MMS1_OBSTRUCTION_TYPE_CAR8, time);
		else MMS1_addObstruction(1, 2, 1.5, 0.1, 0, 0, 0, 25, false, 250, MMS1_OBSTRUCTION_TYPE_CAR9, time);
	}
}

static void p_checkObstructionPhase3Lane2(const size_t genNum, const bool driftAdjust, const uint64_t time)
{
	if(genNum < 50) MMS1_addObstruction(2, 2, 1.5, 0.1, 0, 0, 0, 25, false, 250, MMS1_OBSTRUCTION_TYPE_CAR8, time);
	else MMS1_addObstruction(2, 2, 1.5, 0.1, 0, 0, 0, 25, false, 250, MMS1_OBSTRUCTION_TYPE_CAR9, time);
}

static void p_checkObstructionPhase3Lane3(const size_t genNum, const bool driftAdjust, const uint64_t time)
{
	if(genNum < 50) MMS1_addObstruction(3, 2, 1.5, 0.1, 0, 0, 0, 25, false, 250, MMS1_OBSTRUCTION_TYPE_CAR8, time);
	else MMS1_addObstruction(3, 2, 1.5, 0.1, 0, 0, 0, 25, false, 250, MMS1_OBSTRUCTION_TYPE_CAR9, time);
}

static void p_checkObstructionsPhase3(const uint64_t lane0Duration, const uint64_t lane1Duration, const uint64_t lane2Duration, const uint64_t lane3Duration, const size_t genNum, const bool driftAdjust, const uint64_t time)
{
	if(lane0Duration > 1000) p_checkObstructionPhase3Lane0(genNum, driftAdjust, time);
	if(lane1Duration > 2500) p_checkObstructionPhase3Lane1(genNum, driftAdjust, time);
	if(lane2Duration > 5000) p_checkObstructionPhase3Lane2(genNum, driftAdjust, time);
	if(lane3Duration > 7500) p_checkObstructionPhase3Lane3(genNum, driftAdjust, time);
}

static void p_checkObstructionPhase4Lane0(const size_t genNum, const bool driftAdjust, const uint64_t time)
{
	if(genNum < 20)
	{
		MMS1_addObstruction(0, 2, 1.5, 0.1, 0, 0, 0, 25, false, 250, MMS1_OBSTRUCTION_TYPE_CAR10, time);
	}else{
		if(genNum < 40)
		{
			MMS1_addObstruction(0, 2, 1.5, 0.1, 0, 0, 0, 25, false, 250, MMS1_OBSTRUCTION_TYPE_CAR11, time);
		}else{
			if(genNum < 60)
			{
				MMS1_addObstruction(0, 2, 1.5, 0.1, 0, 0, 0, 25, false, 250, MMS1_OBSTRUCTION_TYPE_CAR12, time);
			}else{
				if(genNum < 80)
				{
					MMS1_addObstruction(0, 2, 1.5, 0.1, 0, 0, 0, 25, false, 250, MMS1_OBSTRUCTION_TYPE_CAR13, time);
				}else{
					MMS1_addObstruction(0, 2, 1.5, 0.1, 0, 0, 0, 25, false, 250, MMS1_OBSTRUCTION_TYPE_CAR14, time);
				}
			}
		}
	}
}

static void p_checkObstructionPhase4Lane1(const size_t genNum, const bool driftAdjust, const uint64_t time)
{
	if(genNum < 20)
	{
		MMS1_addObstruction(1, 2, 1.5, 0.1, 0, 0, 0, 25, false, 250, MMS1_OBSTRUCTION_TYPE_CAR10, time);
	}else{
		if(genNum < 40)
		{
			MMS1_addObstruction(1, 2, 1.5, 0.1, 0, 0, 0, 25, false, 250, MMS1_OBSTRUCTION_TYPE_CAR11, time);
		}else{
			if(genNum < 60)
			{
				MMS1_addObstruction(1, 2, 1.5, 0.1, 0, 0, 0, 25, false, 250, MMS1_OBSTRUCTION_TYPE_CAR12, time);
			}else{
				if(genNum < 80)
				{
					MMS1_addObstruction(1, 2, 1.5, 0.1, 0, 0, 0, 25, false, 250, MMS1_OBSTRUCTION_TYPE_CAR13, time);
				}else{
					MMS1_addObstruction(1, 2, 1.5, 0.1, 0, 0, 0, 25, false, 250, MMS1_OBSTRUCTION_TYPE_CAR14, time);
				}
			}
		}
	}
}

static void p_checkObstructionPhase4Lane2(const size_t genNum, const bool driftAdjust, const uint64_t time)
{
	if(genNum < 20)
	{
		MMS1_addObstruction(2, 2, 1.5, 0.1, 0, 0, 0, 25, false, 1000, MMS1_OBSTRUCTION_TYPE_CAR10, time);
	}else{
		if(genNum < 40)
		{
			MMS1_addObstruction(2, 2, 1.5, 0.1, 0, 0, 0, 25, false, 1000, MMS1_OBSTRUCTION_TYPE_CAR11, time);
		}else{
			if(genNum < 60)
			{
				MMS1_addObstruction(2, 2, 1.5, 0.1, 0, 0, 0, 25, false, 1000, MMS1_OBSTRUCTION_TYPE_CAR12, time);
			}else{
				if(genNum < 80)
				{
					MMS1_addObstruction(2, 2, 1.5, 0.1, 0, 0, 0, 25, false, 1000, MMS1_OBSTRUCTION_TYPE_CAR13, time);
				}else{
					MMS1_addObstruction(2, 2, 1.5, 0.1, 0, 0, 0, 25, false, 1000, MMS1_OBSTRUCTION_TYPE_CAR14, time);
				}
			}
		}
	}
}

static void p_checkObstructionPhase4Lane3(const size_t genNum, const bool driftAdjust, const uint64_t time)
{
	if(genNum < 20)
	{
		MMS1_addObstruction(3, 1, 1.25, 0.1, 0, 0, 0, 25, false, 250, MMS1_OBSTRUCTION_TYPE_CAR10, time);
	}else{
		if(genNum < 40)
		{
			MMS1_addObstruction(3, 2, 1.5, 0.1, 0, 0, 0, 25, false, 250, MMS1_OBSTRUCTION_TYPE_CAR11, time);
		}else{
			if(genNum < 60)
			{
				MMS1_addObstruction(3, 2, 1.5, 0.1, 0, 0, 0, 25, false, 250, MMS1_OBSTRUCTION_TYPE_CAR12, time);
			}else{
				if(genNum < 80)
				{
					MMS1_addObstruction(3, 2, 1.5, 0.1, 0, 0, 0, 25, false, 250, MMS1_OBSTRUCTION_TYPE_CAR13, time);
				}else{
					MMS1_addObstruction(3, 2, 1.5, 0.1, 0, 0, 0, 25, false, 250, MMS1_OBSTRUCTION_TYPE_CAR14, time);
				}
			}
		}
	}
}

static void p_checkObstructionsPhase4(const uint64_t lane0Duration, const uint64_t lane1Duration, const uint64_t lane2Duration, const uint64_t lane3Duration, const size_t genNum, const bool driftAdjust, const uint64_t time)
{
	if(lane0Duration > 1000) p_checkObstructionPhase4Lane0(genNum, driftAdjust, time);
	if(lane1Duration > 2500) p_checkObstructionPhase4Lane1(genNum, driftAdjust, time);
	if(lane2Duration > 5000) p_checkObstructionPhase4Lane2(genNum, driftAdjust, time);
	if(lane3Duration > 10000) p_checkObstructionPhase4Lane3(genNum, driftAdjust, time);
}

static void p_checkObstructions(const size_t phase, const size_t playerLane, const uint64_t time)
{
	const uint64_t lane0Duration = time - p_objGenMarker[0];
	const uint64_t lane1Duration = time - p_objGenMarker[1];
	const uint64_t lane2Duration = time - p_objGenMarker[2];
	const uint64_t lane3Duration = time - p_objGenMarker[3];

	const size_t genNum = PLEX_randomNumber(0, 100);

	const bool driftAdjust = PLEX_randomNumber(0, 10) < 5;

	if(!p_start) return;

	if(!phase) p_checkObstructionsPhase0(lane0Duration, lane1Duration, lane2Duration, lane3Duration, genNum, driftAdjust, time);

	if(phase == 1) p_checkObstructionsPhase1(lane0Duration, lane1Duration, lane2Duration, lane3Duration, genNum, driftAdjust, time);
	if(phase == 2) p_checkObstructionsPhase2(lane0Duration, lane1Duration, lane2Duration, lane3Duration, genNum, driftAdjust, time);
	if(phase == 3) p_checkObstructionsPhase3(lane0Duration, lane1Duration, lane2Duration, lane3Duration, genNum, driftAdjust, time);
	if(phase == 4) p_checkObstructionsPhase4(lane0Duration, lane1Duration, lane2Duration, lane3Duration, genNum, driftAdjust, time);

	p_checkObstructionsAllPhases(playerLane, time);
}

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

void MMS1_resetObstructionStart()
{
	p_start = 0;
	p_obstructionCount = 0;
}

void MMS1_checkMarkObstructionStart(const uint64_t time)
{
	if(p_start) return;

	p_start = time;
}

void MMS1_addObstruction(const size_t lane, const double w, const double h, const double velocity, const double driftVelocity, const double leftDrift, const double rightDrift, const double weight, const bool startDriftRight, const uint64_t duration, const MMS1_OBSTRUCTION_TYPE type, const uint64_t time)
{
	if(p_objGenDuration[lane]) return;

	p_objGenDuration[lane] = duration;
	p_objGenMarker[lane] = time;
	p_objGen[lane] = MMS1_genObstruction(lane, w, h, velocity, driftVelocity, leftDrift, rightDrift, weight, startDriftRight, type);
}

bool MMS1_beginObstructionManager(const size_t chapter1SpriteTex, const uint64_t time)
{
	MMS1_beginObstructions(chapter1SpriteTex, time);

	for(size_t ze = 0; ze < 4; ++ze)
	{
		p_objGenDuration[ze] = 0;
		p_objGenMarker[ze] = 0;
	}

	p_obstructionCount = 0;

	p_warnPlayer = false;

	return true;
}

bool MMS1_updateObstructionManager(const size_t phase, const size_t lane, const uint64_t time)
{
	MMS1_updateObstructions(phase, lane, time);

	p_checkObstructions(phase, lane, time);

	for(size_t ze = 0; ze < p_obstructionCount; ++ze) p_updateObstruction(ze, p_obstructions + ze, time, PLEX_getGameSecondsPassed());

	return true;
}

void MMS1_endObstructionManager(){ MMS1_endObstructions(); }

uint64_t MMS1_obstructionStart(){ return p_start; }

bool MMS1_warnPlayer(){ return p_warnPlayer; }
