#pragma once
#include<iostream>




class RunParam{

public:
//Member VAriables
static bool RUN;
static double StepSize;
static double MinStepSize;
static int LJARatio;
static double BoxSize;
static bool MaxStep;

//Log File Config
static const char* LogOutput;
static const char* LogErrorOut;
const char* termpath;
static bool term2;
static bool sysInterrupt;

//Rotation parameters
static double minRotor;
static double maxRotor;
static double resoRotor;
static bool MaxRot;


static const char* ParentPath;
static std::string ParentPathS;
static double ETPSl;
static double ETPSu;

/*RunParam()
{
extern const char* setTermPath();
termpath = setTermPath();
}*/
//1
//Accessor - checkRUN()
//Switch to indicate if the program is running
inline bool volatile checkRUN()
{
	return RUN;
}

//2
//Accessor - checkStepSize()
//Returns the max StepSize
volatile double checkStepSize()
{
	return StepSize;
}

inline volatile double checkMinStepSize()
{
	return MinStepSize;
}

//3
inline volatile static int checkLJARatio()
{
	return LJARatio; //Acceptance of higher energy configuration
}

//4
inline volatile double checkBoxSize()
{
	return BoxSize;
}
//5
inline const char* fileConfig(int i)
{
	switch(i)
	{	
		//Log Files:: demanded by class Log
		case 1:	return(LogErrorOut); break; //For error log 
		case 2: return(LogOutput); break; //For output log
		//case 3: {return(termpath); std::cout<<"termpath returned";break;} //For Terminal 2
	}
}

//6

inline volatile double RotParam(int i)
{
	switch(i)
	{
		case 1: return(minRotor); break;
		case 2: return(maxRotor); break;
		case 3: return(resoRotor); break;
	}
}

inline volatile bool isMaxRot()
{
	return MaxRot;
}

inline volatile bool checkTerm2()
{
	return term2;
}
	
inline volatile bool checkInterrupt()
{
	return sysInterrupt;
}

/*inline static void set()
{
	extern void setTP();
	termpath = setTP();
}*/

/*inline void createTerm2()
	{
		
	//Check Terminals
	system("ls /dev/pts/  | wc -l > '.temp_term.temp'");
	ifstream r;
	r.open(".temp_term.temp", ios::in);
	char p;
	r.read((char*)&p, sizeof(char));
	cout<<"p "<<p<<endl;
	r.close();remove(".temp_term.temp");


	//cout<<"Make sure that there are no residual terminals open!"<<endl<<"Press any key to continue!"<<endl;
	//std::cin.get();
	system("gnome-terminal");
		int q = int(p) - 48;																																																																																										;
		//cout<<"q"<<q<<endl;
		std:: string tpath = "/dev/pts/";
		tpath.append(1,p);
		cout<<tpath<<endl;
		extern void setTermPath(const char*);
		setTermPath(tpath.c_str());
		//termpath = tpath.c_str();
		cout<<termpath;
		
		ofstream t;
		t.open(termpath);

		t<<"----------------Commisioned for Logging-----------------"<<endl;
		t.close();
		
	}*/

};//End of class RunParam


/*class LogParam
{

//Log File Config
static const char* LogOutput;
static const char* LogErrorOut;
const char* termpath;
static bool term2;
static bool sysInterrupt;};*/