
prefix=/usr/local

CC=$(CROSS_COMPILE)gcc
CXX=$(CROSS_COMPILE)g++

INC=-Ithird -Isrc

LIBS_base= -lpthread -lrt -ldl
LIBS_encode = -lvencoder
LIBS_rtmp = -lrtmp
LIBS_rtsp = -lliveMedia -lgroupsock -lUsageEnvironment -lBasicUsageEnvironment
LIBS_poco = -lPocoXML -lPocoJSON -lPocoUtil -lPocoNet -lPocoFoundation

LIBS_DIR=-L./lib

P_Macro=-DH264_TB=1024*1024 -DCAP_FPS=30 -DH264_IDR=5
OPT=-O2 $(INC) -DSOCKLEN_T=socklen_t -DNO_SSTREAM=1 -D_LARGEFILE_SOURCE=1 -D_FILE_OFFSET_BITS=64 -DC_DEBUG=0 -DCPP_DEBUG=0 $(P_Macro)

CFLAGS =-Wall $(OPT) 
CXXFLAGS =-Wall $(OPT)


SOURCES +=

include src/base/Makefile
include src/h264/Makefile
include src/flv/lang/Makefile
include src/flv/Makefile
include src/encoder/Makefile
include src/camera/Makefile
include src/rtmp/Makefile
include src/rtsp/Makefile
include src/media/Makefile
include src/server/Makefile
include src/exe/Makefile

OBJS += $(patsubst %cpp,%o,$(filter %cpp ,$(SOURCES))) 
OBJS +=$(patsubst %c,%o,$(filter %c ,$(SOURCES)))

TARGET :=all

all:  vlserver vlrtmp vlrtsp vlsave recorder

live: $(OBJS)
	$(CXX) $(LIBS_DIR)  -o $@ $(OBJS) $(LIBS)

vlserver: $(OBJS)
	$(CXX) $(LIBS_DIR)  -o $@ $(vlserver) $(base_module) $(carmer_module) $(media_module) $(server_module) $(LIBS_base) $(LIBS_encode) $(LIBS_poco)

vlrtmp: $(OBJS)
	$(CXX) $(LIBS_DIR)  -o $@ $(vlrtmp) $(base_module) $(rtmp_module) $(h264_module) $(flv_module) $(lang_module) $(encode_module) $(LIBS_base) $(LIBS_rtmp) $(LIBS_poco)

vlrtsp: $(OBJS)
	$(CXX) $(LIBS_DIR)  -o $@ $(vlrtsp) $(base_module) $(io_module) $(h264_module) $(rtsp_module) $(LIBS_base) $(LIBS_rtsp) $(LIBS_poco) 

vlsave: $(OBJS)
	$(CXX) $(LIBS_DIR)  -o $@ $(vlsave) $(base_module) $(h264_module) $(LIBS_base) $(LIBS_poco) 
	
recorder: $(OBJS)
	$(CXX) $(LIBS_DIR)  -o $@ $(recorder) $(base_module) $(carmer_module) $(media_module) $(LIBS_base) $(LIBS_encode)
	
help:

install:
	mkdir -p $(prefix)
	cp vlserver $(prefix)/vlserver
	cp vlrtmp $(prefix)/vlrtmp
	cp vlrtsp $(prefix)/vlrtsp
	cp vlsave $(prefix)/vlsave
	cp recorder $(prefix)/recorder

clean:
	rm -rf $(OBJS) vlserver vlrtmp vlrtsp vlsave recorder
	
%.o:%.c
	$(CC) $(CFLAGS) -c  $< -o $@ 

%.o:%.cpp
	$(CXX) $(CXXFLAGS) -c  $< -o $@ 
