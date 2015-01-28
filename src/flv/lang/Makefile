lang_src +=src/flv/lang/Number.cpp src/flv/lang/String.cpp src/flv/lang/Struct.cpp  src/flv/lang/ECMAArray.cpp 
	
SOURCES += $(lang_src)

lang_module += $(patsubst %cpp,%o,$(filter %cpp ,$(lang_src))) 
lang_module += $(patsubst %c,%o,$(filter %c ,$(lang_src)))
	