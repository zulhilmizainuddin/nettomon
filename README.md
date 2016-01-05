# nettomon
C++ program for monitoring Linux and Android process network upload and download speed using libpcap.
Currently supports IPv4.

<img src="https://github.com/zulhilmizainuddin/nettomon/blob/master/nettomon.gif">

## Getting Started

###Linux

####Environment setup

Install the following dependencies:

    CMake v3.3
    g++ v4.9
    Boost v1.54
    libpcap v1.5.3-2
    
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
