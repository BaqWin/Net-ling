#include "file_logger.hpp"

FileLogger::FileLogger(std::vector<std::unique_ptr<pcpp::RawPacket>>&& vec, const std::string& path)
    : buffer(std::move(vec))
{
    thread = std::thread(&FileLogger::logPackets, this, path);
}

FileLogger::~FileLogger()
{
    if (thread.joinable())
    {
        thread.join();
    }
}

void FileLogger::logPackets(const std::string& path)
{
    if (!std::filesystem::exists(path))
    {
        std::filesystem::create_directories(path);
    }
    pcpp::PcapFileWriterDevice pcapWriter(path + generateUniqueFileName());
    pcapWriter.open();
    for (const auto& packet : buffer)
    {
        pcapWriter.writePacket(*packet);
    }
}

std::string FileLogger::generateUniqueFileName()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 100);
    std::time_t now = std::time(nullptr);
    std::stringstream ss;
    ss << "capture_" << std::put_time(std::localtime(&now), "%Y%m%d_%H%M%S") << "_" << dist(gen) << ".pcap";

    return ss.str();
}
