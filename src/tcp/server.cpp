#include <iostream>
#include <string>
#include <thread>
#include <atomic>
#include <cstring>
#include "utils.h"

class TCPEchoServer {
public:
    TCPEchoServer(const std::string& port) : port_(port), running_(false) {}

    void start() {
        server_fd_ = open_listening_socket(port_.c_str(), SOMAXCONN);
        if (server_fd_ == -1) {
            std::cerr << "Failed to open listening socket" << std::endl;
            return;
        }

        running_ = true;
        std::cout << "Server listening on port " << port_ << std::endl;

        while (running_) {
            int client_fd = Accept(server_fd_);
            if (client_fd == -1) {
                std::cerr << "Failed to accept connection" << std::endl;
                continue;
            }

            char* client_ip = ip_from_fd(client_fd);
            if (client_ip) {
                std::cout << "Accepted connection from " << client_ip << std::endl;
                free(client_ip);
            }

            std::thread client_thread(&TCPEchoServer::handle_client, this, client_fd);
            client_thread.detach();
        }
    }

    void stop() {
        running_ = false;
        close_socket(server_fd_);
    }

private:
    void handle_client(int client_fd) {
        char buffer[1024];
        while (true) {
            memset(buffer, 0, sizeof(buffer));
            ssize_t received_bytes = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
            if (received_bytes <= 0) {
                break;
            }
            ssize_t sent_bytes = strsend(client_fd, buffer);
            if (sent_bytes == -1) {
                std::cerr << "Failed to send response" << std::endl;
                break;
            }
            std::cout << "Echoed message: " << buffer << std::endl;
        }
        close_socket(client_fd);
    }

    std::string port_;
    int server_fd_;
    std::atomic<bool> running_;
};

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <server-port>" << std::endl;
        return 1;
    }

    TCPEchoServer server(argv[1]);
    server.start();

    return 0;
}