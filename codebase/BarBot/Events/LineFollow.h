#ifndef BARBOT_LINEFOLLOW_H
#define BARBOT_LINEFOLLOW_H


#include "../Sensors/LineDetection.h"

class LineFollow {
public:
    /**
     * collect data from LineDetection::getLineDirection, process it and send to function Movement::steer()
     */
    void follow(double sensorValue, int32_t centerPos, Movement M, LineDetection LD);

    /**
     * Sets boolean toBePaused to true and stops the motor
     */
    void pause(Movement &M);

    /**
     * Sets boolean toBePaused to false
     */
    void resume();
};


#endif //BARBOT_LINEFOLLOW_H
