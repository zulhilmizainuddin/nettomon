#ifndef NETTOMON_PAYLOAD_H
#define NETTOMON_PAYLOAD_H

#include <mutex>

using namespace std;

class PacketPayload {
private:
    volatile unsigned long uploadedBytes;
    volatile unsigned long downloadedBytes;

    mutex uploadMutex;
    mutex downloadMutex;

public:
    static PacketPayload & getInstance() {
        static PacketPayload instance;
        return instance;
    }

    void resetUploadedBytes() {
        uploadMutex.lock();
        PacketPayload::uploadedBytes = 0;
        uploadMutex.unlock();
    }

    unsigned long getUploadedBytes() {
        uploadMutex.lock();
        auto uploadedBytesTemp = uploadedBytes;
        uploadMutex.unlock();

        return uploadedBytesTemp;
    }

    void addUploadedBytes(unsigned long uploadedBytes) {
        uploadMutex.lock();
        PacketPayload::uploadedBytes += uploadedBytes;
        uploadMutex.unlock();
    }

    void resetDownloadedBytes() {
        downloadMutex.lock();
        PacketPayload::downloadedBytes = 0;
        downloadMutex.unlock();
    }

    unsigned long getDownloadedBytes() {
        downloadMutex.lock();
        auto downloadedBytesTemp = downloadedBytes;
        downloadMutex.unlock();

        return downloadedBytesTemp;
    }

    void addDownloadedBytes(unsigned long downloadedBytes) {
        downloadMutex.lock();
        PacketPayload::downloadedBytes += downloadedBytes;
        downloadMutex.unlock();
    }

private:
    PacketPayload() { }
    PacketPayload(PacketPayload &);
    void operator=(PacketPayload const&);
};


#endif //NETTOMON_PAYLOAD_H
