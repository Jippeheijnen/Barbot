//
// Created by Niels on 4/8/2019.
//

#ifndef BARBOT_BARBOT_H
#define BARBOT_BARBOT_H


#include <BrickPI3/BrickPi3.h>
#include <BarBot/Movement/ArduinoMotor.h>
#include <BarBot/Movement/Movement.h>
#include <BarBot/Sensors/LineDetection.h>
#include <BarBot/Scripts/LineFollow.h>
#include <BarBot/Sensors/CupDetection.h>
#include <BarBot/Connectivity/PumpService.h>
#include <BarBot/Connectivity/BluetoothConnection.h>
#include <BarBot/Speech/SpeechRecognition.h>
#include <cmath>

class BarBot {
public:
    BrickPi3 *brickPi3;
    ArduinoMotor *motor;
    Movement *movement;
    LineDetection *lineDetection;
    LineFollow *lineFollow;
    CupDetection *cupDetection;
    PumpService *pumpService;
    BluetoothConnection *bluetoothConnection;
    SpeechRecognition *speechRecognition;

    int16_t lineDetectionTarget, lineDetectionMargin;
    float_t cupDetectionDistance;

    void setCupDetectionDistance(const float_t &cupDetectionDistance);

    void setLineDetectionTarget(int16_t lineDetectionTarget);

    void setLineDetectionMargin(int16_t lineDetectionMargin);

    BarBot();
    void init();
    void step();

};


#endif //BARBOT_BARBOT_H
