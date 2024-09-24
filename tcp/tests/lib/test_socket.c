#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include "../../lib/tcp.h"

void test_open_listening_socket() {
    int sockfd = open_listening_socket("8080", 5);
    if (sockfd != -1) {
        printf("Successfully opened listening socket on port 8080.\n");
        close_socket(sockfd);
    } else {
        fprintf(stderr, "Failed to open listening socket: %s\n", strerror(errno));
    }
}

void test_accept() {
    int sockfd = open_listening_socket("8080", 5);
    if (sockfd != -1) {
        printf("Listening for incoming connections...\n");
        int client_sockfd = Accept(sockfd);
        if (client_sockfd != -1) {
            printf("Accepted a client connection.\n");
            close_socket(client_sockfd);
        } else {
            fprintf(stderr, "Failed to accept a connection: %s\n", strerror(errno));
        }
        close_socket(sockfd);
    } else {
        fprintf(stderr, "Failed to open listening socket: %s\n", strerror(errno));
    }
}

int main() {
    printf("Running tests for Open Listening Socket:\n");
    test_open_listening_socket();
    printf("\nRunning tests for Accepting Connections:\n");
    test_accept();
    
    return 0;
}
