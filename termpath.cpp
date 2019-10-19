//Create second Terminal
#include<iostream>
using namespace std;
#include<fstream>
#include"file.h"


void setTermPath(std::string, const char*);
int main(){//setTermPath("dgdgdg", "temp");
}

//void setTermPath(std::string s, const char* filename)
//{
	
	//Check Terminals
	/*system("ls /dev/pts/  | wc -l > '.temp_term.temp'");
	ifstream r;
	r.open(".temp_term.temp", ios::in);
	char p;
	r.read((char*)&p, sizeof(char));
	//cout<<"p "<<p<<endl;
	r.close();remove(".temp_term.temp");
*/

	//cout<<"Make sure that there are no residual terminals open!"<<endl<<"Press any key to continue!"<<endl;
	//std::cin.get();
	/*system("gnome-terminal");
		int q = int(p) - 49;																																																																																										;
		//cout<<"q"<<q<<endl;
		char pq = q+48;
		//cout<<"pq "<<pq;
		std:: string tpath = "/dev/pts/";
		tpath.append(1,pq);
		//cout<<tpath<<endl;
		const char* tpath2 = tpath.c_str();
		ofstream f;
		f.open(tpath2);
		f<<"Path: "<<tpath2<<endl<<s<<endl;
		f.close();
	*/	//cout<<tpath2<<endl;

		//Take arguement of a constchar filename
		//Call the File class and write the path to it.
		//return void
		//return(tpath2);
		//File log(filename, true, true, tpath);
//}