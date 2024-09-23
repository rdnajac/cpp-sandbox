ifeq ($(shell uname), Darwin)
    CXX = g++-14
else 
    CXX = clang++
endif

CXXFLAGS = -std=c++20 -Wall -Wextra -pedantic
LDFLAGS = -pthread

SRCS = server.cpp client.cpp utils.cpp
DEPS = $(SRCS:.cpp=.d)

.PHONY: all clean

all: server client

server: server.cpp utils.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

client: client.cpp utils.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

-include $(DEPS)

clean:
	rm -f server client $(DEPS)

