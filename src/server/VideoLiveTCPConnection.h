/*
 * VideoLiveTCPConnection.h
 *
 *  Created on: Jan 23, 2015
 *      Author: ouyangfeng
 */

#ifndef SRC_SERVER_VIDEOLIVETCPCONNECTION_H_
#define SRC_SERVER_VIDEOLIVETCPCONNECTION_H_

#ifndef VLSERVER_HAND
#define VLSERVER_HAND "vlserver"
#endif

#include "Poco/Net/TCPServerConnection.h"
#include "Poco/Net/StreamSocket.h"
#include <string.h>

#include "VideoLiveObserver.h"
#include "VideoLiveObservable.h"

#include "../utils.h"

using namespace Poco::Net;

class VideoLiveTCPConnection: public TCPServerConnection, public VideoLiveObserver
{

private:
	bool firstI;

public:
	VideoLiveTCPConnection(const StreamSocket& s);
	virtual ~VideoLiveTCPConnection()
	{
	}
	void run();
	void doWork();
	bool hand();
	bool sendData(const void* buffer, int length);

};

#endif /* SRC_SERVER_VIDEOLIVETCPCONNECTION_H_ */
