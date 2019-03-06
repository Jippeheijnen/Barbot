//
// Created by niels on 3/6/2019.
//

#ifndef BARBOT_LINEDETECTION_H
#define BARBOT_LINEDETECTION_H

#include "../include/BrickPI3/BrickPi3.h"

class LineDetection {
private:
    double LIGHT_SENSOR_FACTOR = 0.2;
    sensor_light_t LIGHT_SENSOR_DATA;
    uint8_t LIGHT_SENSOR_PORT = PORT_1;
    int16_t target,margin;
    BrickPi3 BP;
public:
    /**
     * Initializes LineDetection with a line threshold
     * @param target The target value
     * @param margin Error margin for detection
     */
    void init(int16_t target, int16_t margin);


    /**
     *
     * @return (arbitrary) value that indicates distance to the line. Positive values indicate the line is on the right
     * whereas negative values indicate the line is on the left
     */
    double getLineDirection();
};


#endif //BARBOT_LINEDETECTION_H
