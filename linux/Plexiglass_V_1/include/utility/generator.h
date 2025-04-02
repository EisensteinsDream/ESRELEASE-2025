#ifndef PLEX_GENERATOR_H
#define PLEX_GENERATOR_H

#include "utility/math.h"

#include "mem/expandarray.h"

// This unit creates 'generators' which are essentially a means to generate a number of x/y coordinates over a period of time. This serves multiple functions within various PLEX-based projects. It can also be used for very basic particle generators but I haven't fully tested it for that.

// NOTE: This is an independent unit. Not a unit with an accompanying state machine. It has no 'start, update, or end' functions that need to be called to operate.

// macro functions and macros -----------------------------------------------------------------------------------------------

// ARGUMENTS: (const double minX, const double maxX, const double minY, const double maxY, const double minEndX, const double maxEndX, const double minEndY, const double maxEndY, const uint64_t duration, const uint64_t minWait, const uint64_t maxWait, const uint64_t minGenDuration, const uint64_t maxGenDuration, const bool recycle) - returns PLEX_GENERATOR*

#define PLEX_genGenerator(minX, maxX, minY, maxY, minEndX, maxEndX, minEndY, maxEndY, duration, minWait, maxWait, minGenDuration, maxGenDuration, recycle) PLEX_genGeneratorInt(minX, maxX, minY, maxY, minEndX, maxEndX, minEndY, maxEndY, duration, minWait, maxWait, minGenDuration, maxGenDuration, recycle, __LINE__, __FILE__);

// ARGUMENTS: (PLEX_GENERATOR** generator)

#define PLEX_destroyGenerator(generator) PLEX_destroyGeneratorInt(generator, __LINE__, __FILE__)

// ARGUMENTS: (PLEX_GENERATOR* generator, const uint64_t time)

#define PLEX_startGenerator(generator, time) PLEX_startGeneratorInt(generator, time,  __LINE__, __FILE__)

// ARGUMENTS: (PLEX_GENERATOR* generator, const uint64_t time)

#define PLEX_updateGenerator(generator, time) PLEX_updateGeneratorInt(generator, time, __LINE__, __FILE__)

// ARGUMENTS: (const double minX, const double maxX, const double minY, const double maxY, const double minEndX, const double maxEndX, const double minEndY, const double maxEndY, PLEX_GENERATOR* generator)

#define PLEX_changeGeneratorArea(minX, maxX, minY, maxY, minEndX, maxEndX, minEndY, maxEndY, generator)  PLEX_changeGeneratorAreaInt(minX, maxX, minY, maxY, minEndX, maxEndX, minEndY, maxEndY, generator, __LINE__, __FILE__)

// ARGUMENTS: (const uint64_t by, PLEX_GENERATOR* generator)

#define PLEX_extendGeneratorDuration(by, generator) PLEX_extendGeneratorDurationInt(by, generator, __LINE__, __FILE__)

// ARGUMENTS: (const size_t index, const uint64_t time, double* x, double* y, PLEX_GENERATOR* generator) - returns bool

#define PLEX_pullGenerated(index, time, x, y, generator) PLEX_pullGeneratedInt(index, time, x, y, generator, __LINE__, __FILE__)

// ARGUMENTS: (double* minX, double* maxX, double* minY, double* maxY, double* minEndX, double* maxEndX, double* minEndY, double* maxEndY, PLEX_GENERATOR* generator)

#define PLEX_getGeneratorArea(minX, maxX, minY, maxY, minEndX, maxEndX, minEndY, maxEndY, generator) PLEX_getGeneratorAreaInt(minX, maxX, minY, maxY, minEndX, maxEndX, minEndY, maxEndY, generator, __LINE__, __FILE__)

// ARGUMENTS: (const PLEX_GENERATOR generator) - returns size_t

#define PLEX_generatedCount(generator) PLEX_generatedCountInt(generator, __LINE__, __FILE__)

// ARGUMENTS: (const PLEX_GENERATOR generator, const uint64_t time) - returns bool

#define PLEX_generationFinished(generator, time) PLEX_generationFinishedInt(generator, time, __LINE__, __FILE__)

// structs, unions, enums, function prototypes ------------------------------------------------------------------------------

typedef struct
{
	double startX, startY, endX, endY;
	uint64_t phaseStart, phaseLen;
} PLEX_GENERATED;

typedef struct
{
	double minX, maxX, minY, maxY, minEndX, maxEndX, minEndY, maxEndY;
	uint64_t start, duration, minWait, maxWait, wait, minGenDuration, maxGenDuration;

	bool recycle;

	PLEX_EXPANDARRAY* generated;
} PLEX_GENERATOR;

// public functions ---------------------------------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C"
{
#endif

// specialized functions ----------------------------------------------------------------------------------------------------

	// creates a 'generator' struct. Contains a range for x and y. Contains the duration which chooses how long the generator will continue generating. A minimum and maximum wait time before generation starts. The minimum and maximum amount of time between coordinate generation. If 'recycle' is true then the generator resets itself. All times in microseconds.

	extern PLEX_GENERATOR* PLEX_genGeneratorInt(const double minX, const double maxX, const double minY, const double maxY, const double minEndX, const double maxEndX, const double minEndY, const double maxEndY, const uint64_t duration, const uint64_t minWait, const uint64_t maxWait, const uint64_t minGenDuration, const uint64_t maxGenDuration, const bool recycle, const size_t errorline, const char* const errorfile);

	// destroys generator and clears out all allocated data

	extern void PLEX_destroyGeneratorInt(PLEX_GENERATOR** generator, const size_t errorline, const char* const errorfile);

	// starts the generator at the marked time.

	extern void PLEX_startGeneratorInt(PLEX_GENERATOR* generator, const uint64_t time, const size_t errorline, const char* const errorfile);

	// updates the generator at the marked time.

	extern void PLEX_updateGeneratorInt(PLEX_GENERATOR* generator, const uint64_t time, const size_t errorline, const char* const errorfile);

// setters ------------------------------------------------------------------------------------------------------------------

	// changes the generator's generation area

	extern void PLEX_changeGeneratorAreaInt(const double minX, const double maxX, const double minY, const double maxY, const double minEndX, const double maxEndX, const double minEndY, const double maxEndY, PLEX_GENERATOR* generator, const size_t errorline, const char* const errorfile);

	// extends the duration time of the generator by 'by' microseconds

	extern void PLEX_extendGeneratorDurationInt(const uint64_t by, PLEX_GENERATOR* generator, const size_t errorline, const char* const errorfile);

// getters ------------------------------------------------------------------------------------------------------------------

	// pulls the last x/y from the generator. Returns 'false' if the generation is not ready to pull yet. Also checks by 'index' which should be externally incremented if utilized in a loop.

	extern bool PLEX_pullGeneratedInt(const size_t index, const uint64_t time, double* x, double* y, PLEX_GENERATOR* generator, const size_t errorline, const char* const errorfile);

	// acquires the generator's generation area

	extern void PLEX_getGeneratorAreaInt(double* minX, double* maxX, double* minY, double* maxY, double* minEndX, double* maxEndX, double* minEndY, double* maxEndY, PLEX_GENERATOR* generator, const size_t errorline, const char* const errorfile);

	// returns the number of coordinates generated

	extern size_t PLEX_generatedCountInt(const PLEX_GENERATOR generator, const size_t errorline, const char* const errorfile);

	// returns whether or not the generator is finished

	extern bool PLEX_generationFinishedInt(const PLEX_GENERATOR generator, const uint64_t time, const size_t errorline, const char* const errorfile);
#ifdef __cplusplus
}
#endif

#endif
