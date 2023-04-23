//
// Created by andrey on 20.04.2023.
//

#include "SocketServer.h"

#include <process.h>

#include <stdexcept>
#include <fstream>
#include <iostream>

#include <algorithm>

SocketServer::SocketServer(const std::string &ip, u_short port) {
    WORD wVersionRequested = MAKEWORD(2, 2);
    WSADATA wsaData;
    if (int error = WSAStartup(wVersionRequested, &wsaData)) {
        throw std::runtime_error("Failed to start: " + std::to_string(error));
    }

    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        int error = WSAGetLastError();
        WSACleanup();
        throw std::runtime_error("Failed to create socket: " + std::to_string(error));
    }

    sockaddr_in socket_info{};
    socket_info.sin_family = AF_INET;
    socket_info.sin_addr.s_addr = inet_addr(ip.c_str());
    socket_info.sin_port = htons(port);
    if (bind(server_socket, (SOCKADDR*) &socket_info, sizeof(socket_info)) == SOCKET_ERROR) {
        int error = WSAGetLastError();
        closesocket(server_socket);
        WSACleanup();
        throw std::runtime_error("Failed to bind socket: " + std::to_string(error));
    }
}

void SocketServer::Start(int queue_size, int type_of_server) {
    if (listen(server_socket, queue_size) == SOCKET_ERROR) {
        int error = WSAGetLastError();
        closesocket(server_socket);
        WSACleanup();
        throw std::runtime_error("Error on listen: " + std::to_string(error));
    }

    SOCKET client_socket;
    sockaddr_in client_addr;
    int client_addr_size = sizeof(client_addr);
    while ((client_socket = accept(server_socket, (sockaddr*) &client_addr, &client_addr_size))) {
        DWORD thID;
        if (type_of_server == 0) {
            _beginthread(HandleClientMessages, 0, (void *) client_socket);
        } else {
            _beginthread(HandleClientFiles, 0, (void *) client_socket);
        }
    }
}

void SocketServer::HandleClientMessages(void* client_sock) {
    auto client_socket = reinterpret_cast<SOCKET>(client_sock);
    int nsize;
    char buff[BUF_SIZE];
    while ((nsize = recv(client_socket, buff, sizeof(buff), 0)) != SOCKET_ERROR) {
        std::cout << "Recieved message: " << std::string(buff, buff + nsize);
        while (nsize == BUF_SIZE) {
            nsize = recv(client_socket, buff, sizeof(buff), 0);
            std::cout <<  std::string(buff, buff + nsize);
        }
        std::cout << std::endl;
    }
    closesocket(client_socket);
}

void SocketServer::HandleClientFiles(void* client_sock) {
    auto client_socket = reinterpret_cast<SOCKET>(client_sock);
    int nsize;
    char buff[BUF_SIZE];
    while ((nsize = recv(client_socket, buff, sizeof(buff), 0)) != SOCKET_ERROR) {
        if (nsize == 0) {
            continue;
        }

        auto pos = std::find(buff, buff + BUF_SIZE, '$');
        if (pos == std::end(buff)) {
            closesocket(client_socket);
            WSACleanup();
            throw std::runtime_error("Invalid data, \'$\' not found");
        }

        std::string file_name(buff, buff + (pos - &buff[0]));
        std::cout << "Recieved file: " << file_name << std::endl;
        std::ofstream outfile(file_name, std::ios::trunc);
        if (!outfile.good()) {
            closesocket(client_socket);
            WSACleanup();
            throw std::runtime_error("Failed to create/write file: " + file_name);
        }

        outfile.write(buff + (pos - &buff[0]) + 1, static_cast<long long>(nsize - file_name.size() - 1));
        while (nsize == BUF_SIZE) {
            nsize = recv(client_socket, buff, sizeof(buff), 0);
            outfile.write(buff, nsize);
        }
        outfile.close();
    }
    closesocket(client_socket);
}

SocketServer::~SocketServer() {
    closesocket(server_socket);
    WSACleanup();
}


