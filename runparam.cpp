#include "runparam.h"



bool RunParam::RUN = true;
double RunParam::StepSize = 0.1;
int RunParam::LJARatio = 20;
double RunParam::BoxSize = 5;
bool RunParam::MaxStep = true;
const char* RunParam::LogOutput = "log.txt";
const char* RunParam::LogErrorOut = "error.txt";
