/*
 * FLVVideoTagBody.h
 *
 *  Created on: 2014-12-19
 *      Author: maygolf
 */

#ifndef FLVVIDEOTAGBODY_H_
#define FLVVIDEOTAGBODY_H_

#include "FLVTagBody.h"

class FLVVideoTagBody: public FLVTagBody
{
private:
	char frameType;
	char codec;
public:
	FLVVideoTagBody();
	virtual ~FLVVideoTagBody();
	int getFrameType()
	{
		return frameType;
	}
	void setFrameType(char frameType)
	{
		this->frameType = frameType;
	}

	char getCodec()
	{
		return codec;
	}

	void setCodec(char codec)
	{
		this->codec = codec;
	}
	void decoderBoby(Bytes *bytes);
};

#endif /* FLVVIDEOTAGBODY_H_ */
