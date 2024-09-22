#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <system_error>
#include <netdb.h>
#include <span>
#include <vector>

namespace utils {

// Wrapper for socket operations to throw exceptions on errors
int create_socket(int domain, int type, int protocol);
void bind_socket(int sockfd, const struct sockaddr* addr, socklen_t addrlen);
void listen_on_socket(int sockfd, int backlog);
int accept_connection(int sockfd, struct sockaddr* addr, socklen_t* addrlen);
void connect_to_server(int sockfd, const struct sockaddr* addr, socklen_t addrlen);

// Helper function to get address info
struct addrinfo* get_address_info(const char* node, const char* service, 
                                  const struct addrinfo* hints);

// Helper function to print IP address
std::string get_ip_str(const struct sockaddr* sa);

// Function to send a vector of bytes
void send_bytes(int sockfd, std::span<const std::byte> data);

// Function to receive a vector of bytes
std::vector<std::byte> receive_bytes(int sockfd, size_t size);

// New: Function to convert string to bytes
std::vector<std::byte> string_to_bytes(const std::string& str);

// New: Function to convert bytes to string
std::string bytes_to_string(std::span<const std::byte> bytes);

}  // namespace utils

#endif // UTILS_H