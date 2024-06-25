#include "file_logger.hpp"

#include <iostream>

FileLogger::FileLogger(TransmissionCapture& capture, const std::string& filePath)
: capture(capture), pcapWriter(filePath), thread(&FileLogger::logPackets, this){}

FileLogger::~FileLogger(){
    if(thread.joinable()){
        thread.join();
    }
    pcapWriter.close();
}

void FileLogger::logPackets(){
    std::unique_lock<std::mutex> lock(capture.getInactiveMutex());

    auto buffer = capture.getInactiveBuffer();
    pcapWriter.open();
    for (const auto& packet : *buffer){
        pcapWriter.writePacket(*packet);
        delete packet;
    }
    buffer->clear();
}
