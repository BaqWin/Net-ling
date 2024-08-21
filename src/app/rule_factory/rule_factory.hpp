#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <variant>
#include <vector>

#include "rule_type.hpp"

using Variant = std::variant<int, std::string>;

class RuleFactory
{
  public:
    RuleFactory() = default;
    std::vector<std::pair<RuleType, Variant>> getRules(const std::string& filePath);
};
