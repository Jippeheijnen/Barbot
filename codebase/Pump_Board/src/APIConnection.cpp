/*
  Morse.cpp - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/

//#include <stdio.h>
#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "APIConnection.h"




APIConnection::APIConnection() = default;

void APIConnection::wifiConnect(char *SSID, char *password)
{

    Serial.printf("Connecting to %s \r\n", SSID);
    WiFi.config(IPAddress(192, 168, 137, 81), IPAddress(192, 168, 137, 1), IPAddress(255, 255, 255, 0),
                IPAddress(8, 8, 8, 8), IPAddress(8, 8, 4, 4));
    WiFi.begin(SSID, password);

    while(WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");

    }
    Serial.println("WiFi Connected");
}


std::vector<int> APIConnection::get()
{
    HTTPClient http;
    http.begin("http://sitewolfe.com:8443/pumps" );
    int httpCode = http.GET();
    if(httpCode == 200) {
        std::vector<int> resultVector = {};
        String result = http.getString();
        String currentPart = "";
        for(char c : result) {
            if(c != ' ')
            {
                currentPart += c;
            }
            else {
                resultVector.push_back(currentPart.toInt());
                currentPart = "";
            }
        }
        resultVector.push_back(currentPart.toInt());
        return resultVector;
    }
    else {
        return {};
    }
}