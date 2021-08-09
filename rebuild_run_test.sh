#!/bin/bash

rm CMakeCache.txt
cmake -D CMAKE_CXX_COMPILER=g++ -D CMAKE_C_COMPILER=gcc .
make clean
make
./socketcan_wrapper_test
