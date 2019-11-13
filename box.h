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
//#include"random.h" //For Random(int, int)
#include "log.h" //For logoutput()
#include "runparam.h" //Obvious
using namespace std;

//Class Box
class Box{


public: //Member Variables

//Box Param
int count;
double edge;
double energy;

//Particle Vector Container
vector<Particle> partlist;

//Ghost parameters
vector<int> ghostlist;
int ghost;

//Statistical Quantities
double totdis;
double totdisSq;
int ACCEPT;
int REJECT;

//Member Functions

//1
//@brief - Constructor - Create empty countainer with edge 1
Box():count(0), ghost(0), edge(1), ACCEPT(0), REJECT(0), totdis(0.00000), totdisSq(0.00000)
{
	edge = RunParam::BoxSize;
	
}

//2
//Overloading Constructor
//@brief - Create a box container with a fixed size and particles
//@param - count - number of particles
//		 - size - edge size of the box
Box(int count):count(count), ghost(0), energy(energy), ACCEPT(0), REJECT(0), totdis(0.00000), totdisSq(0.00000)
{
	//Particle p(-1);
	//p.setEDGE(this->edge);
	edge = RunParam::BoxSize;
	for(unsigned int i = 0; i<count; i++ )
	{
		partlist.push_back(Particle(i, 1)); //1 is the type of the particle
		//Include code to catch exception thrown and generate error log
		//cout<<partlist.at(i).getPosition().info()<<endl;
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
//@brief - Logs that the box was destroyed
~Box()
{
	//std::cout<<"The Box class destructor was called. The container is destroyed!"
	Log boxdes;
	boxdes.logoutput("box.h", "The Box class destructor was called. The container is destroyed!", true);
}


///Accessors

//4
//@brief - Get Acceptance Ratio
volatile double const getRatio()
{
	return ((double)ACCEPT/(REJECT+ACCEPT));
}

//5
//@brief - prints the ghostlist vector - tab seperated
void const printGhostList()
{
	for(unsigned int i= this->ghost; i<(this->ghost); i++)
	{
		std::cout<<ghostlist[i]<<"\t";
	}
	std::cout<<std::endl;
}

//6
//Runs a complete LJ loop insted of partial energy calculation
void UpdateEnergy()
{
	extern double LjLoop(std::vector<Particle> &vect);
	this->energy = LjLoop(this->partlist); //Run LJ Loop
}

///Mutators

//7
//@brief - Changes the box size - use with causion
volatile void setBoxSize(double size)
{
	this->edge = size;
	RunParam::BoxSize = size;
}


//8
//@brief - Remove Particle - Ghost Particle
void RemoveParticle(int partid)
{
	this->partlist.at(partid).MakeGhost(true);
	ghost+=1;
	ghostlist.push_back(partid); //Maintain a ghost list
}

//9
//@brief - Bring back a removed particle
void CPRParticle(int partid, int vectorpos)
{
	this->partlist.at(partid).MakeGhost(false);
	ghostlist.erase(ghostlist.begin() + vectorpos);
	ghost--;
}

//10
//@brief - Bring Back a Random Ghost particle
void CPRRandGhost()
{
	unsigned int partid = Rndm(0, ghost-1);
	unsigned int pid = ghostlist.at(partid);
	partlist.at(pid).ghost=false;
	ghostlist.erase(ghostlist.begin() + partid);
	ghost--;
}

//11
//@brief - Add new Particle to the container
void AddParticle(int type)
{
	this->partlist.push_back(Particle(count+1,type));
	count+=1;
}

//12
//@brief - Remove all ghost particles and renormalize the list
void FlushGhosts()
{
	//Add function to renormalize particle ids. - Remove all ghosts from the list.
	//This approach needs rearrangement of the partlist

}

//13
//@brief - Increment RETECT
volatile void Reject(int a)
{
	if(a==1) {REJECT+=1;}
}

//14
//@brief - Increment ACCEPT
volatile void Accept(int a)
{
	if(a==1){ACCEPT+=1; }
}

//15
//@brief - Creates a TrialMove
double trialMove()
{
	//extern int Rndm(int, int);
	int pid = Rndm(0, count-1);
	Particle temp;
	temp = partlist.at(pid); //Copy particle to a temp particle

	extern double PartEnergyCalc(std::vector<Particle> &vect, int pid);
	double E_old = PartEnergyCalc(this->partlist, pid);
	//Store Old Partial Energy

	extern void UpdatorO(Particle &p);
	extern void UpdatorP(Particle &p);
	UpdatorO(partlist.at(pid));
	UpdatorP(partlist.at(pid));
	double disp = V(temp.position-partlist.at(pid).position).size();
	//Move Particle

	//Calculate New Partial Energy
	double E_new = PartEnergyCalc(this->partlist, pid);
	

	//Energy Considerations
	if(E_new < E_old)
		{
			//Update Box Parameters
			Accept(1);
			energy = energy + E_new - E_old;
			totdis+=disp;
			totdisSq+=disp*disp;

			//Update Particle Parameters
			partlist.at(pid).accept++;
			partlist.at(pid).partdis+=disp;
			partlist.at(pid).partdisSq+=disp*disp;
			
			/*Log trial;
			trial.logoutput("particle.h","Move Accepted! Energy Decreased!", true);*/
		}
	else
	{
		double E_inc = ((E_new-E_old)/energy)*100;
		//Increased energy - acceptance move
		if(E_inc <= RunParam::MaxEnergyFluctuation && E_new <= 999 && Rndm(0,100) < RunParam::LJARatio)
		{
			//Update Box Parameters
			Accept(1);
			energy = energy + E_new - E_old;
			totdis+=disp;
			totdisSq+=disp*disp;

			//Update Particle Parameters
			partlist.at(pid).accept++;
			partlist.at(pid).partdis+=disp;
			partlist.at(pid).partdisSq+=disp*disp;
			/*Log trial;
			trial.logoutput("particle.h","Move Accepted! Energy Increased!", true);*/
			//cout<<"1";
		}

		/*else if(Rndm(0,100) < RunParam::LJARatio &&  E_new<999)
		{
			//Update Box Parameters
			Accept(1);
			energy = energy + E_new - E_old;
			totdis+=disp;
			totdisSq+=disp*disp;

			//Update Particle Parameters
			partlist.at(pid).accept++;
			partlist.at(pid).partdis+=disp;
			partlist.at(pid).partdisSq+=disp*disp;
			cout<<"2";
		}*/

		else
		{
			partlist.at(pid) = temp; //Copy back from temp, if rejected.
			partlist.at(pid).reject++; //Particle reject incremented
			Reject(1);
			if(RunParam::term2)
			{
				cout<<"___Move Rejected!___"<<endl;
				cout<<"---Particle "<<pid<<" moved to "<<partlist.at(pid).position.info()<<endl;
			}
			else
			{
				//cout<<"r"<<flush;
				//cout<<"3";
			}
			/*Log trial;
			trial.logoutput("particle.h","Move Rejected!", true);*/
			
		}

		
	}
}

void Graph(string path, int sweeps)
{
	string filename=path+"/energyflux.dat";
	ofstream graph(filename, ios::app);
	graph<<sweeps<<":"<<energy<<":"<<totdis<<":"<<totdisSq<<":"<<ACCEPT<<":"<<REJECT<<endl;
	graph.close();
	
}

//Friend class Declarations

};//End of Class Box