//Header file for a basic random number generator - seeded by random_device
#include "urandom.h"
#include<random>

int Rndm(int lower, int upper)
{
	std::random_device s;
	std::mt19937 g(s());
	std::uniform_int_distribution<int> d(lower, upper);
	return d(g);
}


double Rndm(double lower, double upper)
{
	std::random_device s;
	std::mt19937 g(s());
	std::uniform_real_distribution<double> d(lower, upper);
	return d(g);
}

//roll returns a number between 1 and 1000
int roll()
{
	std::random_device s;
	std::mt19937 g(s());
	std::uniform_int_distribution<int> d(1, 1000);
	return d(g);	
}
