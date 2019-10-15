#pragma once


#define EtaRep 0.25e-20
#define SigmaRep 1
#define CutOffRep 2



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
static bool term2;
static bool sysInterrupt;

//Rotation parameters
static double minRotor;
static double maxRotor;
static double resoRotor;
static bool MaxRot;


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

};//End of class RunParam

