CXX = g++
CXXFLAGS = -std=c++17 -g -Wall -Wpedantic
LDFLAGS =

TARGET = main
SRCS = main.cpp classify-pointer.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c $<

classify-pointer.o: classify_pointer.cpp
	$(CXX) $(CXXFLAGS) -c $<

.PHONY: clean
clean:
	rm -f $(TARGET) $(OBJS)
