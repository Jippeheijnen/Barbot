#include "../Actors/Movement.h"
#include <zconf.h>
#include <iostream>
#include "LineFollow.h"
#include "../Sensors/LineDetection.h"

bool toBePaused = false;

void LineFollow::pause(Movement &M) {
    M.stop();
    toBePaused = true;
}

void LineFollow::resume() {
    toBePaused = false;
}

void LineFollow::follow(double sensorValue, int32_t centerPos, Movement M, LineDetection LD) {

    // Todo: New version for only one steering motor

    if (!toBePaused) {
        if (sensorValue < 0) M.steer(centerPos, true, abs(sensorValue)/2);
        else if (sensorValue > 0)
            M.steer(centerPos, false, sensorValue/2);
        else
            M.center(centerPos);
    }
    if (toBePaused) {
        M.stop();
    }
    M.step();
}