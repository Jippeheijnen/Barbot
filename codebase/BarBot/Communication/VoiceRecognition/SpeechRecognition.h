//
// Created by User on 7-4-2019.
//

#ifndef BARBOT_SPEECHRECOGNITION_H
#define BARBOT_SPEECHRECOGNITION_H


#include <string>
#include <vector>

class SpeechRecognition {
public:
    void innit();
    std::vector<std::string> poll();
    void logics();

private:
    //innit variables
    long pipefd[2];
    long P;
    std::string item;
    char file;
    char *arg;

    //poll variables
    std::vector<std::string> pollResult;
    char pipeResult;
    long bytesread;
    std::string temp;
};


#endif //BARBOT_SPEECHRECOGNITION_H
