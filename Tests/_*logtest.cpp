#include<iostream>
#include "log.h"
using namespace std;

#define errorlog "error.txt"
#define outputloglog "output.txt"
#define RUN true

int main(){
	cout<<"Create logs!<<<<Testing!"<<endl;
	Log l;
	l.logerror("./sample.txt", "File open error!");
	l.logoutput("./sample.txt", "Dont output on xterm", false);
	l.logoutput("./sample.txt", "Dont output on xterm", true);
	l.~Log();
	cout<<"Create logs!<<<<Testing!"<<endl;
	return 0;
}