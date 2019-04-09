#include "BarBot/Speech/SpeechRecognition.h"
#include <syscall.h>
#include <zconf.h>
#include <string>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
#include <BarBot/Connectivity/DrinkService.h>
#include <BarBot/Speech/SpeechSynthesis.h>
#include <BarBot/Scripts/LineFollow.h>
#include <BarBot/Sensors/CupDetection.h>
#include <BarBot/Util/Logger.h>

const std::string SpeechRecognition::TAG = "SpeechRecognition";
const std::string SpeechRecognition::TAG_PYTHON = "SpeechRecognition.py";

void SpeechRecognition::init(LineFollow *linFol, DrinkService *pumpSer, CupDetection *cupDet) {
    lineFollow = linFol;
    drinkService = pumpSer;
    cupDetection = cupDet;
    int pipeFD[2];
    pipe(pipeFD);

    long PID;
    Logger::log(TAG, "Forking Process");
    PID = fork();
    if(PID == 0) {

//        dup2(pipeFD[1], STDOUT_FILENO);

        Logger::log(TAG_PYTHON, "Closing Useless pipes");
        close(pipeFD[0]);
        Logger::log(TAG_PYTHON, "Starting up speech recognition");
        char* arg[] = {"/usr/bin/python", "/home/pi/SpeechRecognition.py", nullptr};
        execve(arg[0], arg, nullptr);
        Logger::log(TAG_PYTHON, "Something went wrong, this is after an exec call");
        exit(0);
    }
    else {
        Logger::log(TAG, "Closing useless pipes");
        speechPipe = pipeFD[0];
        syscall(SYS_close, pipeFD[1], nullptr);
    }


}


std::vector<std::string> SpeechRecognition::poll() {
    std::vector<std::string> pollResult = {};
    char speechResult[301];
    long bytesread = syscall(SYS_read, speechPipe, speechResult, 300,  nullptr);
    std::string temp;
    for(int i=0; i < bytesread; i++){
        if(speechResult[i] == ' ' or speechResult[i] == '\n'){
            pollResult.push_back(temp);
            temp = "";

        }else{
            temp.push_back(speechResult[i]);
        }
    }
    if(temp.size() > 0)
        pollResult.push_back(temp);
    return pollResult;
}



#pragma clang diagnostic pop