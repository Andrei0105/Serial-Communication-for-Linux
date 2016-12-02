/*
 * CBuffer.h
 *
 *  Created on: Nov 28, 2016
 *      Author: tudor-andrei
 */

#ifndef SRC_CBUFFER_H_
#define SRC_CBUFFER_H_
#include <string>

class CBuffer
{
public:
	std::string internalBuffer;
	long maxSize;
	//long size; //not needed -> use internalBuffer.size()
	void Init();

public:
	CBuffer();
	virtual ~CBuffer();

	void AddData(char ch);
	void AddData(std::string& data);
	void AddData(std::string& data, int iLen);
	void AddData(char *strData, int iLen);

	long ReadNoBytes(std::string &data, long noBytes);

	std::string GetData() { return internalBuffer; }
	inline long GetSize() { return internalBuffer.size(); }
	inline bool IsEmpty() { return internalBuffer.size() == 0; }

};



#endif /* SRC_CBUFFER_H_ */
