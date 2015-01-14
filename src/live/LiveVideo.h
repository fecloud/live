/*
 * live.h
 *
 *  Created on: 2015-1-8
 *      Author: maygolf
 */

#ifndef LIVE_H_
#define LIVE_H_

#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>

#include "../vencoder/CDX_Debug.h"
#include "../vencoder/include_vencoder/H264encLibApi.h"
#include "../vencoder/include_vencoder/venc.h"
#include "../camera/CameraSource.h"
#include "../vencoder/include_vencoder/text.h"
#include "../camera/V4L2.h"
#include "../vencoder/cedarv_osal_linux.h"

#include "../encoder/FLVEncoder.h"
#include "../h264/H264NALU.h"
#include "../io/RTMPOutPutStream.h"
#include "H264MemReader.h"

class VideoLive
{

public:
	cedarv_encoder_t* venc_device;
	VencBaseConfig base_cfg;
	VencInputBuffer input_buffer;
	VencOutputBuffer output_buffer;
	VencAllocateBufferParam alloc_parm;
	VencSeqHeader header_data;
	AWCameraDevice *cameraDevice;
	pthread_t thread_enc_id;
	int mstart;
	int width;
	int height;
	FLVOutPutStream* output;
	FLVEncoder* flvEncoder;
	/**
	 * 启动采集和h264编码
	 */
	bool startCameraAndEnCoder();

	VideoLive(char*, int, int);
	~VideoLive();
	bool init();
	bool start();
	bool stop();
	FILE* outfile;

};

/**
 * 摄像头回调
 */
int cameraSourceCallback(void *cookie, void *data);

/**
 * AWCodec工作线程
 */
void* encoderThread(void* pThreadData);

#endif /* LIVE_H_ */
