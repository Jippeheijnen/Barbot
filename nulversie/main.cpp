//
// Created by Jippe Heijnen on 2/26/2019.
//

#include "nulVersie.cpp"

int main()
{
    signal(SIGINT, exit_signal_handler); // register the exit function for Ctrl+C
    BP.detect(); // Make sure that the BrickPi3 is communicating and that the firmware is compatible with the drivers.
    BP.set_motor_limits(PORT_B, 60, 0);
    BP.set_motor_limits(PORT_C, 60, 0);

    move();

    return 0;
}