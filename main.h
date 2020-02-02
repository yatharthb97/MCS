//main header file
#pragma once
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<cstring>
#include"log.h"
#include"runparam.h"
#include"box.h"
#include <sys/stat.h>


#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;


#include"file.h"
#include<thread>


//setparam - ReadArgs
void setParam(int &argc, char** &argv, bool &arg_run_counter, double &RunID, int &sweeps, int &checkpoints, int &threads, int &particles)
{
	for(int i=0; i<argc; i++)
	{
		std::string s = "set"; 
		if(argv[i]==s && i<argc)
		{
			RunID = atoi(argv[i+1]);
			ofstream f(".RunID.simx", ios::out | std::ofstream::trunc);
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
		if(argv[i]==s && i<argc)
		{
			RunID = 0;
			ofstream f(".RunID.simx", ios::out | std::ofstream::trunc);
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
		if(argv[i]==s && i<argc)
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
		if(argv[i]==s && i<argc)
		{
			sweeps = atoi(argv[i+1]);
		}


		s="checkpoints";
		if(argv[i]==s && i<argc)
		{
			checkpoints=atoi(argv[i+1]);
		}

		s="threads";
		if(argv[i]==s && i<argc)
		{
			threads=atoi(argv[i+1]);
		}

		s="particles";
		if(argv[i]==s && i<argc)
		{
			particles = atoi(argv[i+1]);
		}
	}

	if(!arg_run_counter)
	{
		ifstream f(".RunID.simx", ios::in);
			f>>RunID;
			f.close();
			RunID = int(RunID)+1;
			ofstream ff(".RunID.simx",ios::out | std::ofstream::trunc);
			ff<<RunID;
			ff.close();
			cout<<"RunID is set to: "<<RunID<<endl;
			arg_run_counter = true;
	}
}
//End of setParam


//PrintInitText - Print Welcome Text
std::string PrintInitText()
{
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
	return out;
}
//End of Print Welcome Text


//dirExists
/******************************************************************************
 * Checks to see if a directory exists. Note: This method only checks the
 * existence of the full path AND if path leaf is a dir.
 *
 * @return  >0 if dir exists AND is a dir,
 *           0 if dir does not exist OR exists but not a dir,
 *          <0 if an error occurred (errno is also set)
 *****************************************************************************/
int dirExists(const char* const path)
{
    struct stat info;

    int statRC = stat( path, &info );
    if( statRC != 0 )
    {
        if (errno == ENOENT)  { return 0; } // something along the path does not exist
        if (errno == ENOTDIR) { return 0; } // something in path prefix is not a dir
        return -1;
    }

    return ( info.st_mode & S_IFDIR ) ? 1 : 0;
}
//End of dirExists

//setFileSystem
void setFileSystem(double RunID, std::string &parent, int threads)
{
	parent = RunParam::ParentPathS; 
	ostringstream mkd;
	mkd<<parent<<"RunID_"<<RunID;
	//parent+="RunID_"; parent+=(char)RunID;
	int checkdir = dirExists(mkd.str().c_str());
	while(checkdir>0)
	{
		mkd<<"_1";
		checkdir = dirExists(mkd.str().c_str());
	}
	parent = mkd.str();
	/*Log mkdr; mkdr.logoutput("main2.cpp", "Parent Path of Filesystem:"+parent, true);*/
	


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

	string rawrend = parent+"/Raw_Render/";
	const int dir_err3 = mkdir(rawrend.c_str(), 0777);
	if (-1 == dir_err3)
	{
	    Log l; l.logerror("runtime.cpp", "Filesystem not created! ==> 'Parent/Raw_Render'");
	}

	bool threadfileerror = false;
	if(threads>1)
	{
		for(int i = 0; i<threads; i++)
		{

			std::ostringstream thr;
			thr<<rawrend<<i;
			//string thr = rawrend+i;
			const int dir_err = mkdir(thr.str().c_str(), 0777);
			if (-1 == dir_err)
			{
			    std::ostringstream o;
			    o<<"Filesystem not created! ==> Parent Directory/Raw_Render_Thread_"<<i;
			    Log l; l.logerror("runtime.cpp", o.str());
			    threadfileerror = true;

		}	}
	}

	if((dir_err1!=-1) && (dir_err2!=-1) && (dir_err3!=-1) &&(threadfileerror==false)){Log l; l.logoutput("runtime.cpp", "Filesystem created without any errors.", true);}
	else{Log l; l.logerror("runtime.cpp", "Filesystem created with errors.End Program to resolve.");}
	//File System set
}
//End of setFileSystem

//setTermPath - Set Paths for extra terminals
void setTermPath(std::string s, const char* filename)
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
		//const char* tpath2 = tpath.c_str();
		ofstream f;
		f.open(tpath);
		f<<PrintInitText()<<endl<<"Path: "<<tpath<<endl<<s<<endl;
		f.close();
		//cout<<tpath2<<endl;

		//Take arguement of a constchar filename
		//Call the File class and write the path to it.
		//return void
		//return(tpath2);
		static SetFile logt(filename, true, true, tpath);
		Log t_path; t_path.logoutput("main.h/setTermPath()", "TermPath Set: "+ tpath, true);
}
//End of setTerminalPath




//Render - Create XYZ Plots Raw
void Render(Box &b, const char* filename)
{
	fstream rend;
	rend.open(filename, ios::out);
	if(rend.is_open())
	{
		int count = b.count;
		for(unsigned int i= 0; i<count; i++)
		{
		rend<<b.partlist.at(i).getPosition().infoRaw()<<std::endl;
		}
		rend.close();
	}
	else{
		Log rend;
		rend.logerror("main.cpp/Rend(int, int)", std::string(filename) +" :file not open!");
	}

}
//End of Render

//AutoPlot - Run Gnuplot Script to plot XYZ Plots
void AutoPlot(string filename, string filename2, int sweeps, double energy)
{
	std::ostringstream command;
    command<<"./autoplot.gnu "<<filename<<" "<<filename2<<" "<<sweeps<<" "<<energy;
    system(command.str().c_str());
    std::ostringstream l;
    l<<"Autoplot render after sweeps: "<<sweeps<<": actuated.";
    Log autoplot; autoplot.logoutput("main.h/AutoPlot()",l.str() , true);
}
//End of AutoPlot

//PlotEnergyFlux - Run Gnuplot Script to render energyflux plots
void PlotEnergyFlux(int RunID, string ParentPath)
{
	std::ostringstream opfile;
	opfile<<ParentPath<<"/Plots/";
	std::ostringstream infile;
	infile<<ParentPath<<"/energyflux.dat";
	std::ostringstream command;
	command<<"./fluxplot.gnu "<<infile.str()<<" "<<opfile.str()<<" "<<RunID;
	system(command.str().c_str());
}
//End of PlotEnergyFlux

//TimeStamp - Create TimeStamps
std::time_t TimeStamp()
{
	auto stamp = std::chrono::system_clock::now();
	std::time_t stamp_time = std::chrono::system_clock::to_time_t(stamp);
	return(std::time_t (stamp_time));
}
//End of TimeStamp

//Scheduler - Event Scheduler
bool Scheduler(Box &b)
{
	bool ret = true;
	int addpart_num = RunParam::AddPartRate*10;
	int rmpart_num = RunParam::RmPartRate*10;
	int mutpart_num = RunParam::MutaPartRate*10;
	extern int roll();
	int eventid =  roll();

	if(eventid <= RunParam::AddPartRate && RunParam::GrandCanonical)
	{
		int counter = roll(); int type;
		if(counter<=RunParam::AddRate1){type = 1;}
		if(counter > RunParam::AddRate1 && counter <= RunParam::AddRate1 + RunParam::AddRate2) {type = 2;}
		b.AddParticle(type);
		ret = true;
	}

	else if(eventid > RunParam::AddPartRate && eventid <= (RunParam::AddPartRate + RunParam::RmPartRate) && RunParam::GrandCanonical)
	{
		b.RemoveRndParticle();
		ret=true;
	}

	else if(eventid > (RunParam::AddPartRate + RunParam::RmPartRate) && eventid <= (RunParam::AddPartRate + RunParam::RmPartRate + RunParam::MutaPartRate))
	{
		b.MutateRndm();
		ret=true;
	}

	return ret;
}
//End of Scheduler

//The BoxManager - Create Box
void BoxManager(std::string ParentPath, int RunID, int scope_particles, int scope_sweeps, int scope_checkpoints, int threads, int i)
{

	int loop_runs = scope_sweeps/scope_checkpoints;
	Box b(scope_particles);
	double e1 = b.energy;

	//Initial Render
	std::ostringstream filename;
	if(threads>1) {filename<<ParentPath<<"/Raw_Render/"<<i<<"/"<<0;}
	else {filename<<ParentPath<<"/Raw_Render/"<<0;}
	Render(b, filename.str().c_str());

	if(RunParam::autoplotraw)
	{
		std::ostringstream filename2;
		if(threads>1) {filename2<<ParentPath<<"/Plots/"<<i<<"/"<<0;}
		else {filename2<<ParentPath<<"/Plots/"<<0;}
		AutoPlot(filename.str(), filename2.str(),0, b.energy);
	}
	cout<<"Rendered: "<<0<<"  "<<flush;
	//End of Initial Render

	//Initial timestamp
	std::ostringstream t_stamp;
	std:: time_t start_time = TimeStamp();
	t_stamp<<"Thread: "<<i<<" Time of Initiation: "<< std::ctime(&start_time)<<std::endl;
	Log tstamp; tstamp.logoutput("main.h", t_stamp.str(), true);

	//BoxManager Main Loop
	int energyrendercount = 0; //For EnergyFlux File
	int counter = 0; //Overall Sweep Counter
	for(int k = 0; k<scope_checkpoints; k++)
	{
		for(int j=0; j<loop_runs; j++)
		{
			//if(Scheduler(b))
			b.TrialMove();
			
			energyrendercount++;
			counter++;

			//EnergyFlux Graphs Render
			if(energyrendercount>=RunParam::PlotEnergyAfter)
			{
				//b.UpdateEnergy();
				std:: time_t now_time = TimeStamp();
				double elapsed_seconds = double(now_time - start_time);
				b.Graph(ParentPath, counter, elapsed_seconds);
				energyrendercount=0;
			}
			//End of EnergyFlux Graphs Render
		}

		//XYZ Render
		std::ostringstream filename;
		if(threads>1) {filename<<ParentPath<<"/Raw_Render/"<<i<<"/"<<k+1;}
		else {filename<<ParentPath<<"/Raw_Render/"<<k+1;}
		Render(b, filename.str().c_str());
		if(RunParam::autoplotraw)
		{
			std::ostringstream filename2;
			if(threads>1) {filename2<<ParentPath<<"/Plots/"<<i<<"/"<<k+1;}
			else {filename2<<ParentPath<<"/Plots/"<<k+1;}
			AutoPlot(filename.str(), filename2.str(),counter, b.energy);
		}
		void ParticleRenderTCLTk(std::vector<Particle> &partlist);
		ParticleRenderTCLTk(b.partlist);
		cout<<"Rendered: "<<k+1<<"  "<<flush;
		//End of XYZ Render
	}

	//Output of Vital Information
	double e2 = b.energy;
	std:: time_t end_time = TimeStamp();
	double elapsed_seconds = double(end_time - start_time);
	////std::chrono::duration<double> elapsed_seconds = end-start;
	
	std::ostringstream la;
	la<<"Run ID: "<<RunID<<std::endl;
	la<<"Thread ID: "<<i<<endl;
	la<<"Time of Completion: "<< std::ctime(&end_time)<<std::endl;
	la<<"Elapsed Time: "<< elapsed_seconds<<" seconds"<<endl;
	la<<"Accepted Moves: "<<b.ACCEPT<<"  Rejected Moves: "<<b.REJECT<<endl;
	la<<"Acceptance Ratio: "<<b.getRatio()<<endl;
	la<<"Initial Energy: "<<e1<<endl;
	la<<"Final Energy: "<<e2<<endl;
	la<<"Energy Change: "<<e2-e1<<endl<<endl<<endl;
	Log last;
	last.logoutput("main.cpp", la.str(), true);

	PlotEnergyFlux(RunID, ParentPath);
}
//End of BoxManager


