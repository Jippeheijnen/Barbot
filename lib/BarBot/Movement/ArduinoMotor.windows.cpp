//
// Created by niels on 4/5/2019.
//


#include <BarBot/Util/Logger.h>
#include "BarBot/Movement/ArduinoMotor.h"



const std::string ArduinoMotor::TAG = "ArduinoMotor";

void ArduinoMotor::command(const std::string & pack) {
}

void ArduinoMotor::setSpeed(uint8_t speed) {
    Logger::log(TAG, "Setting speed: " + std::to_string(speed));
}

void ArduinoMotor::setDirection(bool rot) {
    Logger::log(TAG, "Setting rotation direction: " + std::to_string(rot));
}

void ArduinoMotor::init() {
}

void ArduinoMotor::clear() {
}








