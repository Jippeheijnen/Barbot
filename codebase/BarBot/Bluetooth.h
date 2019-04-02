#ifndef BARBOT_BLUETOOTH_H
#define BARBOT_BLUETOOTH_H


#include <cstdint>

class Bluetooth {
public:
    /**
     * Open the Bluetooth socket
     */
    void openSocket();
    /**
     * Accept Bluetooth connections
     */
    void acceptConnection();
    /**
     * Get Bluetooth input message
     */
    int getBTInput();
    /**
     * Close the Bluetooth socket
     */
    void closeBTSocket();
    /**
     * Processes the BT input from getBTInput and sends commands to Movement
     */
    void processBTInput();
    /**
     * Initialises openSocket and acceptConnection
     */
    void init();
};


#endif //BARBOT_BLUETOOTH_H
