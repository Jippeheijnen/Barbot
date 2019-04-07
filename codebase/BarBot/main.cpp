
#include  <iostream>

#include <iomanip>
#include <csignal>
#include <zconf.h>
#include <functional>
#include <BarBot/Sensors/CupDetection.h>
#include <BarBot/Actors/Movement.h>
#include <BarBot/Events/LineFollow.h>
#include <BarBot/API/PumpService.h>
#include <unistd.h>
#include <sys/time.h>
#include "BarBot/App/BluetoothConnection.h"
#include "BarBot/Actors/ArduinoMotor.h"


const int16_t LINEDETECTION_THRESHOLD = 2005;
const int16_t LINEDETECTION_MARGIN = 30;

const int16_t CUPDETECTION_DISTANCE = 10;


BrickPi3 *brickPi3 = new BrickPi3();
Movement *movement = new Movement(brickPi3);
LineDetection *lineDetection = new LineDetection(brickPi3, movement);
LineFollow *lineFollow = new LineFollow(movement, lineDetection);
CupDetection *cupDetection = new CupDetection(brickPi3);
//PumpService *pumpService = new PumpService();
BluetoothConnection *bluetoothConnection = new BluetoothConnection(lineFollow);

void exit_handler(int signo) {
    if (signo == SIGINT) {
        brickPi3->reset_all();
//        pumpService->close();
        exit(-2);
    }
};

void mainInit() {
    std::cout << "Detecting BrickPi" << std::endl;
    brickPi3->detect();

//     Initialize Sensors
    lineDetection->init(LINEDETECTION_THRESHOLD, LINEDETECTION_MARGIN);
    std::cout << "Initializing CupDetection" << std::endl;
    cupDetection->init(CUPDETECTION_DISTANCE);

    std::cout << "Movement Init" << std::endl;
    movement->init();

    // Initialize Actors
//    std::cout << "Initializing Pump Service" << std::endl;
//    pumpService->init();

    std::cout << "BluetoothInit " << std::endl;
    bluetoothConnection->init();

    std::cout << "Sig Exit" << std::endl;
    signal(SIGINT, exit_handler);

}

long get_millis() {
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return tp.tv_sec * 1000 + tp.tv_usec / 1000;
}

int main() {

//    Todo: Event-loop here.

    bool running = true;
    int count = 0;
    std::cout << "Starting Main Init" << std::endl;
    mainInit();

//    movement->speed(0);

    long ms = get_millis();
    while(running) {
        lineFollow->follow();
    }
    usleep(10000000);
    movement->speed(-255);


}