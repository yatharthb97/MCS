//Header file - For class Box
//Creates a square conatainer for Particles

//Dependencies ==> log.h for logout()
//				   particle.h for class Particle

//Status - Incomplete, Not tested
//Author - yatharthb97

//Preprocessors
#pragma once
#include<iostream>
#include<vector>
#include<sstream> //ostringstream used in Constructor
#include "particle.h" //for the Particle class
#include"random.h" //For Random(int, int)
#include "log.h" //For logoutput()
#include "runparam.h" //Obvious
#include "particle_energy_calc.h" //For LJ Loop
using namespace std;

//Class Box
class Box{


private: //Member Variables

int count;
double edge;
vector<int> ghostlist;
int ghost;
double energy;
vector<Particle> partlist;
int ACCEPT;
int REJECT;

public: //Member Functions

//1
//@brief - Constructor - Create empty countainer with edge 1
Box():count(0), ghost(0), edge(1), ACCEPT(0), REJECT(0)
{
	RunParam::BoxSize = 1;
}

//2
//Overloading Constructor
//@brief - Create a box container with a fixed size and particles
//@param - count - number of particles
//		 - size - edge size of the box
Box(int count, double edge):count(count), ghost(0), energy(energy), edge(edge), ACCEPT(0), REJECT(0)
{
	RunParam::BoxSize = edge;
	for(unsigned int i = 0; i<count; i++ )
	{
		partlist.push_back(Particle((int)i));
		//Include code to catch exception thrown and generate error log

	}

	//Assign initial Energy to the Box
	extern double LjLoop(std::vector<Particle> &vect);
	this->energy = LjLoop(this->partlist); //Run LJ Loop

	//Condition that checks if the conatiner is empty
	if(partlist.empty())
	{Log box; box.logerror("box.h","Container empty!");}

	else{
	std::ostringstream o;
	o<<"Box created with edge: "<<this->edge<<", particles: "<<count<<", and energy: "<<energy;
	Log box;
	box.logoutput("box.h", o.str(), true);
	}
}

//3
//Destructor
//Logs that the box was destroyed
~Box()
{
	//std::cout<<"The Box class destructor was called. The container is destroyed!"
	Log boxdes;
	boxdes.logoutput("box.h", "The Box class destructor was called. The container is destroyed!", true);
}


///Accessors

//4
//Returns the box size - Redundant after RunParam
volatile double checkBoxSize()
{
	return(edge); //Size of the box
}

//5
//Returns the number of particles in the box excluding the ghost particles
//@return - int count - ghost
int const getCount()
{
	return(count);
}

//6
//@brief - Returns the number of ghost particles in the box
//@return - int ghost 
int const getGhostCount()
{
	return(ghost);
}

//7
//@brief - Returns the ghostlist vector
//@return - vector<int> ghostlist
std::vector<int> const getGhostList()
{
	return ghostlist;
}

//8
//@brief - prints the ghostlist vector - tab seperated
void const printGhostList()
{
	for(unsigned int i= this->ghost; i<(this->ghost); i++)
	{
		std::cout<<ghostlist[i]<<"\t";
	}
	std::cout<<std::endl;
}
//9
double const getEnergy()
{
	return this->energy;
}

//10
std::vector<Particle> PassPartlist()
{
	return vector<Particle>(this->partlist);
}

//10
volatile int countReject()
{
	return REJECT;
}

//11
volatile int countAccept()
{
	return ACCEPT;
}

//12
volatile double getRatio()
{
	return (double)(ACCEPT/REJECT);
}


//13
//Changes the box size - use with causion
volatile void setBoxSize(double size)
{
	this->edge = size;
	RunParam::BoxSize = size;
}

//14
//Remove Particle
void RemoveParticle(int partid)
{
	this->partlist.at(partid).MakeGhost(true);
	ghost+=1;
	ghostlist.push_back(partid); //Maintain a ghost list
}

//15
//Bring back a removed particle
void CPRParticle(int partid, int vectorpos)
{
	this->partlist.at(partid).MakeGhost(false);
	ghost-=ghost;
	ghostlist.erase(ghostlist.begin() + vectorpos);
}

//16
//Add new Particle to the container
void AddParticle()
{
	this->partlist.push_back(count+1);
	count+=1;
}

//17
//Remove all ghost particles and renormalize the list
void RemoveAllGhosts()
{}

//18
volatile void Reject(int a)
{
	if(a==1) {REJECT+=1;}
}

//19
volatile void Accept(int a)
{
	if(a==1){ACCEPT+=1; }
}

//20
double trialPos()
{
	extern int Random(int, int);
	int pid = Random(0, count-1); //Random not defined
	V temp;
	//temp.null(); //define in vector V class
	extern void Updator3(V &temp);
	partlist.at(pid).translator(temp); //Edit Updator3 function
	extern double LjLoop(std::vector<Particle> &vect);
	double E_new = LjLoop(this->partlist); //Run LJ Loop

	//Energy Considerations
	if(E_new <= this->energy)
		{
			Accept(1);
			this->energy = E_new;
			Log trial;
			trial.logoutput("particle.h","Move Accepted! Energy Decreased!", false);
		}
	else
	{
		int LJRR = RunParam::checkLJARatio();
		//Increased energy - acceptance move
		if(Random(0,100) < LJRR)
		{
			Accept(1);
			this->energy = E_new;
			Log trial;
			trial.logoutput("particle.h","Move Accepted! Energy Increased!", false);
		}

		else
		{
			partlist.at(pid).translator(temp*-1);
			Log trial;
			trial.logoutput("particle.h","Move Rejected!", false);
			Reject(1);
		}

		
	}



}

//Friend class Declarations

};//End of Class Box


//Add function to renormalize particle ids. - Remove all ghosts from the list.