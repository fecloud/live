/*
 * Utils.h
 *
 *  Created on: 2014-12-18
 *      Author: Administrator
 */

#ifndef UTILS_H_
#define UTILS_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


#include <time.h>
#include <sys/time.h>



//extern "C" {
//	int gettimeofday(struct timeval *tv, struct timezone *tz);
//}
//
//static char HEX[] =
//		{ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D',
//				'E', 'F' };
//
//static const char* getNALUTypeName(char type)
//{
//	switch (type)
//	{
//	case 1:
//		return "NALU_TYPE_SLICE";
//	case 2:
//		return "NALU_TYPE_DPA";
//	case 3:
//		return "NALU_TYPE_DPB";
//	case 4:
//		return "NALU_TYPE_DPC";
//	case 5:
//		return "NALU_TYPE_IDR";
//	case 6:
//		return "NALU_TYPE_SEI";
//	case 7:
//		return "NALU_TYPE_SPS";
//	case 8:
//		return "NALU_TYPE_PPS";
//	case 9:
//		return "NALU_TYPE_AUD";
//	case 10:
//		return "NALU_TYPE_EOSEQ";
//	case 11:
//		return "NALU_TYPE_EOSTREAM";
//	case 12:
//		return "NALU_TYPE_FILL";
//
//	default:
//		break;
//	}
//	return 0;
//}

//static bool isBigEndian()
//{
//	union
//	{
//		unsigned short a;
//		char b;
//	} c;
//
//	c.a = 0x0102;
//
//	if (c.b == 1)
//		return true;
//	else
//		return false;
//}

void YUV422To420(unsigned char yuv422[], unsigned char yuv420[], unsigned int width,
		unsigned int height);
/**
 * 当前的毫秒
 */
long long current_time();

/**
 * 当前的秒
 */
long long current_time_m();

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* UTILS_H_ */
