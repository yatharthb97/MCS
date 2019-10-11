//Main program

//Preprocessors
#include<iostream>
using namespace std;
#include<fstream>
#include<sstream>
#include "box.h"
#include "runparam.h"
#include "log.h"
#include <chrono>
#include <ctime> 

#define RunID 5

void Render(Box &b, const char* filename);

int main()
{
	auto start = std::chrono::system_clock::now();
	 std::time_t start_time = std::chrono::system_clock::to_time_t(start);


	cout<<"Welocme Message!"<<endl;
	std::ostringstream o;
	o<<"Run ID: "<<RunID<<"  Time of initiation: "<< std::ctime(&start_time)<<std::endl;
	fstream m;
	m.open("./Output/log.txt", ios::app);
	m<<o.str();
	m.close();
	m.open("./Output/error.txt", ios::app);
	m<<o.str();
	m.close();
	cout<<o.str();


//Create Box
Log boxdes;
Box b(1000,5);
Render(b, "./Output/initial.txt");

for(int i = 0; i<1000; i++)
{
b.trialPos();
}
Render(b, "./Output/final.txt");
std::ostringstream la;
la<<"Accepted Moves: "<<b.countAccept()<<"  Rejected Moves: "<<b.countReject()<<endl;
Log last;
last.logoutput("main.cpp", la.str(), true);
la<<"Final Energy: "<<b.getEnergy()<<endl;
last.logoutput("main.cpp", la.str(), true);

}//End of Main classs


void Render(Box &b, const char* filename)
{
	fstream rend;
	rend.open(filename, ios::out);
	int count = b.getCount();
	for(unsigned int i= 0; i<count; i++)
	{
	rend<<b.PassPartlist().at(i).getPosition().infoRaw()<<std::endl;
	}
	rend.close();
}
/*Metropolis
{
	//Select particle at random from the container
	//Give trial new position
	//Give trial orientation
	//Calculate the energy - LJ loop
	//Acceptance conditions - Probablity distibution
	//Accept trial move - b.partlist[i].translate();

}*/