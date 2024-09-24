ifeq ($(shell uname), Darwin)
    CXX = g++-14
    CC = gcc
else 
    CXX = clang++
    CC = clang
endif

CXXFLAGS = -std=c++20 -Wall -Wextra -pedantic
CFLAGS = -std=c11 -Wall -Wextra -pedantic
LDFLAGS = -pthread

SRCS = server.cpp client.cpp
OBJS = $(SRCS:.cpp=.o) utils.o
DEPS = $(SRCS:.cpp=.d)

.PHONY: all clean

all: server client

server: server.o utils.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

client: client.o utils.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

utils.o: utils.c
	$(CC) $(CFLAGS) -c $< -o $@

# Include the dependency files
-include $(DEPS)

clean:
	rm -f server client $(OBJS) $(DEPS)
