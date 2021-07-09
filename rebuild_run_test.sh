#!/bin/bash

rm CMakeCache.txt
cmake .
make clean
make
./socketcan_wrapper_test
