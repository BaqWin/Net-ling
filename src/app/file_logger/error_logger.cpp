#include "error_logger.hpp"

ErrorLogger::ErrorLogger(){
    errorFile_.open("errors.log", std::ios_base::app);
}

void ErrorLogger::log(const std::string& message){
    std::lock_guard<std::mutex> lock(mutex_);
    if (errorFile_.is_open())
    {
        errorFile_ << message << std::endl;
    }
}

ErrorLogger::~ErrorLogger(){
    errorFile_.close();
}
