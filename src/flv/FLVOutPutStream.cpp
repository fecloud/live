/*
 * FLVOutPutStream.cpp
 *
 *  Created on: 2014-12-25
 *      Author: maygolf
 */

#include "flv/FLVOutPutStream.h"

FLVOutPutStream::FLVOutPutStream()
{
	filename = 0;
	previousTagSize = 0;
	timestamp = 0;
}

FLVOutPutStream::FLVOutPutStream(const char* file)
{
	filename = 0;
	previousTagSize = 0;
	timestamp = 0;
	filename = new char[strlen(file) + 1];
	strcpy(filename, file);
}

FLVOutPutStream::~FLVOutPutStream()
{
	if (file.is_open())
	{
		close();
	}
	previousTagSize = 0;
	timestamp = 0;
	if (filename)
	{
		delete[] filename;
		filename = NULL;
	}
}

bool FLVOutPutStream::writeBytes(const char* bytes, unsigned int len)
{
	file.write(bytes, len);
	flush();
	return true;
}

bool FLVOutPutStream::writeFileHeader()
{
	char fileHeader[9] =
	{ 'F', 'L', 'V', 0x1, 0x1, 0x0, 0x0, 0x0, 0x9 };
	file.write(fileHeader, 9);
	flush();
	return true;
}

bool FLVOutPutStream::open()
{
	this->file.open(filename);
	writeFileHeader();
	return true;
}

bool FLVOutPutStream::writeData(char type, Bytes* body)
{
	FLVTag tag;
	tag.header.setType(type);
	tag.header.setDataLength(body->getLength());
	tag.header.setPreviousTagSize(this->previousTagSize);
	tag.header.setTimestamp(timestamp);
	tag.header.setStreamid(0);
	tag.body = 0;

	//编码成一个tag
	Bytes* headers = tag.header.encoder();
	this->previousTagSize = headers->getLength() - 4 + body->getLength();
	writeBytes(headers->getData(), headers->getLength());
	writeBytes(body->getData(), body->getLength());
	delete headers;
	headers = NULL;

	return true;
}

bool FLVOutPutStream::setParam(Bytes* bytes)
{
	return writeData(SCRIPT, bytes);
}

bool FLVOutPutStream::writeHeaders(Bytes* bytes)
{
	return writeData(VIDEO, bytes);
}

bool FLVOutPutStream::writeFrame(Bytes* bytes, char type, unsigned time)
{
	this->timestamp += time;
	//cout << "timestamp:" << timestamp << endl;
	return writeData(VIDEO, bytes);
}

bool FLVOutPutStream::flush()
{
	file.flush();
	return true;
}

bool FLVOutPutStream::close()
{
	char fileHeader[4] =
	{ 0x0, 0x0, 0x0, 0x10 };
	file.write(fileHeader, 4);
	flush();
	file.close();
	return true;
}

