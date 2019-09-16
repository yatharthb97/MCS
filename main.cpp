//Main program

//Preprocessors
#include<iostream>
using namespace std;
#include "particle.h"


int main()
{
	cout<<"Welocme Message!";
	Particle p1;
	Particle p2;
	cout<<p1.getPosition().info()<<endl;
	cout<<p2.getPosition().info()<<endl;







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