#include "LineFollow.h"
#include "LineDetection.h"
#include "Movement.h"

void Follow() {
    double SensorInput = LineDetection::getLineDirection();
    if (SensorInput > 0) {
        Movement::steer(true, 100 - x);
    } else {
        Movement::steer(false, 100 + x);
    }
}