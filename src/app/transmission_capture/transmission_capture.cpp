#include "transmission_capture.hpp"

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

void TransmissionCapture::startCapture(const std::string& deviceIp){
    dev = pcpp::PcapLiveDeviceList::getInstance().getPcapLiveDeviceByIp(deviceIp);
    capturing = true;
    if(dev == nullptr){
        return;
    }
    if(!dev->open()){
        return;
    }
    dev->startCapture(TransmissionCapture::onPacketArrival, this);
    std::cout << "started capture\n";

    while(capturing){
        if(activeBuffer->size() >= 100 && inactiveBuffer->size() >= 100){
            stopCapture();
        }else if(activeBuffer->size() >= 100){
            swapBuffers();
        }
    }
}

void TransmissionCapture::stopCapture() {
        capturing = false;
        dev->stopCapture();
        dev->close();
        std::cout << "Przechwycono active: " << activeBuffer->size() << " pakietow\n";
        std::cout << "Przechwycono inactive: " << inactiveBuffer->size() << " pakietow\n";
        for (auto packet : *activeBuffer) {
            delete packet;
        }
}

void TransmissionCapture::swapBuffers(){
    std::unique_lock<std::mutex> lock1(activeMtx, std::defer_lock);
    std::unique_lock<std::mutex> lock2(inactiveMtx, std::defer_lock);
    std::lock(lock1, lock2);
    std::swap(activeBuffer, inactiveBuffer);
}
