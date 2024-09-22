#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <atomic>
#include <format>
#include "utils.h"

#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

class TCPEchoServer {
public:
    TCPEchoServer(const std::string& port) : port_(port), running_(false) {}

    void start() {
        addrinfo hints{};
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;
        hints.ai_flags = AI_PASSIVE;

        addrinfo* info = utils::get_address_info(nullptr, port_.c_str(), &hints);

        server_fd_ = utils::create_socket(info->ai_family, info->ai_socktype, info->ai_protocol);

        utils::bind_socket(server_fd_, info->ai_addr, info->ai_addrlen);

        freeaddrinfo(info);

        utils::listen_on_socket(server_fd_, SOMAXCONN);

        running_ = true;
        std::cout << std::format("Server listening on port {}\n", port_);

        while (running_) {
            sockaddr_in client_addr{};
            socklen_t client_addr_len = sizeof(client_addr);

            try {
                int client_fd = utils::accept_connection(server_fd_, reinterpret_cast<sockaddr*>(&client_addr), &client_addr_len);
                std::cout << std::format("Accepted connection from {}\n", 
                    utils::get_ip_str(reinterpret_cast<sockaddr*>(&client_addr)));

                std::jthread client_thread(&TCPEchoServer::handle_client, this, client_fd);
            } catch (const std::system_error& e) {
                if (e.code().value() != EINTR) {
                    std::cerr << std::format("Error accepting connection: {}\n", e.what());
                }
            }
        }
    }

    void stop() {
        running_ = false;
        close(server_fd_);
    }

private:
    void handle_client(int client_fd) {
        try {
            while (true) {
                auto message = utils::receive_bytes(client_fd, 1024);
                if (message.empty()) {
                    break;
                }
                utils::send_bytes(client_fd, message);
                std::cout << std::format("Echoed message: {}\n", utils::bytes_to_string(message));
            }
        } catch (const std::exception& e) {
            std::cerr << std::format("Error handling client: {}\n", e.what());
        }

        close(client_fd);
    }

    std::string port_;
    int server_fd_;
    std::atomic<bool> running_;
};

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << std::format("Usage: {} <server-port>\n", argv[0]);
        return 1;
    }

    try {
        TCPEchoServer server(argv[1]);
        server.start();
    } catch (const std::exception& e) {
        std::cerr << std::format("Error: {}\n", e.what());
        return 1;
    }

    return 0;
}