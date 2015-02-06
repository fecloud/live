/*
 * FLVEncoder.cpp
 *
 *  Created on: 2014-12-25
 *      Author: maygolf
 */

#include "FLVEncoder.h"

FLVEncoder::FLVEncoder()
{
	in = NULL;
	out = NULL;
	findSPSPPS = false;
	findSEIIDR = false;
	buffer = new Bytes(1048510);
	sps = new H264NALU(1024);
	pps = new H264NALU(100);
	sei = new H264NALU(1024000);
	idr = new H264NALU(1024000);
}

FLVEncoder::FLVEncoder(MediaOutputStream* out)
{
	this->in = NULL;
	this->out = out;
	findSPSPPS = false;
	findSEIIDR = false;
	buffer = new Bytes(1048510);
	sps = new H264NALU(1024);
	pps = new H264NALU(100);
	sei = new H264NALU(1024000);
	idr = new H264NALU(1024000);
}

FLVEncoder::FLVEncoder(H264Reader* in, MediaOutputStream* out)
{
	this->in = in;
	this->out = out;
	findSPSPPS = false;
	findSEIIDR = false;
	buffer = new Bytes(1048510);
	sps = new H264NALU(1024);
	pps = new H264NALU(100);
	sei = new H264NALU(1024000);
	idr = new H264NALU(1024000);
}

FLVEncoder::~FLVEncoder()
{
	//cout << "~FLVEncoder" << endl;
	findSPSPPS = false;
	findSEIIDR = false;
	delete sps;
	delete pps;
	delete sei;
	delete idr;
	sps = pps = sei = idr = NULL;
	delete buffer;
	buffer = NULL;
}

bool FLVEncoder::checkInAndOut()
{
	if (in && out)
	{
		if (!in->open())
		{
			cout << "open input fail" << endl;
			return false;
		}
		if (!out->open())
		{
			cout << "open output fail" << endl;
			return false;
		}
		return true;
	}
	return false;
}

bool FLVEncoder::closeInAndOut()
{
	if (in && out)
	{
		if (in->close() && out->close())
		{
			return true;
		}
	}
	return false;
}

bool FLVEncoder::encoderOnMetaData()
{
	//cout << "encoderOnMetaData" << endl;
	Struct* st = new Struct();
	int width = 0;
	int height = 0;
	h264_decode_sps(sps->getData(), sps->getLength(), width, height);
	//cout << "w:" << width << "h:" << height << endl;
	st->put(new String("onMetaData"));
	ECMA_Array* array = new ECMA_Array();
	array->put("duration", new Number(0));
	array->put("width", new Number(width));
	array->put("height", new Number(height));
	array->put("videodatarate", new Number(0));
	array->put("framerate", new Number(25));
	array->put("videocodecid", new Number(7));
	array->put("encoder", new String("Lavf53.32.100"));
	array->put("filesize", new Number(0));
	st->put(array);

	buffer->clear();
	st->encoder(buffer);
	buffer->flip();
	//cout << "encoderOnMetaData data:length " << buffer->getLength() << endl;
	bool result = out->setParam(buffer);
	delete st;
	st = NULL;
	return result;
}

bool FLVEncoder::encoderSPSPPS()
{
	//cout << "encoderSPSPPS" << endl;
	buffer->clear();
	// 写入avc头
	buffer->put((char) ((KEYF_RAME << 4) | Codec_AVC_H264));
	buffer->put((char) AVC_PACKAGE);
	buffer->put((char) 0x0);
	buffer->put((char) 0x0);
	buffer->put((char) 0x0);

	// 写入AVC file forma
	buffer->put(0x1);
	buffer->put(sps->getData()[1]);
	buffer->put(sps->getData()[2]);
	buffer->put(sps->getData()[3]);

	// lengthSizeMinusOne
	buffer->put((char) 0xFF);

	buffer->put((char) 0xE1);
	// sps nums and data
	buffer->putChar(sps->getLength());
	buffer->put(sps->getData(), sps->getLength());

	// pps num and data
	buffer->put((char) 0x1);
	buffer->putChar(pps->getLength());
	buffer->put(pps->getData(), pps->getLength());
	buffer->flip();
	return out->writeHeaders(buffer);
}

bool FLVEncoder::encodeKeyFrame()
{
	buffer->clear();
	buffer->put((char) ((KEYF_RAME << 4) | Codec_AVC_H264));
	buffer->put((char) AVC_FRAME);
	buffer->put((char) 0x0);
	buffer->put((char) 0x0);
	buffer->put((char) 0x0);
	// 写入SPS信息
	buffer->putInt(sps->getLength());
	buffer->put(sps->getData(), sps->getLength());

	// 写入PPS信息
	buffer->putInt(pps->getLength());
	buffer->put(pps->getData(), pps->getLength());

	if (!findSEIIDR)
	{
		//有的h264文件没有sei
		if (sei->getLength())
		{
			buffer->putInt(sei->getLength());
			buffer->put(sei->getData(), sei->getLength());
		}
		findSEIIDR = true;
		buffer->putInt(idr->getLength());
		buffer->put(idr->getData(), idr->getLength());

		buffer->flip();
		return out->writeFrame(buffer, 1, 0);
	}

	buffer->putInt(idr->getLength());
	buffer->put(idr->getData(), idr->getLength());

	buffer->flip();
	return out->writeFrame(buffer, 2, idr->getTime());
}

bool FLVEncoder::encodeFrame(H264NALU* nalu)
{
	buffer->clear();
	buffer->put((char) ((INNER_FRAME << 4) | Codec_AVC_H264));
	buffer->put((char) AVC_FRAME);
	buffer->put((char) 0x0);
	buffer->put((char) 0x0);
	buffer->put((char) 0x0);
	// 写入h264长度加数据
	buffer->putInt(nalu->getLength());
	buffer->put(nalu->getData(), nalu->getLength());

	buffer->flip();
	return out->writeFrame(buffer, 3, nalu->getTime());
}

bool FLVEncoder::encodeEndFrame()
{
	buffer->clear();
	buffer->put((char) ((KEYF_RAME << 4) | Codec_AVC_H264));
	buffer->put((char) AVC_END);
	buffer->put((char) 0x0);
	buffer->put((char) 0x0);
	buffer->put((char) 0x0);

	buffer->flip();
	return out->writeFrame(buffer, 4, 0);
}

void FLVEncoder::encoder()
{
	if (checkInAndOut())
	{
		H264NALU* nalu = NULL;
		bool finish = false;
		while ((nalu = in->readH264()) && !finish)
		{
//			cout << "type:" << (int) nalu->getType() << " " << nalu->getLength() << endl;
			switch (nalu->getType())
			{
			case SEI:
				memcpy(sei->getData(), nalu->getData(), nalu->getLength());
				sei->setLength(nalu->getLength());
				break;
			case IDR:
				memcpy(idr->getData(), nalu->getData(), nalu->getLength());
				idr->setLength(nalu->getLength());
				if (idr->getLength())
				{
					if (!encodeKeyFrame())
						finish = true;
				}
				break;
			case SPS:
				memcpy(sps->getData(), nalu->getData(), nalu->getLength());
				sps->setLength(nalu->getLength());
				break;
			case PPS:
				memcpy(pps->getData(), nalu->getData(), nalu->getLength());
				pps->setLength(nalu->getLength());
				if (sps->getLength() && pps->getLength() && !findSPSPPS)
				{
					if (encoderOnMetaData() && encoderSPSPPS())
					{
						findSPSPPS = true;
					}
					else
					{
						finish = true;
					}
				}
				break;
			default:
				if (!encodeFrame(nalu))
					finish = true;
				break;
			}

		}
		if (!finish)
			encodeEndFrame();
	}

	closeInAndOut();

	//std::cout << "encoder finish" << std::endl;
}

