carmer_src = src/camera/V4L2.c src/camera/CameraSource.c src/camera/camera.c
SOURCES += $(carmer_src)

carmer_module += $(patsubst %cpp,%o,$(filter %cpp ,$(carmer_src))) 
carmer_module += $(patsubst %c,%o,$(filter %c ,$(carmer_src)))
	