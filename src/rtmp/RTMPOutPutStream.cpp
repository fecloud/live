/*
 * RTMPOutPutStream.cpp
 *
 *  Created on: 2014-12-25
 *      Author: maygolf
 */
#include <string.h>

#include "rtmp/RTMPOutPutStream.h"
#include "base/utils.h"

RTMP *rtmp; //rtmp应用指针

RTMPOutPutStream::RTMPOutPutStream(const char* url, bool live)
{
	cout << "url:" << url << endl;
	this->url = new char[strlen(url) + 1];
	strcpy(this->url, url);
	this->live = live;
}

RTMPOutPutStream::~RTMPOutPutStream()
{
	if (url)
		delete[] url;
	url = NULL;
	live = false;
}

bool RTMPOutPutStream::setParam(Bytes* bytes)
{
	Bytes* tmp = new Bytes(16 + bytes->getLength());
	String setDataFrame("@setDataFrame");
	setDataFrame.encoder(tmp);

	tmp->put(bytes);
	bool result = false;
	result = sendData(RTMP_PACKET_SIZE_LARGE, SCRIPT, tmp);

	delete tmp;
	tmp = NULL;

	return result;
}

bool RTMPOutPutStream::writeHeaders(Bytes* bytes)
{
	return sendData(RTMP_PACKET_SIZE_LARGE, VIDEO, bytes);
}

bool RTMPOutPutStream::writeFrame(Bytes* bytes, char type, unsigned time)
{
	char packet_type = RTMP_PACKET_SIZE_LARGE;

	if (type != 0x1)
		packet_type = RTMP_PACKET_SIZE_MEDIUM;

	this->timestamp += time;
	bool result = sendData(packet_type, VIDEO, bytes);
	if (result)
	{
		if (!live)
			usleep(time * 1000);
	}
	return result;
}

bool RTMPOutPutStream::sendData(char packet_type, char data_type, Bytes* bytes)
{
	bool result = false;
	RTMPPacket packet; //创建包
	memset(&packet, 0, sizeof(RTMPPacket));
	RTMPPacket_Alloc(&packet, bytes->getLength()); //给packet分配数据空间
	RTMPPacket_Reset(&packet); //重置packet状态
	packet.m_headerType = packet_type;
	packet.m_hasAbsTimestamp = FALSE; //绝对时间戳
	packet.m_nChannel = 0x04; //通道
	packet.m_nInfoField2 = rtmp->m_stream_id;
	packet.m_packetType = data_type;
	packet.m_nTimeStamp = timestamp;
	packet.m_nBodySize = bytes->getLength();
	memcpy(packet.m_body, bytes->getData(), bytes->getLength());
	if (RTMP_IsConnected(rtmp) && RTMP_SendPacket(rtmp, &packet, 0))
		result = true;
	else
		cout << "rtmp is not connect" << endl;
	RTMPPacket_Free(&packet);
	return result;
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
		cout << "Connect Err\n" << endl;
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
	return true;
}

