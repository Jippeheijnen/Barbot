#include <iostream>
#include "CupDetection.h"

/*
 * Yes, floats are being used because it's used that way in the original Brickpi code.
 * (•_•)
 * ( •_•)>⌐■-■
 * (⌐■_■)
 * Deal with it */

void CupDetection::init(float dD) {

    detectDistance = dD;
    brickPi3->set_sensor_type(ULTRASONIC_SENSOR_PORT, SENSOR_TYPE_NXT_ULTRASONIC);

}

bool CupDetection::isCupPlaced() {

    if(brickPi3->get_sensor(ULTRASONIC_SENSOR_PORT, ULTRASONIC_SENSOR_DATA) == 0) {

        float distance = ULTRASONIC_SENSOR_DATA.cm;
        return distance < detectDistance;

    }

    std::cout << "Error receiving Sonar Sensor Data" << std::endl;

    return false;

}

CupDetection::CupDetection(BrickPi3 *brickPi3) : brickPi3(brickPi3) {}
