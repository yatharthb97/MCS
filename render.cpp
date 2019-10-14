#include<iostream>
#include<fstream>
using namespace std;
#include"box.h"

void Render(Box b&, const char* filename)
{
	fstream rend;
	rend.open(filename, ios::out);
	int count = b.getCount();
	for(unsigned int i= 0; i<count; i++)
	{
	rend<<b.PassPartlist().at(i).getPosition().infoRaw()<<std::endl;
	}
	rend.close();
}
