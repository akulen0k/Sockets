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
public:
    SocketServer(const std::string &ip, u_short port);
    ~SocketServer();
    void Start(int queue_size, int type_of_server);
    static void HandleClientMessages(void* client_socket);
    static void HandleClientFiles(void* client_socket);
};


#endif //SERVER_SOCKETSERVER_H
