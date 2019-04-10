//
// Created by Niels on 4/8/2019.
//

#include "SocketConnection.h"
#include <iostream>
#include <queue>
#ifndef BARBOT_APPREQUESTSERVICE_H
#define BARBOT_APPREQUESTSERVICE_H

/**
 * Stores a drink request from the App
 */
struct App_Request {
    std::string location;
    std::string name;
};


/**
 * Retrieves requests from the server that were made in the app
 * Stores them in a queue, for FIFO retrieval
 */
class AppRequestService {
private:
    SocketConnection* drinkServerConnection;
    std::queue<App_Request> reqeustQueue;
public:
    std::string TAG = "AppRequestService";
    void init(SocketConnection *dsC);
    void update();

    App_Request nextRequest();
};

#endif //BARBOT_APPREQUESTSERVICE_H
