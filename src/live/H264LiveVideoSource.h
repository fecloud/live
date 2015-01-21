/*
 * H264LiveVideoSource.h
 *
 *  Created on: 2015年1月21日
 *      Author: maygolf
 */
#ifndef H264_LIVEVIDEOSOURCE_H
#define H264_LIVEVIDEOSOURCE_H

#include "../live555/UsageEnvironment/UsageEnvironment.hh"
#include "../live555/liveMedia/FramedSource.hh"

class H264LiveVideoSource: public FramedSource
{

public:
	static H264LiveVideoSource* createNew(UsageEnvironment& env, Boolean deleteBufferOnClose = True, unsigned preferredFrameSize = 0, unsigned playTimePerFrame = 0,
			int fd_pipe[2] = NULL);

	void seekToByteAbsolute(u_int64_t byteNumber, u_int64_t numBytesToStream = 0);
	// if "numBytesToStream" is >0, then we limit the stream to that number of bytes, before treating it as EOF
	void seekToByteRelative(int64_t offset);

protected:
	H264LiveVideoSource(UsageEnvironment& env, Boolean deleteBufferOnClose, unsigned preferredFrameSize, unsigned playTimePerFrame, int fd_pipe[2]);
	~H264LiveVideoSource();

private:
	// redefined virtual functions:
	virtual void doGetNextFrame();

private:
  int fd[2];
//  frame_I* fBuffer;
  Boolean fDeleteBufferOnClose;
  unsigned fPreferredFrameSize;
  unsigned fPlayTimePerFrame;
  unsigned fLastPlayTime;
  Boolean fLimitNumBytesToStream;
  u_int64_t fNumBytesToStream; // used iff "fLimitNumBytesToStream" is True

};


//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////H264LiveVideoServerMediaSubsession//////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////


#include "../live555/liveMedia/H264VideoFileServerMediaSubsession.hh"

class H264LiveVideoServerMediaSubsession: public OnDemandServerMediaSubsession
{
public:
	static H264LiveVideoServerMediaSubsession*
	createNew(UsageEnvironment& env, Boolean reuseFirstSource, int fifo[2]);
	void checkForAuxSDPLine1();
	void afterPlayingDummy1();
private:
	H264LiveVideoServerMediaSubsession(UsageEnvironment& env, Boolean reuseFirstSource, int fifo[2]);
	virtual ~H264LiveVideoServerMediaSubsession();

	void setDoneFlag()
	{
		fDoneFlag = ~0;
	}

private:
	// redefined virtual functions
	virtual FramedSource* createNewStreamSource(unsigned clientSessionId, unsigned& estBitrate);
	virtual RTPSink* createNewRTPSink(Groupsock* rtpGroupsock, unsigned char rtpPayloadTypeIfDynamic, FramedSource* inputSource);
	virtual char const* getAuxSDPLine(RTPSink* rtpSink, FramedSource* inputSource);

private:
//	frame_I *pNal;
	int m_fifo[2];
	char* fAuxSDPLine;
	char fDoneFlag; // used when setting up "fAuxSDPLine"
	RTPSink* fDummyRTPSink; // ditto

};

#endif /* H264LIVEVIDEOSOURCE_H */

