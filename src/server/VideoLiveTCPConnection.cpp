/*
 * VideoLiveTCPConnection.cpp
 *
 *  Created on: Jan 23, 2015
 *      Author: ouyangfeng
 */

#include <unistd.h>

#include "Poco/Util/Application.h"
#include "Poco/Timestamp.h"
#include "Poco/Exception.h"
#include "Poco/DateTimeFormatter.h"

#include "VideoLiveTCPConnection.h"

using namespace Poco;
using namespace Poco::Util;
using namespace Poco::Net;

VideoLiveTCPConnection::VideoLiveTCPConnection(const StreamSocket& s) :
		TCPServerConnection(s)
{

}

void VideoLiveTCPConnection::doWork()
{

	while (1)
	{
		pthread_mutex_lock(&mt);

		if (buffer.id > 0)
		{
			//send
			if (socket().sendBytes(buffer.ptr0, buffer.size0))
			{
				if (buffer.size1 > 0)
				{
					if (!socket().sendBytes(buffer.ptr1, buffer.size1))
					{
						break;
					}
				}
				resetVencOutputBuffer();
			}
			else
			{
				break;
			}

		}
		else
		{
			pthread_cond_wait(&ct, &mt);
		}

		pthread_mutex_unlock(&mt);
	}

}

void VideoLiveTCPConnection::run()
{
	Application& app = Application::instance();
	// 日志输出连接的TCP用户的地址（IP和端口）
	//app.logger().information("Request from " + this->socket().peerAddress().toString());
	try
	{
		VideoLiveObservable* instance = VideoLiveObservable::createNew();
		cpyVencSeqHeader(instance->registerVideoLiveObserver(this));
		if (this->seqhead.length > 0)
		{
			if (socket().sendBytes(this->seqhead.bufptr, this->seqhead.length))
			{
				doWork();
			}
			app.logger().warning("send head error finish");

		}
		instance->unRegisterVideoLiveObserver(this);
		socket().shutdown();

	} catch (Poco::Exception& e)
	{
		app.logger().log(e);
	}
}
