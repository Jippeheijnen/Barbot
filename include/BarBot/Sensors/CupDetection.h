#ifndef BARBOT_CUPDETECTION_H
#define BARBOT_CUPDETECTION_H

#include <iostream>
#include "BrickPI3/BrickPi3.h"


/**
 * Uses the ultrasonic sensor to detect if a cup is placed in the cupholder
 */
class CupDetection {
private:
    sensor_ultrasonic_t ULTRASONIC_SENSOR_DATA;

    uint8_t ULTRASONIC_SENSOR_PORT = PORT_4;

    BrickPi3* brickPi3;
public:
    static const std::string TAG ;
    float detectDistance;


    /**
     * Initializes CupDetection with a distance threshold
     * Sets sensor type of the selected port to ultrasonic
     * @param bp3 Pointer to the used brickpi instance
     * @param dD The targeted distance value in CM
     */
    void init(BrickPi3 *bp3, float dD);

    /**
     * Uses the Ultrasonic sensor to check if a cup is placed in the cupholder.
     * @return true if a cup is placed
     */
    int8_t isCupPlaced();
};


#endif //BARBOT_CUPDETECTION_H
