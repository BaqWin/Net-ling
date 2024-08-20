#pragma once

#include <string>

enum class RuleType{
    BERKELEY,
    FILE_LENGTH,
    UNKNOWN
};

RuleType getRuleType(std::string& type);
