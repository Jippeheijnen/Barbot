#ifndef BARBOT_ARDUINOMOTOR_H
#define BARBOT_ARDUINOMOTOR_H



#include <iostream>

#if _WIN32
    struct pollfd{};
#else
    #include <poll.h>
#endif

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

    /**
     *  Initiates this class.
     */
    void init();

    /**
     * Sets the motor speed.
     * @param speed Input speed, uint8_t datatype.
     */
    void setSpeed(uint8_t speed);

    /**
     * Sets which direction the motors should turn.
     * @param rot Rotation boolean. True is forward.
     */
    void setDirection(bool rot);

};

#endif //BARBOT_ARDUINOMOTOR_H
