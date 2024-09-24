#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include "../../lib/tcp.h"

void test_getaddrinfo() {
	struct addrinfo *info = Getaddrinfo("www.example.com", "80", 0, AF_INET, SOCK_STREAM, 0);
	if (info) {
		printf("Successfully retrieved addrinfo for www.example.com:\n");
		print_all_addrinfo(info);
		freeaddrinfo(info);
	} else {
		fprintf(stderr, "Failed to get addrinfo: %s\n", strerror(errno));
	}
}

void test_connect_to_host() {
	int sockfd = connect_to_host("www.example.com", "80");
	if (sockfd != -1) {
		printf("Successfully connected to www.example.com on port 80.\n");
		close_socket(sockfd);
	} else {
		fprintf(stderr, "Failed to connect: %s\n", strerror(errno));
	}
}

int main() {
	printf("Running tests for Getaddrinfo:\n");
	test_getaddrinfo();
	printf("\nRunning tests for Connect to Host:\n");
	test_connect_to_host();

	return 0;
}

