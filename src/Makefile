base_src =src/main.cpp src/Bytes.cpp src/utils.c	

SOURCES += $(base_src)

base_module += $(patsubst %cpp,%o,$(filter %cpp ,$(base_src))) 
base_module +=$(patsubst %c,%o,$(filter %c ,$(base_src)))
