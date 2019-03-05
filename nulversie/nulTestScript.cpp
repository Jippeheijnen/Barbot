#include "../include/BrickPI3/BrickPi3.h"
#include <iostream>
#include <unistd.h>
#include <signal.h>

using namespace std;



void exit_signal_handler(int signo);

//Stop
//void stop(void)
//{
//    BP.set_motor_power(PORT_B, 0);
//    BP.set_motor_power(PORT_C, 0);
//}

//Move Forward
void fwd(void)
{
    BP.set_motor_power(PORT_B, 20);
    BP.set_motor_power(PORT_C, 20);
    usleep(500000);
    BP.set_motor_power(PORT_B, 40);
    BP.set_motor_power(PORT_C, 40);
    usleep(500000);
    BP.set_motor_power(PORT_B, 50);
    BP.set_motor_power(PORT_C, 50);
    sleep(2);
    stop();

}
//Move Left
void left(void)
{
    BP.set_motor_position_relative(PORT_B, 270);
    BP.set_motor_position_relative(PORT_C, -270);
}
//Move Right
void right(void)
{
    BP.set_motor_position_relative(PORT_B, -270);
    BP.set_motor_position_relative(PORT_C, 270);
}
//Move backward
void back(void)
{
    BP.set_motor_dps(PORT_B, -360);
    BP.set_motor_dps(PORT_C, -360);
    sleep(3);
    stop();
}

// Signal handler that will be called when Ctrl+C is pressed to stop the program
//void exit_signal_handler(int signo){
////    if(signo == SIGINT){
////        BP.reset_all();    // Reset everything so there are no run-away motors
////        exit(-2);
////    }
////}