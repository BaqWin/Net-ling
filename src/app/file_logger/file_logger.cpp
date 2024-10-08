#include "file_logger.hpp"

FileLogger::FileLogger(std::vector<std::unique_ptr<pcpp::RawPacket>>&& vec, const std::string& path)
    : buffer_(std::move(vec)), path_(path)
{
}

FileLogger::~FileLogger()
{
}

void FileLogger::logPackets()
{
    std::unordered_map<pcpp::LinkLayerType, std::unique_ptr<pcpp::PcapFileWriterDevice>> writerMap;

    if (!std::filesystem::exists(path_))
    {
        std::filesystem::create_directories(path_);
    }

    for (const auto& packet : buffer_)
    {
        pcpp::LinkLayerType linkLayerType = packet->getLinkLayerType();

        if (writerMap.find(linkLayerType) == writerMap.end())
        {
            std::string fileName = path_ + generateUniqueFileName(linkLayerType);
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
    std::stringstream ss;
    ss << "capture_" << linkLayerType << "_" << dist(gen) << "_" << dist(gen) << ".pcap";

    return ss.str();
}
