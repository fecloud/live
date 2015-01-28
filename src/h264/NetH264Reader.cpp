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
		address(string(host), port), head(12), nalu(4)
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
		const char *hand = "vlserver";
		socket.sendBytes(hand, strlen(hand));
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
	return true;
}

bool NetH264Reader::readNaluBytes(int length)
{
	try
	{
		nalu.clear();
		int read = 0;
		int tread = 0;
		while (read < length)
		{
			char* buffer = &(nalu.getData()[read]);
			tread = socket.receiveBytes(buffer, (length - read));
			if (tread == 0)
			{
				return false;
			}
			read += tread;
		}

	} catch (Exception& e)
	{
		return false;
	}
	nalu.flip();
	return true;
}

bool NetH264Reader::readBytes(int length)
{
	if (readNaluBytes(nalu.getCapacity()))
	{
		try
		{
			byte->clear();
			int read = 0;
			int tread = 0;
			while (read < length - nalu.getCapacity())
			{
				char* buffer = &(byte->getData()[read]);
				tread = socket.receiveBytes(buffer, (length - nalu.getCapacity() - read));
				if (tread == 0)
				{
					return false;
				}
				read += tread;
			}

		} catch (Exception& e)
		{
			return false;
		}
		byte->setLength(length - nalu.getCapacity());
		byte->setType(byte->getData()[0] & 0x1F);
		byte->flip();
		return true;
	}
	return false;
}

bool NetH264Reader::readHeadBytes(int length)
{
	try
	{
		head.clear();
		int read = 0;
		int tread = 0;
		while (read < length)
		{
			char* buffer = &(head.getData()[read]);
			tread = socket.receiveBytes(buffer, (length - read));
			if (tread == -1)
			{
				return false;
			}
			read += tread;
		}

	} catch (Exception& e)
	{
		return false;
	}
	head.flip();
	return true;
}

int NetH264Reader::getHeadBodyLength()
{
	head.postion(0);
	return head.getInt();
}

long long NetH264Reader::getHeadTime()
{
	head.postion(4);
	return head.getLong();
}

H264NALU* NetH264Reader::readH264()
{
	if (readHeadBytes(head.getCapacity()))
	{
		if (readBytes(getHeadBodyLength()))
		{
			return byte;
		}
	}

	return NULL;
}

