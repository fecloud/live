/*
 * NetH264Reader.cpp
 *
 *  Created on: 2015年1月26日
 *      Author: maygolf
 */

#include "NetH264Reader.h"
#include "Poco/LocalDateTime.h"
#include "Poco/DateTime.h"
#include "Poco/Timestamp.h"

NetH264Reader::NetH264Reader(char *host) :
		address(string(host)), head(12), nalu(4), pretime(0)
{
}

NetH264Reader::~NetH264Reader()
{

}

bool NetH264Reader::open()
{
	try
	{
		socket.connect(address, Poco::Timespan(10, 0));
		socket.setReceiveTimeout(Poco::Timespan(10, 0));
		const char *hand = "vlserver";
		socket.sendBytes(hand, strlen(hand));
	} catch (Poco::Exception& e)
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

	} catch (Poco::Exception& e)
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

		} catch (Poco::Exception& e)
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

	} catch (Poco::Exception& e)
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
		Poco::Timestamp t(getHeadTime());
		Poco::DateTime ld(t);

		//cout << "getHeadTime 1 " << ld.minute() << " " <<ld.second() << endl;
		//cout << "getHeadTime 2 " << Poco::LocalDateTime().minute() << " " << Poco::LocalDateTime().second() << endl;
		if (readBytes(getHeadBodyLength()))
		{
			if (pretime != 0)
			{
				byte->setTime(getHeadTime() - pretime);
			}
			pretime = getHeadTime();
			return byte;
		}
	}

	return NULL;
}

