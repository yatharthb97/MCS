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
#include <sys/stat.h>
//#include"file.h"

void Render(Box &b, const char* filename);
//void setTermPath(string, const char*);
//void ReadInitText();

int main(int argc, char** argv)
{
	static int arg2=0;
	static double RunID;

	if((argv[1]!= "set") && (argv[1]!= "reset") && (argv[1]!= "noincrement"))
	{
		
		//cout<<"Invlid arguements."<<endl<<"Program terminated with exit(1)."<<endl;
		RunID = -1;

	}
	
	else if(argv[1]== "set")
	{
		ofstream f;
		f.open(".RunID.xxx",ios::out);
		f<<argv[2]<<endl;
		f.close();
		ifstream  ff(".RunID.xxx",ios::in);
		char runid;
		ff>>runid;
		ff.close();
		cout<<"RunID is set to: "<<runid<<endl;
		RunID = (double)runid - 48;
		arg2 = 1;

	}

	else if(argv[1]=="reset")
	{
		ofstream f(".RunID.xxx",ios::out);
		f<<"0"<<endl;
		f.close();
		ifstream  ff(".RunID.xxx",ios::in);
		char runid;
		ff>>runid;
		ff.close();
		cout<<"RunID is reset to: "<<runid<<endl;
		RunID = (double)runid - 48;
		int arg2 = 0;
	}

	else if(argv[1]=="noincrement")
	{
		ifstream f(".RunID.xxx",ios::in);
		int c,b;
		f>>c>>b;
		ofstream ff(".RunID.xxx",ios::out);
		ff<<c<<endl<<b+1<<endl;
		ff.close();
		ifstream fff(".RunID.xxx",ios::in);
		//int a,b;
		fff>>c>>b;
		fff.close();
		if(b<9){RunID = c+0.1*b;}
		else{RunID = c+0.01*b;}
		cout<<"RunID is set to: "<<RunID<<endl;
		int arg2 = 0;
	}
	//2.1

	//void ReadInitText();
	ifstream Reader("./Resource/inittext");
	
	std::string out;
	while(Reader.good())
	{
		std::string TempLine;                  //Temp line
	    std::getline (Reader , TempLine);        //Get temp line
	    TempLine += "\n";                      //Add newline character
	    
	    out += TempLine;                     //Add newline
	}
	Reader.close();
	std::cout<<out<<std::endl;
	//Intro Text

	//2.2 - Set RunID as shell variable
	std::ostringstream run;
	run<<"RunID="<<RunID;
	cout<<run.str()<<endl;
	//const char* command = run.c_str();
	system(run.str().c_str());
	cout<<"Shell Variable 'RunID' set to:";
	system("echo $RunID");
	//RunID set as shell variable
	cout<<"flag - shell variable set"<<endl;

	//3
	int sweeps = atoi(argv[2+arg2])-48;
	int checkpoint = atoi(argv[3+arg2])-48;
	//int loopfor = sweeps/checkpoint; //Loss of sweeps if the division is not an integer



	//4.1 - Call terminals
	/*if(RunParam::term2)
		{
			void setTermPath(string, const char*);
			setTermPath("======Commisioned for Logging======\n", "LogTerm");
		}*/

	//Terminal Paths Set

	//4.2 - Create log for RunID
	std::ostringstream runlog;
	runlog<<"RunID: "<<RunID;
	Log p; p.logoutput("runtime.cpp",runlog.str() ,true);

	cout<<"flag - shell variable set"<<endl;

	//4.3 - Set Up filesystem
	std::string parent = RunParam::ParentPathS;
	parent+="RunID_"; parent+=RunID;

	const int dir_err1 = mkdir(parent.c_str(), 0777);
	if (-1 == dir_err1)
	{
	    std::ostringstream o;
	    o<<"Filesystem not created! ==> Parent Directory RunID_"<<RunID;
	    Log l; l.logerror("runtime.cpp", o.str());
	}

	string plots = parent+"/Plots";
	const int dir_err2 = mkdir(plots.c_str(), 0777);
	if (-1 == dir_err2)
	{
	    Log l; l.logerror("runtime.cpp", "Filesystem not created! ==> 'Parent/Plots'");
	}

	string rawrend = parent+"/Raw_Render";
	const int dir_err3 = mkdir(rawrend.c_str(), 0777);
	if (-1 == dir_err3)
	{
	    Log l; l.logerror("runtime.cpp", "Filesystem not created! ==> 'Parent/Raw_Render'");
	}

	if((dir_err1 && dir_err2 && dir_err3)!=-1){Log l; l.logoutput("runtime.cpp", "Filesystem created without any errors.", true);}
	//File System Set
	cout<<"flag - file system set"<<endl;

	//5

	//ETRun Set
	double t1 = (RunParam::ETPSl)*sweeps;
	double t2 = (RunParam::ETPSu)*sweeps;
	std::ostringstream a;
	a<<"Estimated Time For Run:"<<t1<<"-"<<t2<<" seconds.";
	Log l; l.logoutput("runtime.cpp", a.str(), true);
	a.str(std::string());
	//Time Stamp - Start
	auto start = std::chrono::system_clock::now();
	std::time_t start_time = std::chrono::system_clock::to_time_t(start);
	a<<"Time of initiation: "<<std::ctime(&start_time);
	l.logoutput("runtime.cpp",a.str(), true);
	a.str(std::string());

	//Box Manager Called
	//BoxManager(sweeps, checkpoint); //Create Box Manager(int, int);
//Create Box
Log boxdes;
Box b(1000,5);
Render(b, "./Output/initial.txt");
double e1 = b.getEnergy();
//1
for(int i = 0; i<100; i++)
{
b.trialPos();
}
Render(b, "./Output/final1.txt");



	//Time Stamp - End
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end-start;
	std::time_t end_time = std::chrono::system_clock::to_time_t(end);
	a<<"Time of Completion: "<<std::ctime(&end_time)<<endl<<"Elapsed time: "<<elapsed_seconds.count()<<" seconds";
	l.logoutput("runtime.cpp",a.str(),true);

	//goto PreRunTime;
	/*char* RunID = argv[1];
	std::ostringstream run;
	run<<"RunID="<<RunID;
	const char* command = run.str().c_str();
	system(command);
	auto start = std::chrono::system_clock::now();
	 std::time_t start_time = std::chrono::system_clock::to_time_t(start);
	 Log::createTerm2();

	cout<<endl<<"________Particle Simulator________"<<endl<<"Weeks-Chadler-Anderson Repulsive Potential"<<endl<<"Particles: Point Particles"<<endl<<"-Yatharth Bhasin"<<endl<<endl;
	std::ostringstream o;
	o<<"Run ID: "<<RunID<<"   Time of initiation: "<< std::ctime(&start_time)<<std::endl;
	Log last;
	last.logoutput("main.cpp", o.str(),true);
	fstream m;
	m.open("./Output/error.txt", ios::app);
	m<<o.str();
	m.close();*/

/*BoxRun:
//Create Box
Log boxdes;
Box b(1000,5);
Render(b, "./Output/initial.txt");
double e1 = b.getEnergy();
//1
for(int i = 0; i<100; i++)
{
b.trialPos();
}
Render(b, "./Output/final1.txt");*/
/*//2
for(int i = 0; i<3000; i++)
{
b.trialPos();
}
Render(b, "./Output/final2.txt");
//3
for(int i = 0; i<3000; i++)
{
b.trialPos();
}
Render(b, "./Output/final3.txt");*/
//Time Calculation
/*auto end = std::chrono::system_clock::now();
std::chrono::duration<double> elapsed_seconds = end-start;
std::time_t end_time = std::chrono::system_clock::to_time_t(end);*/
////////////////////
//Con:

//std::ostringstream la;

///la<<"Run ID: "<<"RunID"<<"  Finished computation at " << std::ctime(&end_time)<<endl<< "Elapsed time: " << elapsed_seconds.count() << " seconds"<<endl;
/*la<<"Accepted Moves: "<<b.countAccept()<<"  Rejected Moves: "<<b.countReject()<<endl;
la<<"Accept/Reject Ratio: "<<b.getRatio()<<endl;
double e2 = b.getEnergy();
la<<"Final Energy: "<<e1<<endl;
la<<"Final Energy: "<<e2<<endl;
la<<"Energy Change: "<<e2-e1<<endl;
last.logoutput("main.cpp", la.str(), true);*/

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

/*void setTermPath(string s, const char* filename)
	{
	//Check Terminals
	system("ls /dev/pts/  | wc -l > '.temp_term.temp'");
	ifstream r;
	r.open(".temp_term.temp", ios::in);
	char p;
	r.read((char*)&p, sizeof(char));
	//cout<<"p "<<p<<endl;
	r.close();remove(".temp_term.temp");


	//cout<<"Make sure that there are no residual terminals open!"<<endl<<"Press any key to continue!"<<endl;
	//std::cin.get();
	system("gnome-terminal");
		int q = int(p) - 49;																																																																																										;
		//cout<<"q"<<q<<endl;
		char pq = q+48;
		//cout<<"pq "<<pq;
		std:: string tpath = "/dev/pts/";
		tpath.append(1,pq);
		//cout<<tpath<<endl;
		const char* tpath2 = tpath.c_str();
		ofstream f;
		f.open(tpath2);
		f<<"Path: "<<tpath2<<endl<<s<<endl;
		f.close();
		//cout<<tpath2<<endl;

		//Take arguement of a constchar filename
		//Call the File class and write the path to it.
		//return void
		//return(tpath2);
		//File log(filename, true, true, tpath);

}*/