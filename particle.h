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
#include "Vector.h"
#include "runparam.h"

class Particle
{
public:

//1
//Constructor
	//@brief - Calls initializer and sets up the particle
	//@param - partid ==> particle ID	
	Particle(int partid): energy(0.0000), c_energy(0.0000), partid(partid), ghost(false), moves(0)
	{
		extern void initializerP(V &v); //Defined in initial.cpp
		extern void initializerO(V &v);
		initializerP(position);
		initializerO(unit);
		//normal = unit.orthagonalise(); //set normal as orthogonal to the unit
		/*RunParam p;
		EDGE = p.checkBoxSize();*/
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
	/*Q getOrientation() const
	{
		
		return (this->orientation);
	
	}*/

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
		RunParam p;
		double EDGE = p.checkBoxSize();
		position=position+translate;
		this->moves++;
		
		//Simple Periodic Boundary Conditions
		//cout<<"1.     "<<position.x<<" "<<position.y<<" "<<position.z<<endl;
		if (position.x > EDGE) { position.x = (position.x - EDGE);}
		if (position.y > EDGE) { position.y = (position.y - EDGE);}
		if (position.z > EDGE) { position.z = (position.z - EDGE);}
		if (position.x < 0.0000000) { position.x = (EDGE+position.x);}
		if (position.y < 0.0000000) { position.y = (EDGE+position.y);}
		if (position.z < 0.0000000) { position.z = (EDGE+position.z);}
		//cout<<"2.     "<<position.x<<" "<<position.y<<" "<<position.z<<endl;
	

		//Translation Info
		cout<<"---Particle "<<partid<<" moved to "<<position.info()<<endl;
	}

	
	//Orientation Updator - Mutator
	//brief - Updates the angular orientation of the particle
	//  	  Contains no rejection condition
	//@param - Q orient
	void orienter(Q orient)
	{
		//1. Perform a 3D rotation on the unit vector, which is in the global frame
		//2. Normalise unit
		//3. Select unit vector as thea xis and generate a 2D rotation around it - normal vector
		//4. Normalise normal
		//5. No boundary conditions

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


	/*static void setEDGE(double e)
	{
		EDGE = e;
	}*/

/////Member variables
	private:

	//Two sets of energy
	double energy;
	double c_energy;

	//Box Parameters
	int partid;
	bool ghost;
	int moves;//Records the number of times the particle is called
	int reject; //Records the number of times the particle is rejected when called
	//static double EDGE;

	//Particle Properties
	V position;
	V unit;
	V normal;




/////Friend declarations
//Friend class Render;

}; //End of class Particle
