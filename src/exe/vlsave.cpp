/*
 * vlsave.cpp
 *
 *  Created on: 2015年1月28日
 *      Author: maygolf
 */

#include <stdio.h>
#include <iostream>

#include "h264/NetH264Reader.h"

using namespace std;

int main(int argc, char **argv)
{

	if (argc < 2)
	{
		cout << "Uage:" << argv[0] << " <src server name > <src server port > <save file >" << endl;
		exit(0);
	}

	NetH264Reader reader(argv[1], atoi(argv[2]));
	FILE *out;

	cout << "connect server " << argv[1] << ":" << argv[2] << endl;
	if (reader.open())
	{
		cout << "connect server " << argv[1] << ":" << argv[2] << " sucess" << endl;
		out = fopen(argv[3], "wb");
		if (out)
		{

			H264NALU *nalu = 0;
			char naluHead[] = { 0x0, 0x0, 0x0, 0x1 };
			while (1)
			{
				nalu = reader.readH264();
				if (nalu != 0)
				{
					fwrite(naluHead, 4, 1, out);
					fwrite(nalu->getData(), nalu->getLength(), 1, out);
				}
				else
				{
					cout << "disconnet server " << endl;
					break;
				}

			}
		}
		else
		{
			cout << "open file " << argv[3] << " error" << endl;
		}
	}
	else
	{
		cout << "connect server " << argv[1] << ":" << argv[2] << " fail" << endl;
	}

}

