#include "transmission_capture.hpp"
#include "controller.hpp"

void TransmissionCapture::onPacketArrival(pcpp::RawPacket* packet, pcpp::PcapLiveDevice* dev, void* cookie){
    (void)dev;
    TransmissionCapture* captureInstance = static_cast<TransmissionCapture*>(cookie);
    std::lock_guard lock(captureInstance->bufferMutex);
    captureInstance->buffer.push_back(std::make_unique<pcpp::RawPacket>(*packet));
}

void TransmissionCapture::startCapture(const std::string& nic) {
    pcpp::PcapLiveDevice* dev = pcpp::PcapLiveDeviceList::getInstance().getPcapLiveDeviceByIp(nic);
    if (dev == nullptr) {
        return;
    }
    if (!dev->open()) {
        return;
    }

    dev->startCapture(TransmissionCapture::onPacketArrival, this);

    int end = 0;
    while (true) {
        if (end == 11) {
            break;
        } else if (buffer.size() >= 10) {
            std::lock_guard lock(bufferMutex);
            Controller::getInstance().addToPacketCollections(std::move(buffer));
            buffer.clear();
            end++;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    dev->stopCapture();
    dev->close();
}
