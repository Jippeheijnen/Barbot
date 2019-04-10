//
// Created by niels on 3/8/2019.
//

#include "BarBot/Communication/SpeechSynthesis.h"
#include <cstdlib>
#include <algorithm>
#include <BarBot/Util/Logger.h>

const std::string SpeechSynthesis::TAG = "SpeechSynthesis";

void SpeechSynthesis::speak(std::string text) {
    std::replace(text.begin(), text.end(), ' ', '+');
    std::string test = "mplayer -ao alsa -noconsolecontrols -volume 500 \"http://translate.google.com/translate_tts?ie=UTF-8&client=tw-ob&q=" + text + "&tl=nl\" > /dev/null 2>&1";
    Logger::log(TAG, text);
    system(test.c_str());
}
