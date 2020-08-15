//
// Created by KeyForce on 2019/8/14.
//

#ifndef CODE_PERFORMANCE_OPTIMIZATION_COSINE_SIMILARITY_H
#define CODE_PERFORMANCE_OPTIMIZATION_COSINE_SIMILARITY_H

#include <cmath>
#include <float.h>
#include <immintrin.h>

template<typename T>
T Cosine_similarity(const T *const vectorA, // 第一个特征向量的首地址
                    const T *const vectorB, // 第二个特征向量的首地址
                    const int len) // 特征向量长度(维数)
{
    T mult_add = 0.0f;
    T a_norm2 = 0.0f;
    T b_norm2 = 0.0f;

    for (int i = 0; i < len; i++) {
        const T ai = vectorA[i];
        const T bi = vectorB[i];
        mult_add += ai * bi;
        a_norm2 += ai * ai;
        b_norm2 += bi * bi;
    }

    // 避免除零错误，分母加上FLT_MIN
    const T similarity = mult_add / (sqrt(a_norm2 * b_norm2) + FLT_MIN);

    return similarity;
}

#endif //CODE_PERFORMANCE_OPTIMIZATION_COSINE_SIMILARITY_H
