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
		address(string(host), port)
{
	fp = fopen("out.h264","wb");
}

NetH264Reader::~NetH264Reader()
{

}

bool NetH264Reader::open()
{
	try
	{
		socket.connect(address, Timespan(10, 0));
	} catch (Exception& e)
	{
		cout << e.displayText() << endl;
		return false;
	}
	return true;
}

bool NetH264Reader::close()
{
	socket.close();
	fclose(fp);
	return true;
}

Bytes* NetH264Reader:: reader()
{
	char *data = new char[1024];
	int len = socket.receiveBytes(data,1024);
	cout << "len:" << len << endl;
	fwrite(data,len,1,fp);
	delete [] data;
	return NULL;
}

