//Header file - For class BoxParticle
//Creates a particle

//Dependencies ==> Box.h for checkBoxSize() 
//				   initial.cpp for initializerP and initializero
//				   Vector.h for class V and class Q
//				   Global.cpp for checkBoxSize

//Status - Incomplete, Not tested
//Author - yatharthb97s

//Preprocessors
#pragma once
#include "box.h"
#include "./Vector.h"


extern volatile double checkBoxSize();

class Particle
{
public:

//1
//Constructor
	//@brief - Calls initializer and sets up the particle
	//@param - partid ==> particle ID	
	Particle(int partid): energy(0.0000), c_energy(0.0000), partid(partid), ghost(false)
	{
		
		extern volatile double checkBoxSize();
		extern void initializerP(double &x, double &y, double &z);
		//extern void initializerO(&double a, &double b, &double c, &double d);
		double EDGE = checkBoxSize(); //set the value for EDGE
		initializerP(position.x, position.y, position.z); //Defined in initial.cpp
		//initializerO(&orientation.a, &orientation.b, &orientation.c, &orientation.d); //Defined in initial.cpp
		
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
		
		return V(this->position);
	}

	//4
	//getOrientation - Accessor
	//@brief - Returns the orientation of the particle
	//@return - Q orientation
	Q getOrientation() const
	{
		
		return (this->orientation);
	
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

		position=position+translate;
		
		//Simple Periodic Boundary Conditions
		if (position.x > EDGE) { position.x = (position.x - EDGE); }
		if (position.y > EDGE) { position.y = (position.y - EDGE); }
		if (position.z > EDGE) { position.z = (position.z - EDGE); }
		if (position.x < 0) { position.x = (position.x + EDGE); }
		if (position.y < 0) { position.y = (position.y + EDGE); }
		if (position.z < 0) { position.x = (position.z + EDGE); }
	
	}

	//9
	//Orientation Updator - Mutator
	//brief - Updates the angular orientation of the particle
	//  	  Contains no rejection condition
	//@param - Q orient
	/*void orienter(Q orient)
	{

			orientation.a+=orient.a;
			orientation.b+=orient.b;
			orientation.c+=orient.c;
			orientation.d+=orient.d;
	}*/

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
	void c_energiser(double &c_energise)
	{
		energy+=c_energise;
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
	double c_energy;
	int partid;
	bool ghost;
	static int EDGE;
	V position;
	Q orientation;



/////Friend declarations
//Friend class Render;

}; //End of class Particle
