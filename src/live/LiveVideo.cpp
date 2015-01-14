/*
 * live.cpp
 *
 *  Created on: 2015-1-8
 *      Author: maygolf
 */

#include "../Utils.h"

#include "LiveVideo.h"

using namespace std;

bool VideoLive::init()
{

	// init base config param
	this->base_cfg.codectype = VENC_CODEC_H264;

	this->base_cfg.framerate = 30;
	this->base_cfg.input_width = width;
	this->base_cfg.input_height = height;
	this->base_cfg.dst_width = width;
	this->base_cfg.dst_height = height;
	this->base_cfg.maxKeyInterval = 25;
	this->base_cfg.inputformat = VENC_PIXEL_YUV420; //uv combined
	this->base_cfg.targetbitrate = 2 * 1024 * 1024;

	// init allocate param
	this->alloc_parm.buffernum = 4;
	return true;
}

VideoLive::VideoLive(char* server, int width, int height)
{
	output = new RTMPOutPutStream(server);
	this->width = width;
	this->height = height;
	this->mstart = 0;
	flvEncoder = NULL;
}

VideoLive::~VideoLive()
{
	if (output)
		delete output;
	output = NULL;

	if (venc_device)
		free(venc_device);
	venc_device = NULL;

	if (flvEncoder)
		delete flvEncoder;
	flvEncoder = NULL;

}

bool VideoLive::start()
{
	cedarx_hardware_init(0);
	cout << "cedarx_hardware_init" << endl;
	cout << "AWCodec version " << getCodecVision() << endl;

	venc_device = cedarvEncInit();

	venc_device->ioctrl(venc_device, VENC_CMD_BASE_CONFIG, &base_cfg);
	venc_device->ioctrl(venc_device, VENC_CMD_ALLOCATE_INPUT_BUFFER,
			&alloc_parm);
	venc_device->ioctrl(venc_device, VENC_CMD_OPEN, 0);
	venc_device->ioctrl(venc_device, VENC_CMD_HEADER_DATA, &header_data);

	if (output)
	{
		flvEncoder = new FLVEncoder(output);

		if (output->open())
		{
			//解析sps pps
			H264MemReader reader;
			reader.setVencSeqHeader(&header_data);
			int i = 0;
			while (true)
			{ //读取sps pss
				H264NALU* bytes = (H264NALU*) reader.reader();
				if (bytes)
				{
					flvEncoder->encoder(bytes);
					delete bytes;
					bytes = NULL;
					i++;
				}
				else
				{
					//读取失败
					break;
				}

			}
			if (i == 2)
			{
				startCameraAndEnCoder();
			}
			return true;
		}

	}
	return false;
}

int cameraSourceCallback(void *cookie, void *data)
{
	cout << "cameraSourceCallback:" << time(NULL) << endl;
	VideoLive* videoLive = (VideoLive*) cookie;

	cedarv_encoder_t* venc_device = videoLive->venc_device;
	AWCameraDevice* cameraDevice = videoLive->cameraDevice;

	VencInputBuffer input_buffer;
	int result = 0;
	struct v4l2_buffer *p_buf = (struct v4l2_buffer *) data;
	v4l2_mem_map_t* p_v4l2_mem_map = GetMapmemAddress(getV4L2ctx(cameraDevice));

	void *buffer = (void *) p_v4l2_mem_map->mem[p_buf->index];
/*
	result = venc_device->ioctrl(venc_device,
			VENC_CMD_GET_ALLOCATE_INPUT_BUFFER, &input_buffer);
	//cout << "VENC_CMD_GET_ALLOCATE_INPUT_BUFFER result:" <<  result << endl;
	if (result == 0)
	{
		YUV422To420((unsigned char*) buffer, input_buffer.addrvirY,videoLive->width, videoLive->height);
		venc_device->ioctrl(venc_device, VENC_CMD_FLUSHCACHE_ALLOCATE_INPUT_BUFFER, &input_buffer);
		//cout << " VENC_CMD_FLUSHCACHE_ALLOCATE_INPUT_BUFFER" << endl;
		result = venc_device->ioctrl(venc_device, VENC_CMD_ENQUENE_INPUT_BUFFER, &input_buffer);
		//cout << " VENC_CMD_ENQUENE_INPUT_BUFFER result:" <<  result << endl;
		if (result < 0)
		{
		//	cout << "enquene input buffer is full" << endl;
			usleep(10 * 1000);
		}
	}
	*/
	cameraDevice->returnFrame(cameraDevice, p_buf->index);
	return 1;
}

void* encoderThread(void* pThreadData)
{

	VideoLive* videoLive = (VideoLive*) pThreadData;
	cedarv_encoder_t* venc_device = videoLive->venc_device;

	VencInputBuffer input_buffer;
	int result = 0;

	VencOutputBuffer output_buffer;

	while (videoLive->mstart)
	{

		memset(&input_buffer, 0, sizeof(VencInputBuffer));

		// dequene buffer from input buffer quene;
		result = venc_device->ioctrl(venc_device, VENC_CMD_DEQUENE_INPUT_BUFFER, &input_buffer);

		if (result < 0)
		{
			usleep(10 * 1000);
			continue;
		}
		//cout << "enquene input buffer not empty" << endl;

		result = venc_device->ioctrl(venc_device, VENC_CMD_ENCODE, &input_buffer);

		//cout << "VENC_CMD_ENCODE result:" <<  result << endl;
		// return the buffer to the alloc buffer quene after encoder
		venc_device->ioctrl(venc_device, VENC_CMD_RETURN_ALLOCATE_INPUT_BUFFER, &input_buffer);

		if (result == 0)
		{
			memset(&output_buffer, 0, sizeof(VencOutputBuffer));
			result = venc_device->ioctrl(venc_device, VENC_CMD_GET_BITSTREAM, &output_buffer);

			H264MemReader reader;
			reader.setVencOutputBuffer(&output_buffer);
			while (true)
			{
				H264NALU* bytes = (H264NALU*) reader.reader();
				if (bytes)
				{
					videoLive->flvEncoder->encoder(bytes);
					delete bytes;
					bytes = NULL;
				}
				else
				{
					//读取失败
					break;
				}

			}


			if (result == 0)
			{
				venc_device->ioctrl(venc_device, VENC_CMD_RETURN_BITSTREAM, &output_buffer);
			}
		}
		else
		{
			cout << "encoder fatal error" << endl;
		}
	}

	return (void*) 0;

}

bool VideoLive::startCameraAndEnCoder()
{
	cameraDevice = CreateCamera(width, height);
	cout << "create camera ok" << endl;

	cameraDevice->setCameraDatacallback(cameraDevice, this,
			(void*) &cameraSourceCallback);

	cameraDevice->startCamera(cameraDevice);

	/* start encoder */
	mstart = 1;
	/* create encode thread
	int err = pthread_create(&thread_enc_id, NULL, encoderThread,this);
	if (err || !thread_enc_id)
	{
		cout << "Create thread_enc_id fail !\n" << endl;
	}else
	{
		void* status;
		pthread_join(thread_enc_id,&status);
	}
*/
	sleep(10);

	return true;
}

bool VideoLive::stop()
{
	cameraDevice->stopCamera(cameraDevice);

	DestroyCamera(cameraDevice);
	cameraDevice = NULL;

	venc_device->ioctrl(venc_device, VENC_CMD_CLOSE, 0);
	cedarvEncExit(venc_device);
	venc_device = NULL;

	cedarx_hardware_exit(0);

	return false;
}
