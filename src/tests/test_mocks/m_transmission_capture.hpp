#pragma once

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "transmission_capture.hpp"

class MockTransmissionCapture : public TransmissionCapture
{
  public:
    MOCK_METHOD(void, startCapture, (), (override));
    MOCK_METHOD(void, setBerkeleyRule, (const std::string&), (override));
    MOCK_METHOD(void, setNIC, (std::string&), (override));
    MOCK_METHOD(void, setFileLength, (std::size_t), (override));
    MOCK_METHOD(void, setFileAmount, (std::size_t), (override));
};
