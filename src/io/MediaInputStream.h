/*
 * MediaInputStream.h
 *
 *  Created on: 2014-12-25
 *      Author: maygolf
 */

#ifndef MEDIAINPUTSTREAM_H_
#define MEDIAINPUTSTREAM_H_

#include "../Bytes.h"

class MediaInputStream
{

public:
	virtual ~MediaInputStream()
	{
	}
	;
	virtual bool open() = 0;
	virtual Bytes* reader() = 0;
	virtual bool close() = 0;

};

#endif /* MEDIAINPUTSTREAM_H_ */
