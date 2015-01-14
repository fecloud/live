/*
 * FLVTagBody.h
 *
 *  Created on: 2014-12-19
 *      Author: maygolf
 */

#ifndef FLVTAGBODY_H_
#define FLVTAGBODY_H_

#include "../Bytes.h"
#include <iostream>

class FLVTagBody
{

protected:
	Bytes *data;

public:
	FLVTagBody()
	{
	}
	virtual ~FLVTagBody()
	{
		//std::cout << "FLVTagBody delete data" << std::endl;
		if (data)
			delete data;
	}
	Bytes* getData()
	{
		return data;
	}
	void setData(Bytes*bytes)
	{
		this->data = bytes;
	}
	virtual void decoderBoby(Bytes *bytes) = 0;

};

#endif /* FLVTAGBODY_H_ */
