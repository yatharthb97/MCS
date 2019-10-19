#include <iostream>
#include<fstream>

void ReadInitText()
{
	ifstream Reader("./Resource/inittext");
	
	std::string out;
	while(Reader.good())
	{
		std::string TempLine;                  //Temp line
	    std::getline (Reader , TempLine);        //Get temp line
	    TempLine += "\n";                      //Add newline character
	    
	    out += TempLine;                     //Add newline
	}
	Reader.close();
	std::cout<<out<<std::endl;
}