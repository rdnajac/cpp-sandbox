#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include "tcp.h"

#define EXIT_ERR(msg) \
	do { perror(msg); exit(EXIT_FAILURE); } while (0)

/*
 * @brief Macro for iterating through addrinfo structures.
 * @param p Pointer to an addrinfo structure.
 * @param info Pointer to the first addrinfo structure.
 *
 * This macro is used to iterate through the linked list of addrinfo, starting
 * from the first addrinfo structure and continuing until it reaches the end.
 */
#define FOR_EACH_ADDRINFO(p, info) \
	for (p = info; p != NULL; p = p->ai_next)

/*
 * @brief Get the appropriate address structure based on the address family.
 */
#define GET_IN_ADDR(sa) \
	((sa->sa_family == AF_INET) ? \
	 (void *)&(((struct sockaddr_in*)sa)->sin_addr) : \
	 (void *)&(((struct sockaddr_in6*)sa)->sin6_addr))

struct addrinfo *Getaddrinfo(const char *hostname, const char *port,
		int flags, int family, int socktype, int protocol)
{
	static struct addrinfo hints;

	memset(&hints, 0, sizeof(hints));
	hints.ai_flags = flags;
	hints.ai_family = family;
	hints.ai_socktype = socktype;
	hints.ai_protocol = protocol;

	struct addrinfo *info;
	int error = getaddrinfo(hostname, port, &hints, &info);
	if (error) {
		fprintf(stderr, "getaddrinfo(): %s\n", gai_strerror(error));
		return NULL;
	}
	return info; /* remember to `freeaddrinfo()` */
}

void print_addrinfo(const struct addrinfo *info)
{
	char ipv4_addr[INET_ADDRSTRLEN] = { 0 };
	char ipv6_addr[INET6_ADDRSTRLEN] = { 0 };

	if (info->ai_family == AF_INET)
		inet_ntop(AF_INET, &((struct sockaddr_in *)info->ai_addr)->sin_addr, ipv4_addr, sizeof(ipv4_addr));
	else if (info->ai_family == AF_INET6)
		inet_ntop(AF_INET6, &((struct sockaddr_in6 *)info->ai_addr)->sin6_addr, ipv6_addr, sizeof(ipv6_addr));

	printf("struct addrinfo %p {\n", (void*)info);
	printf("\t.flags = %d,\n", info->ai_flags);
	printf("\t.family = %s,\n", (info->ai_family == AF_INET) ? "AF_INET" : (info->ai_family == AF_INET6) ? "AF_INET6" : "Unknown");
	printf("\t.socktype = %s,\n", (info->ai_socktype == SOCK_STREAM) ? "SOCK_STREAM" : (info->ai_socktype == SOCK_DGRAM) ? "SOCK_DGRAM" : "Unknown");
	printf("\t.protocol = %d,\n", info->ai_protocol);
	printf("\t.addrlen = %d,\n", (int)info->ai_addrlen);
	printf("\t.canonname = %s,\n", (info->ai_canonname) ? info->ai_canonname : "N/A");

	if (info->ai_family == AF_INET)
		printf("\tIPv4 Address: %s\n", ipv4_addr);
	else if (info->ai_family == AF_INET6)
		printf("\tIPv6 Address: %s\n", ipv6_addr);

	printf("}\n");
}

void print_all_addrinfo(const struct addrinfo *info)
{
	for (; info != NULL; info = info->ai_next)
		print_addrinfo(info);
}

/*
 * @brief Creates a socket based on the provided addrinfo.
 * @param info Pointer to a struct addrinfo with socket configuration.
 * @return Returns the file descriptor of the created socket, or -1 on error.
 */
static inline int Socket(struct addrinfo *info)
{
	int fd = socket(info->ai_family, info->ai_socktype, info->ai_protocol);
	if (fd == -1)
		perror("socket()");
	return fd;
}

/*
 * @brief Creates a client socket and connects it to a remote host specified in addrinfo.
 * @param sockfd The socket file descriptor.
 * @param info Pointer to struct addrinfo containing remote host information.
 * @return int Returns 0 on success, or -1 on error.
 */
static inline int Connect(int sockfd, struct addrinfo *info)
{
	if (connect(sockfd, info->ai_addr, info->ai_addrlen) == -1) {
		perror("connect()");
		close(sockfd);
		return -1;
	}
	return 0;
}

int connect_to_host(const char *hostname, const char *port)
{
	int sockfd;
	struct addrinfo *info;

	info = Getaddrinfo(hostname, port, 0, AF_INET, SOCK_STREAM, 0);
	if (!info)
		return -1;

	for (struct addrinfo *p = info; p != NULL; p = p->ai_next) {
		sockfd = Socket(p);
		if (sockfd == -1)
			continue; /* try next addrinfo */

		if (!Connect(sockfd, p))
			break; /* we're connected! */

		close(sockfd);
	}
	freeaddrinfo(info);
	return sockfd;
}

/*
 * @brief Binds a socket to an address and port specified in addrinfo.
 * @param sockfd Socket file descriptor.
 * @param info Pointer to struct addrinfo containing address and port information.
 * @return int Returns 0 on success, or -1 on error.
 */
static inline int Bind(int sockfd, struct addrinfo *info)
{
	if (bind(sockfd, info->ai_addr, info->ai_addrlen)) {
		perror("bind()");
		close(sockfd);
		return -1;
	}
	return 0;
}

/*
 * @brief Sets the socket to listen for incoming connections.
 * @param sockfd Socket file descriptor.
 * @param backlog The maximum length of the queue for pending connections.
 * @return int Returns 0 on success, or -1 on error.
 */
static inline int Listen(int sockfd, int backlog)
{
	if (listen(sockfd, backlog)) {
		perror("listen()");
		close(sockfd);
		return -1;
	}
	return 0;
}

int open_listening_socket(const char *port, int backlog)
{
	int sockfd;
	struct addrinfo *info;
	int yes = 1;

	info = Getaddrinfo(NULL, port, AI_PASSIVE, AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (!info)
		return -1; /* fatal error */

	sockfd = Socket(info);
	if (sockfd != -1) {
		/* lose the pesky "address already in use" error message */
		setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
		if (Bind(sockfd, info) || Listen(sockfd, backlog))
			sockfd = -1;
	}

	freeaddrinfo(info);
	return sockfd;
}

/*
 * @brief Accepts a client connection on the provided server socket.
 * @param serv_sockfd The server socket file descriptor.
 * @return The client socket file descriptor on success, -1 on error.
 *
 * @details This function accepts a client connection on the provided server socket.
 * It operates in blocking mode and retries if the operation would block.
 */
int Accept(int serv_sockfd)
{
	int clnt_sockfd;

	do {
		clnt_sockfd = accept(serv_sockfd, NULL, NULL);
	} while (clnt_sockfd == -1 && errno == EWOULDBLOCK);

	if (clnt_sockfd == -1)
		perror("accept()");

	return clnt_sockfd;
}

/*
 * @brief Send binary data over a socket.
 * @param sockfd The socket descriptor.
 * @param data The data to send.
 * @param len The length of the data to send.
 * @return The number of bytes sent on success, or -1 on error.
 *
 * @details
 * This function sends the specified amount of binary data over a given socket.
 * It continues to send data until either all data has been sent or an error occurs.
 * It handles partial sends by continuing to send the remaining data.
 */
static inline ssize_t Send(int sockfd, const void *data, size_t len)
{
	const char *data_ptr = data;
	size_t sent_total = 0;

	while (sent_total < len) {
		ssize_t sent_now = send(sockfd, data_ptr + sent_total, len - sent_total, 0);
		if (sent_now == -1) {
			perror("send()");
			return -1;
		}
		sent_total += sent_now;
	}
	return sent_total;
}

/*
 * @details
 * This function assumes that str is a null-terminated string, so
 * don't use this function to send binary data. It delegates the
 * actual sending to the Send function.
 */
ssize_t strsend(int sock, const char *str)
{
	size_t len = strlen(str);
	return Send(sock, str, len);
}

void close_socket(int sock)
{
	struct sockaddr_in addr;
	socklen_t addr_len = sizeof(addr);

	if (!getsockname(sock, (struct sockaddr *)&addr, &addr_len))
		fprintf(stderr, "Closing socket at fd %d bound to port: %d\n",
				sock, ntohs(addr.sin_port));
	if (close(sock))
		fprintf(stderr, "Error closing socket at fd %d\n", sock);
}

char *ip_from_fd(int sockfd)
{
	struct sockaddr_storage addr;
	socklen_t addr_len = sizeof(addr);

	if (getsockname(sockfd, (struct sockaddr*)&addr, &addr_len) == -1) {
		perror("getsockname()");
		return NULL;
	}

	size_t ip_size = (addr.ss_family == AF_INET) ? INET_ADDRSTRLEN : INET6_ADDRSTRLEN;
	char *ip_str = calloc(ip_size, sizeof(char));
	if (!ip_str) {
		perror("calloc()");
		return NULL;
	}

	if (addr.ss_family == AF_INET) {
		struct sockaddr_in *addr_in = (struct sockaddr_in*)&addr;
		if (!inet_ntop(AF_INET, &addr_in->sin_addr, ip_str, ip_size)) {
			perror("inet_ntop for IPv4");
			free(ip_str);
			return NULL;
		}
	} else if (addr.ss_family == AF_INET6) {
		struct sockaddr_in6 *addr_in6 = (struct sockaddr_in6*)&addr;
		if (!inet_ntop(AF_INET6, &addr_in6->sin6_addr, ip_str, ip_size)) {
			perror("inet_ntop for IPv6");
			free(ip_str);
			return NULL;
		}
	} else {
		fprintf(stderr, "Unsupported address family.\n");
		free(ip_str);
		return NULL;
	}
	return ip_str;
}

/*
 * Extra functions (not used in the main implementation)
 */

/*
 * @brief Send clnt_sock through sock.
 * @param clnt_sockfd Client socket file descriptor to be sent.
 * @param sock A UNIX domain socket.
 */
void send_connection(int clnt_sockfd, int sock)
{
	struct msghdr msg = {0};
	struct iovec iov[1];
	char buf[2] = "FD";

	union {
		struct cmsghdr cm;
		char control[CMSG_SPACE(sizeof(int))];
	} ctrl_un = {0};
	struct cmsghdr *cmptr;

	msg.msg_control = ctrl_un.control;
	msg.msg_controllen = sizeof(ctrl_un.control);

	cmptr = CMSG_FIRSTHDR(&msg);
	cmptr->cmsg_len = CMSG_LEN(sizeof(int));
	cmptr->cmsg_level = SOL_SOCKET;
	cmptr->cmsg_type = SCM_RIGHTS;
	*((int *) CMSG_DATA(cmptr)) = clnt_sockfd;

	msg.msg_name = NULL;
	msg.msg_namelen = 0;

	iov[0].iov_base = buf;
	iov[0].iov_len = 2;
	msg.msg_iov = iov;
	msg.msg_iovlen = 1;

	if (sendmsg(sock, &msg, 0) != 2)
		perror("Failed to send connection to child");
}

/*
 * @brief Returns an open file descriptor received through sock.
 * @param sock A UNIX domain socket.
 * @return int The received file descriptor, or -1 on error.
 */
int recv_connection(int sock)
{
	struct msghdr msg = {0};
	struct iovec iov[1];
	ssize_t n;
	char buf[2];

	union {
		struct cmsghdr cm;
		char control[CMSG_SPACE(sizeof(int))];
	} ctrl_un;
	struct cmsghdr *cmptr;

	msg.msg_control = ctrl_un.control;
	msg.msg_controllen = sizeof(ctrl_un.control);

	msg.msg_name = NULL;
	msg.msg_namelen = 0;

	iov[0].iov_base = buf;
	iov[0].iov_len = sizeof(buf);
	msg.msg_iov = iov;
	msg.msg_iovlen = 1;

	for (;;) {
		n = recvmsg(sock, &msg, 0);
		if (n == -1) {
			if (errno == EINTR)
				continue;
			perror("Error in recvmsg");
			return -1;
		}
		// Messages with client connections are always sent with
		// "FD" as the message. Silently skip unsupported messages.
		if (n != 2 || buf[0] != 'F' || buf[1] != 'D')
			continue;

		if ((cmptr = CMSG_FIRSTHDR(&msg)) != NULL
				&& cmptr->cmsg_len == CMSG_LEN(sizeof(int))
				&& cmptr->cmsg_level == SOL_SOCKET
				&& cmptr->cmsg_type == SCM_RIGHTS) {
			return *((int *) CMSG_DATA(cmptr));
		}
	}
}
