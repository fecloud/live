/*
 * H264FramedLiveSource.cpp
 *
 *  Created on: 2015��1��22��
 *      Author: maygolf
 */

/*
 * Filename:  H264FramedLiveSource.cpp
 * Auther:  mlj
 * Create date: 2013/ 1/22
 */

#include <rtsp/H264FramedLiveSource.h>

using namespace std;

H264FramedLiveSource::H264FramedLiveSource(UsageEnvironment& env, char const* fileName, unsigned preferredFrameSize, unsigned playTimePerFrame) :
		FramedSource(env)
{
	fp = fopen(fileName, "rb");
}

H264FramedLiveSource* H264FramedLiveSource::createNew(UsageEnvironment& env, char const* fileName, unsigned preferredFrameSize /*= 0*/, unsigned playTimePerFrame /*= 0*/)
{
	H264FramedLiveSource* newSource = new H264FramedLiveSource(env, fileName, preferredFrameSize, playTimePerFrame);

	return newSource;
}

H264FramedLiveSource::~H264FramedLiveSource()
{
	fclose(fp);
}

long filesize(FILE *stream)
{
	long curpos, length;
	curpos = ftell(stream);
	fseek(stream, 0L, SEEK_END);
	length = ftell(stream);
	fseek(stream, curpos, SEEK_SET);
	return length;
}

void H264FramedLiveSource::doGetNextFrame()
{
	cout << "doGetNextFrame fMaxSize:" << fMaxSize << endl;
	if (filesize(fp) > fMaxSize)
		fFrameSize = fread(fTo, 1, fMaxSize, fp);
	else
	{
		fFrameSize = fread(fTo, 1, filesize(fp), fp);
		fseek(fp, 0, SEEK_SET);
	}
	//fFrameSize = fMaxSize;
	nextTask() = envir().taskScheduler().scheduleDelayedTask(0, (TaskFunc*) FramedSource::afterGetting, this);
	return;
}
