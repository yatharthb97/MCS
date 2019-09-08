/*define int REJECT = 0; //Counts the number of moves rejected
define bool RUN = true;*/



//fileconfig
#define REJECT
REJECT = 0;
//Switch to indicate if the program is running
bool volatile checkRUN()
{
	return true;
}

volatile const char* fileConfig(int i)
{
	switch(i)
	{	
		//Log Files:: demanded by class Log
		case 1:	return("error.txt"); break; //For error log 
		case 2: return("output.txt"); break; //For output log
	}
}


volatile int checkStepSize()
{
	return(1); //STEP SIZE
}

volatile double checkBoxSize()
{
	return(); //Size of the box
}

volatile void Reject(int a)
{
	if(a==1) {extern REJECT+=1;}
}

