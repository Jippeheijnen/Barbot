#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-narrowing-conversions"
#pragma clang diagnostic ignored "-Wconversion"
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma ide diagnostic ignored "cert-err58-cpp"

//
// Created by Jippe Heijnen on 2/27/2019.
//

#include "../include/BrickPI3/BrickPi3.h"

#include <iostream>
#include <unistd.h>
#include <csignal>

using namespace std;

BrickPi3 BP;

/**
 * This function resets the motor voltages, nothing too complicated here.
 */

void stop() {
    BP.set_motor_power(PORT_B, 0);
    BP.set_motor_power(PORT_C, 0);
}

/**
 * this function uses two forloops to increase and decrease the voltage
 * to the motors gradually.
 * @param sleeptime The time in seconds you want to move between
 * the accelerating and decelerating. This  value has to be positive.
 */
void gradually_forward(float sleeptime) {
    for (unsigned int i=0; i<51;i++) {
        BP.set_motor_power(PORT_B, i);
        BP.set_motor_power(PORT_C, i);
        usleep(25000);
    }

    sleep(sleeptime);

    for (int i=50; i>=0;i--) {
        BP.set_motor_power(PORT_B, i);
        BP.set_motor_power(PORT_C, i);
        usleep(25000);
    }
}

/**
 * This function is self explanatory, only one interesting thing tho,
 * the turnspeed is dialled down. This way the turns are a lot more consistent.
 */
void turn_around() {
    BP.set_motor_limits(PORT_B, 20, 0);
    BP.set_motor_limits(PORT_C, 20, 0);
    BP.set_motor_position_relative(PORT_B, 390);
    BP.set_motor_position_relative(PORT_C, -390);

    usleep(500000);
    sleep(2);

    BP.set_motor_limits(PORT_B, 60, 0);
    BP.set_motor_limits(PORT_C, 60, 0);

}

/**
 * This function makes sure all the motors stop when the user presses ctrl + c.
 * We wouldn't want a rogue robot now, would we?
 * @param signo This parameter is the exitcode provided by the compiled program.
 */

void exit_signal_handler(int signo){
    if(signo == SIGINT){
        BP.reset_all();    // Reset everything so there are no run-away motors
        exit(-2);
    }
}
/**
 * This function sets the brickPi to be ready for receiving commands.
 */
void brickPiSetup() {
    signal(SIGINT, exit_signal_handler); // register the exit function for Ctrl+C
    BP.detect(); // Make sure that the BrickPi3 is communicating and that the firmware is compatible with the drivers.
    BP.set_motor_limits(PORT_B, 60, 0);
    BP.set_motor_limits(PORT_C, 60, 0);
}

void move_forward(float sleeptime) {

    gradually_forward(sleeptime);

    turn_around();

    gradually_forward(.5);

    turn_around();

    stop();
}

#pragma clang diagnostic pop