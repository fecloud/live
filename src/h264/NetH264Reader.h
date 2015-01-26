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

using namespace Poco::Net;

class NetH264Reader: public H264Reader
{

private:
	SocketAddress address;
	StreamSocket socket;
	FILE * fp;

public:
	NetH264Reader(char*, unsigned short);
	virtual ~NetH264Reader();
	virtual bool close();
	virtual bool open();
	virtual Bytes* reader();
};

#endif /* CLIENT_NETH264READER_H_ */
