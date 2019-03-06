//
// amended by Jippe Heijnen on 2/27/2019.
//

#include <iostream>
#include <iomanip>
#include <csignal>
#include "../codebase/Movement.h"
#include "../codebase/LineDetection.h"
#include "../include/BrickPI3/BrickPi3.h"

BrickPi3 BP;

void exit_signal_handler(int signo){
    if(signo == SIGINT){
        BP.reset_all();    // Reset everything so there are no run-away motors
        exit(-2);
    }
}

int main() {
    signal(SIGINT, exit_signal_handler);
    BP.detect();
    BP.set_sensor_type(PORT_1, SENSOR_TYPE_NXT_LIGHT_ON);

    sensor_light_t Light3;

    while(true) {
        if(BP.get_sensor(PORT_1, Light3) == 0){
            std::cout << "Light sensor (S3): reflected " << std::setw(4) << Light3.reflected << std::endl;
        }
    }
    return 0;
}