#include "runparam.h"
#include"particle.h"


//Macro Definations
#define EtaRep 0.25e-20
#define SigmaRep 1
#define CutOffRep 2
#define EtaAtrr 1
#define SigmaAtrr 0.25e-20

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
int RunParam::LJARatio = 20;
double RunParam::BoxSize = 5.0000000;
//Particle::EDGE = 5.0000000; //Streamline
bool RunParam::MaxStep = false;


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



