//
// Created by Niels on 4/8/2019.
//

#include <BarBot/Connectivity/AppRequestService.h>


void AppRequestService::update() {
    std::vector<std::string> result = drinkServerConnection->command({"get_app_requests"});
    if (!result.empty() && result.size() >=2) {
        for(size_t i = 0; i < result.size(); i++) {
            reqeustQueue.push({result[i], result[i+1]});
            i++;
        }
    }
}

App_Request noRequest = {
        "",
        ""
};

App_Request AppRequestService::nextRequest() {
    if(reqeustQueue.empty())
        return noRequest;
    App_Request ar = reqeustQueue.front();
    reqeustQueue.pop();
    return ar;
}

void AppRequestService::init(SocketConnection *dsC) {
    drinkServerConnection = dsC;
}

