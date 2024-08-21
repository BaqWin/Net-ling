#pragma once

#include <vector>
#include <utility>
#include <variant>
#include <string>
#include <fstream>
#include <sstream>

#include "rule_type.hpp"

using Variant = std::variant<int, std::string>;

class RuleFactory{
    public:
        RuleFactory() = default;
        std::vector<std::pair<RuleType, Variant>> getRules(const std::string& filePath);
};
