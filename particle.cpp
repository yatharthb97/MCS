//Function Definations
//Comments complete
	
	#include <iostream>
	#include "particle.h"
	#include "particle_energy_calc.h"
	#include "RenderingEngine.h"
	#include "log.h"
	#include "random.h"
	using namespace std;

	//Constructor - only energy 	//1
	particle::particle()
	{
		c_energy=0.00;
	}


	//Destructor	 //2
	particle::~particle() {}

	//Overloading Initializer 	//3
	particle::particle(double &position[], double &orientation[])
		//Calls initializer and sets up the initial environment
		//@param - &position[], &orientation[]

	{
		random::initializerP(); //Notdefined - class random
		random::initializerO();	//Notdefined - class random
		c_position[] = &position[];
		c_orientation[] = &orientation[];
		//Returns 6 values of randomly generated coordinates
		double render::createxyz(c_position); //Not defined
			//Creates a trajectory file of the initial setup
	}

	//Translaton Updator - Mutator 		//4
	void particle::translator(double &translate[], double &c_position[])
		//double particle::translator -Updates the position of the particle
		//double particle::translator -Contains rejection condition
		//@param - &translate[], &c_position[]
		if((c_position[0]+=c_translate[0] && c_position[1]+=c_translate[1] && < c_position[2]+=c_translate[2] &&) < EDGE &&)
		//if(for(i = 0 && 1 && 2):(c_position[0]+=c_translate[0]) < EDGE)
		{
			for(int i = 0; i<3; i++)
			{
				c_position[i]+=translate[i];
			}
		else
			{
				log::createlogerr("Tranlation move out of bounds!");  //Not defined and also class not defined
			}
		}

	//Orientation Updator - Mutator 	//5
	void particle::orienter(double &orient[], double &c_orientation[])
	{
		//Updates the angular orientation of the particle
		//@param - &orient[], &c_orientation[] 
		for(int i = 0; i<3; i++)
		{
			c_orientation[i]+=orient[i];
		}
	}

	//Energy Updator - Mutator 		//6
	void particle::energiser(double &c_energy, double &c_position[])
	{
		//Updates the energy of the particle
		//@param - &c_energy, &c_position
		c_energy = energycalc::positionalenergy(c_position); //Not defined
	}
	
	//getPosition - Accessor 	//7
	double particle::getPosition(&c_position[]) const
	{
		//Returns the position array of the particle
		//@param - &c_position[]
		//@returns - c_position[]
		return(c_position);
	
	}

	//printPosition - Accessor 	//8
	void particle::printPosition(&c_position[]) const
	{
		//Prints the position array of the particle And ends line
		//@param - &c_position[]
		for(int i=0; i<3; i++)
		{
			cout<<c_position[i]<<"\t";
		}
		cout<<endl;
	}
	
	//getOrientation - Accessor 	//9
	double particle::getOrientation(&c_orientation[]) const
	{
		//Returns the orientation of the particle
		//@param - c_orientation
		//@return - c_orientation[]
		return(c_orientation);
	
	}

	//printOrientation - Accessor 	//10
	void particle::printOrientation(&c_orientation[]) const
	{
		//Prints the orientation of the particle And ends line
		//@param - &c_orientation
		for(int i=0; i<3; i++)
		{
			cout<<c_orientation[i]<<"\t";
		}
		cout<<endl;
	}

	//getEnergy - Accessor 	//11
	double particle::getEnergy(&c_energy[]) const
	{
		//Returns the Energy of the particle And ends line
		//@return double c_energy
		return(c_energy);
	}