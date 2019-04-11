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
#include <BarBot/Connectivity/DrinkService.h>
#include <BarBot/Connectivity/AppControlService.h>
#include <BarBot/Communication/LCD_Smiley.h>
#include <BarBot/Communication/SpeechRecognition.h>
#include <BarBot/Connectivity/AppRequestService.h>
#include <BarBot/Scripts/Pathing.h>
#include <cmath>
#include <BarBot/Scripts/SpeechInterpretation.h>

/**
 * Class for holding pointers to all components in this program
 */
class BarBot {
public:
    BrickPi3 *brickPi3;
    ArduinoMotor *motor;
    Movement *movement;
    LineDetection *lineDetection;
    LineFollow *lineFollow;
    CupDetection *cupDetection;
    DrinkService *drinkService;
    AppControlService *appControlService;
    SpeechRecognition *speechRecognition;
    SocketConnection *drinkServerConnection;
    AppRequestService *appRequestService;
    Pathing* pathing;
    LCD_Smiley *lcd_smiley;
    SpeechInterpretation * speechInterpretation;
    bool running, logSensorData, noReadings;

    void setNoReadings(bool noReadings);

    int16_t lineDetectionTarget, lineDetectionMargin;
    uint8_t movementKickStartPower;
    std::vector<int> pathingColorOrder = {};

    void setPathingColorOrder(const std::vector<int> &pathingColorOrder);

    void setMovementKickStartPower(uint8_t movementKickStartPower);

    float_t cupDetectionDistance;
    std::string drinkServerIP;

    void setDrinkServer(const std::string &drinkServerIp, int drinkServerPort);

    int drinkServerPort;

    void setCupDetectionDistance(const float_t &cupDetectionDistance);

    void setLineDetectionTarget(int16_t lineDetectionTarget);

    void setLineDetectionMargin(int16_t lineDetectionMargin);

    BarBot();

    void init();

    void step();

    void setLogSensorData(bool logSensorData);

    void exit_handler(int signo);

};


#endif //BARBOT_BARBOT_H
