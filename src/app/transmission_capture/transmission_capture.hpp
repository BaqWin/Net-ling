#pragma once

#include "pcapplusplus/PcapLiveDevice.h"
#include "pcapplusplus/PcapLiveDeviceList.h"
#include <condition_variable>
#include <future>
#include <mutex>
#include <thread>
#include <vector>
#include <string>

class TransmissionCapture
{
    std::vector<std::unique_ptr<pcpp::RawPacket>> buffer;
    std::mutex bufferMutex;
    std::condition_variable cv;
    std::string berkeleyRule_;
    std::size_t fileLength_ = 500;

    static void onPacketArrival(pcpp::RawPacket* packet, pcpp::PcapLiveDevice* dev, void* cookie);

  public:
    TransmissionCapture() = default;
    void startCapture(const std::string& nic);
    void setBerkeleyRule(const std::string& rule);
    void setFileLength(std::size_t rule);
};
