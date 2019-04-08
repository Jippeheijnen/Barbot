//
// Created by niels on 4/3/2019.
//

#ifndef BARBOT_BLUETOOTHCONNECTION_H
#define BARBOT_BLUETOOTHCONNECTION_H


#include <BarBot/Events/LineFollow.h>
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
    BluetoothConnection(LineFollow *lineFollow);

    void init();
    void poll();
};


#endif //BARBOT_BLUETOOTHCONNECTION_H
