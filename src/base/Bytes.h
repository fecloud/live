/*
 * byte.h
 *
 *  Created on: 2014-12-19
 *      Author: maygolf
 */

#ifndef BYTE_H_
#define BYTE_H_

#include <stdlib.h>

class Bytes
{
private:
	char *data;
	int length;
	int cpostion;
	int capacity;

public:
	Bytes();
	Bytes(char*data, int length);
	Bytes(int);
	virtual ~Bytes();
	char* getData();
	void setData(char* data);
	int getLength();
	void setLength(int length);
	char get();
	int get(char[], int len);
	int getChar();
	int getInt();
	double getDouble();
	long long getLong();
	int postion();
	void postion(int);
	bool hasRemaining();
	void clear();
	void put(char);
	void put(char*,int);
	void put(Bytes*);
	void putChar(int);
	void putInt(int);
	void putDouble(double);
	void putLong(long long);
	void flip();
	int getCapacity();
};

#endif /* BYTE_H_ */
