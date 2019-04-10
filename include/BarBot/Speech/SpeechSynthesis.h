
#ifndef BARBOT_SPEECHSYNTHESIS_H
#define BARBOT_SPEECHSYNTHESIS_H

#include <iostream>

class SpeechSynthesis {
public:
    /**
     * @param text
     * Excecutes a bash script that pronounces the text given as parameter.
     */
    static void speak(std::string text);
};


#endif //BARBOT_SPEECHSYNTHESIS_H
