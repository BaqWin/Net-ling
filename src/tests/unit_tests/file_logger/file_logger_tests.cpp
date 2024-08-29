#include "file_logger_tests.hpp"

namespace
{

TEST_F(FileLoggerTest, PacketLogTest)
{
    auto packets = createTestPackets(5);

    FileLogger logger(std::move(packets), tempDir_);
    logger.logPackets();

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    bool fileCreated = false;
    for (const auto& entry : std::filesystem::directory_iterator(tempDir_))
    {
        if (entry.path().extension() == ".pcap")
        {
            fileCreated = true;
            tempFilePath_ = entry.path();
            break;
        }
    }
    ASSERT_TRUE(fileCreated);

    std::ifstream pcapFile(tempFilePath_, std::ios::binary | std::ios::ate);
    ASSERT_TRUE(pcapFile.is_open());
    ASSERT_GT(pcapFile.tellg(), 0);
    pcapFile.close();
}

TEST_F(FileLoggerTest, UniqueFileNameTest)
{
    FileLogger logger({}, tempDir_);

    std::string fileName1 = logger.generateUniqueFileName(pcpp::LINKTYPE_ETHERNET);
    std::string fileName2 = logger.generateUniqueFileName(pcpp::LINKTYPE_NULL);

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    ASSERT_NE(fileName1, fileName2);
}

} // namespace
