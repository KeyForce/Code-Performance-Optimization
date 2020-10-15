/*
 * CLion使用VS作为编译器 平台设置为AMD64
 * CMakeLists 添加find_package(CUDA) find_package(CUDA REQUIRED)
*/
#include <iostream>
#include <math.h>
#include "timer.h"
// 两个向量加法kernel，grid和block均为一维 只采用一个GPU
__global__
void add_one_cuda(int n, float *x, float *y)
{
    for (int i = 0; i < n; i++)
        y[i] = x[i] + y[i];
}

int main(void)
{
    int N = 1<<20;
    float *x, *y;

    // 申请device内存
    cudaMallocManaged(&x, N*sizeof(float));
    cudaMallocManaged(&y, N*sizeof(float));

    // 申请host内存
    for (int i = 0; i < N; i++) {
        x[i] = 1.0f;
        y[i] = 2.0f;
    }

    // 执行kernel
    add_one_cuda<<<1, 1>>>(N, x, y);

    // 保证device和host数据同步，这样不用手动将device得到的结果拷贝到host
    cudaDeviceSynchronize();

    // 计算误差
    float maxError = 0.0f;
    for (int i = 0; i < N; i++)
        maxError = fmax(maxError, fabs(y[i]-3.0f));
    std::cout << "Max error: " << maxError << std::endl;

    // 释放device内存
    cudaFree(x);
    cudaFree(y);

    return 0;
}