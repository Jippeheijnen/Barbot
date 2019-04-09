//
// Created by Niels on 4/9/2019.
//
#include <BarBot/Scripts/Pathing.h>
#include <BarBot/Util/Logger.h>
#include <BarBot/Scripts/LineFollow.h>

const std::string Pathing::TAG = "Pathing";

void Pathing::init(SocketConnection *dSC, AppRequestService * aRS, LineDetection * lD, LineFollow * lF, Movement* m, std::vector<int> & cO) {
    drinkServerConnection = dSC;
    appRequestService = aRS;
    lineDetection = lD;
    colorOrder = cO;
    lineFollow = lF;
    movement = m;

    if(!cO.empty())
        nextColor = cO[0];
    Logger::log(TAG, "Requesting pathing locations");
    std::vector<std::string> results = drinkServerConnection->command({"get_locations"});
    Logger::log(TAG, "Got pathing locations");
    if(results.size()>= 3)
        for(size_t i = 0; i < results.size(); i++) {
            Logger::log(TAG, "-- " + results[i]);
            loadedLocations.push_back({results[i], stoi(results[i+1]), results[i+2]});
            i += 2;
        }
    Logger::log(TAG, "Init Done");
}

void Pathing::acquireTarget() {
    if(!hasTarget) {
        App_Request nextRequest = appRequestService->nextRequest();
        if(!nextRequest.location.empty()) {
            for(Location l : loadedLocations) {
                if(l.location == nextRequest.location) {
                    hasTarget = true;
                    currentTarget = l;
                    targetName = nextRequest.name;
                }
            }
        }
    }
}

void Pathing::step() {
    acquireTarget();

    ColorReading reading = lineDetection->readColor();
    if(!reading.hasChanged)
        return;

    bool markerFound = false;
    if(reading.color == nextColor) {
        currentIndex++;
        nextColor = colorOrder[(currentIndex+1) % colorOrder.size()];
    }

    if(currentIndex >= loadedLocations.size())
        currentIndex = 0;

    if (currentIndex == currentTarget.node && hasTarget) {
        Logger::log(TAG, "We arrived at our destination, let's go");
        lineFollow->pause();
        if(currentTarget.side != SIDE_NONE) {
            movement->steer(currentTarget.side == SIDE_LEFT, 120);
        }
    }
}




