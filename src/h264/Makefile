h264_src +=src/h264/H264NALU.cpp src/h264/H264Reader.cpp src/h264/NetH264Reader.cpp

SOURCES += $(h264_src)

h264_module += $(patsubst %cpp,%o,$(filter %cpp ,$(h264_src))) 
h264_module += $(patsubst %c,%o,$(filter %c ,$(h264_src)))