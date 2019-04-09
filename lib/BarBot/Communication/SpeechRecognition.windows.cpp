#include <BarBot/Util/Logger.h>
#include "BarBot/Speech/SpeechRecognition.h"

const std::string SpeechRecognition::TAG = "SpeechRecognition";

void SpeechRecognition::init(LineFollow *linFol, DrinkService *pumpSer, CupDetection *cupDet) {
}


std::vector<std::string> SpeechRecognition::poll() {
    Logger::log(TAG, "Requesting speech recognition, but we're on windows, soooo no bueno");
    return {};
}



