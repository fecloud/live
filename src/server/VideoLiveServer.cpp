/*
 * VideLiveServer.cpp
 *
 *  Created on: Jan 23, 2015
 *      Author: ouyangfeng
 */

#include <iostream>

#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/TCPServer.h"
#include "Poco/Net/TCPServerParams.h"

#include "VideoLiveServer.h"
#include "VideoLiveTCPConnectionFactory.h"

using namespace Poco;
using namespace Poco::Net;

VideoLiveServer::VideoLiveServer()
{

}

VideoLiveServer::~VideoLiveServer()
{

}

int VideoLiveServer::main(const std::vector<std::string>& args)
{
	CPPLOG("VideLiveServer::main");
	std::string port = *(++args.begin());
	std::cout << port << std::endl;
	// 1. Bind a ServerSocket with an address
	ServerSocket serverSocket(atoi(port.c_str()));

	TCPServerParams::Ptr param = new TCPServerParams();
	param->setMaxThreads(3);

	// 2. Pass the ServerSocket to a TCPServer
	TCPServer server(new VideoLiveTCPConnectionFactory(), serverSocket,param);

	// 3. Start the TCPServer
	server.start();

	// 4. Wait for termination
	waitForTerminationRequest();

	// 5. Stop the TCPServer
	server.stop();

	return 1;
}

void VideoLiveServer::initialize(Application& self)
{
	ServerApplication::loadConfiguration();
	ServerApplication::initialize(self);
}

void VideoLiveServer::uninitialize()
{
	ServerApplication::uninitialize();
}

