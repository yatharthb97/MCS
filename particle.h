//Header file for Particle class

//Periodic boundary conditions not implemented

#pragma once

#include "./Vector.h"

class particle
{
public:
/////Constructor - only for energy
	//Initializes energy
	particle()
	{
		energy=0.000000; //Float precision - 6
		c_energy=0.000000; //Float precision - 6
	}
	

/////Destructor
	~particle(){}

/////Overloading Constructor
	//@brief - Calls initializer and sets up the initial environment
	//@param - partid ==> particle ID	
	particle(int partid)
	{
		//random::initializerP(); //Notdefined - class random
		//random::initializerO();	//Notdefined - class random
		position.x, position.y, position.z = random::initializerP();
		orientation.a, orientation.b, orientation.c, orientation.d = random::initializerO();
		this->partid = partid;
		//Returns 6 values of randomly generated coordinates
		Render::createxyz(filename); //INsert filename config reference
			//Creates a trajectory file of the initial setup*/
	}

//////Accessor Functions

	//getPosition - Accessor
	//@brief - Returns the position array of the particle
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
	void translator(double &translate[])
	{
		if((position.x+=translate[0] && position.y+=translate[1] && < position.z+=translate[2]) < EDGE)
		//if(for(i = 0 && 1 && 2):(c_position[0]+=c_translate[0]) < EDGE)
		{
			
				position.x+=translate[0];
				position.y+=translate[1];
				position.z+=translate[2];
		}
		else
			{
				Log::logerror([Move Rejected],"Tranlation move out of bounds!");
				REJECT = REJECT+1; //REJECT defined globally
			}
	}

	//Orientation Updator - Mutator
	//brief - Updates the angular orientation of the particle
	// 	  Contains no rejection condition
	//@param - double &orient[]
	void orienter(double &orient[])
	{
		
			orientation.a+=orient[0];
			orientation.b+=orient[1];
			orientation.c+=orient[2];
			orientation.d+=orient[3];
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
	V.position;
	Q.orientation;
	double energy;
	double c_energy
	int partid;



/////Friend declarations
Friend class Render;

};
