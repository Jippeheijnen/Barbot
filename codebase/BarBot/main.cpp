
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
#include "BarBot/Communication/SpeechSynthesis.h"
#include "BarBot/Communication/VoiceRecognition/SpeechRecognition.h"
#include "BarBot/Util/Logger.h"


const int16_t LINEDETECTION_THRESHOLD = 2005;
const int16_t LINEDETECTION_MARGIN = 30;

const int16_t CUPDETECTION_DISTANCE = 10;


BrickPi3 *brickPi3 = new BrickPi3();
Movement *movement = new Movement(brickPi3);
LineDetection *lineDetection = new LineDetection(brickPi3, movement);
LineFollow *lineFollow = new LineFollow(movement, lineDetection);
CupDetection *cupDetection = new CupDetection(brickPi3);
PumpService *pumpService = new PumpService();
BluetoothConnection *bluetoothConnection = new BluetoothConnection(lineFollow);
SpeechRecognition *speechRecognition = new SpeechRecognition(lineFollow, pumpService, cupDetection);

void exit_handler(int signo) {
    if (signo == SIGINT) {
        brickPi3->reset_all();
//        pumpService->close();
        exit(-2);
    }
};

void mainInit() {
    Logger::setLogShow({
                               BluetoothConnection::TAG
                       });

    brickPi3->detect();

    lineDetection->init(LINEDETECTION_THRESHOLD, LINEDETECTION_MARGIN);

    cupDetection->init(CUPDETECTION_DISTANCE);

    movement->init();

    // Initialize Actors
//    std::cout << "Initializing Pump Service" << std::endl;
//    pumpService->init();

    bluetoothConnection->init();

    Logger::log("Main", "Setting SIG Exit");
    signal(SIGINT, exit_handler);

}

long get_millis() {
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return tp.tv_sec * 1000 + tp.tv_usec / 1000;
}

int main() {

    bool running = true;
    int count = 0;
    mainInit();

//    movement->speed(0);

    long ms = get_millis();
    while(running) {
        lineFollow->follow();
        bluetoothConnection->poll();
    }
    usleep(10000000);
    movement->speed(-255);


}