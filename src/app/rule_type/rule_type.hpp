#pragma once

#include <algorithm>
#include <cctype>
#include <string>

enum class RuleType{
    BERKELEY,
    FILE_LENGTH,
    UNKNOWN
};

RuleType getRuleType(std::string& type);
