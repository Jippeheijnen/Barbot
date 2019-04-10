//
// Created by niels on 3/28/2019.
//

#ifndef ARDUINO_PUMP_PUMPHANDLER_H
#define ARDUINO_PUMP_PUMPHANDLER_H

using std::vector;

/**
 * Code For Arduino
 * Can pump from 4 pumps simultaneously, based on amounts of time in ms
 */
class PumpHandler {
private:
    std::vector<uint8_t> pump_pins = {0, 2, 4, 5};
public:
    PumpHandler();
    void pumpAmounts(vector<int> amounts);
};


#endif //ARDUINO_PUMP_PUMPHANDLER_H
