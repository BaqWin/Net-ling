#include "file_logger.hpp"

#include <iostream>

FileLogger::FileLogger(TransmissionCapture& capture, const std::string& filePath)
: capture(capture), pcapWriter(filePath), stopLogging(false), thread(&FileLogger::logPackets, this){}

FileLogger::~FileLogger() {
    if (thread.joinable()) {
        thread.join();
    }
    pcapWriter.close();
}

void FileLogger::stop() {
    stopLogging = true;
    capture.getCV().notify_all();
}

void FileLogger::logPackets() {
    while (true) {
        std::unique_lock<std::mutex> lock(capture.getInactiveMutex());
        capture.getCV().wait(lock, [this] { return !capture.getInactiveBuffer()->empty() || stopLogging; });

        if (stopLogging && capture.getInactiveBuffer()->empty()) {
            break;
        }

        auto buffer = capture.getInactiveBuffer();
        pcapWriter.open();
        for (const auto& packet : *buffer) {
            pcapWriter.writePacket(*packet);
            delete packet;
        }
        buffer->clear();
        pcapWriter.close();
    }
}
