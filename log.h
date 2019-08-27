#include<iostream>
#include<fstream>

#include "./Global.h"


ofstream eo;
ofstream oo;
eo.open(errorlog, ios::in);
oo.open(outputlog, ios::in);

if(RUN == false){eo.close(); oo.close(); }


class Log{

public:

	void logerror(const char* filename, string arguement){
		std::cerr<<"[ERROR] "<<filename<<"  ==>"<<arguement<<std::endl;

		if(eo.is_open())
			eo<<"[ERROR] "<<filename<<"  ==>"<<arguement<<std::endl;
		else{
			std::cerr<<"[FATAL ERROR] log failure: logerror"<<std::endl;
			exit(1);
		}


	void logout(const char* filename, string arguement, bool out){

		if(out == true){
			std::cerr<<<<filename<<"  ==>"<<arguement<<std::endl;

			if(oo.is_open())
			oo<<"[LOG] "<<filename<<"  ==>"<<arguement<<std::endl;
			else{
			Log::logerror(outputlog, "[FATAL ERROR] log failure: logerror");
			}
		}

		else{

			if(oo.is_open())
			oo<<"[LOG] "<<filename<<"  ==>"<<arguement<<std::endl;
			else{
			Log::logerror(outputlog, "[FATAL ERROR] log failure: logerror");
			}

		}23
	}


}

};//end of class Log
