#include "file_logger.hpp"

FileLogger::FileLogger(std::vector<std::unique_ptr<pcpp::RawPacket>>&& vec)
    : buffer(std::move(vec)), pcapWriter(generateUniqueFileName()), thread(&FileLogger::logPackets, this)
{
}

FileLogger::~FileLogger()
{
    if (thread.joinable())
    {
        thread.join();
    }
    pcapWriter.close();
}

void FileLogger::logPackets()
{
    pcapWriter.open();
    for (const auto& packet : buffer)
    {
        pcapWriter.writePacket(*packet);
    }
    buffer.clear();
}

std::string FileLogger::generateUniqueFileName()
{
    std::time_t now = std::time(nullptr);
    std::stringstream ss;
    ss << "capture_" << std::put_time(std::localtime(&now), "%Y%m%d_%H%M%S") << ".pcap";

    return ss.str();
}
