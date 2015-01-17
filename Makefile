
prefix=/usr/local

CC=$(CROSS_COMPILE)gcc
CXX=$(CROSS_COMPILE)g++


LIBS=-ld
LIBS_DIR=

OPT=-O2

CFLAGS =-Wall $(OPT) -DDEBUG
CXXFLAGS =-Wall $(OPT) -DDEBUG


SOURCES +=

OBJS += 

include src/Makefile
include src/h264/Makefile
include src/flv/lang/Makefile
include src/flv/Makefile
include src/io/Makefile
include src/encoder/Makefile
include src/camera/Makefile
include src/live/Makefile
include src/media/Makefile

TARGET :=live

all: librtmp live

FORCE:

librtmp: FORCE
	@cd ./src/librtmp; $(MAKE) all

live: $(OBJS)
	$(CXX)  -Lsrc/librtmp -L./lib -o $@ $(OBJS) -lrtmp -lpthread -lvencoder -ldl

help:

clean:
	@cd ./src/librtmp; $(MAKE) clean
	rm -rf $(OBJS) $(TARGET)
	
%.o:%.c
	$(CC) $(CFLAGS) -c  $< -o $@ 

%.o:%.cpp
	$(CXX) $(CXXFLAGS) -c  $< -o $@ 
