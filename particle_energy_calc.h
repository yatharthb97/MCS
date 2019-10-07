//Particle Engergy Calculator - Calculate the energy terms of the particle using hamiltonian and reject the move if the energy calculated is out of the box
#include<cmath>
#include<vector>
#include"runparam.h"
#include "Vector.h"

//Truncated LJ Potential - Weeks-Chandler Anderson Potential - Repulsion
//		0	- Attraction


	
	
	/*double Eta = RunParam::RepEta //Set value
	double sigma = 0.0000; //Set value*/
	double A = 4*EtaRep*pow(SigmaRep,12);
	double B = 4*EtaRep*pow(SigmaRep,6);
	//double rc = 2.5*SigmaRep; //Cutoff distance of 2.5 Sigma
	double C= (A/pow(CutOffRep,6));
	double D = B/(CutOffRep*CutOffRep);


double LjLoop(std::vector<Particle> &partlist) 
{
	//Probably Not Shifted
	double Vlj = 0.0000; //Initialize
	V r; //Define vector r
	int count = partlist.size();
	for(unsigned int i = 0; i<count; i++)
	{
		for(unsigned int j = 0; j<count; j++)
		{
			if((i!=j) && (partlist.at(i).isGhost() == false) && (partlist.at(j).isGhost()) == false)//If i = j, the contribution is zero and if particle is ghost.
			{
				r = partlist.at(i).getPosition() - partlist.at(j).getPosition();
				double rval = r.size();


				//Repulsion Portion
				if(rval<=CutOffRep) //Accept only if the distance is less than cutoff distance
				{
					double r6 = pow(rval,6);
					double r12 = r6*r6;
					Vlj+= ((A/r12) - (B/r6)) -(C-D); 
				}

				//Attraction Portion
				//{Vlj +=0;}

			}	
		}
	}

	return Vlj;

}

