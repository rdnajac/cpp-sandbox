CXX = g++
CXXFLAGS = -g -Wall -Wpedantic -std=c++17

# By default, build all targets
.PHONY: default
default: myncat mycopy

myncat: myncat.cpp utils.hpp
	$(CXX) $(CXXFLAGS) -o $@ $<

mycopy: mycopy.cpp utils.hpp
	$(CXX) $(CXXFLAGS) -o $@ $<

.PHONY: clean
clean:
	rm -rf *.o a.out myncat mycopy
