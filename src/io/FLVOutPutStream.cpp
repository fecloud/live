/*
 * FLVOutPutStream.cpp
 *
 *  Created on: 2014-12-25
 *      Author: maygolf
 */

#include "FLVOutPutStream.h"

FLVOutPutStream::FLVOutPutStream()
{
	filename = 0;
	previousTagSize = 0;
	timestamp = 0;
	oneframetime = 0;
	framenum = 0;
}

FLVOutPutStream::FLVOutPutStream(const char* file,unsigned int framerate)
{
	filename = 0;
	previousTagSize = 0;
	timestamp = 0;
	oneframetime = 0;
	filename = new char[strlen(file)];
	strcpy(filename,file);
	oneframetime = 1000 / framerate;
	framenum = 0;
}

FLVOutPutStream::~FLVOutPutStream()
{
	if (file.is_open())
	{
		close();
	}
	previousTagSize = 0;
	timestamp = 0;
	oneframetime = 0;
	if(filename)
	{
		delete [] filename;
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
	char fileHeader[9] = { 'F', 'L', 'V', 0x1, 0x1, 0x0, 0x0, 0x0, 0x9 };
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

bool FLVOutPutStream::writeData(char type, FLVTagBody* body)
{
	FLVTag tag;
	tag.header.setType(type);
	tag.header.setDataLength(body->getData()->getLength());
	tag.header.setPreviousTagSize(this->previousTagSize);
	tag.header.setTimestamp(timestamp);
	tag.header.setStreamid(0);
	tag.body = 0;

	//编码成一个tag
	Bytes* headers = tag.header.encoder();
	this->previousTagSize = headers->getLength() - 4 + body->getData()->getLength();
	writeBytes(headers->getData(), headers->getLength());
	writeBytes(body->getData()->getData(), body->getData()->getLength());
	delete headers;
	headers = NULL;

	body->setData(0x0);
	delete body;
	body = NULL;
	return true;
}

bool FLVOutPutStream::setParam(Bytes* bytes)
{
	FLVScriptTagBody* body = new FLVScriptTagBody();
	body->setData(bytes);
	return writeData(SCRIPT, body);
}

bool FLVOutPutStream::writeHeaders(Bytes* bytes)
{
	FLVVideoTagBody* body = new FLVVideoTagBody();
	body->setData(bytes);
	return writeData(VIDEO, body);
}

bool FLVOutPutStream::writeFrame(Bytes* bytes)
{
	return writeFrame(bytes,false);
}

bool FLVOutPutStream::writeFrame(Bytes* bytes,bool end)
{
	this->timestamp = getTimeStamp();
	FLVVideoTagBody* body = new FLVVideoTagBody();
	body->setData(bytes);
	return writeData(VIDEO, body);
}

long FLVOutPutStream::getTimeStamp()
{
	long t = framenum * oneframetime;
	framenum++;
	return t;
}

bool FLVOutPutStream::flush()
{
	file.flush();
	return true;
}

bool FLVOutPutStream::close()
{
	char fileHeader[4] = { 0x0, 0x0, 0x0, 0x10 };
	file.write(fileHeader, 4);
	flush();
	file.close();
	return true;
}

