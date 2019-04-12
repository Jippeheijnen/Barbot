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

    /**
     * commands the arduino motor
     * @param pack The packt for command
     */
    void command(const std::string & pack);

    /**
     * Clears the commands to the arduino motor
     */
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
