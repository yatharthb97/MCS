//Particle Header class

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
	double particle(double[3], double[3], double);
		//Calls initializer

	//Translaton Updator - Mutator
	double translator(double[3]);
		//Updates the position of the particle
		//@param c_translate[]

	//Orientation Updator - Mutator
	double orienter(double[3]);
		//Updates the angular orientation of the particle
		//@param c_orient[]

	//Energy Updator - Mutator
	double energiser(double);
		//Updates the energy of the particle
	
	//getPosition - Accessor
	void getPosition() const;
		//Returns the position array of the particle
		//@return double c_position[]
	
	//getOrientation - Accessor
	void getOrientation() const;
		//Returns the orientation of the particle
		//@return double c_orientation[]

	//getEnergy - Accessor
	void getEnergy() const;
		//Returns the Energy of the particle
		//@return double c_energy



private:
	//Member variables
	double c_position[3];
	double c_orientation[3];
	double c_energy;
	double c_translate[3];
	double c_orient[3];


};