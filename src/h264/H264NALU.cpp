/*
 * H264NALU.cpp
 *
 *  Created on: 2014-12-18
 *      Author: maygolf
 */

#include "H264NALU.h"
#include <iostream>

using namespace std;

H264NALU::H264NALU() :
		Bytes(), type(0), time(0)
{

}

H264NALU::H264NALU(int capacity) :
		Bytes(capacity), type(0), time(0)
{

}
H264NALU::H264NALU(char*data, int length) :
		Bytes(data, length), type(0), time(0)
{
}

H264NALU::~H264NALU()
{
}

char H264NALU::getType()
{
	return this->type;
}

void H264NALU::setType(char type)
{
	this->type = type;
}

unsigned H264NALU::getTime()
{
	return time;
}

void H264NALU::setTime(unsigned time)
{
	this->time = time;
}

