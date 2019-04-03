#include <iostream>
#include "CupDetection.h"

/*
 * Yes, floats are being used because it's used that way in the original Brickpi code.
 * (•_•)
 * ( •_•)>⌐■-■
 * (⌐■_■)
 * Deal with it */

void CupDetection::init(float detectDistance) {
    this->detectDistance = detectDistance;

    BP.detect();
    BP.set_sensor_type(ULTRASONIC_SENSOR_PORT, SENSOR_TYPE_NXT_ULTRASONIC);
}

bool CupDetection::isCupPlaced() {
    if(BP.get_sensor(ULTRASONIC_SENSOR_PORT, ULTRASONIC_SENSOR_DATA) == 0) {
        float distance = ULTRASONIC_SENSOR_DATA.cm;
        return distance < detectDistance;
    }
    std::cout << "Error receiving Sonar Sensor Data" << std::endl;
    return false;
}
