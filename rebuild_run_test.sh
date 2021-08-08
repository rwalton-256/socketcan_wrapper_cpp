#!/bin/bash

rm CMakeCache.txt
cmake -D CMAKE_CXX_COMPILER=g++-4.8 -D CMAKE_C_COMPILER=gcc-4.8 .
make clean
make
./socketcan_wrapper_test
