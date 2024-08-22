#pragma once

#include "pcapplusplus/PcapLiveDevice.h"
#include "pcapplusplus/PcapLiveDeviceList.h"
#include <algorithm>
#include <condition_variable>
#include <future>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

class TransmissionCapture
{
    std::vector<std::unique_ptr<pcpp::RawPacket>> buffer;
    std::mutex bufferMutex;
    std::condition_variable cv;
    std::string berkeleyRule_;
    std::size_t fileLength_ = 500;
    std::string nic_;
    bool infinite_ = false;
    std::size_t loopAmount_ = 1;

    static void onPacketArrival(pcpp::RawPacket* packet, pcpp::PcapLiveDevice* dev, void* cookie);
    std::string getActiveNIC();

  public:
    TransmissionCapture() = default;
    virtual void startCapture();
    virtual void setBerkeleyRule(const std::string& rule);
    virtual void setFileLength(std::size_t rule);
    virtual void setNIC(const std::string& rule);
    virtual void setFileAmount(std::size_t amount);
    virtual void setFileAmount(std::string& rule);
    virtual ~TransmissionCapture() = default;
    std::string getBerkeleyRule() const;
    std::size_t getFileLength() const;
    std::string getNIC() const;
    bool isInfinite() const;
    std::size_t getLoopAmount() const;
};
