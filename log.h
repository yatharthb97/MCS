//Header File to create Logs
//Dependency ==> - runparam.h for RunParam class

///Status - Complete and Tested
//@Author - yatharthb97

//---------------

//Preprocessors
#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include "runparam.h"
using namespace std;

//class Log
class Log{
private:

	//Data Members

	//Output Stream colour selection
	/*const std::string red = "\033[0;31m";
	const std::string blue = "\033[0;34m";*/
	
	//Filestream objects
	ofstream eo;
	ofstream oo;

	const char* errorlog;
	const char* outputlog;
	bool RUN;

public:

	//Constructor
	Log()
	{
		//Check if the program is running
		inline extern volatile bool checkRUN();
		RunParam l;
		RUN = l.checkRUN();

		//File assignments
		errorlog = l.fileConfig(1);
		outputlog = l.fileConfig(2);
		

	if(RUN == false){eo.close(); oo.close(); }

	else{
		
		eo.open(errorlog, ios::app);
		oo.open(outputlog, ios::app);
		}


	}

	//@brief - Function for creating Error Log on xterm and file
	//@param - const char* filename, string arguement
	void logerror(const char* filename, string arguement){
		std::cerr<<"\033[0;31m"<<"[ERROR]"<<"\t"<<filename<<",\t"<<arguement<<std::endl<<"\033[0;0m"<<"\a";
		
		//If condition
		{
			cout<<"\033[0;31m"<<"*****Press any key to continue.*****"<<std::endl<<"\033[0;0m";
			std::cin.get(); 
		}

		if(eo.is_open())
			eo<<"[ERROR]"<<"\t"<<filename<<"\t"<<arguement<<std::endl;
		else{
			std::cerr<<"\033[0;31m"<<"[FATAL ERROR] log failure: logerror"<<std::endl<<"\033[0;0m"<<"\a\a\a\a\a";
			
			//If condition
			{
				cout<<"\033[0;31m"<<"*****Press any key to continue.*****"<<std::endl<<"\033[0;0m";
				std::cin.get();
			}
		}
	}

	//@brief - Function for creating Output Log in file. If out = true ==> display message to xterm too
	//@param - const char* filename, string arguement, bool out
	void logoutput(const char* filename, string arguement, bool out){

		if(out == true){
			std::cerr<<"\033[0;34m"<<"[LOG]"<<"\t"<<filename<<",\t"<<arguement<<std::endl<<"\033[0;0m";

			if(oo.is_open())
			oo<<"[LOG]"<<"\t"<<filename<<"\t"<<arguement<<std::endl;
			else{
			Log::logerror(outputlog, "[FATAL ERROR] log failure: logerror");
			}
		}


		else{

			if(oo.is_open())
			oo<<"[LOG]"<<"\t"<<filename<<"\t"<<arguement<<std::endl;
			
			else{
				Log::logerror(outputlog, "[FATAL ERROR] log failure: logerror");
				}

		}

	}

	//Destructor
	~Log()
	{
		eo.close();
		oo.close();
		cout<<"\033[0;0m";
	}


};//end of class Log
