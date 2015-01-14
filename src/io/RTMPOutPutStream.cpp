/*
 * RTMPOutPutStream.cpp
 *
 *  Created on: 2014-12-25
 *      Author: maygolf
 */
#include <string.h>

#include "RTMPOutPutStream.h"
#include "../Utils.h"

RTMP*rtmp = NULL; //rtmp应用指针
RTMPPacket* packet = NULL; //rtmp包结构

RTMPOutPutStream::RTMPOutPutStream(const char* url, bool live,  unsigned int framerate = 25)
{
	cout << "url:" << url << endl;
	this->url = new char[strlen(url) + 1];
	strcpy(this->url, url);
	this->live = live;
	oneframetime = 1000 / framerate;
	pretime = 0;
}

RTMPOutPutStream::~RTMPOutPutStream()
{
	if (url)
		delete[] url;
	url = 0;
	live = false;
	pretime = 0;
}

bool RTMPOutPutStream::setParam(Bytes* bytes)
{
	Bytes* tmp = new Bytes(16 + bytes->getLength());
	String setDataFrame("@setDataFrame");
	setDataFrame.encoder(tmp);

	tmp->put(bytes);

	FLVScriptTagBody* body = new FLVScriptTagBody();
	body->setData(tmp);

	bool result = writeData(SCRIPT, body);

	delete tmp;
	tmp = NULL;

	return result;
}

bool RTMPOutPutStream::writeData(char type, FLVTagBody* body)
{
	bool result = false;
	packet = (RTMPPacket*) malloc(sizeof(RTMPPacket)); //创建包
	memset(packet, 0, sizeof(RTMPPacket));
	RTMPPacket_Alloc(packet, body->getData()->getLength()); //给packet分配数据空间
	RTMPPacket_Reset(packet); //重置packet状态
	packet->m_headerType = RTMP_PACKET_SIZE_LARGE;
	packet->m_hasAbsTimestamp = 0; //绝对时间戳
	packet->m_nChannel = 0x04; //通道
	packet->m_nInfoField2 = rtmp->m_stream_id;
	packet->m_packetType = type;
	packet->m_nTimeStamp = timestamp;
	packet->m_nBodySize = body->getData()->getLength();
	memcpy(packet->m_body, body->getData()->getData(),
			body->getData()->getLength());

	body->setData(0x0);
	delete body;
	body = NULL;

	if (RTMP_IsConnected(rtmp) && RTMP_SendPacket(rtmp, packet, 0))
	{
		if (!live)
			usleep(oneframetime * 1000);
		result = true;
	}
	else
	{
		cout << "rtmp is not connect" << endl;
	}
	RTMPPacket_Free(packet); //释放内存
	free(packet);
	packet = NULL;

	return result;
}

long RTMPOutPutStream::getTimeStamp()
{
	if(live)
	{
		if(pretime == 0)
		{
			pretime = current_time();
		}else
		{
			long long tmp = current_time();
			long long lost = tmp - pretime;
			pretime = tmp;
			timestamp +=lost;
			return timestamp;
		}
	}else
	{
		return FLVOutPutStream::getTimeStamp();
	}
	return 0;
}

bool RTMPOutPutStream::open()
{
	RTMP_LogLevel loglevel = RTMP_LOGINFO; //设置RTMP信息等级
	RTMP_LogSetLevel(loglevel); //设置信息等级
	rtmp = RTMP_Alloc(); //申请rtmp空间
	RTMP_Init(rtmp); //初始化rtmp设置
	rtmp->Link.timeout = 5; //设置连接超时，单位秒，默认30秒
	RTMP_SetupURL(rtmp, url); //设置url
	RTMP_EnableWrite(rtmp); //设置可写状态
	//连接服务器
	if (!RTMP_Connect(rtmp, NULL))
	{
		printf("Connect Err\n");
		return false;
	}
	//创建并发布流(取决于rtmp->Link.lFlags)
	if (!RTMP_ConnectStream(rtmp, 0))
	{
		printf("ConnectStream Err\n");
		return false;
	}
	return true;
}

bool RTMPOutPutStream::flush()
{
	return true;
}

bool RTMPOutPutStream::close()
{
	cout << "RTMPOutPutStream: close" << endl;
	if (rtmp != NULL)
	{
		RTMP_Close(rtmp); //断开连接
		RTMP_Free(rtmp); //释放内存
		rtmp = NULL;
	}
	if (packet != NULL)
	{
		RTMPPacket_Free(packet); //释放内存
		free(packet);
		packet = NULL;
	}
	return true;
}

