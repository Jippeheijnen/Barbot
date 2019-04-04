
#include  <iostream>

#include <iomanip>
#include <csignal>
#include <zconf.h>
#include <functional>

#include "../../include/BrickPI3/BrickPi3.h"
#include "App/BluetoothConnection.h"


#include "Actors/Movement.h"

Movement M;

#include "Sensors/LineDetection.h"

LineDetection LD;

#include "Events/LineFollow.h"
#include "API/SocketConnection.h"
#include "API/PumpService.h"

LineFollow *LF_Pointer = nullptr;
LineDetection *LD_Pointer = nullptr;
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
    // Init all relevant libraries.


    LD_Pointer = new LineDetection();
    LD_Pointer->init(2000, 30);

    Pumps_Pointer = new PumpService();

    Pumps_Pointer->init();

    BP3_Pointer = new BrickPi3();
    BP3_Pointer->detect();
    M.init(*BP3_Pointer);

    signal(SIGINT, exit_handler);

}

int main() {

//    Todo: Event-loop here.

    bool running = true;
//    int count = 0;

    mainInit();

    BP3_Pointer->reset_motor_encoder(PORT_D);
    int32_t centerPos = BP3_Pointer->get_motor_encoder(PORT_D);
    sleep(2);
    BluetoothConnection connection;
    connection.init();
    while(true) {
        connection.poll();
        usleep(1000);
    }
//    mainInit();
//    if(Pumps_Pointer->pour(7))
//        std::cout << "SUCCESS" << std::endl;
//
//    if(!Pumps_Pointer->pour(21))
//        std::cout << "FAILED SUCCESFULLY" << std::endl;

    while (running) {
        double sensorValue = LD_Pointer->getLineDirection();
        std::cout << "sensorValue: " << sensorValue << std::endl;
        LF_Pointer->follow(sensorValue, centerPos, M, LD);
        usleep(250000);
    }

    BP3_Pointer->reset_all();
}