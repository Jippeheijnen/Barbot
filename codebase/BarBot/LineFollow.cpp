#include <zconf.h>
#include <iostream>
#include "LineFollow.h"
#include "LineDetection.h"
#include "Movement.h"

LineDetection LD;
Movement movement;

bool toBePaused = false;

void LineFollow::pause() {
    movement.stop();
    toBePaused = true;
}

void LineFollow::resume() {
    toBePaused = false;
}

void LineFollow::follow() {
//    if(ColorReading.hasChanged == true){cout << ColorReading.color;}
    if(!toBePaused) {
        LD.init(2000, 20);
        movement.init();
        double SensorInput = LD.getLineDirection();
        std::cout << SensorInput << std::endl;
        if (SensorInput < 0) {
            movement.leftSpeed(((100 + SensorInput) / 100) * 30);
            movement.rightSpeed(30);
        } else if (SensorInput > 0) {
            movement.rightSpeed(((100 - SensorInput) / 100) * 30);
            movement.leftSpeed(30);
        }
        usleep(1000);
    }
}