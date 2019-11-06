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
#include <stdlib.h>
#include "runparam.h"
using namespace std;

//class Log
class Log
{
private:

	//Data Members

	//Output Stream colour selection
	/*const std::string red = "\033[0;31m";
	const std::string blue = "\033[0;34m";*/
	
	//Filestream objects
	ofstream eo;
	ofstream oo;
	ofstream term2;

	//Filenmaes from RunParam
	const char* errorlog;
	const char* outputlog;
	const char* termpath;

	//From RunParam
	bool RUN;
	bool is_term2;
	bool is_interrupt;

public:

	//Constructor
	Log()
	{
		//Check if the program is running
		RunParam l;
		RUN = l.checkRUN();
		is_term2 = RunParam::term2;
		//cout<<is_term2<<endl;
		is_interrupt = l.checkInterrupt();
		//cout<<is_interrupt<<endl;

		//File assignments
		errorlog = l.fileConfig(1);
		outputlog = l.fileConfig(2);
		if(is_term2)
		{
			ifstream t2;
			t2.open(".LogTerm",ios::in);
			string t2path;
			t2>>t2path;
			termpath = t2path.c_str();
			t2.close();
			
		}

		else{termpath = "" ;}
		cout<<termpath<<endl;
	if(RUN == false){eo.close(); oo.close(); }

	else{
		
		eo.open(errorlog, ios::app);
		oo.open(outputlog, ios::app);
		if(is_term2){term2.open(termpath);}

		}


	}

	//@brief - Function for creating Error Log on xterm and file
	//@param - const char* filename, string arguement
	void logerror(const char* filename, string arguement){
		std::cerr<<"\033[0;31m"<<"[ERROR]"<<"\t"<<filename<<",\t"<<arguement<<std::endl<<"\033[0;0m"<<"\a";
		
		if(is_interrupt)
		{
			cout<<"\033[0;31m"<<"*****Press any key to continue.*****"<<std::endl<<"\033[0;0m";
			std::cin.get();
			 cin.sync(); //Clear std::in Buffer
		}

		if(eo.is_open())
			eo<<"[ERROR]"<<"\t"<<filename<<"\t"<<arguement<<std::endl;
		else{
			std::cerr<<"\033[0;31m"<<"[FATAL ERROR] logerror Output File Not Open.   "<<errorlog<<std::endl<<"\033[0;0m"<<"\a\a\a\a\a";
			
			/*if(is_interrupt)
			{
				cout<<"\033[0;31m"<<"*****Press any key to continue.*****"<<std::endl<<"\033[0;0m";
				std::cin.get();
				 cin.sync(); //Clear std::in Buffer
			}*/
		}

		//Terminal 2
		if(is_term2 && term2.is_open())
			term2<<"\033[0;31m"<<"[ERROR]"<<"\t"<<filename<<",\t"<<arguement<<std::endl<<"\033[0;0m"<<"\a";
		if(!term2.is_open() && is_term2)
		{
			std::cerr<<"\033[0;31m"<<"[FATAL ERROR] logerror Output File Not Open.   Terminal 2"<<std::endl<<"\033[0;0m"<<"\a\a\a\a\a";
			
			if(is_interrupt)
			{
				term2<<"\033[0;31m"<<"*****Press any key to continue.*****"<<std::endl<<"\033[0;0m";
				std::cerr<<"\033[0;31m"<<"*****Press any key to continue.*****"<<std::endl<<"\033[0;0m";
				std::cin.get();
				 cin.sync(); //Clear std::in Buffer
			}
		}
	}

	//@brief - Function for creating Output Log in file. If out = true ==> display message to xterm too
	//@param - const char* filename, string arguement, bool out
	void logoutput(const char* filename, string arguement, bool out){

		if(out == true){
			std::cerr<<"\033[0;34m"<<"[LOG]"<<"\t"<<filename<<",\t"<<arguement<<std::endl<<"\033[0;0m";

			if(oo.is_open())
			oo<<"\t"<<filename<<"\t"<<arguement<<std::endl;
			else{
			Log::logerror(outputlog, "[FATAL ERROR] log failure: logerror");
			}
		}


		else{

			if(oo.is_open())
			oo<<"\t"<<filename<<"\t"<<arguement<<std::endl;
			
			else{
				Log::logerror(outputlog, "[FATAL ERROR] log failure: logerror");
				}

		}


		//Terminal 2
		if(is_term2 && term2.is_open())
			{
				term2<<"\033[0;34m"<<"[LOG]"<<"\t"<<filename<<",\t"<<arguement<<std::endl<<"\033[0;0m";
			}
		if(!term2.is_open() && is_term2)
		{
			std::cerr<<"\033[0;31m"<<"[FATAL ERROR] logerror Output File Not Open.   Terminal 2"<<std::endl<<"\033[0;0m"<<"\a\a\a\a\a";
			
			if(is_interrupt)
			{
				term2<<"\033[0;31m"<<"*****Press any key to continue.*****"<<std::endl<<"\033[0;0m";
				std::cerr<<"\033[0;31m"<<"*****Press any key to continue.*****"<<std::endl<<"\033[0;0m";
				std::cin.get();
				 cin.sync(); //Clear std::in Buffer
			}
		}

	}

	//Destructor
	~Log()
	{
		eo.close();
		oo.close();
		term2.close();
		cout<<"\033[0;0m";
	}
	
};//end of class Log
