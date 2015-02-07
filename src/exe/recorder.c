/*
 * recorder.c
 *
 *  Created on: Jan 28, 2015
 *      Author: ouyangfeng
 */
#include <signal.h>

#include "base/utils.h"
#include "media/videorecorder.h"

long long t;
int fps = 0;
Video_Recorder *recorder = NULL;

void cdear(int type, void* cookie, void* data)
{
	if (current_time_m() == t)
	{
		fps++;
	}
	else
	{
		printf("fps:%d\n", fps);
		fps = 1;
		t = current_time_m();
	}

}

/* 信号处理例程，其中dunno将会得到信号的值 */
static void sigroutine(int dunno)
{
    stop_video_recorder(recorder);
	free(recorder);
	recorder = NULL;
    return;
}

void testCamera(void)
{
	recorder = create_video_recorder(640, 480);
	recorder->setDataCallBack(recorder, (void*) cdear, (void*) cdear);
	start_video_recorder(recorder);
}
#ifndef NO_MAIN
int main(int argc, char **argv)
{
	t = current_time_m();
	signal(SIGHUP, sigroutine); //* 下面设置三个信号的处理方法
	signal(SIGINT, sigroutine);
	signal(SIGQUIT, sigroutine);
	testCamera();
	return 1;
}
#endif
