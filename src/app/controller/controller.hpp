#pragma once

#include <string>

class Controller{
        Controller() = default;

    public:
        void init();
        void start(const std::string& nic);
        static Controller& getInstance();

        Controller(const Controller&) = delete;
        Controller& operator=(const Controller&) = delete;
};