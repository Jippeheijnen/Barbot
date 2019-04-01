#ifndef BARBOT_CUPDETECTION_H
#define BARBOT_CUPDETECTION_H

#include "../../include/BrickPI3/BrickPi3.h"


class CupDetection {
private:
    sensor_ultrasonic_t ULTRASONIC_SENSOR_DATA;

    uint8_t ULTRASONIC_SENSOR_PORT = PORT_3;

    BrickPi3 BP;
public:
    float detectDistance;

    /**
     * Initializes CupDetection with a distance threshold
     * @param detectDistance The targeted distance value in CM
     */
    void init(float detectDistance);


    bool isCupPlaced();
};


#endif //BARBOT_CUPDETECTION_H
