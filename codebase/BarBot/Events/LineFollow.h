#ifndef BARBOT_LINEFOLLOW_H
#define BARBOT_LINEFOLLOW_H


#include "BarBot/Sensors/LineDetection.h"


class LineFollow {
private:
    Movement *movement;
    LineDetection *lineDetection;
public:
    LineFollow(Movement *movement, LineDetection *lineDetection);

    /**
     * collect data from LineDetection::getLineDirection, process it and send to function Movement::steer()
     */
    void follow();

    /**
     * Sets boolean toBePaused to true and stops the motor
     */
    void pause();

    /**
     * Sets boolean toBePaused to false
     */
    void resume();
};


#endif //BARBOT_LINEFOLLOW_H
