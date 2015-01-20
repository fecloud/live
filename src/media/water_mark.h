#ifndef WATER_MARK_H
#define WATER_MARK_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


typedef struct WaterMark_Template {

	unsigned int width;
	unsigned int height;
	unsigned char* data;

} WaterMark_Template;

typedef struct WaterMark {

	WaterMark_Template* templates[13];

} WaterMark;

int waterMark_init(WaterMark*);

int waterMark_exit(WaterMark*);

void waterMarkShowTime(WaterMark* waterMark, char* src,unsigned int w,unsigned int h, unsigned int x, unsigned int y);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif


