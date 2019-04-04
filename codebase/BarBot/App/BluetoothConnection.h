//
// Created by niels on 4/3/2019.
//

#ifndef BARBOT_BLUETOOTHCONNECTION_H
#define BARBOT_BLUETOOTHCONNECTION_H


#include <BarBot/Events/LineFollow.h>
#include "BluetoothSocket.h"

class BluetoothConnection {
private:
    BluetoothServerSocket *serverSocket;
    std::vector<BluetoothSocket*> clientSockets = {};
    LineFollow *lineFollow;
public:
    BluetoothConnection(const LineFollow &lineFollow);

    BluetoothConnection(LineFollow *lineFollow);

    void init();
    void poll();
};


#endif //BARBOT_BLUETOOTHCONNECTION_H
