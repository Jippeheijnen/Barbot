
#include <iostream>
#include <BarBot/Util/Logger.h>
#include "BarBot/Sensors/LineDetection.h"


const std::string LineDetection::TAG = "LineDetection";

double LineDetection::getLineDirection() {
    if(brickPi3->get_sensor(LIGHT_SENSOR_PORT, LIGHT_SENSOR_DATA) == 0) {
        int16_t relative = LIGHT_SENSOR_DATA.reflected - this->target;
        if (abs(relative) < margin)
            return 0;

        if(logSensorData)
            Logger::log(TAG, std::to_string(LIGHT_SENSOR_DATA.reflected));
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

void LineDetection::init(BrickPi3 *bp3, Movement *mov, int16_t tar, int16_t mar, bool lSD) {
    logSensorData = lSD;
    brickPi3 = bp3;
    movement = mov;
    margin = mar;
    target = tar;
    brickPi3->set_sensor_type(LIGHT_SENSOR_PORT, SENSOR_TYPE_NXT_LIGHT_ON);
    brickPi3->set_sensor_type(COLOR_SENSOR_PORT, SENSOR_TYPE_NXT_COLOR_FULL);
}

