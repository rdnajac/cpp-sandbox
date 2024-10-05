#include <cuda_runtime.h>
#include <stdio.h>

#define BLOCK_SIZE 256

__global__ void reduce(float *input, float *output, int n) {
    __shared__ float sdata[BLOCK_SIZE];

    unsigned int tid = threadIdx.x;
    unsigned int i = blockIdx.x * blockDim.x + threadIdx.x;

    sdata[tid] = (i < n) ? input[i] : 0;
    __syncthreads();

    for (unsigned int s = blockDim.x / 2; s > 0; s >>= 1) {
        if (tid < s) {
            sdata[tid] += sdata[tid + s];
        }
        __syncthreads();
    }

    if (tid == 0) output[blockIdx.x] = sdata[0];
}

int main() {
    int n = 1000000;
    size_t size = n * sizeof(float);

    float *h_input = (float *)malloc(size);
    for (int i = 0; i < n; i++) {
        h_input[i] = rand() / (float)RAND_MAX;
    }

    float *d_input, *d_output;
    cudaMalloc(&d_input, size);
    cudaMalloc(&d_output, (n / BLOCK_SIZE) * sizeof(float));

    cudaMemcpy(d_input, h_input, size, cudaMemcpyHostToDevice);

    int numBlocks = (n + BLOCK_SIZE - 1) / BLOCK_SIZE;
    reduce<<<numBlocks, BLOCK_SIZE>>>(d_input, d_output, n);

    float *h_output = (float *)malloc(numBlocks * sizeof(float));
    cudaMemcpy(h_output, d_output, numBlocks * sizeof(float), cudaMemcpyDeviceToHost);

    float sum = 0;
    for (int i = 0; i < numBlocks; i++) {
        sum += h_output[i];
    }

    printf("Sum: %f\n", sum);

    free(h_input); free(h_output);
    cudaFree(d_input); cudaFree(d_output);

    return 0;
}
