/*
 * MediaOutputStream.h
 *
 *  Created on: 2014-12-25
 *      Author: maygolf
 */

#ifndef MEDIAOUTPUTSTREAM_H_
#define MEDIAOUTPUTSTREAM_H_

#include "../base/Bytes.h"

class MediaOutputStream
{

public:
	MediaOutputStream()
	{
	}
	virtual ~MediaOutputStream()
	{
	};
	virtual bool open() = 0;
	virtual bool setParam(Bytes*) = 0;
	virtual bool writeHeaders(Bytes*) = 0;
	virtual bool writeFrame(Bytes*) = 0;
	virtual bool writeFrame(Bytes*,bool) = 0;
	virtual bool flush() = 0;
	virtual bool close() = 0;
};

#endif /* MEDIAOUTPUTSTREAM_H_ */
