//
// Created by Niels on 4/8/2019.
//

#ifndef BARBOT_SPEECHINTERPRETATION_H
#define BARBOT_SPEECHINTERPRETATION_H

#include <BarBot/Sensors/CupDetection.h>
#include <BarBot/Connectivity/DrinkService.h>
#include <BarBot/Speech/SpeechRecognition.h>
#include "LineFollow.h"

class SpeechInterpretation {
private:
    LineFollow *lineFollow;
    CupDetection *cupDetection;
    DrinkService *pumpService;
    SpeechRecognition *speechRecognition;

public:
    void init(LineFollow *lF, CupDetection *cD, DrinkService *pS);
    void listen();
};


#endif //BARBOT_SPEECHINTERPRETATION_H
