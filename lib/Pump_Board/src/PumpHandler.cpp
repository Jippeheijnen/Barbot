//
// Created by niels on 3/28/2019.
//
#include "Arduino.h"
#include <cstdint>
#include "PumpHandler.h"

/**
 * Stores an amount of fluid a pump should dispense
 */
struct PumpAmount {
    uint8_t pump;
    int amount;
};

/**
 * Comparator for pumpamounts, compares by amount
 * @param a First PumpAmount
 * @param b Second PumpAmount
 * @return
 */
bool comparePumpAmounts(PumpAmount a, PumpAmount b)
{
    return (a.amount < b.amount);
}

PumpHandler::PumpHandler() {
    for (uint8_t p : pump_pins) {
        pinMode(p, OUTPUT);
    }
}

void PumpHandler::pumpAmounts(vector<int> amounts) {
    vector<PumpAmount> pumpAmounts = {};
    for(uint8_t i = 0; i < amounts.size(); i++) {
        if(amounts[i] != 0)
            pumpAmounts.push_back({i, amounts[i]});
    }
    if(pumpAmounts.empty())
        return;

    sort(pumpAmounts.begin(), pumpAmounts.end(), comparePumpAmounts);
    int substractsum  = 0;
    for (PumpAmount & p : pumpAmounts) {
        p.amount -= substractsum;
        substractsum += p.amount;
    }

    for(PumpAmount & p : pumpAmounts) {
        Serial.print("Turning on pin ");
        Serial.println(pump_pins[p.pump]);
        digitalWrite(pump_pins[p.pump], HIGH);
    }

    for (PumpAmount & p : pumpAmounts) {
        delay(p.amount);
        digitalWrite(pump_pins[p.pump], LOW);
        Serial.print("Turning off pin ");
        Serial.println(pump_pins[p.pump]);
    }
}
