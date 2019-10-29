#include"main.h"
#include<thread>

//Global variables with default parameters
static bool arg_run_counter = false;
static double RunID = -1;
static int sweeps = 1000;
static int checkpoints = 1;
static int threads = 1;
static int particles = 100;
static std::string ParentPath = "";

int main(int argc, char** argv)
{
	/*static bool arg_run_counter = false;
	static double RunID = -1;
	static int sweeps = 1000;
	static int checkpoints = 1;
	static int threads = 1;*/
	
	//Check Arguements
	/*cout << "You have entered " << argc 
         << " arguments:" << endl; 
  
    for (int i = 0; i < argc; ++i) 
        cout << argv[i] << endl;*/ 


//Read Arguements
setParam(argc, argv, arg_run_counter, RunID, sweeps, checkpoints, threads, particles);

//Print Initial Text
cout<<PrintInitText()<<endl;


//Call terminals
if(RunParam::term2)
	{
		setTermPath("======Commisioned for Logging======\n", "LogTerm");
	}
//Terminal Paths Set

	//Print System Parameters
	std::ostringstream runlog;
	runlog<<"RunID: "<<RunID<<" (default: -1)"<<endl<<"Sweeps: "<<sweeps<<" (default: 1000)"<<endl;
	runlog<<"Checkpoint: "<<checkpoints<<" (default: 1)"<<endl<<"Threads: "<<threads<<" (default: 1)"<<endl;
	runlog<<"Particles in Box: "<<particles<<" (default: 100)";
	Log p; p.logoutput("runtime.cpp",runlog.str() ,true);


//4.3 - Set Up filesystem
setFileSystem(RunID, ParentPath);
Log mkdr; mkdr.logoutput("main2.cpp", "Parent Path of Filesystem:"+ParentPath, true);
//Filesystem Set

//ETRun Set
double t1 = (RunParam::ETPSl)*sweeps;
double t2 = (RunParam::ETPSu)*sweeps;
std::ostringstream a;
a<<"Estimated Time For Run:"<<t1<<" - "<<t2<<" seconds per thread."<<endl<<"Total time: "<<t1*threads<<" - "<<t2*threads<< "seconds."<<endl;
Log l; l.logoutput("runtime.cpp", a.str(), true);

//Start Simulation run
//if()
//std::vector<thread> t;

/*for(unsigned int i=0; i<threads;i++)
	t.push_back(BoxManager(ParentPath, RunID, particles, sweeps, checkpoints, i));
	Log threadlog; threadlog.logoutput("Main Function", "Thread Created: Thread "+i,true);

}*/
int i = 1;
BoxManager(ParentPath, RunID, particles, sweeps, checkpoints, i);

/*for(unsigned int i=0; i<threads;i++)
{
	t.at(i).join();
	Log threadlog; threadlog.logoutput("Main Function", "Thread Ended: Thread "+i,true);

}*/

}//End of Main


