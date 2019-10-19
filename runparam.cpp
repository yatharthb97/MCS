#include "runparam.h"


bool RunParam::RUN = true;
double RunParam::StepSize = 0.5000000;
double RunParam::MinStepSize = 0.1000000;
int RunParam::LJARatio = 20;
double RunParam::BoxSize = 5.0000000;
//Particle::EDGE = 5.0000000; //Streamline
bool RunParam::MaxStep = true;


//Rotation parameters
double RunParam::minRotor=0.000000;
double RunParam::maxRotor=0.000000;
double RunParam::resoRotor=0.000000;
bool RunParam::MaxRot= true;



//Log Parameters
bool RunParam::term2 = false;
bool RunParam::sysInterrupt = false;
const char* RunParam::LogOutput = "./Output/log.txt";
const char* RunParam::LogErrorOut = "./Output/error.txt";


//
const char* RunParam::ParentPath = "/home/yatharth1997/";
std::string RunParam::ParentPathS = "/home/yatharth1997/";



//System Param

//Estimated Time Per Sweep
double RunParam::ETPSl = 0.15;
double RunParam::ETPSu = 0.20;