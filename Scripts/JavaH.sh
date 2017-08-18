#!/bin/bash
exec /home/federico/Java/jdk1.8.0_144/bin/javah -d ../Cpp/NativeTest/ -jni -classpath ../Java/target/classes ocl.OCL
