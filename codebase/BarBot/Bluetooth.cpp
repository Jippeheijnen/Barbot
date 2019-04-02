#include "Bluetooth.h"
#include "../Bluetooth/BluetoothSocket.h"

using std::cout, std::endl;

Movement m;

uint16_t tempBTInput = 0;

void Bluetooth::openSocket(){
    BluetoothServerSocket serversock(2, 1);  //2 is het channel-number
    cout << "listening" << endl;
}

void Bluetooth::acceptConnection(){
    BluetoothSocket* clientsock = serversock.accept();
    cout << "accepted from " << clientsock->getForeignAddress().getAddress() << endl;
    MessageBox& mb = clientsock->getMessageBox();
}

int Bluetooth::getBTInput(){
    return mb.readMesage;
}

void Bluetooth::closeBTSocket(){
    clientsock->close();
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
        if(xdirection&128){
            m.steer(1,(xdirection-128)/2.55)
        }
        else{
            m.steer(0,xdirection/2.55)
        }
        if(ydirection&128){
            m.speed((ydirection-128)/2.55)
        }
        else{
            m.speed(ydirection/2.55)
        }
    }
    tempBTInput = BTInput;
}

