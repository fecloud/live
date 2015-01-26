///*
// * NetH264Reader.cpp
// *
// *  Created on: 2015年1月26日
// *      Author: maygolf
// */
//
//#include "NetH264Reader.h"
//
//using namespace Poco::Net;
//
//NetH264Reader::NetH264Reader(char* host, unsigned int port)
//{
////	H264Reader(0);
//	int len = strlen(host);
//	this->host = new char[len + 1];
//	strcpy(this->host, host);
//	this->port = port;
//}
//
//NetH264Reader::~NetH264Reader()
//{
//	if (host)
//		delete[] host;
//
//}
//
//bool NetH264Reader::open()
//{
//
//	SocketAddress sa(host, port);
//	return false;
//}
//
//bool NetH264Reader::close()
//{
//
//	return false;
//}
//
