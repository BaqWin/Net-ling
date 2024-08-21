#include "controller.hpp"

void Controller::init()
{
    transmissionCapture_ = std::make_shared<TransmissionCapture>();
    applyRules();
    start();
}

void Controller::applyRules()
{
    RuleFactory factory;
    auto vec = factory.getRules("Test.txt");
    for (auto& p : vec)
    {
        RuleType e = p.first;
        auto& v = p.second;

        std::visit(
            [this, e](auto&& arg) {
                using T = std::decay_t<decltype(arg)>;
                if constexpr (std::is_same_v<T, std::string>)
                {
                    if (e == RuleType::BERKELEY)
                    {
                        transmissionCapture_->setBerkeleyRule(arg);
                    }
                    else if (e == RuleType::NIC)
                    {
                        transmissionCapture_->setNIC(arg);
                    }
                    else if (e == RuleType::LOOP_RULE)
                    {
                        transmissionCapture_->setFileAmount(arg);
                    }
                }
                else if constexpr (std::is_integral_v<T>)
                {
                    if (e == RuleType::FILE_LENGTH)
                    {
                        transmissionCapture_->setFileLength(arg);
                    }
                    else if (e == RuleType::LOOP_RULE)
                    {
                        transmissionCapture_->setFileAmount(arg);
                    }
                }
            },
            v);
    }
}

void Controller::start()
{
    std::thread captureThread([this]() { transmissionCapture_->startCapture(); });
    captureThread.detach();

    while (true)
    {
        if (!packetCollections.empty())
        {
            FileLogger log(std::move(packetCollections.front()));
            packetCollections.erase(packetCollections.begin());
        }
        else if (packetCollections.empty() && !capturing_)
        {
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
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

void Controller::switchCapture()
{
    capturing_ = false;
}
