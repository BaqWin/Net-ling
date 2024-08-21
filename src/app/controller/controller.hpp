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

    void applyRules();
    void start();

  public:
    void init();
    void addToPacketCollections(std::vector<std::unique_ptr<pcpp::RawPacket>>&& newVector);

    static Controller& getInstance();

    Controller(const Controller&) = delete;
    Controller& operator=(const Controller&) = delete;
};