#include "berkeley_rule.hpp"

BerkleyRule::BerkleyRule(const std::string& key) : rule_(key){}

Variant BerkleyRule::apply(){
    return rule_;
}
