//
// Created by Niels on 4/8/2019.
//

#ifndef BARBOT_SPEECHINTERPRETATION_H
#define BARBOT_SPEECHINTERPRETATION_H

#include <BarBot/Sensors/CupDetection.h>
#include <BarBot/Connectivity/DrinkService.h>
#include <BarBot/Communication/SpeechRecognition.h>
#include <BarBot/Communication/LCD_Smiley.h>
#include "LineFollow.h"

/**
 * Program to interpret Speech Recognition results
 */
class SpeechInterpretation {
private:
    Movement * movement;
    LineFollow *lineFollow;
    CupDetection *cupDetection;
    DrinkService *pumpService;
    SpeechRecognition *speechRecognition;
    LCD_Smiley * lcdSmiley;
    std::vector<std::string> heardLast;

public:
    static const std::string TAG;
    /**
     * initializes speech recognition
     * @param lF
     * @param cD
     * @param pS
     */
    void init(LineFollow *lF, CupDetection *cD, DrinkService *pS, SpeechRecognition  * sR,  LCD_Smiley *lS, Movement * mo);

    /**
     * Polls speech recognition.
     * This data is then compared to certain words to find commands.
     * If command is found, pauses linefollow.
     * Then it polls again to see which drink is wanted.
     * If a drink is given, waits untill a cup is detected.
     * Start to pump the given drink.
     * Then resumes linefollow.
     */
    void listen();

    bool wasHeard(std::string search);


    void handleDrinkDispensing();
};


#endif //BARBOT_SPEECHINTERPRETATION_H
