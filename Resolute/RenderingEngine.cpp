#pragma once
#include<ostream>
#include<iostream>
#include<iomanip>

void createxyz(&double[]);
void closerend();

using namespace std;

	ofstream orend;
	orend.open("~/MCS/Render/initialrender.dat");
	if(orend.is_open)
	{
		std::cout<<"File intialrender.dat :: open succesfull."<<endl;
	}

	else
	cerr<<"File initialrender.dat ::open failure!"<<endl;
void createxyz(&c_position[])
{
	if (orend.is_open)
	{
		orend << setprecision(7) << c_position[0] << "\t" << c_position[1] << "\t" << c_position[2] << endl;
	}
	else cerr<< "File initialrender.dat ::open failure!" << endl;
}

void closerend()
{
	orend.ofstream::close();
}

orend.ofstream::close();