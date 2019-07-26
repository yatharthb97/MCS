//Particle Header class
//Comments incomplete

#pragma once

class particle
{
public:
	//Constructor - only for energy
	particle();
	//Initializes energy

	//Destructor
	~particle();

	//Overloading Initializer
	particle(&double[], &double[]);
		//Calls initializer
		//Calls initializer and sets up the initial environment
		//@param - &position[], &orientation[]

	//Translaton Updator - Mutator
	void translator(&double[], &double[]);
		//Updates the position of the particle
		//@param &c_position[], &translate[]

	//Orientation Updator - Mutator
	void orienter(&double[], &double[]);
		//Updates the angular orientation of the particle
		//@param &orient[], &c_orientation[]
//-------------------------------------------------------------------Comments incomplete after this line
	//Energy Updator - Mutator
	void energiser(&double, &double[]);
		//Updates the energy of the particle
	
	//getPosition - Accessor
	double getPosition(&c_position[]) const;
		//Returns the position array of the particle
		//@return double c_position[]
	
	void printPosition(&c_position[]) const;
		//Prints the position array of the particle And ends line
		//@param - c_position[]

	//getOrientation - Accessor
	double getOrientation(&c_orientation) const;
		//Returns the orientation of the particle
		//@return - double c_orientation[]

	void printOrientation(&c_orientation) const;
		//Prints the position array of the particle and ends line
		//@param - &c_orientation[]

	//getEnergy - Accessor
	double getEnergy(&c_energy) const;
		//Returns the Energy of the particle
		//@return - c_energy



private:
	//Member variables
	double c_position[3];
	double c_orientation[3];
	double c_energy;
	//double c_translate[3];
	//double c_orient[3];


};