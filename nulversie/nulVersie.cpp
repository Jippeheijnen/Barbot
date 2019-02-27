//
// Created by Jippe Heijnen on 2/26/2019.
//

#include "../include/BrickPi3.h"
#include <iostream>
#include <unistd.h>
#include <signal.h>

using namespace std;

BrickPi3 BP;

void stop(void)
{
    BP.set_motor_power(PORT_B, 0);
    BP.set_motor_power(PORT_C, 0);
}

void move(void) {
    for (unsigned int i=0; i<51;i++) {
        BP.set_motor_power(PORT_B, i);
        BP.set_motor_power(PORT_C, i);
        usleep(25000);
    }
    for (int i=50; i>=0;i--) {
        BP.set_motor_power(PORT_B, i);
        BP.set_motor_power(PORT_C, i);
        usleep(25000);
    }
//    BP.set_motor_power(PORT_B, 20);
//    BP.set_motor_power(PORT_C, 20);
//    usleep(500000);
//    BP.set_motor_power(PORT_B, 40);
//    BP.set_motor_power(PORT_C, 40);
//    usleep(500000);
//    BP.set_motor_power(PORT_B, 50);
//    BP.set_motor_power(PORT_C, 50);
//    usleep(500000);
//    sleep(2);
//    BP.set_motor_position_relative(PORT_B, 180);
//    BP.set_motor_position_relative(PORT_C, -180);
//    usleep(500000);
//    BP.set_motor_power(PORT_B, 20);
//    BP.set_motor_power(PORT_C, 20);
//    sleep(2);
//    BP.set_motor_power(PORT_B, 20);
//    BP.set_motor_power(PORT_C, 20);
//    usleep(500000);
//    BP.set_motor_power(PORT_B, 40);
//    BP.set_motor_power(PORT_C, 40);
//    usleep(500000);
//    BP.set_motor_power(PORT_B, 50);
//    BP.set_motor_power(PORT_C, 50);
//    usleep(500000);
//    sleep(2);
//    BP.set_motor_position_relative(PORT_B, 180);
//    BP.set_motor_position_relative(PORT_C, -180);
//    BP.set_motor_power(PORT_B, 20);
//    BP.set_motor_power(PORT_C, 20);
    sleep(2);
    stop();
}

void exit_signal_handler(int signo){
    if(signo == SIGINT){
        BP.reset_all();    // Reset everything so there are no run-away motors
        exit(-2);
    }
}