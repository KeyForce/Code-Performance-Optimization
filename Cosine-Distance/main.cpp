#include <iostream>
#include "timer.h"
#include "search_best.h"

#define FACENUM  (100000) // 100万张人脸

#define FEATSIZE (512) // 每个人脸特征向量 512维

// 修改数据精度
typedef float DType;
//typedef int DType;
//typedef double DType;

// Step 1, set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -std=c++11")
// Step 2, set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -std=c++11 -O3")
// Step 3, set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -std=c++11 -O3 -Ofast -ffast-math")
// Step 4, 浮点转定点

int main(int argc, char *argv[]) {
    // 定义当前脸的特征，并初始化
    DType vectorA[FEATSIZE];
    // 数据初始化
    for (int i = 0; i < FEATSIZE; i++) {
        vectorA[i] = static_cast<DType>(FACENUM / 2 * FEATSIZE + i) / (FACENUM * FEATSIZE);
    }

    // 当数字长度很大不能用下面的初始化方式
    // DType pDB[FACENUM * FEATSIZE];
    DType *pDB = nullptr;
    try {
        pDB = new DType[FACENUM * FEATSIZE];
    } catch (...) {
        cout << "out of memory\n";
        return -1;
    }
    // 数据初始化
    for (int i = 0; i < FACENUM; i++) {
        for (int j = 0; j < FEATSIZE; j++) {
            pDB[i * FEATSIZE + j] = static_cast<DType>(i * FEATSIZE + j) / (FACENUM * FEATSIZE);
        }
    }

    // 定义计数器并开始计时
    Timer t;

    int best_index = SearchBest(static_cast<DType *>(vectorA), FEATSIZE, pDB, FACENUM * FEATSIZE);

    // 打印结果
    cout << "Best Index: " << best_index << std::endl;
    cout << "Search Time: " << t.elapsed_micro() << "us" << std::endl;
    cout << "Single Cosine Similarity Time: " << t.elapsed_nano() / FACENUM << "ns" << std::endl;

    delete[] pDB;
    return 0;
}