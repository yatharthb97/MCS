//C code for urandom ==> seed by system entropy ///Include licence information


//Preprocessors
#pragma once
#include<unistd.h>
#include<fcntl.h>


//class Urandom
class Urandom{

private: 

int seed;

public:
int seedby_urandom(){
	int ur, fd, seed;
	fd = open("/dev/urandom", O_RDONLY, O_NONBLOCK); //Non-blocking mode implemented
	read(fd,&ur,sizeof(int));
	close(fd);
	seed = (ur>0)?ur:-ur;
	return seed;
}

};//End of class Urandom
