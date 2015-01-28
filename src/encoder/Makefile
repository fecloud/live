encode_src +=src/encoder/FLVEncoder.cpp src/encoder/SpsDecode.cpp
	
SOURCES += $(encode_src)	
	
encode_module += $(patsubst %cpp,%o,$(filter %cpp ,$(encode_src))) 
encode_module += $(patsubst %c,%o,$(filter %c ,$(encode_src)))
	