/*
 * FLVTagHeader.h
 *
 *  Created on: 2014-12-19
 *      Author: maygolf
 */

#ifndef FLVTAGHEADER_H_
#define FLVTAGHEADER_H_

#include <stdint.h>

#include "../Bytes.h"
class FLVTagHeader
{
private:
	/**
	 * 1到4个字节为上一个tag的总长度
	 */
	int previousTagSize;

	/**
	 * 音频（0x8），视频（0x9），脚本（0x12）
	 */
	char type;

	/**
	 * flvbody的长度
	 */
	int dataLength;

	/**
	 * 这一帧或者视频的时间戳
	 */
	int timestamp;

	/**
	 * 流id(好像总是为0)
	 */
	int streamid;
public:
	FLVTagHeader();
	int getPreviousTagSize()
	{
		return previousTagSize;
	}

	void setPreviousTagSize(int previousTagSize)
	{
		this->previousTagSize = previousTagSize;
	}

	int getType()
	{
		return type;
	}

	void setType(char type)
	{
		this->type = type;
	}

	int getDataLength()
	{
		return dataLength;
	}

	void setDataLength(int dataLength)
	{
		this->dataLength = dataLength;
	}

	int getTimestamp()
	{
		return timestamp;
	}

	void setTimestamp(int timestamp)
	{
		this->timestamp = timestamp;
	}

	int getStreamid()
	{
		return streamid;
	}

	void setStreamid(int streamid)
	{
		this->streamid = streamid;
	}
	virtual ~FLVTagHeader();
	void decoder(Bytes *bytes);
	virtual Bytes* encoder();

};

#endif /* FLVTAGHEADER_H_ */
