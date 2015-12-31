cmake_minimum_required(VERSION 3.3)
project(nettomon)

set(CMAKE_CXX_COMPILER g++-4.9)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lpcap -pthread")

set(SOURCE_FILES main.cpp ProcFd.cpp ProcFd.h ProcNet.cpp ProcNet.h InodeIpHelper.cpp InodeIpHelper.h NetData.h Sniffer.cpp Sniffer.h PacketProcessor.h TcpProcessor.cpp TcpProcessor.h PacketPayload.h UdpProcessor.cpp UdpProcessor.h ProcNetPublisher.cpp ProcNetPublisher.h ProcNetObserver.cpp ProcNetObserver.h ProcReadTimer.cpp ProcReadTimer.h ProcReadTimerData.h)

find_path(PCAP_ROOT_DIR NAMES include/pcap.h)
find_path(PCAP_INCLUDE_DIR NAMES pcap.h HINTS ${PCAP_ROOT_DIR}/include)
find_library(PCAP_LIBRARY NAMES pcap HINTS ${PCAP_ROOT_DIR}/lib)

find_package(Boost 1.54.0 COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(nettomon ${SOURCE_FILES})

target_link_libraries(nettomon ${PCAP_LIBRARY} ${Boost_LIBRARIES})