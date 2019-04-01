
#ifndef BARBOT_MOTOR_H
#define BARBOT_MOTOR_H


#include "../../include/BrickPI3/BrickPi3.h"

class Movement {

private:
    BrickPi3 test;
    uint8_t currSpeed = 0;
    uint8_t targSpeed = 0;
public:
    uint8_t MOTOR_LEFT = PORT_B;
    uint8_t MOTOR_RIGHT = PORT_C;

    /**
     * This function checks the current & target speed. When they
     * are not equal, the bot will accelerate or decelerate.
     */
    void step();

    /**
     * Initializes Motors
     */
    void init(Classes &inC);

    /**
     * Stops the robot gradually
     */
    void stop();


    /**
     * steers the BarBot by limiting the speed to a certain motor
     * @param direction true is right, false is left.
     * @param percentage percentage in integers.
     */
    void steer(bool direction, uint8_t percentage);

    /**
     * Sets the speed for the motors
     * @param speed (arbitrary) speed to set
     */
    void speed(uint8_t speed);
};


#endif //BARBOT_MOTOR_H
