#include "SocketServer.h"
#include "SocketClient.h"

#include <stdexcept>

#include <iostream>

#define SERVER_IP "192.168.1.2" // 192.168.1.6
#define PORT 5555
#define QUEUE_SIZE 100

int main(int argc, char* argv[]) {
    std::cout << "1. Server\n";
    std::cout << "2. Client\n";

    int cur_type;
    std::cin >> cur_type;
    if (cur_type == 1) {
        auto* s = new SocketServer(SERVER_IP, PORT);
        s->Start(QUEUE_SIZE);
        delete s;
    } else if (cur_type == 2) {
        auto* s = new SocketClient(SERVER_IP, PORT);
        std::string msg;
        while (std::cin >> msg) {
            s->SendToServer(msg);
        }
    } else {
        throw std::invalid_argument("Expected 1 or 2, but " + std::to_string(cur_type) + " was found\n");
    }
    return 0;
}
