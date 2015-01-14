/*
 * SpsDecode.h
 *
 *  Created on: 2014-12-28
 *      Author: Administrator
 */

#ifndef SPSDECODE_H_
#define SPSDECODE_H_

#include <stdio.h>
#include <stdint.h>
#include <math.h>

char ue(char *pBuff, char nLen, char &nStartBit);

int u(char BitCount, char * buf, char &nStartBit);

bool h264_decode_sps(char* buf, int nLen, int &width, int &height);

#endif /* SPSDECODE_H_ */
