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

#include "librtmp/rtmp_sys.h"
#include "librtmp/log.h"

#include "flv/FLVOutPutStream.h"
#include "flv/lang/String.h"

class RTMPOutPutStream: public FLVOutPutStream
{

private:
	char* url;
	bool live;

protected:
	virtual bool sendData(char packet_type, char data_type, Bytes* bytes);

public:
	RTMPOutPutStream(const char*, bool);
	virtual ~RTMPOutPutStream();
	virtual bool open();
	virtual bool setParam(Bytes*);
	virtual bool writeHeaders(Bytes*);
	virtual bool writeFrame(Bytes*, char, unsigned);
	virtual bool flush();
	virtual bool close();
	void setUrl(char*);

};

#endif
