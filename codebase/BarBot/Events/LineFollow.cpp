#include <cstdlib>
#include <iostream>
#include <cmath>
#include "LineFollow.h"

bool toBePaused = false;

const std::string LineFollow::TAG = "LineFollow";

void LineFollow::pause() {
    movement->stop();
    toBePaused = true;
}

void LineFollow::resume() {
    toBePaused = false;
}


double_t min = 0;
double_t max = 0;
void LineFollow::follow() {
    double_t sensorValue = lineDetection->getLineDirection();
    if(sensorValue > max)
        max = sensorValue;
    if (sensorValue < min) {
        min = sensorValue;
    }


    sensorValue /= 145;
    sensorValue *= 120;
    if (sensorValue > 120) {
        sensorValue = 120;
    }

    if (sensorValue < -120) {
        sensorValue = -120;
    }

    if (!toBePaused) {
        if (sensorValue < 0) {
            movement->steer(true, abs(sensorValue*0.75));
        }
        else if (sensorValue > 0){
            movement->steer(false, sensorValue*.75);
        }
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
