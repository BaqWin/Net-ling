#pragma once

#include "pcapplusplus/PcapLiveDevice.h"
#include "pcapplusplus/PcapLiveDeviceList.h"
#include <algorithm>
#include <condition_variable>
#include <future>
#include <mutex>
#include <pcap/pcap.h>
#include <string>
#include <thread>
#include <vector>

class TransmissionCapture
{
    std::vector<std::unique_ptr<pcpp::RawPacket>> buffer_;
    std::mutex bufferMutex_;
    std::condition_variable cv_;
    pcpp::PcapLiveDevice* pcapDevice_ = nullptr;
    std::string berkeleyRule_;
    std::size_t fileLength_ = 50;
    std::string nic_;
    bool infinite_ = false;
    std::size_t loopAmount_ = 1;
    std::size_t timeout_ = 10;

    static bool onPacketArrivesBlockingMode(pcpp::RawPacket* packet, pcpp::PcapLiveDevice* dev, void* cookie);
    std::string getActiveNIC();

  public:
    TransmissionCapture() = default;
    virtual void startCapture();
    virtual void setBerkeleyRule(const std::string& rule);
    virtual void setFileLength(std::size_t rule);
    virtual void setNIC(std::string& rule);
    virtual void setFileAmount(std::size_t amount);
    virtual void setFileAmount(std::string& rule);
    void setTimeoutAmount(std::size_t amount);
    virtual ~TransmissionCapture() = default;
    std::string getBerkeleyRule() const;
    std::size_t getFileLength() const;
    std::string getNIC() const;
    std::size_t getTimeoutLength() const;
    bool isInfinite() const;
    std::size_t getLoopAmount() const;
};
