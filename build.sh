#!/bin/bash

if [[ $# -ne 1 ]]; then
    echo "usage: ./build.sh <number of parallel build worker>"
    exit 1
fi

if [[ ! -d build ]]; then
    mkdir -v build
fi

cd build
cmake ..
cd ..
cmake --build build --target nettomon -- -j $1
