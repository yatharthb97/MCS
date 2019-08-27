//Particle Header class

#pragma once

class particle
{
public:
/////Constructor - only for energy
	//Initializes energy
	particle()
	{
		energy=0.000000;
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
		position = random::initializerP();
		orientation = random::initializerO();
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


/////Mutator Functions

	//Translaton Updator - Mutator
	//@brief - Updates the position of the particle
	//	   Contains rejection condition
	//@param - double &translate[]
	void translator(double &translate[])
	{
		if((position[0]+=translate[0] && position[1]+=translate[1] && < position[2]+=translate[2]) < EDGE)
		//if(for(i = 0 && 1 && 2):(c_position[0]+=c_translate[0]) < EDGE)
		{
			for(int i = 0; i<3; i++)
			{
				position[i]+=translate[i];
			}
		}
		else
			{
				Log::createlogerr("Tranlation move out of bounds!");  //Not defined and also class not defined
				REJECT = REJECT+1; //REJECT defined globally
			}
	}

	//Orientation Updator - Mutator
	//brief - Updates the angular orientation of the particle
	// 	  Contains no rejection condition
	//@param - double &orient[]
	void orienter(double &orient[])
	{
		
		for(int i = 0; i<3; i++)
		{
			orientation[i]+=orient[i];
		}
	}

	//Energy Updator - Mutator
	//@brief - Updates the energy of the particle
	//	   Contains no rejecion condition
	//@param - double energise
	void energiser(double &energise)
	{
		energy = energise;
	}

	
private:
/////Member variables
	double position[3];
	double orientation[3];
	double energy;
	int partid;



/////Friend declarations
Friend class Render;

};
