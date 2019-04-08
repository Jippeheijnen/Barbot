//
// Created by niels on 4/3/2019.
//

#ifndef BARBOT_BLUETOOTHCONNECTION_H
#define BARBOT_BLUETOOTHCONNECTION_H


#include <BarBot/Scripts/LineFollow.h>
#include <vector>
#if _WIN32
class BluetoothServerSocket{};
class BluetoothSocket{};
#else
#include "BluetoothSocket.h"
#endif

class BluetoothConnection {
private:
    BluetoothServerSocket *serverSocket;
    std::vector<BluetoothSocket*> clientSockets = {};
    LineFollow *lineFollow;
public:
    static const std::string TAG;

    void init(LineFollow *linFol);
    void poll();
};


#endif //BARBOT_BLUETOOTHCONNECTION_H
