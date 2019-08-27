#pragma once

#include<iostream>
#include<fstream>
#include<string>

class Render{

public:

	//printPosition
	//@brief - Prints the position array of the particle that is tab seperated. And ends line.
	void printPosition() const
	{
		V.pos = particle::getPosition();
			std::cout<<pos.x<<"\t"<<pos.y<<"\t"<<pos.z;
		std::cout<<endl;
	}



	//printOrientation
	//@brief - Prints the orientation of the particle And ends line
	void printOrientation() const
	{	
		V.ori = particle::getOrientation();
		
			std::cout<<ori.a<<"\t"<<ori.b<<"\t"<<ori.c<<"\t"<<ori.d;
		
		std::cout<<endl;
	}


	
	//createxyz
	//@brief - creates a file log of the xyz position to 
	/*void createxyz() const
	{
		freopen("~/MCS/Render/initialrender.dat","w",stdout);
		render::printPosition();
	}*/
	
	void createxyz(const char* initial) const
	{
	ofstream orend; //Try to create externally
	orend.open(initiallog, ios::in); //*
	if(orend.is_open())
	{
		std::cout.rdbuf(out.rdbuf());
		render::printPosition();
	}

	else
	{Log::logerror(initial, ("::open failure!"));}

	if(RUN == false) orend.close();

	}

	void render(const char* filename)
	{
		system("$FILEPLOT = filename")		
		system("./Render/gnuplot.sh");
	}

};// End of Class Render
