/*
 * vlrtmp.cpp
 *
 *  Created on: 2015年1月28日
 *      Author: maygolf
 */

#include <stdio.h>
#include <iostream>

#include "h264/NetH264Reader.h"
#include "io/RTMPOutPutStream.h"
#include "encoder/FLVEncoder.h"

using namespace std;

int main(int argc, char **argv)
{
	if (argc < 4)
	{
		cout << "Uage:" << argv[0] << " <src server name > <src server port > <rtmp server>" << endl;
		exit(0);
	}
	NetH264Reader reader(argv[1], atoi(argv[2]));

	RTMPOutPutStream output(argv[3], false, 25);
	FLVEncoder encoder(&reader, &output);
	encoder.encoder();
}

