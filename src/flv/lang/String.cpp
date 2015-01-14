/*
 * String.cpp
 *
 *  Created on: 2014-12-20
 *      Author: maygolf
 */

#include "String.h"
#include <iostream>

using namespace std;

String::String() {
	length = 0;
}

String::String(const char* string) {
	this->length = strlen(string);
	this->string = new char[length+1];
	strcpy(this->string, string);
}

String::~String() {
//	cout << "String"<< endl;
	if (string)
		delete[] string;
	string = NULL;
	length = 0;
}

char String::getType() {
	return STRING;
}

void String::decoder(Bytes *bytes) {
	if (bytes->hasRemaining()) {
		this->length = bytes->getChar();
		string = new char[length + 1];
		int i = 0;
		for (; i < length; i++) {
			string[i] = bytes->get();
		}
		string[length] = '\0';
		std::cout << "cout:" << length << std::endl;
		this->string = string;
		cout << string << endl;
	}
}

void String::encoder(Bytes *bytes) {
	bytes->put(getType());
	bytes->putChar(length);
	bytes->put(string, length);
}

