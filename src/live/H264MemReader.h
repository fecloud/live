/*
 * H264MemReader.h
 *
 *  Created on: 2015-1-8
 *      Author: maygolf
 */

#ifndef H264MEMREADER_H_
#define H264MEMREADER_H_

#include "../vencoder/include_vencoder/venc.h"

#include "../h264/H264Reader.h"

class H264MemReader
{
private:
	bool isHeader;
	int length;
	int postion;
	char* data;
	int startNalu();
	H264NALU* readVencSeqHeader();
	H264NALU* readVencOutputBuffer();

public:
	H264MemReader();
	virtual ~H264MemReader();
	virtual bool close();
	virtual bool open();
	virtual Bytes* reader();
	void setVencSeqHeader(VencSeqHeader*);
	void setVencOutputBuffer(VencOutputBuffer*);

};

#endif /* H264MEMREADER_H_ */
