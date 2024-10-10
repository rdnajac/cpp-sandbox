#include <cuda_runtime.h>
#include <stdio.h>

__global__ void increment(int *a, int N) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < N) {
        a[i]++;
    }
}

int main() {
    int N = 1000000;
    size_t size = N * sizeof(int);

    int *a;
    cudaMallocManaged(&a, size);

    for (int i = 0; i < N; i++) {
        a[i] = i;
    }

    int blockSize = 256;
    int numBlocks = (N + blockSize - 1) / blockSize;
    increment<<<numBlocks, blockSize>>>(a, N);

    cudaDeviceSynchronize();

    printf("First few elements after increment:\n");
    for (int i = 0; i < 10; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    cudaFree(a);

    return 0;
}
