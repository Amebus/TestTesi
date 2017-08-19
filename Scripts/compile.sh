#!/bin/bash

echo "compiling..."
g++ -fPIC -shared ../Cpp/NativeTest/OCL.cpp -o ../Cpp/Out/libNativeTest.so -lOpenCL -I/home/federico/Java/jdk1.8.0_144/include -I/home/federico/Java/jdk1.8.0_144/include/linux
echo "done"

echo "execstack..."
sudo execstack -c ../Cpp/Out/libNativeTest.so
echo "done"
