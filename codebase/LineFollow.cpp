#include <zconf.h>
#include <iostream>
#include "LineFollow.h"
#include "LineDetection.h"
#include "Movement.h"

LineDetection LD;
Movement movement;

void LineFollow::follow() {
//    if(ColorReading.hasChanged == true){cout << ColorReading.color;}
    LD.init(2000, 20);
    movement.init();
    double SensorInput = LD.getLineDirection();
    std::cout << SensorInput << std::endl;
    if (SensorInput < 0) {
        movement.leftSpeed(((100+SensorInput)/100)*30);
        movement.rightSpeed(30);
    } else if (SensorInput > 0) {
        movement.rightSpeed(((100-SensorInput)/100)*30);
        movement.leftSpeed(30);
    }
    usleep(1000);
}

//void LineFollow::destination(){
//    if(ColorReading.hasChanged==true && ColorReading.color == DestinationColor){
//        M.stop()
//    }
//}

//double SensorInput = LineDetection::getLineDirection();
//if (SensorInput > 0) {
//BP.set_motor_power(MOTOR_STEER,(SensorInput&3.65));
//} else {
//BP.set_motor_position_relative(MOTOR_STEER,(SensorInput*3.65));
//}