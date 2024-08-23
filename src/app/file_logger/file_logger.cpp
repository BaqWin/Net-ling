#include "file_logger.hpp"

#include <iostream>

FileLogger::FileLogger(std::vector<std::unique_ptr<pcpp::RawPacket>>&& vec, const std::string& path)
    : buffer_(std::move(vec))
{
    thread_ = std::thread(&FileLogger::logPackets, this, path);
}

FileLogger::~FileLogger()
{
    if (thread_.joinable())
    {
        thread_.join();
    }
}

void FileLogger::logPackets(const std::string& path)
{
    std::unordered_map<pcpp::LinkLayerType, std::unique_ptr<pcpp::PcapFileWriterDevice>> writerMap;

    if (!std::filesystem::exists(path))
    {
        std::filesystem::create_directories(path);
    }
    
    for (const auto& packet : buffer_)
{
    pcpp::LinkLayerType linkLayerType = packet->getLinkLayerType();

    if (writerMap.find(linkLayerType) == writerMap.end())
    {
        std::string fileName = path + generateUniqueFileName(linkLayerType);
        writerMap.emplace(linkLayerType, std::make_unique<pcpp::PcapFileWriterDevice>(fileName, linkLayerType));
    }
    
    writerMap[linkLayerType]->open();
    writerMap[linkLayerType]->writePacket(*packet);
}

    for (auto& writer : writerMap)
    {
        writer.second->close();
    }
}

std::string FileLogger::generateUniqueFileName(pcpp::LinkLayerType linkLayerType)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 100);
    std::time_t now = std::time(nullptr);
    std::stringstream ss;
    ss << "capture_" << linkLayerType << "_" << std::put_time(std::localtime(&now), "%Y%m%d_%H%M%S") << "_" << dist(gen) << ".pcap";

    return ss.str();
}

std::thread& FileLogger::getThread()
{
    return thread_;
}
