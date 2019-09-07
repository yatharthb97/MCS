//Header File to create Logs
//Dependency ==> - Global.cpp for defination of checkRUN() and fileConfig

///Status - Complete and Tested
//@Author - yatharthb97

//---------------

//Preprocessors
#include<iostream>
#include<fstream>
using namespace std;

//class Log
class Log{
private:

	//Data Members

	//Output Stream colour selection
	const std::string red = "\033[0;31m";
	const std::string blue = "\033[0;34m";
	
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
		extern volatile bool checkRUN();
		RUN = checkRUN();

		//File assignments
		extern const char* fileConfig(int);
		errorlog = fileConfig(1);
		outputlog = fileConfig(2);
		

	if(RUN == false){eo.close(); oo.close(); }

	else{
		
		eo.open(errorlog, ios::out);
		oo.open(outputlog, ios::out);
		}


	}

	//@brief - Function for creating Error Log on xterm and file
	//@param - const char* filename, string arguement
	void logerror(const char* filename, string arguement){
		std::cerr<<red<<"[ERROR]"<<"\t"<<filename<<"  ==>"<<arguement<<std::endl<<"\033[0;0m";

		if(eo.is_open())
			eo<<"[ERROR]"<<"\t"<<filename<<"\t"<<arguement<<std::endl;
		else{
			std::cerr<<red<<"[FATAL ERROR] log failure: logerror"<<std::endl<<"\033[0;0m";
		}
	}

	//@brief - Function for creating Output Log in file. If out = true ==> display message to xterm too
	//@param - const char* filename, string arguement, bool out
	void logoutput(const char* filename, string arguement, bool out){

		if(out == true){
			std::cerr<<blue<<"[LOG]"<<"\t"<<filename<<"  ==>"<<arguement<<std::endl<<"\033[0;0m";

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
