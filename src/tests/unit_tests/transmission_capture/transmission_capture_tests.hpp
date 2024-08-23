#include "transmission_capture.hpp"
#include <gtest/gtest.h>

class TransmissionCaptureTest : public ::testing::Test
{
  protected:
    std::unique_ptr<TransmissionCapture> capture_;

    void SetUp() override
    {
        capture_ = std::make_unique<TransmissionCapture>();
    }
};
