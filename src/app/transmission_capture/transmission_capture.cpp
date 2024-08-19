#include "transmission_capture.hpp"
#include "controller.hpp"

void TransmissionCapture::onPacketArrival(pcpp::RawPacket* packet, pcpp::PcapLiveDevice* dev, void* cookie)
{
    (void)dev;
    TransmissionCapture* captureInstance = static_cast<TransmissionCapture*>(cookie);
    {
        std::lock_guard lock(captureInstance->bufferMutex);
        captureInstance->buffer.push_back(std::make_unique<pcpp::RawPacket>(*packet));
    } // lock_guard
    if (captureInstance->buffer.size() >= 100)
    {
        captureInstance->cv.notify_one();
    }
}

void TransmissionCapture::startCapture(const std::string& nic)
{
    pcpp::PcapLiveDevice* dev = pcpp::PcapLiveDeviceList::getInstance().getPcapLiveDeviceByIp(nic);
    if (dev == nullptr)
    {
        return;
    }
    if (!dev->open())
    {
        return;
    }

    dev->startCapture(TransmissionCapture::onPacketArrival, this);

    int end = 0;
    while (true)
    {
        if (end == 10)
        {
            break;
        }

        std::unique_lock<std::mutex> lock(bufferMutex);
        cv.wait(lock);

        Controller::getInstance().addToPacketCollections(std::move(buffer));
        buffer.clear();
        end++;
    }

    dev->stopCapture();
    dev->close();
}
