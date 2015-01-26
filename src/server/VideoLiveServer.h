/*
 * VideoLiveServer.h
 *
 *  Created on: Jan 23, 2015
 *      Author: ouyangfeng
 */

#ifndef SRC_SERVER_VIDEOLIVESERVER_H_
#define SRC_SERVER_VIDEOLIVESERVER_H_

#include "Poco/Util/ServerApplication.h"
#include "Poco/Util/Application.h"

using Poco::Util::ServerApplication;
using Poco::Util::Application;

class VideoLiveServer: public ServerApplication
{

public:
	VideoLiveServer();
	virtual ~VideoLiveServer();
	void init();

protected:
	void initialize(Application& self);
	void uninitialize();
	int main(const std::vector<std::string>& args);

};

#endif /* SRC_SERVER_VIDEOLIVESERVER_H_ */
