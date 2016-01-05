#!/bin/bash

mkdir -v build
cd build
cmake ..
cd ..
cmake --build build --target nettomon