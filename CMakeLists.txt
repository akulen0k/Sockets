cmake_minimum_required(VERSION 3.24)
project(Server)


set(CMAKE_CXX_STANDARD 17)
set(GCC_COVERAGE_COMPILE_FLAGS "-lws2_32 -Wextra -Wconversion")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lws2_32")

add_executable(Server main.cpp SocketServer.cpp SocketServer.h SocketClient.cpp SocketClient.h)
