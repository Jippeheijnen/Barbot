#include <iostream>
#include <BarBot/Util/Logger.h>
#include "BarBot/Sensors/CupDetection.h"

const std::string CupDetection::TAG = "CupDetection";

/*
 * Yes, floats are being used because it's used that way in the original Brickpi code.
 * (•_•)
 * ( •_•)>⌐■-■
 * (⌐■_■)
 * Deal with it */

void CupDetection::init(BrickPi3 *bp3, float dD) {
    brickPi3 = bp3;
    detectDistance = dD;
    brickPi3->set_sensor_type(ULTRASONIC_SENSOR_PORT, SENSOR_TYPE_NXT_ULTRASONIC);

}

bool CupDetection::isCupPlaced() {

    if(brickPi3->get_sensor(ULTRASONIC_SENSOR_PORT, ULTRASONIC_SENSOR_DATA) == 0) {

        float distance = ULTRASONIC_SENSOR_DATA.cm;
        return distance < detectDistance;

    }

    Logger::log(TAG, "Error receiving Sonar Sensor Data");

    return false;

}

