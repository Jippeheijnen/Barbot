
#include <iostream>
#include <csignal>
#include "Movement.h"

void Movement::init() {
    motor = new ArduinoMotor();
    motor->init();
    brickPi3->set_motor_limits(PORT_A, 60, 200);
    brickPi3->reset_motor_encoder(PORT_A);
    centerPosition = brickPi3->get_motor_encoder(PORT_A);
}

void Movement::stop() {
    targSpeed = 0;
}

void Movement::steer(bool direction, uint8_t percentage) {
    //TODO: Steering function
    if (direction)
        brickPi3->set_motor_position(PORT_A, (centerPosition - percentage));
    else
        brickPi3->set_motor_position(PORT_A, (centerPosition + percentage));
}

void Movement::center() {
    brickPi3->set_motor_position(PORT_A, centerPosition);
}

void Movement::speed(int16_t speed) {
    targSpeed = speed;
}

void Movement::step() {
    int16_t speedDiff = targSpeed - currSpeed;
    if (speedDiff != 0) {
        int16_t step = speedDiff / abs(speedDiff);
        int16_t newSpeed = currSpeed + step;

        if((currSpeed ^ newSpeed) < 0) {
            motor->setForwardRotation(targSpeed >= 0);
        }
        motor->setSpeed(static_cast<uint8_t>(abs(newSpeed)));
        currSpeed = newSpeed;
    }
}

Movement::Movement(BrickPi3 *brickPi3) : brickPi3(brickPi3) {}

