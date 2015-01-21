#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>

#include <time.h>
#include "water_template.h"
#include "water_mark.h"

#define TEMPLATE_SET_VALUE(DATA) wm->width = DATA[0]; \
	wm->height = DATA[1]; \
	wm->data = malloc(wm->width * wm->height); \
	memcpy(wm->data,&DATA[2],wm->width * wm->height); \
	break; \

WaterMark_Template* get_template(int i)
{
	WaterMark_Template* wm = (WaterMark_Template*) malloc(sizeof(WaterMark_Template));
	switch (i)
	{
	case 0:
		TEMPLATE_SET_VALUE(data0)
	case 1:
		TEMPLATE_SET_VALUE(data1)
	case 2:
		TEMPLATE_SET_VALUE(data2)
	case 3:
		TEMPLATE_SET_VALUE(data3)
	case 4:
		TEMPLATE_SET_VALUE(data4)
	case 5:
		TEMPLATE_SET_VALUE(data5)
	case 6:
		TEMPLATE_SET_VALUE(data6)
	case 7:
		TEMPLATE_SET_VALUE(data7)
	case 8:
		TEMPLATE_SET_VALUE(data8)
	case 9:
		TEMPLATE_SET_VALUE(data9)
	case 10:
		TEMPLATE_SET_VALUE(data10)
	case 11:
		TEMPLATE_SET_VALUE(data11)
	default:
		TEMPLATE_SET_VALUE(data12)
	}
	return wm;
}


int waterMark_init(WaterMark* waterMark)
{
	int i;
	for (i = 0; i < TEMPLATE_NUM; i++)
	{
		waterMark->templates[i] = get_template(i);
	}
	return 1;
}

int waterMark_exit(WaterMark* waterMark)
{
	int i;
	for (i = 0; i < TEMPLATE_NUM; i++)
	{

		WaterMark_Template* t = waterMark->templates[i];
		free(t);
		t = NULL;
	}
	return 1;
}

static int data_convert(int input, int length, int *output)
{
	int tmp_data;
	tmp_data = input;

	if (length == 2)
	{
		output[0] = tmp_data / 10;
		output[1] = tmp_data % 10;
	}
	else if (length == 4)
	{
		output[0] = tmp_data / 1000;
		tmp_data = tmp_data % 1000;
		output[1] = tmp_data / 100;
		tmp_data = tmp_data % 100;
		output[2] = tmp_data / 10;
		output[3] = tmp_data % 10;
	}
	else
	{
//				LOGD("error length\n");
		return -1;
	}

	return 0;

}

inline int addMarkUV(unsigned char* target,unsigned int offset)
{
	target[offset] = 0x10;
	target[offset +1] = 0x70;
	return 1;
}

static int addMark(unsigned char* target,unsigned int w,unsigned int h, int x, int y, WaterMark_Template* src)
{

	unsigned int i,j,offset;
	unsigned int uvoffset = w * h;
	// y
	for (i = 0; i < src->height; i++)
	{
		for (j = 0; j < src->width; j++)
		{
			char o = src->data[(src->width * i + j)];
//			if (Transparent_Y != o)
//			{
				target[(w * (y + i) + x + j)] = o;
//				if(i % 2 ==0 &&  j%2 == 0 )
//				{
//					//璁剧疆uv
////					printf("i:%d j:%d\n",i,j);
//					offset = uvoffset + w * i + j;
//					addMarkUV(target,offset);
//				}
//			}
		}
	}

//	unsigned int offset = w * h;
//	unsigned int soffset = src->width * src->height;
//	unsigned int uvH = src->height / 2;
//	unsigned int uvW = src->width / 2;
//	unsigned int tuvH = h / 2;
//	unsigned int tuvW = h / 2;
//
//	for (int i = 0; i <uvH ; i++)
//	{
//		for (int j = 0; j < uvW ; j++)
//		{
//			// System.out.println(String.format("i:%s j:%s", i, j));
//			target[offset + (tuvH * (y / 2 + i) + x / 2 + j)] = src->data[soffset + (uvW * i + j)];
//		}
//	}
//
//	offset += ( w * h / 4);
//	soffset += ( src->width * src->height / 4);
//
//	for (int i = 0; i <uvH ; i++)
//		{
//			for (int j = 0; j < uvW ; j++)
//			{
//			// System.out.println(String.format("i:%s j:%s", i, j));
//			target[offset + (target.getWidth() / 2 * (y / 2 + i) + x / 2 + j)] = src.getData()[soffset + (src.getWidth() / 2 * i + j)];
//		}
//	}

	return 1;
}

void waterMarkShowTime(WaterMark* waterMark, unsigned char* src,unsigned int w,unsigned int h, unsigned int x, unsigned int y)
{
	//printf("waterMarkShowTime %d\n",__LINE__);
	time_t	now;
	struct	tm   *timenow;

	int year[4];
	int month[2];
	int day[2];
	int hour[2];
	int min[2];
	int sec[2];

	/* get current time */
	time(&now);

	timenow = localtime(&now);
	data_convert(timenow->tm_year + 1900, 4, (int *)&year);
	data_convert(timenow->tm_mon+1, 2, (int *)&month);
	data_convert(timenow->tm_mday, 2, (int *)&day);
	data_convert(timenow->tm_hour, 2, (int *)&hour);
	data_convert(timenow->tm_min, 2, (int *)&min);
	data_convert(timenow->tm_sec, 2, (int *)&sec);

	const char strings[19] = { year[0], year[1], year[2], year[3],10, month[0], month[1],10, day[0], day[1],12, hour[0], hour[1],11, min[0], min[1], 11, sec[0], sec[1] };
	int i = 0;
	WaterMark_Template* palints[19];
	int c = 0;
	for( i = 0 ;i < 19;i++)
	{
		c = strings[i];
		palints[i] =  waterMark->templates[c];

	}

	unsigned int targetx = x;
	for( i = 0 ;i < 19;i++)
	{
		if(i > 0)
		{
			targetx+= palints[i -1]->width;
		}
		addMark(src, w, h, targetx, y, palints[i]);
	}


}

#ifdef __cplusplus
}
#endif /* __cplusplus */

