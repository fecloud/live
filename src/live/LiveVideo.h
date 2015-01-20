/*
 * live.h
 *
 *  Created on: 2015-1-8
 *      Author: maygolf
 */

#ifndef LIVE_H_
#define LIVE_H_

#include <iostream>

#include "../media/videorecorder.h"
#include "../encoder/FLVEncoder.h"
#include "../h264/H264NALU.h"
#include "../io/RTMPOutPutStream.h"
#include "H264MemReader.h"

class VideoLive
{

public:
	FLVOutPutStream* output;
	FLVEncoder* flvEncoder;
	Video_Recorder* recorder;
	VideoLive(char*, int, int);
	~VideoLive();
	bool init();
	bool start();
	bool stop();
//	FILE* outfile;

};

/**
 * 录制视频回调
 */
int recevie_data(int type, void* cookie, void* data);


#endif /* LIVE_H_ */
