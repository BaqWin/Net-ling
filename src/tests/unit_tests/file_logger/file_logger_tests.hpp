#pragma once

#include "file_logger.hpp"
#include "gtest/gtest.h"

class FileLoggerTest : public ::testing::Test
{
  protected:
    std::string tempDir_ = "test_logs/";
    std::string tempFilePath_ = tempDir_ + "test_logs/test_capture.pcap";

    void SetUp() override
    {
        std::filesystem::remove_all(tempDir_);
        std::filesystem::create_directories(tempDir_);
    }

    void TearDown() override
    {
        std::filesystem::remove_all(tempDir_);
    }

    std::vector<std::unique_ptr<pcpp::RawPacket>> createTestPackets(size_t numPackets)
    {
        std::vector<std::unique_ptr<pcpp::RawPacket>> packets;
        packets.reserve(numPackets);

        for (size_t i = 0; i < numPackets; ++i)
        {
            timeval ts{};
            ts.tv_sec = 1616161616;
            std::vector<uint8_t> data(64, 0x01);

            auto packet = std::make_unique<pcpp::RawPacket>(data.data(), data.size(), ts, false);

            packets.push_back(std::move(packet));
        }
        return packets;
    }
};
