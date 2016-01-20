LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

NDK_TOOLCHAIN_VERSION = 4.9

LOCAL_MODULE    := nettomon
LOCAL_SRC_FILES :=\
        main.cpp\
        ProcFd.cpp\
        ProcNet.cpp\
        InodeIpHelper.cpp\
        Sniffer.cpp\
        TcpProcessor.cpp\
        UdpProcessor.cpp\
        ProcNetPublisher.cpp\
        ProcNetObserver.cpp\
        ProcReadTimer.cpp\
        NetworkSpeedTimer.cpp

LOCAL_CFLAGS := -O3
LOCAL_C_INCLUDES := $(LOCAL_PATH) $(LOCAL_PATH)/libpcap
LOCAL_STATIC_LIBRARIES := libpcap boost_system_static

include $(BUILD_EXECUTABLE)

include $(LOCAL_PATH)/libpcap/Android.mk

$(call import-module,boost/1.59.0)
