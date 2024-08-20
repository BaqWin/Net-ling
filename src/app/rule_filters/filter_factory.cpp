#include "filter_factory.hpp"

void FilterFactory::registerRule(const std::string& key, std::function<std::unique_ptr<FilterRule>()> func) {
            factoryMap_[key] = func;
        }

std::unique_ptr<FilterRule> FilterFactory::createFilter(const std::string& key) {
        auto it = factoryMap_.find(key);
        if (it != factoryMap_.end()) {
            return (it->second)();
        }
        return nullptr;
}
