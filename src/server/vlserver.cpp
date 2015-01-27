/*
 * test.cpp
 *
 *  Created on: Jan 23, 2015
 *      Author: ouyangfeng
 */
#include <iostream>

#include "VideoLiveServer.h"
#include "VideoLiveObservable.h"

using namespace std;

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		cout << "Uage:" << argv[0] << " <port>" << endl;
		exit(0);
	}
	VideoLiveObservable* oable = VideoLiveObservable::createNew();
	VideoLiveServer().run(argc, argv);
	VideoLiveObservable::destory(oable);
	return 1;
}
