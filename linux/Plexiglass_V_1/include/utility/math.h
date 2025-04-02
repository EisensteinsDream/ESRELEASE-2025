#ifndef PLEX_MATH_H
#define PLEX_MATH_H

#include "utility/error.h"

// This is a unit that contains basic reusable math functions. Also includes geometric and collision data. Also includes random numbers and other useful functions in that vein.

#include "meta/cinclude.h"

// macro functions and macros -----------------------------------------------------------------------------------------------

// insures that pi exists for equations that need them

#ifdef M_PI
	#define p_PI M_PI
#else
	#define p_PI 3.1415926
#endif

// indicates the precision type for math. This should either be a double or a float. There may eventually be a default to chose the precision between. In most cases a double should be fine but on older systems changing to a float might give a bit of a performance boost.

#ifndef PLEX_MPREC_TYPE
	#define PLEX_MPREC_TYPE double
#endif

typedef PLEX_MPREC_TYPE PLEX_MPREC;

// ARGUMENTS: (const PLEX_MPREC min, const PLEX_MPREC max) - returns PLEX_MPREC

#define PLEX_randomNumber(min, max) PLEX_randomNumberInt(min, max, __LINE__, __FILE__)

// ARGUMENTS: (const PLEX_POINT point, const PLEX_POLYGON polygon, const PLEX_MPREC moveX, const PLEX_MPREC moveY) - returns uint8_t

#define PLEX_pointToPolygonCollision(point, polygon, moveX, moveY) PLEX_pointToPolygonCollisionInt(point, polygon, moveX, moveY, __LINE__, __FILE__)

// ARGUMENTS: (const PLEX_POLYGON a, const PLEX_POLYGON b, const PLEX_MPREC moveX, const PLEX_MPREC moveY) - returns uint8_t

#define PLEX_polygonToPolygonCollision(a, b, moveX, moveY) PLEX_polygonToPolygonCollisionInt(a, b, moveX, moveY, __LINE__, __FILE__)

// ARGUMENTS: (const PLEX_POINT point, const PLEX_POLYGON polygon) ) - returns uint8_t

#define PLEX_pointToPolygonCollisionNoMove(point, polygon) PLEX_pointToPolygonCollisionNoMoveInt(point, polygon, __LINE__, __FILE__);

// ARGUMENTS: (const PLEX_POLYGON a, const PLEX_POLYGON b) - returns uint8_t

#define PLEX_polygonToPolygonCollisionNoMove(a, b) PLEX_polygonToPolygonCollisionNoMoveInt(a, b, __LINE__, __FILE__);

// structs, unions, enums, function prototypes ------------------------------------------------------------------------------

// a point is a coordinate, dimens are usually the dimensions of rectangles

typedef struct
{
	PLEX_MPREC x, y;
} PLEX_POINT;

typedef struct
{
	PLEX_MPREC w, h;
} PLEX_DIMENS;

// a struct to hold information for a line. This is not used as extensively in PLEX as I would like.

typedef struct
{
	PLEX_POINT origin, intercept;
	PLEX_MPREC slope, length, lenx, leny, rise, run;
} PLEX_LINE;

// a rectangle, basically contains an 'origin' for the point of origin and dimens for the dimensions.

typedef struct
{
	PLEX_POINT origin;
	PLEX_DIMENS dimens;
} PLEX_RECT;

typedef struct
{
	PLEX_POINT points[PLEX_LIMIT_POLYSIDES];
	size_t pointCount;
} PLEX_POLYGON;

// public functions ---------------------------------------------------------------------------------------------------------

#ifdef __cplusplus
extern"C"
{
#endif

// specialized functions ----------------------------------------------------------------------------------------------------

	// returns the signum which C's standard math library doesn't seem to have for some reason

	extern PLEX_MPREC PLEX_signum(const PLEX_MPREC num);

	// returns the signum which C's standard math library doesn't seem to have for some reason

	extern PLEX_MPREC PLEX_invSignum(const PLEX_MPREC num);

	// converts degrees into radians

	extern PLEX_MPREC PLEX_radians(const PLEX_MPREC degrees);

	// converts radians into degrees

	extern PLEX_MPREC PLEX_degrees(const PLEX_MPREC radians);

	// square root function that's potentially faster than the built in function as it uses square root tables

	extern PLEX_MPREC PLEX_squareRoot(const PLEX_MPREC num);

	// square function that's potentially faster than the built in function as it uses square root tables

	extern PLEX_MPREC PLEX_square(const PLEX_MPREC num);

	// the difference between two numbers. Not to be confuses with subtraction as this is the actual numerical difference. I.E. negative two minus four would be negative six. However, the difference between negative two and four is actually six numbers.

	extern PLEX_MPREC PLEX_difference(const PLEX_MPREC a, const PLEX_MPREC b);

	// turns off the internal random algorithm and sets it to a fixed seed

	extern void PLEX_rigSeed(const uint8_t fixedNumber);

	// turns the internal random algorithms back on after setting them to a fixed seed

	extern void PLEX_unrigSeed();

	// returns a random percentage (ie. decimal between 0.00 and 1.00)

	extern PLEX_MPREC PLEX_randomPercentage();

	// returns a random number between minimum and maximum

	extern PLEX_MPREC PLEX_randomNumberInt(const PLEX_MPREC min, const PLEX_MPREC max, const size_t errorline, const char* const errorfile);

	// converts an x and a y into a plex point struct

	extern PLEX_POINT PLEX_convPoint(const PLEX_MPREC x, const PLEX_MPREC y);

	//  converts a width and a height to a plex dimensions struct

	extern PLEX_DIMENS PLEX_convDimens(const PLEX_MPREC w, const PLEX_MPREC h);

	// converts two points into a plex line struct which also contains the slope, rise, run, length, length x, and length y

	extern PLEX_LINE PLEX_convLine(const PLEX_POINT a, const PLEX_POINT b);

	// converts a point and dimensions into a rectangle struct

	extern PLEX_RECT PLEX_convRect(const PLEX_POINT origin, const PLEX_DIMENS dimens);

	// returns the distance, xlen, and ylen between two points

	extern PLEX_MPREC PLEX_distance(const PLEX_POINT point, const PLEX_POINT point2, PLEX_MPREC* lenx, PLEX_MPREC* leny);

	// returns the slope rise, and run between two points

	extern PLEX_MPREC PLEX_slope(const PLEX_POINT point, const PLEX_POINT point2, PLEX_MPREC* rise, PLEX_MPREC* run);

	// returns the slope's angle in radians

	extern PLEX_MPREC PLEX_slopeToRads(const PLEX_MPREC slope);

	// returns radians of a passed in rise and run value

	extern PLEX_MPREC PLEX_slopeToRads2(const PLEX_MPREC rise, const PLEX_MPREC run);

	// returns the angle in radians between two points

	extern PLEX_MPREC PLEX_radsBetweenPoints(const PLEX_POINT point, const PLEX_POINT point2);

	// returns the xIntercept of a point and a slope

	extern PLEX_MPREC PLEX_xIntercept(const PLEX_POINT point, const PLEX_MPREC slope);

	// returns the yIntercept of a point and a slope

	extern PLEX_MPREC PLEX_yIntercept(const PLEX_POINT point, const PLEX_MPREC slope);

	// returns a point equivalent to the intercept of a slope

	extern PLEX_POINT PLEX_intercept(const PLEX_POINT point, const PLEX_MPREC slope);

	// returns the end of a line from it's origin

	extern PLEX_POINT PLEX_endPoint(const PLEX_LINE line);

	// returns the halfway point from a line's origin

	extern PLEX_POINT PLEX_halfPoint(const PLEX_LINE line);

	// returns if a point is inside a rectangle

	extern bool PLEX_insideRect(const PLEX_POINT point, const PLEX_RECT rect);

	// returns if any chunk of a rectangle is inside another rectangle

	extern bool PLEX_rectInsideRect(const PLEX_RECT rectA, const PLEX_RECT rectB);

	// returns the side (0 - no collision, 1 - topside, 2 - right side, 3 - bottom side, 4 - left side, 5 - collision but no particular side)

	extern uint8_t PLEX_rectCollision(const PLEX_RECT rect, const PLEX_RECT rect2, const PLEX_MPREC moveX, const PLEX_MPREC moveY);

	// same as rectCollision but assuming that the rects are not moving.

	extern uint8_t PLEX_rectCollisionNoMove(const PLEX_RECT rect, const PLEX_RECT rect2);

	// returns whether a point is below a line. Not just in terms of y space but adjusted to whatever angle the line is facing. I have not tested this in awhile so I'm considering it experimental/untested.

	extern bool PLEX_pointBelowLine(const PLEX_POINT point, const PLEX_LINE line);

	// converts a rectangle into a polygon version of itself

	extern PLEX_POLYGON PLEX_convRectToPoly(const PLEX_RECT rect);

	// determines if a point is colliding with a polygon. Since this uses pointBelowLine it's considered experimental/untested for the time being.

	extern uint8_t PLEX_pointToPolygonCollisionInt(const PLEX_POINT point, const PLEX_POLYGON polygon, const PLEX_MPREC moveX, const PLEX_MPREC moveY, const size_t errorline, const char* const errorfile);

	// determines whether a polygon is colliding with another polygon. Since this uses pointBelowLine it's considered experimental/untested for the time being.

	extern uint8_t PLEX_polygonToPolygonCollisionInt(const PLEX_POLYGON a, const PLEX_POLYGON b, const PLEX_MPREC moveX, const PLEX_MPREC moveY, const size_t errorline, const char* const errorfile);

	// determines whether a point is inside a polygon assuming neither is moving. Since this uses pointBelowLine it's considered experimental/untested for the time being.

	extern uint8_t PLEX_pointToPolygonCollisionNoMoveInt(const PLEX_POINT point, const PLEX_POLYGON polygon, const size_t errorline, const char* const errorfile);

	// determines whether a polygon is colliding with another polygon assuming neither is moving. Since this uses pointBelowLine it's considered experimental/untested for the time being.

	extern uint8_t PLEX_polygonToPolygonCollisionNoMoveInt(const PLEX_POLYGON a, const PLEX_POLYGON b, const size_t errorline, const char* const errorfile);

	// returns the radians of the percentage of a slice of a circle

	extern PLEX_MPREC PLEX_circlePerc(const PLEX_MPREC perc);

// start, update, end functions ---------------------------------------------------------------------------------------------

	// starts the math function. Doesn't need to be called as PLEX_start calls it. Doesn't need to return a boolean as it, for the time being,  cannot fail.

	extern void PLEX_startMath();

// getters ------------------------------------------------------------------------------------------------------------------

	// a built in percentage for reverse diagonal movement among a circle's radius in radians

	extern PLEX_MPREC PLEX_revDiagonalMoveAmount();

	// a built in percentage for diagonal movement among a circle's radius in radians

	extern PLEX_MPREC PLEX_diagonalMoveAmount();

	// returns eighth of the radius of a circle in radians

	extern PLEX_MPREC PLEX_eighthCircleRads();

	// return a quarter of the radius of a circle in radians

	extern PLEX_MPREC PLEX_quarterCircleRads();

	// returns the radius of a half circle in radians

	extern PLEX_MPREC PLEX_halfCircleRads();

	// returns the radius of three quarters of a circle in radians

	extern PLEX_MPREC PLEX_threeQuarterCircleRads();

	// returns the full radius of a complete circle in radians

	extern PLEX_MPREC PLEX_circleRads();
#ifdef __cplusplus
}
#endif

#endif
