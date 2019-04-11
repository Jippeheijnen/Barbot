
#ifndef BARBOT_MOVEMENT_H
#define BARBOT_MOVEMENT_H

#include <cmath>
#include "BrickPI3/BrickPi3.h"
#include "ArduinoMotor.h"

/**
 * Performs all tasks that move the robot.
 * Movement takes care of gradually adjusting motor speed, to prevent damage the motor.
 *
 */
class Movement {
private:
    int16_t currSpeed = 0;
    int16_t targSpeed = 0;
    int32_t centerPosition;
    BrickPi3 * brickPi3;
    double_t correction = 1;
    bool forward;
    ArduinoMotor * motor;
    int16_t kickStartPower, finalSpeed;
    bool kickStarting = false;

public:
    static const std::string TAG;


/**
     * This function checks the current & target speed. When they
     * are not equal, the bot will accelerate or decelerate.
     */
    void step();

    /**
     * Initializes Motors.
     */
    void init(ArduinoMotor *mot, BrickPi3 *bp3, int16_t kSP);

    /**
     * Stops the robot gradually.
     */
    void stop();


    /**
     * steers the BarBot by limiting the speed to a certain motor.
     * @param direction true is right, false is left.
     * @param percentage percentage in integers.
     */
    void steer(bool direction, uint8_t percentage);

    /**
     * Centers the steering wheel.
     */
    void center();

    /**
     * Sets the target speed for the motors.
     * Note: This sets the target speed. When step is called periodically, motor speed will approach this target speed
     * @param speed (arbitrary) speed to set
     * @param force Should the speed be applied immediately, instead of gradually approaching it. This only works when the new speed is lower thant the current speed
     */
    void speed(int16_t speed, bool force);

};



#endif //BARBOT_MOVEMENT_H
