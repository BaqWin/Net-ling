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
    std::vector<std::vector<std::unique_ptr<pcpp::RawPacket>>> packetCollections_;
    bool capturing_ = true;
    std::string outputSubDirectory_ = "pcap_files/";
    std::string ruleFile_ = "RuleList.txt";

    Controller(const Controller&) = delete;
    Controller& operator=(const Controller&) = delete;

  public:
    void init();
    void addToPacketCollections(std::vector<std::unique_ptr<pcpp::RawPacket>>&& newVector);
    void switchCapture();
    void setTransmissionCapture(const std::shared_ptr<TransmissionCapture>& transmissionCapture_);
    void applyRules();
    void start();
    void setOutputSubDirectory(const std::string& dir);
    void setRuleFilePath(const std::string& name);

    static Controller& getInstance();
};