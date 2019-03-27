#include "LineFollow.h"
#include "LineDetection.h"
#include "Movement.h"
#include "../include/BrickPI3/BrickPi3.h"

BrickPi3 BP3;
LineDetection LD;

void Follow() {
//    if(ColorReading.hasChanged == true){cout << ColorReading.color;}
    double SensorInput = LD.getLineDirection();
    if (SensorInput > 0) {
        BP3.set_motor_power(PORT_B,((100+SensorInput)/100)*20);
        BP3.set_motor_power(PORT_C, 20);
    } else {
        BP3.set_motor_power(PORT_C,((100-SensorInput)/100)*20);
        BP3.set_motor_power(PORT_B,20);
    }
}

//void Destination(){
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