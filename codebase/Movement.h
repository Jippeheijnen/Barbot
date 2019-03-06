//
// Created by niels on 3/6/2019.
//

#ifndef BARBOT_MOTOR_H
#define BARBOT_MOTOR_H

#include "../include/BrickPI3/BrickPi3.h"

class Movement {
private:
    int8_t MOTOR_LEFT = PORT_B;
    int8_t MOTOR_RIGHT = PORT_C;
    int8_t currSpeed = 0;
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
     * Steer the robot in a direction
     * @param direction (arbitrary) The direction to steer in, negative values will steer left, whereas positive values will steer right
     * @param milliseconds The time in milliseconds to steer for
     */
    void steer(int32_t direction, int32_t milliseconds = 1000);

    /**
     * Sets the speed for the motors
     * @param speed (arbitrary) speed to set
     */
    void speed(int32_t speed);
};


#endif //BARBOT_MOTOR_H
