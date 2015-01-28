base_src = src/base/Bytes.cpp src/base/utils.c	

SOURCES += $(base_src)

base_module += $(patsubst %cpp,%o,$(filter %cpp ,$(base_src))) 
base_module +=$(patsubst %c,%o,$(filter %c ,$(base_src)))
