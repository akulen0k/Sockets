//
// Created by andrey on 20.04.2023.
//

#include "SocketServer.h"

#include <stdexcept>
#include <iostream>

SocketServer::SocketServer(const std::string &ip, u_short port) {
    WORD wVersionRequested = MAKEWORD(2, 2);
    WSADATA wsaData;
    if (int error = WSAStartup(wVersionRequested, &wsaData)) {
        throw std::runtime_error("Failed to start: " + std::to_string(error));
    }

    if ((this->server_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        int error = WSAGetLastError();
        WSACleanup();
        throw std::runtime_error("Failed to create socket: " + std::to_string(error));
    }

    sockaddr_in socket_info{};
    socket_info.sin_family = AF_INET;
    socket_info.sin_addr.s_addr = inet_addr(ip.c_str());
    socket_info.sin_port = htons(port);
    if (bind(this->server_socket, (SOCKADDR*) &socket_info, sizeof(socket_info)) == SOCKET_ERROR) {
        int error = WSAGetLastError();
        closesocket(this->server_socket);
        WSACleanup();
        throw std::runtime_error("Failed to bind socket: " + std::to_string(error));
    }
}

void SocketServer::Start(int queue_size) {
    if (listen(this->server_socket, queue_size) == SOCKET_ERROR) {
        int error = WSAGetLastError();
        closesocket(this->server_socket);
        WSACleanup();
        throw std::runtime_error("Error on listen: " + std::to_string(error));
    }

    SOCKET client_socket;
    sockaddr_in client_addr;
    int client_addr_size = sizeof(client_addr);
    while ((client_socket = accept(this->server_socket, (sockaddr*) &client_addr, &client_addr_size))) {
        std::cout << "New connection";
        closesocket(client_socket);
    }
}
