
prefix=/usr/local

CC=$(CROSS_COMPILE)gcc
CXX=$(CROSS_COMPILE)g++

#-lliveMedia -lBasicUsageEnvironment -lUsageEnvironment -lgroupsock
LIBS=-lrtmp -lpthread -lvencoder -lrtsp -ldl
LIBS_DIR= -Lsrc/librtmp -L./lib

OPT=-O2 -DSOCKLEN_T=socklen_t -DNO_SSTREAM=1 -D_LARGEFILE_SOURCE=1 -D_FILE_OFFSET_BITS=64

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

OBJS += $(patsubst %cpp,%o,$(filter %cpp ,$(SOURCES))) 
OBJS +=$(patsubst %c,%o,$(filter %c ,$(SOURCES)))

TARGET :=live

all: librtmp live

FORCE:

librtmp: FORCE
	@cd ./src/librtmp; $(MAKE) all

live: $(OBJS)
	$(CXX) $(LIBS_DIR)  -o $@ $(OBJS) $(LIBS)

help:

clean:
	@cd ./src/librtmp; $(MAKE) clean
	rm -rf $(OBJS) $(TARGET)
	
%.o:%.c
	$(CC) $(CFLAGS) -c  $< -o $@ 

%.o:%.cpp
	$(CXX) $(CXXFLAGS) -c  $< -o $@ 
