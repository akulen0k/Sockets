
server: main.o SocketServer.o SocketClient.o
	g++ main.o SocketServer.o SocketClient.o -o server -lws2_32

main.o: main.cpp
	g++ -c main.cpp

SocketServer.o: SocketServer.cpp SocketServer.h
	g++ -c SocketServer.cpp

SocketClient.o: SocketClient.cpp SocketClient.h
	g++ -c SocketClient.cpp
