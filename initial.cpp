//Implementation for Initializer

//Dependencied ==> urandom.h for seedby_urandom()
//			   ==> Global.cpp for checkBoxSize()


#include<random>
#include<iostream>
#include "urandom.h" //seedby_urandom
#include <cstdlib> //using rand
#include <ctime> //using time
//#include<log.h> //Log errors
using namespace std;


extern volatile Box::checkBoxSize();
void initializerP(&double, &double, &double);
void initializerO(&double, &double, &double, &double);



void initializerP(&double x, &double y, &double z)
{
	double BoxSize = Box::checkBoxSize();
	ranlux48 rlx; // ranlux48_base rlx; //Creating object for RANLUX random number generator
	uniform_real_distribution<double> drandom(0.0, BoxSize);

	Urandom urandom;//Object for Urandom class
	int sx = urandom.seedby_urandom(); //Seeding
	rlx.seed(sx);
	std::srand(std::time(nullptr)); // use current time as seed for random generator

	x = drandom(rlx);
	int sy = sx+std::rand();
	rlx.seed(sy);
	y = drandom(rlx);

	int sz = sx+std::rand();
	rlx.seed(sz);
	z = drandom(rlx);

	/*//Periodic Boundary condition
	if (x > BoxSize) { x = (x - BoxSize) }
	if (y > BoxSize) { y = (y - BoxSize) }
	if (z > BoxSize) { x = (z - BoxSize) }
*/



}


void initializerO(&double a, &double b, &double c, &double d)
{
	///
}