# nettomon [![Build Status](https://travis-ci.org/zulhilmizainuddin/nettomon.svg?branch=master)](https://travis-ci.org/zulhilmizainuddin/nettomon)
C++ program for monitoring and capturing Linux and Android process specific network usage using libpcap.

* Supported link layer:
    * Ethernet
    * Linux cooked/SLL
* Supported internet layer:
    * IPv4
    * IPv6
* Supported transport layer:
    * TCP
    * UDP
* Monitor process specific upload and download speed.
* Capture process specific packets to pcap file.

<img src="https://github.com/zulhilmizainuddin/nettomon/blob/master/nettomon.gif">

##Usage

View help by executing:

    nettomon -h

    Usage: nettomon <pid | process name> [OPTIONS...]
    
      -l            list result line by line
      -d n          execute program for n number of seconds
      -w file       dump captured packets into pcap format at file location

##Linux

###Environment setup

Install the dependencies.

    sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test
    sudo apt-get -y update
    sudo apt-get -y install cmake
    sudo apt-get -y install g++-5
    sudo apt-get -y install libboost-all-dev
    sudo apt-get -y install libpcap-dev
    
Edit CMakeLists.txt if using different version of the dependencies.

###Get the source code

Clone the repository.

    git clone https://github.com/zulhilmizainuddin/nettomon.git nettomon

###Build

Run build.sh. The nettomon binary will be located under the build directory.

    ./build.sh <number of build workers>
    
###Execute the program

Nettomon must be executed with superuser permission as it is using libpcap for the network monitoring.

Pass the pid of the process to be monitored.

    sudo ./build/nettomon <pid or process name>

##Android

###Environment setup

Download and extract <a href="https://www.crystax.net/download/crystax-ndk-10.3.1-linux-x86_64.tar.xz">CrystaX NDK<a/> for Linux.

Add CrystaX NDK to the PATH variable in .bashrc.

    PATH=$PATH:~/crystax-ndk-10.3.1/
    
###Get the source code

Clone the repository into nettomon/jni directory.

    git clone https://github.com/zulhilmizainuddin/nettomon.git nettomon/jni
    
###Build

Build the source code. The binaries will be under the libs directory.

    ndk-build
    
###Deploy

Deploy the binaries to the Android device under directory /data/local/tmp.

    adb push libs/armeabi-v7a/libcrystax.so /data/local/tmp
    adb push libs/armeabi-v7a/libgnustl_shared.so /data/local/tmp
    adb push libs/armeabi-v7a/nettomon /data/local/tmp
    
###Execute

Make the binaries executable.

    adb shell chmod 755 /data/local/tmp/libcrystax.so /data/local/tmp/libgnustl_shared.so /data/local/tmp/nettomon
    
Nettomon must be executed with superuser permission as it is using libpcap for the network monitoring. **Make sure the device is rooted.**

Execute the program by passing it the pid of the process to be monitored.

    adb shell su -c LD_LIBRARY_PATH=/data/local/tmp ./data/local/tmp/nettomon <pid or process name>
