# CUDA

CUDA is a general-purpose parallel computing platform and programming
model developed by NVIDIA to leverage the massive parallel processing
power of GPUs. It allows developers to use C++ and other programming
languages to solve complex computational problems more efficiently than
on CPUs. CUDA's scalable programming model uses abstractions like thread
group hierarchies, shared memories, and barrier synchronization to enable
fine-grained and coarse-grained parallelism. This model allows CUDA
programs to automatically scale across various GPU architectures,
from high-performance devices to mainstream GPUs, by adjusting the
number of multiprocessors and memory partitions.

## Using CUDA

This repository contains several CUDA examples demonstrating various concepts:

1. `vector_add.cu`: Basic vector addition kernel
2. `matrix_multiply.cu`: Matrix multiplication using shared memory
3. `reduction.cu`: Parallel reduction using shared memory
4. `stream_example.cu`: Using CUDA streams for concurrent execution
5. `unified_memory.cu`: Using Unified Memory

To compile and run these examples, use the provided Makefile:

```sh
make
./vector_add
./matrix_multiply
./reduction
./stream_example
./unified_memory
```

## Further Reading

- [CUDA Toolkit Documentation](https://docs.nvidia.com/cuda/index.html)
- [CUDA C++ Programming Guide](https://docs.nvidia.com/cuda/cuda-c-programming-guide/)
