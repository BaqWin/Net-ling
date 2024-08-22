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
    std::vector<std::unique_ptr<pcpp::RawPacket>> buffer;
    std::thread thread;

    std::string generateUniqueFileName();
    void logPackets(const std::string& path);

  public:
    FileLogger(std::vector<std::unique_ptr<pcpp::RawPacket>>&& vec, const std::string& path);
    ~FileLogger();
};
