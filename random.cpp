//Header file for a basic random number generator - seeded by random_device
//#pragma once
#include "urandom.h"
#include<random>

int Rndm(int lower, int upper)
{
	std::random_device s;
	std::mt19937 g(s());
	std::uniform_int_distribution<int> d(lower, upper);
	return d(g);
}