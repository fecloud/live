/*
 * Struct.cpp
 *
 *  Created on: 2014-12-20
 *      Author: maygolf
 */

#include "Struct.h"
#include <iostream>

Struct::Struct()
{

}

Struct::~Struct()
{
//	std::cout << "delete Struct "<< this << std::endl;
	if (objects.size())
	{
		list<FLVData*>::iterator it;
		for (it = objects.begin(); it != objects.end(); ++it)
		{
			delete *it;
			*it = NULL;
		}
	}
	objects.clear();
}

void Struct::put(FLVData* data)
{
	objects.push_back(data);
}

void Struct::decoder(Bytes* bytes)
{
	while (bytes->hasRemaining())
	{
		objects.push_back(parseFLVData(bytes));
	}
}

void Struct::encoder(Bytes* bytes)
{
	if (objects.size())
	{
		list<FLVData*>::iterator it;
		for (it = objects.begin(); it != objects.end(); ++it)
		{
			(*it)->encoder(bytes);
		}
	}
}

