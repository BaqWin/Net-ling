#pragma once
#include <thread>
#include "pcapplusplus/PcapFileDevice.h"
#include "transmission_capture.hpp"

class FileLogger{
    TransmissionCapture& capture;
    pcpp::PcapFileWriterDevice pcapWriter;
    std::thread thread;

    public:
        FileLogger(TransmissionCapture& capture, const std::string& filePath);
        ~FileLogger();
        void logPackets();
};
