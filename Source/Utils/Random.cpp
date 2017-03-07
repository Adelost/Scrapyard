#include "Random.h"

#include "StaticInit.h"

#include <stdlib.h> // srand
#include <time.h> // time

namespace ae
{
// Init constructor automatically
STATIC_INIT(Random::initSeed();)

void Random::initSeed()
{
	srand((unsigned int)time(nullptr));
}

void Random::setSeed(int seed)
{
	srand((unsigned int)seed);
}

int Random::nextUniform(int min, int max)
{
	return rand() % (max - min + 1) + min;
}

int Random::next(int max)
{
	return rand() % max;
}

float Random::nextFloat()
{
	return nextFloat(0.0f, 1.0f);
}

float Random::nextFloat(float min, float max)
{
	float random = ((float)rand()) / (float)RAND_MAX;
	float range  = (max - min);
	random = random * range ;

	return min + random;
}

bool Random::nextBool()
{
	return next(1) == 0;
}

}