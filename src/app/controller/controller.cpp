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
    auto vec = factory.getRules(ruleFile_);

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
                    else if (e == RuleType::FILE_AMOUNT)
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
                    else if (e == RuleType::FILE_AMOUNT)
                    {
                        transmissionCapture_->setFileAmount(arg);
                    }
                    else if (e == RuleType::TIMEOUT)
                    {
                        transmissionCapture_->setTimeoutAmount(arg);
                    }
                }
            },
            v);
    }
}

void Controller::start()
{
    std::thread captureThread([this]() { transmissionCapture_->startCapture(); });
    std::vector<std::thread> loggerThreads;

    while (true)
    {
        std::lock_guard lock(collectionMutex_);
        if (!packetCollections_.empty())
        {
            auto packetCollection = std::move(packetCollections_.front());
            packetCollections_.erase(packetCollections_.begin());

            loggerThreads.emplace_back([packetCollection = std::move(packetCollection), this]() mutable {
                auto logger = std::make_unique<FileLogger>(std::move(packetCollection), outputSubDirectory_);
                logger->logPackets();
            });
        }
        else if (packetCollections_.empty() && !capturing_)
        {
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    captureThread.join();
    for (auto& thread : loggerThreads)
    {
        if (thread.joinable())
        {
            thread.join();
        }
    }
}

void Controller::addToPacketCollections(std::vector<std::unique_ptr<pcpp::RawPacket>>&& newVector)
{
    std::lock_guard<std::mutex> lock(collectionMutex_);
    packetCollections_.push_back(std::move(newVector));
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

void Controller::setTransmissionCapture(const std::shared_ptr<TransmissionCapture>& newCapture)
{
    transmissionCapture_ = newCapture;
}

void Controller::setOutputSubDirectory(const std::string& dir)
{
    outputSubDirectory_ = dir;
}

void Controller::setRuleFilePath(const std::string& name)
{
    ruleFile_ = name;
}

bool Controller::isCapturing() const
{
    return capturing_.load();
}

std::mutex& Controller::getPacketMutex()
{
    return collectionMutex_;
}
