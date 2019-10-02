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
#include "particle.h" //for the Particle class
#include "log.h" //For logoutput()
#include<sstream> //ostringstream used in Constructor
using namespace std;

//Class Box
class Box{


private: //Member Variables

int count;
double edge;
static vector<int> ghostlist;
int ghost;
double energy;

public: //Member Functions

//1
//@brief - Constructor - Create empty countainer with edge 1
Box():count(0), edge(1), ghost(0), energy(0){}

//2
//Overloading Constructor
//@brief - Create a box container with a fixed size and particles
//@param - count - number of particles
//		 - size - edge size of the box
Box(int count, double size, double energy):count(count), edge(size), ghost(0), energy(energy)
{
	vector<Particle> partlist;

	for(unsigned int i = 1; i<=count; i++ )
	{
		partlist.push_backpush(Particle((int)i));
		//Include code to catch exception thrown and generate error log

	}

	//Condition that checks if the conatiner is empty
	if(partlist.empty)
	{Log box; box.logerror("box.h","Container empty!")}

	else{
	std::ostringstream o;
	o<<"Box created with edge: "<<this->size<<" and particles: "<<count;
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
//Returns the box size
volatile double checkBoxSize()
{
	return(edge); //Size of the box
}

//5
//Returns the number of particles in the box excluding the ghost particles
void const getCount()
{
	return(count-ghost);
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

//7
//@brief - prints the ghostlist vector - tab seperated
void const printGhostList()
{
	for(unsigned int i= this->ghost; i<(this->ghost); i++)
	{
		std::cout<<ghostlist[i]<<"\t";
	}
	std::cout<<std::endl;
}



///Mutators

//8
//Changes the box size - use with causion
volatile void setBoxSize(double size)
{
	this->edge = edge;
}

//9
//Remove Particle
void RemoveParticle(int partid)
{
	partlist(partid).MakeGhost(true);
	ghost+=1;
	ghostlist.push_back(partid); //Maintain a ghost list
}

//10
//Bring back a removed particle
void CPRParticle(int partid, int vectorpos)
{
	partlist(partid).MakeGhost(false);
	ghost-=ghost;
	ghostlist.erase(ghostlist.begin() + vectorpos);
}

//11
//Add new Particle to the container
void AddParticle()
{
	partlist.push_back(count+1);
	count+=1;
}

//12
//Remove all ghost particles and renormalize the list
void RemoveAllGhosts()
{}



//13
double trialPos()
{
	int pid = Random(1, count); //Random not defined
	V temp;
	temp = Updator3();
	partlist(pid).translate(temp); //Edit Updator3 function
	extern double LjLoop(std::vector<Particle> &vect);
	double E_new = LjLoop(this->partlist); //Run LJ Loop

	//Energy Considerations
	if(E_new <= this->energy)
		{	extern inline Accept(1);
			Accept(1);
			this->energy = E_new;
		}
	else
	{
		extern inline volatile checkLJARatio();
		int LJRR = checkLJARatio();
		//Increased energy acceptance move
		if(Random(0,100) < LJRR)
		{
			extern inline Accept(1);
			Accept(1);
			this->energy = E_new;
		}

		else
		{
			partlist(pid).translate(-1*temp); //Complete vector class
			Log trial;
			trial.logoutput("particle.h","Move Rejected!", false);
			extern inline Reject(int); //Defined in Global.cpp
			Reject(1);
		}

		
	}

}
//Friend class Declarations

};//End of Class Box


//Add function to renormalize particle ids. - Remove all ghosts from the list.