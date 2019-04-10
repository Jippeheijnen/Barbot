#include "BarBot/Communication/SpeechRecognition.h"
#include <syscall.h>
#include <zconf.h>
#include <string>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
#include <BarBot/Connectivity/DrinkService.h>
#include <BarBot/Communication/SpeechSynthesis.h>
#include <BarBot/Scripts/LineFollow.h>
#include <BarBot/Sensors/CupDetection.h>
#include <BarBot/Util/Logger.h>
#include <fcntl.h>

const std::string SpeechRecognition::TAG = "SpeechRecognition";
const std::string SpeechRecognition::TAG_PYTHON = "SpeechRecognition.py";

void SpeechRecognition::init(LineFollow *linFol, DrinkService *pumpSer, CupDetection *cupDet) {
    lineFollow = linFol;
    drinkService = pumpSer;
    cupDetection = cupDet;
    int pipeOut[2], pipeIn[2];

    pipe(pipeOut);
    pipe(pipeIn);

    pid_t pid = fork();
    fcntl(pipeOut[0], F_SETFL, O_NONBLOCK);
    fcntl(pipeOut[1], F_SETFL, O_NONBLOCK);
    fcntl(pipeIn[0], F_SETFL, O_NONBLOCK);
    fcntl(pipeIn[1], F_SETFL, O_NONBLOCK);

    if(pid == 0) {
        Logger::log(TAG_PYTHON, "Starting up speech recognition");
        dup2(pipeOut[1], STDOUT_FILENO);
        dup2(pipeIn[0], STDIN_FILENO);

        Logger::log(TAG_PYTHON, "Closing Useless pipes");
        close(pipeOut[0]);
        close(pipeIn[1]);


        char* arg[] = {"/usr/bin/python", "/home/pi/SpeechRecognition.py", nullptr};
        execve(arg[0], arg, nullptr);
        Logger::log(TAG_PYTHON, "Something went wrong, this is after an exec call");
        exit(0);
    }
    else {
        Logger::log(TAG, "Closing useless pipes");
        close(pipeOut[1]);
        close(pipeIn[0]);
        speechPipe = pipeOut[0];
    }
}


std::vector<std::string> SpeechRecognition::poll() {
    std::vector<std::string> pollResult = {};
    char speechResult[301];
    Logger::log(TAG, "READING");
    long bytesread = read(speechPipe, speechResult, 300);
    Logger::log(TAG, std::to_string(bytesread));
    std::string temp;
    for(int i=0; i < bytesread; i++){
        if(speechResult[i] == ' ' or speechResult[i] == '\n'){
            pollResult.push_back(temp);
            Logger::log(TAG, temp);
            temp = "";

        }else{
            temp.push_back(speechResult[i]);
        }
    }

    if(temp.size() > 0)
        pollResult.push_back(temp);
    return pollResult;
}


