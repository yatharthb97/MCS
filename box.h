//Header file - For class Box
//Creates a square conatainer for Particles

//Dependencies ==> log.h for logout()
//				   particle.h for class Particle

//Status - Incomplete, Not tested
//Author - yatharthb97

//Preprocessors
#pragma once
#include<iostream>


#include<bits/stdc++.h>
#include<sstream> //ostringstream used in Constructor
#include "particle.h" //for the Particle class
//#include"random.h" //For Random(int, int)
#include "log.h" //For logoutput()
#include "runparam.h" //Obvious
#include<cmath>
#include<algorithm>
//#include "cluster.h"
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


//Cluster parameters
//vector<Cluster> clustlist;
int ClusterCount;
int ParticleInClusterCount;
//vector<int> ClusterIDActiveList;
//vector<int> ClusterIDBin;

//Member Functions

//1
//@brief - Constructor - Create empty countainer with edge 1
Box():count(0), ghost(0), edge(1), ACCEPT(0), REJECT(0), totdis(0.00000), totdisSq(0.00000)
{
	edge = RunParam::BoxSize;
	
}
//End of 1

//2
//Overloading Constructor
//@brief - Create a box container with a fixed size and particles
//@param - count - number of particles
//		 - size - edge size of the box
Box(int count):count(count), ghost(0), energy(energy), ACCEPT(0), REJECT(0), totdis(0.00000), totdisSq(0.00000), ClusterCount(0), ParticleInClusterCount(0)
{
	//Particle p(-1);
	//p.setEDGE(this->edge);
	edge = RunParam::BoxSize;


	//Uniform Shuffle
    int shufflelist[count-1];
    for(int i=0; i<count; i++)
    {
        shufflelist[i] = count-i-1;
    }

      //Shuffling
     for(int i=0; i<count; i++)
     {
    
     
        	int j = Rndm(0,i);
     		if(i!=j)
     		{
            	int temp = shufflelist[i];
            	shufflelist[i] = shufflelist[j];
            	shufflelist[j] = temp;
            } 
     }
     

     //Type 1
	int sc_1cp_number = count*(RunParam::SC_1CP_recipie)/100;
	//Type 2
	int sc_1tp_number = count*(RunParam::SC_1TP_recipie)/100;
	int ledger1 = 0;
	int ledger2 = 0;

    //Fill Box with recipie
	for(unsigned int i = 0; i<count; i++ )
	{
		
		if(shufflelist[i] < sc_1tp_number)
		{
			partlist.push_back(Particle(i, 2));
			ledger2++;
		}

		if(shufflelist[i] >= sc_1tp_number)
		{
			ledger1++;
			partlist.push_back(Particle(i, 1));
			if(shufflelist[i]>=sc_1tp_number+sc_1cp_number)
			{
				Log recipe;
				std::ostringstream r;
				r<<"Default Particle-type invoked for particle: "<<i;
				recipe.logerror("box.h, Box()", r.str());
			}
		}
	}


	//Assign initial Energy to the Box
	extern double LjLoop(std::vector<Particle> &vect);
	this->energy = LjLoop(this->partlist); //Run LJ Loop

	//Condition that checks if the conatiner is empty
	if(partlist.empty())
	{Log box; box.logerror("box.h","Container empty!");}

	if(partlist.size()< ledger1+ledger2)
	{
		ostringstream t;
		t<<"Container Not Filled Properly! Number of particles: "<<ledger1+ledger2;
		Log a; a.logerror("box.h/Box()", t.str()); 
	}

	else
	{
		std::ostringstream o;
		o<<"Box created with edge: "<<this->edge<<", particles: "<<count<<", and energy: "<<energy<<endl<<"Particle-Type 1: "<<ledger1<<",   Particle-Type 2: "<<ledger2;
		Log box;
		box.logoutput("box.h", o.str(), true);
	}

}
//End of 2


//3
//Destructor
//@brief - Logs that the box was destroyed
~Box()
{
	//std::cout<<"The Box class destructor was called. The container is destroyed!"
	Log boxdes;
	boxdes.logoutput("box.h", "The Box class destructor was called. The container is destroyed!", true);
}
//End of 3

///Accessors***********************************************************************************************

//4
//@brief - Get Acceptance Ratio
volatile double const getRatio()
{
	return ((double)ACCEPT/(REJECT+ACCEPT));
}
//End of 4


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
//End of 5

//6
//Runs a complete LJ loop insted of partial energy calculation
void UpdateEnergy()
{
	extern double LjLoop(std::vector<Particle> &vect);
	this->energy = LjLoop(this->partlist); //Run LJ Loop
}
//End of 6



///Mutators************************************************************************************************


//7
//@brief - Changes the box size - use with causion
volatile void setBoxSize(double size)
{
	this->edge = size;
	RunParam::BoxSize = size;
}
//End of 7

//8
//@brief - Mutate a Random Particle in the box
void MutateRndm()
{
	int pid = Rndm(0, count-1);
	int ptype = partlist.at(pid).type;
	extern int roll();
	int rolldie = roll();
	int counter  = 0;
	int ifbreak = false;
	for(int i = 1; i<4; i++)
	{
		counter += RunParam::MutaMatrix[ptype][i]*10;
		if(counter <=rolldie && !ifbreak)
		{
			int mtype = ptype+i;
			if(mtype>4){mtype = mtype-4;}
			partlist.at(pid).type = mtype;
		}
	}
}
//End of 8


//9
//@brief - Remove Particle - Ghost Particle
void RemoveParticle(int partid)
{
	this->partlist.at(partid).MakeGhost(true);
	ghost+=1;
	ghostlist.push_back(partid); //Maintain a ghost list
}
//End of 9


//10
//@brief - Remove a random particle from the box 
void RemoveRndParticle()
{
	if(Rndm(1,1000)<=RunParam::RmPartTrialAcceptRate*10)
	{
		int partid = Rndm(1, count-1);
		this->partlist.at(partid).MakeGhost(true);
		ghost+=1;
		ghostlist.push_back(partid); //Maintain a ghost list
	}
}
//End of 10


//11
//@brief - Bring back a removed particle
void CPRParticle(int partid, int vectorpos)
{
	this->partlist.at(partid).MakeGhost(false);
	ghostlist.erase(ghostlist.begin() + vectorpos);
	ghost--;
}
//End of 11


//12
//@brief - Bring Back a Random Ghost particle
void CPRRndGhost()
{
	unsigned int partid = Rndm(0, ghost-1);
	unsigned int pid = ghostlist.at(partid);
	partlist.at(pid).ghost=false;
	ghostlist.erase(ghostlist.begin() + partid);
	ghost--;
}
//End of 12


//13
//@brief - Add new Particle to the container
void AddParticle(int type)
{
	this->partlist.push_back(Particle(count+1,type));
	count+=1;
}
//End of 13


//14
//@brief - Remove all ghost particles and renormalize the list
void FlushGhosts()
{
	//Add function to renormalize particle ids. - Remove all ghosts from the list.
	//This approach needs rearrangement of the partlist

}
//End of 14


//15
//@brief - Increment RETECT
volatile void Reject(int a)
{
	if(a==1) {REJECT+=1;}
}
//End of 15

//16
//@brief - Increment ACCEPT
volatile void Accept(int a)
{
	if(a==1){ACCEPT+=1; }
}
//End of 16

//17
//@brief - Creates a TrialMove
double TrialMove()
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
	double disp = V(temp.position - this->partlist.at(pid).position).size();
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
		double E_inc = (abs(E_new-E_old)/energy)*100;
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
//End of 17

//18
//@brief - Raw Render EnergyFlux Graphs
void Graph(string path, int sweeps, double elapsedseconds)
{
	string filename=path+"/energyflux.dat";
	ofstream graph(filename, ios::app);
	graph<<sweeps<<":"<<energy<<":"<<totdis<<":"<<totdisSq/elapsedseconds<<":"<<ACCEPT<<":"<<REJECT<<endl;
	graph.close();
	
}//End of 18

//19
double NumberDensity()
{

}


/*//20
int newClustID()
{
	if(ClusterIDBin.size()!=0)
	{
		sort(ClusterIDBin.begin(), ClusterIDBin.end); //Sort ClusterID Bin
		int tempClustID = ClustIDBin.pop();
		clustlist.at(tempClustID).active = true;
		ClusterIDActiveList.push_back(tempClustID);
		ClusterCount++;
	}
 
	else
	{
		int tempClustID = ClusterCount;
		clustlist.push_back(Cluster(tempClustID)); //Call Constructor of the Cluster Class
		ClusterIDActiveList.push_back(tempClustID);
		ClusterCount++;
	}

	return tempClustID;
}//End of 20

//21
void ClusterPair(int partid1, intpartid2)
{
	if(partlist.at(partid1).ClusterSwitch = true && partlist.at(partid2).ClusterSwitch = true && )
	{
		
		if(partlist.at(partid1).ClusterID != -1 || partlist.at(partid2).ClusterID != -1) 
		{
			cerr<<"Particle's cluster state undefined: "<<partid1<<"or"<<partid2<<endl;
		}

		else
		{
			if(partlist.at(partid1).ClusterSwitch ==true && partlist.at(partid2).ClusterSwitch == true)
			{
			//
			}

			else
			{
					int retainClustID = std::min(partlist.at(partid1).ClusterID, partlist.at(partid1).ClusterID);
					int binClustID = std::max(partlist.at(partid1).ClusterID, partlist.at(partid1).ClusterID);


				}

				//Copy one Cluster in another
				clustlist.at(retainClustID).CopyCluster(&clustlist.at(binClustID));
				//Clear the spare Cluster
				clustlist.at(binClustID).binCluster();

				//Find Clust ID in ClusterIDActiveList
				std::vector<int>::iterator it;
				// std::find function call 
   				it = std::find(ClusterIDActiveList.begin(), ClusterIDActiveList.end(), binClustID); 
    			if (it != ClusterIDActiveList.end()) 
    			{ 
        			
        			//Erase ClustID from ClusterIDActiveList
        			ClusterIDActiveList.erase(it);
        			//Add ClustID to ClusterIDBin
        			ClusterIDBin.push_back(binClustID);
    			} 
    			else
    			{
        			cerr << "ClustID not present in ClusterIDActiveList container."<<endl;; 
    			}

				ClusterCount--;
			} 
		}

	else if(partlist.at(partid1).ClusterSwitch = true && partlist.at(partid2).ClusterSwitch = false)
	{
		int tempClustID = partlist.at(partid1).ClusterID;

		//Allowed?
		partlist.at(partid2).ClusterSwitch = true;
		partlist.at(partid2).ClusterID = tempClustID;
		//
		clustlist.at(tempClustID).clustadd(partid1);

		ParticleInClusterCount++;

	}

	else if(partlist.at(partid1).ClusterSwitch = false && partlist.at(partid2).ClusterSwitch = true)
	{
		int tempClustID = partlist.at(partid2).ClusterID;

		//Allowed?
		partlist.at(partid1).ClusterSwitch = true;
		partlist.at(partid1).ClusterID = tempClustID;
		//
		clustlist.at(tempClustID).clustadd(partid1);

		ParticleInClusterCount++;

	}

	else if(partlist.at(partid1).ClusterSwitch = false && partlist.at(partid2).ClusterSwitch = false)
	{
		int tempClustID = newClustID();

		//Allowed?

		partlist.at(partid1).ClusterSwitch = true;
		partlist.at(partid1).ClusterID = tempClustID;
		partlist.at(partid2).ClusterSwitch = true;
		partlist.at(partid2).ClusterID = tempClustID;
		//
		clustlist.at(tempClustID).clustadd(partid1);
		clustlist.at(tempClustID).clustadd(partid2);
		
		ParticleInClusterCount + 2;
	}

	
}//End of 21
*/


//Friend class Declarations

};//End of Class Box
