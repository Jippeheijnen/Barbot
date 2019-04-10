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

/**
 * Script to guide the bot to a destination
 * All destinations are saved in the database
 */
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
    /**
     * If Pathng has no target at the moment, retrieves the next target through AppRequestService
     */
    void acquireTarget();
    int currentIndex = 0;
    int nextColor;
public:
    static const std::string TAG;
    /**
     * Initializes Pathing
     * @param dSC  Reference to the bot's drinkServerConnection instance
     * @param aRS  Reference to the bot's appRequestService instance
     * @param lD  Reference to the bot's lineDetection instance
     * @param lF  Reference to the bot's lineFollow instance
     * @param m  Reference to the bot's movement instance
     * @param cO  Order of colors in which they should appear along the line, so pathing can keep track of its position along the line
     */
    void init(SocketConnection* dSC, AppRequestService* aRS, LineDetection * lD, LineFollow * lF, Movement* m, std::vector<int> & cO);

    /**
     * Steps pathing
     * Checks for colors along the line,
     * Checks if the current destination has been reached
     */
    void step();
};

#endif //BARBOT_PATHING_H
