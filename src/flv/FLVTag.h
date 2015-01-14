/*
 * FLVTag.h
 *
 *  Created on: 2014-12-19
 *      Author: maygolf
 */

#ifndef FLVTAG_H_
#define FLVTAG_H_

#include "FLVTagHeader.h"
#include "FLVTagBody.h"

class FLVTag
{

public:
	FLVTagHeader header;
	FLVTagBody *body;

	virtual ~FLVTag()
	{
		//std::cout << "~FLVTag" << std::endl;
		if (body)
			delete body;
		body = NULL;
	}
	//virtual Bytes* encoder();

};

#endif /* FLVTAG_H_ */
