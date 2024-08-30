#include "transmission_capture.hpp"
#include "controller.hpp"

#include "controller.hpp"
#include "transmission_capture.hpp"

bool TransmissionCapture::onPacketArrivesBlockingMode(pcpp::RawPacket* packet, pcpp::PcapLiveDevice*, void* cookie)
{
    TransmissionCapture* captureInstance = static_cast<TransmissionCapture*>(cookie);

    std::lock_guard<std::mutex> lock(captureInstance->bufferMutex_);
    captureInstance->buffer_.push_back(std::make_unique<pcpp::RawPacket>(*packet));

    if (captureInstance->buffer_.size() >= captureInstance->fileLength_)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void TransmissionCapture::startCapture()
{

    if (nic_.empty())
    {
        nic_ = getActiveNIC();
    }

    pcapDevice_ = pcpp::PcapLiveDeviceList::getInstance().getPcapLiveDeviceByIp(nic_);
    if (pcapDevice_ == nullptr || !pcapDevice_->open())
    {
        return;
    }

    if (!berkeleyRule_.empty())
    {
        pcapDevice_->setFilter(berkeleyRule_);
    }

    std::size_t end = 0;
    while (end < loopAmount_ || infinite_)
    {
        pcapDevice_->startCaptureBlockingMode(onPacketArrivesBlockingMode, this, timeout_);
        {
            std::lock_guard<std::mutex> lock(bufferMutex_);
            Controller::getInstance().addToPacketCollections(std::move(buffer_));
            buffer_.clear();
        }
        pcapDevice_->stopCapture();
        end++;
    }
    pcapDevice_->close();
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

    std::mutex packetCountMutex;

    for (pcpp::PcapLiveDevice* device : devices)
    {
        if (!device->open())
        {
            continue;
        }
        if (device->getIPv4Address().toString() == "0.0.0.0")
        {
            continue;
        }

        int packetCount = 0;

        device->startCapture(
            [&packetCountMutex](pcpp::RawPacket*, pcpp::PcapLiveDevice*, void* cookie) {
                int* packetCount = static_cast<int*>(cookie);
                std::lock_guard<std::mutex> lock(packetCountMutex);
                (*packetCount)++;
            },
            &packetCount);

        std::this_thread::sleep_for(std::chrono::seconds(2));
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

void TransmissionCapture::setNIC(std::string& rule)
{
    std::transform(rule.begin(), rule.end(), rule.begin(), ::toupper);
    if (rule == "AUTO")
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

void TransmissionCapture::setTimeoutAmount(std::size_t amount)
{
    timeout_ = amount;
}
