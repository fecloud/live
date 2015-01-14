/*
 * ECMAArray.h
 *
 *  Created on: 2014-12-24
 *      Author: maygolf
 */

#ifndef ECMAARRAY_H_
#define ECMAARRAY_H_

#include <list>

#include "FLVData.h"
#include "String.h"
#include "Number.h"

using namespace std;

class ECMA_Array_Name {

public:
	char* name;
	int length;
	ECMA_Array_Name() {
		name = NULL;
		length = 0;
	}
	ECMA_Array_Name(const char*c) {
		this->length = strlen(c);
		name = new char[length+1];
		strcpy(name, c);
	}
	ECMA_Array_Name(char*c, int length) {
		name = c;
		this->length = length;
	}
	~ECMA_Array_Name() {
		delete[] name;
		name = NULL;
		length = 0;
	}

};

class ECMA_Array: public FLVData {

private:
	list<ECMA_Array_Name*> names;
	list<FLVData*> values;

protected:
	FLVData* parseString(Bytes*);
	FLVData* parseNubmer(Bytes*);
	FLVData* parseECMAArray(Bytes*);
	FLVData* parseFLVData(Bytes*);

public:
	ECMA_Array();
	virtual ~ECMA_Array();
	virtual char getType();
	virtual void decoder(Bytes*);
	virtual void encoder(Bytes*);
	void put(const char*, FLVData*);

};

#endif /* ECMAARRAY_H_ */
