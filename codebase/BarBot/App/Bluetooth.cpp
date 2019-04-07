#include "Bluetooth.h"
#include "../Bluetooth/BluetoothSocket.h"

using std::cout, std::endl;

Movement m;

uint16_t tempBTInput = 0;

void Bluetooth::openSocket(){

    BluetoothServerSocket serverSock(2, 1);  //2 is het channel-number
    cout << "listening" << endl;

}

void Bluetooth::acceptConnection(){

    BluetoothSocket* clientSock = serverSock.accept();
    cout << "accepted from " << clientSock->getForeignAddress().getAddress() << endl;
    MessageBox& mb = clientSock->getMessageBox();

}

int Bluetooth::getBTInput(){

    return mb.readMesage;

}

void Bluetooth::closeBTSocket(){

    clientSock->close();

}

void init(){

    openSocket();
    acceptConnection();

}

void Bluetooth::processBTInput(){

    uint16_t BTInput = getBTInput();
    uint8_t xdirection = direction>>8;
    uint8_t ydirection = direction;

    if(tempBTInput != BTInput){

        xdirection = BTInput;
        ydirection = BTInput >>8;
        if (xdirection&128) m.steer(1,(xdirection-128)/1.27);
        else m.steer(0,xdirection/1.27);

        if (ydirection&128) m.speed((ydirection-128)/1.27);
        else m.speed(ydirection/1.27);

    }

    tempBTInput = BTInput;

}

