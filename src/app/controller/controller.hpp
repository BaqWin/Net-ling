#pragma once

#include "file_logger.hpp"
#include "rule_factory.hpp"
#include "rule_type.hpp"
#include "transmission_capture.hpp"

#include <functional>
#include <map>
#include <memory>
#include <string>

class Controller
{
    Controller() = default;
    std::shared_ptr<TransmissionCapture> transmissionCapture_;
    std::vector<std::vector<std::unique_ptr<pcpp::RawPacket>>> packetCollections;
    bool capturing_ = true;
    std::string subDirectory_ = "pcap_files/";

    Controller(const Controller&) = delete;
    Controller& operator=(const Controller&) = delete;

  public:
    void init();
    void addToPacketCollections(std::vector<std::unique_ptr<pcpp::RawPacket>>&& newVector);
    void switchCapture();
    void setTransmissionCapture(const std::shared_ptr<TransmissionCapture>& transmissionCapture_);
    void applyRules();
    void start();

    static Controller& getInstance();
};