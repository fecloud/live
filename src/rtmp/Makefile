vlrtmp_src += src/rtmp/vlrtmp.cpp
	
SOURCES += $(vlrtmp_src)
	
vlrtmp_module += $(patsubst %cpp,%o,$(filter %cpp ,$(vlrtmp_src))) 
vlrtmp_module += $(patsubst %c,%o,$(filter %c ,$(vlrtmp_src)))
	