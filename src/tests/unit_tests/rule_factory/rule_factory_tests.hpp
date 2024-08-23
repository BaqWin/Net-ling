#pragma once

#include "rule_factory.hpp"
#include "test_utils.hpp"
#include <gtest/gtest.h>

class RuleFactoryTest : public ::testing::Test
{
  protected:
    RuleFactory ruleFactory_;
    std::string filePath_ = "test_file.txt";

    void TearDown() override
    {
        std::filesystem::remove(filePath_);
    }
};
