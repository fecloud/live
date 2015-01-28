server_src +=src/server/VideoLiveObservable.cpp src/server/VideoLiveObserver.cpp src/server/VideoLiveServer.cpp src/server/VideoLiveTCPConnection.cpp
 
SOURCES+=$(server_src)

server_module += $(patsubst %cpp,%o,$(filter %cpp ,$(server_src))) 
server_module += $(patsubst %c,%o,$(filter %c ,$(server_src)))
