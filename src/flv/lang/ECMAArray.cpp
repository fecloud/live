/*
 * ECMAArray.cpp
 *
 *  Created on: 2014-12-24
 *      Author: maygolf
 */

#include "ECMAArray.h"

ECMA_Array::ECMA_Array()
{

}

ECMA_Array::~ECMA_Array()
{
//	cout << "~ECMA_Array" <<this << endl;
	if (names.size())
	{
		list<ECMA_Array_Name*>::iterator it;
		for (it = names.begin(); it != names.end(); ++it)
		{
			delete *it;
			*it = NULL;
		}
		names.clear();
	}

	if (values.size())
	{
		list<FLVData*>::iterator it;
		for (it = values.begin(); it != values.end(); ++it)
		{
			delete *it;
			*it = NULL;
		}
		values.clear();
	}

}
char ECMA_Array::getType()
{
	return ECMA_ARRAY;
}

FLVData* ECMA_Array::parseString(Bytes* bytes)
{
	String *string = new String();
	string->decoder(bytes);
	return string;
}

FLVData* ECMA_Array::parseNubmer(Bytes* bytes)
{
	Number *number = new Number();
	number->decoder(bytes);
	return number;
}

FLVData* ECMA_Array::parseECMAArray(Bytes* bytes)
{
	ECMA_Array* array = new ECMA_Array();
	array->decoder(bytes);
	return array;
}

FLVData* ECMA_Array::parseFLVData(Bytes* bytes)
{
	switch (bytes->get())
	{
	case STRING:
		return parseString(bytes);
	case NUMBER:
		return parseNubmer(bytes);
	case ECMA_ARRAY:
		return parseECMAArray(bytes);
	default:
		return NULL;
	}
}

void ECMA_Array::put(const char* name, FLVData* value)
{

	names.push_back(new ECMA_Array_Name(name));
	values.push_back(value);

}

void ECMA_Array::decoder(Bytes* bytes)
{
	char nameLength = 0;
	char* tmp;
	int size = bytes->getInt();
	int i = 0;
	for (; i < size; i++)
	{
		nameLength = bytes->getChar();
		tmp = new char[nameLength];
		if (bytes->hasRemaining())
		{
			bytes->get(tmp, nameLength);
			names.push_back(new ECMA_Array_Name(tmp,nameLength));
		}
		if (bytes->hasRemaining())
		{
			values.push_back(parseFLVData(bytes));
		}
	}

	if (bytes->hasRemaining())
	{
		bytes->postion(bytes->postion() + 3);
	}
}

void ECMA_Array::encoder(Bytes* bytes)
{
	bytes->put(getType());
	bytes->putInt(names.size());

	list<ECMA_Array_Name*>::iterator it_name = names.begin();
	list<FLVData*>::iterator it_value = values.begin();

	for (; it_name != names.end() && it_value != values.end();)
	{
		bytes->putChar((*it_name)->length);
		bytes->put((*it_name)->name, (*it_name)->length);
		(*it_value)->encoder(bytes);
		++it_name;
		++it_value;
	}

	bytes->put((char) 0x0);
	bytes->put((char) 0x0);
	bytes->put((char) 0x9);

}

