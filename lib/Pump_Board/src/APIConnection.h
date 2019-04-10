//
// Created by niels on 1/16/2019.
//
#ifndef APICONNECTION_H
#define APICONNECTION_H

#include "Arduino.h"

/**
 * Connection to the drinkserver pump part.
 * Retrieves all poured_drink pump values
 */
class APIConnection
{
public:
    APIConnection();
    /**
     * Connects to WiFi network using ESP's wifi library
     * @param SSID Name of the WiFi network to connect to
     * @param password Passphrase to use while connecting
     */
    void wifiConnect(char* SSID, char* password);
    /**
     * Retrieves newest pump request
     * @return List containing the pumps, and amounts to dispense with it
     */
    std::vector<int> get();
private:
    int _pin;
};

#endif //APICONNECTION_H
