#pragma once

#include "file_logger.hpp"
#include "transmission_capture.hpp"
#include "rule_factory.hpp"
#include "rule_type.hpp"

#include <memory>
#include <string>
#include <map>
#include <functional>

class Controller
{
    Controller() = default;
    std::shared_ptr<TransmissionCapture> transmissionCapture_;
    std::vector<std::vector<std::unique_ptr<pcpp::RawPacket>>> packetCollections;

    void applyRules();

  public:
    void init();
    void start(const std::string& nic);
    void addToPacketCollections(std::vector<std::unique_ptr<pcpp::RawPacket>>&& newVector);
    static Controller& getInstance();

    Controller(const Controller&) = delete;
    Controller& operator=(const Controller&) = delete;
};