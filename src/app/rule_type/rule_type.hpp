#pragma once

#include <algorithm>
#include <cctype>
#include <string>

enum class RuleType
{
    BERKELEY,
    FILE_LENGTH,
    NIC,
    LOOP_RULE,
    UNKNOWN
};

RuleType getRuleType(std::string& type);
