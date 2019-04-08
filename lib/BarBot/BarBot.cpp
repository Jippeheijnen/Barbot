//
// Created by Niels on 4/8/2019.
//

#include "BarBot/BarBot.h"




BarBot::BarBot() {
    brickPi3 = new BrickPi3();
    motor = new ArduinoMotor();
    movement = new Movement();
    lineDetection = new LineDetection();
    lineFollow = new LineFollow();
    cupDetection = new CupDetection();
    pumpService = new PumpService();
    bluetoothConnection = new BluetoothConnection();
    speechRecognition = new SpeechRecognition();
}

void BarBot::init() {
    brickPi3->detect();
    motor->init();
    movement->init(motor, brickPi3);
    lineDetection->init(brickPi3, movement, lineDetectionTarget, lineDetectionMargin);
    lineFollow->init(movement, lineDetection);
    cupDetection->init(brickPi3, cupDetectionDistance);
    pumpService->init();
    bluetoothConnection->init(lineFollow);
    speechRecognition->init(lineFollow, pumpService, cupDetection);
}



void BarBot::setLineDetectionTarget(int16_t lineDetectionTarget) {
    BarBot::lineDetectionTarget = lineDetectionTarget;
}

void BarBot::setLineDetectionMargin(int16_t lineDetectionMargin) {
    BarBot::lineDetectionMargin = lineDetectionMargin;
}

void BarBot::setCupDetectionDistance(const float_t &cupDetectionDistance) {
    BarBot::cupDetectionDistance = cupDetectionDistance;
}

void BarBot::step() {

}
