CC = gcc
CXX = g++
AR = ar
ARFLAGS = rcs
CFLAGS = -std=c11 -Wall -Wextra -pedantic
CXXFLAGS = -std=c++20 -Wall -Wextra -pedantic
LDFLAGS = -pthread

SRCS = server.cpp client.cpp tcp.c
OBJS = $(SRCS:.cpp=.o) $(SRCS:.c=.o)

.PHONY: all clean

all: server client

server: server.o tcp.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

client: client.o tcp.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f server client $(OBJS)

