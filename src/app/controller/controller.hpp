#pragma once

#include "transmission_capture.hpp"

#include <string>
#include <memory>

class Controller{
        Controller() = default;
        std::shared_ptr<TransmissionCapture> transmissionCapture;
        std::vector<std::vector<std::unique_ptr<pcpp::RawPacket>>> packetCollections;

    public:
        void init();
        void start(const std::string& nic);
        void addToPacketCollections(std::vector<std::unique_ptr<pcpp::RawPacket>>&& newVector);
        static Controller& getInstance();

        Controller(const Controller&) = delete;
        Controller& operator=(const Controller&) = delete;
};