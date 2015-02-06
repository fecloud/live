/*
 * H264NALU.h
 *
 *  Created on: 2014-12-18
 *      Author: maygolf
 */

#ifndef H264NALU_H_
#define H264NALU_H_

#include <stdlib.h>
#include <string.h>

#define SLICE 0x1

#define DPA 0x2

#define DPB 0x3

#define DPC 0x4

#define IDR 0x5

#define SEI 0x6

#define SPS 0x7

#define PPS 0x8

#define AUD 0x9

#define EOSEQ 0x10

#define EOSTREAM 0x11

#define FILL 0x12

#include "../base/Bytes.h"

class H264NALU: public Bytes
{

private:
	char type;
	unsigned time;

public:
	H264NALU();
	H264NALU(int);
	H264NALU(char*data, int length);
	virtual ~H264NALU();
	char getType();
	void setType(char type);
	unsigned getTime();
	void setTime(unsigned time);

};

#endif /* H264NALU_H_ */
