#ifndef BARBOT_BLUETOOTH_H
#define BARBOT_BLUETOOTH_H


class Bluetooth {
private:
    uint_8t direction;
public:
    /**
     * Open the Bluetooth socket
     */
    void openSocket();
    /**
     * Accept Bluetooth connections
     */
    void acceptConnection;
    /**
     * Get Bluetooth input message
     */
    void getBTInput();
    /**
     * Close the Bluetooth socket
     */
    void closeSocket();
};


#endif //BARBOT_BLUETOOTH_H
