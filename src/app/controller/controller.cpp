#include "controller.hpp"

void Controller::init()
{
    transmissionCapture = std::make_shared<TransmissionCapture>();
}
void Controller::start(const std::string& nic)
{
    std::thread captureThread([this, nic]() { transmissionCapture->startCapture(nic); });
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
