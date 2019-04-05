#include <cstdlib>
#include <iostream>
#include "LineFollow.h"

bool toBePaused = false;

void LineFollow::pause() {
    movement->stop();
    toBePaused = true;
}

void LineFollow::resume() {
    toBePaused = false;
}

void LineFollow::follow() {
    double sensorValue = lineDetection->getLineDirection();
    std::cout << "sensorValue: " << sensorValue << std::endl;

    if (!toBePaused) {
        if (sensorValue < 0) movement->steer(true, abs(sensorValue)/2);
        else if (sensorValue > 0)
            movement->steer( false, sensorValue/2);
        else
            movement->center();
    }
    if (toBePaused) {
        movement->stop();
    }
    movement->step();
}

LineFollow::LineFollow(Movement *movement, LineDetection *lineDetection)
        : movement(movement), lineDetection(lineDetection) {}
