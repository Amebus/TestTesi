#!/bin/bash
exec g++ -fPIC -shared ../Cpp/NativeTest/OCL.cpp -o ../Cpp/Out/libNativeTest.so -lOpenCL -I/home/federico/Java/jdk1.8.0_144/include -I/home/federico/Java/jdk1.8.0_144/include/linux

exec sudo execstack -c ../Cpp/Out/libNativeTest.so
