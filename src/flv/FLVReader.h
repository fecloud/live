/*
 * FLVReader.h
 *
 *  Created on: 2014-12-19
 *      Author: maygolf
 */

#ifndef FLVREADER_H_
#define FLVREADER_H_

#include <iostream>
#include <fstream>
#include <stdlib.h>

#include "FLVType.h"
#include "FLVFileHead.h"
#include "FLVTag.h"
#include "FLVVideoTagBody.h"
#include "FLVScriptTagBody.h"

using namespace std;
class FLVReader
{
private:
	long long filesize;
	ifstream file;
	void readFLVTagHeader(FLVTag*);
	void readFLVTagBody(FLVTag*);
public:
	FLVReader(char*filename);
	virtual ~FLVReader();
	void openFile();
	void close();
	FLVFileHead* readFileHead();
	FLVTag* readerTag();
};

#endif /* FLVREADER_H_ */
