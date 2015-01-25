/*
 * VideoLiveTCPConnection.h
 *
 *  Created on: Jan 23, 2015
 *      Author: ouyangfeng
 */

#ifndef SRC_SERVER_VIDEOLIVETCPCONNECTION_H_
#define SRC_SERVER_VIDEOLIVETCPCONNECTION_H_

#include "Poco/Net/TCPServerConnection.h"
#include "Poco/Net/StreamSocket.h"
#include <string.h>

#include "VideoLiveObserver.h"
#include "VideoLiveObservable.h"

using namespace Poco::Net;

class VideoLiveTCPConnection: public TCPServerConnection, public VideoLiveObserver
{

private :
	 bool firstI;

public:
	VideoLiveTCPConnection(const StreamSocket& s);
	virtual ~VideoLiveTCPConnection()
	{
	}
	void run();
	void doWork();

};

#endif /* SRC_SERVER_VIDEOLIVETCPCONNECTION_H_ */
