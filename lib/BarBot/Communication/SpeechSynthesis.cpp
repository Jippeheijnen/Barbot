//
// Created by niels on 3/8/2019.
//

#include "BarBot/Communication/SpeechSynthesis.h"
#include <cstdlib>

void SpeechSynthesis::speak(std::string text) {
    std::string test = "/home/pi/speech.sh \"" + text + "\"";
    system(test.c_str());
}
