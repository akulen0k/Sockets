//
// Created by andrey on 21.04.2023.
//

#include "SocketClient.h"

#include <stdexcept>
#include <fstream>
#include <iostream>

SocketClient::SocketClient(const std::string &ip, u_short port) {
    int wVersionRequested = MAKEWORD(2, 2);
    WSADATA wsaData;
    if (int error = WSAStartup(wVersionRequested, &wsaData)) {
        throw std::runtime_error("Failed to start: " + std::to_string(error));
    }

    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        int error = WSAGetLastError();
        WSACleanup();
        throw std::runtime_error("Failed to create socket: " + std::to_string(error));
    }

    sockaddr_in addr_info{};
    addr_info.sin_family = AF_INET;
    addr_info.sin_addr.s_addr = inet_addr(ip.c_str());
    addr_info.sin_port = htons(port);
    if (int error = connect(client_socket, (sockaddr*) &addr_info, sizeof(addr_info))) {
        closesocket(client_socket);
        WSACleanup();
        throw std::runtime_error("Failed to connect: " + std::to_string(error));
    }
}

void SocketClient::SendToServer(const std::string &msg) const {
    char* sendbuff = new char[msg.size() + 1];
    msg.copy(sendbuff, msg.size());
    sendbuff[msg.size()] = 0;
    send(client_socket, sendbuff, static_cast<int>(strlen(sendbuff)), 0);
    delete[] sendbuff;
}

void SocketClient::SendFileToServer(const std::string &filename) const {
    std::ifstream infile(filename);
    if (!infile.good()) {
        throw std::runtime_error("Error on file open: " + filename);
    }

    infile.seekg(0, std::ios::end);
    size_t file_size = infile.tellg();
    infile.seekg(0, std::ios::beg);

    char* buff = new char[filename.size() + 1 + file_size + 1];
    filename.copy(buff, filename.size());
    buff[filename.size()] = '$';
    infile.read(buff + filename.size() + 1, static_cast<long long>(file_size));
    buff[filename.size() + 1 + file_size] = 0;
    infile.close();

    send(client_socket, buff, static_cast<int>(strlen(buff)), 0);
    delete[] buff;
}

SocketClient::~SocketClient() {
    closesocket(client_socket);
    WSACleanup();
}
