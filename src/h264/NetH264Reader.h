/*
 * NetH264Reader.h
 *
 *  Created on: 2015年1月26日
 *      Author: maygolf
 */

#ifndef CLIENT_NETH264READER_H_
#define CLIENT_NETH264READER_H_

#include <string.h>

#include "Poco/Net/SocketAddress.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/SocketStream.h"
#include "Poco/StreamCopier.h"

#include "H264Reader.h"

#include <stdio.h>

class NetH264Reader: public H264Reader
{

private:
	Poco::Net::SocketAddress address;
	Poco::Net::StreamSocket socket;
	Bytes head;
	Bytes nalu;
	bool readNaluBytes(int length);
	bool readBytes(int length);
	bool readHeadBytes(int length);
	int getHeadBodyLength();
	long long getHeadTime();
	long long pretime;

public:
	NetH264Reader(char*);
	virtual ~NetH264Reader();
	virtual bool close();
	virtual bool open();
	virtual H264NALU* readH264();
};

#endif /* CLIENT_NETH264READER_H_ */
