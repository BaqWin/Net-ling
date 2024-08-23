#pragma once

#include "controller.hpp"
#include "m_transmission_capture.hpp"
#include "gtest/gtest.h"
#include <regex>

class ControllerTest : public ::testing::Test
{
  protected:
    Controller* controller;
    std::shared_ptr<MockTransmissionCapture> mockCapture;
    std::string filePath = "RuleList.txt";
    std::string newDir_ = "test_logs/";

    void SetUp() override
    {
        controller = &Controller::getInstance();
        mockCapture = std::make_shared<MockTransmissionCapture>();
        controller->setSubDirectory(newDir_);

        controller->setTransmissionCapture(mockCapture);
    }

    void TearDown() override
    {
    }

    void modifyFileLengthInRuleList(const std::regex& toFind, const std::string& replacement)
    {
        std::ifstream inFile(filePath);

        std::stringstream buffer;
        buffer << inFile.rdbuf();
        std::string fileContent = buffer.str();

        inFile.close();

        fileContent = std::regex_replace(fileContent, toFind, replacement);

        std::ofstream outFile(filePath);
        outFile << fileContent;
        outFile.close();
    }
};
