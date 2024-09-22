#include <iostream>
#include <string>
#include <vector>
#include <format>
#include "utils.h"

#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

class TCPEchoClient {
public:
    TCPEchoClient(const std::string& server_ip, const std::string& server_port)
        : server_ip_(server_ip), server_port_(server_port) {}

    void send_and_receive(const std::string& message) {
        addrinfo hints{};
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;

        addrinfo* info = utils::get_address_info(server_ip_.c_str(), server_port_.c_str(), &hints);

        int server_fd = utils::create_socket(info->ai_family, info->ai_socktype, info->ai_protocol);

        utils::connect_to_server(server_fd, info->ai_addr, info->ai_addrlen);

        freeaddrinfo(info);

        auto message_bytes = utils::string_to_bytes(message);
        utils::send_bytes(server_fd, message_bytes);

        auto received_bytes = utils::receive_bytes(server_fd, message.length());
        std::string received_message = utils::bytes_to_string(received_bytes);

        std::cout << std::format("Received: {}\n", received_message);
        std::cout << std::format("Sent and received {} bytes in total\n", received_message.length());

        close(server_fd);
    }

private:
    std::string server_ip_;
    std::string server_port_;
};

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << std::format("Usage: {} <echo-word> <server-addr> <server-port>\n", argv[0]);
        return 1;
    }

    std::string echo_word = argv[1];
    std::string server_ip = argv[2];
    std::string server_port = argv[3];

    try {
        TCPEchoClient client(server_ip, server_port);
        client.send_and_receive(echo_word);
    } catch (const std::exception& e) {
        std::cerr << std::format("Error: {}\n", e.what());
        return 1;
    }

    return 0;
}