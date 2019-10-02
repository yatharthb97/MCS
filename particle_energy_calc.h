//Particle Engergy Calculator - Calculate the energy terms of the particle using hamiltonian and reject the move if the energy calculated is out of the box
#include<cmath>
#include<vector>
//Truncated LJ Potential - Weeks-Chandler Anderson Potential


	double Eta = 0.0000; //Set value
	double sigma = 0.0000; //Set value
	double A = 4*Eta*pow(sigma,12);
	double B = 4*Eta*pow(sigma,6);
	double rc = 2.5*sigma; //Cutoff distance of 2.5 Sigma
	double C= (A/pow(rc,6));
	double D = B/(rc6*rc6);
	double vlj = 0.0000; //Initialize


double LjLoop(std::vector<Particle> &partlist) //Skeleton Function
{
	//Neither shifted nor truncated
	V r; //Define vector r
	for(unsigned int i = 1; i<=count; i++)
	{
		for(unsigned int j = 1; j<=count; j++)
		{
			if((i!=j) && (partlist(i).isGhost() == false) && (partlist(j).isGhost()) == false)//If i = j, the contribution is zero and if particle is ghost.
			{
				r = b.partlist(i).getPosition() - b.partlist(j).getPosition();
				r = r.size();
				if(r<=rc) //Accept only if the distance is less than cutoff distance
				{
					r6 = pow(r,6);
					r12 = r6*r6;
					Vlj+= ((A/r12) - (B/r6)) -(C-D);
				}
			}	
		}
	}

	return Vlj;
}

