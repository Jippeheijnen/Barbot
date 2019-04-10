#include <cstdlib>
#include <iostream>
#include <cmath>
#include <BarBot/Util/Logger.h>
#include "BarBot/Scripts/LineFollow.h"

bool toBePaused = false;

const std::string LineFollow::TAG = "LineFollow";

void LineFollow::pause() {
    Logger::log(TAG, "Pausing Line following");
    toBePaused = true;
    movement->stop();
}

void LineFollow::resume() {
    Logger::log(TAG, "Resuming Line following");
    toBePaused = false;
}


double_t min = 0;
double_t max = 0;

void LineFollow::step() {
    double_t sensorValue = lineDetection->getLineDirection();
    if (sensorValue > max)
        max = sensorValue;
    if (sensorValue < min) {
        min = sensorValue;
    }


//    sensorValue /= 145;
//    sensorValue *= 200;
//    if (sensorValue > 120) {
//        sensorValue = 120;
//    }
//
//    if (sensorValue < -120) {
//        sensorValue = -120;
//    }

    Logger::log(TAG, std::to_string(sensorValue));
    if (sensorValue > 0)
        sensorValue *= .8;
    else
        sensorValue *= .4;


    if (!toBePaused) {
        if (sensorValue < 0) { // leaving line
            movement->steer(true, abs(sensorValue * 0.75));
        } else if (sensorValue > 0) { // entering line
            movement->steer(false, sensorValue * 0.75);
        } else
            movement->center();
    }

}

void LineFollow::init(Movement *mov, LineDetection *lineDet) {
    movement = mov;
    lineDetection = lineDet;
}

