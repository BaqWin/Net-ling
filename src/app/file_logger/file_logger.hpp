#pragma once

#include <ctime>
#include <iomanip>
#include <random>
#include <sstream>
#include <thread>

#include "pcapplusplus/PcapFileDevice.h"

class FileLogger
{
    std::vector<std::unique_ptr<pcpp::RawPacket>> buffer;
    pcpp::PcapFileWriterDevice pcapWriter;
    std::thread thread;

    std::string generateUniqueFileName();

  public:
    FileLogger(std::vector<std::unique_ptr<pcpp::RawPacket>>&& vec);
    ~FileLogger();
    void logPackets();
};
