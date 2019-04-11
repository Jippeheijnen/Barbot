
#ifndef BARBOT_SPEECHSYNTHESIS_H
#define BARBOT_SPEECHSYNTHESIS_H

#include <iostream>

/**
 * Uses Google Speech and an sh script to synthesise speech
 */
class SpeechSynthesis {
public:
    static const std::string TAG;
    /**
     * @param text
     * Excecutes a bash script that pronounces the text given as parameter.
     */
    static void speak(std::string text);
};


#endif //BARBOT_SPEECHSYNTHESIS_H