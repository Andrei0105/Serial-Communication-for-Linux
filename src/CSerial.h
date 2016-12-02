/*
 * CSerial.h
 *
 *  Created on: Nov 29, 2016
 *      Author: tudor-andrei
 */

#ifndef SRC_CSERIAL_H_
#define SRC_CSERIAL_H_
#include <termios.h>
#include <unistd.h>
#include <pthread.h>
#include "CBuffer.h"

class CSerial
{
public:
	int fd;
	char* portName;
	long baudRate;
	int parity, stopBits, dataBits; //parity 0 none, 1 odd, 2 even, 3 mark, 4 space
	termios options;
	pthread_t thread;

	CBuffer buffer;

public:
	CSerial();
	CSerial(char* portName, long baudRate = B9600, int parity = 0, int stopBits = CSTOPB, int dataBits = CS8);
	virtual ~CSerial();
	void SetBaudRate(long baudRate);
	void SetParity(int parity);
	void SetStopBits(int stopBits);
	void SetPortName(char* portName);
	void SetDataSize(int dataBits);

	ssize_t Write(const char* data, unsigned int size);
	void Init();
	void Start(); //start reading thread

};

void *ContinousRead(void *fd);


#endif /* SRC_CSERIAL_H_ */
