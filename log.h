#include<iostream>
#include<fstream>
#include<iomanip>

#include "./Global.h"  //Global Variables File defining log filenames

if(RUN == false){eo.close(); oo.close(); }

else{
	ofstream eo;
	ofstream oo;
	eo.open(errorlog, ios::in);
	oo.open(outputlog, ios::in);
}

const std::string red("\033[0;31m");
const std::string blue("\033[0;34m");

class Log{

public:

	void logerror(const char* filename, string arguement){
		std::cerr<<red<<"[ERROR]"<<"\t"<<filename<<"  ==>"<<arguement<<std::endl;

		if(eo.is_open())
			eo<<"[ERROR]"<<"\t"<<filename<<"\t"<<arguement<<std::endl;
		else{
			std::cerr<<red<<"[FATAL ERROR] log failure: logerror"<<std::endl;
		}


	void logout(const char* filename, string arguement, bool out){

		if(out == true){
			std::cerr<<blue<<"[LOG]"<<"\t"<<filename<<"  ==>"<<arguement<<std::endl;

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


}

};//end of class Log
