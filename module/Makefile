# Compiler
CXX = clang++
CXXFLAGS = -std=c++20 -fmodules-ts

# Targets
MODULE = std
MODULE_SRC = std.cppm
MAIN = main
MAIN_SRC = main.cpp
OUTPUT = program

# Default target
all: $(OUTPUT)

# Compile the module
$(MODULE).pcm: $(MODULE_SRC)
	$(CXX) $(CXXFLAGS) -c $<

# Compile and link the main program
$(OUTPUT): $(MAIN_SRC) $(MODULE).pcm
	$(CXX) $(CXXFLAGS) $^ -o $@

# Clean up build artifacts
clean:
	rm -f $(MODULE).pcm $(OUTPUT)

.PHONY: all clean

