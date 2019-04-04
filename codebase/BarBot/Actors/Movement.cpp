
#include <iostream>
#include <unistd.h>
#include <csignal>
#include "Movement.h"
#include "../../../include/BrickPI3/BrickPi3.h"
// Todo: Exit handler fix



void Movement::init(BrickPi3 &BP3) {
    this->BP3 = BP3;
//    BP3.set_motor_limits(MOTOR_LEFT, 60, 50);
    BP3.set_motor_limits(PORT_D, 60, 200);
}

void Movement::stop() {
    targSpeed = 0;
}

void Movement::steer(int32_t centerPos, bool direction, uint8_t percentage) {
    //TODO: Steering function
    if (direction)
        BP3.set_motor_position(PORT_D, (centerPos - percentage));
    else
        BP3.set_motor_position(PORT_D, (centerPos + percentage));

    std::cout << "Encoder: " << BP3.get_motor_encoder(PORT_D) << std::endl;
}

void Movement::center(int32_t centerPos) {
    BP3.set_motor_position(PORT_D, centerPos);
}

void Movement::speed(uint8_t speed) {
    targSpeed = speed;
}

//Todo: GPIO function here

void Movement::step() {
    int speedDiff = targSpeed - currSpeed;
    if (currSpeed != targSpeed)
        currSpeed=(static_cast<uint8_t>
                (currSpeed + (speedDiff / abs(speedDiff))));
    //todo: Call GPIO function here: func(currSpeed);
}