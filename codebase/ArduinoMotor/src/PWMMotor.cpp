#include "PWMMotor.h"
#include "Arduino.h"

PWMMotor::PWMMotor(uint8_t pinA, uint8_t pinB) : pinA(pinA), pinB(pinB) {}


void PWMMotor::setPinA(uint8_t pinA) {
    PWMMotor::pinA = pinA;
    pinMode(pinA, OUTPUT);
    update();
}

void PWMMotor::setPinB(uint8_t pinB) {
    PWMMotor::pinB = pinB;
    pinMode(pinB, OUTPUT);
    update();
}

void PWMMotor::setSpeed(uint8_t speed) {
    if(speed > 255)
        speed = 255;
    PWMMotor::speed = speed;
    update();
}

void PWMMotor::setForwardRotation(bool forwardRotation) {
    PWMMotor::forwardRotation = forwardRotation;
    update();
}

void PWMMotor::update() {
    analogWrite(this->forwardRotation ? pinB : pinA, 0);
    analogWrite(this->forwardRotation ? pinA : pinB, speed);
}