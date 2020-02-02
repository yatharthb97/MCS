//  mmmm           "      m           #                   
// #"   "m     m mmm    mm#mm   mmm   # mm    mmm    mmm  
// "#mmm "m m m"   #      #    #"  "  #"  #  #"  #  #   " 
//     "# #m#m#    #      #    #      #   #  #""""   """m 
// "mmm#"  # #   mm#mm    "mm  "#mm"  #   #  "#mm"  "mmm" 

//ʌʌʌʌʌʌʌʌʌʌʌʌʌʌʌʌʌʌʌʌʌʌʌʌʌʌʌʌʌʌʌʌʌʌʌʌʌʌʌʌʌʌʌʌʌʌʌʌʌʌʌʌʌʌʌʌʌʌʌʌʌʌʌ
//vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv


#include "runparam.h"
#include"particle.h"


//Particle Types:
#define T_1CP 1 //Spherocylinder with 1 chiral patch
#define T_1TP 2 //Spherocylinder with 1 tip patch

//Monte Carlo Parameters
double RunParam::BoxSize = 0.050000000;
bool RunParam::GrandCanonical = false;
int RunParam::LJARatio = 40; //Expressed in Percentage
double RunParam::MaxEnergyFluctuation = 10; //Expressed in Percentage
int RunParam::PlotEnergyAfter = 10;
//Monte Carlo Parameters

//Particle Geometry
double Patch::width = 1.000000;
double Particle::L = 4*SigmaAtrr;
double Particle::D = SigmaAtrr;
//Particle Geometry

//Recipie - Expressed in percentages
//Initial Recipie
//**Exhaustive Rates**
int RunParam::SC_1CP_recipie = 90; //Type 1
int RunParam::SC_1TP_recipie = 10; //Type 2
//Initial Recipie

//Recipie - Mutators
//**Absolute Rates** - Relates per number of Sweeps 
double RunParam::AddPartRate = 2;
double RunParam::RmPartRate = 2;
double RunParam::MutaPartRate = 2;
//Recipie - Mutators 

//Addition and Removal Rates
//**Exhaustive Rates**
float RunParam::AddRate1 = 80;
float RunParam::AddRate2 = 20;
//**Absolute Rates**
double RunParam::RmPartTrialAcceptRate=10;
//Addition and Removal Rates

//Recipie-Mutation Rates
//**Absolute Rates**		   1--->2	  2->1
float RunParam::MutaMatrix[2][2] = {{1,  100}, {2, 0}};
int RunParam::TotalSpecies = 2;

//Translation Switches
double RunParam::StepSize = 1.000000;
double RunParam::MinStepSize = 0.00100000;
bool RunParam::MaxStep = false;
//Translation Switches


//Rotation switches
double RunParam::minRotor=0.500000;
double RunParam::maxRotor=1.000000;
double RunParam::resoRotor=0.000000; //Not used anywhere
bool RunParam::MaxRot= false;
//Rotation switches


//Log Parameters
bool RunParam::term2 = false;
bool RunParam::sysInterrupt = true;
const char* RunParam::LogOutput = "./Output/log.txt";
const char* RunParam::LogErrorOut = "./Output/error.txt";
//Estimated Time Per Sweep for logging
double RunParam::ETPSl = 0.0004;
double RunParam::ETPSu = 0.0005;
//Log Parameters


//Environmental Setup Board
bool RunParam::RUN = true;
const char* RunParam::ParentPath = "/mnt/m/Runs/";
std::string RunParam::ParentPathS = "/mnt/m/Runs/";
bool RunParam::printRunParamData = true; //Not implemented Yet
bool RunParam::autoplotraw = true;
bool RunParam::UseSysEntropy = true;
//Environmental Setup Board

string RunParam::patch_color =  "red" ;
string RunParam::default_color =  "blue";
int RunParam::render_resolution = 20;