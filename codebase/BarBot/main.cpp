
#include  <iostream>

#include <iomanip>
#include <csignal>
#include <zconf.h>
#include <functional>
#include <BarBot/Sensors/CupDetection.h>
#include <BarBot/Actors/Movement.h>
#include <BarBot/Events/LineFollow.h>
#include <BarBot/API/PumpService.h>
#include <BarBot/Actors/PWMMotor.h>
#include "BarBot/App/BluetoothConnection.h"



const int16_t LINEDETECTION_THRESHOLD = 2000;
const int16_t LINEDETECTION_MARGIN = 30;

const int16_t CUPDETECTION_DISTANCE = 5;


BrickPi3 *brickPi3 = new BrickPi3();
Movement *movement = new Movement(brickPi3);
LineDetection *lineDetection = new LineDetection(brickPi3, movement);
LineFollow *lineFollow = new LineFollow(movement, lineDetection);
CupDetection *cupDetection = new CupDetection(brickPi3);
PumpService *pumpService = new PumpService();
PWMMotor *pwm = new PWMMotor(0, 0, 0);
BluetoothConnection *bluetoothConnection = new BluetoothConnection(lineFollow);

void exit_handler(int signo) {
    if (signo == SIGINT) {
        brickPi3->reset_all();
        exit(-2);
    }
    pumpService->close();
};

void mainInit() {
    brickPi3->detect();

    // Initialize Sensors
    lineDetection->init(LINEDETECTION_THRESHOLD, LINEDETECTION_MARGIN);
    cupDetection->init(CUPDETECTION_DISTANCE);
    movement->init();

    // Initialize Actors
    pumpService->init();

    bluetoothConnection->init();

    signal(SIGINT, exit_handler);

}

int main() {

//    Todo: Event-loop here.

    bool running = true;
//    int count = 0;

    mainInit();


    while (running) {
        lineFollow->follow();
        bluetoothConnection->poll();
        usleep(250000);
    }
}