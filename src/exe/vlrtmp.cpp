/*
 * vlrtmp.cpp
 *
 *  Created on: 2015年1月28日
 *      Author: maygolf
 */

#include <stdio.h>
#include <iostream>

#include "h264/NetH264Reader.h"
#include "rtmp/RTMPOutPutStream.h"
#include "encoder/FLVEncoder.h"

using namespace std;

int main(int argc, char **argv)
{
	if (argc < 3)
	{
		cout << "Uage:" << argv[0] << " <src server> <rtmp server>" << endl;
		exit(0);
	}
	NetH264Reader reader(argv[1]);

	RTMPOutPutStream output(argv[2], false, 25);
	FLVEncoder encoder(&reader, &output);
	encoder.encoder();
}

