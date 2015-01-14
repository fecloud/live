/*
 * Number.h
 *
 *  Created on: 2014-12-20
 *      Author: maygolf
 */

#ifndef NUMBER_H_
#define NUMBER_H_

#include <iostream>

#include "FLVData.h"

using namespace std;
class Number: public FLVData
{
private:
	double number;
public:
	Number()
	{
		number = 0;
	}
	Number(double number)
	{
		this->number = number;
	}
	virtual ~Number()
	{
		//cout << "Number"<< endl;
		number = 0;
	}
	virtual char getType();
	virtual void decoder(Bytes *bytes);
	virtual void encoder(Bytes*);

	double getNumber()
	{
		return number;
	}

	void setNumber(double number)
	{
		this->number = number;
		cout << "Number:" << number << endl;
	}
};

#endif /* NUMBER_H_ */
