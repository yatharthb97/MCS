//Particle Engergy Calculator - Calculate the energy terms of the particle using hamiltonian and reject the move if the energy calculated is out of the box


//Truncated LJ Potential - Need a box energy

double LjLoop()
{
	double Eta, sigma ;
	double A = 4*Eta*pow(sigma,12);
	double B = 4*Eta*pow(sigma,6);
	double rc = 1000000; //Cutoff distance
	for(unsigned int i = 1; i<=count; i++)
	{
		for(unsigned int j = 1; j<=count; j++)
		{
			if(i!=j) //If i = j, the contribution is zero. 
			{
				r = b.partlist(i).size() - b.partlist(j).size();
				if(r>rc) //Accept only if the distance
				{
					r6 = pow(r,6);
					r12 = r6*r6;
					E+= (A/r12) - (B/r6);
				}
			}	
		}
	}

	return E;
}


if(Ej < Ei)
{

}

