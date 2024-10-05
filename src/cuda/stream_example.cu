#include <cuda_runtime.h>
#include <stdio.h>

#define N 1000000
#define STREAMS 4

__global__ void vectorAdd(float *a, float *b, float *c, int n) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < n) {
        c[i] = a[i] + b[i];
    }
}

int main() {
    float *h_a, *h_b, *h_c;
    float *d_a, *d_b, *d_c;
    cudaStream_t streams[STREAMS];

    cudaMallocHost(&h_a, N * sizeof(float));
    cudaMallocHost(&h_b, N * sizeof(float));
    cudaMallocHost(&h_c, N * sizeof(float));

    cudaMalloc(&d_a, N * sizeof(float));
    cudaMalloc(&d_b, N * sizeof(float));
    cudaMalloc(&d_c, N * sizeof(float));

    for (int i = 0; i < N; i++) {
        h_a[i] = rand() / (float)RAND_MAX;
        h_b[i] = rand() / (float)RAND_MAX;
    }

    for (int i = 0; i < STREAMS; i++) {
        cudaStreamCreate(&streams[i]);
    }

    int streamSize = N / STREAMS;
    int blockSize = 256;
    int numBlocks = (streamSize + blockSize - 1) / blockSize;

    for (int i = 0; i < STREAMS; i++) {
        int offset = i * streamSize;
        cudaMemcpyAsync(&d_a[offset], &h_a[offset], streamSize * sizeof(float), cudaMemcpyHostToDevice, streams[i]);
        cudaMemcpyAsync(&d_b[offset], &h_b[offset], streamSize * sizeof(float), cudaMemcpyHostToDevice, streams[i]);
        vectorAdd<<<numBlocks, blockSize, 0, streams[i]>>>(&d_a[offset], &d_b[offset], &d_c[offset], streamSize);
        cudaMemcpyAsync(&h_c[offset], &d_c[offset], streamSize * sizeof(float), cudaMemcpyDeviceToHost, streams[i]);
    }

    cudaDeviceSynchronize();

    printf("First few elements of the result:\n");
    for (int i = 0; i < 10; i++) {
        printf("%f + %f = %f\n", h_a[i], h_b[i], h_c[i]);
    }

    for (int i = 0; i < STREAMS; i++) {
        cudaStreamDestroy(streams[i]);
    }

    cudaFreeHost(h_a); cudaFreeHost(h_b); cudaFreeHost(h_c);
    cudaFree(d_a); cudaFree(d_b); cudaFree(d_c);

    return 0;
}
