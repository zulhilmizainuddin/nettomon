#!/bin/bash

if [[ ! -d build ]]; then
    mkdir -v build
fi
cd build
cmake ..
cd ..
cmake --build build --target nettomon
