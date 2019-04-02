
#include  <iostream>

#include <iomanip>
#include <csignal>
#include <zconf.h>
#include <functional>

#include "../../include/BrickPI3/BrickPi3.h"


#include "Movement.h"

Movement M;

#include "LineDetection.h"

LineDetection LD;

#include "LineFollow.h"

LineFollow LF;

BrickPi3 *BP3_Pointer = nullptr;

void exit_handler(int signo) {
    BrickPi3 BP3 = *BP3_Pointer;
    if (signo == SIGINT) {
        BP3.reset_all();
        exit(-2);
    }
};

void mainInit(BrickPi3 &BP3) {
    //Todo: init all relevant libraries.
    signal(SIGINT, exit_handler);
    BP3.detect();
    M.init(BP3);

}

int main() {
//    Todo: Event-loop here.

    BrickPi3 BP3;
    BP3_Pointer = &BP3;

    bool running = true;
    int count = 0;
    mainInit(BP3);
    BP3.reset_motor_encoder(PORT_D);
    uint8_t startPos = BP3.get_motor_encoder(PORT_D);
    sleep(2);
    while (running) {

    }
    BP3.reset_all();
}