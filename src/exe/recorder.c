/*
 * recorder.c
 *
 *  Created on: Jan 28, 2015
 *      Author: ouyangfeng
 */
#include "base/utils.h"
#include "media/videorecorder.h"

long long t;
int fps = 0;

void cdear(int type, void* cookie, void* data)
{
	if (current_time_m() == t)
	{
		fps++;
	}
	else
	{
		printf("fps:%d\n", fps);
		fps = 0;
		t = current_time_m();
	}

}

void testCamera(void)
{
	Video_Recorder* recorder = create_video_recorder(640, 480);
	recorder->setDataCallBack(recorder, (void*) cdear, (void*) cdear);
	start_video_recorder(recorder);
	stop_video_recorder(recorder);
	free(recorder);
	recorder = NULL;
}

int main(int argc, char **argv)
{
	t = current_time_m();
	testCamera();
}

