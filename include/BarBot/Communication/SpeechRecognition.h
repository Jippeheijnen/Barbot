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

/**
 * Uses Google Cloud Speech and Python to recognise speech
 */
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
    /**
     * Forks the code to a child. The child creates a pipe and
     * initiates the python script that listens with a usb microphone,
     * and connects with the google speech api.
     * Result streamed to the pipe.
     * @param linFol
     * @param pumpSer
     * @param cupDet
     */
    void init(LineFollow *linFol, DrinkService *pumpSer, CupDetection *cupDet);

    /**
     * Reads out the pipe.
     * The recieved char array gets split into words, words are pushed to a vector.
     * Vector gets returned.
     * @return
     */
    std::vector<std::string> poll();

};


#endif //BARBOT_SPEECHRECOGNITION_H
