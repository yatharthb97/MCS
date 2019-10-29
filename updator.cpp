//Implementation of Updator mechanism - Random Walker Static Step Size

//Dependencies ==> urandom.h for seedby_urandom()
//			   ==> log.h for logerror()
//			   ==> global.cpp for checkStepSize()

//Status - Not tested
//@Author - yatharthb97

//--------------------------

//Preprocessors
#include<iostream>
#include "urandom.h" //seedby_urandom
#include <cstdlib> //using rand
#include <ctime> //using time
#include"log.h" //Log errors
#include "Vector.h"
#include"runparam.h"
#include<random>
using namespace std;

void UpdatorP(Particle &p);
void Updator4(Particle &p);

void UpdatorP(Particle &p)
{

		ranlux48 rlx; // ranlux48_base rlx; //Creating object for RANLUX random number generator
		uniform_real_distribution<double> drandom;

		Urandom urandom;//Object for Urandom class
		int sx = urandom.seedby_urandom(); //Seeding
		rlx.seed(sx);
		//std::srand(std::time(nullptr)); // use current time as seed for random generator

		double d = drandom(rlx);
		int i = int(d*3);
		int x = 0;
		switch(i){
			case 0: {x = 0; break;}
			case 1: {x = 1; break;}
			case 2: {x = -1; break;}
			default: {x = 0; Log updator;
							updator.logerror("updator.cpp",  "Random number generator overflow. 'default' invoked.");
							 break;}
		}
		
		//int sy = sx+std::rand();
		//rlx.seed(sy);

		d = drandom(rlx);
		i = int(d*3);
		int y = 0;
		switch(i){
			case 0: {y = 0; break;}
			case 1: {y = 1; break;}
			case 2: {y = -1; break;}
			default: {x = 0; Log updator;
							updator.logerror("updator.cpp",  "Random number generator overflow. 'default' invoked.");
							 break;}
		}
		
		//int sz = sy+std::rand();
		//rlx.seed(sz);

		d = drandom(rlx);
		i = int(d*3);
		int z = 0;
		switch(i){
			case 0: {z = 0; break;}
			case 1: {z = 1; break;}
			case 2: {z = -1; break;}
			default: {x = 0; Log updator;
							updator.logerror("updator.cpp",  "Random number generator overflow. 'default' invoked.");
							 break;}
		}
		
		double check = RunParam::MaxStep;
		if(RunParam::MaxStep) //Output Max Step Size
		{
			p.translate(V(x*RunParam::MaxStep, y*RunParam::MaxStep, z*RunParam::MaxStep));
		}

		else if(RunParam::MaxStep == false) //Output Dynamic Step Sizes
		{
			ranlux48 rlx2; // ranlux48_base rlx; //Creating object for RANLUX random number generator
			uniform_real_distribution<double> erandom(RunParam::MinStepSize, RunParam::MinStepSize);

			int st = sx+std::rand();
			rlx2.seed(st);

			p.translate(V(x*erandom(rlx2), y*erandom(rlx2), z*erandom(rlx2)));

		//cout<<temp.info()<<endl;
		}

}


void UpdatorO(Particle &p)
{
	
	V temp; temp.rndUnit();
	extern double Rndm(double, double);

	if(MaxRot)
	{
		p.patch.rotate(temp, maxRotor);
	}

	else
	{
		double angle = Rndm(minRotor, maxRotor);
		p.patch.rotate(temp, angle);
	}

}