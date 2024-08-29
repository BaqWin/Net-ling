#pragma once

#include "controller.hpp"
#include "m_transmission_capture.hpp"
#include "test_utils.hpp"
#include "gtest/gtest.h"
#include <regex>

class ControllerTest : public ::testing::Test
{
  protected:
    Controller* controller_;
    std::shared_ptr<MockTransmissionCapture> mockCapture_;
    std::string filePath_ = "ut_rules.txt";
    std::string newDir_ = "test_logs/";

    void SetUp() override
    {
        createTempFile({"BERKELEY:udp", "FILE_LENGTH:5", "NIC:Auto", "LOOP_RULE:2"}, filePath_);
        controller_ = &Controller::getInstance();
        mockCapture_ = std::make_shared<MockTransmissionCapture>();
        controller_->setOutputSubDirectory(newDir_);

        controller_->setTransmissionCapture(mockCapture_);
    }

    void TearDown() override
    {
        std::filesystem::remove_all(filePath_);
    }

    void modifyFileLengthInRuleList(const std::regex& toFind, const std::string& replacement)
    {
        std::ifstream inFile(filePath_);

        std::stringstream buffer;
        buffer << inFile.rdbuf();
        std::string fileContent = buffer.str();

        inFile.close();

        fileContent = std::regex_replace(fileContent, toFind, replacement);

        std::ofstream outFile(filePath_);
        outFile << fileContent;
        outFile.close();
    }
};
