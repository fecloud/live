rtsp_src += src/rtsp/H264FramedLiveSource.cpp src/rtsp/H264LiveVideoServerMediaSubssion.cpp

SOURCES += $(rtsp_src)

rtsp_module += $(patsubst %cpp,%o,$(filter %cpp ,$(rtsp_src))) 
rtsp_module += $(patsubst %c,%o,$(filter %c ,$(rtsp_src)))


