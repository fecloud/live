/*
 * vlrtmp.cpp
 *
 *  Created on: 2015年1月28日
 *      Author: maygolf
 */

#include <stdio.h>
#include <iostream>
#include <sstream>

#include "Poco/Base64Encoder.h"
#include "Poco/Base64Decoder.h"
#include "Poco/Exception.h"

#include "base/utils.h"
#include "h264/NetH264Reader.h"
#include "rtmp/RTMPOutPutStream.h"
#include "encoder/FLVEncoder.h"

using namespace std;
using namespace Poco;

/**
 * 创建随机字符串
 */
string randomstr() {
	srand((unsigned) time(NULL));
	const int r = rand();
	std::ostringstream str;
	std::stringstream instr;
	instr << r;
	Base64Encoder en(str);
	en << instr.str();
	en.close();
	const int len = str.str().length();
	return str.str().replace(len - 2, 2, "XX");
}

bool write_url(const char *url) {
	FILE *fp = fopen("/var/run/liveurl", "w+");
	if (!fp) {
		cout << "open /var/run/liveurl fail" << endl;
		return false;
	}
	fwrite(url, strlen(url), 1, fp);
	fclose(fp);
	fp = NULL;
	return true;
}
#ifndef NO_MAIN
int main(int argc, char **argv) {
	if (argc < 3) {
		cout << "Uage:" << argv[0] << " <src server> <rtmp server>" << endl;
		exit(0);
	}
	NetH264Reader reader(argv[1]);

	std::stringstream instr;
	instr << argv[2];
	instr << randomstr();
	string pid_path(argv[0]);
	pid_path = pid_path + ".pid";
	save_pid(pid_path.c_str());
	if (write_url(instr.str().c_str())) {
		RTMPOutPutStream output(instr.str().c_str(), true);
		FLVEncoder encoder(&reader, &output);
		encoder.encoder();
	}
}
#endif
