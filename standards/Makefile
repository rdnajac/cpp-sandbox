CXX := g++
CXXFLAGS := -Wall -Wextra -pedantic
TARGET := myprogram

.PHONY: all clean 11 14 17 20

all: 11 14 17 20

11:
	$(CXX) $(CXXFLAGS) -std=c++11 main.cpp -o $(TARGET)_11

14:
	$(CXX) $(CXXFLAGS) -std=c++14 main.cpp -o $(TARGET)_14

17:
	$(CXX) $(CXXFLAGS) -std=c++17 main.cpp -o $(TARGET)_17

20:
	$(CXX) $(CXXFLAGS) -std=c++20 main.cpp -o $(TARGET)_20

clean:
	rm -f $(TARGET)_11 $(TARGET)_14 $(TARGET)_17 $(TARGET)_20