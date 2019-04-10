//
// Created by Niels on 4/8/2019.
//

#include <BarBot/Util/Logger.h>
#include "BarBot/BarBot.h"




BarBot::BarBot() {
    brickPi3 = new BrickPi3();
    motor = new ArduinoMotor();
    movement = new Movement();
    lineDetection = new LineDetection();
    lineFollow = new LineFollow();
    cupDetection = new CupDetection();
    drinkServerConnection = new SocketConnection();
    drinkService = new DrinkService();
    appControlService = new AppControlService();
    appRequestService = new AppRequestService();
    speechRecognition = new SpeechRecognition();
    speechInterpretation = new SpeechInterpretation();
    lcd_smiley = new LCD_Smiley();
    pathing = new Pathing();
}

void BarBot::init() {
    brickPi3->detect();
    motor->init();
    movement->init(motor, brickPi3, movementKickStartPower);
    lineDetection->init(brickPi3, movement, lineDetectionTarget, lineDetectionMargin, logSensorData, noReadings);
    lineFollow->init(movement, lineDetection);
    cupDetection->init(brickPi3, cupDetectionDistance);
    drinkServerConnection->init(drinkServerIP, drinkServerPort);
    drinkService->init(drinkServerConnection);
    appRequestService->init(drinkServerConnection);
    appControlService->init(movement);
    speechRecognition->init(lineFollow, drinkService, cupDetection);
    lcd_smiley->init();
    speechInterpretation->init(lineFollow, cupDetection, drinkService, speechRecognition, lcd_smiley);
    pathing->init(drinkServerConnection, appRequestService, lineDetection, lineFollow, movement, pathingColorOrder);
    running = true;
}

void BarBot::step() {
    lineFollow->step();
    appRequestService->update();
    appControlService->update();
    pathing->step();
    movement->step();
    speechInterpretation->listen();
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


void BarBot::setDrinkServer(const std::string &drinkServerIp, int drinkServerPort) {
    drinkServerIP = drinkServerIp;
    BarBot::drinkServerPort = drinkServerPort;
}

void BarBot::setMovementKickStartPower(uint8_t movementKickStartPower) {
    BarBot::movementKickStartPower = movementKickStartPower;
}

void BarBot::setPathingColorOrder(const std::vector<int> &pathingColorOrder) {
    BarBot::pathingColorOrder = pathingColorOrder;
}

void BarBot::setLogSensorData(bool logSensorData) {
    BarBot::logSensorData = logSensorData;
}

void BarBot::setNoReadings(bool noReadings) {
    BarBot::noReadings = noReadings;
}
