// add.cu
#include <iostream>
#include <math.h>
// Kernel function to add the elements of two arrays
// __global__ 变量声明符，作用是将add函数变成可以在GPU上运行的函数
// __global__ 函数被称为kernel，
// 在 GPU 上运行的代码通常称为设备代码（device code），而在 CPU 上运行的代码是主机代码（host code）。
__global__ 
void add(int n, float *x, float *y)
{
    for (int i = 0; i < n; i++)
    y[i] = x[i] + y[i];
}

int main(void)
{
    int N = 1<<25;
    float *x, *y;

    // Allocate Unified Memory – accessible from CPU or GPU
    // 内存分配，在GPU或者CPU上统一分配内存
    cudaMallocManaged(&x, N*sizeof(float));
    cudaMallocManaged(&y, N*sizeof(float));

    // initialize x and y arrays on the host
    for (int i = 0; i < N; i++) {
    x[i] = 1.0f;
    y[i] = 2.0f;
}

    // Run kernel on 1M elements on the GPU
    // execution configuration, 执行配置
    add<<<1, 1>>>(N, x, y);

    // Wait for GPU to finish before accessing on host
    // CPU需要等待cuda上的代码运行完毕，才能对数据进行读取
    cudaDeviceSynchronize();

    // Check for errors (all values should be 3.0f)
    float maxError = 0.0f;
    for (int i = 0; i < N; i++)
    maxError = fmax(maxError, fabs(y[i]-3.0f));
    std::cout << "Max error: " << maxError << std::endl;

    // Free memory
    cudaFree(x);
    cudaFree(y);

    return 0;
}