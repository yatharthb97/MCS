
#include<random>
#include<iostream>
#include "urandom.h" //seedby_urandom
#include <cstdlib> //using rand
#include <ctime> //using time
using namespace std;

int Updator(int[3]);
int Updator(int[4]);
extern int seedby_urandom();
extern volatile double checkStepSize();

int Updator(int array[3]){
	ranlux48 rlx; // ranlux48_base rlx; //Creating object for RANLUX random number generator
	uniform_real_distribution<double> drandom;

	int sx = seedby_urandom(); //Seeding
	rlx.seed(sx);
	std::srand(std::time(nullptr)); // use current time as seed for random generator

	double d = drandom(rlx);
	int i = int(d*3);
	int x = 0;
	switch(i){
		case 0: {x = 0; break;}
		case 1: {x = 1; break;}
		case 2: {x = -1; break;}
		default: {x = 0; std::cout<<"error"; break;}
	}
	int sy = sx+std::rand();
	rlx.seed(sy);

	d = drandom(rlx);
	i = int(d*3);
	int y = 0;
	switch(i){
		case 0: {y = 0; break;}
		case 1: {y = 1; break;}
		case 2: {y = -1; break;}
		default: {y = 0; std::cout<<"error"; break;}
	}

	int sz = sy+std::rand();
	rlx.seed(sz);

	d = drandom(rlx);
	i = int(d*3);
	int z = 0;
	switch(i){
		case 0: {z = 0; break;}
		case 1: {z = 1; break;}
		case 2: {z = -1; break;}
		default: {z = 0; std::cout<<"error"; break;}
	}
	
	array[0] = x*checkStepSize();
	array[1] = y*checkStepSize();
	array[2] = z*checkStepSize();
}

//Overloaded
int Updator(int array[4]){
	ranlux48 rlx; // ranlux48_base rlx; //Creating object for RANLUX random number generator
	uniform_real_distribution<double> drandom;

	int sx = seedby_urandom(); //Seeding
	rlx.seed(sx);
	std::srand(std::time(nullptr)); // use current time as seed for random generator

	double d = drandom(rlx);
	int i = int(d*3);
	int x = 0;
	switch(i){
		case 0: {x = 0; break;}
		case 1: {x = 1; break;}
		case 2: {x = -1; break;}
		default: {x = 0; std::cout<<"error"; break;}
	}
	int sy = sx+std::rand();
	rlx.seed(sy);

	d = drandom(rlx);
	i = int(d*3);
	int y = 0;
	switch(i){
		case 0: {y = 0; break;}
		case 1: {y = 1; break;}
		case 2: {y = -1; break;}
		default: {y = 0; std::cout<<"error"; break;}
	}

	int sz = sy+std::rand();
	rlx.seed(sz);

	d = drandom(rlx);
	i = int(d*3);
	int z = 0;
	switch(i){
		case 0: {z = 0; break;}
		case 1: {z = 1; break;}
		case 2: {z = -1; break;}
		default: {z = 0; std::cout<<"error"; break;}
	}
	
	int sw = sz+std::rand();
	rlx.seed(sw);

	d = drandom(rlx);
	i = int(d*3);
	int w = 0;
	switch(i){
		case 0: {w = 0; break;}
		case 1: {w = 1; break;}
		case 2: {w = -1; break;}
		default: {w = 0; std::cout<<"error"; break;}
	}
	
	array[0] = x*checkStepSize();
	array[1] = y*checkStepSize();
	array[2] = z*checkStepSize();
	array[3] = w*checkStepSize();
}