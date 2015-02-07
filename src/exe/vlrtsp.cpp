/*
 * vlrtsp.cpp
 *
 *  Created on: 2015年1月29日
 *      Author: maygolf
 */

/*
 * main.cpp
 *
 *  Created on: 2015年1月22日
 *      Author: maygolf
 */

#include <rtsp/H264FramedLiveSource.h>
#include <rtsp/H264LiveVideoServerMediaSubssion.h>
#include "live555/liveMedia/liveMedia.hh"
#include "live555/BasicUsageEnvironment/BasicUsageEnvironment.hh"

UsageEnvironment* env;

// To make the second and subsequent client for each stream reuse the same
// input stream as the first client (rather than playing the file from the
// start for each client), change the following "False" to "True":
Boolean reuseFirstSource = False;

// To stream *only* MPEG-1 or 2 video "I" frames
// (e.g., to reduce network bandwidth),
// change the following "False" to "True":
Boolean iFramesOnly = False;

static void announceStream(RTSPServer* rtspServer, ServerMediaSession* sms, char const* streamName, char const* inputFileName); // fwd

static char newMatroskaDemuxWatchVariable;
static MatroskaFileServerDemux* demux;
static void onMatroskaDemuxCreation(MatroskaFileServerDemux* newDemux, void* /*clientData*/)
{
	demux = newDemux;
	newMatroskaDemuxWatchVariable = 1;
}
#ifndef NO_MAIN
int main(int argc, char** argv)
{
	// Begin by setting up our usage environment:
	TaskScheduler* scheduler = BasicTaskScheduler::createNew();
	env = BasicUsageEnvironment::createNew(*scheduler);

	UserAuthenticationDatabase* authDB = NULL;
#ifdef ACCESS_CONTROL
	// To implement client access control to the RTSP server, do the following:
	authDB = new UserAuthenticationDatabase;
	authDB->addUserRecord("username1", "password1");// replace these with real strings
	// Repeat the above with each <username>, <password> that you wish to allow
	// access to the server.
#endif

	// Create the RTSP server:
	RTSPServer* rtspServer = RTSPServer::createNew(*env, 10000, authDB);
	if (rtspServer == NULL)
	{
		*env << "Failed to create RTSP server: " << env->getResultMsg() << "\n";
		exit(1);
	}

	char const* descriptionString = "Session streamed by \"testOnDemandRTSPServer\"";

	// Set up each of the possible streams that can be served by the
	// RTSP server.  Each such stream is implemented using a
	// "ServerMediaSession" object, plus one or more
	// "ServerMediaSubsession" objects for each audio/video substream.

	// A H.264 video elementary stream:
	{
		char const* streamName = "demo";
		char const* inputFileName = "test.264";
		ServerMediaSession* sms = ServerMediaSession::createNew(*env, streamName, streamName, descriptionString);
		sms->addSubsession(H264LiveVideoServerMediaSubssion::createNew(*env, inputFileName, reuseFirstSource));  //修改为自己实现的servermedia  H264LiveVideoServerMediaSubssion
		rtspServer->addServerMediaSession(sms);

		announceStream(rtspServer, sms, streamName, inputFileName);
	}

	// Also, attempt to create a HTTP server for RTSP-over-HTTP tunneling.
	// Try first with the default HTTP port (80), and then with the alternative HTTP
	// port numbers (8000 and 8080).

	//if (rtspServer->setUpTunnelingOverHTTP(80) || rtspServer->setUpTunnelingOverHTTP(8000) || rtspServer->setUpTunnelingOverHTTP(8080)) {
	//  *env << "\n(We use port " << rtspServer->httpServerPortNum() << " for optional RTSP-over-HTTP tunneling.)\n";
	//} else {
	//  *env << "\n(RTSP-over-HTTP tunneling is not available.)\n";
	//}

	env->taskScheduler().doEventLoop(); // does not return

	return 0; // only to prevent compiler warning
}
#endif

static void announceStream(RTSPServer* rtspServer, ServerMediaSession* sms, char const* streamName, char const* inputFileName)
{
	char* url = rtspServer->rtspURL(sms);
	UsageEnvironment& env = rtspServer->envir();
	env << "\n\"" << streamName << "\" stream, from the file \"" << inputFileName << "\"\n";
	env << "Play this stream using the URL \"" << url << "\"\n";
	delete[] url;
}
