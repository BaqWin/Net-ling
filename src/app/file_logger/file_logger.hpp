#pragma once

#include "pcapplusplus/PcapFileDevice.h"
#include <ctime>
#include <filesystem>
#include <iomanip>
#include <random>
#include <sstream>
#include <string>
#include <thread>
#include <unordered_map>
#include <mutex>

class FileLogger
{
    std::vector<std::unique_ptr<pcpp::RawPacket>> buffer_;
    std::string path_;

  public:
    FileLogger(std::vector<std::unique_ptr<pcpp::RawPacket>>&& vec, const std::string& path);
    void logPackets();
    std::string generateUniqueFileName(pcpp::LinkLayerType linkLayerType);
    ~FileLogger();
};
