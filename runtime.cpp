
//Preprocessors
#include <sys/stat.h>





//Runtime Function




PreRunTime:


	//Sequence of operation
	//0. Intro Text
	//1. Check for parameter validity in args[]
	//2. Write to the RunID file and output intro text 2
	//3. Read and define the operation parameters
	//4. Setup filesystem
	//5. Create box and return to the main program
	//0
	//Initial Intro text

	//1
	if(argv[1]!= 'set' || argv[1]!= 'reset' || argv[1]!= 'noincrement'){cout<<"Invlid arguements."<<"Program terminated with exit(1)."<<endl;exit(1);}
	else-if(argv[1]== 'set')
	{
		ofstream f;
		f.open(".RunID.xxx",ios::out);
		f<<argv[2]<,endl;
		f.close();
		ifstream  ff(".RunID.xxx",ios::in);
		char runid;
		ff>>runid;
		ff.close();
		cout<<"RunID is set to: "<<runid<<endl;
		double RunID = (double)runid - 48;
		int arg2 = 1;

	}

	else-if(argv[1]=='reset')
	{
		ofstream f(".RunID.xxx",ios::out);
		f<<"0"<<endl;
		f.close();
		ifstream  ff(".RunID.xxx",ios::in);
		char runid;
		ff>>runid;
		ff.close();
		cout<<"RunID is reset to: "<<runid<<endl;
		double RunID = (double)runid - 48;
		int arg2 = 0;
	}

	else-if(argv[1]=='noincrement')
	{
		ifstream f(".RunID.xxx",ios::in);
		int a,b;
		f>>a>>b;
		ofstream ff(".RunID.xxx",ios::out);
		ff>>a>>endl>>b+1>>endl;
		ff.close();
		cout<<"RunID is reset to: "<<runid<<endl;
		ifstream  fff(".RunID.xxx",ios::in);
		int a,b;
		fff>>a>>b;
		fff.close();
			if(b<9){double RunID = a+0.1*b;}
			else{double RunID = a+0.01*b;}
		cout<<"RunID is set to: "<<runid<<endl;
		int arg2 = 0;
	}
	//2.1
	//Intro Text

	//2.2 - Set RunID as shell variable
	string run;
	run = "RunID="+RunID;
	const char* command = run.c_str();
	system(command);
	cout<<"Shell Variable 'RunID' set to:"
	system("echo $RunID");
	//RunID set as shell variable



	//3
	int sweeps = argv[2+arg2];
	int checkpoint = argv[3+arg2];
	//int loopfor = sweeps/checkpoint; //Loss of sweeps if the division is not an integer


	//4.1 - Call terminals
	if(RunParam::is_term2)
		{
			void setTermPath(string, const char*);
			setTermPath("======Commisioned for Logging======\n", LogTerm);
		}

	//Terminal Paths Set

	//4.2 - Create log for RunID
	Log p; p.logoutput("runtime.cpp", "RunID: ")

	//4.3 - Set Up filesystem
	string parent = RunParam::ParentPathS;
	parent+="RunID_"; parent+=RunID;

	const int dir_err1 = mkdir(parent.c_str(), 0777);
	if (-1 == dir_err1)
	{
	    Log l; l.logerror("runtime.cpp", "Filesystem not created! ==> Parent Directory RunID_"+RunID);
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

	//5

	//ETRun Set
	double t1 = (RunParam::ETPSl)*sweeps;
	double t2 = (RunParam::ETPSu)*sweeps;
	Log l; l.logoutput("runtime.cpp", "Estimated Time For Run:"+t1+"-"t2+" seconds.", true);

	//Time Stamp - Start
	auto start = std::chrono::system_clock::now();
	std::time_t start_time = std::chrono::system_clock::to_time_t(start);
	l.logoutput("runtime.cpp","Time of initiation: "+std::ctime(&start_time), true);

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
	l.logoutput("runtime.cpp","Time of Completion: "+std::ctime(&end_time), true);
	l.logoutput("runtime.cpp", "Elapsed time: "+elapsed_seconds.count()+" seconds",true);


	//Return to main
	//goto main2:
goto Con;