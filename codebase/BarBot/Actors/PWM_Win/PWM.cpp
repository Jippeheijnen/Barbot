#include <iostream>

#include "../PWM.h"

void PWM::init(){
    std::cout << "Fake-initializing PWM, since we don't have WiringPi on Windows :(";
}

void PWM::setRotation(bool rotation){
    std::cout << "Setting rotation to " << rotation << std::endl;
}

void PWM::sendPWM(uint8_t pwmspeed){
    std::cout << "Setting PWM-Speed to " << pwmspeed << std::endl;
}

void PWM::setCornerPWM(uint8_t pwmspeed) {
    std::cout << "Setting cornerPWMspeed to " << pwmspeed << std::endl;
}