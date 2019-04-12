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

    /**
     * Function sets the noReadings boolean false or true
     * @param noReadings The boolean to set function true or false
     */
    void setNoReadings(bool noReadings);

    int16_t lineDetectionTarget, lineDetectionMargin;
    uint8_t movementKickStartPower;
    std::vector<int> pathingColorOrder = {};

    /**
     * Function sets the order of colors for pathing
     * @param pathingColorOrder The vector of ints for the order of colors for pathing
     */
    void setPathingColorOrder(const std::vector<int> &pathingColorOrder);

    /**
     * sets the kick start power
     * @param movementKickStartPower The uint to set the kickstartpower
     */
    void setMovementKickStartPower(uint8_t movementKickStartPower);

    float_t cupDetectionDistance;
    std::string drinkServerIP;

    /**
     * Sets the drink server
     * @param drinkServerIp The drinkserverip
     * @param drinkServerPort The drinkserverport
     */
    void setDrinkServer(const std::string &drinkServerIp, int drinkServerPort);

    int drinkServerPort;

    /**
     * sets the cupdetectiondistance according to @param cupDetectionDistance
     */
    void setCupDetectionDistance(const float_t &cupDetectionDistance);

    /**
     * sets linedetectiontarget according to @param lineDetectionTarget
     */
    void setLineDetectionTarget(int16_t lineDetectionTarget);

    /**
     * set linedetectionmargin according to @param lineDetectionMargin
     */
    void setLineDetectionMargin(int16_t lineDetectionMargin);

    BarBot();

    /**
     * Initiates everything
     */
    void init();

    /**
     * step function does one step of the eventloop
     */
    void step();

    /**
     * If @param logSensorData == true, saves every sensoroutput
     */
    void setLogSensorData(bool logSensorData);

    /**
     * handles the exits according to @param signo
     */
    void exit_handler(int signo);

};


#endif //BARBOT_BARBOT_H
