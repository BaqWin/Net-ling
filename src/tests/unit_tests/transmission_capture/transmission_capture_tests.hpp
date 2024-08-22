#include "transmission_capture.hpp"
#include <gtest/gtest.h>

class TransmissionCaptureTest : public ::testing::Test
{
  protected:
    std::unique_ptr<TransmissionCapture> capture;

    void SetUp() override
    {
        capture = std::make_unique<TransmissionCapture>();
    }
};
