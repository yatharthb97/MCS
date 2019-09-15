//Header file for Particle class

//Periodic boundary conditions not implemented

#pragma once

#include "./Vector.h"


inline extern int checkBoxSize();

class Particle
{
public:

//Overloading Constructor
	//@brief - Calls initializer and sets up the initial environment
	//@param - partid ==> particle ID	
	Particle(int partid): energy(0.0000), c_energy(0.0000), partid(partid)
	{
		
		volatile double Box::checkBoxSize();
		double EDGE = Box::checkBoxSize(); //set the value for EDGE
		V position; //Create Position Vector
		Q orientaion; //Create orientation Quaternion
		initializerP(&position.x, &position.y, &position.z); //No overlap check, defined in initial.cpp
		initializerO(&orientation.a, &orientation.b, &orientation.c, &orientation.d); //Defined in initial.cpp
		
	}


/*/////Constructor - only for energy
	//Initializes energy
	Particle(): energy(0.0000), c_energy(0.0000) {} //Float precision 4*/
	

//Destructor
	~Particle(){}



//////Accessor Functions

	//getPosition - Accessor
	//@brief - Returns the position vector of the particle
	//@return - position[]
	double getPosition() const
	{
		
		return(this->position);
	}

	//getOrientation - Accessor
	//@brief - Returns the orientation of the particle
	//@return - orientation[]
	double getOrientation() const
	{
		
		return(this->orientation);
	
	}

	//getEnergy - Accessor
	//@brief - Returns the Energy of the particle And ends line
	//@return - double energy
	double getEnergy() const
	{
		
		return(this -> energy);
	}


	//getc_Energy - Accessor
	//@brief - Returns the Chemical Energy of the particle And ends line
	//@return - double c_energy
	double getc_Energy() const
	{
		
		return(this -> c_energy);
	}


/////Mutator Functions

	//Translaton Updator - Mutator
	//@brief - Updates the position of the particle
	//	   Contains rejection condition, periodic boundary conditions not implemented
	//@param - double &translate[]
	void translator(V translate)
	{

		position.x+=translate.x;
		position.y+=translate.y;
		position.z+=translate.z;
		
		//Simple Periodic Boundary Conditions
		if (position.x > EDGE) { position.x = (position,x - EDGE) }
		if (position.y > EDGE) { position.y = (position.y - EDGE) }
		if (position.z > EDGE) { position.z = (position.z - EDGE) }
		if (position.x < 0) { position.x = (-1*position,x) }
		if (position.y < 0) { position.y = (-1*position.y) }
		if (position.z < 0) { position.z = (-1*position.z) }
	
	}

	//Orientation Updator - Mutator
	//brief - Updates the angular orientation of the particle
	// 	  Contains no rejection condition
	//@param - double &orient[]
	void orienter(Q orient)
	{

			orientation.a+=orient.a;
			orientation.b+=orient.b;
			orientation.c+=orient.c;
			orientation.d+=orient.d;
	}

	//Energy Updator - Mutator
	//@brief - Updates the energy of the particle
	//	   Contains no rejecion condition
	//@param - double energise
	void energiser(double &energise)
	{
		energy = energise;
	}

	//Chemical Energy Updator - Mutator
	//@brief - Updates the cheical energy of the particle
	//	   Contains no rejecion condition
	//@param - double energise
	void energiser(double &c_energise)
	{
		energy+=energise;
	}

	
private:
/////Member variables
	
	double energy;
	double c_energy
	int partid;
	bool ghost;
	static int EDGE;



/////Friend declarations
Friend class Render;

}; //End of class Particle
