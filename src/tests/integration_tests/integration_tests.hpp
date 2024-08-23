#pragma once

#include <gtest/gtest.h>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>
#include <future>
#include <cstdlib>
#include <filesystem>
#include "controller.hpp"
#include "test_utils.hpp"

class IntegrationTestFixture : public ::testing::Test{
    protected:
    std::string ruleFilePath_ = "it_rules.txt";
    std::string scriptPath_ = "../src/tests/test_utils/scripts/it_script.py";
    std::string tempDir_ = "it_output/";
    std::size_t timeout_duration_seconds = 5;

    void SetUp() override
    {
        Controller::getInstance().setOutputSubDirectory(tempDir_);
    }

    void TearDown() override
    {
        std::filesystem::remove_all(tempDir_);
        std::filesystem::remove_all(ruleFilePath_);
    }

    void setTestRuleFilePath(const std::string& path){
        ruleFilePath_ = path;
        std::ifstream file(ruleFilePath_);

        if (!file) {
            FAIL() << "File " << ruleFilePath_ << " not found.";
        }

        Controller::getInstance().setRuleFilePath(ruleFilePath_);
    }
};
