/*
 * VideoLiveObservable.h
 *
 *  Created on: Jan 24, 2015
 *      Author: ouyangfeng
 */

#ifndef SRC_SERVER_VIDEOLIVEOBSERVABLE_H_
#define SRC_SERVER_VIDEOLIVEOBSERVABLE_H_

#include <pthread.h>
#include <list>

#include "../utils.h"
#include "../media/videorecorder.h"

#include "VideoLiveObserver.h"

using namespace std;

class VideoLiveObservable
{

private:
	list<VideoLiveObserver*> obables;
	Video_Recorder* recorder;
	VencSeqHeader seqhead;
	pthread_mutex_t mt;

protected:
	VideoLiveObservable();
	virtual ~VideoLiveObservable();

public:
	static VideoLiveObservable* createNew();
	static void destory(VideoLiveObservable*);
	VencSeqHeader* registerVideoLiveObserver(VideoLiveObserver*);
	void unRegisterVideoLiveObserver(VideoLiveObserver*);
	void notification(VencOutputBuffer*);
	void cpyVencSeqHeader(VencSeqHeader* );

};

#endif /* SRC_SERVER_VIDEOLIVEOBSERVABLE_H_ */
