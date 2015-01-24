/*
 * VideoLiveObserver.cpp
 *
 *  Created on: Jan 24, 2015
 *      Author: ouyangfeng
 */

#include "VideoLiveObserver.h"

VideoLiveObserver::VideoLiveObserver()
{
	pthread_mutex_init(&mt, NULL);
	pthread_cond_init(&ct, NULL);
	buffer.id = 0;
	buffer.ptr0 = buffer.ptr1 = 0;
	buffer.pts = 0;
	buffer.size0 = buffer.size1 = 0;
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

	resetVencOutputBuffer();
}

void VideoLiveObserver::cpyVencSeqHeader(VencSeqHeader* head)
{
	seqhead.bufptr = (unsigned char*) malloc(head->length);
	seqhead.bufsize = head->bufsize;
	seqhead.length = head->length;
}

void VideoLiveObserver::cpyVencOutputBuffer(VencOutputBuffer* output)
{
	resetVencOutputBuffer();

	buffer.id = output->id;
	buffer.size0 = output->size0;
	buffer.size1 = output->size1;
	if (output->size0 > 0)
	{
		buffer.ptr0 = (unsigned char*) malloc(output->size0);
		memcpy(buffer.ptr0, output->ptr0, output->size0);
	}
	if (output->size1 > 0)
	{
		buffer.ptr1 = (unsigned char*) malloc(output->size1);
		memcpy(buffer.ptr1, output->ptr1, output->size1);
	}

}

void VideoLiveObserver::resetVencOutputBuffer()
{
	buffer.id = 0;
	buffer.pts = 0;
	if (buffer.ptr0 > 0)
	{
		free(buffer.ptr0);
		buffer.ptr0 = NULL;
		buffer.size0 = 0;
	}
	if (buffer.ptr1 > 0)
	{
		free(buffer.ptr1);
		buffer.ptr1 = NULL;
		buffer.size1 = 0;
	}
}

void VideoLiveObserver::update(VencOutputBuffer* output)
{
	pthread_mutex_lock(&mt);
	cpyVencOutputBuffer(output);
	pthread_cond_signal(&ct);
	pthread_mutex_unlock(&mt);
}

