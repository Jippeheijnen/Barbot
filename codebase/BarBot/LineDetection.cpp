//
// Created by niels on 3/6/2019.
//

#include <iostream>
#include <zconf.h>
#include "LineDetection.h"

void LineDetection::init(int16_t target, int16_t margin) {
    this->target = target;
    this->margin = margin;

    BP.detect(); // Ensure
    BP.set_sensor_type(LIGHT_SENSOR_PORT, SENSOR_TYPE_NXT_LIGHT_ON);
    BP.set_sensor_type(COLOR_SENSOR_PORT, SENSOR_TYPE_NXT_COLOR_FULL);
}

double LineDetection::getLineDirection() {
    if(BP.get_sensor(LIGHT_SENSOR_PORT, LIGHT_SENSOR_DATA) == 0) {
//        std::cout << LIGHT_SENSOR_DATA.reflected << std::endl;
        int16_t relative = LIGHT_SENSOR_DATA.reflected - this->target;
        if (abs(relative) < margin)
            return 0;
        return ((double) relative) * LIGHT_SENSOR_FACTOR;
    }
    std::cout << "Error getting Light Sensor Data" << std::endl;
    return 0;
}

ColorReading LineDetection::readColor() {
    if (BP.get_sensor(COLOR_SENSOR_PORT, COLOR_SENSOR_DATA) == 0) {
        lastColorReading.hasChanged = lastColorReading.color != COLOR_SENSOR_DATA.color;
        lastColorReading.color = COLOR_SENSOR_DATA.color;
    }
    return lastColorReading;
}
