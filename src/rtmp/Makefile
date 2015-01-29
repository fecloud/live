rtmp_src += src/rtmp/RTMPOutPutStream.cpp
	
SOURCES += $(rtmp_src)

rtmp_module += $(patsubst %cpp,%o,$(filter %cpp ,$(rtmp_src))) 
rtmp_module += $(patsubst %c,%o,$(filter %c ,$(rtmp_src)))
	