//
// Created by andrey on 21.04.2023.
//

#ifndef SERVER_SOCKETCLIENT_H
#define SERVER_SOCKETCLIENT_H

#include <winsock2.h>
#include <windows.h>

#include <string>

#define BUF_SIZE 1024

class SocketClient {
private:
    SOCKET client_socket;
    char buff[BUF_SIZE];
public:
    SocketClient(const std::string &ip, u_short port);
    void SendToServer(const std::string &msg) const;
};


#endif //SERVER_SOCKETCLIENT_H
