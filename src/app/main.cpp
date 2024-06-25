#include <iostream>
#include <thread>
#include "transmission_capture.hpp"

int main()
{
    TransmissionCapture& capture = TransmissionCapture::getInstance();
    capture.startCapture("192.168.1.26");
    // std::thread th(&TransmissionCapture::startCapture, &capture, "192.168.1.26");
    // th.join();
}
