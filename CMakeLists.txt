cmake_minimum_required(VERSION 3.3)
project(nettomon)

set(CMAKE_CXX_COMPILER g++-4.9)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp ProcFd.cpp ProcFd.h ProcNet.cpp ProcNet.h InodeIpHelper.cpp InodeIpHelper.h NetData.h)

add_executable(nettomon ${SOURCE_FILES})