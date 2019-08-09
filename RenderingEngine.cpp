#pragma once
#include<ostream>
#include<iostream>
#include<iomanip>
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
	orend<<setprecision(7)<<c_position[0]<<"\t"<<c_position[1]<<"\t"<<c_position[2]<<endl;
}



