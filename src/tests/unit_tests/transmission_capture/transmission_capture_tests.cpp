#include "transmission_capture_tests.hpp"

namespace
{

TEST_F(TransmissionCaptureTest, SetBerkeleyRuleTest)
{
    std::string rule = "tcp port 80";
    capture_->setBerkeleyRule(rule);

    EXPECT_EQ(capture_->getBerkeleyRule(), rule);
}

TEST_F(TransmissionCaptureTest, SetFileLengthTest)
{
    std::size_t fileLength = 100;
    capture_->setFileLength(fileLength);

    EXPECT_EQ(capture_->getFileLength(), fileLength);
}

TEST_F(TransmissionCaptureTest, SetNICTest)
{
    std::string nic = "192.168.1.1";
    capture_->setNIC(nic);

    EXPECT_EQ(capture_->getNIC(), nic);
}

TEST_F(TransmissionCaptureTest, SetFileAmountIntegerTest)
{
    std::size_t amount = 5;
    capture_->setFileAmount(amount);

    EXPECT_EQ(capture_->getLoopAmount(), amount);
}

TEST_F(TransmissionCaptureTest, SetFileAmountStringTest)
{
    std::string rule = "infinite";
    capture_->setFileAmount(rule);

    EXPECT_TRUE(capture_->isInfinite());
}

TEST_F(TransmissionCaptureTest, SetTimeoutIntegerTest)
{
    std::size_t amount = 20;
    capture_->setTimeoutAmount(amount);

    EXPECT_EQ(capture_->getTimeoutLength(), amount);
}

} // namespace
