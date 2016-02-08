LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

NDK_TOOLCHAIN_VERSION := 5

LOCAL_MODULE    := nettomon
LOCAL_SRC_FILES :=\
        Duration.cpp\
        EthernetProcessor.cpp\
        InodeIpHelper.cpp\
        InputValidation.cpp\
        IPv4Processor.cpp\
        IPv6Processor.cpp\
        LinkLayerController.cpp\
        LinuxCookedProcessor.cpp\
        main.cpp\
        NetworkSpeedTimer.cpp\
        ProcFd.cpp\
        ProcNet.cpp\
        ProcNetPublisher.cpp\
        ProcReadTimer.cpp\
        Sniffer.cpp

LOCAL_CFLAGS += -fopenmp -O3
LOCAL_LDFLAGS += -fopenmp
LOCAL_C_INCLUDES := $(LOCAL_PATH) $(LOCAL_PATH)/libpcap
LOCAL_STATIC_LIBRARIES := libpcap boost_system_static

include $(BUILD_EXECUTABLE)

include $(LOCAL_PATH)/libpcap/Android.mk

$(call import-module,boost/1.59.0)
