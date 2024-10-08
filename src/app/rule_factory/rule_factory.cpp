#include "rule_factory.hpp"

std::vector<std::pair<RuleType, Variant>> RuleFactory::getRules(const std::string& filePath)
{
    std::vector<std::pair<RuleType, Variant>> rules;
    std::ifstream file(filePath);

    if (file.is_open())
    {
        std::string line;

        while (std::getline(file, line))
        {
            std::stringstream ss(line);
            std::string key, value;

            if (std::getline(ss, key, ':'))
            {
                if (std::getline(ss, value))
                {
                    std::stringstream valueStream(value);
                    int number;

                    if (valueStream >> number && valueStream.eof())
                    {
                        rules.push_back(std::make_pair(getRuleType(key), number));
                    }
                    else
                    {
                        rules.push_back(std::make_pair(getRuleType(key), value));
                    }
                }
            }
        }
        file.close();
    }
    return rules;
}
