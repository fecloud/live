/*
 * vlsave.cpp
 *
 *  Created on: 2015年1月28日
 *      Author: maygolf
 */
#include <signal.h>
#include <stdio.h>
#include <iostream>

#include "Poco/LocalDateTime.h"

#include "h264/NetH264Reader.h"
#include "base/utils.h"

using namespace std;
using namespace Poco;

int run = 1;
/* 信号处理例程，其中dunno将会得到信号的值 */
static void sigroutine(int dunno)
{ 
    run = 0;
}

#ifndef NO_MAIN
int main(int argc, char **argv)
{

	if (argc < 3)
	{
		cout << "Uage:" << argv[0] << " [ -f ] <src server > <save file >" << endl;
		exit(0);
	}

	signal(SIGHUP, sigroutine); //* 下面设置三个信号的处理方法
	signal(SIGINT, sigroutine);
	signal(SIGQUIT, sigroutine);

	bool dfps = false;
	int postion = 0;
	if (argc == 4 && (string(argv[1]) == string("-f")))
	{
		postion++;
		dfps = true;
	}

	NetH264Reader reader(argv[postion + 1]);
	FILE *out;

	cout << "connect server " << argv[postion + 1] << endl;
	if (reader.open())
	{
		cout << "connect server " << argv[postion + 1] << " sucess" << endl;
		out = fopen(argv[postion + 2], "wb");
		if (out)
		{

			H264NALU *nalu = 0;
			char naluHead[] =
			{ 0x0, 0x0, 0x0, 0x1 };
			int time = LocalDateTime().second();
			int fps = 0;
			while (run)
			{
				nalu = reader.readH264();
				if (nalu != 0)
				{
					if (dfps)
					{
						if (LocalDateTime().second() == time)
						{
							fps++;
						}
						else
						{
							LocalDateTime ld;
							cout << ld.year() << "-" << ld.month() << "-" << ld.day() << " " << ld.hour() << ":" << ld.minute() << ":" << ld.second() << " recevie fps:" << fps
									<< endl;
							fps = 1;
							time = LocalDateTime().second();
						}
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
			
			fclose(out);
			out = NULL;
		}
		else
		{
			cout << "open file " << argv[postion + 2] << " error" << endl;
		}
	}
	else
	{
		cout << "connect server " << argv[postion + 1] << " fail" << endl;
	}

}

#endif
