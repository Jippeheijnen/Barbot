#ifndef BARBOT_CUPDETECTION_H
#define BARBOT_CUPDETECTION_H

#include <iostream>
#include "BrickPI3/BrickPi3.h"


class CupDetection {
private:
    sensor_ultrasonic_t ULTRASONIC_SENSOR_DATA;

    uint8_t ULTRASONIC_SENSOR_PORT = PORT_1;

    BrickPi3* brickPi3;
public:
    static const std::string TAG ;
    float detectDistance;


/**
     * Initializes CupDetection with a distance threshold
     * @param detectDistance The targeted distance value in CM
     */
    void init(BrickPi3 *bp3, float dD);


    bool isCupPlaced();
};


#endif //BARBOT_CUPDETECTION_H
