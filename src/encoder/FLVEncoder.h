/*
 * FLVEncoder.h
 *
 *  Created on: 2014-12-25
 *      Author: maygolf
 */

#ifndef FLVENCODER_H_
#define FLVENCODER_H_

#include <iostream>
#include <stdio.h>

#include "../flv/amf.h"
#include "../io/MediaOutputStream.h"
#include "../h264/H264NALU.h"
#include "../h264/H264Reader.h"
#include "../flv/lang/Struct.h"
#include "SpsDecode.h"

using namespace std;

#define  AVC_PACKAGE 0x0
#define  AVC_FRAME 0x1
#define  AVC_END 0x2

class FLVEncoder {

private:
	H264Reader* in;
	MediaOutputStream* out;
	H264NALU* sps;
	H264NALU* pps;
	H264NALU* sei;
	H264NALU* idr;
	bool findSPSPPS;
	bool findSEIIDR;
	bool checkInAndOut();
	bool closeInAndOut();
	Bytes* buffer;

protected:
	bool encoderSPSPPS();
	bool encoderOnMetaData();
	bool encodeSEI();
	bool encodeFrame(H264NALU*);
	bool encodeEndFrame();

public:
	FLVEncoder();
	FLVEncoder(MediaOutputStream* out);
	FLVEncoder(H264Reader* in, MediaOutputStream* out);
	virtual ~FLVEncoder();
	void encoder();
	/**
	 * 编码指定的数据
	 */
	bool encoder(H264NALU*);

};

#endif /* FLVENCODER_H_ */
