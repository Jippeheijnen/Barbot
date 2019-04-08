//
// Created by niels on 1/16/2019.
//
#ifndef APICONNECTION_H
#define APICONNECTION_H

#include "Arduino.h"

class APIConnection
{
public:
    APIConnection();
    void wifiConnect(char* SSID, char* password);
    std::vector<int> get();
private:
    int _pin;
};

#endif //APICONNECTION_H
