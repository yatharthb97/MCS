#pragma once
#include<iostream>

//Macro Definations
#define EtaRep 0.5 //Strength of Repulsive Potential
#define SigmaRep 0.05 //Sigma of Repulsive Potential
#define CutOffRep 1 //CutOff distance of Repulsive Potential
#define EtaAtrr -1 //Strength of Repulsive Potential
#define SigmaAtrr 0.0005 //Sigma of Repulsive Potential


class RunParam{

public:

//Monte Carlo Parameters
double static BoxSize;
bool static GrandCanonical;
int static LJARatio; //Expressed in Percentage
double static MaxEnergyFluctuation; //Expressed in Percentage
int static PlotEnergyAfter;
//Monte Carlo Parameters

//Recipie - Expressed in percentages
//Initial Recipie
//**Exhaustive Rates**
int static SC_1CP_recipie; //Type 1
int static SC_1TP_recipie; //Type 2
//Initial Recipie

//Recipie - Mutators
//**Absolute Rates** - Relates per number of Sweeps 
double static AddPartRate;
double static RmPartRate;
double static MutaPartRate;
//Recipie - Mutators 

//Addition and Removal Rates
//**Exhaustive Rates**
float static AddRate1;
float static AddRate2;
//**Absolute Rates**
double static RmPartTrialAcceptRate;
//Addition and Removal Rates

//Recipie-Mutation Rates
//**Absolute Rates**
float static MutaMatrix[2][2]; //TotalSpecies*TotalSpecies
int static TotalSpecies;

//Translation Switches
double static StepSize;
double static MinStepSize;
bool static MaxStep;
//Translation Switches


//Rotation switches
double static minRotor;
double static maxRotor;
double static resoRotor; //Not used anywhere
bool static MaxRot;
//Rotation switches


//Log Parameters
bool static term2;
bool static sysInterrupt;
static const char* LogOutput;
static const char* LogErrorOut;
//Estimated Time Per Sweep for logging
double static ETPSl;
double static ETPSu;
//Log Parameters


//Environmental Setup Board
bool static RUN;
static const char*  ParentPath;
std::string static ParentPathS;
bool static printRunParamData;
bool static autoplotraw;
bool static UseSysEntropy;
//Environmental Setup Board;



/*void printRunParamData()
{
	ostringstream paramdat;
	paramdet<<
}*/
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