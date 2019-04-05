
#include <iostream>
#include <csignal>
#include "Movement.h"
// Todo: Exit handler fix



void Movement::init() {
    motorPWM = new PWM(16, 18, 20);
    brickPi3->set_motor_limits(PORT_D, 60, 200);
    brickPi3->reset_motor_encoder(PORT_D);
    centerPosition = brickPi3->get_motor_encoder(PORT_D);
}

void Movement::stop() {
    targSpeed = 0;
}

void Movement::steer(bool direction, uint8_t percentage) {
    //TODO: Steering function
    if (direction)
        brickPi3->set_motor_position(PORT_D, (centerPosition - percentage));
    else
        brickPi3->set_motor_position(PORT_D, (centerPosition + percentage));

    std::cout << "Encoder: " << brickPi3->get_motor_encoder(PORT_D) << std::endl;
}

void Movement::center() {
    brickPi3->set_motor_position(PORT_D, centerPosition);
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

Movement::Movement(BrickPi3 *brickPi3) : brickPi3(brickPi3) {}

