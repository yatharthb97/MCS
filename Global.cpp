/*define int REJECT = 0; //Counts the number of moves rejected
define bool RUN = true;*/



//fileconfig

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


volatile double checkStepSize()
{
	return(1); //STEP SIZE
}