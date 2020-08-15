cmake_minimum_required(VERSION 3.17)
project(Code_Performance_Optimization)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -std=c++11 -mfma -O3 -Ofast -ffast-math -fopenmp")
#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_DEBUG} -O3")
add_executable(Code_Performance_Optimization main.cpp)