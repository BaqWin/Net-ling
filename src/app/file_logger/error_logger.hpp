#pragma once

#include <fstream>
#include <string>

class ErrorLogger{
        std::ofstream errorFile_;
        std::mutex mutex_;
    public:
        ErrorLogger();
        void log(const std::string& message);
        ~ErrorLogger();
};
