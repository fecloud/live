flv_src += src/flv/FLVTag.cpp src/flv/FLVScriptTagBody.cpp src/flv/FLVTagHeader.cpp src/flv/FLVVideoTagBody.cpp src/flv/FLVReader.cpp \
	
SOURCES += $(flv_src)

flv_module += $(patsubst %cpp,%o,$(filter %cpp ,$(flv_src))) 
flv_module += $(patsubst %c,%o,$(filter %c ,$(flv_src)))
	