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

	CSerial c= CSerial(portname, B9600);
	c.Init();
	c.Start();
	int x=0;
	while(x<50)
	{
		std::cout<<c.Write("TESt",4);
		x++;
		//std::cout<<c.buffer.internalBuffer;
		usleep(100*25*4);

	}
	std::cout<<c.buffer.internalBuffer;
	return 0;
}
