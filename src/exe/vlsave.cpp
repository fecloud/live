/*
 * vlsave.cpp
 *
 *  Created on: 2015年1月28日
 *      Author: maygolf
 */

#include <stdio.h>
#include <iostream>

#include "Poco/LocalDateTime.h"

#include "h264/NetH264Reader.h"
#include "base/utils.h"

using namespace std;
using namespace Poco;

int main(int argc, char **argv)
{

	if (argc < 3)
	{
		cout << "Uage:" << argv[0] << " <src server > <save file >" << endl;
		exit(0);
	}

	NetH264Reader reader(argv[1]);
	FILE *out;

	cout << "connect server " << argv[1] << endl;
	if (reader.open())
	{
		cout << "connect server " << argv[1] << " sucess" << endl;
		out = fopen(argv[2], "wb");
		if (out)
		{

			H264NALU *nalu = 0;
			char naluHead[] =
			{ 0x0, 0x0, 0x0, 0x1 };
			int time = LocalDateTime().second();
			int fps = 0;
			while (1)
			{
				nalu = reader.readH264();
				if (nalu != 0)
				{
					if (LocalDateTime().second() == time)
					{
						fps++;
					}
					else
					{
						cout << LocalDateTime().second() <<"recevie fps:" << fps << endl;
						fps = 0;
						time = LocalDateTime().second();
					}
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
			cout << "open file " << argv[2] << " error" << endl;
		}
	}
	else
	{
		cout << "connect server " << argv[1] << " fail" << endl;
	}

}

