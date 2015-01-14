/*
 * String.h
 *
 *  Created on: 2014-12-20
 *      Author: maygolf
 */

#ifndef STRING_H_
#define STRING_H_

#include <cstring>

#include "FLVData.h"

class String: public FLVData
{
private:
	char* string;
	int length;

public:
	String();
	String(const char*);
	virtual ~String();
	/**
	 * 数据类型
	 *
	 * @return
	 */
	virtual char getType();
	/**
	 * 解码
	 *
	 * @param #defines
	 */
	virtual void decoder(Bytes *bs);
	virtual void encoder(Bytes*);
};

#endif /* STRING_H_ */
