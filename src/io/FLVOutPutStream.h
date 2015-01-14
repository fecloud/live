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
	char*filename;
	
protected:
	ofstream file;
	bool writeFileHeader();
	int previousTagSize;
	long timestamp;
	virtual bool writeData(char,FLVTagBody*);

public:
	FLVOutPutStream();
	FLVOutPutStream(char*);
	virtual ~FLVOutPutStream();
	virtual bool open();
	virtual bool setParam(Bytes*);
	virtual bool writeHeaders(Bytes*);
	virtual bool writeFrame(Bytes*);
	virtual bool writeFrame(Bytes*,bool);
	virtual bool flush();
	virtual bool close();
	bool writeBytes(char*, int);
};

#endif /* FLVOUTPUTSTREAM_H_ */
