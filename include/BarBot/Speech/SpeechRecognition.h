//
// Created by User on 7-4-2019.
//

#ifndef BARBOT_SPEECHRECOGNITION_H
#define BARBOT_SPEECHRECOGNITION_H


#include <string>
#include <vector>
#include <BarBot/Sensors/CupDetection.h>
#include <BarBot/Scripts/LineFollow.h>
#include <BarBot/Connectivity/DrinkService.h>

class SpeechRecognition {
private:
    //init variables
    long speechPipe;
    char file;
    char *arg;
    LineFollow *lineFollow;
    DrinkService *drinkService;
    CupDetection *cupDetection;

    //step variables
public:
    static const std::string TAG, TAG_PYTHON;
    void init(LineFollow *linFol, DrinkService *pumpSer, CupDetection *cupDet);
    std::vector<std::string> poll();

};


#endif //BARBOT_SPEECHRECOGNITION_H
