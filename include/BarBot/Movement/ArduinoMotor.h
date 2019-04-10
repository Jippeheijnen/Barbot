#ifndef BARBOT_ARDUINOMOTOR_H
#define BARBOT_ARDUINOMOTOR_H



#include <iostream>

#if _WIN32
    struct pollfd{};
#else
    #include <poll.h>
#endif

/**
 * Maintains a serial connection to an arduino that controls a motor
 */
class ArduinoMotor {
private:
    int fileDescriptor;
    char buffer[255];
    int variable;
    struct pollfd fds[1];
    void command(const std::string & pack);
    void clear();

public:
    static const std::string TAG;
    void init();
    void setSpeed(uint8_t speed);
    void setDirection(bool rot);

};

#endif //BARBOT_ARDUINOMOTOR_H
