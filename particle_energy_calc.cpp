//Particle Engergy Calculator - Calculate the energy terms of the particle using hamiltonian and reject the move if the energy calculated is out of the box
#include<cmath>
#include<vector>
#include"runparam.h"
#include "Vector.h"
#include "particle.h"
#define PI 3.141592653
//Check and place the correct value of PI

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
	double Vlj = 0.000000; //Initializes
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

				//Dynamic Positiona CutOFF
				V point = partlist.at(i).position.point(partlist.at(j).position);

				if(point.arccos(partlist.at(i).patch.unit) > PI/4)
				{
					if(rval<=(Particle::L+Particle::D/2))
					{
						return 999;
					}
				}

				else
				{
					if(rval<=Particle::D)
					{
						return 999;
					}
				}

				point = point*-1;
				if(point.arccos(partlist.at(j).patch.unit) > PI/4)
				{
					if(rval<=(Particle::L+Particle::D/2))
					{
						return 999;
					}
				}

				else
				{
					if(rval<=Particle::D)
					{
						return 999;
					}
				}
				//Dynamic Positional CutOFF
				

				//Repulsion part - only position dependent
				//Repulsion Portion
				if(rval<=CutOffRep) //Accept only if the distance is less than cutoff distance
				{
					double r6 = pow(rval,6);
					double r12 = r6*r6;
					Vlj+= ((A/r12) - (B/r6)) -(C-D); 
				}
				//End of Repulsion part - LJLoop

				//Attraction Portion
				double normo = partlist.at(i).patch.normal.dot(partlist.at(j).patch.normal);
				double unito = partlist.at(i).patch.unit.dot(partlist.at(j).patch.unit);

				if (rval <= 1.5*SigmaAtrr)
				{
					if(acos(normo) <= (Patch::width)/2 && acos(normo) >= -(Patch::width)/2)
					{
						Vlj+= +EtaAtrr*unito*unito + EtaAtrr*2; //Last Term: -EtaAtrr*SigmaAtrr/Radius ==> diameter = SigmaAtrr
					}
				}
			}	
		}
	}

	//cout<<"Energy: "<<Vlj<<endl;
	return Vlj;

}

double PartEnergyCalc(std::vector<Particle> &partlist, int i) 
{
	//Probably Not Shifted
	double Vlj = 0.000000; //Initializes
	V r; //Define vector r
	int count = partlist.size();

		for(unsigned int j = 0; j<count; j++)
		{
			if((i!=j) && (partlist.at(i).isGhost() == false) && (partlist.at(j).isGhost()) == false)//If i = j, the contribution is zero and if particle is ghost.
			{
				
				r = partlist.at(i).getPosition() - partlist.at(j).getPosition();
				double rval = r.size();

				//Dynamic Positiona CutOFF
				V point = partlist.at(i).position.point(partlist.at(j).position);

				if(point.arccos(partlist.at(i).patch.unit) > PI/4)
				{
					if(rval<=(Particle::L+Particle::D/2))
					{
						return 999;
					}
				}

				else
				{
					if(rval<=Particle::D)
					{
						return 999;
					}
				}

				point = point*-1;
				if(point.arccos(partlist.at(j).patch.unit) > PI/4)
				{
					if(rval<=(Particle::L+Particle::D/2))
					{
						return 999;
					}
				}

				else
				{
					if(rval<=Particle::D)
					{
						return 999;
					}
				}
				//Dynamic Positional CutOFF
				

				//Repulsion part - only position dependent
				//Repulsion Portion
				if(rval<=CutOffRep) //Accept only if the distance is less than cutoff distance
				{
					double r6 = pow(rval,6);
					double r12 = r6*r6;
					Vlj+= ((A/r12) - (B/r6)) -(C-D); 
				}
				//End of Repulsion part - LJLoop

				//Attraction Portion
				double normo = partlist.at(i).patch.normal.dot(partlist.at(j).patch.normal);
				double unito = partlist.at(i).patch.unit.dot(partlist.at(j).patch.unit);

				if (rval <= 1.5*SigmaAtrr)
				{
					if(acos(normo) <= (Patch::width)/2 && acos(normo) >= -(Patch::width)/2)
					{
						Vlj+= +EtaAtrr*unito*unito + EtaAtrr*2; //Last Term: -EtaAtrr*SigmaAtrr/Radius ==> diameter = SigmaAtrr
					}
				}
			}	
		}
	

	//cout<<"Energy: "<<Vlj<<endl;
	return Vlj;
}

