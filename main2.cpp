#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<cstring>
#include"log.h"
#include"runparam.h"
#include <sys/stat.h>

using namespace std;



int main(int argc, char** argv)
{
	bool arg_run_counter = false;
	static double RunID = -1;
	static int sweeps = 1000;
	static int checkpoints = 1;
	static int threads = 1;
	
	//Check Arguements
	/*cout << "You have entered " << argc 
         << " arguments:" << endl; 
  
    for (int i = 0; i < argc; ++i) 
        cout << argv[i] << endl;*/ 


	for(int i=0; i<argc; i++)
	{
		std::string s = "set"; 
		if(argv[i]==s)
		{
			RunID = atoi(argv[i+1]);
			ofstream f(".RunID.simx", ios::out);
			f<<RunID;
			f.close();
			ifstream ff(".RunID.simx",ios::in);
			double RunID2;
			ff>>RunID2;
			ff.close();
			cout<<"RunID is set to: "<<RunID2<<endl;
			arg_run_counter = true;

		}
		s = "reset";
		if(argv[i]==s)
		{
			RunID = 0;
			ofstream f(".RunID.simx", ios::out);
			f<<RunID;
			f.close();
			ifstream ff(".RunID.simx",ios::in);
			double RunID2;
			ff>>RunID2;
			ff.close();
			cout<<"RunID is reset to: "<<RunID2<<endl;
			arg_run_counter = true;
		}
		s = "noincrement";
		if(argv[i]==s)
		{
			ifstream f(".RunID.simx", ios::in);
			f>>RunID;
			f.close();
			RunID+=0.1;
			ofstream ff(".RunID.simx",ios::out);
			ff<<RunID;
			ff.close();
			cout<<"RunID is set to: "<<RunID<<endl;
			arg_run_counter = true;
		}


		s="sweeps";
		if(argv[i]==s)
		{
			sweeps = atoi(argv[i+1])-48;
		}


		s="checkpoints";
		if(argv[i]==s)
		{
			checkpoints=atoi(argv[i+1])-48;
		}

		s="threads";
		if(argv[i]==s)
		{
			threads=atoi(argv[i+1])-48;
		}
	}

	if(!arg_run_counter)
	{
		ifstream f(".RunID.simx", ios::in);
			f>>RunID;
			f.close();
			RunID+=1;
			ofstream ff(".RunID.simx",ios::out);
			ff<<RunID;
			ff.close();
			cout<<"RunID is set to: "<<RunID<<endl;
			arg_run_counter = true;
	}

	//Call terminals
	/*if(RunParam::term2)
		{
			void setTermPath(string, const char*);
			setTermPath("======Commisioned for Logging======\n", "LogTerm");
		}*/

	//Terminal Paths Set


	//Print Initial Text
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


	//Print System Parameters
	std::ostringstream runlog;
	runlog<<"RunID: "<<RunID<<endl<<"Sweeps: "<<sweeps<<" (default: 1000)"<<endl;
	runlog<<"Checkpoint: "<<checkpoints<<" (default: 1)"<<endl<<"Threads: "<<threads<<" (default: 1)"<<endl;
	Log p; p.logoutput("runtime.cpp",runlog.str() ,true);

	

	//4.3 - Set Up filesystem
	std::string parent = RunParam::ParentPathS;
	ostringstream mkd;
	mkd<<parent<<"RunID_"<<RunID;
	//parent+="RunID_"; parent+=(char)RunID;
	parent = mkd.str();

	const int dir_err1 = mkdir(mkd.str().c_str(), 0777);
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


}//End of Main
