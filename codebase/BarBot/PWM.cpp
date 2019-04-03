#include <wiringPi.h>
#include <iostream>
#include <stdio.h>
#include "PWM.h"

void init(){
    wiringPiSetupGPIO();
    pinMode(16, PWM_OUTPUT);
    pwmSetMode(PWN_MODE_MS);
    pwmSetRange(255);
}

void sendPWM(uint8_t pwmspeed){
    pwmWrite(16,pwmspeed);
}