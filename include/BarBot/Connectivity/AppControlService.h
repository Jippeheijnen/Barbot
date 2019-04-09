//
// Created by niels on 4/3/2019.
//

#ifndef BARBOT_APPCONTROLSERVICE_H
#define BARBOT_APPCONTROLSERVICE_H


#include <BarBot/Scripts/LineFollow.h>
#include <vector>
#if _WIN32
class BluetoothServerSocket{};
class BluetoothSocket{};
#else
#include "BluetoothSocket.h"
#endif

class AppControlService {
private:
    BluetoothServerSocket *serverSocket;
    std::vector<BluetoothSocket*> clientSockets = {};
    LineFollow *lineFollow;
    long ctlPipe[3];
public:
    static const std::string TAG;
    static const std::string TAG_CTL;

    void init();
    void relayLogs(int fD);
    void update();
};


#endif //BARBOT_APPCONTROLSERVICE_H
