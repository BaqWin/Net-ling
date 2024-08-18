#include "controller.hpp"

void Controller::init(){

}
void Controller::start(const std::string& nic){
    std::string networkCard = nic;
}
Controller& Controller::getInstance(){
    static Controller instance;
    return instance;
}