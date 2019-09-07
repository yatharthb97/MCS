//C code for urandom ==> seed by system entropy ///Include licence information
#pragma once


#include<unistd.h>
#include<fcntl.h>

int seedby_urandom(){
	int ur, fd;
	fd = open("/dev/urandom", O_RDONLY);
	read(fd,&ur,sizeof(int));
	close(fd);
	return (ur>0)?ur:-ur;
}
