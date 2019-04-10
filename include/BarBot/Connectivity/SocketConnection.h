//
// Created by Niels on 4/2/2019.
//

#ifndef BARBOT_SOCKETCONNECTION_H
#define BARBOT_SOCKETCONNECTION_H
#ifdef __linux__
//linux code goes here
#elif _WIN32
    #define WSMAN_API_VERSION_1_0
    #include <winsock2.h>
    #include <windows.h>
    #include <wsman.h>
#else

#endif

#include <iostream>
#include <vector>
#include <plibsys.h>
#include <psocket.h>


class SocketConnection {
private:
    PSocket * socket;
    char buffer[1025];

    /**
     * CLeans up the socket connections, showing a given error message in the meantime
     * @param message Message to show
     * @param address Socket address to clean up for
     */
    void cleanup(const std::string & message, PSocketAddress * address);
public:
    static const std::string TAG;
    /**
     * Initialize a socket connection
     * @param IP IP Address to connect to
     * @param port Port to connect to
     */
    void init(std::string IP, int port);

    /**
     * Closes this socket connection and cleans it up
     */
    void close();

    /**
     * Reads the next line from the socket connection
     * @return Vector of words in the line
     */
    std::vector<std::string> read_line();

    /**
     * Sends a line to the socket server connected to
     * @param command  Command to send, should be a vector of the words
     */
    void send_line(const std::vector<std::string> & command);

    /**
     * Sends a command and retrieves its result
     * @param command  Command to send
     * @return Command result, vector of words
     */
    std::vector<std::string> command(const std::vector<std::string> &command);
};


#endif //BARBOT_SOCKETCONNECTION_H
