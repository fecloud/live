/*
 * FLVReader.cpp
 *
 *  Created on: 2014-12-19
 *      Author: maygolf
 */

#include "FLVReader.h"

FLVReader::FLVReader(char *filename)
{
	this->file.open(filename);
	openFile();
}

FLVReader::~FLVReader()
{
	close();
}
void FLVReader::openFile()
{
	file.seekg(0, file.end);
	filesize = file.tellg();
	file.seekg(0, file.beg);
}
void FLVReader::close()
{
	if (file.is_open())
	{
		file.close();
	}
}

FLVFileHead* FLVReader::readFileHead()
{
	if (filesize > 9)
	{
		char header[9];
		file.read(header, 9);
		/**
		 * 是否有音频视频在第5个字节
		 */
		char av = header[4];
		FLVFileHead *head = new FLVFileHead();
		/**
		 * 第5个字节的第1位为1 说明有视频
		 */
		if ((av & 0x1) == 0x1)
		{
			head->haveVideo = true;
		}
		/**
		 * 第5个字节的第4位为1 说明有音频
		 */
		if ((av & 0x4) == 0x4)
		{
			head->havdAudio = true;
		}
		return head;
	}
	return NULL;
}

void FLVReader::readFLVTagHeader(FLVTag* tag)
{
	if (!file.eof())
	{
		char *bytes = new char[15];
		file.read(bytes, 15);
		if (file)
		{
			Bytes *bs = new Bytes(bytes, 15);
			tag->header.decoder(bs);
			delete bs;
			bs = NULL;
		}
		else
		{
			delete[] bytes;
		}

		bytes = NULL;
	}
}

void FLVReader::readFLVTagBody(FLVTag*tag)
{
	FLVTagBody *body = NULL;
	if (!file.eof())
	{
		int bodyLen = tag->header.getDataLength();
		//内容大小0字节
		if (bodyLen)
		{
			char *bytes = new char[bodyLen];
			file.read(bytes, bodyLen);
			Bytes *bs = new Bytes(bytes, bodyLen);
			bytes = NULL;
			switch (tag->header.getType())
			{
			case AUDIO:
				break;
			case VIDEO:
				body = new FLVVideoTagBody();
				break;
			case SCRIPT:
				body = new FLVScriptTagBody();
				break;
			default:
				break;
			}
			if (body)
			{
				body->decoderBoby(bs);
			}
			tag->body = body;
		}
	}

}

FLVTag* FLVReader::readerTag()
{
	FLVTag *tag = new FLVTag();
	readFLVTagHeader(tag);
	readFLVTagBody(tag);
	if (tag->body)
	{
		return tag;
	}
	delete tag;
	tag = NULL;
	return NULL;
}

