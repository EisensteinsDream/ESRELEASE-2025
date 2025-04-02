#ifndef MMS1_FUNCTION_H
#define MMS1_FUNCTION_H

#include "minigame/minigame1/struct.h"

#ifdef __cplusplus
extern "C"
{
#endif

// COLLISION

	// restores the health of all parts of the car

	extern void MMS1_resetCarDamage();

	// moves an obstruction (anything the player can hit) by what lane it's in and velocity

	extern PLEX_POINT MMS1_translateLaneMove(const size_t lane, const double velocity, const PLEX_POINT xy, const double tilt, double* totalVelocity);

	// translates the drawscale of an obstruction depending on it's y and height

	extern double MMS1_translateLaneProp(const double y, const double h);

	// adjusts the velocity of an obstruction by the seconds passed and player acceleration

	extern double MMS1_totalObstructionVelocity(const double velocity);

	// drifts the player left and right

	extern void MMS1_driftLeft();
	extern void MMS1_driftRight();

	// drifts the player automatically dependant on car body damage

	extern void MMS1_factorDamageDrift();

	// accelerate or deccelerate car as response to player input

	extern void MMS1_accelCar();
	extern void MMS1_deaccelCar();

	// accelerate or deccelerate car based automatically

	extern void MMS1_accumAccel();

	// stop the car

	extern void MMS1_stopAccel();

	// manually set the car speed

	extern void MMS1_controlledDeccelCar(const double amount);

	// functions to indicate the time when a crash starts or extend the length of a crash as it's happened (crash duration = how long before the player can start accelerating)

	extern void MMS1_setCrashMarker(const uint64_t time);
	extern void MMS1_incrementCrashDuration(const uint64_t by);

	// functions to damage the individual parts of the car

	extern void MMS1_damageCarBack(const double damage);
	extern void MMS1_damageCarSeat(const double damage);
	extern void MMS1_damageWindshield(const double damage);
	extern void MMS1_damageCarLeft(const double damage);
	extern void MMS1_damageCarRight(const double damage);

	// the begin, update, and end methods of the collision subsystem

	extern bool MMS1_beginCollision(const uint64_t time);
	extern bool MMS1_updateCollision(const size_t backing, const uint64_t time);
	extern void MMS1_endCollision();

	// returns distance travelled

	extern double MMS1_dist();

	// returns the player's acceleration

	extern double MMS1_accel();

	// returns a modifier percent on player's acceleration dependant on car damage

	extern double MMS1_accelMod();

	// check to update crash

	extern uint64_t MMS1_checkUpdateCrash(const uint64_t time);

	// returns the player crash time

	extern uint64_t MMS1_crashTime(const uint64_t time);

	// returns the crash duration (0 == no crash)

	extern uint64_t MMS1_crashDuration();

	// returns the crash marker

	extern uint64_t MMS1_crashMarker();

	// return the health of each portion of the car

	extern double MMS1_carBackHealth();
	extern double MMS1_carSeatHealth();
	extern double MMS1_windshieldHealth();
	extern double MMS1_carWingLeftHealth();
	extern double MMS1_carWingRightHealth();

	// returns the physical space occupied by the player

	extern PLEX_RECT MMS1_playerRegion();

	// returns the physical space occupied by every piece of the car

	extern PLEX_RECT MMS1_carDrawArea();
	extern PLEX_RECT MMS1_carBackArea();
	extern PLEX_RECT MMS1_carSeatArea();
	extern PLEX_RECT MMS1_carWindshieldArea();
	extern PLEX_RECT MMS1_carWingLeftArea();
	extern PLEX_RECT MMS1_carWingRightArea();

// PAM AND CAR

	// updates the cycle speed of the pamaleana sprite

	extern void MMS1_updatePamaleanaCycleSpeed(const uint64_t time);

	// sets pamaleana to the crash sprite if in the crash cycle

	extern void MMS1_updatePamaleanaCrashCycle(const uint64_t crashCycle);

	// starts the animation of the sprites that make up the car body

	extern void MMS1_startCarSprites(const uint64_t time);

	// stops all the car sprites animation

	extern void MMS1_stopCarSprites();

	// the begin, update, and end functions for the pam and car subsystem

	extern bool MMS1_beginPamAndCar(const size_t chapter1SpriteTex, const size_t pamaleanaSpriteTex, const uint64_t time);
	extern bool MMS1_updatePamAndCar(const size_t backing, const uint64_t time);
	extern void MMS1_endPamAndCar();

	// manually changes the pamaleana animation index

	extern void MMS1_setPamAniIndex(const size_t index);

	// returns the animation index of the winshield

	extern size_t MMS1_windshieldAniIndex();

	// returns pamaleana's animation index

	extern size_t MMS1_pamAniIndex();

// ENVIRONMENT

	// the begin, update, and end functions of the environment subsystem

	extern bool MMS1_beginEnvironment(const uint64_t time);
	extern bool MMS1_updateEnvironment(const size_t phase, const double phasePerc, const double completePerc, const uint64_t time);
	extern void MMS1_endEnvironment();

// OBSTRUCTION

	// generates an obstruction (not on the playing field that's 'add obstruction' in obstruction manager)

	extern MMS1_OBSTRUCTION MMS1_genObstruction(const size_t lane, const double w, const double h, const double velocity, const double driftVelocity, const double leftDrift, const double rightDrift, const double weight, const bool startDriftRight, const MMS1_OBSTRUCTION_TYPE type);

	// the beginning, update, and end methods of obstructions subsystem

	extern bool MMS1_beginObstructions(const size_t chapter1SpriteTex, const uint64_t time);
	extern bool MMS1_updateObstructions(const size_t phase, const size_t lane, const uint64_t time);
	extern void MMS1_endObstructions();

// OBSTURCTION MANAGER

	// resets the obstruction start time

	extern void MMS1_resetObstructionStart();

	// sets the obstruction start time if it's not already set

	extern void MMS1_checkMarkObstructionStart(const uint64_t time);

	// adds a new obstruction

	extern void MMS1_addObstruction(const size_t lane, const double w, const double h, const double velocity, const double driftVelocity, const double leftDrift, const double rightDrift, const double weight, const bool startDriftRight, const uint64_t duration, const MMS1_OBSTRUCTION_TYPE type, const uint64_t time);

	// the beginning, update, and end of the obstruction manager subsystem

	extern bool MMS1_beginObstructionManager(const size_t chapter1SpriteTex, const uint64_t time);
	extern bool MMS1_updateObstructionManager(const size_t phase, const size_t lane, const uint64_t time);
	extern void MMS1_endObstructionManager();

	// returns the starting time of the obstruction manager

	extern uint64_t MMS1_obstructionStart();

	// returns whether or not the player should be warned there's a car behind them

	extern bool MMS1_warnPlayer();

// MINIGAME 1

	// calculates the animation cycle based on the current player acceleration

	extern uint64_t MMS1_calcAnimationCycle(const uint64_t min, const uint64_t max);

	// calculates the draw layer dependant on the y, height, and a base layer dependant on what it is

	extern size_t MMS1_calcOverroadLayer(const double y, const double h, const size_t baselayer);
#ifdef __cplusplus
}
#endif

#endif
