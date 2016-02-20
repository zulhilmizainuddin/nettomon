LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

NDK_TOOLCHAIN_VERSION := 5

LOCAL_MODULE    := nettomon
LOCAL_SRC_FILES :=\
        Duration.cpp\
        EthernetProcessor.cpp\
        InodeIpHelper.cpp\
        InputValidation.cpp\
        InternetLayerProcessorFactory.cpp\
        IPv4MappedIPv6.cpp\
        IPv4Processor.cpp\
        IPv6Processor.cpp\
        LinkLayerController.cpp\
        LinkLayerProcessorFactory.cpp\
        LinuxCookedProcessor.cpp\
        main.cpp\
        NetworkSpeedTimer.cpp\
        PcapDumper.cpp\
        ProcessId.cpp\
        ProcFd.cpp\
        ProcNet.cpp\
        ProcNetPublisher.cpp\
        ProcReadTimer.cpp\
        Sniffer.cpp

LOCAL_CFLAGS += -O3
#LOCAL_CFLAGS += -fopenmp
#LOCAL_LDFLAGS += -fopenmp
LOCAL_C_INCLUDES := $(LOCAL_PATH) $(LOCAL_PATH)/libpcap
LOCAL_STATIC_LIBRARIES := libpcap boost_system_static

include $(BUILD_EXECUTABLE)

include $(LOCAL_PATH)/libpcap/Android.mk

$(call import-module,boost/1.59.0)
