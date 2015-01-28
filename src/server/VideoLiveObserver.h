/*
 * VideoLiveObserver.h
 *
 *  Created on: Jan 24, 2015
 *      Author: ouyangfeng
 */

#ifndef SRC_SERVER_VIDEOLIVEOBSERVER_H_
#define SRC_SERVER_VIDEOLIVEOBSERVER_H_

#include "media/videorecorder.h"

class VideoLiveObserver
{

protected:
	pthread_mutex_t mt;
	pthread_cond_t ct;
	VencSeqHeader seqhead;
	VencOutputBuffer buffer;
	void cpyVencSeqHeader(VencSeqHeader* head);
	void cpyVencOutputBuffer(VencOutputBuffer*);
	void resetVencOutputBuffer();

public:
	VideoLiveObserver();
	virtual ~VideoLiveObserver();
	void update(VencOutputBuffer*);

};

#endif /* SRC_SERVER_VIDEOLIVEOBSERVER_H_ */
