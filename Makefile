
prefix=/usr/local

CC=$(CROSS_COMPILE)gcc
CXX=$(CROSS_COMPILE)g++

INC=-Ithird

#-lliveMedia -lBasicUsageEnvironment -lUsageEnvironment -lgroupsock
LIBS=-lrtmp -lpthread -lvencoder -lliveMedia -lrt -lPocoXML -lPocoJSON -lPocoUtil -lPocoNet -lPocoFoundation -lgroupsock -lUsageEnvironment -lBasicUsageEnvironment -ldl
LIBS_DIR=-L./lib

OPT=-O2 $(INC) -DSOCKLEN_T=socklen_t -DNO_SSTREAM=1 -D_LARGEFILE_SOURCE=1 -D_FILE_OFFSET_BITS=64

CFLAGS =-Wall $(OPT) -DDEBUG
CXXFLAGS =-Wall $(OPT) -DDEBUG


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

VLSERVER_MAIN_OBJ = $(patsubst %cpp,%o,$(VLSERVER_MAIN))

TARGET :=live

all:  vlserver

live: $(OBJS)
	$(CXX) $(LIBS_DIR)  -o $@ $(OBJS) $(LIBS)

vlserver: $(VLSERVER_MAIN_OBJ) $(OBJS)
	$(CXX) $(LIBS_DIR)  -o $@ $(VLSERVER_MAIN_OBJ) $(OBJS)  $(LIBS)

help:

clean:
	rm -rf $(OBJS) vlserver
	
%.o:%.c
	$(CC) $(CFLAGS) -c  $< -o $@ 

%.o:%.cpp
	$(CXX) $(CXXFLAGS) -c  $< -o $@ 
