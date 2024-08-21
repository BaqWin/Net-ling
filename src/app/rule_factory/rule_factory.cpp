#include "rule_factory.hpp"

std::vector<std::pair<RuleType, Variant>> RuleFactory::getRules(const std::string& filePath){
    std::vector<std::pair<RuleType, Variant>> rules;
    std::ifstream file(filePath);

    if(file.is_open()){
        std::string line;

        while (std::getline(file, line)){
            std::stringstream ss(line);
            std::string key, strValue;
            int number;

            if(std::getline(ss, key, ':')){
                if(ss >> number){
                    rules.push_back(std::make_pair(getRuleType(key), number));
                }else{
                    ss.clear();
                    if(std::getline(ss, strValue)){
                        rules.push_back(std::make_pair(getRuleType(key), strValue));
                    }
                }
            }
        }
        file.close();
    }
    return rules;
}
