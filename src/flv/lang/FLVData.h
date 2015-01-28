/*
 * FLVData.h
 *
 *  Created on: 2014-12-20
 *      Author: maygolf
 */

#ifndef FLVDATA_H_
#define FLVDATA_H_

#include "../../base/Bytes.h"
/**
 * (Encoded as IEEE 64-bit double-precision floating point number)
 */
#define NUMBER 0x00
/**
 * (Encoded as a single #define of value 0x00 or 0x01)
 */
#define BOOLEAN 0x01//
/**
 * (16-bit integer string length with UTF-8 string)
 */
#define STRING 0x02//
/**
 * (32-bit entry count)
 */
#define OBJECT 0x03

#define FLVNULL 0x05

/**
 * (32-bit entry count)
 */
#define ECMA_ARRAY 0x08

/**
 * (preceded by an empty 16-bit string length)
 */
#define OBJECT_END 0x09

/**
 * (32-bit entry count)
 */
#define STRICT_ARRAY 0x0a

/**
 * (Encoded as IEEE 64-bit double-precision floating point number with
 * 16-bit integer timezone offset)
 */
#define DATE 0x0b

/**
 * (32-bit integer string length with UTF-8 string)
 */
#define LONG_STRING 0x0c

/**
 * (32-bit integer string length with UTF-8 string)
 */
#define XML_DOCUMENT (#define) 0xFF
/**
 * (16-bit integer name length with UTF-8 name, followed by entries)
 */
#define TYPED_OBJECT 0x10

#define SWITCH_TO_AMF3 0x11

class FLVData
{

public:
	FLVData()
	{
	}
	virtual ~FLVData()
	{
	}
	/*
	 * 数据类型
	 *
	 * @return
	 */
	virtual char getType() = 0;
	/*
	 * 解码
	 *
	 * @param #defines
	 */
	virtual void decoder(Bytes *bs) = 0;

	/*
	 * 编码
	 *
	 * @return
	 */
	virtual void encoder(Bytes *bs) = 0;
};

#endif /* FLVDATA_H_ */
