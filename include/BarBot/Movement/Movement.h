
#ifndef BARBOT_MOVEMENT_H
#define BARBOT_MOVEMENT_H

#include "BrickPI3/BrickPi3.h"
#include "ArduinoMotor.h"

class Movement {
private:
    int16_t currSpeed = 0;
    int16_t targSpeed = 0;
    int32_t centerPosition;
    BrickPi3 * brickPi3;
    bool forward;
    ArduinoMotor * motor;
    uint8_t kickStartPower, finalSpeed;
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
    void init(ArduinoMotor *mot, BrickPi3 *bp3, uint8_t kSP);

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
     * @param centerPos This is the posistion in which the steeringwheel is centered.
     */
    void center();

    /**
     * Sets the speed for the motors.
     * @param speed (arbitrary) speed to set
     */
    void speed(int16_t speed, bool force);

};



#endif //BARBOT_MOVEMENT_H
