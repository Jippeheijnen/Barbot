#ifndef BARBOT_LINEFOLLOW_H
#define BARBOT_LINEFOLLOW_H


class LineFollow {
public:
    /**
     * collect data from LineDetection::getLineDirection, process it and send to function Movement::steer()
     */
    void Follow();
};


#endif //BARBOT_LINEFOLLOW_H
