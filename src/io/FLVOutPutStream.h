/*
 * FLVOutPutStream.h
 *
 *  Created on: 2014-12-25
 *      Author: maygolf
 */

#ifndef FLVOUTPUTSTREAM_H_
#define FLVOUTPUTSTREAM_H_

#include <fstream>

#include "MediaOutputStream.h"
#include "../flv/FLVType.h"
#include "../flv/FLVTag.h"
#include "../flv/FLVTagHeader.h"
#include "../flv/FLVScriptTagBody.h"
#include "../flv/FLVVideoTagBody.h"

using namespace std;

class FLVOutPutStream: public MediaOutputStream
{

private:
	char* filename;
	unsigned long framenum;
	
protected:
	ofstream file;
	/**
	 * 写入FLV9个字节的头
	 */
	bool writeFileHeader();
	unsigned int previousTagSize;
	unsigned long timestamp;
	unsigned int oneframetime;
	virtual bool writeData(char,FLVTagBody*);
	virtual long getTimeStamp();

public:
	FLVOutPutStream();
	FLVOutPutStream(const char*,unsigned int);
	virtual ~FLVOutPutStream();
	virtual bool open();
	virtual bool setParam(Bytes*);
	virtual bool writeHeaders(Bytes*);
	virtual bool writeFrame(Bytes*);
	virtual bool writeFrame(Bytes*,bool);
	virtual bool flush();
	virtual bool close();
	bool writeBytes(const char*, unsigned int);

};

#endif /* FLVOUTPUTSTREAM_H_ */
