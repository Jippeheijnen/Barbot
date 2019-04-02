#include "Bluetooth.h"
#include "../Bluetooth/BluetoothSocket.h"

using std::cout, std::endl;
void Bluetooth::openSocket(){
    BluetoothServerSocket serversock(2, 1);  //2 is het channel-number
    cout << "listening" << endl;
}

void Bluetooth::acceptConnection(){
    BluetoothSocket* clientsock = serversock.accept();
    cout << "accepted from " << clientsock->getForeignAddress().getAddress() << endl;
    MessageBox& mb = clientsock->getMessageBox();
}

void Bluetooth::getBTInput(){
    input = mb.readMessage();  //blokkeert niet
    if(input != "") cout << endl << input << endl;
    //doe andere dingen.
    cout << ".";
    cout.flush();
}

void Bluetooth::closeSocket(){
    clientsock->close();
}