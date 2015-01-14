/*
 * FLVTagHeader.cpp
 *
 *  Created on: 2014-12-19
 *      Author: maygolf
 */

#include "FLVTagHeader.h"

FLVTagHeader::FLVTagHeader()
{
	previousTagSize = 0;
	type = 0;
	dataLength = 0;
	timestamp = 0;
}

FLVTagHeader::~FLVTagHeader()
{
}

void FLVTagHeader::decoder(Bytes *bytes)
{
	//4个字节的前一个tag长度
	int previousTagSize = bytes->getInt();
	setPreviousTagSize(previousTagSize);

	//一个字节的类型
	setType(bytes->get());

	//3个字节的body长度
	int dataLength = (((0) << 24) | ((bytes->get() & 0xff) << 16)
			| ((bytes->get() & 0xff) << 8) | ((bytes->get() & 0xff)));
	setDataLength(dataLength);

	//4个字节的时间戳,平常3位,最高位第每4
	int timestamp = bytes->getInt();
	timestamp >>= 8;
	bytes->postion(bytes->postion() - 1);
	timestamp += bytes->get() << 24;
	setTimestamp(timestamp);

	//3个字节的流id
	bytes->postion(bytes->postion() - 1);
	int streamid = bytes->getInt();
	setStreamid(streamid);

}

Bytes* FLVTagHeader::encoder()
{
	Bytes* bytes = new Bytes(15);
	bytes->putInt(previousTagSize);

	bytes->put(type);

	bytes->put(0xFFFFFF & dataLength >> 16);
	bytes->put(0xFFFF & dataLength >> 8);
	bytes->put(0xFF & dataLength);

	bytes->put(0xFFFFFF & timestamp >> 16);
	bytes->put(0xFFFF & timestamp >> 8);
	bytes->put(0xFF & timestamp);
	bytes->put(0xFFFFFFFF & timestamp >> 24);

	bytes->put(0xFFFFFF & streamid >> 16);
	bytes->put(0xFFFF & streamid >> 8);
	bytes->put(0xFF & streamid);
	bytes->flip();
	return bytes;
}

