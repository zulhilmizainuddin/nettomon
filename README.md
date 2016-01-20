# nettomon [![Build Status](https://travis-ci.org/zulhilmizainuddin/nettomon.svg?branch=master)](https://travis-ci.org/zulhilmizainuddin/nettomon)
C++ program for monitoring Linux and Android process network upload and download speed using libpcap.
Currently supports IPv4.

<img src="https://github.com/zulhilmizainuddin/nettomon/blob/master/nettomon.gif">

## Getting Started

###Linux

####Environment setup

Install the dependencies:

    sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test
    sudo apt-get -y update
    sudo apt-get -y install build-essential
    sudo apt-get -y install cmake
    sudo apt-get -y install g++-4.9
    sudo apt-get -y install libboost-all-dev
    sudo apt-get -y install libpcap-dev
    
Edit CMakeLists.txt if using different version of the dependencies.

####Build

Run build.sh. The nettomon binary will be located under the build directory:

    ./build.sh
    
####Execute the program

Nettomon must be executed with superuser permission as it is using libpcap for the network monitoring.

Pass the pid of the process to be monitored:

    sudo ./nettomon <pid>

###Android
TODO
