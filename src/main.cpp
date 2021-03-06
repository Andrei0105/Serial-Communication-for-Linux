#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <pthread.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <bitset>
#include "CSerial.h"


int main()
{
	char *portname = "/dev/ttyUSB0";

	/*CSerial c= CSerial(portname, B115200, 0, 1, CS7);
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

	std::cout<<std::endl;
	for(int i = 0; i<10; i++)
	{
		std::cout<<(int)str.c_str()[i]<<" | ";
		std::bitset<7> x(str.c_str()[i]);
		std::cout << x << " | ";
		std::cout << x.to_ulong()<<" | "<< (char)x.to_ulong()<<std::endl;
	}*/

	CSerial c = CSerial(portname, B115200, 0, 1, CS8);
	c.Init();
	c.Start();

	getchar();
	std::cout<<"xx"<<c.buffer.internalBuffer;
	return 0;
}
