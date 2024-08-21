#include "controller.hpp"

#include <iostream>

void Controller::init()
{
    transmissionCapture_ = std::make_shared<TransmissionCapture>();
    applyRules();
}

void Controller::applyRules(){
    RuleFactory factory;
    auto vec = factory.getRules("Test.txt");
    for(auto& p : vec){
        RuleType e = p.first;
        auto& v = p.second;

        std::visit([this, e](auto&& arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, std::string>) {
                if (e == RuleType::BERKELEY) {
                    transmissionCapture_->setBerkeleyRule(arg);
                }
            } else if constexpr (std::is_integral_v<T>) {
                if (e == RuleType::FILE_LENGTH) {
                    transmissionCapture_->setFileLength(arg);
                }
            }
        }, v);
    }
}

void Controller::start(const std::string& nic)
{
    std::thread captureThread([this, nic]() { transmissionCapture_->startCapture(nic); });
    captureThread.detach();

    int end = 0;
    while (true)
    {
        if (!packetCollections.empty())
        {
            FileLogger log(std::move(packetCollections.front()));
            packetCollections.erase(packetCollections.begin());
            end++;
        }
        std::this_thread::sleep_for(std::chrono::seconds(2));
        if (end == 10)
        {
            break;
        }
    }
}

void Controller::addToPacketCollections(std::vector<std::unique_ptr<pcpp::RawPacket>>&& newVector)
{
    packetCollections.push_back(std::move(newVector));
}

Controller& Controller::getInstance()
{
    static Controller instance;
    return instance;
}
