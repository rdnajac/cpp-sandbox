#include <iostream>
#include <string>
#include <cstring>
#include "client.hpp"
#include "utils.h"

class TCPEchoClient {
public:
    TCPEchoClient(const std::string &server_ip, const std::string &server_port)
        : server_ip_(server_ip), server_port_(server_port) {}

    void send_and_receive(const std::string &message) {
        int server_fd = connect_to_host(server_ip_.c_str(), server_port_.c_str());
        if (server_fd == -1) {
            std::cerr << "Failed to connect to server" << std::endl;
            return;
        }

        ssize_t sent_bytes = strsend(server_fd, message.c_str());
        if (sent_bytes == -1) {
            std::cerr << "Failed to send message" << std::endl;
            close_socket(server_fd);
            return;
        }

        char buffer[1024] = {0};
        ssize_t received_bytes = recv(server_fd, buffer, sizeof(buffer) - 1, 0);
        if (received_bytes == -1) {
            std::cerr << "Failed to receive response" << std::endl;
            close_socket(server_fd);
            return;
        }

        std::cout << "Received: " << buffer << std::endl;
        std::cout << "Sent " << sent_bytes << " bytes and received " << received_bytes << " bytes in total" << std::endl;

        close_socket(server_fd);
    }

private:
    std::string server_ip_;
    std::string server_port_;
};

int main(int argc, char *argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <echo-word> <server-addr> <server-port>" << std::endl;
        return 1;
    }

    std::string echo_word = argv[1];
    std::string server_ip = argv[2];
    std::string server_port = argv[3];

    TCPEchoClient client(server_ip, server_port);
    client.send_and_receive(echo_word);

    return 0;
}
