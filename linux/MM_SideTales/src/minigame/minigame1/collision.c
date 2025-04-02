#include "minigame/minigame1/function.h"

static PLEX_RECT p_playerRegion, p_carDrawArea, p_carBackArea, p_carSeatArea, p_carWindshieldArea, p_carWingLeftArea, p_carWingRightArea;

static double p_backHealth = 1, p_carSeatHealth = 1, p_windshieldHealth = 1, p_carWingLeftHealth = 1, p_carWingRightHealth = 1;

static double p_accel = 0;
static double p_accelMod = 1;
static double p_dist = 0;

static uint64_t p_crashMarker = 0;
static uint64_t p_crashDuration = 0;

static void p_updateAreas()
{
	p_carDrawArea = PLEX_convRect(PLEX_convPoint(p_playerRegion.origin.x - p_playerRegion.dimens.w * 1.5, p_playerRegion.origin.y), PLEX_convDimens(p_playerRegion.dimens.w * 4, p_playerRegion.dimens.h));

	p_carBackArea = p_carDrawArea;

	p_carWingLeftArea = p_carDrawArea;
	p_carWingRightArea = p_carDrawArea;

	p_carBackArea.origin.x += p_carBackArea.dimens.w * 0.2;
	p_carBackArea.dimens.w *= 0.6;

	p_carWindshieldArea = p_carBackArea;
	p_carWindshieldArea.origin.x += p_carSeatArea.dimens.w * 0.25;
	p_carWindshieldArea.dimens.h *= 0.25;
	p_carWindshieldArea.dimens.w *= 0.6;

	p_carSeatArea = p_carWindshieldArea;

	p_carWingLeftArea.origin.x += p_carWingLeftArea.dimens.w * 0.05;
	p_carWingLeftArea.origin.y += p_carWingLeftArea.dimens.h * 0.355;
	p_carWingLeftArea.dimens.w *= 0.3;
	p_carWingLeftArea.dimens.h *= 0.3;

	p_carWingRightArea.origin.x += p_carWingRightArea.dimens.w * 0.7;
	p_carWingRightArea.origin.y += p_carWingRightArea.dimens.h * 0.355;
	p_carWingRightArea.dimens.w *= 0.25;
	p_carWingRightArea.dimens.h *= 0.3;
}

static void p_updateAccel()
{
	p_accelMod = (MMS1_carBackHealth() * 0.5) + 0.5;
	p_dist += p_accel * p_accelMod * PLEX_getGameSecondsPassed();
}

static double p_driftAdjust(const double health)
{
	return MMS1_DRIFTSPEED * PLEX_getGameSecondsPassed() + health * MMS1_DRIFTHEALTHEFFECT;
}

static PLEX_POINT p_translateLane0Move(const double velocity, const PLEX_POINT xy, const double tilt, double* totalVelocity)
{
	const double lTotalVelocity = MMS1_totalObstructionVelocity(velocity);

	PLEX_POINT ret = xy;

	ret.x -= lTotalVelocity - tilt;
	ret.y += lTotalVelocity * MMS1_ANGLERISE;

	*totalVelocity = lTotalVelocity;

	return ret;
}

static PLEX_POINT p_translateLane1Move(const double velocity, const PLEX_POINT xy, const double tilt, double* totalVelocity)
{
	const double lTotalVelocity = MMS1_totalObstructionVelocity(velocity);

	PLEX_POINT ret = xy;

	ret.x += tilt;
	ret.y += lTotalVelocity * MMS1_ANGLERISE;

	*totalVelocity = lTotalVelocity;

	return ret;
}

static PLEX_POINT p_translateLane2Move(const double velocity, const PLEX_POINT xy, const double tilt, double* totalVelocity)
{
	const double lTotalVelocity = MMS1_totalObstructionVelocity(velocity);

	PLEX_POINT ret = xy;

	ret.x += tilt;
	ret.y -= lTotalVelocity * MMS1_ANGLERISE;

	*totalVelocity = lTotalVelocity;

	return ret;
}

static PLEX_POINT p_translateLane3Move(const double velocity, const PLEX_POINT xy, const double tilt, double* totalVelocity)
{
	const double lTotalVelocity = MMS1_totalObstructionVelocity(velocity);

	PLEX_POINT ret = xy;

	ret.x -= lTotalVelocity - tilt;
	ret.y -= lTotalVelocity * MMS1_ANGLERISE;

	*totalVelocity = lTotalVelocity;

	return ret;
}

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

void MMS1_resetCarDamage()
{
	p_backHealth = 1;
	p_carSeatHealth = 1;
	p_windshieldHealth = 1;
	p_carWingLeftHealth = 1;
	p_carWingRightHealth = 1;
}

PLEX_POINT MMS1_translateLaneMove(const size_t lane, const double velocity, const PLEX_POINT xy, const double tilt, double* totalVelocity)
{
	PLEX_POINT ret = xy;

	if(PLEX_getGameTimePaused()) return ret;

	switch(lane)
	{
		case 0: ret = p_translateLane0Move(velocity, xy, tilt, totalVelocity); break;
		case 1: ret = p_translateLane1Move(velocity, xy, tilt, totalVelocity); break;
		case 2: ret = p_translateLane2Move(velocity, xy, tilt, totalVelocity); break;
		case 3: ret = p_translateLane3Move(velocity, xy, tilt, totalVelocity); break;
	};

	return ret;
}

double MMS1_translateLaneProp(const double y, const double h)
{
	const double range = PLEX_HEIGHTUNITMAX() * 0.75;
	const double area = PLEX_HEIGHTUNITMAX() - range;

	const double dist = (y + h - range);

	return dist/area * MMS1_DRAWTRANSLATE + (1 - MMS1_DRAWTRANSLATE);
}

double MMS1_totalObstructionVelocity(const double velocity)
{
	const double secondsPass = PLEX_getGameSecondsPassed();

	const double natural =  MM1_OBSTRUCTIONVELOCITYLOW + (MM1_OBSTRUCTIONVELOCITYBASE * secondsPass) * (MMS1_accel()/MMS1_ACCEL_MAX);

	return velocity + natural;
}

void MMS1_driftLeft()
{
	p_playerRegion.origin.x -= p_driftAdjust(p_carWingLeftHealth);

	if(p_playerRegion.origin.x < MMS1_BOUNDARYRANGE) p_playerRegion.origin.x = MMS1_BOUNDARYRANGE;
}

void MMS1_driftRight()
{
	p_playerRegion.origin.x += p_driftAdjust(p_carWingRightHealth);

	if(p_playerRegion.origin.x > PLEX_WIDTHUNITMAX() - MMS1_BOUNDARYRANGE) p_playerRegion.origin.x = PLEX_WIDTHUNITMAX() - MMS1_BOUNDARYRANGE;
}

void MMS1_factorDamageDrift()
{
	const double damageDrift = (1 - p_carSeatHealth) * PLEX_getGameSecondsPassed();

	p_playerRegion.origin.x -= damageDrift;
}

void MMS1_capAccel()
{
	if(p_accel < 0) p_accel = 0;
	if(p_accel > MMS1_ACCEL_MAX) p_accel = MMS1_ACCEL_MAX;
}

void MMS1_accelCar()
{
	if(p_accel < 5) p_accel = 5;

	p_accel += MMS1_ACCELRATE * PLEX_getGameSecondsPassed();

	MMS1_capAccel();
}

void MMS1_deaccelCar()
{
	p_accel -= MMS1_ACCELRATE * PLEX_getGameSecondsPassed();

	MMS1_capAccel();
}

void MMS1_accumAccel()
{
	if(p_accel < MMS1_ACCELFASTCAP) p_accel += MMS1_ACCELRATE * PLEX_getGameSecondsPassed();
	else if(p_accel < MMS1_ACCELFASTERCAP) p_accel += MMS1_FASTACCELRATE * PLEX_getGameSecondsPassed();
	else if(p_accel < MMS1_ACCELFASTESTCAP) p_accel -= MMS1_CAPDEACCELRATE * PLEX_getGameSecondsPassed();
	else p_accel -= MMS1_DEACCELRATE * PLEX_getGameSecondsPassed();

	MMS1_capAccel();
}

void MMS1_stopAccel()
{
	p_accel = 0;
}

void MMS1_controlledDeccelCar(const double amount)
{
	p_accel -= amount;

	MMS1_capAccel();
}

void MMS1_setCrashMarker(const uint64_t time){ p_crashMarker = time; }
void MMS1_incrementCrashDuration(const uint64_t by){ p_crashDuration += by; }

uint64_t MMS1_checkUpdateCrash(const uint64_t time)
{
	bool crash = false;

	if(!p_crashDuration) return 0;

	crash = MMS1_crashTime(time) > p_crashDuration;

	if(crash)
	{
		MMS1_startCarSprites(time);

		p_crashDuration = 0;

		return 0;
	}

	return MMS1_crashTime(time);
}

bool MMS1_beginCollision(const uint64_t time)
{
	p_playerRegion = PLEX_convRect(PLEX_convPoint(PLEX_WIDTHUNITMAX()/2 - 0.25 + 1.5, PLEX_HEIGHTUNITMAX() - 2), PLEX_convDimens(0.75, 1.5));

	p_dist = 0;
	p_accel = MMS1_STARTACCEL;
	p_accelMod = 1;

	return true;
}

void MMS1_damageCarBack(const double damage)
{
	p_backHealth -= damage;
	if(p_backHealth < 0) p_backHealth = 0;
}

void MMS1_damageCarSeat(const double damage)
{
	p_carSeatHealth -= damage;
	if(p_carSeatHealth < 0) p_carSeatHealth = 0;
}

void MMS1_damageWindshield(const double damage)
{
	p_windshieldHealth -= damage;
	if(p_windshieldHealth < 0) p_windshieldHealth = 0;
}

void MMS1_damageCarLeft(const double damage)
{
	p_carWingLeftHealth -= damage;
	if(p_carWingLeftHealth < 0) p_carWingLeftHealth = 0;
}

void MMS1_damageCarRight(const double damage)
{
	p_carWingRightHealth -= damage;
	if(p_carWingRightHealth < 0) p_carWingRightHealth = 0;
}

bool MMS1_updateCollision(const size_t backing, const uint64_t time)
{
	if(p_playerRegion.origin.x + p_playerRegion.dimens.w/2 - p_carDrawArea.dimens.w/2 < 0) p_playerRegion.origin.x = p_carDrawArea.dimens.w/2 - p_playerRegion.dimens.w/2;
	if(p_playerRegion.origin.x + p_playerRegion.dimens.w/2 + p_carDrawArea.dimens.w/2 > PLEX_WIDTHUNITMAX()) p_playerRegion.origin.x = PLEX_WIDTHUNITMAX() - p_carDrawArea.dimens.w/2 - p_playerRegion.dimens.w/2;

	p_updateAreas();

	p_updateAccel();

	return true;
}

void MMS1_endCollision()
{

}

double MMS1_dist(){ return p_dist; }
double MMS1_accel(){ return p_accel; }
double MMS1_accelMod(){ return p_accelMod; }

uint64_t MMS1_crashTime(const uint64_t time){ return time - p_crashMarker; }
uint64_t MMS1_crashDuration(){ return p_crashDuration; }
uint64_t MMS1_crashMarker(){ return p_crashMarker; }

double MMS1_carBackHealth(){ return p_backHealth; }
double MMS1_carSeatHealth(){ return p_carSeatHealth; }
double MMS1_windshieldHealth(){ return p_windshieldHealth; }
double MMS1_carWingLeftHealth(){ return p_carWingLeftHealth; }
double MMS1_carWingRightHealth(){ return p_carWingRightHealth; }

PLEX_RECT MMS1_playerRegion(){ return p_playerRegion; }
PLEX_RECT MMS1_carDrawArea(){ return p_carDrawArea; }
PLEX_RECT MMS1_carBackArea(){ return p_carBackArea; }
PLEX_RECT MMS1_carSeatArea(){ return p_carSeatArea; }
PLEX_RECT MMS1_carWindshieldArea(){ return p_carWindshieldArea; }
PLEX_RECT MMS1_carWingLeftArea(){ return p_carWingLeftArea; }
PLEX_RECT MMS1_carWingRightArea(){ return p_carWingRightArea; }
