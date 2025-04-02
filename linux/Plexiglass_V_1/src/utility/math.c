#include "utility/math.h"

// NOTE: global function descriptions in header.

// NOTE: This is a unit with a state machine affiliated but only has a start function. Some functions will not work if the 'start' function is not called successfully. PLEX_start should call the start function of the state machine so it doesn't need to be called manually.

// static values ------------------------------------------------------------------------------------------------------------------

// square table

static PLEX_MPREC p_sqrtable[PLEX_STANDNUM_SQRTTABLE];

// values for a 'fixed' or 'rigged' seed for randomness
static uint8_t p_seedFix = 0;
static bool p_doFixSeed = false;

// basic numbers for radian and degree conversion. May eventually be macros in the header.
static const PLEX_MPREC p_radConv = p_PI/180.0;
static const PLEX_MPREC p_degConv = 180/p_PI;
static const PLEX_MPREC p_fullRad = 360 * p_radConv;

// values to calculate accurate diagonal movement.
static const PLEX_MPREC p_revDiagonalMoveAmount = -0.707105;
static const PLEX_MPREC p_diagonalMoveAmount = 0.707105;

// constant values for segments of pi that can be used to calculate portions of a circle. May eventually be macros in the header.
static const PLEX_MPREC p_eighthCircleRads = 0.7853981634;
static const PLEX_MPREC p_quarterCircleRads = 1.5707963268;
static const PLEX_MPREC p_halfCircleRads = 3.1415926536;
static const PLEX_MPREC p_threeQuarterCircleRads = 5.4977871438;
static const PLEX_MPREC p_circleRads = 6.2831853072;

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

// specialized functions ----------------------------------------------------------------------------------------------------

PLEX_MPREC PLEX_signum(const PLEX_MPREC num)
{
	if(!num) return 0;

	return num < 0 ? -1 : 1;
}

PLEX_MPREC PLEX_invSignum(const PLEX_MPREC num)
{
	return PLEX_signum(num) * -1;
}

PLEX_MPREC PLEX_radians(const PLEX_MPREC degrees){ return degrees * p_radConv; }
PLEX_MPREC PLEX_degrees(const PLEX_MPREC radians){ return radians * p_degConv; }

PLEX_MPREC PLEX_squareRoot(const PLEX_MPREC num)
{
	PLEX_MPREC neg = 0;
	PLEX_MPREC nnum = 0;

	uint64_t inum = 0;

	if(!num) return 0;

	neg = PLEX_signum(num);
	nnum = neg * num;
	inum = nnum;

	if(inum == nnum && inum < PLEX_STANDNUM_SQRTTABLE) return p_sqrtable[inum];

	return sqrt(nnum);
}

PLEX_MPREC PLEX_square(const PLEX_MPREC num){ return num * num; }

PLEX_MPREC PLEX_difference(const PLEX_MPREC a, const PLEX_MPREC b)
{
	const PLEX_MPREC ret = a > b ? a - b : b - a;

	return ret * PLEX_signum(ret);
}

void PLEX_unrigSeed()
{
	p_doFixSeed = false;
}

void PLEX_rigSeed(const uint8_t fixedNumber)
{
	p_seedFix = (fixedNumber/7) * (fixedNumber % 2) + (fixedNumber/5) * (fixedNumber % 3) + (fixedNumber/2) * (fixedNumber % 5);
	p_doFixSeed = true;
}

PLEX_MPREC PLEX_randomPercentage()
{
	if(!p_doFixSeed)
	{
		static uint64_t variant = 0;

		const uint64_t time = SDL_GetTicks();

		uint32_t base = 0;

		uint64_t subVar = variant/4 % 4 * PLEX_STANDNUM_RANDGENWEIGHT;

		variant += subVar + variant/9 + time/7 + variant/5 + time/3;

		base = (time + variant);

		return (base % PLEX_STANDNUM_RANDPERCPREC)/(double)PLEX_STANDNUM_RANDPERCPREC;
	}else return p_seedFix/256.0;
}

PLEX_MPREC PLEX_randomNumberInt(const PLEX_MPREC min, const PLEX_MPREC max, const size_t errorline, const char* const errorfile)
{
	PLEX_MPREC tMin = min;
	PLEX_MPREC tMax = max;
	PLEX_MPREC range = 0;

	if(min == max)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_MATH, PLEX_ERROR_SAMEVALUE, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_MATH_ONGETRANDOMNUMBER, PLEX_ERRORMESS_MATH_MINMAXRANDNUM, errorline, errorfile);
		return min;
	}

	if(min > max)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_MATH, PLEX_ERROR_MINMAXREVERSE, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_MATH_ONGETRANDOMNUMBER, PLEX_ERRORMESS_MATH_MINMAXRANDNUM, errorline, errorfile);

		tMin = max;
		tMax = min;
	}

	range = tMax - tMin;

	return tMin + (PLEX_randomPercentage() * range);
}

PLEX_POINT PLEX_convPoint(const PLEX_MPREC x, const PLEX_MPREC y)
{
	PLEX_POINT ret;

	ret.x = x;
	ret.y = y;

	return ret;
}

PLEX_DIMENS PLEX_convDimens(const PLEX_MPREC w, const PLEX_MPREC h)
{
	PLEX_DIMENS dimens;

	dimens.w = w;
	dimens.h = h;

	return dimens;
}

PLEX_LINE PLEX_convLine(const PLEX_POINT a, const PLEX_POINT b)
{
	PLEX_LINE line;

	line.origin = a;
	line.slope = PLEX_slope(a, b, &(line.rise), &(line.run));
	line.length = PLEX_distance(a, b, &(line.lenx), &(line.leny));
	line.intercept = PLEX_intercept(line.origin, line.slope);

	return line;
}

PLEX_RECT PLEX_convRect(const PLEX_POINT origin, const PLEX_DIMENS dimens)
{
	PLEX_RECT ret;

	ret.origin = origin;
	ret.dimens = dimens;

	return ret;
}

PLEX_MPREC PLEX_distance(const PLEX_POINT point, const PLEX_POINT point2, PLEX_MPREC* lenx, PLEX_MPREC* leny)
{
	const PLEX_MPREC llenx = point2.x - point.x;
	const PLEX_MPREC lleny = point2.y - point.y;

	*lenx = llenx;
	*leny = lleny;

	return PLEX_squareRoot(PLEX_square(llenx) + PLEX_square(lleny));
}

PLEX_MPREC PLEX_slope(const PLEX_POINT point, const PLEX_POINT point2, PLEX_MPREC* rise, PLEX_MPREC* run)
{
	PLEX_MPREC lrise = point2.y - point.y;
	PLEX_MPREC lrun = point2.x - point.x;

	*rise = lrise;
	*run = lrun;

	if(!lrun) return 0;

	return lrise/lrun;
}

PLEX_MPREC PLEX_slopeToRads(const PLEX_MPREC slope)
{
	return atan(slope);
}

PLEX_MPREC PLEX_slopeToRads2(const PLEX_MPREC rise, const PLEX_MPREC run)
{
	return atan2(rise, run);
}

PLEX_MPREC PLEX_radsBetweenPoints(const PLEX_POINT point, const PLEX_POINT point2)
{
	PLEX_MPREC rise = 0;
	PLEX_MPREC run = 0;

	PLEX_slope(point, point2, &rise, &run);

	return PLEX_slopeToRads2(rise, run);
}

PLEX_MPREC PLEX_xIntercept(const PLEX_POINT point, const PLEX_MPREC slope)
{
	return (0 - point.y)/slope + point.x;
}

PLEX_MPREC PLEX_yIntercept(const PLEX_POINT point, const PLEX_MPREC slope)
{
	return point.y - (slope * point.x);
}

PLEX_POINT PLEX_intercept(const PLEX_POINT point, const PLEX_MPREC slope)
{
	PLEX_POINT ret;

	ret.x = PLEX_xIntercept(point, slope);
	ret.y = PLEX_yIntercept(point, slope);

	return ret;
}

PLEX_POINT PLEX_endPoint(const PLEX_LINE line)
{
	PLEX_POINT point;

	point.x = line.origin.x + line.lenx;
	point.y = line.origin.y + line.leny;

	return point;
}

PLEX_POINT PLEX_halfPoint(const PLEX_LINE line)
{
	PLEX_POINT point;

	point.x = line.origin.x + line.lenx/2;
	point.y = line.origin.y + line.leny/2;

	return point;
}

bool PLEX_insideRect(const PLEX_POINT point, const PLEX_RECT rect)
{
	if(point.x > rect.origin.x + rect.dimens.w) return false;
	if(point.y > rect.origin.y + rect.dimens.h) return false;
	if(point.x < rect.origin.x) return false;
	if(point.y < rect.origin.y) return false;

	return true;
}

bool PLEX_rectInsideRect(const PLEX_RECT rectA, const PLEX_RECT rectB)
{
	return PLEX_insideRect(rectA.origin, rectB) && PLEX_insideRect(PLEX_convPoint(rectA.origin.x + rectA.dimens.w, rectA.origin.y), rectB) && PLEX_insideRect(PLEX_convPoint(rectA.origin.x + rectA.dimens.w, rectA.origin.y + rectA.dimens.h), rectB) && PLEX_insideRect(PLEX_convPoint(rectA.origin.x, rectA.origin.y + rectA.dimens.h), rectB);
}

uint8_t PLEX_rectCollision(const PLEX_RECT rect, const PLEX_RECT rect2, const PLEX_MPREC moveX, const PLEX_MPREC moveY)
{
	PLEX_RECT newRect = PLEX_convRect(PLEX_convPoint(rect.origin.x + moveX, rect.origin.y + moveY), rect.dimens);

	if(newRect.origin.x >= rect2.origin.x + rect2.dimens.w) return 0;
	if(newRect.origin.y >= rect2.origin.y + rect2.dimens.h) return 0;
	if(newRect.origin.x + newRect.dimens.w <= rect2.origin.x) return 0;
	if(newRect.origin.y + newRect.dimens.h <= rect2.origin.y) return 0;

	if(moveY > 0) return 1;
	if(moveX < 0) return 2;
	if(moveY < 0) return 3;
	if(moveX > 0) return 4;

	return 5;
}

uint8_t PLEX_rectCollisionNoMove(const PLEX_RECT rect, const PLEX_RECT rect2)
{
	return PLEX_rectCollision(rect, rect2, 0, 0);
}

// EXPERIMENTAL/UNTESTED//

bool PLEX_pointBelowLine(const PLEX_POINT point, const PLEX_LINE line)
{
	const uint8_t blankSpots[4] = { 1, 3, 0, 2 };
	const uint8_t upSpots[4] = { 0, 1, 2, 3 };
	const uint8_t downSpots[4] = { 3, 2, 1, 0 };

	PLEX_LINE colline;
	PLEX_LINE adaptedLine;

	PLEX_POINT halfPoint = PLEX_halfPoint(line);
	//PLEX_POINT endPoint = PLEX_endPoint(line);

	uint8_t quadrant = 0;
	uint8_t quadrant2 = 0;

	if(!line.run)
	{
		if(point.y < line.origin.y || point.y > line.origin.y + line.length) return false;

		if(line.leny < 0) return point.x >= line.origin.x;

		return point.x <= line.origin.x;
	}

	adaptedLine = line;

	// only bothers with what it needs
	colline.origin = halfPoint;
	colline.slope = PLEX_slope(halfPoint, point, &(colline.rise), &(colline.run));

	if(!colline.run)
	{
		halfPoint.x += 0.001;
		colline.origin = halfPoint;
		colline.slope = PLEX_slope(halfPoint, point, &(colline.rise), &(colline.run));
	}

	// quadrant order = 0 - NW, 1 - NE, 2 - SW, 3 - SE

	// DECIDES WHICH SIDE IT'S FACING
	quadrant = (point.x >= halfPoint.x);
	quadrant += (point.y >= halfPoint.y) * 2;

	// DECIDES WHICH SIDE IS UP
	quadrant2 = (adaptedLine.origin.x >= halfPoint.x);
	quadrant2 += (adaptedLine.origin.y >= halfPoint.y) * 2;

	if(quadrant == blankSpots[quadrant2]) return false;
	if(quadrant == upSpots[quadrant2]) return adaptedLine.slope >= colline.slope;
	if(quadrant == downSpots[quadrant2]) return adaptedLine.slope <= colline.slope;

	return true;
}

PLEX_POLYGON PLEX_convRectToPoly(const PLEX_RECT rect)
{
	PLEX_POLYGON ret;

	ret.points[0] = rect.origin;
	ret.points[1] = PLEX_convPoint(rect.origin.x + rect.dimens.w, rect.origin.y);
	ret.points[2] = PLEX_convPoint(rect.origin.x + rect.dimens.w, rect.origin.y + rect.dimens.h);
	ret.points[3] = PLEX_convPoint(rect.origin.x, rect.origin.y + rect.dimens.h);

	ret.pointCount = 4;

	return ret;
}

// EXPERIMENTAL/UNTESTED//

uint8_t PLEX_pointToPolygonCollisionInt(const PLEX_POINT point, const PLEX_POLYGON polygon, const PLEX_MPREC moveX, const PLEX_MPREC moveY, const size_t errorline, const char* const errorfile)
{
	PLEX_POINT newPoint = point;

	if(polygon.pointCount < 3)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_MATH, PLEX_ERROR_UNDERLIMIT, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_MATH_ONPOINTTOPOLYGONCOLLISION, PLEX_ERRORMESS_MATH_POLYGONPOINTS, errorline, errorfile);
		return 0;
	}

	newPoint.x += moveX;
	newPoint.y += moveY;

	for(size_t ze = 0; ze < polygon.pointCount; ++ze)
	{
		const PLEX_POINT a = polygon.points[ze];
		const PLEX_POINT b = ze != polygon.pointCount - 1 ? polygon.points[ze + 1] : polygon.points[0];
		const PLEX_LINE line = PLEX_convLine(a, b);

		if(!PLEX_pointBelowLine(newPoint, line)) return ze;
	}

	return 0;
}

// EXPERIMENTAL/UNTESTED//

uint8_t PLEX_polygonToPolygonCollisionInt(const PLEX_POLYGON a, const PLEX_POLYGON b, const PLEX_MPREC moveX, const PLEX_MPREC moveY, const size_t errorline, const char* const errorfile)
{
	if(a.pointCount < 3)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_MATH, PLEX_ERROR_UNDERLIMIT, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_MATH_ONPOLYGONTOPOLYGONCOLLISION, PLEX_ERRORMESS_MATH_POLYGONPOINTS, errorline, errorfile);
		return 0;
	}

	if(b.pointCount < 3)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_MATH, PLEX_ERROR_UNDERLIMIT, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_MATH_ONPOLYGONTOPOLYGONCOLLISION, PLEX_ERRORMESS_MATH_POLYGONPOINTS2, errorline, errorfile);
		return 0;
	}

	for(size_t ze = 0; ze < a.pointCount; ++ze)
	{
		const uint8_t collision = PLEX_pointToPolygonCollision(a.points[ze], b, moveX, moveY);

		if(collision) return collision;
	}

	return 0;
}

// EXPERIMENTAL/UNTESTED//

uint8_t PLEX_pointToPolygonCollisionNoMoveInt(const PLEX_POINT point, const PLEX_POLYGON polygon, const size_t errorline, const char* const errorfile){ return PLEX_pointToPolygonCollisionInt(point, polygon, 0, 0, errorline, errorfile); }

// EXPERIMENTAL/UNTESTED//

uint8_t PLEX_polygonToPolygonCollisionNoMoveInt(const PLEX_POLYGON a, const PLEX_POLYGON b, const size_t errorline, const char* const errorfile){ return PLEX_polygonToPolygonCollisionInt(a, b, 0, 0, errorline, errorfile); }

PLEX_MPREC PLEX_circlePerc(const PLEX_MPREC perc)
{
	if(perc > 1 || perc < -1) return p_fullRad;
	if(perc < 0) return (1 + perc) * p_fullRad;

	return perc * p_fullRad;
}

// start, update, end functions ---------------------------------------------------------------------------------------------

void PLEX_startMath()
{
	for(size_t ze = 0; ze < PLEX_STANDNUM_SQRTTABLE; ++ze) p_sqrtable[ze] = sqrt(ze);
}

// getters ------------------------------------------------------------------------------------------------------------------

PLEX_MPREC PLEX_revDiagonalMoveAmount(){ return p_revDiagonalMoveAmount; }
PLEX_MPREC PLEX_diagonalMoveAmount(){ return p_diagonalMoveAmount; }

PLEX_MPREC PLEX_eighthCircleRads(){ return p_eighthCircleRads; }
PLEX_MPREC PLEX_quarterCircleRads(){ return p_quarterCircleRads; }
PLEX_MPREC PLEX_halfCircleRads(){ return p_halfCircleRads; }
PLEX_MPREC PLEX_threeQuarterCircleRads(){ return p_threeQuarterCircleRads; }
PLEX_MPREC PLEX_circleRads(){ return p_circleRads; }
