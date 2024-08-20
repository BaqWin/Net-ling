#pragma once

#include <map>
#include <string>
#include <memory>
#include <functional>

#include "filter_rule.hpp"

class FilterFactory{
        std::map<std::string, std::function<std::unique_ptr<FilterRule>()>> factoryMap_;

    public:
        void registerRule(const std::string& key, std::function<std::unique_ptr<FilterRule>()> func);
        std::unique_ptr<FilterRule> createFilter(const std::string& key);
};
