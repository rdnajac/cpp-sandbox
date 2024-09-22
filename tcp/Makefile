CXX = g++-14
CXXFLAGS = -std=c++20 -Wall -Wextra -pedantic
LDFLAGS = -pthread

SRCS = server.cpp client.cpp utils.cpp
OBJS = $(SRCS:.cpp=.o)
DEPS = $(SRCS:.cpp=.d)

.PHONY: all clean

all: server client

server: server.o utils.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

client: client.o utils.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

-include $(DEPS)

clean:
	rm -f server client $(OBJS) $(DEPS)
