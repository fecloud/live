/*
 * H264MemReader.cpp
 *
 *  Created on: 2015-1-8
 *      Author: maygolf
 */

#include "H264MemReader.h"

H264MemReader::H264MemReader()
{
	isHeader = false;
}

H264MemReader::~H264MemReader()
{
	isHeader = false;
	length = 0;
	postion = 0;
	if(data)
		delete [] data;
	data = NULL;

}

void H264MemReader::setVencSeqHeader(VencSeqHeader* sqlHeader)
{
	this->isHeader = true;
	this->postion = 0;
	this->length = sqlHeader->length;
	this->data = new char[length];
	memcpy(data, sqlHeader->bufptr, length);
}

void H264MemReader::setVencOutputBuffer(VencOutputBuffer* outputBuffer)
{
	this->postion = 0;
	this->isHeader = false;
	this->data = NULL;
	this->length = 0;
	if (outputBuffer->size0 > 0)
	{
		this->length = outputBuffer->size0 + outputBuffer->size1;
		data = new char[length];
		memcpy(data, outputBuffer->ptr0, outputBuffer->size0);
		if (outputBuffer->size1 > 0)
			memcpy(&data[outputBuffer->size0], outputBuffer->ptr1,
					outputBuffer->size1);
	}

}

bool H264MemReader::close()
{
	return true;
}

bool H264MemReader::open()
{
	return true;
}

int H264MemReader::startNalu()
{
	if (data && length > 4)
	{
		if (data[0] == 0x0 && data[1] == 0x0 && data[2] == 0x0
				&& data[3] == 0x1)
		{
			return 4;
		}
		else if (data[0] == 0x0 && data[1] == 0x0 && data[2] == 0x1)
		{
			return 3;
		}
	}
	return 0;
}

H264NALU* H264MemReader::readVencSeqHeader()
{
	if (postion == 0)
		this->postion = startNalu();

	int start = postion;
	int size = 0;

	while (postion < length)
	{
		if (data[postion] == 0x1)
		{
			if (data[postion - 3] == 0 && data[postion - 2] == 0
					&& data[postion - 1] == 0)
			{
				postion++;
				size -= 3;
				break;
			}
			else if (data[postion - 2] == 0 && data[postion - 1] == 0)
			{
				postion++;
				size -= 2;
				break;
			}
		}
		postion++;
		size++;
	}
	if (size > 0)
	{
		H264NALU* bytes = new H264NALU(size);
		int i = 0;
		for (; i < size; i++)
		{
			bytes->put((char) data[start + i]);
		}
		bytes->setType(0x1F & bytes->getData()[0]);
		bytes->flip();
		return bytes;
	}
	return NULL;
}

H264NALU* H264MemReader::readVencOutputBuffer()
{
	if (data)
	{
		H264NALU* bytes = new H264NALU(&data[4],length - 4);
		bytes->setType(0x1F & data[4]);
		bytes->flip();
		return bytes;
	}
	return NULL;
}

Bytes* H264MemReader::reader()
{
	if (startNalu())
	{
		if (isHeader)
		{
			return readVencSeqHeader();
		}
		return readVencOutputBuffer();
	}
	return NULL;
}

