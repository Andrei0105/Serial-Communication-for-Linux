#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <pthread.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include "CSerial.h"


int main()
{
	char *portname = "/dev/ttyUSB0";

	CSerial c= CSerial(portname, B115200);
	c.Init();
	c.Start();
	int x=0;
	while(x<5)
	{
		std::cout<<c.Write("test\n",5);
		x++;
	}
	sleep(2);
	std::cout<<std::endl<<c.buffer.internalBuffer;
	std::string str;
	c.buffer.ReadNoBytes(str, 5);
	c.buffer.ReadNoBytes(str, 3);
	c.buffer.ReadNoBytes(str, 2);
	std::cout<<"buffer"<<std::endl<<c.buffer.internalBuffer;
	std::cout<<"str"<<std::endl<<str;
	return 0;
}
