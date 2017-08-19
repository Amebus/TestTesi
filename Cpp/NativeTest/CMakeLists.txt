cmake_minimum_required(VERSION 3.8)
project(NativeTest)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES library.cpp library.h OCL.cpp ocl_OCL.h)
add_library(NativeTest SHARED ${SOURCE_FILES})