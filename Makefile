
prefix=/usr/local

CC=$(CROSS_COMPILE)gcc
CXX=$(CROSS_COMPILE)g++

INC=-Ithird

#-lliveMedia -lBasicUsageEnvironment -lUsageEnvironment -lgroupsock
LIBS=-lrtmp -lpthread -lvencoder -lliveMedia -lrt -lPocoXML -lPocoJSON -lPocoUtil -lPocoNet -lPocoFoundation -lgroupsock -lUsageEnvironment -lBasicUsageEnvironment -ldl
LIBS_DIR=-L./lib

OPT=-O2 $(INC) -DSOCKLEN_T=socklen_t -DNO_SSTREAM=1 -D_LARGEFILE_SOURCE=1 -D_FILE_OFFSET_BITS=64 -DC_DEBUG=0 -DCPP_DEBUG=0

CFLAGS =-Wall $(OPT) 
CXXFLAGS =-Wall $(OPT)


SOURCES +=

include src/Makefile
include src/h264/Makefile
include src/flv/lang/Makefile
include src/flv/Makefile
include src/io/Makefile
include src/encoder/Makefile
include src/camera/Makefile
include src/live/Makefile
include src/media/Makefile
include src/server/Makefile

OBJS += $(patsubst %cpp,%o,$(filter %cpp ,$(SOURCES))) 
OBJS +=$(patsubst %c,%o,$(filter %c ,$(SOURCES)))

TARGET :=live

all:  vlserver

live: $(OBJS)
	$(CXX) $(LIBS_DIR)  -o $@ $(OBJS) $(LIBS)

vlserver: $(VLSERVER_MAIN_OBJ) $(OBJS)
	$(CXX) $(LIBS_DIR)  -o $@ $(VLSERVER_MAIN_OBJ) $(base_module) $(carmer_module) $(media_module) $(server_module) -lpthread -lvencoder -lPocoXML -lPocoJSON -lPocoUtil -lPocoNet -lPocoFoundation -ldl -lrt

help:

install:
	mkdir -p $(prefix)
	cp vlserver $(prefix)/vlserver

clean:
	rm -rf $(OBJS) vlserver
	
%.o:%.c
	$(CC) $(CFLAGS) -c  $< -o $@ 

%.o:%.cpp
	$(CXX) $(CXXFLAGS) -c  $< -o $@ 
