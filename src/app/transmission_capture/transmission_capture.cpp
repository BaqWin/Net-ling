#include "transmission_capture.hpp"
#include "controller.hpp"

void TransmissionCapture::onPacketArrival(pcpp::RawPacket* packet, pcpp::PcapLiveDevice*, void* cookie)
{
    TransmissionCapture* captureInstance = static_cast<TransmissionCapture*>(cookie);
    {
        std::lock_guard lock(captureInstance->bufferMutex);
        captureInstance->buffer.push_back(std::make_unique<pcpp::RawPacket>(*packet));
    } // lock_guard
    if (captureInstance->buffer.size() >= captureInstance->fileLength_)
    {
        captureInstance->cv.notify_one();
    }
}

void TransmissionCapture::startCapture()
{
    if (nic_.empty())
    {
        nic_ = getActiveNIC();
    }

    pcpp::PcapLiveDevice* dev = pcpp::PcapLiveDeviceList::getInstance().getPcapLiveDeviceByIp(nic_);
    if (dev == nullptr)
    {
        return;
    }
    if (!dev->open())
    {
        return;
    }

    if (!berkeleyRule_.empty())
    {
        dev->setFilter(berkeleyRule_);
    }

    dev->startCapture(TransmissionCapture::onPacketArrival, this);

    std::size_t end = 0;
    while (end < loopAmount_ || infinite_)
    {
        std::unique_lock<std::mutex> lock(bufferMutex);
        cv.wait(lock);

        Controller::getInstance().addToPacketCollections(std::move(buffer));
        buffer.clear();
        end++;
    }

    dev->stopCapture();
    dev->close();
    Controller::getInstance().switchCapture();
}

void TransmissionCapture::setBerkeleyRule(const std::string& rule)
{
    berkeleyRule_ = rule;
}

void TransmissionCapture::setFileLength(std::size_t rule)
{
    fileLength_ = rule;
}

std::string TransmissionCapture::getActiveNIC()
{
    pcpp::PcapLiveDeviceList& deviceList = pcpp::PcapLiveDeviceList::getInstance();
    std::vector<pcpp::PcapLiveDevice*> devices = deviceList.getPcapLiveDevicesList();

    std::string activeNIC = "127.0.0.1";
    int highestPacketCount = -1;

    for (pcpp::PcapLiveDevice* device : devices)
    {
        device->open();

        int packetCount = 0;
        device->startCapture(
            [](pcpp::RawPacket*, pcpp::PcapLiveDevice*, void* cookie) {
                int* packetCount = static_cast<int*>(cookie);
                (*packetCount)++;
            },
            &packetCount);

        std::this_thread::sleep_for(std::chrono::seconds(5));
        device->stopCapture();
        device->close();
        if (packetCount > highestPacketCount)
        {
            highestPacketCount = packetCount;
            activeNIC = device->getIPv4Address().toString();
        }
    }
    return activeNIC;
}

void TransmissionCapture::setNIC(const std::string& rule)
{
    if (rule == "Auto")
    {
        nic_ = getActiveNIC();
    }
    else
    {
        nic_ = rule;
    }
}

void TransmissionCapture::setFileAmount(std::size_t amount)
{
    loopAmount_ = amount;
}

void TransmissionCapture::setFileAmount(std::string& rule)
{
    std::transform(rule.begin(), rule.end(), rule.begin(), ::toupper);
    if (rule == "INFINITE" || rule == "LOOP")
    {
        infinite_ = true;
    }
}

std::string TransmissionCapture::getBerkeleyRule() const
{
    return berkeleyRule_;
}

std::size_t TransmissionCapture::getFileLength() const
{
    return fileLength_;
}

std::string TransmissionCapture::getNIC() const
{
    return nic_;
}

bool TransmissionCapture::isInfinite() const
{
    return infinite_;
}

std::size_t TransmissionCapture::getLoopAmount() const
{
    return loopAmount_;
}
