#include <iostream>

#include "../PWM.h"


void PWM::setRotation(bool rotation){
    std::cout << "Setting rotation to " << rotation << std::endl;
}

void PWM::sendPWM(uint8_t pwmspeed){
    std::cout << "Setting PWM-Speed to " << pwmspeed << std::endl;
}

void PWM::sendCornerPWM(uint8_t pwmspeed) {
    std::cout << "Setting cornerPWMspeed to " << pwmspeed << std::endl;
}

PWM::PWM(int pinPWM, int pinEnableCLK, int pinEnableCCLK) : pinPWM(pinPWM), pinEnableCLK(pinEnableCLK) {
    std::cout << "* Fake-initializing PWM, since we don't have WiringPi on Windows :(";
    std::cout << "* Using Pins: " << pinPWM << "," << pinEnableCLK << " and " << pinEnableCCLK;
}
