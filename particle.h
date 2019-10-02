//Header file for Particle class

//Periodic boundary conditions not implemented

#pragma once

#include "./Vector.h"


inline extern int checkBoxSize();

class Particle
{
public:

//1
//Constructor
	//@brief - Calls initializer and sets up the particle
	//@param - partid ==> particle ID	
	Particle(int partid): energy(0.0000), c_energy(0.0000), partid(partid), ghost(false)
	{
		
		volatile double Box::checkBoxSize();
		double EDGE = Box::checkBoxSize(); //set the value for EDGE
		V position; //Create Position Vector
		Q orientaion; //Create orientation Quaternion
		initializerP(&position.x, &position.y, &position.z); //No overlap check, defined in initial.cpp
		initializerO(&orientation.a, &orientation.b, &orientation.c, &orientation.d); //Defined in initial.cpp
		
	}
	
//2	
//Destructor
	~Particle(){}


//////Accessor Functions

	//3
	//getPosition - Accessor
	//@brief - Returns the position vector of the particle
	//@return - V position
	V getPosition() const
	{
		
		return(this->position);
	}

	//4
	//getOrientation - Accessor
	//@brief - Returns the orientation of the particle
	//@return - Q orientation
	Q getOrientation() const
	{
		
		return(this->orientation);
	
	}

	//5
	//getEnergy - Accessor
	//@brief - Returns the Energy of the particle
	//@return - double energy
	double getEnergy() const
	{
		
		return(this -> energy);
	}

	//6
	//getc_Energy - Accessor
	//@brief - Returns the Chemical Energy of the particle
	//@return - double c_energy
	double getc_Energy() const
	{
		
		return(this -> c_energy);
	}

	//7
	//bool is ghost - Mutator
	//@brief - Checks if the particle is a ghost particle
	//@return - bool true/false
	bool isGhost()
	{
		if(ghost) return true;
		else return false;
	}

/////Mutator Functions

	//8
	//Translaton Updator - Mutator
	//@brief - Updates the position of the particle
	//	 	   Contains periodic boundary condition
	//@param - V translate
	void translator(V translate)
	{

		position.x+=translate.x;
		position.y+=translate.y;
		position.z+=translate.z;
		
		//Simple Periodic Boundary Conditions
		if (x > BoxSize) { x = (x - BoxSize) }
		if (y > BoxSize) { y = (y - BoxSize) }
		if (z > BoxSize) { x = (z - BoxSize) }
		if (x < 0) { x = (x + BoxSize) }
		if (y < 0) { y = (y + BoxSize) }
		if (z < 0) { x = (z + BoxSize) }
	
	}

	//9
	//Orientation Updator - Mutator
	//brief - Updates the angular orientation of the particle
	//  	  Contains no rejection condition
	//@param - Q orient
	void orienter(Q orient)
	{

			orientation.a+=orient.a;
			orientation.b+=orient.b;
			orientation.c+=orient.c;
			orientation.d+=orient.d;
	}

	//10
	//Energy Updator - Mutator
	//@brief - Updates the energy of the particle
	//		   Contains no rejecion condition
	//@param - double energise
	void energiser(double &energise)
	{
		energy = energise;
	}

	//11
	//Chemical Energy Updator - Mutator
	//@brief - Updates the cheical energy of the particle
	//		   Contains no rejecion condition
	//@param - double c_energise
	void energiser(double &c_energise)
	{
		energy+=energise;
	}

	//12
	//void MakeGhost - Mutator
	//@bref - CChange the Ghost status of the particle
	//@param - bool
	void MakeGhost(bool b)
	{
		this->ghost = b;
	}

/////Member variables
	private:
	double energy;
	double c_energy
	int partid;
	bool ghost;
	static int EDGE;



/////Friend declarations
Friend class Render;

}; //End of class Particle
