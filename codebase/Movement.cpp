//
// Created by niels on 3/6/2019.
//

#include "Movement.h"
#include "../include/BrickPI3/BrickPi3.h"
#include <iostream>
#include <unistd.h>
#include <csignal>

BrickPi3 BP;

// Todo: This script needs to be updated for event-loop usage.

void exit_signal_handler(int signo) {
    if (signo == SIGINT) {
        BP.reset_all();    // Reset everything so there are no run-away motors
        exit(-2);
    }
}


void Movement::init() {
    signal(SIGINT, exit_signal_handler);
    BP.detect();
    BP.set_motor_limits(MOTOR_LEFT, 60, 0);
    BP.set_motor_limits(MOTOR_RIGHT, 60, 0);
}

void Movement::stop() {
        targSpeed = 0;
        BP.set_motor_power(MOTOR_LEFT, currSpeed * currLeft);
        BP.set_motor_power(MOTOR_RIGHT, currSpeed * currRight);
}

void Movement::steer(bool direction, uint8_t percentage) {
    //TODO: Steering function
}

void Movement::speed(uint8_t speed) {
    for (uint8_t i = currSpeed; i < speed; i++) {
        BP.set_motor_power(MOTOR_LEFT, i);
        BP.set_motor_power(MOTOR_RIGHT, i);
    }
    currSpeed = speed;
}
