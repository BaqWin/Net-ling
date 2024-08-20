#pragma once

#include <string>

#include "filter_rule.hpp"

class BerkleyRule : public FilterRule{
        std::string rule_;
    public:
        BerkleyRule(const std::string& key);
        Variant apply() override;
        ~BerkleyRule() = default;
};
