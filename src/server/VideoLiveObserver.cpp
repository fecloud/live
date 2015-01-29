/*
 * VideoLiveObserver.cpp
 *
 *  Created on: Jan 24, 2015
 *      Author: ouyangfeng
 */
#include <iostream>

#include "VideoLiveObserver.h"
#include "../base/utils.h"

using namespace std;

VideoLiveObserver::VideoLiveObserver()
{
	pthread_mutex_init(&mt, NULL);
	pthread_cond_init(&ct, NULL);

	seqhead.bufptr = NULL;

	buffer = 0;
	bufferLength = 0;
	buffer = new char[OUTPUT_BUFFER];
}

VideoLiveObserver::~VideoLiveObserver()
{
	pthread_mutex_destroy(&mt);
	pthread_cond_destroy(&ct);

	if (seqhead.bufptr > 0)
	{
		free(seqhead.bufptr);
		seqhead.bufsize = seqhead.length = 0;
	}

	if(buffer)
	{
		delete [] buffer;
	}
	
	resetVencOutputBuffer();
}

void VideoLiveObserver::cpyVencSeqHeader(VencSeqHeader* head)
{
	seqhead.bufptr = (unsigned char*) malloc(head->length);
	seqhead.bufsize = head->bufsize;
	seqhead.length = head->length;
	memcpy(seqhead.bufptr, head->bufptr, head->length);
}

void VideoLiveObserver::cpyVencOutputBuffer(VencOutputBuffer* output)
{
	resetVencOutputBuffer();

	bufferLength += output->size0;
	bufferLength += output->size1;
	if (output->size0 > 0)
	{
		memcpy(buffer, output->ptr0, output->size0);
	}
	if (output->size1 > 0)
	{
		memcpy(buffer + output->size0, output->ptr1, output->size1);
	}

}

void VideoLiveObserver::resetVencOutputBuffer()
{
	bufferLength = 0;
}

void VideoLiveObserver::update(VencOutputBuffer* output)
{
	pthread_mutex_unlock(&mt);
	cpyVencOutputBuffer(output);
	pthread_cond_signal(&ct);
	pthread_mutex_unlock(&mt);
}

