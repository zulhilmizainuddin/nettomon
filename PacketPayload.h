#ifndef NETTOMON_PAYLOAD_H
#define NETTOMON_PAYLOAD_H


class PacketPayload {
private:
    unsigned long uploadedBytes;
    unsigned long downloadedBytes;

public:
    static PacketPayload & getInstance() {
        static PacketPayload instance;
        return instance;
    }

    void resetUploadedBytes() {
        PacketPayload::uploadedBytes = 0;
    }

    unsigned long getUploadedBytes() const {
        return uploadedBytes;
    }

    void addUploadedBytes(unsigned long uploadedBytes) {
        PacketPayload::uploadedBytes += uploadedBytes;
    }

    void resetDownloadedBytes() {
        PacketPayload::downloadedBytes = 0;
    }

    unsigned long getDownloadedBytes() const {
        return downloadedBytes;
    }

    void addDownloadedBytes(unsigned long downloadedBytes) {
        PacketPayload::downloadedBytes += downloadedBytes;
    }

private:
    PacketPayload() { }
    PacketPayload(PacketPayload &);
    void operator=(PacketPayload const&);
};


#endif //NETTOMON_PAYLOAD_H
