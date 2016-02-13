cmake_minimum_required(VERSION 2.8)
project(nettomon)

set(CMAKE_C_COMPILER gcc-5)
set(CMAKE_CXX_COMPILER g++-5)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lpcap -pthread -fopenmp -O3")

set(SOURCE_FILES
        Duration.cpp Duration.h
        EthernetProcessor.cpp EthernetProcessor.h
        InodeIpHelper.cpp InodeIpHelper.h
        InputValidation.cpp InputValidation.h
        InternetLayerProcessor.h
        InternetLayerProcessorFactory.cpp InternetLayerProcessorFactory.h
        IPv4Processor.cpp IPv4Processor.h
        IPv6Processor.cpp IPv6Processor.h
        LinkLayerController.cpp LinkLayerController.h
        LinkLayerProcessor.h
        LinkLayerProcessorFactory.cpp LinkLayerProcessorFactory.h
        LinuxCookedProcessor.cpp LinuxCookedProcessor.h
        main.cpp
        NetData.h
        NetworkSpeedTimer.cpp NetworkSpeedTimer.h
        PacketPayload.h
        ProcessId.cpp ProcessId.h
        ProcFd.cpp ProcFd.h
        ProcNet.cpp ProcNet.h
        ProcNetObserver.h
        ProcNetPublisher.cpp ProcNetPublisher.h
        ProcReadTimer.cpp ProcReadTimer.h
        sll.h
        Sniffer.cpp Sniffer.h)

find_path(PCAP_ROOT_DIR NAMES include/pcap.h)
find_path(PCAP_INCLUDE_DIR NAMES pcap.h HINTS ${PCAP_ROOT_DIR}/include)
find_library(PCAP_LIBRARY NAMES pcap HINTS ${PCAP_ROOT_DIR}/lib)

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost COMPONENTS system REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(nettomon ${SOURCE_FILES})

target_link_libraries(nettomon ${PCAP_LIBRARY} ${Boost_LIBRARIES})