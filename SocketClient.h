//
// Created by andrey on 21.04.2023.
//

#ifndef SERVER_SOCKETCLIENT_H
#define SERVER_SOCKETCLIENT_H

#include <winsock2.h>
#include <windows.h>

#include <string>

class SocketClient {
private:
    SOCKET client_socket;
public:
    SocketClient(const std::string &ip, u_short port);
    //void SendToServer(const std::string &msg);
};


#endif //SERVER_SOCKETCLIENT_H
