/*
 * Utils.cpp
 *
 *  Created on: 2015-1-8
 *      Author: maygolf
 */
#include "utils.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if DEBUG
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#endif


/**
 * YUV422 packed 格式 转成yuv420sp(nv12)
 * 原理y分量全部复制,隔行取uv
 */
void YUV422To420(unsigned char yuv422[], unsigned char yuv420[], unsigned int width,
		unsigned int height)
{
#if 0
	struct timeval t_start,t_end;

	long cost_time = 0;

	//get start time
	gettimeofday(&t_start, 0);
	long start = ((long)t_start.tv_sec)*1000+(long)t_start.tv_usec/1000;
	cout << "Start time: " << start << endl;
#endif
	unsigned int ynum = width * height;
	unsigned int i, j, k = 0;
	// 得到Y分量
	for (i = 0; i < ynum; i++)
	{
		yuv420[i] = yuv422[i << 1];
	}
	// 得到UV分量
	unsigned int length = width >> 1;
	unsigned int length2 = width << 1;
	unsigned offset = 0;
	for (j = 0; j < height; j += 2)
	{
		unsigned int start = j * length2 ;

		for (k = 0; k < length ; k++)
		{
			offset = start + k * 4;
			yuv420[i++] = yuv422[offset + 1];
			yuv420[i++] = yuv422[offset + 3];
		}
	}
#if 0
	//get end time
	gettimeofday(&t_end, 0);
	long end = ((long)t_end.tv_sec)*1000+(long)t_end.tv_usec/1000;
	cout << "end time: " << end << endl;

	//calculate time slot
	cost_time = end - start;
	cout << "Cost time: " << cost_time << " ms" << endl;
#endif

}

long long current_time()
{
	struct timeval t_start;
	//get start time
	gettimeofday(&t_start, 0);
	long long t = ((long long)t_start.tv_sec) * 1000 + ( long long)t_start.tv_usec / 1000;
	return t;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

