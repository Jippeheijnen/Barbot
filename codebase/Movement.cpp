//
// Created by niels on 3/6/2019.
//

#include "Movement.h"
#include "../include/BrickPI3/BrickPi3.h"
#include <iostream>
#include <unistd.h>
#include <csignal>

BrickPi3 BP;

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
    for (int32_t i = Movement::currSpeed; i >= 0; i--) {
        BP.set_motor_power(MOTOR_LEFT, i);
        BP.set_motor_power(MOTOR_RIGHT, i);
        usleep(25000);
    }
}

void Movement::steer(int32_t direction, int32_t milliseconds) {

}

void Movement::speed(uint8_t speed) {
    for (uint8_t i = 0; i < speed; i++) {
        BP.set_motor_power(MOTOR_LEFT, i);
        BP.set_motor_power(MOTOR_RIGHT, i);
        usleep(25000);
    }
    currSpeed = speed;
}
