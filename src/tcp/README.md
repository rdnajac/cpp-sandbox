# TCP Echo Server and Client

This project implements a simple TCP echo server and client in C++. The server listens for incoming connections and echoes back any data it receives. The client connects to the server, sends a message, and prints the response.

## Prerequisites

- C++17 compatible compiler (e.g., GCC 7+ or Clang 5+)
- Make build system
- POSIX-compatible operating system (Linux, macOS, etc.)

## Project Structure

The project consists of the following files:

- `server.cpp`: Implementation of the TCP echo server
- `client.cpp`: Implementation of the TCP echo client
- `utils.h`: Header file for utility functions
- `utils.cpp`: Implementation of utility functions
- `Makefile`: Build script for compiling the project

## Building the Project

To build the project, follow these steps:

1. Open a terminal and navigate to the project directory.
2. Run the following command:

   ```
   make
   ```

This will compile both the server and client executables.

## Running the Server

To start the echo server, use the following command:

```
./server <port>
```

Replace `<port>` with the port number you want the server to listen on (e.g., 8080).

Example:

```
./server 8080
```

The server will start and listen for incoming connections on the specified port.

## Running the Client

To run the client and send a message to the server, use the following command:

```
./client <message> <server-ip> <server-port>
```

- Replace `<message>` with the text you want to send to the server.
- Replace `<server-ip>` with the IP address of the server (use 127.0.0.1 for localhost).
- Replace `<server-port>` with the port number the server is listening on.

Example:

```
./client "Hello, Server!" 127.0.0.1 8080
```

The client will connect to the server, send the message, receive the echo response, and display it.

## Cleaning Up

To remove all compiled files and start fresh, run:

```
make clean
```

This will remove the server and client executables, as well as any object files.

## Note

This project is designed for educational purposes and may not be suitable for production environments without further enhancements.
