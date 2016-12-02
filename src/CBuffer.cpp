#include "CBuffer.h"
#include <algorithm>

CBuffer::CBuffer()
{
	Init();
}

void CBuffer::Init()
{
	maxSize = 0; // 0 for unlimited
	internalBuffer.erase();
}

CBuffer::~CBuffer()
{

}

void CBuffer::AddData(char ch)
{
	internalBuffer += ch;
}

void CBuffer::AddData(std::string& data)
{
	internalBuffer += data;
}

void CBuffer::AddData(std::string& data, int iLen)
{
	internalBuffer.append(data.c_str(), iLen);
}

void CBuffer::AddData(char *strData, int iLen)
{
	internalBuffer.append(strData, iLen);
}

long CBuffer::ReadNoBytes(std::string &data, long noBytes)
{
	long bufferSize = internalBuffer.size();
	long actualNoBytes = std::min(noBytes, bufferSize);

	data.append(internalBuffer.c_str(), actualNoBytes);
	internalBuffer.erase(0, actualNoBytes);
	return actualNoBytes;
}
