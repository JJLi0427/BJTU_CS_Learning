// cudaPi.cpp : Defines the entry point for the console application.
#include <stdio.h>
#include <cuda.h>
#include <math.h>
#include <tchar.h>
#define NUM_THREAD 1024
#define NUM_BLOCK 1
__global__ void cal_pi(double *sum, long long nbin, float step, long long nthreads, long long nblocks) {
    long long i;
    float x;
    long long idx = blockIdx.x*blockDim.x+threadIdx.x;
    for (i=idx; i< nbin; i+=nthreads*nblocks) {
        x = (i+0.5)*step;
        sum[idx] = sum[idx]+4.0/(1.+x*x);
    }
}
int _tmain(int argc, _TCHAR* argv[]) {
    long long tid;
    double pi = 0;
    long long num_steps = 100000000;
    float step = 1./(float)num_steps;
    long long size = NUM_THREAD*NUM_BLOCK*sizeof(double);
    clock_t before, after;
    double *sumHost, *sumDev;
    sumHost = (double *)malloc(size);
    cudaMalloc((void **)&sumDev, size);// Initialize array in device to 0
    cudaMemset(sumDev, 0, size);
    before = clock();// Do calculation on device
    printf("Before Compute \n\n");
    dim3 numBlocks(NUM_BLOCK,1,1);
    dim3 threadsPerBlock(NUM_THREAD,1,1);
    cal_pi <<<numBlocks, threadsPerBlock>>> (sumDev, (int)num_steps, step, NUM_THREAD, NUM_BLOCK); // call CUDA kernel
    printf("After Compute \n\n");// Retrieve result from device and store it in host array
    cudaMemcpy(sumHost, sumDev, size, cudaMemcpyDeviceToHost);
    printf("After Copy \n\n");
    for(tid=0; tid<NUM_THREAD*NUM_BLOCK; tid++) {
        pi = pi+sumHost[tid];
    }
    pi = pi*step;
    after = clock();
    printf("The value of PI is %15.12f\n",pi);
    printf("The time to calculate PI was %f seconds\n",((float)(after - before)/1000.0));
    free(sumHost);
    cudaFree(sumDev);
    return 0;
}