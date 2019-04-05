
#include "BluetoothConnection.h"

void BluetoothConnection::init() {
    pid_t pid = fork();
    if (pid == 0) {
        system("bluetoothctl discoverable on > /dev/null");
        exit(0);
    }

    serverSocket = new BluetoothServerSocket(2,1);

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

BluetoothConnection::BluetoothConnection(LineFollow *lineFollow) : lineFollow(lineFollow) {}

