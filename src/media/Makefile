media_src +=src/media/videorecorder.c src/media/water_mark.c
SOURCES+=$(media_src)
	
media_module += $(patsubst %cpp,%o,$(filter %cpp ,$(media_src))) 
media_module +=$(patsubst %c,%o,$(filter %c ,$(media_src)))