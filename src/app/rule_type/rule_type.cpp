#include "rule_type.hpp"

RuleType getRuleType(std::string& type)
{
    std::transform(type.begin(), type.end(), type.begin(), ::toupper);

    if (type == "BERKELEY")
        return RuleType::BERKELEY;
    if (type == "FILE_LENGTH")
        return RuleType::FILE_LENGTH;
    if (type == "NIC")
        return RuleType::NIC;
    if (type == "LOOP_RULE")
        return RuleType::LOOP_RULE;
    return RuleType::UNKNOWN;
}
