
#include <iostream>
#include <BarBot/Util/Logger.h>
#include "LineDetection.h"


const std::string LineDetection::TAG = "LineDetection";

double LineDetection::getLineDirection() {
    if(brickPi3->get_sensor(LIGHT_SENSOR_PORT, LIGHT_SENSOR_DATA) == 0) {
        int16_t relative = LIGHT_SENSOR_DATA.reflected - this->target;
        if (abs(relative) < margin)
            return 0;
        return ((double) relative) * LIGHT_SENSOR_FACTOR;
    }
    Logger::log(TAG, "Error getting Light Sensor Data");
    return 0;
}

ColorReading LineDetection::readColor() {

    if (brickPi3->get_sensor(COLOR_SENSOR_PORT, COLOR_SENSOR_DATA) == 0) {

        lastColorReading.hasChanged = lastColorReading.color != COLOR_SENSOR_DATA.color;
        lastColorReading.color = COLOR_SENSOR_DATA.color;

    }

    return lastColorReading;
}

void LineDetection::init(int16_t tar, int16_t mar) {

    margin = mar;
    target = tar;
    brickPi3->set_sensor_type(LIGHT_SENSOR_PORT, SENSOR_TYPE_NXT_LIGHT_ON);
    brickPi3->set_sensor_type(COLOR_SENSOR_PORT, SENSOR_TYPE_NXT_COLOR_FULL);

}

LineDetection::LineDetection(BrickPi3 *brickPi3, Movement *movement) : brickPi3(brickPi3), movement(movement) {}
