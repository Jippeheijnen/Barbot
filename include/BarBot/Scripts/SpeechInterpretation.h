//
// Created by Niels on 4/8/2019.
//

#ifndef BARBOT_SPEECHINTERPRETATION_H
#define BARBOT_SPEECHINTERPRETATION_H

#include <BarBot/Sensors/CupDetection.h>
#include <BarBot/Connectivity/DrinkService.h>
#include <BarBot/Speech/SpeechRecognition.h>
#include "LineFollow.h"

/**
 * Program to interpret Speech Recognition results
 */
class SpeechInterpretation {
private:
    LineFollow *lineFollow;
    CupDetection *cupDetection;
    DrinkService *pumpService;
    SpeechRecognition *speechRecognition;

public:
    /**
     * initializes speech recognition
     * @param lF
     * @param cD
     * @param pS
     */
    void init(LineFollow *lF, CupDetection *cD, DrinkService *pS);

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
};


#endif //BARBOT_SPEECHINTERPRETATION_H
