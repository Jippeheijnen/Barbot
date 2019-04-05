#include <iostream>
#include <cstdio>
#include <wiringPi.h>
#include <softPwm.h>
#include "PWMMotor.h"


void PWMMotor::setRotation(bool rotation){
    digitalWrite(pinEnableCCLK, LOW);
    digitalWrite(pinEnableCLK, LOW);
    if(rotation){
        pinEnabled = pinEnableCLK;
    }
    else{pinEnabled = pinEnableCCLK;}
    digitalWrite(pinEnabled, HIGH);
}

void PWMMotor::sendPWM(uint8_t pwmspeed){
    pwmWrite(pinPWM,int(pwmspeed));
}

void PWMMotor::sendCornerPWM(uint8_t pwmspeed) {
    this->sendPWM(uint8_t (pwmspeed*0.8));
}

PWMMotor::PWMMotor(int pinPWM, int pinEnableCLK, int pinEnableCCLK) : pinPWM(pinPWM), pinEnableCLK(pinEnableCLK) {
    wiringPiSetupGpio();
    pinMode(pinPWM, PWM_OUTPUT);
    pwmSetMode(PWM_MODE_MS);
    pinMode(pinEnableCLK, OUTPUT);
    pinMode(pinEnableCCLK, OUTPUT);
    pwmSetRange(1024);
}