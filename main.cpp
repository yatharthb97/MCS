//Main program

//Preprocessors
#include<iostream>
using namespace std;
#include "box.h"
#include "runparam.h"

int main()
{
	cout<<"Welocme Message!";
	Box b;
	

//Running Parameters - Initialization
{
RunParam::RUN = true;
RunParam::StepSize = 0.1;
RunParam::LJARatio = 20;
RunParam::BoxSize = 5;
RunParam::MaxStep = true;
RunPAram::LogOutput = "log.txt";
RunParam::LogErrorOut = "error.txt";
}





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