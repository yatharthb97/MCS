//Header file - For class BoxParticle
//Creates a particle

//Dependencies ==> 
//				   initial.cpp for initializerP and initializero
//				   Vector.h for class V and class Q

//Status - Incomplete, Not tested
//Author - yatharthb97s

//Preprocessors
#pragma once
#include "Vector.h"
#include "runparam.h"
#include<sstream>
#include<iostream>
//#include"random.h"
using namespace std;

//For a single chiral patch
class Patch {
public:
    V side[2];
	V normal;
	V unit;
	static double width; //Patch width in radians

	//Functions
    Patch(){}

    /*Patch(V normal,V s1, V s2) : normal(normal) 
    {
        side[0] = s1;
        side[1] = s2;
    }*/

    void operator= (const Patch &p)
    {
    	side[0]=p.side[0];
    	side[1]=p.side[1];
    	normal=p.normal;
    	unit=p.unit;

    }

    void rotate(V &newaxis, double &angle) 
    {
        double vc, vs, t2, t3, t4, t5, t6, t7, t8, t9, t10;
        double d1, d2, d3, d4, d5, d6, d7, d8, d9 , newx, newy, newz;

        // generate quaternion for rotation
        //    maxcos = cos(maxorient/2/180*PI);
        // vc = maxcos + ran2(&seed)*(1-maxcos); /*cos of angle must be bigger than maxcos and smaller than one

        vc = cos(angle);

        //randomly choose orientation of direction of rotation clockwise or counterclockwise
        if (Rndm(0,100)<50) {vs = sqrt(1.000000 - vc*vc);}
        else{vs = -sqrt(1.000000 - vc*vc);} 

        Q newquat(vc, newaxis.x*vs, newaxis.y*vs, newaxis.z*vs);

         //do quaternion rotation
        t2 =  newquat.a * newquat.b;
        t3 =  newquat.a * newquat.c;
        t4 =  newquat.a * newquat.d;
        t5 = -newquat.b * newquat.b;
        t6 =  newquat.b * newquat.c;
        t7 =  newquat.b * newquat.d;
        t8 = -newquat.c * newquat.c;
        t9 =  newquat.c * newquat.d;
        t10 = -newquat.d * newquat.d;

        d1 = t8 + t10;
        d2 = t6 - t4;
        d3 = t3 + t7;
        d4 = t4 + t6;
        d5 = t5 + t10;
        d6 = t9 - t2;
        d7 = t7 - t3;
        d8 = t2 + t9;
        d9 = t5 + t8;


        //Rotate unit
        newx = 2.000000 * ( d1*this->unit.x + d2*this->unit.y + d3*this->unit.z ) + this->unit.x;
        newy = 2.000000 * ( d4*this->unit.x + d5*this->unit.y + d6*this->unit.z ) + this->unit.y;
        newz = 2.000000 * ( d7*this->unit.x + d8*this->unit.y + d9*this->unit.z ) + this->unit.z;
        this->unit.x = newx;
        this->unit.y = newy;
        this->unit.z = newz;


        //rotate normal
        newx = 2.000000 * ( d1*this->normal.x + d2*this->normal.y + d3*this->normal.z ) + this->normal.x;
        newy = 2.000000 * ( d4*this->normal.x + d5*this->normal.y + d6*this->normal.z ) + this->normal.y;
        newz = 2.000000 * ( d7*this->normal.x + d8*this->normal.y + d9*this->normal.z ) + this->normal.z;
        this->normal.x = newx;
        this->normal.y = newy;
        this->normal.z = newz;


        for (int k=0;k<2;k++) {
                //rotate chiral direction vector2
                newx = 2.000000 * ( d1*this->side[k].x + d2*this->side[k].y + d3*this->side[k].z ) + this->side[k].x;
                newy = 2.000000 * ( d4*this->side[k].x + d5*this->side[k].y + d6*this->side[k].z ) + this->side[k].y;
                newz = 2.000000 * ( d7*this->side[k].x + d8*this->side[k].y + d9*this->side[k].z ) + this->side[k].z;
                this->side[k].x = newx;
                this->side[k].y = newy;
                this->side[k].z = newz;
    	}
    }
    

//Member Functions


}; //eND OF class Patch


class Particle
{
/////Member variables
public:

	//Box Parameters
	int partid;
	bool ghost;
	int type;

	//Statistical Parameters
	double energy;
	int accept;
	int reject;
	double partdis;
	double partdisSq;


	//Particle Properties
	V position;
	Patch patch;

	//Particle dimensions
	static double L; //Length of the SPC
	static double D; //Diameter of the SPC

	//Default Empty constructor
	Particle(): ghost(false), energy(0.000000), accept(0), reject(0), type(type), partdis(0.00000), partdisSq(0.00000), ClusterSwitch(false), ClusterID(-1)
	{}


	//Cluster Parameters
	bool ClusterSwitch;
	int ClusterID;

//1
//Constructor
	//@brief - Calls initializer and sets up the particle
	//@param - partid ==> particle ID	
	Particle(int partid, int type): partid(partid), ghost(false), energy(0.000000), accept(0), reject(0), type(type), partdis(0.00000), partdisSq(0.00000), ClusterSwitch(false), ClusterID(-1)
	{
		extern void initializerP(V &v); //Defined in initial.cpp
		extern void initializerO(V &v);
		initializerP(position);
		initializerO(patch.unit);
		//position= V(1,1,1);
		//unit.rndUnit();
		patch.normal.orthogonal(patch.unit);//Orthogonal to the unit
		patch.side[0] = patch.normal; patch.side[1] = patch.normal;
		//cout<<patch.side[0].info()<<"   "<<patch.side[1].info()<<endl;
		patch.side[0].rotate(patch.unit, patch.width/2);
		patch.side[1].rotate(patch.unit, -(patch.width/2));
		
	}
	
	void operator= (const Particle &p)
	{
        partid = p.partid;
        ghost = p.ghost;
        energy = p.energy;
        accept = p.accept;
        reject = p.reject;
        type = p.type;
        position = p.position;
        patch = p.patch;
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


	std::string partinfo()
	{
		std::ostringstream info;
		info<<"PartID: "<<partid<<",   Ghost: "<<ghost<<endl;
		info<<"Accepted: "<<accept<<",   Rejected: "<<reject<<endl;
		info<<"Position: "<<position.info()<<",   Orientation(patch.unit): "<<patch.unit.info()<<endl;
		info<<"Patch normal: "<<patch.normal.info()<<",   Width(rad): "<<patch.width<<endl;
		info<<"Patch s1: "<<patch.side[0].info()<<",   Patch s1: "<<patch.side[1].info()<<endl;
		info<<"s0.dot.patch.unit: "<<patch.side[0].dot(patch.unit)<<",   s1.dot.patch.unit: "<<patch.side[1].dot(patch.unit)<<endl;
		info<<"Ang. Patch: "<<acos(patch.side[0].dot(patch.side[1]))<<endl;

		return info.str();


	}
	double getEnergy() const
	{
		
		return(this -> energy);
	}

	//6
	//getc_Energy - Accessor
	//@brief - Returns the Chemical Energy of the particle
	//@return - double c_energy
	/*double getc_Energy() const
	{
		
		return(this -> c_energy);
	}*/

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
		//this->moves++;
		
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
		if(RunParam::term2)
		{
			cout<<"---Particle "<<partid<<" moved to "<<position.info()<<endl;
		}

		else
		{
			//cout<<"."<<flush;
		}
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
	/*void c_energiser(double &c_energise)
	{
		energy+=c_energise;
	}
*/
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


/////Friend declarations
//Friend class Render;

}; //End of class Particle


