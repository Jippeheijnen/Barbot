#include "Bluetooth.h"
#include "../Bluetooth/BluetoothSocket.h"

void openSocket(){
    BluetoothServerSocket serversock(2, 1);  //2 is het channel-number
    cout << "listening" << endl;
}

void acceptConnection(){
    BluetoothSocket* clientsock = serversock.accept();
    cout << "accepted from " << clientsock->getForeignAddress().getAddress() << endl;
    MessageBox& mb = clientsock->getMessageBox();
}

void getBTMessage(){
    input = mb.readMessage();  //blokkeert niet
    if(input != "") cout << endl << input << endl;
    //doe andere dingen.
    cout << ".";
    cout.flush();
}

void closeSocket(){
    clientsock->close();
}