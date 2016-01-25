# nettomon [![Build Status](https://travis-ci.org/zulhilmizainuddin/nettomon.svg?branch=master)](https://travis-ci.org/zulhilmizainuddin/nettomon)
C++ program for monitoring Linux and Android process network upload and download speed using libpcap.
Currently supports IPv4.

<img src="https://github.com/zulhilmizainuddin/nettomon/blob/master/nettomon.gif">

##Linux

###Environment setup

Install the dependencies:

    $ sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test
    $ sudo apt-get -y update
    $ sudo apt-get -y install build-essential
    $ sudo apt-get -y install cmake
    $ sudo apt-get -y install g++-4.9
    $ sudo apt-get -y install libboost-all-dev
    $ sudo apt-get -y install libpcap-dev
    
Edit CMakeLists.txt if using different version of the dependencies.

###Get the source code

Clone the repository.

    $ git clone https://github.com/zulhilmizainuddin/nettomon.git nettomon

###Build

Run build.sh. The nettomon binary will be located under the build directory:

    $ ./build.sh
    
###Execute the program

Nettomon must be executed with superuser permission as it is using libpcap for the network monitoring.

Pass the pid of the process to be monitored:

    $ sudo ./nettomon <pid>

##Android

###Environment setup

Download and extract <a href="https://www.crystax.net/download/crystax-ndk-10.3.1-linux-x86_64.tar.xz">CrystaX NDK<a/> for Linux.

Add CrystaX NDK to the PATH variable in .bashrc.

    PATH=$PATH:~/crystax-ndk-10.3.1/
    
###Get the source code

Clone the repository into nettomon/jni directory.

    $ git clone https://github.com/zulhilmizainuddin/nettomon.git nettomon/jni
    
###Build

Build the source code. The binaries will be under the libs directory.

    $ ndk-build APP_ABI=armeabi-v7a
    
###Deploy

Deploy the binaries to the Android device under directory /data/local/tmp.

    $ adb push libs/armeabi-v7a/libcrystax.so /data/local/tmp
    $ adb push libs/armeabi-v7a/libgnustl_shared.so /data/local/tmp
    $ adb push libs/armeabi-v7a/nettomon /data/local/tmp
    
###Execute

Make the binaries executable.

    $ chmod 755 libcrystax.so libgnustl_shared.so nettomon
    
Run as superuser. Nettomon must be executed with superuser permission as it is using libpcap for the network monitoring. Make sure the device is rooted.

    $ su
    
Execute the program by passing it the pid of the process to be monitored.

    # LD_LIBRARY_PATH=/data/local/tmp ./nettomon <pid>
