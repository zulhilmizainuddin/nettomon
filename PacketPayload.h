#ifndef NETTOMON_PAYLOAD_H
#define NETTOMON_PAYLOAD_H

#include <pthread.h>

class PacketPayload {
private:
    volatile unsigned long uploadedBytes;
    volatile unsigned long downloadedBytes;

    pthread_mutex_t uploadMutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_t downloadMutex = PTHREAD_MUTEX_INITIALIZER;

public:
    static PacketPayload & getInstance() {
        static PacketPayload instance;
        return instance;
    }

    void resetUploadedBytes() {
        pthread_mutex_lock(&uploadMutex);
        PacketPayload::uploadedBytes = 0;
        pthread_mutex_unlock(&uploadMutex);
    }

    unsigned long getUploadedBytes() {
        pthread_mutex_lock(&uploadMutex);
        auto uploadedBytesTemp = uploadedBytes;
        pthread_mutex_unlock(&uploadMutex);

        return uploadedBytesTemp;
    }

    void addUploadedBytes(unsigned long uploadedBytes) {
        pthread_mutex_lock(&uploadMutex);
        PacketPayload::uploadedBytes += uploadedBytes;
        pthread_mutex_unlock(&uploadMutex);
    }

    void resetDownloadedBytes() {
        pthread_mutex_lock(&downloadMutex);
        PacketPayload::downloadedBytes = 0;
        pthread_mutex_unlock(&downloadMutex);
    }

    unsigned long getDownloadedBytes() {
        pthread_mutex_lock(&downloadMutex);
        auto downloadedBytesTemp = downloadedBytes;
        pthread_mutex_unlock(&downloadMutex);

        return downloadedBytesTemp;
    }

    void addDownloadedBytes(unsigned long downloadedBytes) {
        pthread_mutex_lock(&downloadMutex);
        PacketPayload::downloadedBytes += downloadedBytes;
        pthread_mutex_unlock(&downloadMutex);
    }

private:
    PacketPayload() { }
    PacketPayload(PacketPayload &);
    void operator=(PacketPayload const&);
};


#endif //NETTOMON_PAYLOAD_H
