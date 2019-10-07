//Main program

//Preprocessors
#include<iostream>
using namespace std;
#include "box.h"
#include "runparam.h"
#include "log.h"

int main()
{
	cout<<"Welocme Message!"<<endl;
	

//Running Parameters - Initialization

//Create Box
Log boxdes;
	boxdes.logoutput("main.cpp", "Creating Box!", true);
Box b(10,5);
	boxdes.logoutput("main.cpp", "Destroying Box!", true);

	/*//Create container with the desired number of particles - Take 200, Size 5 units
	Box b(200,5, 20);//Particles, size, energy

	//Implement Metropolis sequence*/


	
}



/*Metropolis
{
	//Select particle at random from the container
	//Give trial new position
	//Give trial orientation
	//Calculate the energy - LJ loop
	//Acceptance conditions - Probablity distibution
	//Accept trial move - b.partlist[i].translate();

}*/