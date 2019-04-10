
#include <BarBot/Util/Logger.h>
#include <BarBot/Connectivity/AppControlService.h>

#include "BarBot/Connectivity/AppControlService.h"

const std::string AppControlService::TAG = "AppControlService";
const std::string AppControlService::TAG_CTL = "BluetoothCTL";

void AppControlService::init(Movement* mov) {
    movement = mov;
    int fdOut[2], fdErr[2], fdW[2];

    pipe(fdOut);
    pipe(fdErr);
    pipe(fdW);

    pid_t pid = fork();
    fcntl(fdOut[0], F_SETFL, O_NONBLOCK);
    fcntl(fdOut[1], F_SETFL, O_NONBLOCK);

    fcntl(fdErr[0], F_SETFL, O_NONBLOCK);
    fcntl(fdErr[1], F_SETFL, O_NONBLOCK);

    if (pid == 0) {
        Logger::log(TAG_CTL, "Replacing File Pipes");
        dup2(fdOut[1], STDOUT_FILENO);
        dup2(fdErr[1], STDERR_FILENO);
        dup2(fdW[0], STDIN_FILENO);

        Logger::log(TAG_CTL, "Closing Useless Pipes");
        close(fdOut[0]);
        close(fdErr[0]);
        close(fdW[1]);

        Logger::log(TAG_CTL, "Starting ctl");
        char *argm[] = {"/usr/bin/bluetoothctl", "discoverable", "on", nullptr};

        execve(argm[0], argm, nullptr);
        Logger::log(TAG_CTL, std::strerror(errno));
        Logger::log(TAG_CTL, "We probably shouldnt be seeing this, CTL was executed here, error:");
        exit(0);
    }
    else {
        Logger::log(TAG, "Closing Useless Pipes");
        close(fdOut[1]);
        close(fdErr[1]);
        close(fdW[0]);
        ctlPipe[0] = fdOut[0];
        ctlPipe[1] = fdErr[0];
        ctlPipe[2] = fdW[1];


        Logger::log(TAG, "Setting Discoverable On");
        char disc[] = "discoverable on\n";
        write(ctlPipe[2], disc, sizeof(disc));
    }

    Logger::log(TAG, "Making Server Socket");
    try {
        serverSocket = new BluetoothServerSocket(2, 1);
    }
    catch(BluetoothException& e) {
        dieEneKutError = true;
        std::cout << e.what() << std::endl;
    }

}



void AppControlService::relayLogs(int fD) {
    char logBuffer[501];
    long bytesRead = read(fD, logBuffer, 500);
    if(bytesRead != -1) {
        std::string logMessage;
        for(size_t i = 0; i < bytesRead; i++) {
            if(logBuffer[i] == '\n') {
                Logger::log(TAG_CTL, logMessage);
                logMessage = "";
            }
            else
                logMessage += logBuffer[i];
        }
        if(!logMessage.empty())
            Logger::log(TAG_CTL, logMessage);
    }
}

void AppControlService::update() {
    if(dieEneKutError)
        return;
    try {
        BluetoothSocket *clientSock = serverSocket->accept();
        clientSock->getMessageBox();
        clientSockets.push_back(clientSock);

        Logger::log(TAG, "Connection Accepted");

    } catch(BluetoothException & e) {}

    for (size_t i = 0; i < clientSockets.size(); i++) {

        MessageBox* messageBox = clientSockets[i]->getMessageBox();


        if (messageBox->isRunning()) {
            std::string mess =  messageBox->readMessage();

            while(mess != "") {
                if (!mess.empty()) {
                    if (mess[0] == 'J') {
                        std::string xS, yS;
                        bool xDone = false;
                        for(size_t j = 2; j < mess.size(); j++) {
                            if(!xDone) {
                                if(mess[j] == 'Y')
                                    xDone = true;
                                else
                                    xS +=mess[j];
                            } else {
                                yS += mess[j];
                            }
                        }
                        int x = std::stoi(xS)/2;
                        int y = std::stoi(yS)*-2.2;
                        Logger::log(TAG, std::to_string(y));
                        movement->steer(x >= 0, abs(x));
                        movement->speed(y, false);
                    }
                }
                mess = messageBox->readMessage();
            }



        }
        else {
            Logger::log(TAG, "Connection Lost! Removing Socket");
            clientSockets.erase(clientSockets.begin()+i);
            i--;
        }
    }
    relayLogs(ctlPipe[0]);
    relayLogs(ctlPipe[1]);
}

void AppControlService::close_connection() {
    serverSocket->close();
}


