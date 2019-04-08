//
// Created by User on 7-4-2019.
//

#ifndef BARBOT_SPEECHRECOGNITION_H
#define BARBOT_SPEECHRECOGNITION_H


#include <string>
#include <vector>
#include <BarBot/Sensors/CupDetection.h>
#include <BarBot/Scripts/LineFollow.h>
#include <BarBot/Connectivity/PumpService.h>

class SpeechRecognition {
private:
    //init variables
    long pipefd[2];
    long P;
    std::string item;
    char file;
    char *arg;
    LineFollow *lineFollow;
    PumpService *pumpService;
    CupDetection *cupDetection;

    //poll variables
    std::vector<std::string> pollResult;
    char pipeResult;
    long bytesread;
    std::string temp;

public:
    void init(LineFollow *linFol, PumpService *pumpSer, CupDetection *cupDet);
    std::vector<std::string> poll();
    void logics();

};


#endif //BARBOT_SPEECHRECOGNITION_H
