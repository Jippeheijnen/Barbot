#include "Movement.h"
#include <zconf.h>
#include <iostream>
#include "LineFollow.h"
#include "LineDetection.h"

bool toBePaused = false;

void LineFollow::pause(Movement &M) {
    M.stop();
    toBePaused = true;
}

void LineFollow::resume() {
    toBePaused = false;
}

void LineFollow::follow() {

    // Todo: New version for only one steering motor

//    if(ColorReading.hasChanged == true){cout << ColorReading.color;}
//    if(!toBePaused) {
//        LD.init(2000, 20);
//        movement.init();
//        double SensorInput = LD.getLineDirection();
//        std::cout << SensorInput << std::endl;
//        if (SensorInput < 0) {
//            movement.leftSpeed(((100 + SensorInput) / 100) * 30);
//            movement.rightSpeed(30);
//        } else if (SensorInput > 0) {
//            movement.rightSpeed(((100 - SensorInput) / 100) * 30);
//            movement.leftSpeed(30);
//        }
//        usleep(1000);
//    }
}