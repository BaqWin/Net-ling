#pragma once

#include "pcapplusplus/PcapLiveDeviceList.h"
#include "pcapplusplus/PcapLiveDevice.h"
#include <vector>
#include <thread>
#include <mutex>
#include <future>
#include <iostream>

class TransmissionCapture{
        std::vector<std::unique_ptr<pcpp::RawPacket>> buffer;
        std::mutex bufferMutex;

        static void onPacketArrival(pcpp::RawPacket* packet, pcpp::PcapLiveDevice* dev, void* cookie);

    public:
        TransmissionCapture() = default;
        void startCapture(const std::string& nic);
};
