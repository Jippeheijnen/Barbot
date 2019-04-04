//
// Created by niels on 4/3/2019.
//

#include "BluetoothConnection.h"
#include "BluetoothSocket.h"

void BluetoothConnection::init() {
    pid_t pid = fork();
    if (pid == 0) {
        system("bluetoothctl discoverable on > /dev/null");
        exit(0);
    }

    serverSocket = new BluetoothServerSocket(2,1);

//    std::cout << "listening" << std::endl;
//    while(true) {
//        BluetoothSocket* clientsock = serversock.accept();
//        cout << "accepted from " << clientsock->getForeignAddress().getAddress() << endl;
//        MessageBox& mb = clientsock->getMessageBox();
//
//        string input;
//        while(mb.isRunning()) {
//            input = mb.readMessage();  //blokkeert niet
//            if(input != "") cout << endl << input << endl;
//            //doe andere dingen.
//            cout << ".";
//            cout.flush();
//            usleep(500000); // wacht 500 ms
//        }
//
//        clientsock->close();
//
//    }
}

void BluetoothConnection::poll() {
    try {
        BluetoothSocket *clientSock = serverSocket->accept();
        std::cout << "Connection Accepted" << std::endl;
        clientSockets.push_back(clientSock);
    } catch(BluetoothException & e) {}

    for (size_t i = 0; i < clientSockets.size(); i++) {
        MessageBox &messageBox = clientSockets[i]->getMessageBox();
        if (messageBox.isRunning()) {
            std::string mess = messageBox.readMessage();
            if (!mess.empty()) {
                std::cout << mess << std::endl;
            }

        }
        else {
            std::cout << "Messagebox not running!" << std::endl;
        }
    }
}
