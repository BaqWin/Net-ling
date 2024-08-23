#pragma once

#include "pcapplusplus/PcapFileDevice.h"
#include <ctime>
#include <filesystem>
#include <iomanip>
#include <random>
#include <sstream>
#include <string>
#include <thread>

class FileLogger
{
    std::vector<std::unique_ptr<pcpp::RawPacket>> buffer_;
    std::thread thread_;

    void logPackets(const std::string& path);

  public:
    FileLogger(std::vector<std::unique_ptr<pcpp::RawPacket>>&& vec, const std::string& path);
    std::thread& getThread();
    std::string generateUniqueFileName(pcpp::LinkLayerType linkLayerType);
    ~FileLogger();
};
