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
	int parity, parityOn, stopBits, dataBits; //parity 0 none, 1 odd, 2 even
	termios options;
	pthread_t thread;
	pthread_mutex_t mutex;

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

//	inline void Lock() {pthread_mutex_lock(&mutex);}
//	inline void Unlock() {pthread_mutex_unlock(&mutex);}
//	inline void InitLock() {pthread_mutex_init(&mutex, NULL);}
//	inline void DelLock() {pthread_mutex_destroy(&mutex);}
	virtual void ProcessData(char* data, long length);
};

void *ContinuousRead(void *fd);




#endif /* SRC_CSERIAL_H_ */
