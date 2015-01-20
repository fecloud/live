/*
 * videorecorder.h
 *
 *  Created on: 2015-1-8
 *      Author: maygolf
 */
#ifndef VIDEO_RECORDER_H
#define VIDEO_RECORDER_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

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

#include "water_mark.h"
#include "../utils.h"


typedef void (*DataCallBack)(int type, void* cookie,void* data);

typedef struct Video_Recorder
{
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
	DataCallBack callback;
	void* cookie;
	int (*setDataCallBack)(struct Video_Recorder*p, void* cookie, void* callBack);
	WaterMark*	waterMark;
} Video_Recorder;


Video_Recorder* create_video_recorder(int width,int height);

int start_video_recorder(Video_Recorder*);

int stop_video_recorder(Video_Recorder*);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* VIDEO_RECORDER_H */
