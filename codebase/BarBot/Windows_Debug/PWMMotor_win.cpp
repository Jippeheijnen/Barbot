#include <iostream>

#include "BarBot/Actors/PWMMotor.h"



void PWMMotor::setRotation(bool rotation){
    std::cout << "Setting rotation to " << rotation << std::endl;
}

void PWMMotor::sendPWM(uint8_t pwmspeed){
    std::cout << "Setting PWM-Speed to " << pwmspeed << std::endl;
}

void PWMMotor::sendCornerPWM(uint8_t pwmspeed) {
    std::cout << "Setting cornerPWMspeed to " << pwmspeed << std::endl;
}

PWMMotor::PWM(int pinPWM, int pinEnableCLK, int pinEnableCCLK) : pinPWM(pinPWM), pinEnableCLK(pinEnableCLK) {
    std::cout << "* Fake-initializing PWM, since we don't have WiringPi on Windows :(";
    std::cout << "* Using Pins: " << pinPWM << "," << pinEnableCLK << " and " << pinEnableCCLK;
}
