/*
 * RTMPOutPutStream.h
 *
 *  Created on: 2014-12-25
 *      Author: maygolf
 */

#ifndef RTMPOUTPUTSTREAM_H_
#define RTMPOUTPUTSTREAM_H_

#include <unistd.h>
#include <time.h>

#include "../librtmp/rtmp_sys.h"
#include "../librtmp/log.h"

#include "FLVOutPutStream.h"
#include "../flv/lang/String.h"

class RTMPOutPutStream: public FLVOutPutStream {
private:
	char* url;
	bool live;
	long long pretime;

protected:
	virtual bool writeData(char, FLVTagBody*);
	virtual long getTimeStamp();

public:
	RTMPOutPutStream(const char*, bool, unsigned int);
	virtual ~RTMPOutPutStream();
	virtual bool open();
	virtual bool setParam(Bytes*);
	virtual bool flush();
	virtual bool close();
	void setUrl(char*);

};

#endif
