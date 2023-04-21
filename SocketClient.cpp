//
// Created by andrey on 21.04.2023.
//

#include "SocketClient.h"

#include <stdexcept>
#include <iostream>

SocketClient::SocketClient(const std::string &ip, u_short port) {
    int wVersionRequested = MAKEWORD(2, 2);
    WSADATA wsaData;
    if (int error = WSAStartup(wVersionRequested, &wsaData)) {
        throw std::runtime_error("Failed to start: " + std::to_string(error));
    }

    if ((this->client_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        int error = WSAGetLastError();
        WSACleanup();
        throw std::runtime_error("Failed to create socket: " + std::to_string(error));
    }

    sockaddr_in addr_info{};
    addr_info.sin_family = AF_INET;
    addr_info.sin_addr.s_addr = inet_addr(ip.c_str());
    addr_info.sin_port = htons(port);
    if (int error = connect(this->client_socket, (sockaddr*) &addr_info, sizeof(addr_info))) {
        closesocket(this->client_socket);
        WSACleanup();
        throw std::runtime_error("Failed to connect: " + std::to_string(error));
    }
    std::cout << "Successfully connected" << std::endl;
}
