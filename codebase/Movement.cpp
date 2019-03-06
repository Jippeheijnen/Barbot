//
// Created by niels on 3/6/2019.
//

#include "Movement.h"

void Movement::init() {
    signal(SIGINT, exit_signal_handler);
    BP.detect();
    BP.set_motor_limits(PORT_B, 60, 0);
    BP.set_motor_limits(PORT_C, 60, 0);
}

void Movement::stop() {
    for (int32_t i=Movement::currSpeed; i>=0;i--) {
        BP.set_motor_power(PORT_B, i);
        BP.set_motor_power(PORT_C, i);
        usleep(25000);
    }
}

void Movement::steer(int32_t direction, int32_t milliseconds) {

}

void Movement::speed(int32_t speed) {
    for (int62_t i=0; i<51;i++) {
        BP.set_motor_power(PORT_B, i);
        BP.set_motor_power(PORT_C, i);
        usleep(25000);
    }
}
