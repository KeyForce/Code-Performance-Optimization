cmake_minimum_required(VERSION 3.17)
project(Code_Performance_Optimization CUDA)

find_package(CUDA)
find_package(CUDA REQUIRED)

set(CMAKE_CXX_STANDARD 11)

add_executable(Code_Performance_Optimization main.cu)

set_target_properties(
        Code_Performance_Optimization
        PROPERTIES
        CUDA_SEPARABLE_COMPILATION ON)