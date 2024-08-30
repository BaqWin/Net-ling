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
    if (type == "FILE_AMOUNT")
        return RuleType::FILE_AMOUNT;
    if (type == "TIMEOUT")
        return RuleType::TIMEOUT;
    return RuleType::UNKNOWN;
}
