#include "utility/generator.h"

// NOTE: function descriptions in header.

// ---------------------------- //
// PUBLIC FUNCTIONS:
// ---------------------------- //

// specialized functions ----------------------------------------------------------------------------------------------------

PLEX_GENERATOR* PLEX_genGeneratorInt(const double minX, const double maxX, const double minY, const double maxY, const double minEndX, const double maxEndX, const double minEndY, const double maxEndY, const uint64_t duration, const uint64_t minWait, const uint64_t maxWait, const uint64_t minGenDuration, const uint64_t maxGenDuration, const bool recycle, const size_t errorline, const char* const errorfile)
{
	PLEX_GENERATOR* ret = PLEX_allocInt(sizeof(PLEX_GENERATOR), errorline, errorfile);

	if(ret == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GENERATOR, PLEX_ERROR_ALLOCFAIL, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_GENERATOR_ONGEN, PLEX_ERRORMESS_GENERATOR_GENERATOR, errorline, errorfile);
		return NULL;
	}

	ret->minX = minX;
	ret->maxX = maxX;
	ret->minY = minY;
	ret->maxY = maxY;

	ret->minEndX = minEndX;
	ret->maxEndX = maxEndX;
	ret->minEndY = minEndY;
	ret->maxEndY = maxEndY;

	ret->duration = duration;
	ret->minWait = minWait;
	ret->maxWait = maxWait;
	ret->maxGenDuration = maxGenDuration;
	ret->minGenDuration = minGenDuration;

	ret->start = 0;
	ret->recycle = recycle;

	ret->generated = NULL;

	ret->wait = PLEX_randomNumberInt(minWait, maxWait, errorline, errorfile);

	return ret;
}

void PLEX_destroyGeneratorInt(PLEX_GENERATOR** generator, const size_t errorline, const char* const errorfile)
{
	PLEX_GENERATOR* generatorPtr = NULL;

	if(generator == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GENERATOR, PLEX_ERROR_FREENULLPTR, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GENERATOR_ONDESTROYING, PLEX_ERRORMESS_GENERATOR_GENERATOR, errorline, errorfile);
		return;
	}

	generatorPtr = *generator;

	if(generatorPtr == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GENERATOR, PLEX_ERROR_FREENULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GENERATOR_ONDESTROYING, PLEX_ERRORMESS_GENERATOR_GENERATOR, errorline, errorfile);
		return;
	}

	if(generatorPtr->generated != NULL) PLEX_destroyExpandArrayInt(&generatorPtr->generated, errorline, errorfile);

	PLEX_deallocInt((void**)generator, errorline, errorfile);
}

void PLEX_startGeneratorInt(PLEX_GENERATOR* generator, const uint64_t time, const size_t errorline, const char* const errorfile)
{
	if(generator == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GENERATOR, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GENERATOR_ONSTART, PLEX_ERRORMESS_GENERATOR_GENERATOR, errorline, errorfile);
		return;
	}

	generator->start = time;

	if(generator->generated != NULL) PLEX_destroyExpandArrayInt(&generator->generated, errorline, errorfile);

	generator->generated = PLEX_genExpandArrayInt(PLEX_getMemProfileGenStart(), sizeof(PLEX_GENERATED), errorline, errorfile);
}

void PLEX_updateGeneratorInt(PLEX_GENERATOR* generator, const uint64_t time, const size_t errorline, const char* const errorfile)
{
	uint64_t duration = 0;

	size_t genCount = 0;

	PLEX_GENERATED* generated = NULL;

	if(generator == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GENERATOR, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GENERATOR_ONUPDATE, PLEX_ERRORMESS_GENERATOR_GENERATOR, errorline, errorfile);
		return;
	}

	if(generator->generated == NULL)
	{
		// not neccesarily content corruption
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GENERATOR, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GENERATOR_ONUPDATE, PLEX_ERRORMESS_GENERATOR_GENERATED, errorline, errorfile);
		return;
	}

	duration = time - generator->start;

	if(duration < generator->wait) return;

	genCount = PLEX_expandArrayCountInt(generator->generated, errorline, errorfile);

	if(genCount)
	{
		generated = PLEX_getExpandArrayLastInt(generator->generated, errorline, errorfile);

		if(generated == NULL)
		{
			PLEX_errorInt(PLEX_ERROR_CATEGORY_GENERATOR, PLEX_ERROR_ACQUIRELAST, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_GENERATOR_ONUPDATE, PLEX_ERRORMESS_GENERATOR_GENERATED, errorline, errorfile);
			return;
		}
	}

	if(!genCount || (generated->phaseLen < duration && duration < generator->duration))
	{
		if(!PLEX_incrementExpandArrayInt(generator->generated, errorline, errorfile))
		{
			PLEX_errorInt(PLEX_ERROR_CATEGORY_GENERATOR, PLEX_ERROR_INCREMENT, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_GENERATOR_ONUPDATE, PLEX_ERRORMESS_GENERATOR_GENERATED, errorline, errorfile);
			return;
		}

		generated = PLEX_getExpandArrayLastInt(generator->generated, errorline, errorfile);

		if(generated == NULL)
		{
			PLEX_errorInt(PLEX_ERROR_CATEGORY_GENERATOR, PLEX_ERROR_ACQUIRELAST, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_GENERATOR_ONUPDATE, PLEX_ERRORMESS_GENERATOR_GENERATED, errorline, errorfile);
			return;
		}

		generated->startX = PLEX_randomNumberInt(generator->minX, generator->maxX, errorline, errorfile);
		generated->startY = PLEX_randomNumberInt(generator->minY, generator->maxY, errorline, errorfile);
		generated->endX = PLEX_randomNumberInt(generator->minEndX, generator->maxEndX, errorline, errorfile);
		generated->endY = PLEX_randomNumberInt(generator->minEndY, generator->maxEndY, errorline, errorfile);

		generated->phaseLen = duration + PLEX_randomNumberInt(generator->minGenDuration, generator->maxGenDuration, errorline, errorfile);
		generated->phaseStart = duration;
	}
}

// setters ------------------------------------------------------------------------------------------------------------------

void PLEX_changeGeneratorAreaInt(const double minX, const double maxX, const double minY, const double maxY, const double minEndX, const double maxEndX, const double minEndY, const double maxEndY, PLEX_GENERATOR* generator, const size_t errorline, const char* const errorfile)
{
	if(generator == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GENERATOR, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GENERATOR_ONCHANGEAREA, PLEX_ERRORMESS_GENERATOR_GENERATOR, errorline, errorfile);
		return;
	}

	generator->minX = minX;
	generator->maxX = maxX;
	generator->minY = minY;
	generator->maxY = maxY;

	generator->minEndX = minEndX;
	generator->maxEndX = maxEndX;
	generator->minEndY = minEndY;
	generator->maxEndY = maxEndY;
}

void PLEX_extendGeneratorDurationInt(const uint64_t by, PLEX_GENERATOR* generator, const size_t errorline, const char* const errorfile)
{
	if(generator == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GENERATOR, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GENERATOR_ONEXTENDINGDURATION, PLEX_ERRORMESS_GENERATOR_GENERATOR, errorline, errorfile);
		return;
	}

	generator->duration += by;
}

// getters ------------------------------------------------------------------------------------------------------------------

bool PLEX_pullGeneratedInt(const size_t index, const uint64_t time, double* x, double* y, PLEX_GENERATOR* generator, const size_t errorline, const char* const errorfile)
{
	PLEX_GENERATED* generated = NULL;

	uint64_t duration = 0;

	double perc = 0;

	size_t count = 0;

	if(x == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GENERATOR, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GENERATOR_ONPULL, PLEX_ERRORMESS_GENERATOR_XCOORDINATE, errorline, errorfile);
		return false;
	}

	*x = 0;

	if(y == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GENERATOR, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GENERATOR_ONPULL, PLEX_ERRORMESS_GENERATOR_YCOORDINATE, errorline, errorfile);
		return false;
	}

	*y = 0;

	if(generator == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GENERATOR, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GENERATOR_ONPULL, PLEX_ERRORMESS_GENERATOR_GENERATOR, errorline, errorfile);
		return false;
	}

	count = PLEX_expandArrayCountInt(generator->generated, errorline, errorfile);

	if(index >= count)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GENERATOR, PLEX_ERROR_OVERLIMIT, PLEX_ERROR_SEVERITY_MINOR, PLEX_ERRORMESS_GENERATOR_ONPULL, PLEX_ERRORMESS_GENERIC_INDEX, errorline, errorfile);
		return false;
	}

	duration = time - generator->start;

	generated = PLEX_getExpandArrayEntryInt(index, generator->generated, errorline, errorfile);

	if(generated == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GENERATOR, PLEX_ERROR_ACQUIRE, PLEX_ERROR_SEVERITY_FATAL, PLEX_ERRORMESS_GENERATOR_ONPULL, PLEX_ERRORMESS_GENERATOR_GENERATED, errorline, errorfile);
		return false;
	}

	perc = generated->phaseLen ? (duration - generated->phaseStart)/(double)generated->phaseLen : 0;

	if(perc > 1) perc = 1;

	*x = generated->startX + (perc * (generated->endX - generated->startX));
	*y = generated->startY + (perc * (generated->endY - generated->startY));

	if(generator->recycle && perc >= 1) generated->phaseStart = duration;

	return true;
}

void PLEX_getGeneratorAreaInt(double* minX, double* maxX, double* minY, double* maxY, double* minEndX, double* maxEndX, double* minEndY, double* maxEndY, PLEX_GENERATOR* generator, const size_t errorline, const char* const errorfile)
{
	if(minX == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GENERATOR, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GENERATOR_ONGETAREA, PLEX_ERRORMESS_GENERATOR_MINX, errorline, errorfile);
		return;
	}

	*minX = 0;

	if(maxX == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GENERATOR, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GENERATOR_ONGETAREA, PLEX_ERRORMESS_GENERATOR_MAXX, errorline, errorfile);
		return;
	}

	*maxX = 0;

	if(minY == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GENERATOR, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GENERATOR_ONGETAREA, PLEX_ERRORMESS_GENERATOR_MINY, errorline, errorfile);
		return;
	}

	*minY = 0;

	if(maxY == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GENERATOR, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GENERATOR_ONGETAREA, PLEX_ERRORMESS_GENERATOR_MAXY, errorline, errorfile);
		return;
	}

	*maxY = 0;

	if(minEndX == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GENERATOR, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GENERATOR_ONGETAREA, PLEX_ERRORMESS_GENERATOR_MINXEND, errorline, errorfile);
		return;
	}

	*minEndX = 0;

	if(maxEndX == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GENERATOR, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GENERATOR_ONGETAREA, PLEX_ERRORMESS_GENERATOR_MAXXEND, errorline, errorfile);
		return;
	}

	*maxEndX = 0;

	if(minEndY == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GENERATOR, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GENERATOR_ONGETAREA, PLEX_ERRORMESS_GENERATOR_MINYEND, errorline, errorfile);
		return;
	}

	*minEndY = 0;

	if(maxEndY == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GENERATOR, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GENERATOR_ONGETAREA, PLEX_ERRORMESS_GENERATOR_MAXYEND, errorline, errorfile);
		return;
	}

	*maxEndY = 0;

	if(generator == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GENERATOR, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GENERATOR_ONGETAREA, PLEX_ERRORMESS_GENERATOR_GENERATOR, errorline, errorfile);

		return;
	}

	*minX = generator->minX;
	*maxX = generator->maxX;

	*minY = generator->minY;
	*maxY = generator->maxY;

	*minEndX = generator->minEndX;
	*maxEndX = generator->maxEndX;

	*minEndY = generator->minEndY;
	*maxEndY = generator->maxEndY;
}

size_t PLEX_generatedCountInt(const PLEX_GENERATOR generator, const size_t errorline, const char* const errorfile)
{
	if(generator.generated == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GENERATOR, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GENERATOR_ONGETCOUNT, PLEX_ERRORMESS_GENERATOR_GENERATED, errorline, errorfile);
		return 0;
	}

	return PLEX_expandArrayCountInt(generator.generated, errorline, errorfile);
}

bool PLEX_generationFinishedInt(const PLEX_GENERATOR generator, const uint64_t time, const size_t errorline, const char* const errorfile)
{
	if(generator.generated == NULL)
	{
		PLEX_errorInt(PLEX_ERROR_CATEGORY_GENERATOR, PLEX_ERROR_ISNULL, PLEX_ERROR_SEVERITY_BADSTYLE, PLEX_ERRORMESS_GENERATOR_ONGETFINISHED, PLEX_ERRORMESS_GENERATOR_GENERATED, errorline, errorfile);
		return true; // < return true rather than false
	}

	return time - generator.start >= generator.duration;
}
