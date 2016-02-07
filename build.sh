#!/bin/bash

if [[ $# -ne 1 ]]; then
    echo "usage: ./build.sh <number of parallel build worker>"
    exit 1
fi

if [[ -x /usr/bin/gcc-5 ]] && [[ -x /usr/bin/g++-5 ]]; then
    export CC=/usr/bin/gcc-5
    export CXX=/usr/bin/g++-5
fi

if [[ ! -d build ]]; then
    mkdir -v build
fi

cd build
cmake ..
cd ..
cmake --build build --target nettomon -- -j $1
