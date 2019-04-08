
#include <BarBot/Util/Logger.h>
#include "BluetoothConnection.h"

const std::string BluetoothConnection::TAG = "BluetoothConnection";

void BluetoothConnection::init() {
    pid_t pid = fork();
    if (pid == 0) {
        Logger::log(TAG, "Setting Bluetooth To Discoverable");
        system("bluetoothctl discoverable on > /dev/null");
        exit(0);
    }

    serverSocket = new BluetoothServerSocket(2,1);

}

void BluetoothConnection::poll() {
    try {
//        Logger::log(TAG, "Trying to accept a connection");
        BluetoothSocket *clientSock = serverSocket->accept();
        Logger::log(TAG, "Connection Accepted");
        clientSock->getMessageBox();
        clientSockets.push_back(clientSock);

        Logger::log(TAG, "Connection Pushed Back");

    } catch(BluetoothException & e) {}

    for (size_t i = 0; i < clientSockets.size(); i++) {
        Logger::log(TAG, "Getting Message Box");

        MessageBox* messageBox = clientSockets[i]->getMessageBox();

        Logger::log(TAG, "Checking if messagebox is running");
        Logger::log(TAG, typeid(messageBox).name());

        if (messageBox->isRunning()) {
            Logger::log(TAG, "Reading Message");
            std::string mess = messageBox->readMessage();

            if (!mess.empty()) {
                Logger::log(TAG, "Message Received" + mess);
            }

        }
        else {
            Logger::log(TAG, "Message not running!");
        }
    }
}

BluetoothConnection::BluetoothConnection(LineFollow *lineFollow) : lineFollow(lineFollow) {}

