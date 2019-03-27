#ifndef BARBOT_LINEFOLLOW_H
#define BARBOT_LINEFOLLOW_H


class LineFollow {
public:
    /**
     * collect data from LineDetection::getLineDirection, process it and send to function Movement::steer()
     */
    void Follow();

    /**
     * Collects data from LineDetection::readColor, detects if it is the destination and makes the robot stop
     */
    void Destination();
};


#endif //BARBOT_LINEFOLLOW_H
