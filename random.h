//Header file for a basic random number generator - seeded by random_device
#include "urandom.h"
#include<random>

int Random(int lower, int upper)
{
	std::random_device s;
	mt19937 g(s());
	uniform_int_distribution<int> d(lower, upper);
	return d(g);
}