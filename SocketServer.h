//
// Created by andrey on 20.04.2023.
//

#ifndef SERVER_SOCKETSERVER_H
#define SERVER_SOCKETSERVER_H

#include <winsock2.h>
#include <windows.h>

#include <string>

#define BUF_SIZE 1024

class SocketServer {
private:
    SOCKET server_socket;
    char buff[BUF_SIZE];
public:
    SocketServer(const std::string &ip, u_short port);
    void Start(int queue_size);
    static void HandleClient(void* client_socket);
};


#endif //SERVER_SOCKETSERVER_H
