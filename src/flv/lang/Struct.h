/*
 * Struct.h
 *
 *  Created on: 2014-12-20
 *      Author: maygolf
 */

#ifndef STRUCT_H_
#define STRUCT_H_

#include <list>

#include "ECMAArray.h"
#include "../FLVTagBody.h"

using namespace std;

class Struct: public ECMA_Array
{

private:
	list<FLVData*> objects;

public:
	Struct();
	virtual ~Struct();
	virtual void decoder(Bytes*);
	virtual void encoder(Bytes*);
	virtual void put(FLVData*);

};

#endif /* STRUCT_H_ */
