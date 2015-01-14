/*
 * main.cpp
 *
 *  Created on: 2014-12-18
 *      Author: maygolf
 */
#include <time.h>

#include "h264/H264Reader.h"
#include "flv/FLVReader.h"
#include "io/FLVOutPutStream.h"
#include "io/RTMPOutPutStream.h"
#include "encoder/FLVEncoder.h"
#include "Utils.h"
#include "live/LiveVideo.h"

char h264[] = "out.h264";
char parflv[] = "test.flv";
char outflv[] = "test1.flv";
char outrtmp[] = "rtmp://127.0.0.1/live/demo";
uint64_t flv_dbl2int(double value)
{
	return (union
			{	double f; uint64_t i;})
	{	value}.i;
}

void testFLVData()
{
	cout << "encoderOnMetaData" << endl;
	Bytes*buffer = new Bytes(1024);
	Struct* st = new Struct();
	st->put(new String("onMetaData"));
	ECMA_Array* array = new ECMA_Array();
	array->put("duration", new Number(0));
	array->put("width", new Number(320));
	array->put("height", new Number(240));
	array->put("videodatarate", new Number(0));
	array->put("framerate", new Number(25));
	array->put("videocodecid", new Number(7));
	array->put("encoder", new String("Lavf53.32.100"));
	array->put("filesize", new Number(0));
	st->put(array);

	st->encoder(buffer);
	buffer->flip();
	cout << "encoderOnMetaData data:length " << buffer->getLength() << endl;
	delete st;
	st = NULL;
}

void testParseFLV()
{
	FLVReader* reader = new FLVReader(parflv);
	FLVFileHead* header = reader->readFileHead();
//	cout << "haveVideo:" << header->haveVideo << " haveAudio:"
//			<< header->havdAudio << endl;
	delete header;
	header = NULL;

	int i = 0;
	FLVTag* tag = NULL;
	while ((tag = reader->readerTag()))
	{
		i++;
//		cout << "index:" << i << " type:" << tag->header.getType() << " len:"
//				<< tag->header.getDataLength() << " timestamp:"
//				<< tag->header.getTimestamp() << endl;
		delete tag;
		tag = NULL;
	}

	reader->close();
	delete reader;
	reader = NULL;
}

void testParseH264()
{
	H264Reader *reader = new H264Reader(h264);
	H264NALU* h264nalu = NULL;
	while ((h264nalu = (H264NALU*) reader->reader()))
	{
		//cout << getNALUTypeName(h264nalu->getType()) << endl;
	}
	reader->close();
	delete reader;
	reader = NULL;
}

void testH264ToFLV()
{
	cout << "testH264ToFLV" << endl;
	H264Reader* reader = new H264Reader(h264);
	cout << "reader out" << endl;
	FLVOutPutStream* out = new FLVOutPutStream(outflv, 25);
	cout << "FLVOutPutStream out" << endl;
	FLVEncoder encoder(reader, out);

	encoder.encoder();
	delete reader;
	reader = NULL;
	delete out;
	out = NULL;
}

void testH264ToRTMP()
{
	cout << "testH264ToRTMP" << endl;
	H264Reader* reader = new H264Reader(h264);

	RTMPOutPutStream* output = new RTMPOutPutStream(outrtmp, false, 25);
	FLVEncoder encoder(reader, output);
	encoder.encoder();
	delete reader;
	reader = NULL;
	delete output;
	output = NULL;
}

void testCamera(void)
{

}

int main(int argc, char **argv)
{
//	cout << isBigEndian() << endl;
	time_t t = time(NULL);
	printf("%d\n", t);

//	while (true) {
//		testParseH264();
//		testParseFLV();
//		testH264ToFLV();
//		testH264ToRTMP();
//		testFLVData();
//		cout << "10" << endl;
//		usleep(5000000);
	//	break;
//	char* s = new char[100];
//	delete[] s;
//	}
	VideoLive live(outrtmp, 640, 480);
	live.init();
	live.start();
	live.stop();
	time_t t2 = time(NULL);
	printf("%d\n", t2);
	return 0;
}

