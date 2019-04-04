
#ifndef BARBOT_MOTOR_H
#define BARBOT_MOTOR_H


#include "../../../include/BrickPI3/BrickPi3.h"

class Movement {

private:
    uint8_t currSpeed = 0;
    uint8_t targSpeed = 0;
    BrickPi3 BP3;
public:

    /**
     * This function checks the current & target speed. When they
     * are not equal, the bot will accelerate or decelerate.
     */
    void step();

    /**
     * Initializes Motors
     */
    void init(BrickPi3 &BP3);

    /**
     * Stops the robot gradually
     */
    void stop();


    /**
     * steers the BarBot by limiting the speed to a certain motor
     * @param direction true is right, false is left.
     * @param percentage percentage in integers.
     */
    void steer(int32_t centerPos, bool direction, uint8_t percentage);

    /**
     * Centers the steering wheel
     * @param centerPos
     */
    void center(int32_t centerPos);

    /**
     * Sets the speed for the motors
     * @param speed (arbitrary) speed to set
     */
    void speed(uint8_t speed);
};


#endif //BARBOT_MOTOR_H
