CXX := g++
CXXFLAGS := -std=c++20 -g -Wall -Wpedantic -O2
LDFLAGS :=

#Directories
INCLUDE_DIR := include
LIB_DIR := lib
OBJ_DIR := obj

#Source files
LIB_SOURCES := $(wildcard $(LIB_DIR)/*.cpp)
LIB_OBJECTS := $(patsubst $(LIB_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(LIB_SOURCES))

# Libraries
LIBS := $(OBJ_DIR)/libtimer.a $(OBJ_DIR)/librng.a

# Executables
EXECUTABLES := loops vectors

all: $(EXECUTABLES)

# Rule for executables
$(EXECUTABLES): %: %.cpp $(LIBS)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -o $@ $< -L$(OBJ_DIR) -ltimer -lrng

# Rule for object files
$(OBJ_DIR)/%.o: $(LIB_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Rule for static libraries
$(OBJ_DIR)/lib%.a: $(OBJ_DIR)/%.o
	ar rcs $@ $^

# Create object directory
$(OBJ_DIR):
	mkdir -p $@

clean:
	rm -rf $(OBJ_DIR) $(EXECUTABLES) ./*.dSYM

.PHONY: all clean
