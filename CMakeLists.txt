cmake_minimum_required (VERSION 3.2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(UNIX)
	set(CMAKE_CXX_FLAGS_DEBUG "-g")
	set(CMAKE_CXX_FLAGS_RELEASE "-O3")
endif(UNIX)

set(HEADERS 
	${HEADERS}
	task.h
	parqueue.h
	ticket.h
	simulator.h
	counter.h
	randgenerator.h
	logger.h
	)
	
set(SOURCES 
	${SOURCES}
	WaitRoomSM.cpp
	ticket.cpp
	simulator.cpp
	logger.cpp
	)
	

project (WaitRoomSM)

add_executable(WaitRoomSM ${SOURCES})
if(UNIX)
	target_link_libraries(WaitRoomSM pthread atomic)
endif (UNIX)