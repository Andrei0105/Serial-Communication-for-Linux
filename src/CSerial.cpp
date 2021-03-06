/*
 * CSerial.cpp
 *
 *  Created on: Nov 29, 2016
 *      Author: tudor-andrei
 */

#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <pthread.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include "CSerial.h"


CSerial::CSerial()
{

}

CSerial::CSerial(char* portName, long baudRate, int parity, int stopBits, int dataBits)
{
	this->portName = new char[strlen(portName) + 1];
	strncpy(this->portName, portName, strlen(portName) + 1);
	this->baudRate = baudRate;
	//
	if(parity == 0)
	{
		this->parity = 0;
		this->parityOn = 0;
	}
	else if(parity == 1)
	{
		this->parity = PARODD;
		this->parityOn = PARENB;
	}
	else if(parity == 2)
	{
		this->parity = 0;
		this->parityOn = PARENB;
	}
	if (stopBits == 1)
	{
		this->stopBits = 0;
	}
	else if (stopBits == 2)
	{
		this->stopBits = CSTOPB;
	}
	//
	this->dataBits = dataBits;
	this->thread = NULL;
	this->fd = NULL;
	//InitLock();

}

void CSerial::Init()
{
	//open the port
	fd = open(portName, O_RDWR | O_NOCTTY | O_SYNC);

	memset(&options, 0, sizeof options);

	//set baud rate
	cfsetospeed (&options, baudRate);
	cfsetispeed (&options, baudRate);

	options.c_iflag &= ~IGNBRK;
	options.c_lflag = 0;

	options.c_oflag = 0;
	options.c_cc[VMIN] = 0; //read nonblocking
	options.c_cc[VTIME] = 1; //0.1 sec read timeout

	options.c_iflag &= ~(IXON | IXOFF | IXANY); //disable xon/xoff ctrl

	options.c_cflag |= dataBits;
	options.c_cflag |= (CLOCAL | CREAD); //ignore modem controls, enable reading
	options.c_cflag |= (parity|parityOn);
	options.c_cflag |= stopBits;
	options.c_cflag |= CRTSCTS;

	tcflush(fd,TCIOFLUSH);

	if (tcsetattr (fd, TCSANOW, &options) != 0)
	{
		printf ("error %d from tcsetattr", errno);
		return;
	}
	sleep(2); //enough time for all changes to be applied
}

void CSerial::Start()
{
	pthread_create(&this->thread, NULL, ContinuousRead, this);
}

CSerial::~CSerial()
{
	delete[] portName;
	//DelLock();
}

ssize_t CSerial::Write(const char* data, unsigned int size)
{
	ssize_t noBytes = write(fd, data, size);
	return noBytes;
}

void *ContinuousRead(void *cInstance)
{
	CSerial *callingInstance = (CSerial *)cInstance;
	char buf[1];
	while(true)
	{

		int n = read (callingInstance->fd, buf, 1);
		//std::cout<<n;
		callingInstance->buffer.LockBuffer();
		if(n)
		{
			callingInstance->buffer.AddData(buf, 1);
			callingInstance->ProcessData(buf,n);
		}
		callingInstance->buffer.UnlockBuffer();
	}
}

void CSerial::ProcessData(char* data, long length)
{
	if (length > 0)
		fprintf(stdout, "%c", data[0]);
}
