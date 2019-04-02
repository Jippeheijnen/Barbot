
#include <iostream>
#include <unistd.h>
#include <csignal>
#include "Movement.h"
#include "../../include/BrickPI3/BrickPi3.h"
// Todo: Exit handler fix



void Movement::init(BrickPi3 &BP3) {
//    BP3.set_motor_limits(MOTOR_LEFT, 60, 50);
    BP3.set_motor_limits(MOTOR_RIGHT, 60, 200);
}

void Movement::stop() {
    targSpeed = 0;
}

void Movement::steer(bool direction, uint8_t percentage) {
    //TODO: Steering function
}

void Movement::speed(uint8_t speed) {
    targSpeed = speed;
}

//Todo: GPIO function here

void Movement::step() {
    int speedDiff = targSpeed - currSpeed;
    if (currSpeed != targSpeed)
        currSpeed=(static_cast<uint8_t>(currSpeed + (speedDiff / abs(speedDiff))));
    //todo: Call GPIO function here: func(currSpeed);
}