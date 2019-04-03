//
// Created by niels on 4/3/2019.
//

#ifndef BARBOT_BLUETOOTHCONNECTION_H
#define BARBOT_BLUETOOTHCONNECTION_H


#include "BluetoothSocket.h"

class BluetoothConnection {
private:
    BluetoothServerSocket *serverSocket;
    std::vector<BluetoothSocket*> clientSockets = {};
public:
    void init();
    void poll();
};


#endif //BARBOT_BLUETOOTHCONNECTION_H
