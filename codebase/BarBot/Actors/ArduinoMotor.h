#ifndef BARBOT_ARDUINOMOTOR_H
#define BARBOT_ARDUINOMOTOR_H


#include <cstdint>
#include <termios.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/signal.h>
#include <sys/types.h>
#include <termios.h>
#include <time.h>
#include <stdbool.h>
#include <stropts.h>
#include <poll.h>
#include <errno.h>

class ArduinoMotor {
private:
    int fileDescriptor;
    char buffer[255];
    int variable;
    struct pollfd fds[1];
    void command(std::string pack);
    void clear();

public:
    void init();
    void setSpeed(uint8_t speed);
    void setForwardRotation(bool rot);

};


#endif //BARBOT_ARDUINOMOTOR_H
