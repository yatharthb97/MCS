#include "runparam.h"
#include"particle.h"


//Particle Types:

#define T_SC_1CP 1
//Spherocylinder with 1 chiral patch
//Particle Parrameters
double Patch::width = 1.000000;
double Particle::L = 4*SigmaAtrr;
double Particle::D = SigmaAtrr;





bool RunParam::RUN = true;
double RunParam::StepSize = 0.5000000;
double RunParam::MinStepSize = 0.1000000;
int RunParam::LJARatio = 50;
double RunParam::BoxSize = 5.0000000;
//Particle::EDGE = 5.0000000; //Streamline
bool RunParam::MaxStep = false;


//Rotation parameters
double RunParam::minRotor=0.500000;
double RunParam::maxRotor=1.000000;
double RunParam::resoRotor=0.000000;
bool RunParam::MaxRot= true;



//Log Parameters
bool RunParam::term2 = false;
bool RunParam::sysInterrupt = false;
const char* RunParam::LogOutput = "./Output/log.txt";
const char* RunParam::LogErrorOut = "./Output/error.txt";


//
const char* RunParam::ParentPath = "/home/yatharth1997/Runs/";
std::string RunParam::ParentPathS = "/home/yatharth1997/Runs/";
bool RunParam::printRunParamData = true;


//System Param

//Estimated Time Per Sweep
double RunParam::ETPSl = 0.15;
double RunParam::ETPSu = 0.20;



