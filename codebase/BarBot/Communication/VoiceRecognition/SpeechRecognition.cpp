#include "SpeechRecognition.h"
#include <syscall.h>
#include <zconf.h>
#include <string>
#include <cstring>
#include <iostream>
#include <vector>


void SpeechRecognition::innit() {
    syscall(SYS_pipe, pipefd, nullptr);


    long P;
    P = syscall(SYS_fork);
    if(P == 0) {

        syscall(SYS_dup2, pipefd[1], STDOUT_FILENO);
        syscall(SYS_close, pipefd[0], nullptr);


        std::string item = "/home/pi/Niels_VR/codebase/BarBot/Communication/VoiceRecognition/vr.py";
        char file[item.size()];
        std::strcpy(file, item.c_str());
        char *arg[] = {file, nullptr};

        syscall(SYS_execve, file, arg, NULL);
    }


}


std::vector<std::string> SpeechRecognition::poll() {
    std::vector<std::string> pollResult = {};


    char pipeResult[300];
    long bytesread = syscall(SYS_read, pipefd[0], pipeResult, 300,  nullptr);
    std::string temp;
    for(int i=0; i < bytesread -1; i++){
        if(pipeResult[i] == ' ' or pipeResult[i] == '\n'){
            pollResult.push_back(temp);
            temp = "";

        }else{
            temp.push_back(pipeResult[i]);
        }
    }
    return pollResult;
}
