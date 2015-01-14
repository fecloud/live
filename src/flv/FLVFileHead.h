/*
 * FLVFileHead.h
 *
 *  Created on: 2014-12-19
 *      Author: maygolf
 */

#ifndef FLVFILEHEAD_H_
#define FLVFILEHEAD_H_

class FLVFileHead
{

public:
	bool havdAudio;
	bool haveVideo;
	FLVFileHead()
	{
		havdAudio = false;
		haveVideo = false;
	}
	;
	virtual ~FLVFileHead()
	{
		havdAudio = false;
		haveVideo = false;
	}
	;

};

#endif /* FLVFILEHEAD_H_ */
