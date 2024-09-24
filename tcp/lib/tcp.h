#ifndef _TCP_H
#define _TCP_H

#include <netdb.h> /* struct addrinfo */
#include <sys/types.h> /* ssize_t */

#ifdef __cplusplus
extern "C" {
#endif



/*
 * @brief Initializes addrinfo with the specified parameters.
 * @param hostname The hostname or IP address.
 * @param port The port number as a string.
 * @param flags Address info flags (e.g., AI_PASSIVE).
 * @param family Address family (e.g., AF_INET for IPv4).
 * @param socktype Socket type (e.g., SOCK_STREAM for TCP).
 * @param protocol Protocol (e.g., IPPROTO_TCP for TCP).
 * @return Pointer to the allocated addrinfo structure or NULL on error.
 */
struct addrinfo *Getaddrinfo(const char *hostname, const char *port,
		int flags, int family, int socktype, int protocol);
/*
 * @brief Prints the details of an addrinfo structure in a formatted manner.
 * @param info Pointer to an addrinfo structure.
 */
void print_addrinfo(const struct addrinfo *info);

/*
 * @brief Prints the details of a linked list of addrinfo structures.
 * @param info Pointer to the first node in a linked list of addrinfo structures.
 */
void print_all_addrinfo(const struct addrinfo *info);

/*
 * @brief Connects to a remote host.
 * @param hostname Hostname or IP address.
 * @param port Port number to connect to.
 * @return File descriptor of the connected socket, or -1 on error.
 */
int connect_to_host(const char *hostname, const char *port);

/*
 * @brief Opens a single server port for listening.
 * @param port The server port number as a string.
 * @param backlog The maximum length for the queue of pending connections.
 * @return int Returns the fd of the opened socket on success, or -1 on error.
 */
int open_listening_socket(const char *port, int backlog);

/*
 * @brief Wrapper function for accept that ignores client address and length parameters.
 * @param serv_sockfd The server socket file descriptor.
 * @return The client socket file descriptor on success, -1 on error.
 */
int Accept(int serv_sockfd);

/*
 * @brief Send a null-terminated string over a socket.
 * @param sock The socket descriptor.
 * @param str The string to send.
 * @return The number of bytes sent on success, or -1 on error.
 */
ssize_t strsend(int sock, const char *str);

/*
 * @brief Prints metadata about the socket then closes it.
 * @param sock The socket to be closed.
 */
void close_socket(int sock);

/*
 * @brief Extracts the IP address from a socket file descriptor and returns it as a newly allocated string.
 * @param sockfd The socket file descriptor from which to extract the IP address.
 * @return A newly allocated string containing the IP address, or NULL on error.
 */
char *ip_from_fd(int sockfd);

#ifdef __cplusplus
}
#endif

#endif /* _TCP_H */
