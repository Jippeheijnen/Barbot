#ifndef BARBOT_LINEFOLLOW_H
#define BARBOT_LINEFOLLOW_H


#include "BarBot/Sensors/LineDetection.h"


class LineFollow {
private:
    Movement *movement;
    LineDetection *lineDetection;
    bool toBePaused, disabled;
public:
    static const std::string TAG;

    /**
     * Initializes LineFollower
     * @param mov  Reference to the bot's movement instance
     * @param lineDet  Reference to the bot's linedetection instance
     */
    void init(Movement *mov, LineDetection *lineDet, bool disab);


    /**
     * collect data from LineDetection::getLineDirection, process it and send to function Movement::steer()
     */
    void step();

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
