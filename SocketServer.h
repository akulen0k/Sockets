//
// Created by andrey on 20.04.2023.
//

#ifndef SERVER_SOCKETSERVER_H
#define SERVER_SOCKETSERVER_H

#include <winsock2.h>
#include <windows.h>

#include <string>

class SocketServer {
private:
    SOCKET server_socket;
public:
    SocketServer(const std::string &ip, u_short port);
    void Start(int queue_size);
};


#endif //SERVER_SOCKETSERVER_H
