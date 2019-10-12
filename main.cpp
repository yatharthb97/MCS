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
#include<cstring>
#include<string>

void Render(Box &b, const char* filename);

int main(int argc, char** argv)
{
	char* RunID = argv[1];
	std::ostringstream run;
	run<<"RunID="<<RunID;
	const char* command = run.str().c_str();
	system(command);
	auto start = std::chrono::system_clock::now();
	 std::time_t start_time = std::chrono::system_clock::to_time_t(start);


	cout<<endl<<"________Particle Simulator________"<<endl<<"Weeks-Chadler-Anderson Repulsive Potential"<<endl<<"Particles: Point Particles"<<endl<<"-Yatharth Bhasin"<<endl<<endl;
	std::ostringstream o;
	o<<"Run ID: "<<RunID<<"   Time of initiation: "<< std::ctime(&start_time)<<std::endl;
	Log last;
	last.logoutput("main.cpp", o.str(),true);
	fstream m;
	m.open("./Output/error.txt", ios::app);
	m<<o.str();
	m.close();


//Create Box
Log boxdes;
Box b(1000,5);
Render(b, "./Output/initial.txt");
double e1 = b.getEnergy();
//1
for(int i = 0; i<1000; i++)
{
b.trialPos();
}
Render(b, "./Output/final1.txt");
//2
for(int i = 0; i<1000; i++)
{
b.trialPos();
}
Render(b, "./Output/final2.txt");
//3
for(int i = 0; i<1000; i++)
{
b.trialPos();
}
Render(b, "./Output/final3.txt");
//Time Calculation
auto end = std::chrono::system_clock::now();
std::chrono::duration<double> elapsed_seconds = end-start;
std::time_t end_time = std::chrono::system_clock::to_time_t(end);
////////////////////


std::ostringstream la;

la<<"Run ID: "<<RunID<<"  Finished computation at " << std::ctime(&end_time)<<endl<< "Elapsed time: " << elapsed_seconds.count() << " seconds"<<endl;
la<<"Accepted Moves: "<<b.countAccept()<<"  Rejected Moves: "<<b.countReject()<<endl;
la<<"Accept/Reject Ratio: "<<b.getRatio()<<endl;
double e2 = b.getEnergy();
la<<"Final Energy: "<<e2<<endl;
la<<"Energy Change: "<<e2-e1<<endl;
last.logoutput("main.cpp", la.str(), true);

cout<<"-------------------Termination----------------------"<<endl;

//system("gnuplot | load './gnuplot_render.gp' ");
}//End of Main classs


void Render(Box &b, const char* filename)
{
	fstream rend;
	rend.open(filename, ios::out);
	if(rend.is_open())
	{
		int count = b.getCount();
		for(unsigned int i= 0; i<count; i++)
		{
		rend<<b.PassPartlist().at(i).getPosition().infoRaw()<<std::endl;
		}
		rend.close();
	}
	else{
		Log rend;
		rend.logerror("main.cpp/Rend(int, int)", std::string(filename) +" :file not open!");
	}
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