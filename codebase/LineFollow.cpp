#include "LineFollow.h"
#include "LineDetection.h"
#include "Movement.h"

void Follow() {
//    if(ColorReading.hasChanged == true){cout << ColorReading.color;}
    double SensorInput = LineDetection::getLineDirection();
    if (SensorInput > 0) {
        BP.set_motor_power(MOTOR_LEFT,((100+sensorinput)/100)*20);
        BP.set_motor_power(MOTOR_RIGHT, 20);
    } else {
        BP.set_motor_power(MOTOR_RIGHT,((100-sensorinput)/100)*20);
        BP.set_motor_power(MOTOR_LEFT,20);
    }
}

void Destination(){
    if(ColorReading.hasChanged==true && ColorReading.color == DestinationColor){
        Movement::stop()
    }
}

//double SensorInput = LineDetection::getLineDirection();
//if (SensorInput > 0) {
//BP.set_motor_power(MOTOR_STEER,(SensorInput&3.65));
//} else {
//BP.set_motor_position_relative(MOTOR_STEER,(SensorInput*3.65));
//}