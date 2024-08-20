#pragma once

#include <variant>

using Variant = std::variant<std::string, int>;

class FilterRule{
    public:
        virtual Variant apply() = 0;
        virtual ~FilterRule() = default;
};
