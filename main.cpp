#include "SocketServer.h"
#include "SocketClient.h"

#include <stdexcept>

#include <iostream>

#define SERVER_IP "192.168.1.2" // 192.168.1.6
#define PORT 5555
#define QUEUE_SIZE 100

int main(int argc, char* argv[]) {
    std::cout << "1. Server msg\n";
    std::cout << "2. Client msg\n";
    std::cout << "3. Server file\n";
    std::cout << "4. Client file\n";

    int cur_type;
    std::cin >> cur_type;
    if (cur_type == 1) {
        auto* s = new SocketServer(SERVER_IP, PORT);
        s->Start(QUEUE_SIZE, 0);
        delete s;
    } else if (cur_type == 2) {
        auto* s = new SocketClient(SERVER_IP, PORT);
        std::string msg;
        while (std::getline(std::cin, msg)) {
            s->SendToServer(msg);
        }
        delete s;
    } else if (cur_type == 3) {
        auto* s = new SocketServer(SERVER_IP, PORT);
        s->Start(QUEUE_SIZE, 1);
        delete s;
    } else if (cur_type == 4) {
        auto* s = new SocketClient(SERVER_IP, PORT);
        std::string file_name;
        while (std::cin >> file_name) {
            s->SendFileToServer(file_name);
        }
        delete s;
    } else {
        throw std::invalid_argument("Expected [1, 4], but " + std::to_string(cur_type) + " was found\n");
    }
    return 0;
}
