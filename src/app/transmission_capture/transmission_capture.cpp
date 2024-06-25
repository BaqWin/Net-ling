#include "transmission_capture.hpp"
#include "file_logger.hpp"

#include <iostream>

TransmissionCapture::TransmissionCapture() :
    activeBuffer(&buffer1), inactiveBuffer(&buffer2){}

TransmissionCapture& TransmissionCapture::getInstance(){
    static TransmissionCapture instance;
    return instance;
}

void TransmissionCapture::onPacketArrival(pcpp::RawPacket* packet, pcpp::PcapLiveDevice* dev, void* cookie){
    (void)dev;
    TransmissionCapture* captureInstance = static_cast<TransmissionCapture*>(cookie);
    std::lock_guard<std::mutex> lock(captureInstance->activeMtx);
    captureInstance->activeBuffer->push_back(new pcpp::RawPacket(*packet));
}

void TransmissionCapture::startCapture(const std::string& deviceIp) {
    dev = pcpp::PcapLiveDeviceList::getInstance().getPcapLiveDeviceByIp(deviceIp);
    capturing = true;
    if (dev == nullptr) {
        return;
    }
    if (!dev->open()) {
        return;
    }

    dev->startCapture(TransmissionCapture::onPacketArrival, this);
    std::shared_ptr<FileLogger> logger = std::make_shared<FileLogger>(*this, "output.pcap");

    int end = 0;
    while (capturing) {
        if (end == 50) {
            stopCapture();
        } else if (activeBuffer->size() >= 100) {
            swapBuffers();
            cv.notify_one();
            end++;
        }
    }

    logger->stop();
}

void TransmissionCapture::stopCapture() {
    capturing = false;
    if (dev) {
        dev->stopCapture();
        dev->close();
    }
    {
        std::lock_guard<std::mutex> lock(activeMtx);
        for (auto packet : *activeBuffer) {
            delete packet;
        }
        activeBuffer->clear();
    }
    {
        std::lock_guard<std::mutex> lock(inactiveMtx);
        for (auto packet : *inactiveBuffer) {
            delete packet;
        }
        inactiveBuffer->clear();
    }
    cv.notify_all();
}

void TransmissionCapture::swapBuffers(){
    std::unique_lock<std::mutex> lock1(activeMtx, std::defer_lock);
    std::unique_lock<std::mutex> lock2(inactiveMtx, std::defer_lock);
    std::lock(lock1, lock2);
    std::swap(activeBuffer, inactiveBuffer);
}

bool TransmissionCapture::isFinished() const{
    return !capturing;
}

std::mutex& TransmissionCapture::getInactiveMutex(){
    return inactiveMtx;
}

std::condition_variable& TransmissionCapture::getCV(){
    return cv;
}

std::vector<pcpp::RawPacket*>* TransmissionCapture::getInactiveBuffer(){
    return inactiveBuffer;
}
