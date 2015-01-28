io_src += src/io/FLVOutPutStream.cpp src/io/RTMPOutPutStream.cpp
	
SOURCES += $(io_src) 

io_module += $(patsubst %cpp,%o,$(filter %cpp ,$(io_src))) 
io_module += $(patsubst %c,%o,$(filter %c ,$(io_src)))
	