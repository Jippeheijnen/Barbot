//
// Created by niels on 3/27/2019.
//

#include "Arduino.h"
#include "APIConnection.h"
#include "PumpHandler.h"

APIConnection API;
PumpHandler Pumps;

using std::vector;



void setup() {
    Serial.begin(9600);
    API.wifiConnect("DeInternetKraan", "BarBot2019");

}

void loop() {
    vector<int> pumps = API.get();
    for(int i : pumps) {
        Serial.print(i, 10);
        Serial.print('\t');
    }
    Serial.print('\n');
    Pumps.pumpAmounts(pumps);
    delay(100);
}