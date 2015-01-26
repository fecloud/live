/*
 * NetH264Reader.cpp
 *
 *  Created on: 2015年1月26日
 *      Author: maygolf
 */

#include "NetH264Reader.h"

using namespace Poco;
using namespace Poco::Net;

NetH264Reader::NetH264Reader(char* host, unsigned short port) :
		address(string(host), port), stream(0)
{
}

NetH264Reader::~NetH264Reader()
{

}

bool NetH264Reader::open()
{
	try
	{
		socket.connect(address, Timespan(10, 0));
		stream = new SocketStream(socket);
	} catch (Exception& e)
	{
		return false;
	}
	return true;
}

bool NetH264Reader::close()
{
	stream->close();
	socket.close();
	return true;
}

