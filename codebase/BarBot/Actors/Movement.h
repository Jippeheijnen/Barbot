
#ifndef BARBOT_MOVEMENT_H
#define BARBOT_MOVEMENT_H


#include "BrickPI3/BrickPi3.h"

class Movement {
private:
    uint8_t currSpeed = 0;
    uint8_t targSpeed = 0;
    int32_t centerPosition;
    BrickPi3 * brickPi3;
public:

    Movement(BrickPi3 *brickPi3);

/**
     * This function checks the current & target speed. When they
     * are not equal, the bot will accelerate or decelerate.
     */
    void step();

    /**
     * Initializes Motors
     */
    void init();

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
     * Centers the steering wheel
     * @param centerPos
     */
    void center();

    /**
     * Sets the speed for the motors
     * @param speed (arbitrary) speed to set
     */
    void speed(uint8_t speed);
};


#endif //BARBOT_MOVEMENT_H
