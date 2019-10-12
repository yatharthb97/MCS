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

void Updator3(V &temp);
/*void Updator4(Q &temp);*/

void Updator3(V &temp){
	RunParam up;

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
		
		double check = up.checkStepSize();
		if(up.MaxStep) //Output Max Step Size
		{
			temp.x = x*check;
			temp.y = y*check;
			temp.z = z*check;
		}

		else if(up.MaxStep == false) //Output Dynamic Step Sizes
		{
			double lcheck = up.checkMinStepSize();
			ranlux48 rlx2; // ranlux48_base rlx; //Creating object for RANLUX random number generator
			uniform_real_distribution<double> erandom(lcheck, check);

			int st = sx+std::rand();
			rlx2.seed(st);

		temp.x = x*erandom(rlx2);
		temp.y = y*erandom(rlx2);
		temp.z = z*erandom(rlx2);
		//cout<<temp.info()<<endl;
		}

}


/*
void Updator4(Q &temp){
	RunParam up;
	ranlux48 rlx; // ranlux48_base rlx; //Creating object for RANLUX random number generator
	uniform_real_distribution<double> drandom;

	Urandom urandom; //Object for Urandom class
	int sx = urandom.seedby_urandom(); //Seeding
	rlx.seed(sx);
	std::srand(std::time(nullptr)); // use current time as seed for random generator

	double d = drandom(rlx);
	int i = int(d*3);
	int x = 0;
	switch(i){
		case 0: {x = 0; break;}
		case 1: {x = 1; break;}
		case 2: {x = -1; break;}
		default: {x = 0; Log updator3;
						updator.logerror("updator.cpp",  "Random number generator overflow. 'default' invoked.");
						 break;}
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
		default: {x = 0; Log updator3;
						updator.logerror("updator.cpp",  "Random number generator overflow. 'default' invoked.");
						 break;}
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
		default: {x = 0; Log updator3;
						updator.logerror("updator.cpp",  "Random number generator overflow. 'default' invoked.");
						 break;}
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
		default: {x = 0; Log updator3;
						updator.logerror("updator.cpp",  "Random number generator overflow. 'default' invoked.");
						 break;}
	}
	
	double check = up.checkStepSize();
	Q temp;
	temp.a = x*check;
	temp.b = y*check;
	temp.c = z*check;
	temp.d = w*check;
}*/