#pragma once


#define EtaRep 0.25e-20
#define SigmaRep 1
#define CutOffRep 3



class RunParam{

public:
//Member VAriables
static bool RUN;
static double StepSize;
static int LJARatio;
static double BoxSize;
static bool MaxStep;

//Log File Config
static const char* LogOutput;
static const char* LogErrorOut;



//1
//Accessor - checkRUN()
//Switch to indicate if the program is running
bool volatile checkRUN()
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

//3
volatile static int checkLJARatio()
{
	return LJARatio; //Acceptance of higher energy configuration
}

//4
volatile double checkBoxSize()
{
	return BoxSize;
}
//5
const char* fileConfig(int i)
{
	switch(i)
	{	
		//Log Files:: demanded by class Log
		case 1:	return(LogErrorOut); break; //For error log 
		case 2: return(LogOutput); break; //For output log
	}
}

};//End of class RunParam

