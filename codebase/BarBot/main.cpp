
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
#include "SocketConnection.h"
#include "PumpService.h"

LineFollow LF;

BrickPi3 *BP3_Pointer = nullptr;
PumpService *Pumps_Pointer = nullptr;


void exit_handler(int signo) {
    if (signo == SIGINT) {
        BP3_Pointer->reset_all();
        exit(-2);
    }
    Pumps_Pointer->close();
};

void mainInit() {
    //Todo: init all relevant libraries.

    Pumps_Pointer = new PumpService();
    Pumps_Pointer->init();

    BP3_Pointer = new BrickPi3();
    BP3_Pointer->detect();
    M.init(*BP3_Pointer);

    signal(SIGINT, exit_handler);

}

int main() {
//    Todo: Event-loop here.
    mainInit();
    if(Pumps_Pointer->pour(7))
        std::cout << "SUCCESS" << std::endl;

    if(!Pumps_Pointer->pour(21))
        std::cout << "FAILED SUCCESFULLY" << std::endl;

//    for (fluid f : Pumps_Pointer->get_connected_fluids()) {
//        std::cout << " --- " << f.name << ":" << f.amount << std::endl;
//    }
//
//    for (drink d : Pumps_Pointer->get_drinks()) {
//        std::cout << d.name << ":" << d.id << std::endl;
//        for (fluid f : d.fluids) {
//            std::cout << " --- " << f.name << ":" << f.amount << std::endl;
//        }
//    }

//
//
//
//    bool running = true;
//    int count = 0;
//    mainInit(BP3);
//    BP3.reset_motor_encoder(PORT_D);
//    uint8_t startPos = BP3.get_motor_encoder(PORT_D);
//    sleep(2);
//    while (running) {
//
//    }
//    BP3.reset_all();
}