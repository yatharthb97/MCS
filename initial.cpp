//Implementation for Initializer

//Dependencied ==> urandom.h for seedby_urandom()
//


#include<random>
#include<iostream>
#include "urandom.h" //seedby_urandom
#include"runparam.h"
#include"Vector.h"
//#include <cstdlib> //using rand
//#include <ctime> //using time
//#include<cmath>
//#include<log.h> //Log errors
using namespace std;

#define PI 3.14159

extern volatile double checkBoxSize();
void initializerP(V &v);
void initializerO(V &v);



void initializerP(V &v)
{
	RunParam r;
	double BoxSize = r.checkBoxSize();
		//**double BoxSize = Box::checkBoxSize();
		ranlux48 rlx; // ranlux48_base rlx; //Creating object for RANLUX random number generator
		Urandom urandom;//Object for Urandom class
		int sx = urandom.seedby_urandom(); //Seeding
		rlx.seed(sx);
		//Uniform
		//uniform_real_distribution<double> drandom(0, BoxSize);
		//Gaussian
		normal_distribution<double> drandom(2.5, BoxSize/5); //StdDev = Range/5
		//std::srand(std::time(nullptr)); // use current time as seed for random generator

		v.x = abs(drandom(rlx));
		//x = drandom(rlx);

		//int sy = sx+std::rand();
		//rlx.seed(sy);
		v.y = abs(drandom(rlx));
		//y = drandom(rlx);
	 
		//int sz = sx+std::rand();
		//rlx.seed(sz);
		v.z = abs(drandom(rlx));
		//z = drandom(rlx);

		//Periodic Boundary condition
		/*if (x > BoxSize) { x = (x - BoxSize); }
		if (y > BoxSize) { y = (y - BoxSize); }
		if (z > BoxSize) { x = (z - BoxSize); }
		if (x < 0) { x = (x + BoxSize); }
		if (y < 0) { y = (y + BoxSize); }
		if (z < 0) { x = (z + BoxSize); }*/

		//Overlap Conditions
		/*double tempenergy =  LjLoop(&partlist);
		double tempoldenegy = Box::getEnergy();
		double ratio = tempoldenegy/tempenergy;
		if(ratio<0.001) {initializerP(&double x, &double y, double z)} //Recursive step*/
}


void initializerO(V &v)
{
	RunParam inio;

	ranlux48 rlx; // ranlux48_base rlx; //Creating object for RANLUX random number generator
		Urandom urandom;//Object for Urandom class
		int sx = urandom.seedby_urandom(); //Seeding
		rlx.seed(sx);
		//Uniform
		uniform_real_distribution<double> drandom;
		//Gaussian
		//normal_distribution<double> drandom(2.5, BoxSize/5); //StdDev = Range/5
		//std::srand(std::time(nullptr)); // use current time as seed for random generator

		v.x = drandom(rlx);

		//int sy = sx+std::rand();
		//rlx.seed(sy);
		v.y = drandom(rlx);
	 
		//int sz = sx+std::rand();
		//rlx.seed(sz);
		v.z = drandom(rlx);

		while(!v.isUnit())
		{
			v.normalise();
		}
}