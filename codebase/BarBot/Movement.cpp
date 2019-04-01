
#include <iostream>
#include <unistd.h>
#include <csignal>
#include "Movement.h"

// Todo: Exit handler fix

//void exit_signal_handler(int signo) {
//    if (signo == SIGINT) {
//        BP.reset_all();    // Reset everything so there are no run-away motors
//        exit(-2);
//    }
//}



void Movement::init() {
//    signal(SIGINT, exit_signal_handler);
    this->classes = inC;
    classes.BP3.detect();
    classes.BP3.set_motor_limits(MOTOR_LEFT, 60, 0);
    classes.BP3.set_motor_limits(MOTOR_RIGHT, 60, 0);
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