/*
 * VideoLiveTCPConnection.cpp
 *
 *  Created on: Jan 23, 2015
 *      Author: ouyangfeng
 */

#include <unistd.h>
#include <iostream>

#include "Poco/Util/Application.h"
#include "Poco/Timestamp.h"
#include "Poco/Exception.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/LocalDateTime.h"

#include "VideoLiveTCPConnection.h"

using namespace std;
using namespace Poco;
using namespace Poco::Util;
using namespace Poco::Net;

VideoLiveTCPConnection::VideoLiveTCPConnection(const StreamSocket& s) :
		TCPServerConnection(s), firstI(false)
{
}

bool VideoLiveTCPConnection::hand()
{
	try
	{
		int len = strlen(VLSERVER_HAND);
		char chand[len + 1];
		int read = 0;
		int tread = 0;
		while (read < len)
		{
			tread = socket().receiveBytes(&(chand[read]), (len - read));
			if (tread == 0)
			{
				return false;
			}
			read += tread;
		}

		chand[len] = '\0';

		string server(VLSERVER_HAND);
		string c(chand);
		if (server == c)
		{
			return true;
		}
	} catch (Exception& e)
	{

	}

	return false;
}

bool VideoLiveTCPConnection::sendHeader()
{
	unsigned char *start = seqhead.bufptr;
	return sendData(start, 13) && sendData(start + 13, seqhead.length - 13);

	return false;
}

bool VideoLiveTCPConnection::sendData(const void* buffer, int length)
{
	bool re = false;
	char lens[4];
	char time[8];
	try
	{
//		CPPLOG(length);
		lens[0] = length >> 24;
		lens[1] = (length & 0xFFFFFF) >> 16;
		lens[2] = (length & 0xFFFF) >> 8;
		lens[3] = length;

		long long t = current_time();
		time[0] = (t & 0xFFFFFFFFFFFFFFFF) >> 56;
		time[1] = (t & 0xFFFFFFFFFFFFFF) >> 48;
		time[2] = (t & 0xFFFFFFFFFFFF) >> 40;
		time[3] = (t & 0xFFFFFFFFFF) >> 32;
		time[4] = (t & 0xFFFFFFFF) >> 24;
		time[5] = (t & 0xFFFFFF) >> 16;
		time[6] = (t & 0xFFFF) >> 8;
		time[7] = t;

		if (socket().sendBytes(lens, 4) && socket().sendBytes(time, 8) && socket().sendBytes(buffer, length))
		{
			re = true;
		}
	} catch (Poco::Exception& e)
	{
		re = false;
	}
	return re;
}

void VideoLiveTCPConnection::doWork()
{

	while (1)
	{
//		CPPLOG("pthread_mutex_lock(&mt)");
		pthread_mutex_lock(&mt);

		if (bufferLength > 0)
		{
			if (!firstI && (buffer[4] & 0x1F) != 5)
			{
				pthread_mutex_unlock(&mt);
				continue;
			}
			else
			{
				firstI = true;
			}
			try
			{
				//send
				if (sendData(buffer, bufferLength))
				{
					resetVencOutputBuffer();
				}
				else
				{
					break;
				}
			} catch (Poco::Exception& e)
			{
				CPPLOG("Poco::Exception& e");
				pthread_mutex_unlock(&mt);
				break;
			}

		}
		else
		{
//			CPPLOG("pthread_cond_wait(&ct, &mt)");
			pthread_cond_wait(&ct, &mt);
		}

		pthread_mutex_unlock(&mt);
	}

}

void VideoLiveTCPConnection::run()
{
	VideoLiveObservable* instance = VideoLiveObservable::createNew();

	LocalDateTime ld;

	// 日志输出连接的TCP用户的地址（IP和端口）
	string add = socket().peerAddress().toString();

	cout << ld.year() << "-" << ld.month() << "-" << ld.day() << " " << ld.hour() << ":" << ld.minute() << ":" << ld.second() << " request from " + add << endl;

	if (hand())
	{
		LocalDateTime ld1;
		cout << ld1.year() << "-" << ld1.month() << "-" << ld1.day() << " " << ld1.hour() << ":" << ld1.minute() << ":" << ld1.second() << " " + add << " hand success" << endl;
		try
		{
			cpyVencSeqHeader(instance->registerVideoLiveObserver(this));
			if (this->seqhead.length > 0)
			{
				if (sendHeader())
				{
					doWork();
				}
				else
				{
					CPPLOG("send head error finish");
				}

			}
			instance->unRegisterVideoLiveObserver(this);

		} catch (Poco::Exception& e)
		{
			instance->unRegisterVideoLiveObserver(this);
		}
		LocalDateTime ld2;
		cout << ld2.year() << "-" << ld2.month() << "-" << ld2.day() << " " << ld2.hour() << ":" << ld2.minute() << ":" << ld2.second() << " " + add << " disconnet" << endl;
	}
	else
	{
		LocalDateTime ld;
		cout << ld.year() << "-" << ld.month() << "-" << ld.day() << " " << ld.hour() << ":" << ld.minute() << ":" << ld.second() << " " + add << " hand error disconnet" << endl;

	}
}
