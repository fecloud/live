/*
 * test.cpp
 *
 *  Created on: Jan 23, 2015
 *      Author: ouyangfeng
 */
#include <iostream>

#include "server/VideoLiveObservable.h"
#include "server/VideoLiveServer.h"

using namespace std;

#include <iostream>

#include "base/utils.h"
#include "server/VideoLiveServer.h"

using namespace std;

#ifndef NO_MAIN
int main(int argc, char **argv)
{
	if (argc < 2)
	{
		cout << "Uage:" << argv[0] << " <port> [ threads ]" << endl;
		exit(0);
	}
	string pid_path(argv[0]);
	pid_path = pid_path + ".pid";
	save_pid(pid_path.c_str());
	VideoLiveObservable* oable = VideoLiveObservable::getInstance();
	VideoLiveServer().run(argc, argv);
	VideoLiveObservable::destory(oable);
	return 1;
}
#endif
