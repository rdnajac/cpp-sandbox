CXX = clang++
CXXFLAGS = -std=c++20 -Wall -O2

all: test_galois

galois_test: test_galois.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f test_galois

