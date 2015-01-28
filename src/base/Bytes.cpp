/*
 * Bytes.cpp
 *
 *  Created on: 2014-12-23
 *      Author: maygolf
 */
#include <stdint.h>
#include <iostream>

#include "Bytes.h"

using namespace std;

Bytes::Bytes() {
	data = NULL;
	length = 0;
	cpostion = 0;
	capacity = 0;
}

Bytes::Bytes(char*data, int length) {
	this->data = data;
	this->length = length;
	this->capacity = 0;
	cpostion = 0;
}

Bytes::Bytes(int length) {
	this->data = new char[length];
	this->length = 0;
	this->capacity = length;
	cpostion = 0;
}

Bytes::~Bytes() {

	if(data)
		delete[] data;
	data = NULL;
	length = 0;
	cpostion = 0;
	capacity = 0;
}

char* Bytes::getData() {
	return data;
}

void Bytes::setData(char * data) {
	this->data = data;
}

int Bytes::getLength() {
	return length;
}

void Bytes::setLength(int length) {
	this->length = length;
}

char Bytes::get() {
	char c = data[cpostion];
	cpostion++;
	return c;
}

int Bytes::get(char bytes[], int len) {
	int i = 0;
	for (i = 0; i < len; ++i) {
		bytes[i] = get();
	}
	return i;
}

int Bytes::getChar() {
	int i = (((data[cpostion] & 0xff) << 8) | ((data[cpostion + 1] & 0xff)));
	cpostion += 2;
	return i;
}

int Bytes::getInt() {
	int i =
			(((data[cpostion]) << 24) | ((data[cpostion + 1] & 0xff) << 16)
					| ((data[cpostion + 2] & 0xff) << 8)
					| ((data[cpostion + 3] & 0xff)));
	cpostion += 4;
	return i;
}

double Bytes::getDouble() {
	uint64_t t = ((((uint64_t) data[cpostion]) << 56)
			| (((uint64_t) data[cpostion + 1] & 0xff) << 48)
			| (((uint64_t) data[cpostion + 2] & 0xff) << 40)
			| (((uint64_t) data[cpostion + 3] & 0xff) << 32)
			| (((uint64_t) data[cpostion + 4] & 0xff) << 24)
			| (((uint64_t) data[cpostion + 5] & 0xff) << 16)
			| (((uint64_t) data[cpostion + 6] & 0xff) << 8)
			| (((uint64_t) data[cpostion + 7] & 0xff)));
	cpostion += 8;
	return (union
			{	uint64_t i;double f;})
	{	t}.f;

}

long long Bytes::getLong()
{
	uint64_t t = ((((uint64_t) data[cpostion]) << 56)
				| (((uint64_t) data[cpostion + 1] & 0xff) << 48)
				| (((uint64_t) data[cpostion + 2] & 0xff) << 40)
				| (((uint64_t) data[cpostion + 3] & 0xff) << 32)
				| (((uint64_t) data[cpostion + 4] & 0xff) << 24)
				| (((uint64_t) data[cpostion + 5] & 0xff) << 16)
				| (((uint64_t) data[cpostion + 6] & 0xff) << 8)
				| (((uint64_t) data[cpostion + 7] & 0xff)));
		cpostion += 8;
		return (union
					{	uint64_t i;long long f;})
			{	t}.f;
}

int Bytes::postion() {
	return cpostion;
}

void Bytes::postion(int postion) {
	this->cpostion = postion;
}

bool Bytes::hasRemaining() {
	if (cpostion < length) {
		return true;
	}
	return false;

}

void Bytes::clear() {
	cpostion = 0;
	length = 0;
}

void Bytes::put(Bytes* c) {
	int i;
	for (i = 0; i < c->getLength(); i++) {
		data[cpostion + i] = c->getData()[i];
	}
	cpostion += c->getLength();
	length += c->getLength();
}

void Bytes::put(char c) {
	data[cpostion] = c;
	cpostion++;
	length++;
}

void Bytes::put(char* c, int len) {
	int i;
	for (i = 0; i < len; i++) {
		data[cpostion + i] = c[i];
	}
	cpostion += len;
	length += len;
}

void Bytes::putChar(int c) {
	data[cpostion] = (c & 0xFFFF) >> 8;
	data[cpostion + 1] = (c & 0xFF);
	cpostion += 2;
	length += 2;
}

void Bytes::putInt(int i) {
	data[cpostion] = (i & 0xFFFFFFFF) >> 24;
	data[cpostion + 1] = (i & 0xFFFFFF) >> 16;
	data[cpostion + 2] = (i & 0xFFFF) >> 8;
	data[cpostion + 3] = (i & 0xFF);
	cpostion += 4;
	length += 4;
}

void Bytes::putDouble(double d) {
	uint64_t t = (union
			{	double f;uint64_t i;})
	{	d}.i;
	data[cpostion] =     (t >> 56) & 0xFF;
	data[cpostion + 1] = (t >> 48) & 0xFF;
	data[cpostion + 2] = (t >> 40) & 0xFF;
	data[cpostion + 3] = (t >> 32) & 0xFF;
	data[cpostion + 4] = (t >> 24) & 0xFF;
	data[cpostion + 5] = (t >> 16) & 0xFF;
	data[cpostion + 6] = (t >> 8) & 0xFF;
	data[cpostion + 7] = (t & 0xFF);
	cpostion += 8;
	length += 8;
}

void Bytes::putLong(long long d) {
	uint64_t t = (union
			{	long long f;uint64_t i;})
	{	d}.i;
	data[cpostion] =     (t >> 56) & 0xFF;
	data[cpostion + 1] = (t >> 48) & 0xFF;
	data[cpostion + 2] = (t >> 40) & 0xFF;
	data[cpostion + 3] = (t >> 32) & 0xFF;
	data[cpostion + 4] = (t >> 24) & 0xFF;
	data[cpostion + 5] = (t >> 16) & 0xFF;
	data[cpostion + 6] = (t >> 8) & 0xFF;
	data[cpostion + 7] = (t & 0xFF);
	cpostion += 8;
	length += 8;
}

int Bytes::getCapacity()
{
	return capacity;
}

void Bytes::flip() {
	cpostion = 0;
}
