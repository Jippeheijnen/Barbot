//
// Created by niels on 4/5/2019.
//
#include <Arduino.h>
#include "PWMMotor.h"

PWMMotor * motor;
char  op[2];

void setup() {
    Serial.begin(57600);
    motor = new PWMMotor(6, 5);
}

void loop() {
    if(Serial.readBytes(op, 1)>0) {
        long val = Serial.readStringUntil('\n').toInt();

        if(*op == 'a') {
            Serial.println("Setting PWM");
            motor->setPinA(static_cast<uint8_t>(val));
        }

        if(*op == 'b') {
            Serial.println("Setting CLK");
            motor->setPinB(static_cast<uint8_t>(val));
        }

        if (*op == 'd') {
            Serial.println("Setting d");
            motor->setForwardRotation(val == 1);
        }
        if(*op == 's') {
            Serial.println("Setting s");
            motor->setSpeed(static_cast<uint8_t>(val));
        }
        Serial.println(val);
    }

}