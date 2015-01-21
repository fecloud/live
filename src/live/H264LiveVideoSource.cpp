/*
 * H264LiveVideoSource.cpp
 *
 *  Created on: 2015年1月21日
 *      Author: maygolf
 */

#include "H264LiveVideoSource.h"

H264LiveVideoSource* H264LiveVideoSource::createNew(UsageEnvironment& env, Boolean deleteBufferOnClose, unsigned preferredFrameSize, unsigned playTimePerFrame, int fd_pipe[2])
{

	H264LiveVideoSource* videosource = new H264LiveVideoSource(env, deleteBufferOnClose, preferredFrameSize, playTimePerFrame, fd_pipe);
	return videosource;

}

H264LiveVideoSource::H264LiveVideoSource(UsageEnvironment& env, Boolean deleteBufferOnClose, unsigned preferredFrameSize, unsigned playTimePerFrame, int fd_pipe[2]) :
		FramedSource(env), fDeleteBufferOnClose(deleteBufferOnClose), fPreferredFrameSize(preferredFrameSize), fPlayTimePerFrame(playTimePerFrame), fLastPlayTime(0)
{

}

H264LiveVideoSource::~H264LiveVideoSource()
{

}

void H264LiveVideoSource::doGetNextFrame()
{

}

