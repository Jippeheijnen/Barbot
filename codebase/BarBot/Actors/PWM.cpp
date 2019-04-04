#include <iostream>
#include <cstdio>
#include <wiringPi.h>
#include <softPwm.h>
#include "PWM.h"

void PWM::init(){
    wiringPiSetupGpio();
    pinMode(pinPWM, PWM_OUTPUT);
    pwmSetMode(PWN_MODE_MS);
    pinMode(pinEnableCLK, OUTPUT);
    pinMode(pinEnableCCLK, OUTPUT);
    pwmSetRange(1024);
}

void PWM::setRotation(bool rotation){
    digitalWrite(pinEnableCCLK, LOW);
    digitalWrite(pinEnableCLK, LOW);
    if(rotation){
        pinEnabled = pinEnableCLK;
    }
    else{pinEnabled = pinEnableCCLK;}
    digitalWrite(pinEnabled, HIGH);
}

void PWM::sendPWM(uint8_t pwmspeed){
    pwmWrite(pinPWM,int(pwmspeed));
}

void PWM::sendCornerPWM(uint8_t pwmspeed) {
    pwmWrite(pinPWM, int(pwmspeed*0.8))
}