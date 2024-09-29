NVCC := nvcc
NVCC_FLAGS := -O3

# List of all CUDA source files
SOURCES := vector_add.cu matrix_multiply.cu reduction.cu stream_example.cu unified_memory.cu

# Generate a list of executable names by removing the .cu extension
EXECUTABLES := $(SOURCES:.cu=)

.PHONY: all clean

all: $(EXECUTABLES)

# Implicit rule for compiling .cu files
%: %.cu
	$(NVCC) $(NVCC_FLAGS) $< -o $@

clean:
	rm -f $(EXECUTABLES)
