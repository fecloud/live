/*
 * Number.cpp
 *
 *  Created on: 2014-12-20
 *      Author: maygolf
 */

#include "Number.h"

using namespace std;
char Number::getType()
{
	return NUMBER;
}

void Number::decoder(Bytes *bytes)
{
	if (bytes->hasRemaining())
	{
		setNumber(bytes->getDouble());
	}
}

void Number::encoder(Bytes* bytes)
{
	bytes->put(getType());
	bytes->putDouble(number);
}
