#include "transmission_capture_tests.hpp"

namespace
{

TEST_F(TransmissionCaptureTest, TestSetBerkeleyRule)
{
    std::string rule = "tcp port 80";
    capture->setBerkeleyRule(rule);

    EXPECT_EQ(capture->getBerkeleyRule(), rule);
}

TEST_F(TransmissionCaptureTest, TestSetFileLength)
{
    std::size_t fileLength = 100;
    capture->setFileLength(fileLength);

    EXPECT_EQ(capture->getFileLength(), fileLength);
}

TEST_F(TransmissionCaptureTest, TestSetNIC)
{
    std::string nic = "192.168.1.1";
    capture->setNIC(nic);

    EXPECT_EQ(capture->getNIC(), nic);
}

TEST_F(TransmissionCaptureTest, TestSetFileAmountInteger)
{
    std::size_t amount = 5;
    capture->setFileAmount(amount);

    EXPECT_EQ(capture->getLoopAmount(), amount);
}

TEST_F(TransmissionCaptureTest, TestSetFileAmountString)
{
    std::string rule = "infinite";
    capture->setFileAmount(rule);

    EXPECT_TRUE(capture->isInfinite());
}

} // namespace
