#pragma once

#include "pcapplusplus/PcapLiveDeviceList.h"
#include "pcapplusplus/PcapLiveDevice.h"
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>

class FileLogger;

class TransmissionCapture{
        pcpp::PcapLiveDevice* dev;
        std::vector<pcpp::RawPacket*> buffer1{};
        std::vector<pcpp::RawPacket*> buffer2{};
        std::vector<pcpp::RawPacket*>* activeBuffer;
        std::vector<pcpp::RawPacket*>* inactiveBuffer;
        std::mutex activeMtx;
        std::mutex inactiveMtx;
        std::condition_variable cv;
        bool capturing;

        TransmissionCapture();
        void swapBuffers();
        void stopCapture();
        TransmissionCapture(const TransmissionCapture&) = delete;
        void operator=(const TransmissionCapture&) = delete;
    public:
        static TransmissionCapture& getInstance();
        static void onPacketArrival(pcpp::RawPacket* packet, pcpp::PcapLiveDevice* dev, void* cookie);
        void startCapture(const std::string& deviceIp);
        bool isFinished() const;
        std::mutex& getInactiveMutex();
        std::condition_variable& getCV();
        std::vector<pcpp::RawPacket*>* getInactiveBuffer();
};
