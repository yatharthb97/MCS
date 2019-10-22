//Header file for class File
#pragma once
#include<iostream>
#include<fstream>
#include"runparam.h"
using namespace std;

//class File - Creates and writes to files.
class SetFile{

public:

const char* filename;
bool temp;
ofstream f;



	//Constructor
	SetFile(string file, bool hidden, bool temp, string write):temp(temp)
	{
		std::string parent=""; //= RunParam::ParentPathS; //Terminate paths correctly
		if(hidden){parent+=".";}
		parent+=file;
		this->filename = parent.c_str();
		if(write!=" ")
		{
			f.open(filename, ios::out);
			f<<write;
			f.close();
		}
	}


	//Close function
	/*void Close()
	{
		f.close();
	}*/

	//Destructor
	~SetFile()
	{
		if(temp){remove(this->filename);}
	}

};//End of File class
