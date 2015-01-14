/*
 * FLVScriptTagBody.h
 *
 *  Created on: 2014-12-20
 *      Author: maygolf
 */

#ifndef FLVSCRIPTTAGBODY_H_
#define FLVSCRIPTTAGBODY_H_

#include "FLVTagBody.h"
#include "lang/Struct.h"

class FLVScriptTagBody: public FLVTagBody
{
private:
	Struct obj;
public:
	FLVScriptTagBody();
	virtual ~FLVScriptTagBody();
	virtual void decoderBoby(Bytes *bytes);

};

#endif /* FLVSCRIPTTAGBODY_H_ */
