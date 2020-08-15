//
// Created by KeyForce on 2019/8/14.
//

#ifndef CODE_PERFORMANCE_OPTIMIZATION_SEARCH_BEST_H
#define CODE_PERFORMANCE_OPTIMIZATION_SEARCH_BEST_H

#include <assert.h>
#include <cmath>
#include <float.h>
#include <climits>
#include "cosine_similarity.h"


template<typename T>
int SearchBest(const T *const pVecA,  // 待搜索的单个特征向量首地址
               const int lenA,        // 待搜索特征向量长度
               const T *const pVecDB, // 人脸数据库首地址
               const int lenDB)       // 人脸数据库长度 (人脸个数 x 单个特征维数)
{
    assert(lenDB % lenA == 0);
    const int featsize = lenA;
    const int facenum = lenDB / lenA;

    int best_index = -INT_MAX;
    T best_similarity = -FLT_MAX;
//采用OpenMP实现多线程
#pragma omp parallel for num_threads(4)
    for (int i = 0; i < facenum; i++) {
        // 普通C++代码实现的余弦相似度计算
        T similarity = Cosine_similarity(pVecA, pVecDB + i * featsize, featsize);

        if (similarity > best_similarity) {
            best_similarity = similarity;
            best_index = i;
        }
    }

    return best_index;
}

#endif //CODE_PERFORMANCE_OPTIMIZATION_SEARCH_BEST_H
