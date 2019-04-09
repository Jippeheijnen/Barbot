//
// Created by Niels on 4/9/2019.
//

#include <iostream>
#include <BarBot/Connectivity/SocketConnection.h>
#include <BarBot/Connectivity/AppRequestService.h>
#include <BarBot/Sensors/LineDetection.h>
#include "LineFollow.h"

#ifndef BARBOT_PATHING_H
#define BARBOT_PATHING_H

const std::string SIDE_LEFT = "LEFT";
const std::string SIDE_RIGHT = "RIGHT";
const std::string SIDE_NONE = "NONE";

struct Location {
    std::string location;
    int node;
    std::string side;
};

class Pathing {
private:
    std::vector<int> colorOrder;
    std::vector<Location> loadedLocations = {};
    SocketConnection* drinkServerConnection;
    AppRequestService* appRequestService;
    LineFollow* lineFollow;
    LineDetection* lineDetection;
    Movement* movement;
    bool hasTarget = false;
    Location currentTarget;
    std::string targetName;
    void acquireTarget();
    int currentIndex = 0;
    int nextColor;

public:
    static const std::string TAG;

    /**
     * Initiates the Pathing class.
     * @param dSC Pointer for drinkServerConnection.
     * @param aRS Pointer for appRequestService.
     * @param lD Pointer for lineDetection.
     * @param lF Pointer for lineFollow.
     * @param m Pointer for movement.
     * @param cO Vector in which the colorOrder is defined.
     */
    void init(SocketConnection* dSC, AppRequestService* aRS, LineDetection * lD, LineFollow * lF, Movement* m, std::vector<int> & cO);
    void step();
};

#endif //BARBOT_PATHING_H
