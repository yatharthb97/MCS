#include "runparam.h"
#include"particle.h"


//Particle Types:

#define T_SC_1CP 1
//Spherocylinder with 1 chiral patch
//Particle Parrameters
double Patch::width = 1.000000;
double Particle::L = 4*SigmaAtrr;
double Particle::D = SigmaAtrr;


//Recipie - Expressed in percentages
//Type 1
int RunParam::SC_1CP_recipie = 90;
//Type 2
int RunParam::SC_1TP_recipie = 10;


//Recipie-Mutation Rates
int RunParam::TotalSpecies = 2;
double RunParam::MutaRate12 = 0.2; //1
double RunParam::MutaRate21 = 0.0; //2

bool RunParam::RUN = true;
double RunParam::StepSize = 1.000000;
double RunParam::MinStepSize = 0.1000000;
int RunParam::LJARatio = 40; //Expressed in Percentage
double RunParam::MaxEnergyFluctuation = 10; //Expressed in Percentage
int RunParam::PlotEnergyAfter = 10;
double RunParam::BoxSize = 5.0000000;
//Particle::EDGE = 5.0000000; //Streamline
bool RunParam::MaxStep = false;


//Rotation parameters
double RunParam::minRotor=0.500000;
double RunParam::maxRotor=1.000000;
double RunParam::resoRotor=0.000000;
bool RunParam::MaxRot= false;



//Log Parameters
bool RunParam::term2 = false;
bool RunParam::sysInterrupt = true;
const char* RunParam::LogOutput = "./Output/log.txt";
const char* RunParam::LogErrorOut = "./Output/error.txt";


//
const char* RunParam::ParentPath = "/home/yatharth1997/Runs/";
std::string RunParam::ParentPathS = "/home/yatharth1997/Runs/";
bool RunParam::printRunParamData = true;
bool RunParam::autoplotraw = false;


//System Param

//Estimated Time Per Sweep
double RunParam::ETPSl = 0.15;
double RunParam::ETPSu = 0.20;



