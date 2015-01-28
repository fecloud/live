/*
 * H264Reader.h
 *
 *  Created on: 2014-12-18
 *      Author: maygolf
 */

#ifndef H264READER_H_
#define H264READER_H_

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cstring>
#include <string.h>

#include "../base/utils.h"
#include "H264NALU.h"
#include "../io/MediaInputStream.h"

#define READ_BUFFER 10240

using namespace std;

class H264Reader: public MediaInputStream
{

protected:
	char* filename;
	ifstream file;
	H264NALU* byte;
	Bytes* buffer;
	bool findNALU();

public:
	H264Reader();
	H264Reader(char* file);
	virtual ~H264Reader();
	virtual bool close();
	virtual H264NALU* readH264();
	virtual bool open();
	virtual Bytes* reader();

};

#endif /* H264READER_H_ */
