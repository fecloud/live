/*
 * FLVVideoTagBody.cpp
 *
 *  Created on: 2014-12-19
 *      Author: maygolf
 */
#include <iostream>

#include "FLVVideoTagBody.h"

using namespace std;

FLVVideoTagBody::FLVVideoTagBody()
{

}
FLVVideoTagBody::~FLVVideoTagBody()
{
	//cout << "~FLVVideoTagBody" << endl;
}

void FLVVideoTagBody::decoderBoby(Bytes *bytes)
{
	//cout << "decoderBoby" << endl;
	setData(bytes);
	char video = getData()->get();
	setFrameType(((0xF0 & video) >> 4));
	setCodec((0x0F & video));

}
