
#include <iostream>
#include <csignal>
#include <BarBot/Util/Logger.h>
#include "BarBot/Movement/Movement.h"

const std::string Movement::TAG = "Movement";

void Movement::init(ArduinoMotor *mot, BrickPi3 *bp3, int16_t kSP ) {
    motor = mot;
    kickStartPower = kSP;
    brickPi3 = bp3;
    motor->init();
    brickPi3->set_motor_limits(PORT_A, 60, 200);
    brickPi3->reset_motor_encoder(PORT_A);
    centerPosition = brickPi3->get_motor_encoder(PORT_A);
}

void Movement::stop() {
    speed(0, true);
}

void Movement::steer(bool direction, uint8_t percentage) {
//    correction = 1 - (float(percentage) / 100);
//    if(correction < 0.1)
//        correction = 0.1;
//    Logger::log(TAG, std::to_string(correction));
//    Logger::log(TAG, "Setting Direction" + std::to_string(percentage) + ":" + std::to_string(direction));
    if (direction)
        brickPi3->set_motor_position(PORT_A, (centerPosition - percentage));
    else
        brickPi3->set_motor_position(PORT_A, (centerPosition + percentage));
}

void Movement::center() {
    brickPi3->set_motor_position(PORT_A, centerPosition);
}

void Movement::speed(int16_t speed, bool force = false) {
    if (force) {
        if ((targSpeed > 0 && targSpeed > currSpeed) || (targSpeed < 0 && targSpeed < currSpeed)) {
            Logger::log(TAG, "Can't force a speed higher than the current one, this would be bad for the motor");
        } else {
            currSpeed = speed;
            targSpeed = speed;
            motor->setDirection(speed >= 0);
            motor->setSpeed(abs(speed));
        }
    } else {
        if (abs(speed) < kickStartPower && abs(currSpeed) < 10) {
            kickStarting = true;
            finalSpeed = speed;
            if(finalSpeed >= 0)
                targSpeed = kickStartPower;
            else
                targSpeed = int16_t (-1)* kickStartPower;
        } else {
            if(abs(speed) >= kickStartPower) {
                kickStarting = false;
            }
            targSpeed = speed;
        }

    }

}

void Movement::step() {
    if(kickStarting) {
        if(targSpeed == currSpeed) {
            kickStarting = false;
            targSpeed = finalSpeed;
        }
    }

    if(targSpeed == currSpeed)
        return;

    int16_t speedDiff = targSpeed - currSpeed;
    int16_t step = speedDiff / abs(speedDiff) * 4;
    int16_t newSpeed = currSpeed + step;

    Logger::log(TAG, std::to_string(currSpeed));

    motor->setDirection(currSpeed >= 0);
//    Logger::log(TAG, std::to_string(currSpeed) + "-" + std::to_string(newSpeed));
    if(currSpeed != newSpeed)
        motor->setSpeed(static_cast<uint8_t>(abs(newSpeed)*correction));
    currSpeed = newSpeed;
}


