/*
 * H264NALU.cpp
 *
 *  Created on: 2014-12-18
 *      Author: maygolf
 */

#include "H264NALU.h"
#include <iostream>

using namespace std;

H264NALU::H264NALU()
{

}

H264NALU::H264NALU(int capacity) :
		Bytes(capacity)
{

}

H264NALU::~H264NALU()
{
//	cout << "~H264NALU" << endl;
}

char H264NALU::getType()
{
	return this->type;
}

void H264NALU::setType(char type)
{
	this->type = type;
}

