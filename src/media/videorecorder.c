/*
 * videorecorder.c
 *
 *  Created on: 2015-1-17
 *      Author: maygolf
 */
#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include "videorecorder.h"

int setDataCallBack(struct Video_Recorder* p, void* cookie, void* callBack)
{
	if (p)
	{
		p->callback = callBack;
		p->cookie = cookie;
		return 1;
	}
	return 0;
}

Video_Recorder* create_video_recorder(int width, int height)
{
	Video_Recorder* context = NULL;
	context = (Video_Recorder*) malloc(sizeof(Video_Recorder));
	memset(context, 0, sizeof(Video_Recorder));
	context->width = width;
	context->height = height;

	context->setDataCallBack = setDataCallBack;
	return context;

}

static int cameraSourceCallback(void *cookie, void *data)
{
//	printf("cameraSourceCallback %lld\n",current_time());
	Video_Recorder* recorder = (Video_Recorder*) cookie;

	cedarv_encoder_t* venc_device = recorder->venc_device;
	AWCameraDevice* cameraDevice = recorder->cameraDevice;

	VencInputBuffer input_buffer;
	int result = 0;
	struct v4l2_buffer *p_buf = (struct v4l2_buffer *) data;
	v4l2_mem_map_t* p_v4l2_mem_map = GetMapmemAddress(getV4L2ctx(cameraDevice));

	void *buffer = (void *) p_v4l2_mem_map->mem[p_buf->index];
	/* get input buffer*/
	result = venc_device->ioctrl(venc_device, VENC_CMD_GET_ALLOCATE_INPUT_BUFFER, &input_buffer);
	if (result == 0)
	{
		//printf("s:%lld\n",current_time());
		YUV422To420((unsigned char*) buffer, input_buffer.addrvirY, recorder->width, recorder->height);
		waterMarkShowTime(recorder->waterMark, input_buffer.addrvirY, recorder->width, recorder->height, 10, 10);
		//printf("e:%lld\n",current_time());
		input_buffer.addrvirC = input_buffer.addrvirY + recorder->width * recorder->height;
		venc_device->ioctrl(venc_device, VENC_CMD_FLUSHCACHE_ALLOCATE_INPUT_BUFFER, &input_buffer);
		result = venc_device->ioctrl(venc_device, VENC_CMD_ENQUENE_INPUT_BUFFER, &input_buffer);
		if (result < 0)
		{
			usleep(1000);
		}
	}

	cameraDevice->returnFrame(cameraDevice, p_buf->index);
	return 1;
}

static void* encoderThread(void* pThreadData)
{

	Video_Recorder* recorder = (Video_Recorder*) pThreadData;
	cedarv_encoder_t* venc_device = recorder->venc_device;

	VencInputBuffer input_buffer;
	int result = 0;

	VencOutputBuffer output_buffer;

	while (recorder->mstart)
	{

		memset(&input_buffer, 0, sizeof(VencInputBuffer));

		// dequene buffer from input buffer quene;
		result = venc_device->ioctrl(venc_device, VENC_CMD_DEQUENE_INPUT_BUFFER, &input_buffer);

		if (result < 0)
		{
			usleep(1000);
			continue;
		}
		//cout << "enquene input buffer not empty" << endl;

//
//		cedarx_cache_op(input_buffer.addrvirY,
//						input_buffer.addrvirY + recorder->waterMark->bgInfo.width * recorder->waterMark->bgInfo.height * 3/2, 0);

		result = venc_device->ioctrl(venc_device, VENC_CMD_ENCODE, &input_buffer);

		// return the buffer to the alloc buffer quene after encoder
		venc_device->ioctrl(venc_device, VENC_CMD_RETURN_ALLOCATE_INPUT_BUFFER, &input_buffer);

		if (result == 0)
		{
			memset(&output_buffer, 0, sizeof(VencOutputBuffer));
			result = venc_device->ioctrl(venc_device, VENC_CMD_GET_BITSTREAM, &output_buffer);

			//callback header
			if (recorder->callback)
			{
				recorder->callback(1, recorder->cookie, &output_buffer);
			}

			if (result == 0)
			{
				venc_device->ioctrl(venc_device, VENC_CMD_RETURN_BITSTREAM, &output_buffer);
			}
		}
		else
		{
			CLOG("encoder fatal error");
		}
	}

	return (void*) 0;

}

int start_video_recorder(Video_Recorder* recorder)
{
	// init base config param
	recorder->base_cfg.codectype = VENC_CODEC_H264;

	recorder->base_cfg.framerate = CAP_FPS;
	recorder->base_cfg.input_width = recorder->width;
	recorder->base_cfg.input_height = recorder->height;
	recorder->base_cfg.dst_width = recorder->width;
	recorder->base_cfg.dst_height = recorder->height;
	recorder->base_cfg.maxKeyInterval = H264_IDR;
	recorder->base_cfg.inputformat = VENC_PIXEL_YUV420; //uv combined
	recorder->base_cfg.targetbitrate = H264_TB;

	// init allocate param
	recorder->alloc_parm.buffernum = 4;

	cedarx_hardware_init(0);
	CLOG("%s", "cedarx_hardware_init");
	CLOG("AWCodec version %s", getCodecVision());

	recorder->waterMark = malloc(sizeof(WaterMark));
	memset(recorder->waterMark, 0x0, sizeof(WaterMark));
	waterMark_init(recorder->waterMark);

	recorder->venc_device = cedarvEncInit();

	recorder->venc_device->ioctrl(recorder->venc_device, VENC_CMD_BASE_CONFIG, &recorder->base_cfg);
	recorder->venc_device->ioctrl(recorder->venc_device, VENC_CMD_ALLOCATE_INPUT_BUFFER, &recorder->alloc_parm);
	recorder->venc_device->ioctrl(recorder->venc_device, VENC_CMD_OPEN, 0);
	recorder->venc_device->ioctrl(recorder->venc_device, VENC_CMD_HEADER_DATA, &recorder->header_data);

	//callback header
	if (recorder->callback)
	{
		recorder->callback(0, recorder->cookie, &recorder->header_data);
	}

	recorder->cameraDevice = CreateCamera(recorder->width, recorder->height);
	CLOG("%s", "create camera ok");

	recorder->cameraDevice->setCameraDatacallback(recorder->cameraDevice, recorder, (void*) &cameraSourceCallback);

	recorder->cameraDevice->startCamera(recorder->cameraDevice);

	/* start encoder */
	recorder->mstart = 1;
	/* create encode thread */
	int err = pthread_create(&recorder->thread_enc_id, NULL, encoderThread, recorder);
	if (err || !recorder->thread_enc_id)
	{
		CLOG("%s", "Create thread_enc_id fail !");
	}
	else
	{
		void* status;
		pthread_join(recorder->thread_enc_id, &status);
	}

	return 1;
}

static void* recorder_newthread_worker(void* cookie)
{
	start_video_recorder((Video_Recorder*) cookie);
	return (void*) 1;
}

void start_video_recorder_newthread(Video_Recorder* recorder)
{
	pthread_create(&recorder->thread_recorder, NULL, recorder_newthread_worker, recorder);
}

int stop_video_recorder(Video_Recorder* recorder)
{
	if (!recorder)
		return 0;

	recorder->mstart = 0;
	recorder->cameraDevice->stopCamera(recorder->cameraDevice);

	DestroyCamera(recorder->cameraDevice);
	recorder->cameraDevice = NULL;

	waterMark_exit(recorder->waterMark);
	free(recorder->waterMark);
	recorder->waterMark = NULL;

	recorder->venc_device->ioctrl(recorder->venc_device, VENC_CMD_CLOSE, 0);
	cedarvEncExit(recorder->venc_device);
	recorder->venc_device = NULL;

	cedarx_hardware_exit(0);

	return 1;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */
