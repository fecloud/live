/*
 * H264Reader.cpp
 *
 *  Created on: 2014-12-18
 *      Author: maygolf
 */

#include "H264Reader.h"

using namespace std;

H264Reader::H264Reader()
{
	filename = 0;
	byte = new H264NALU(512000);
	buffer = new Bytes(READ_BUFFER);
}

H264Reader::H264Reader(char* file)
{
	filename = new char[strlen(file) + 1];
	byte = new H264NALU(512000);
	buffer = new Bytes(READ_BUFFER);
}

H264Reader::~H264Reader()
{
	delete byte;
	byte = NULL;
	delete buffer;
	buffer = NULL;
	if (file)
	{
		delete[] filename;
	}
	if (file.is_open())
	{
		close();
	}
}

bool H264Reader::open()
{
	this->file.open(filename, ifstream::in | ifstream::binary);
	int i = 0;
	for (; i < 4; i++)
	{
		this->file.get();
	}
	return file.is_open();
}

/**
 * 找到返回位置,没有找到返回-1
 */
bool H264Reader::findNALU()
{
	while (buffer->hasRemaining())
	{
		char c = buffer->get();
		byte->put((char) c);
		if (c == 0x1)
		{
			int postion = byte->postion();
			if (byte->getLength() > 3 && byte->getData()[postion - 4] == 0 && byte->getData()[postion - 3] == 0 && byte->getData()[postion - 2] == 0)
			{
				byte->setLength(postion - 4);
				return true;
			}
			else if (byte->getLength() > 3 && byte->getData()[postion - 3] == 0 && byte->getData()[postion - 2] == 0)
			{
				byte->setLength(postion - 3);
				return true;
			}

		}
	}
	return false;
}

int counts = 0;

H264NALU* H264Reader::readH264()
{
	H264NALU *h264nalu = NULL;
	byte->clear();
	while (!file.eof())
	{
		//缓存里面没有数据了
		if (!buffer->hasRemaining())
		{
			buffer->clear();
//			memset((void*) buffer->getData(), 0, READ_BUFFER);
			file.read(buffer->getData(), READ_BUFFER);
			int count = file.gcount();
//			counts ++ ;
//			cout << "count" << count << endl;
//			cout << "counts" << counts << endl;
			if (count > 0)
			{
				buffer->setLength(count);
				buffer->flip();
			}
			else
			{
				//没有读取到数据
				break;
			}
		}
//		while (buffer->hasRemaining())
//		{
//			buffer->get();
//		}
		if (findNALU())
		{
			break;
		}

	}

	byte->flip();
	if (byte->getLength() > 0)
	{
		h264nalu = byte;
		h264nalu->setType(0x1F & byte->getData()[0]);
	}

	return h264nalu;
}

Bytes* H264Reader::reader()
{
	return readH264();
}

bool H264Reader::close()
{
	if (file.is_open())
	{
		file.close();
	}
	return !file.is_open();
}
