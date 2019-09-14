/*define int REJECT = 0; //Counts the number of moves rejected
define bool RUN = true;*/



//fileconfig
#define REJECT
#define ACCEPT
REJECT = 0;
ACCEPT = 0;

//1
//Switch to indicate if the program is running
inline bool volatile checkRUN()
{
	return true;
}

//2
inline volatile const char* fileConfig(int i)
{
	switch(i)
	{	
		//Log Files:: demanded by class Log
		case 1:	return("error.txt"); break; //For error log 
		case 2: return("output.txt"); break; //For output log
	}
}

//3
inline volatile int checkStepSize()
{
	return(1); //STEP SIZE
}

//4
inline volatile void Reject(int a)
{
	if(a==1) {extern REJECT+=1;}
}

//5
inline accept void Accept(int a)
{
	if(a==1){extern ACCEPT+=1; }
}

