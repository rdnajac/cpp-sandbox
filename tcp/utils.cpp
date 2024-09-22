#include "utils.h"
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

namespace utils {

int create_socket(int domain, int type, int protocol) {
    int sockfd = socket(domain, type, protocol);
    if (sockfd == -1) {
        throw std::system_error(errno, std::generic_category(), "socket creation failed");
    }
    return sockfd;
}

void bind_socket(int sockfd, const struct sockaddr* addr, socklen_t addrlen) {
    if (bind(sockfd, addr, addrlen) == -1) {
        throw std::system_error(errno, std::generic_category(), "bind failed");
    }
}

void listen_on_socket(int sockfd, int backlog) {
    if (listen(sockfd, backlog) == -1) {
        throw std::system_error(errno, std::generic_category(), "listen failed");
    }
}

int accept_connection(int sockfd, struct sockaddr* addr, socklen_t* addrlen) {
    int client_fd = accept(sockfd, addr, addrlen);
    if (client_fd == -1) {
        throw std::system_error(errno, std::generic_category(), "accept failed");
    }
    return client_fd;
}

void connect_to_server(int sockfd, const struct sockaddr* addr, socklen_t addrlen) {
    if (connect(sockfd, addr, addrlen) == -1) {
        throw std::system_error(errno, std::generic_category(), "connect failed");
    }
}

struct addrinfo* get_address_info(const char* node, const char* service, 
                                  const struct addrinfo* hints) {
    struct addrinfo* result;
    int status = getaddrinfo(node, service, hints, &result);
    if (status != 0) {
        throw std::system_error(status, std::generic_category(), "getaddrinfo failed");
    }
    return result;
}

std::string get_ip_str(const struct sockaddr* sa) {
    char ip[INET6_ADDRSTRLEN];
    switch(sa->sa_family) {
        case AF_INET:
            inet_ntop(AF_INET, &(((struct sockaddr_in *)sa)->sin_addr),
                      ip, INET6_ADDRSTRLEN);
            break;
        case AF_INET6:
            inet_ntop(AF_INET6, &(((struct sockaddr_in6 *)sa)->sin6_addr),
                      ip, INET6_ADDRSTRLEN);
            break;
        default:
            return "Unknown AF";
    }
    return std::string(ip);
}

void send_bytes(int sockfd, std::span<const std::byte> data) {
    size_t total_sent = 0;
    while (total_sent < data.size()) {
        ssize_t sent = send(sockfd, data.data() + total_sent, data.size() - total_sent, 0);
        if (sent == -1) {
            throw std::system_error(errno, std::generic_category(), "send failed");
        }
        total_sent += sent;
    }
}

std::vector<std::byte> receive_bytes(int sockfd, size_t size) {
    std::vector<std::byte> data(size);
    size_t total_received = 0;
    while (total_received < size) {
        ssize_t received = recv(sockfd, data.data() + total_received, size - total_received, 0);
        if (received == -1) {
            throw std::system_error(errno, std::generic_category(), "recv failed");
        }
        if (received == 0) {
            throw std::runtime_error("Connection closed by peer");
        }
        total_received += received;
    }
    return data;
}

std::vector<std::byte> string_to_bytes(const std::string& str) {
    return {reinterpret_cast<const std::byte*>(str.data()),
            reinterpret_cast<const std::byte*>(str.data() + str.size())};
}

std::string bytes_to_string(std::span<const std::byte> bytes) {
    return {reinterpret_cast<const char*>(bytes.data()), bytes.size()};
}

}  // namespace utils