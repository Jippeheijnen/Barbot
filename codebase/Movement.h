//
// Created by niels on 3/6/2019.
//

#ifndef BARBOT_MOTOR_H
#define BARBOT_MOTOR_H

#include "../include/BrickPI3/BrickPi3.h"

class Movement {
private:
    uint8_t MOTOR_LEFT = PORT_B;
    uint8_t MOTOR_RIGHT = PORT_C;
    uint8_t currSpeed = 0;
    uint8_t currLeft = 0;
    uint8_t currRight = 0;
    uint8_t targLeft = 0;
    uint8_t targRight = 0;
    uint8_t targSpeed = 0;
public:
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
     * Sets the speed for the motors
     * @param speed (arbitrary) speed to set
     */
    void speed(uint8_t speed);
};


#endif //BARBOT_MOTOR_H
