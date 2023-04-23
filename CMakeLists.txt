cmake_minimum_required(VERSION 3.24)
project(Server)


set(CMAKE_CXX_STANDARD 17)
#set(GCC_COVERAGE_COMPILE_FLAGS "-lws2_32")
#set(GCC_COVERAGE_LINK_FLAGS "-lws2_32")

#SET(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
#SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")
#set(CMAKE_CXX_FLAGS_RELEASE "-lws2_32")
#set(CMAKE_CXX_FLAGS_DEBUG "-lws2_32")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS} -static")
link_libraries(ws2_32 wsock32)

add_executable(Server main.cpp SocketServer.cpp SocketServer.h SocketClient.cpp SocketClient.h)
