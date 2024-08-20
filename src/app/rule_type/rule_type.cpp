#include "rule_type.hpp"

RuleType getRuleType(std::string& type){
    std::transform(type.begin(), type.end(), type.begin(), ::toupper);

    if(type == "BERKELEY") return RuleType::BERKELEY;
    if(type == "FILE_LENGTH") return RuleType::FILE_LENGTH;
    return RuleType::UNKNOWN;
}
