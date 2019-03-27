#include "LineFollow.h"
#include "LineDetection.h"
#include "Movement.h"

void Follow() {
    if(ColorReading.hasChanged == true){cout << ColorReading.color;}
    double SensorInput = LineDetection::getLineDirection();
    if (SensorInput > 0) {
        Movement::steer(true, 100 - x);
        Movement::steer(false,100);
    } else {
        Movement::steer(false, 100 + x);
        Movement::steer(true,100);
    }
}

void Destination(){
    if(ColorReading.hasChanged==true && ColorReading.color == DestinationColor){
        Movement::stop()
    }
}