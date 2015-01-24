/*
 * VideoLiveTCPConnectionFactory.h
 *
 *  Created on: Jan 23, 2015
 *      Author: ouyangfeng
 */

#ifndef SRC_SERVER_VIDEOLIVETCPCONNECTIONFACTORY_H_
#define SRC_SERVER_VIDEOLIVETCPCONNECTIONFACTORY_H_

#include "Poco/Net/TCPServerConnectionFactory.h"
#include "Poco/Net/TCPServerConnection.h"
#include "Poco/Net/StreamSocket.h"
#include <string.h>

#include "VideoLiveTCPConnection.h"

using namespace Poco;
using namespace Poco::Net;


class VideoLiveTCPConnectionFactory: public TCPServerConnectionFactory
{

public:
	VideoLiveTCPConnectionFactory()
    {

    }

    TCPServerConnection* createConnection(const StreamSocket& socket)
    {
        return new VideoLiveTCPConnection(socket);
    }


};




#endif /* SRC_SERVER_VIDEOLIVETCPCONNECTIONFACTORY_H_ */
